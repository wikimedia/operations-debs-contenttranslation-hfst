#!/bin/sh
TOOLDIR=../../tools/src
if ! $TOOLDIR/hfst-optimized-lookup cat2dog.hfstol < $srcdir/cat.strings > test.lookups ; then
    exit 1
fi

# Bug 123
echo > empty
if ! $TOOLDIR/hfst-optimized-lookup cat2dog.hfstol < empty > test.lookups ; then
    exit 1
fi

rm test.lookups empty
