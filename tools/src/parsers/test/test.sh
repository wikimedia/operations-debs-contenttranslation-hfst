#!/bin/sh

XFST_TOOL="../hfst-xfst -s --pipe-mode"
STRINGS2FST="../../hfst-strings2fst -S"
TXT2FST="../../hfst-txt2fst"
COMPARE="../../hfst-compare --quiet"
DIFF="diff --ignore-blank-lines"
LIST_FORMATS="../../hfst-format --list-formats"
EXTRA_FILES="tmp startup"
REMOVE="rm -f"

for format in sfst openfst-tropical foma;
do
    # Test if implementation type is available.
    if ! (${LIST_FORMATS} | grep $format > /dev/null); then
	continue;
    fi

    ## Create a transducer [Foo Bar Baz] where Foo is [foo], Bar [bar] and Baz [Baz].
    ## Definition of Foo is given in startup file, and definitions of Bar and Baz
    ## on command line. Baz is later undefined in input.
    echo "define Foo foo" > startup
    if ! ((echo "undefine Baz" && echo "regex Foo Bar Baz;" && echo "save stack tmp") | \
	${XFST_TOOL} -f $format -l startup \
	-e "define Bar bar;" -e "define Baz baz;" > /dev/null 2> /dev/null)
    then
	${REMOVE} ${EXTRA_FILES}
        echo "fail #1";
	exit 1
    fi

    # Test that the result is as intended.
    if ! (echo "foo bar Baz" | ${STRINGS2FST} -f $format | ${COMPARE} tmp);
    then
	${REMOVE} ${EXTRA_FILES}
        echo "fail #2";
	exit 1
    fi

    # Create a transducer with literal words "define" and "regex".
    for word in define regex
    do
	if ! ((echo "regex "$word";" && echo "save stack tmp") | ${XFST_TOOL} -f $format > /dev/null 2> /dev/null)
	then
	    ${REMOVE} ${EXTRA_FILES}
            echo "fail #3";
	    exit 1
	fi
        # Test that the result is as intended.
	if ! (echo $word | ${STRINGS2FST} -f $format | ${COMPARE} tmp);
	then
	    ${REMOVE} ${EXTRA_FILES}
            echo "fail #4";
	    exit 1
	fi
    done

    ## Test that using special symbols in replace rules yields an error message
    if ! (echo 'regex a -> "@_foo_@";' | ../hfst-xfst --pipe-mode -f $format > /dev/null 2> tmp && grep "warning:" tmp > /dev/null); then
        echo "fail #5";
	exit 1;
    fi
    # silent mode
    if (echo 'regex a -> "@_foo_@";' | ../hfst-xfst --pipe-mode -s -f $format > /dev/null 2> tmp && grep "warning:" tmp > /dev/null); then
        echo "fail #6";
	exit 1;
    fi

    ## Test that using incompatible replace types in parallel rules yields an error message
    if (!(echo 'regex a -> b ,, c (->) d ;' | ../hfst-xfst --pipe-mode -f $format > /dev/null 2> tmp) && grep "failed" tmp > /dev/null); then
        echo "fail #6.5";
        exit 1;
    fi

    ## Test that the transducer info is correct
    if ! (echo 'regex [a|b|c|d|e] ([d|e|f|g]);' | ../hfst-xfst --pipe-mode -f $format > tmp 2> /dev/null); then
        echo "fail #7";
        exit 1;
    fi
    if (! grep "3 states" tmp > /dev/null); then
        echo "here 1"
        exit 1;
    fi
    if (! grep "9 arcs" tmp > /dev/null); then
        echo "here 2"
        exit 1;
    fi

    ## Test that the result of testfile.xfst (written in att format to standard output)
    ## is the same as testfile.att using att-to-fst conversion.
    for testfile in compose_net concatenate_net union_net ignore_net invert_net minus_net intersect_net \
	determinize_net epsilon_remove_net invert_net minimize_net negate_net \
	one_plus_net prune_net reverse_net sort_net upper_side_net zero_plus_net lower_side_net \
	define define_function prolog \
        substitute_symbol_1 substitute_symbol_2 substitute_symbol_3 \
        substitute_symbol_4 substitute_symbol_5 \
        substitute_label_1 substitute_label_2 substitute_label_3 substitute_label_4 \
        substitute_label_5 substitute_label_6 substitute_label_7 substitute_label_8 \
        substitute_defined_1 substitute_defined_2 substitute_defined_3 \
        substitute_defined_4 substitute_defined_5 substitute_defined_6 \
        at_re_1 at_re_2 at_re_3 at_txt at_stxt at_txt_and_stxt at_pl \
        quoted_literals replace_identity
        # substitute_symbol_6 fails on sfst
        # angle_brackets omitted, since xfst and foma handle them differently
    do
	rm -f result result1 result2
	if ! (ls $testfile.xfst 2> /dev/null); then
	    echo "skipping missing test for "$testfile"..."
	    continue
	fi
	if ! (cat $testfile.xfst | ../hfst-xfst --pipe-mode -q -f $format > result 2> /dev/null); then
	    echo "ERROR: in compiling "$testfile".xfst"
	    exit 1;
	fi
	if ! (cat result | ${TXT2FST} > tmp1; cat $testfile.att | ${TXT2FST} > tmp2; ); then
	    echo "ERROR: in compiling "$testfile".att"
	    exit 1;
	fi
	if ! (${COMPARE} tmp1 tmp2); then
	    echo "ERROR: "$testfile" test failed"
	    exit 1;
	fi
    done

    ## Test that testfile_fail fails.
    #for testfile in define_fail
    #do
