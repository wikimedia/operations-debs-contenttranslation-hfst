#!/bin/sh

FORMAT_TOOL=
COMPARE_TOOL=
COMPOSE_TOOL=
REGEXP_TOOL=
CONCATENATE_TOOL=
MINIMIZE_TOOL=
CONJUNCT_TOOL=
SUBTRACT_TOOL=
DISJUNCT_TOOL=
STRINGS2FST_TOOL=
FST2TXT_TOOL=

if [ "$1" = "--python" ]; then
    FORMAT_TOOL="python3 ./hfst-format.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    COMPOSE_TOOL="python3 ./hfst-compose.py"
    REGEXP_TOOL="python3 ./hfst-regexp2fst.py"
    CONCATENATE_TOOL="python3 ./hfst-concatenate.py"
    MINIMIZE_TOOL="python3 ./hfst-minimize.py"
    CONJUNCT_TOOL="python3 ./hfst-conjunct.py"
    SUBTRACT_TOOL="python3 ./hfst-subtract.py"
    DISJUNCT_TOOL="python3 ./hfst-disjunct.py"
    STRINGS2FST_TOOL="python3 ./hfst-strings2fst.py"
    FST2TXT_TOOL="python3 ./hfst-fst2txt.py"
else
    TOOLDIR=../../tools/src/
    FORMAT_TOOL=$TOOLDIR/hfst-format
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    COMPOSE_TOOL=$TOOLDIR/hfst-compose
    REGEXP_TOOL=$TOOLDIR/hfst-regexp2fst
    CONCATENATE_TOOL=$TOOLDIR/hfst-concatenate
    MINIMIZE_TOOL=$TOOLDIR/hfst-minimize
    CONJUNCT_TOOL=$TOOLDIR/hfst-conjunct
    SUBTRACT_TOOL=$TOOLDIR/hfst-subtract
    DISJUNCT_TOOL=$TOOLDIR/hfst-disjunct
    STRINGS2FST_TOOL=$TOOLDIR/hfst-strings2fst
    FST2TXT_TOOL=$TOOLDIR/hfst-fst2txt
fi

