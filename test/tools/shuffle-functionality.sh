#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=
COMPARE_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-shuffle.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
else
    TOOL=$TOOLDIR/hfst-shuffle
    FORMAT_TOOL=$TOOLDIR/hfst-format
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    for tool in $TOOL $FORMAT_TOOL $COMPARE_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

if ! [ -x $TOOLDIR/hfst-shuffle ]; then
    exit 0;
fi

for i in .sfst .ofst .foma; do
    if ! $FORMAT_TOOL --test-format `echo $i | sed "s/.//"`; then
	continue;
    fi

    if ! $TOOL ab$i bc$i > TMP; then
	rm TMP;
	exit 1;
    else
	if ! $COMPARE_TOOL TMP ab_shuffle_bc$i > /dev/null 2>&1; then
	    rm TMP;
	    exit 1;
	fi
    fi
    if ! $TOOL id$i id$i > TMP; then
	rm TMP;
	exit 1;
    else
	if ! $COMPARE_TOOL TMP id_shuffle_id$i > /dev/null 2>&1; then
	    rm TMP;
	    exit 1;
	fi
    fi
    if ! $TOOL aid$i idb$i > TMP; then
	rm TMP;
	exit 1;
    else
	if ! $COMPARE_TOOL TMP aid_shuffle_idb$i > /dev/null 2>&1; then
	    rm TMP;
	    exit 1;
	fi
    fi
    if $TOOL a2b$i ab$i > /dev/null 2>&1; then
	rm TMP;
	exit 1;
    fi
    rm TMP;
done