#	if ! (ls $testfile.xfst 2> /dev/null); then
#	    echo "skipping missing test for "$testfile"..."
#	    continue
#	fi
#	if ! (cat $testfile.xfst | ../hfst-xfst -s -f $format 2> tmp > /dev/null); then
#	    echo "ERROR: in compiling "$testfile".xfst"
#	    exit 1;
#	fi
#	if ! (grep "xre parsing failed" tmp > /dev/null); then
#	    echo "ERROR: in "$testfile".xfst"
#	    exit 1;
#	fi
#    done

    ## Test that the result of testfile.xfst (written to standard output)
    ## is the same as testfile.output
    for testfile in print_stack print_labels print_label_tally \
	shortest_string set_variable info print_net eliminate_flag empty_context xerox_composition
    do
	if ! (ls $testfile.xfst 2> /dev/null); then
	    echo "skipping missing test for "$testfile"..."
	    continue
	fi
        # apply up/down leak to stdout with readline..
	if ! (cat $testfile.xfst | ../hfst-xfst --pipe-mode -f $format -s | tr -d '\r' > tmp); then
	    echo "ERROR: in compiling "$testfile.xfst
	    exit 1;
	fi
	if ! ($DIFF tmp $testfile.output > tmpdiff); then
            if (ls $testfile.alternative_output > /dev/null 2> /dev/null); then
                if ! ($DIFF tmp $testfile.alternative_output); then
                    rm -f tmpdiff
                    echo "ERROR: in result from "$testfile.xfst
                    exit 1;
                fi
            else
                cat tmpdiff
                rm -f tmpdiff
	        echo "ERROR: in result from "$testfile.xfst
	        exit 1;
            fi
            rm -f tmpdiff
	fi
    done

    ## Interactive commands
    for testfile in apply_up apply_down inspect_net
    do
	if ! (ls $testfile.xfst 2> /dev/null); then
	    echo "skipping missing test for "$testfile"..."
	    continue
	fi
        # apply up/down leak to stdout with readline..
        for param in --pipe-mode # --no-readline
        do
            # 'inspect net' requires input from stdin
            if (test "$param" = "--pipe-mode" -a "$testfile" = "inspect_net"); then
                continue
            fi
	    if ! (cat $testfile.xfst | ../hfst-xfst $param -f $format -s | tr -d '\r' > tmp); then
	    echo "ERROR: in compiling "$testfile.xfst" with parameters "$param
	    exit 1;
	    fi
	    if ! ($DIFF tmp $testfile.output > tmpdiff); then
                if (ls $testfile.alternative_output > /dev/null 2> /dev/null); then
                    if ! ($DIFF tmp $testfile.alternative_output); then
                        rm -f tmpdiff
                        echo "ERROR: in result from "$testfile.xfst
                        exit 1;
                    fi
                else
                    cat tmpdiff
                    rm -f tmpdiff
	            echo "ERROR: in result from "$testfile.xfst
	            exit 1;
                fi
                rm -f tmpdiff
	    fi
        done
    done


    ## Test that the results of testfile_true.xfst and testfile_false.xfst (written to file tmp)
    ## contain the lines listed in files test_true.input and test_false.output, respectively.
    for testcase in _true _false # whether we test the positive or negative case
    do
	for testfile in test_overlap test_sublanguage # the function to be tested
	do
	    if ! (ls $testfile$testcase.xfst 2> /dev/null); then
		echo "skipping missing test for "$testfile$testcase"..."
		continue
	    fi
	    if ! (cat $testfile$testcase.xfst | ../hfst-xfst --pipe-mode -s -f $format | tr -d '\r' > tmp); then
		echo "ERROR: in compiling "$testfile$testcase.xfst
		exit 1;
	    fi
	    if ! ($DIFF tmp "test"$testcase.output); then
		echo "ERROR: in testing "$testfile$testcase.xfst
		exit 1;
	    fi
	done
    done

    for file in quit-on-fail.xfst assert.xfst
    do
        if (cat $file | ../hfst-xfst --pipe-mode -s -f $format > tmp 2> /dev/null); then
            echo "ERROR: in compiling "$file
            exit 1;
        fi
        if (grep '^fail' tmp > /dev/null); then
            echo "ERROR: in testing "$file
            exit 1;
        fi
        if ! (grep '^pass' tmp > /dev/null); then
            echo "ERROR: in testing "$file
            exit 1;
        fi
    done

    if [ "$format" = "openfst-tropical" ]; 
    then
        for file in weighted_replace_right_1 weighted_replace_right_2 \
        weighted_replace_right_3 weighted_replace_right_4 weighted_replace_right_5 \
        weighted_replace_right_6 weighted_replace_right_7 weighted_replace_right_8 \
        weighted_replace_right_9 \
        weighted_optional_replace_right_1 weighted_optional_replace_right_2 \
        weighted_optional_replace_right_3 weighted_optional_replace_right_4 \
        weighted_optional_replace_right_5 \
        weighted_optional_replace_right_6 weighted_optional_replace_right_7 \
        weighted_optional_replace_right_8 weighted_optional_replace_right_9 \
        weighted_ltr_longest_match_1 weighted_ltr_longest_match_2 weighted_ltr_longest_match_3 \
        weighted_ltr_shortest_match_1 weighted_ltr_shortest_match_2 weighted_ltr_shortest_match_3
        do
	    if ! (ls $file.xfst 2> /dev/null); then
	        echo "skipping missing test for "$file"..."
	        continue
	    fi
            if ! (cat $file.xfst | ../hfst-xfst --pipe-mode -s -f $format | tr -d '\r' > tmp 2> /dev/null); then
                echo "ERROR: in compiling "$file".xfst"
                exit 1;
            fi
            if ! (cat tmp | ${STRINGS2FST} -j -f $format > tmp1 2> /dev/null); then
                echo "ERROR: in compiling result file from "$file".xfst"
                exit 1;
            fi
            if ! (cat $file.result | ${STRINGS2FST} -j -f $format > tmp2 2> /dev/null); then
                echo "ERROR: in compiling file "$file".result"
                exit 1;
            fi
	    if ! (${COMPARE} tmp1 tmp2); then
	        echo "ERROR: "$file" test failed"
	        exit 1;
	    fi
        done
        for file in contains contains_with_weight contains_once contains_once_optional \
            replace_test_1 replace_test_2 replace_test_3 replace_test_4 replace_test_5 \
            replace_test_6 replace_test_7 replace_test_8 replace_test_9 replace_test_10 \
            replace_test_11 replace_test_12 replace_test_13 replace_test_14 replace_test_15 \
            replace_test_16 replace_test_17 replace_test_18 replace_test_19 replace_test_20 \
            replace_test_21 replace_test_22 replace_test_23 replace_test_24 replace_test_25 \
            replace_test_26 replace_test_27 replace_test_28 replace_test_29 replace_test_30 \
            replace_test_31 replace_test_32 replace_test_33 replace_test_34 replace_test_35 \
            replace_test_36 replace_test_37 replace_test_38 replace_test_39 replace_test_40 \
            replace_test_41 replace_test_42 replace_test_43 replace_test_44 replace_test_45 \
            replace_test_46 replace_test_47 replace_test_48 replace_test_49 replace_test_50 \
            replace_test_51 replace_test_52 replace_test_53 \
            weighted_parallel_rules_1 weighted_parallel_rules_2 weighted_parallel_rules_3 \
            weighted_parallel_rules_4 weighted_parallel_rules_5 weighted_parallel_rules_6 \
            weighted_parallel_rules_7 weighted_parallel_rules_8 weighted_parallel_rules_9 \
            weighted_parallel_rules_10 weighted_parallel_rules_11
        do
            if ! (ls $file.xfst 2> /dev/null); then
	        echo "skipping missing test for "$file"..."
	        continue
	    fi
            if ! (cat $file.xfst | ../hfst-xfst --pipe-mode -s -f $format | tr -d '\r' > tmp 2> /dev/null); then
                echo "ERROR: in compiling "$file".xfst"
                exit 1;
            fi
            if ! (diff $file.output tmp); then
	        echo "ERROR: "$file" test failed"
	        exit 1;
	    fi
        done
    fi

    rm -f result tmp1 tmp2 foo

