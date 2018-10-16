#!/bin/sh
TOOLDIR=../../tools/src
CI_TOOL=
CALCULATE_TOOL=
COMPARE_TOOL=

if [ "$1" = '--python' ]; then
    CI_TOOL="python3 ./hfst-compose-intersect.py"
    CALCULATE_TOOL="python3 ./hfst-calculate.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
else
    CI_TOOL=$TOOLDIR/hfst-compose-intersect
    CALCULATE_TOOL=$TOOLDIR/hfst-calculate
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    for tool in $CI_TOOL $CALCULATE_TOOL $COMPARE_TOOL;
    do	
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
    FFLAG=
    case $i in
        .sfst)
            FFLAG="-f sfst";;
        .ofst)
            FFLAG="-f openfst-tropical";;
        .foma)
            FFLAG="-f foma";;
        *)
            FFLAG=;;
    esac
    if test -f cat$i ; then
        if ! echo "cat|dog" | $CALCULATE_TOOL $FFLAG > lexicon ; then
            exit 1
        fi
        if ! echo "([catdog]|d:D|c:C)*" | $CALCULATE_TOOL $FFLAG > rules ; then
            exit 1
        fi
        if ! echo "([catdog]|d:D|c:C)*" | $CALCULATE_TOOL $FFLAG >> rules ; then
            exit 1
        fi
        if ! $CI_TOOL -1 lexicon -2 rules > test ; then
            exit 1
        fi
        if ! echo "cat|dog|{cat}:{Cat}|{dog}:{Dog}" | $CALCULATE_TOOL $FFLAG > test2 ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test test2  ; then
            exit 1
        fi
        rm test test2 lexicon rules
    fi
done
