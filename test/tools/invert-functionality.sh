#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=
COMPARE_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-invert.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
else
    TOOL=$TOOLDIR/hfst-invert
    FORMAT_TOOL=$TOOLDIR/hfst-format
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    if ! test -x $TOOL; then
	exit 0;
    fi
fi

for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f cat2dog$i ; then
            if ! $TOOL cat2dog$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test dog2cat$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi

done
