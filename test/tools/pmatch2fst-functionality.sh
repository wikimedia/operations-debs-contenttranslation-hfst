#!/bin/sh
TOOLDIR=../../tools/src
if [ "$srcdir" = "" ] ; then
    srcdir=. ;
fi

if ! $TOOLDIR/hfst-pmatch2fst $srcdir/pmatch_blanks.txt > test ; then
        exit 1
    fi
# Test with any old string
if ! $TOOLDIR/hfst-pmatch test < $srcdir/cat.strings > pmatch.out ; then
        exit 1
    fi
rm -f pmatch.out test
exit 0