## add properties
# alias
# apropos
# cleanup net
# clear stack
# collect epsilon-loops
# compact sigma
# compile-replace lower
# compile-replace upper
# complete net
# crossproduct net
# echo
# edit properties
# eliminate flag
# help
# ignore net
# inspect net
# label net
# list
# load defined
# load stack
# name net
# pop stack
# print aliases
# print arc-tally
# print defined
# print directory
# print file-info
# print flags
# print label-maps
# print labels
# print label-tally
# print list
# print lists
# print longest-string
# print longest-string-size
# print lower-words
# print name
# print net
# print random-lower
# print random-upper
# print random-words
# print shortest-string
# print shortest-string-size
# print sigma
# print sigma-tally
# print sigma-word-tally
# print size
# print upper-words
# print words
# push defined
# quit
# read att
# read lexc
# read prolog
# read properties
# read regex
# read spaced-text
# read text
# rotate stack
# save defined
# save stack
# set
# show
# shuffle net
# sigma net
# source
# substitute defined
# substitute label
# substitute symbol
# substring net
# system
# test equivalent
# test lower-bounded
# test lower-universal
# test non-null
# test null
# test overlap
# test sublanguage
# test upper-bounded
# test upper-universal
# turn stack
# twosided flag-diacritics
# undefine
# unlist
# write att
# write definition
# write definitions
# write dot
# write prolog
# write properties
# write spaced-text
# write text



done

${REMOVE} ${EXTRA_FILES}
exit 0;

