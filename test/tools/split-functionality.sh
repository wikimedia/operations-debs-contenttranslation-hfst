#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
COMPARE_TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-split.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    TOOL=$TOOLDIR/hfst-split
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
    if test -f cat2dog$i -a -f dog2cat$i ; then
        if ! (cat cat2dog$i dog2cat$i | $TOOL) ; then
            exit 1
        fi
        if ! ($COMPARE_TOOL -s 1.hfst cat2dog$i)  ; then
            rm 1.hfst 2.hfst
            exit 1
        fi
        if ! ($COMPARE_TOOL -s 2.hfst dog2cat$i)  ; then
            rm 1.hfst 2.hfst
            exit 1
        fi
        rm 1.hfst 2.hfst;
    fi
fi
done
