#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
COMPARE_TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-tail.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
else
    TOOL=$TOOLDIR/hfst-tail
    FORMAT_TOOL=$TOOLDIR/hfst-format
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    for tool in $TOOL $FORMAT_TOOL $COMPARE_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
    if test -f cat2dog$i -a -dog2cat$i ; then
        if ! cat cat2dog$i dog2cat$i | $TOOLDIR/hfst-tail -n 1 > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test dog2cat$i  ; then
            exit 1
        fi
        rm test;
        if ! cat cat2dog$i dog2cat$i | $TOOL -n +2 > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test dog2cat$i  ; then
            exit 1
        fi
        rm test;
    fi
fi
done
