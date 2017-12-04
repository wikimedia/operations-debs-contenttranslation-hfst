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
    
rm test.pmatch test.lookups

# Jyrki's suite
if ! $srcdir/pmatch-tests.sh --log none; then
    if [ -e $srcdir/pmatch-tests.sh.* ]; then
        rm $srcdir/pmatch-tests.sh.*
    fi
    exit 1
fi

if [ -e $srcdir/pmatch-tests.sh.* ]; then
    rm $srcdir/pmatch-tests.sh.*
fi
