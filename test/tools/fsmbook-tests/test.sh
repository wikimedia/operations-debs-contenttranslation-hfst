
if [ "$1" = "-h" -o "$1" = "--help" ]; then
    echo ""
    echo "Usage: "$0" [TESTNAME] [--python PYTHON] [--pythonpath PYTHONPATH]"
    echo ""
    echo "  TESTNAME: The name of the test that will be run. If not given, all tests are run."
    echo "    PYTHON: Python that is used to run the tests instead of hfst-xfst (e.g. 'python3.5')."
    echo "PYTHONPATH: Path that is prepended to sys.path when running tests with python (with --python)."
    echo ""
    exit 0
fi

# check for programs

COMPILE_FROM_SCRATCH="false"
COMPILE_XFST_SCRIPT="true"
COMPILE_HFST_SCRIPT="true"
EXIT_IF_NOT_EQUIVALENT="true"

PYTHON=""
PYTHONPATH=""

HFST_TOOL="../../../tools/src/parsers/hfst-xfst"

if [ "$COMPILE_FROM_SCRATCH" = "true" ]; then
    if ! (which xfst > /dev/null); then
        echo "ERROR: Could not find program 'xfst' that is needed to run the tests"
        exit 1
    fi
    if ! (which foma > /dev/null); then
        echo "ERROR: Could not find program 'foma' that is needed to run the tests"
        exit 1
    fi
fi

XFST="xfst -q"
FOMA="foma -q"
HFST=$HFST_TOOL" -q"
SH="/bin/bash"

compare_flags="-q"

# location of hfst tools
tooldir="../../../tools/src/"
# back-end formats used in testing (common format must be listed first as it is used for comparison)    
backend_formats="openfst-tropical sfst foma"
# back-end format used when comparing results
common_format="openfst-tropical" 

# NOTE: FinnishNumerals depends on NumbersToNumerals, so they must be compiled in the right order.

examples="BetterColaMachine BrazilianPortuguese1 BrazilianPortuguese2 EnglishNumerals "\
"EsperantoAdjectives EsperantoNounsAdjectivesAndVerbs EsperantoNounsAndAdjectivesWithTags "\
"EsperantoNounsAndAdjectives EsperantoNouns FinnishOTProsody Lingala "\
"MonishAnalysis MonishGuesserAnalyzer NumbersToNumerals PlusOrMinus FinnishNumerals "\
"YaleShooting FinnishProsody Palindromes EinsteinsPuzzle"

if [ "$1" = "--python" ]; then
    PYTHON=$2
    if [ "$3" = "--pythonpath" ]; then
	PYTHONPATH=$4
    fi
else
    if ! [ "$1" = "" ]; then
	examples=$1
    fi
    if [ "$examples" = "FinnishNumerals" ]; then
	echo "FinnishNumerals depends on NumbersToNumerals, running tests for both"
	examples="NumbersToNumerals FinnishNumerals"
    fi
fi

if [ "$2" = "--python" ]; then
    PYTHON=$3
    if [ "$4" = "--pythonpath" ]; then
	PYTHONPATH=$5
    fi
fi

if [ "$PYTHON" == "" ]; then
    if [ "$COMPILE_XFST_SCRIPT" = "true" ]; then
	if ! (ls $HFST_TOOL > /dev/null); then
            echo "ERROR: Could not find "$HFST_TOOL" that is needed to run the tests"
            exit 1
	fi
    fi
fi

