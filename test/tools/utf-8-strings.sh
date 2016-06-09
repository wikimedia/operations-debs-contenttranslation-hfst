#!/bin/sh
TOOLDIR=../../tools/src
if ! $TOOLDIR/hfst-strings2fst $srcdir/utf-8.strings > test ; then
    exit 1
fi
if ! $TOOLDIR/hfst-fst2strings < test > test.strings ; then
    exit 1
fi
rm test test.strings
