#!/bin/sh
TOOLDIR=../../tools/src
CONCAT_TOOL=
COMPARE_TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    CONCAT_TOOL="python3 ./hfst-concatenate.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    CONCAT_TOOL=$TOOLDIR/hfst-concatenate
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $CONCAT_TOOL $COMPARE_TOOL $FORMAT_TOOL; do	
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f cat$i -a -f dog$i ; then
            if ! $CONCAT_TOOL cat$i dog$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test catdog$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi
done
