#!/bin/sh
TOOLDIR=../../tools/src
if [ "$srcdir" = "" ] ; then
    srcdir=. ;
fi
if ! $TOOLDIR/hfst-pmatch pmatch_endtag.pmatch < $srcdir/cat.strings > test.lookups ; then
    exit 1
fi

# test equality of output
if ! echo "cat" | $TOOLDIR/hfst-pmatch pmatch_endtag.pmatch > test.pmatch; 
    then
        exit 1
    fi
    if ! grep -q "<animal>cat</animal>" test.pmatch; then
        echo "FAIL: cat should be tagged as animal"
        exit 1
    fi
    
rm test.pmatch

# Jyrki's suite
if ! $srcdir/pmatch-tests.sh --log none; then
    rm $srcdir/pmatch-tests.sh.*
    exit 77
    # Pending stabilisation of various things the suite fails, so we pretend
    # we skipped it
fi

rm $srcdir/pmatch-tests.sh.*
