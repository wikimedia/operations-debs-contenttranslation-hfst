#!/bin/sh
TOOLDIR=../../tools/src
CONJUNCT_TOOL=
COMPARE_TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    CONJUNCT_TOOL="python3 ./hfst-conjunct.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    CONJUNCT_TOOL=$TOOLDIR/hfst-conjunct
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $CONJUNCT_TOOL $COMPARE_TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f cat_or_dog$i -a -f cat$i ; then
            if ! $CONJUNCT_TOOL cat_or_dog$i cat$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test cat$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi
done