for example in $examples;
do
    echo "Testing "$example"..."

    # If flags must be eliminated when comparing the results
    if [ "$example" = "EsperantoAdjectives" -o \
        "$example" = "EsperantoNounsAdjectivesAndVerbs" -o \
        "$example" = "EsperantoNounsAndAdjectivesWithTags" -o \
        "$example" = "EsperantoNounsAndAdjectives" -o \
        "$example" = "EsperantoNouns" ]; then
        # lexc produces a transducer that has flags
        compare_flags="-q --eliminate-flags"
    else
        compare_flags="-q"
    fi

    # Check if xfst solution exists
    XFST_SOLUTION_EXISTS="true"
    if [ "$example" = "FinnishNumerals" -o \
	 "$example" = "FinnishProsody" -o \
	 "$example" = "Palindromes" ]; then
	XFST_SOLUTION_EXISTS="false";
    fi

    # (1) Generate or copy the expected result to file 'Expected_result'
    if [ "$COMPILE_FROM_SCRATCH" = "true" -a "$XFST_SOLUTION_EXISTS" = "true" ]; then
	# if foma must be used instead of xfst
        if [ "$example" = "FinnishOTProsody" -o \
			"$example" = "Lingala" -o \
			"$example" = "DateParser" -o \
			"$example" = "YaleShooting" ]; then
            if [ "$example" = "DateParser" ] ; then
                echo "  compiling with foma (result from xfst will not be equivalent"
                echo "  because symbols enclosed in square brackets are not harmonized)"
            else
                echo "  compiling with foma (result from xfst will be too big)"
            fi
            if ! ($FOMA -f xfst-scripts/$example.xfst.script > /dev/null 2> LOG); then
                echo "ERROR: compiling with foma failed"
                cat LOG
                exit 1
            fi
        else
            echo "  compiling with xfst.."
            if ! ($XFST -f xfst-scripts/$example.xfst.script 2> LOG); then
                echo "ERROR: compiling with xfst failed"
                cat LOG
                exit 1;
            fi
        fi
    else
        if ! [ -e expected-results/$example.prolog ]; then
            echo "ERROR: file expected-results/"$example".prolog missing"
            exit 1
        else
            cp expected-results/$example.prolog Result
        fi
    fi
    # convert from prolog to openfst-tropical for comparing.
    cp Result Result.prolog
    if ! [ "$PYTHON" == "" ]; then
	if ! (cat Result | $PYTHON prolog2fst.py $common_format $PYTHONPATH > tmp && \
		     mv tmp Expected_result); then
            echo "ERROR: in converting result from xfst/foma to hfst format"
            exit 1;
	fi
    else
	if ! (cat Result | $tooldir/hfst-txt2fst --prolog -f $common_format > tmp && \
		     mv tmp Expected_result); then
            echo "ERROR: in converting result from xfst/foma to hfst format"
            exit 1;
	fi
    fi
    rm -f Result.prolog
    # The expected result is now in file 'Expected_result' in prolog format
    
    # (2) Compile with hfst-xfst or hfst python api using all back-end formats..
    if [ "$COMPILE_XFST_SCRIPT" == "true" -a "$XFST_SOLUTION_EXISTS" = "true" ]; then
        for format in $backend_formats; 
        do
	    if ! [ "$PYTHON" == "" ]; then
		if (! $PYTHON list_formats.py $PYTHONPATH | grep $format > /dev/null); then
                    echo "  skipping compilation with hfst-xfst using back-end format "$format" as it is not available"
                    continue;
		fi
		echo "  compiling xfst with HFST python API using back-end format "$format".."
		if ! ($PYTHON compile_xfst.py $format xfst-scripts/$example.xfst.script $PYTHONPATH); then
		    echo "ERROR: compilation of xfst with HFST python API failed"
		    cat LOG;
		    exit 1;
		fi
	    else
		if ! [ -x $HFST_TOOL ]; then
                    echo "  warning: skipping compilation with hfst-xfst, assuming configured off"
                    continue;
		fi
		if (! $tooldir/hfst-format --list-formats | grep $format > /dev/null); then
                    echo "  skipping compilation with hfst-xfst using back-end format "$format" as it is not available"
                    continue;
		fi
		echo "  compiling with hfst-xfst using back-end format "$format".."
		if ! ($HFST -f $format -F xfst-scripts/$example.xfst.script); then
                    echo "ERROR: compilation with hfst-xfst failed"
                    cat LOG;
                    exit 1;
		fi
	    fi
            # and convert from prolog to openfst-tropical and compare the results.
	    if ! [ "$PYTHON" == "" ]; then
		if ! (cat Result | $PYTHON prolog2fst.py $common_format $PYTHONPATH > tmp && \
			     mv tmp Result_from_hfst_xfst); then
		    echo "ERROR: in converting result from hfst prolog to binary format"
		    exit 1;
		fi
	    else
		if ! (cat Result | $tooldir/hfst-txt2fst --prolog -f $common_format > tmp && \
			     mv tmp Result_from_hfst_xfst); then
		    echo "ERROR: in converting result from hfst prolog to binary format"
		    exit 1;
		fi
	    fi
	    if ! [ "$PYTHON" = "" ]; then
		if ! ($PYTHON compare.py Expected_result Result_from_hfst_xfst $compare_flags $PYTHONPATH); then
		    echo "FAIL: results from xfst and hfst-xfst ("$format") are not equivalent, storing results in files:"
                    echo "    log/"$example.result_from_xfst_script_using_xfst_tool 
                    echo "    log/"$example.result_from_hfst_xfst_using_backend_format_$format
                    if ! [ -d log ]; then
			mkdir log
                    fi
                    cp Expected_result log/$example.result_from_xfst_script_using_xfst_tool
                    cp Result_from_hfst_xfst log/$example.result_from_hfst_xfst_using_backend_format_$format
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
			exit 1;
                    fi
		fi
	    else
		if ! ($tooldir/hfst-compare $compare_flags Expected_result Result_from_hfst_xfst); then
                    echo "FAIL: results from xfst and hfst-xfst ("$format") are not equivalent, storing results in files:"
                    echo "    log/"$example.result_from_xfst_script_using_xfst_tool 
                    echo "    log/"$example.result_from_hfst_xfst_using_backend_format_$format
                    if ! [ -d log ]; then
			mkdir log
                    fi
                    cp Expected_result log/$example.result_from_xfst_script_using_xfst_tool
                    cp Result_from_hfst_xfst log/$example.result_from_hfst_xfst_using_backend_format_$format
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
			exit 1;
                    fi
		fi
	    fi
	    rm -f Result_from_hfst_xfst
        done
    fi

    # (3) Compile hfst script with all back-end formats and compare the results..
    if [ "$COMPILE_HFST_SCRIPT" = "true" ]; then
    for format in $backend_formats; 
    do
	if ! [ "$PYTHON" == "" ]; then
	    if (! $PYTHON list_formats.py $PYTHONPATH | grep $format > /dev/null); then
		echo "  skipping compilation of hfst script using back-end format "$format" as it is not available"
		continue;
            fi
	else
            if (! $tooldir/hfst-format --list-formats | grep $format > /dev/null); then
		echo "  skipping compilation of hfst script using back-end format "$format" as it is not available"
		continue;
            fi
	fi

        if [ "$example" = "FinnishNumerals" ]; then
            if ! [ -f tmpdir/NumbersToNumerals ]; then
                echo "FAIL: missing file tmpdir/NumbersToNumerals in test FinnishNumerals,"
                echo "      the test NumbersToNumerals must be run first"
                exit 1
            fi
        fi

	if ! [ "$PYTHON" == "" ]; then
	    if [ -e python-scripts/$example.hfst.py ]; then
		echo "  compiling script with HFST python API using back-end format "$format".."
		if ! ($PYTHON python-scripts/$example.hfst.py $format $PYTHONPATH); then
		    echo "ERROR: compilation of script with HFST python API failed"
		    cat LOG;
		    exit 1;
		fi
	    else
		echo "  no python script found for "$example", using hfst script instead"
		if ! ($SH hfst-scripts/$example.hfst.script $format $tooldir); then
		    echo "ERROR: compilation of hfst script failed"
		    exit 1
		fi
            fi
	else
	    echo "  compiling hfst script with back-end format "$format".."
            if ! ($SH hfst-scripts/$example.hfst.script $format $tooldir); then
		echo "ERROR: compilation of hfst script failed"
		exit 1
            fi
	fi
	if ! [ "$PYTHON" = "" ]; then
	    cat Result | $PYTHON fst2fst.py $common_format $PYTHONPATH > tmp
	else
            cat Result | $tooldir/hfst-fst2fst -f $common_format > tmp
	fi
        mv tmp Result_from_hfst_script_$format
        
        # special case 1
        if [ "$example" = "EinsteinsPuzzle" ]; then
	    echo '(generating all word forms from xfst result, this can take a while)'
	    if ! [ "$PYTHON" = "" ]; then
		if ! (cat Expected_result | $PYTHON fst2strings_space.py $PYTHONPATH | grep "German coffee Prince fish" > /dev/null); then
                    echo "  FAIL: Results differ"
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
			exit 1;
                    fi
		fi
	    else
		if ! ($tooldir/hfst-fst2strings --xfst=print-space Expected_result | grep "German coffee Prince fish" > /dev/null); then
                    echo "  FAIL: Results differ"
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
			exit 1;
                    fi
		fi
	    fi
	    echo '(generating all word forms from hfst result, this can take a while)'
	    if ! [ "$PYTHON" = "" ]; then
		if ! (cat Result_from_hfst_script_$format | $PYTHON fst2strings.py $PYTHONPATH | \
			     grep "fish" | grep "German coffee Prince fish" > /dev/null); then
                    echo "  FAIL: Results differ"
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
			exit 1;
                    fi
		fi
	    else
		if ! ($tooldir/hfst-fst2strings Result_from_hfst_script_$format | \
			     grep "fish" | grep "German coffee Prince fish" > /dev/null); then
                    echo "  FAIL: Results differ"
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
			exit 1;
                    fi
		fi
	    fi
            continue
        fi
        # special case 2
        if [ "$example" = "NumbersToNumerals" ]; then
            if ! [ -d tmpdir ]; then
                mkdir tmpdir
            fi
            cp Expected_result tmpdir/NumbersToNumerals # needed in FinnishNumerals
	    if ! [ "$PYTHON" = "" ]; then
		cat Expected_result | $PYTHON fst2strings.py $PYTHONPATH | sort > tmp_xfst
		cat Result_from_hfst_script_$format | $PYTHON fst2strings.py $PYTHONPATH | sort > tmp_hfst
	    else
		$tooldir/hfst-fst2strings Expected_result | sort > tmp_xfst
		$tooldir/hfst-fst2strings Result_from_hfst_script_$format | sort > tmp_hfst
	    fi
            if ! (diff tmp_xfst tmp_hfst); then
                echo "  FAIL: Results differ"
                if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                    exit 1;
                fi
            fi
            rm -f tmp_hfst tmp_xfst
            continue
        fi
	# special case 3
        if [ "$example" = "FinnishNumerals" -a "$format" = "sfst" ]; then
            echo "    skipping comparing the results, result from SFST will be big because of epsilon handling in composition.."
            continue
        fi

	if ! [ "$PYTHON" = "" ]; then
	    if ! ($PYTHON compare.py Expected_result Result_from_hfst_script_$format $compare_flags $PYTHONPATH); then
		echo "  FAIL: Results from xfst and hfst scripts ("$format") differ in test "$example", storing results in files:"
		echo "    log/"$example.result_from_xfst_script_using_xfst_tool 
		echo "    log/"$example.result_from_hfst_script_using_backend_format_$format
		if ! [ -d log ]; then
                    mkdir log
		fi
		cp Expected_result log/$example.result_from_xfst_script_using_xfst_tool
		cp Result_from_hfst_script_$format log/$example.result_from_hfst_script_using_backend_format_$format
		if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                    exit 1;
		fi
            fi
	else
            if ! ($tooldir/hfst-compare $compare_flags Expected_result Result_from_hfst_script_$format); then
		echo "  FAIL: Results from xfst and hfst scripts ("$format") differ in test "$example", storing results in files:"
		echo "    log/"$example.result_from_xfst_script_using_xfst_tool 
		echo "    log/"$example.result_from_hfst_script_using_backend_format_$format
		if ! [ -d log ]; then
                    mkdir log
		fi
		cp Expected_result log/$example.result_from_xfst_script_using_xfst_tool
		cp Result_from_hfst_script_$format log/$example.result_from_hfst_script_using_backend_format_$format
		if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                    exit 1;
		fi
            fi
	fi
    done
    fi

done

rm -f Expected_result Result
for format in $backend_formats;
do 
    rm -f Result_from_hfst_script_$format
done

rm -f tmpdir/NumbersToNumerals
if [ -d "tmpdir" ]; then
    rmdir tmpdir
fi

echo ""
echo "**********"
echo "All fsmbook tests that were performed passed."
echo "**********"
echo ""

