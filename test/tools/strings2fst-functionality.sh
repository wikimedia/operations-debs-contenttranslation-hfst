#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=
COMPARE_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-strings2fst.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
else
    TOOL=$TOOLDIR/hfst-strings2fst
    FORMAT_TOOL=$TOOLDIR/hfst-format
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    for tool in $TOOL $FORMAT_TOOL $COMPARE_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

if [ "$srcdir" = "" ]; then
    srcdir="./";
fi

for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
    FFLAG=
    case $i in
        .sfst)
            FFLAG="-f sfst";;
        .ofst)
            FFLAG="-f openfst-tropical";;
        .foma)
            FFLAG="-f foma";;
        *)
            FFLAG=;;
    esac
    if test -f cat$i ; then
        if ! $TOOL $FFLAG $srcdir/cat.strings > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test cat$i ; then
            exit 1
        fi
        rm test
        if ! $TOOL $FFLAG -S $srcdir/c_a_t.strings > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test cat$i ; then
            exit 1
        fi
        rm test
    fi
    if test -f heavycat$i ; then
        if ! $TOOL $FFLAG $srcdir/heavycat.strings > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test heavycat$i ; then
            exit 1
        fi
        rm test
    fi
    if test -f cat2dog$i ; then
        if ! $TOOL $FFLAG $srcdir/cat2dog.strings > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test cat2dog$i > /dev/null 1>&1 ; then
            exit 1
        fi
        if ! $TOOL $FFLAG -S $srcdir/cat2dog.spaces > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test cat2dog$i > /dev/null 1>&1 ; then
            exit 1
        fi
        if ! $TOOL $FFLAG -p -S $srcdir/cat2dog.pairs > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test cat2dog$i > /dev/null 1>&1 ; then
            exit 1
        fi
        if ! $TOOL $FFLAG -p $srcdir/cat2dog.pairstring > test ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test cat2dog$i > /dev/null 1>&1 ; then
            exit 1
        fi
        if ! $TOOL $FFLAG $srcdir/dos.strings > test.hfst ; then
            exit 1
        fi
        if ! $COMPARE_TOOL -s test.hfst cat$i ; then
            exit 1
        fi
        rm test.hfst
    fi
fi
done

