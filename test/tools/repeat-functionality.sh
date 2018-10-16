#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
COMPARE_TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-repeat.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    TOOL=$TOOLDIR/hfst-repeat
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $TOOL $COMPARE_TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f cat$i -a -f 2to4cats$i -a -f 0to3cats$i \
            -a -f 4cats$i -a -f 4toINFcats$i ; then
            if ! $TOOL -f 2 -t 4 cat$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test 2to4cats$i  ; then
                exit 1
            fi
            if ! $TOOL -t 3 cat$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test 0to3cats$i  ; then
                exit 1
            fi
            if ! $TOOL -f 4 -t 4 cat$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test 4cats$i  ; then
                exit 1
            fi
            if ! $TOOL -f 4 cat$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test 4toINFcats$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi
done
