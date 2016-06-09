#!/bin/sh
TOOLDIR=../../tools/src
$TOOLDIR/hfst-strings2fst $srcdir/latin-1.strings > test \
    2> /dev/null
RV=$?
rm test
exit $RV
