#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-summarize.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    TOOL=$TOOLDIR/hfst-summarize
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
    if test -f cat$i ; then
        if ! $TOOL cat$i > test.txt ; then
            exit 1
        fi
        rm test.txt;
    fi
fi
done
