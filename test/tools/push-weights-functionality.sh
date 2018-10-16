#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
COMPARE_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-push-weights.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
else
    TOOL=$TOOLDIR/hfst-push-weights
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    for tool in $TOOL $COMPARE_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

if ! $TOOL -p initial cat2dog.hfst > test ; then
    exit 1
fi
if ! $COMPARE_TOOL -s test cat2dog.hfst  ; then
    exit 1
fi
if ! $TOOL -p final cat2dog.hfst > test ; then
    exit 1
fi
if ! $COMPARE_TOOL -s test cat2dog.hfst  ; then
    exit 1
fi
rm test
