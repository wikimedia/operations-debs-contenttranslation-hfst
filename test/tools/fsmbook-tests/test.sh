# check for programs

COMPILE_FROM_SCRATCH="false"
COMPILE_XFST_SCRIPT="true"
COMPILE_HFST_SCRIPT="true"
EXIT_IF_NOT_EQUIVALENT="true"

HFST_TOOL="../../../tools/src/parsers/hfst-xfst"

if [ "$COMPILE_XFST_SCRIPT" = "true" ]; then
    if ! (ls $HFST_TOOL > /dev/null); then
        echo "ERROR: Could not find "$HFST_TOOL" that is needed to run the tests"
        exit 1
    fi
fi
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

if ! [ "$1" = "" ]; then
    examples=$1
fi

for example in $examples;
do
    echo "Testing "$example"..."

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
    
    # (1) If xfst solution exists,
    if ! [ "$example" = "FinnishNumerals" -o \
        "$example" = "FinnishProsody" -o \
        "$example" = "Palindromes" ]; then

        # compile with xfst/foma, if needed..
        if [ "$COMPILE_FROM_SCRATCH" = "true" ]; then
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

        # and convert from prolog to openfst-tropical for comparing.
        cp Result Result.prolog
        if ! (cat Result | $tooldir/hfst-txt2fst --prolog -f $common_format > tmp && \
            mv tmp Result_from_xfst); then
            echo "ERROR: in converting result from xfst/foma to hfst format"
            exit 1;
        fi

        # Also compile with hfst-xfst using all back-end formats..
        if [ "$COMPILE_XFST_SCRIPT" == "true" ]; then
        for format in $backend_formats; 
        do
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
            # and convert from prolog to openfst-tropical and compare the results.
            if ! (cat Result | $tooldir/hfst-txt2fst --prolog -f $common_format > tmp && \
                mv tmp Result_from_hfst_xfst); then
                echo "ERROR: in converting result from hfst prolog to binary format"
                exit 1;
            fi
            if ! ($tooldir/hfst-compare $compare_flags Result_from_xfst Result_from_hfst_xfst); then
                echo "FAIL: results from xfst and hfst-xfst ("$format") are not equivalent, storing results in files:"
                echo "    log/"$example.result_from_xfst_script_using_xfst_tool 
                echo "    log/"$example.result_from_hfst_xfst_using_backend_format_$format
                if ! [ -d log ]; then
                    mkdir log
                fi
                cp Result_from_xfst log/$example.result_from_xfst_script_using_xfst_tool
                cp Result_from_hfst_xfst log/$example.result_from_hfst_xfst_using_backend_format_$format
                if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                    exit 1;
                fi
            fi
        done
        fi

    fi

    # (2) Compile hfst script with all back-end formats and compare the results..
    if [ "$COMPILE_HFST_SCRIPT" = "true" ]; then
    for format in $backend_formats; 
    do
        if (! $tooldir/hfst-format --list-formats | grep $format > /dev/null); then
            echo "  skipping compilation of hfst script using back-end format "$format" as it is not available"
            continue;
        fi

        echo "  compiling hfst script with back-end format "$format".."

        if [ "$example" = "FinnishNumerals" ]; then
            if ! [ -f tmpdir/NumbersToNumerals ]; then
                echo "FAIL: missing file tmpdir/NumbersToNumerals in test FinnishNumerals,"
                echo "      the test NumbersToNumerals must be run first"
                exit 1
            fi
        fi

        if ! ($SH hfst-scripts/$example.hfst.script $format $tooldir); then
            echo "ERROR: compilation of hfst script failed"
            exit 1
        fi
        cat Result | $tooldir/hfst-fst2fst -f $common_format > tmp
        mv tmp Result_from_hfst_script_$format
        
        # with the result from xfst/foma, if available..
        if ! [ "$example" = "FinnishNumerals" -o \
            "$example" = "FinnishProsody" -o \
            "$example" = "Palindromes" ]; then
            # special case 1
            if [ "$example" = "EinsteinsPuzzle" ]; then
                if ! ($tooldir/hfst-fst2strings --xfst=print-space Result_from_xfst | grep "German coffee Prince fish" > /dev/null); then
                    echo "  FAIL: Results differ"
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                        exit 1;
                    fi
                fi
                if ! ($tooldir/hfst-fst2strings Result_from_hfst_script_$format | \
                      grep "fish" | grep "German coffee Prince fish" > /dev/null); then
                    echo "  FAIL: Results differ"
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                        exit 1;
                    fi
                fi
                continue
            fi
            # special case 2
            if [ "$example" = "NumbersToNumerals" ]; then
                if ! [ -d tmpdir ]; then
                    mkdir tmpdir
                fi
                cp Result_from_xfst tmpdir/NumbersToNumerals # needed in FinnishNumerals
                $tooldir/hfst-fst2strings Result_from_xfst | sort > tmp_xfst
                $tooldir/hfst-fst2strings Result_from_hfst_script_$format | sort > tmp_hfst
                if ! (diff tmp_xfst tmp_hfst); then
                    echo "  FAIL: Results differ"
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                        exit 1;
                    fi
                fi
                rm -f tmp_hfst tmp_xfst
                continue
            fi
            if ! ($tooldir/hfst-compare $compare_flags Result_from_xfst Result_from_hfst_script_$format); then
                echo "  FAIL: Results from xfst and hfst scripts ("$format") differ in test "$example", storing results in files:"
                echo "    log/"$example.result_from_xfst_script_using_xfst_tool 
                echo "    log/"$example.result_from_hfst_script_using_backend_format_$format
                if ! [ -d log ]; then
                    mkdir log
                fi
                cp Result_from_xfst log/$example.result_from_xfst_script_using_xfst_tool
                cp Result_from_hfst_script_$format log/$example.result_from_hfst_script_using_backend_format_$format
                if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                    exit 1;
                fi
            fi
            
        # or with the result in common format.
        else
            # special case
            if [ "$example" = "FinnishNumerals" -a "$format" = "sfst" ]; then
                echo "    skipping comparing the results, result from SFST will be big because of epsilon handling in composition.."
                continue
            fi

            if ! [ "$format" = "$common_format" ]; then
                if ! ($tooldir/hfst-compare $compare_flags Result_from_hfst_script_$common_format Result_from_hfst_script_$format); then
                    echo -n "  FAIL: Results from hfst scripts ("$format" and "$common_format") differ in test "$example
                    echo ", storing results in files:"
                    echo "    log/"$example.result_from_hfst_script_using_backend_format_$format
                    echo "    log/"$example.result_from_hfst_script_using_backend_format_$common_format
                    if ! [ -d log ]; then
                        mkdir log
                    fi
                    cp Result_from_hfst_script_$common_format log/$example.result_from_hfst_script_using_backend_format_$common_format
                    cp Result_from_hfst_script_$format log/$example.result_from_hfst_script_using_backend_format_$format
                    if [ "$EXIT_IF_NOT_EQUIVALENT" = "true" ]; then
                        exit 1;
                    fi
                fi
            fi
        fi
    done
    fi

done

rm -f Result_from_xfst Result
for format in $backend_formats;
do 
    rm -f Result_from_hfst_script_$format
done

echo ""
echo "**********"
echo "All fsmbook tests that were performed passed."
#echo "Returning a skip value because result from DateParser test is compared with result from foma"
#echo "instead of xfst, because foma and xfst handle symbols that are enclosed in square brackets"
#echo "differently."
echo "**********"
echo ""
#exit 77
