#!/bin/sh
TOOLDIR=../../tools/src
DET_TOOL=
COMPARE_TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    DET_TOOL="python3 ./hfst-determinize.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    DET_TOOL=$TOOLDIR/hfst-determinize
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $DET_TOOL $COMPARE_TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f non_minimal$i ; then
            if ! $DET_TOOL non_minimal$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test non_minimal$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi
done
