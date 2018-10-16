#!/bin/sh
TOOLDIR=../../tools/src
TOOL1=
TOOL2=

if [ "$1" = '--python' ]; then
    TOOL1="python3 ./hfst-strings2fst.py"
    TOOL2="python3 ./hfst-fst2strings.py"
else
    TOOL1=$TOOLDIR/hfst-strings2fst
    TOOL2=$TOOLDIR/hfst-fst2strings
    if ! test -x $TOOL1; then
	exit 0;
    fi
    if ! test -x $TOOL2; then
	exit 0;
    fi
fi

if ! $TOOL1 $srcdir/utf-8.strings > test ; then
    exit 1
fi
if ! $TOOL2 < test > test.strings ; then
    exit 1
fi
rm test test.strings
