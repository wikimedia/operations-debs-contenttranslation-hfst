#!/bin/sh
TOOLDIR=../../tools/src
TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-strings2fst.py"
else
    TOOL=$TOOLDIR/hfst-strings2fst
    if ! test -x $TOOL; then
	exit 0;
    fi
fi

$TOOL $srcdir/latin-1.strings > test \
    2> /dev/null
RV=$?
rm test
exit $RV
