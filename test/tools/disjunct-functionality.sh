#!/bin/sh
TOOLDIR=../../tools/src
DISJUNCT_TOOL=
FORMAT_TOOL=
COMPARE_TOOL=

if [ "$1" = '--python' ]; then
    DISJUNCT_TOOL="python3 ./hfst-disjunct.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
else
    DISJUNCT_TOOL=$TOOLDIR/hfst-disjunct
    FORMAT_TOOL=$TOOLDIR/hfst-format
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    for tool in $DISJUNCT_TOOL $FORMAT_TOOL $COMPARE_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f cat$i -a -f dog$i ; then
            if ! $DISJUNCT_TOOL cat$i dog$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test cat_or_dog$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi
done
