#!/bin/sh
TOOLDIR=../../tools/src
TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-optimized-lookup.py"
else
    TOOL=$TOOLDIR/hfst-optimized-lookup
    if ! test -x $TOOL; then
	exit 0;
    fi
fi

if ! $TOOL cat2dog.hfstol < $srcdir/cat.strings > test.lookups ; then
    exit 1
fi

# Bug 123
echo > empty
if ! $TOOL cat2dog.hfstol < empty > test.lookups ; then
    exit 1
fi

rm test.lookups empty