for ext in .sfst .ofst .foma; do

    FFLAG=
    case $ext in
        .sfst)
            FFLAG="-f sfst"
            if ! ($FORMAT_TOOL --list-formats | grep "sfst" > /dev/null) ; then
                continue;
            fi;;
        .ofst)
            FFLAG="-f openfst-tropical"
            if ! ($FORMAT_TOOL --list-formats | grep "openfst-tropical" > /dev/null) ; then
                continue;
            fi;;
        .foma)
            FFLAG="-f foma"
            if ! ($FORMAT_TOOL --list-formats | grep "foma" > /dev/null) ; then
                continue;
            fi;;
        *)
            FFLAG=;;
    esac

    # composition

    # harmonization:  [a:b] .o. [ID:ID] == [a:b]
    if ! ($COMPOSE_TOOL a2b$ext id$ext | $COMPARE_TOOL -s a2b$ext); then
	echo "compose #1" ${FFLAG}
	exit 1;
    fi
    # harmonization:  [ID:ID] .o. [a:b] == [a:b]
    if ! ($COMPOSE_TOOL id$ext a2b$ext | $COMPARE_TOOL -s a2b$ext); then
	echo "compose #2" ${FFLAG}
	exit 1;
    fi

    # harmonization:  [a:b] .o. [UNK:UNK | ID:ID] == [[a:a] | [a:b] | [a:UNK]]
    if ! ($COMPOSE_TOOL a2b$ext unk2unk_or_id$ext | $COMPARE_TOOL -s a2a_or_a2b_or_a2unk$ext); then
	echo "compose #3" ${FFLAG}
	exit 1;
    fi
    # harmonization:  [UNK:UNK | ID:ID] .o. [a:b] == [[a:b] | [b:b] | [UNK:b]]
    if ! ($COMPOSE_TOOL unk2unk_or_id$ext a2b$ext | $COMPARE_TOOL -s a2b_or_b2b_or_unk2b$ext); then
	echo "compose #4" ${FFLAG}
	exit 1;
    fi


    # no harmonization:    [a:b] .o. [ID:ID] == empty
    if ! ($COMPOSE_TOOL -H a2b$ext id$ext | $COMPARE_TOOL -s empty$ext); then
	echo "compose #5" ${FFLAG}
	exit 1;
    fi
    # no harmonization:    [ID:ID] .o. [a:b] == empty
    if ! ($COMPOSE_TOOL -H id$ext a2b$ext | $COMPARE_TOOL -s empty$ext); then
	echo "compose #6" ${FFLAG}
	exit 1;
    fi

    # no harmonization:    [a:b] .o. [UNK:UNK | ID:ID] == empty
    if ! ($COMPOSE_TOOL -H a2b$ext unk2unk_or_id$ext | $COMPARE_TOOL -s empty$ext); then
	echo "compose #7" ${FFLAG}
	exit 1;
    fi
    # no harmonization:    [UNK:UNK | ID:ID] .o. [a:b] == empty
    if ! ($COMPOSE_TOOL -H unk2unk_or_id$ext a2b$ext | $COMPARE_TOOL -s empty$ext); then
	echo "compose #8" ${FFLAG}
	exit 1;
    fi

    # concatenation
    echo "[?]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[a:b]" | $REGEXP_TOOL ${FFLAG} > tmp2;

    # harmonization
    $CONCATENATE_TOOL tmp1 tmp2 | $MINIMIZE_TOOL > concatenation;
    echo "[[?|a|b] a:b]" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;  # error
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s concatenation result); then
	echo "concatenate #1" ${FFLAG}
	exit 1;
    fi

    # no harmonization
    $CONCATENATE_TOOL -H tmp1 tmp2 | $MINIMIZE_TOOL > concatenation;
    echo "[? a:b]" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s concatenation result); then
	echo "concatenate #2" ${FFLAG}
	exit 1;
    fi
    rm -f concatenation


    ## conjunction
    echo "[?:?]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[a:b]" | $REGEXP_TOOL ${FFLAG} > tmp2;

    # harmonization
    $CONJUNCT_TOOL tmp1 tmp2 | $MINIMIZE_TOOL > conjunction;
    echo "[a:b]" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s conjunction result); then
	echo "concatenate #1" ${FFLAG}
	exit 1;
    fi

    # no harmonization
    $CONJUNCT_TOOL -H tmp1 tmp2 | $MINIMIZE_TOOL > conjunction;
    echo "[] - []" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s conjunction result); then
	echo "concatenate #2" ${FFLAG}
	exit 1;
    fi
    rm -f conjunction

    # disjunction
    echo "[?]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[a:b]" | $REGEXP_TOOL ${FFLAG} > tmp2;

    # harmonization
    $DISJUNCT_TOOL tmp1 tmp2 | $MINIMIZE_TOOL > disjunction;
    echo "[?|a|b|a:b]" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s disjunction result); then
	echo "concatenate #1" ${FFLAG}
	exit 1;
    fi

    # no harmonization
    $DISJUNCT_TOOL -H tmp1 tmp2 | $MINIMIZE_TOOL > disjunction;
    echo "[?|a:b]" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s disjunction result); then
	echo "concatenate #2" ${FFLAG}
	exit 1;
    fi
    rm -f disjunction


    ## subtraction
    echo "[?:?]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[a:b]" | $REGEXP_TOOL ${FFLAG} > tmp2;

    # harmonization FOMA FAILS
    $SUBTRACT_TOOL tmp1 tmp2 | $MINIMIZE_TOOL > subtraction;
    echo "[?:?|a:?|?:a|b:?|?:b|b:a|a|b]" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s subtraction result); then
	echo "subtract #1" ${FFLAG}
	exit 1;
    fi

    # no harmonization
    $SUBTRACT_TOOL -H tmp1 tmp2 | $MINIMIZE_TOOL > subtraction;
    echo "[?:?]" | $REGEXP_TOOL -H ${FFLAG} | $MINIMIZE_TOOL > result;
    # do not harmonize when comparing, the transducers must be exactly the same
    if ! ($COMPARE_TOOL -H -s subtraction result); then
	echo "subtract #2" ${FFLAG}
	exit 1;
    fi
    rm -f subtraction

    ## substitution
    echo "\`[[a:b ?] , c , d ]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[a:b ?]" | $REGEXP_TOOL ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "substitution test #1" ${FFLAG}
	exit 1;
    fi

    echo "\`[[a:b ?] , b , B C D ]" | $REGEXP_TOOL -H ${FFLAG} > tmp1;
    echo "[[a:B | a:C | a:D] [?]]" | $REGEXP_TOOL -H ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "substitution test #2" ${FFLAG}
	exit 1;
    fi

    echo "\`[[?] , a , b ]" | $REGEXP_TOOL -H ${FFLAG} > tmp1;
    echo "[?]" | $REGEXP_TOOL -H ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "substitution test #3" ${FFLAG}
	exit 1;
    fi

    echo "\`[[a b a:b] , a , ]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[]-[]" | $REGEXP_TOOL ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "substitution test #4" ${FFLAG}
	exit 1;
    fi

    echo "\`[[ [a|c] b [a:b|d:e]] , a , ]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[c b d:e]" | $REGEXP_TOOL ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "substitution test #5" ${FFLAG}
	exit 1;
    fi

    ## freely insert aka ignore
    echo "[?] / a" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[a* [?|a] a*]" | $REGEXP_TOOL -H ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "freely insert (aka ignore) test #1" ${FFLAG}
	exit 1;
    fi

    echo "[?|a] / a:0" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[[a:0]* [?|a] [a:0]*]" | $REGEXP_TOOL -H ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "freely insert (aka ignore) test #2" ${FFLAG}
	exit 1;
    fi

    echo "[?|a] / [a b]" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "[[a b]* [?|a|b] [a b]*]" | $REGEXP_TOOL -H ${FFLAG} > tmp2;
    if ! ($COMPARE_TOOL -H tmp1 tmp2 > /dev/null); then
	echo "freely insert (aka ignore) test #3" ${FFLAG}
	exit 1;
    fi

    ## some cases
    echo "a:?" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "a:?|a" | $REGEXP_TOOL ${FFLAG} > tmp3;
    if ! ($COMPARE_TOOL -H tmp1 tmp3 > /dev/null); then
	echo "[a:?] == [a:?|a] test" ${FFLAG}
	exit 1;
    fi

    echo "?:b" | $REGEXP_TOOL ${FFLAG} > tmp1;
    echo "?:b|b" | $REGEXP_TOOL ${FFLAG} > tmp3;
    if ! ($COMPARE_TOOL -H tmp1 tmp3 > /dev/null); then
	echo "[?:b] == [?:b|b] test" ${FFLAG}
	exit 1;
    fi

    ## test that special symbols @_.*_@ are never harmonized
    echo "@_foo_@" | $STRINGS2FST_TOOL -S ${FFLAG} > tmp1;
    echo "[?:?]" | $REGEXP_TOOL ${FFLAG} > tmp2;
    # using command line binary tools
    for tool in "$COMPOSE_TOOL" "$CONCATENATE_TOOL" "$CONJUNCT_TOOL" "$DISJUNCT_TOOL" "$SUBTRACT_TOOL"
    do
	$tool tmp1 tmp2 | $FST2TXT_TOOL | tr '\t' ' ' > result
	if (grep "@_foo_@ @_UNKNOWN_SYMBOL_@" result > /dev/null); then
	    echo "special symbols" $tool ${FFLAG}
	    exit 1;
	fi
	if (grep "@_UNKNOWN_SYMBOL_@ @_foo_@" result > /dev/null); then
	    echo "special symbols" $tool ${FFLAG}
	    exit 1;
	fi
    done
    # and using regex parser operators
    for operator in ".o." " " "&" "|" "-"
    do
	echo '?:?' $operator '"@_foo_@"' | $REGEXP_TOOL ${FFLAG} | \
	    $FST2TXT_TOOL | tr '\t' ' ' > result
	if (grep "@_foo_@ @_UNKNOWN_SYMBOL_@" result > /dev/null); then
	    echo "special symbols" $tool ${FFLAG}
	    exit 1;
	fi
	if (grep "@_UNKNOWN_SYMBOL_@ @_foo_@" result > /dev/null); then
	    echo "special symbols" $tool ${FFLAG}
	    exit 1;
	fi
    done

    ## test special symbols in replace rules


    ## test ".#." which is a special symbol in foma
    if ! (echo '[".#." ".#."]' | $REGEXP_TOOL ${FFLAG} | $FST2TXT_TOOL > /dev/null); then
	echo "special symbol '.#.'" ${FFLAG}
	exit 1
    fi

    if ! (echo '["@#@" "@#@"]' | $REGEXP_TOOL ${FFLAG} | $FST2TXT_TOOL > /dev/null); then
	echo "special symbol '@#@'" ${FFLAG}
	exit 1
    fi

    if ! (echo '["@#@" ".#."]' | $REGEXP_TOOL ${FFLAG} | $FST2TXT_TOOL > /dev/null); then
	echo "special symbols '.#.' and '#@£'" ${FFLAG}
	exit 1
    fi


done

rm -f tmp1 tmp2 tmp3 result
