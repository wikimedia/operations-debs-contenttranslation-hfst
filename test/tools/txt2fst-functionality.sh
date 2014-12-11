#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
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
        if ! $TOOLDIR/hfst-txt2fst $FFLAG $srcdir/cat.txt > test ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -s test cat$i  ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-txt2fst --prolog $FFLAG $srcdir/cat.prolog > test ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -s test cat$i  ; then
            exit 1
        fi
        rm test
    fi
fi
done
