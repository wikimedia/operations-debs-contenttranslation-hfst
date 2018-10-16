#!/bin/sh
TOOLDIR=../../tools/src
TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-reweight.py"
else
    TOOL=$TOOLDIR/hfst-reweight
    if ! test -x $TOOL; then
	exit 0;
    fi
fi

for i in "" .sfst .ofst .foma; do
    if test -f heavycat$i ; then
        if ! $TOOL -a 1 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -b 3.141 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -a 10 -b 0.001 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -F cos heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -a 11 -b 0.5 -F sin heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -l 1000 -a 1 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -u 100000 -a 1 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -l 1000 -u 100000 -a 1 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -S c -a 1 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -I c -a 1 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -O c -a 1 heavycat$i > test ; then
            exit 1
        fi
        if ! $TOOL -I c -O c -a 1 heavycat$i > test ; then
            exit 1
        fi
    fi
done

