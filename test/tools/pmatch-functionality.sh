#!/bin/sh
TOOLDIR=../../tools/src
TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-pmatch.py"
else
    TOOL=$TOOLDIR/hfst-pmatch
    if ! test -x $TOOL; then
	exit 77;
    fi
fi

if [ "$srcdir" = "" ] ; then
    srcdir=. ;
fi
if ! $TOOL pmatch_endtag.pmatch < $srcdir/cat.strings > test.lookups ; then
    exit 1
fi

# test equality of output
if ! echo "cat" | $TOOL pmatch_endtag.pmatch > test.pmatch; 
    then
        exit 1
    fi
    if ! grep -q "<animal>cat</animal>" test.pmatch; then
        echo "FAIL: cat should be tagged as animal"
        exit 1
    fi
    
rm test.pmatch test.lookups

if [ "$1" != '--python' ]; then
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
fi
