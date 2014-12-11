#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
        if test -f non_minimal$i ; then
            if ! $TOOLDIR/hfst-minimize non_minimal$i > test ; then
                exit 1
            fi
            if ! $TOOLDIR/hfst-compare -s test non_minimal$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi
done
