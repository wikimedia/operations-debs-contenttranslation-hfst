#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
    if test -f cat$i ; then
        if ! $TOOLDIR/hfst-summarize cat$i > test.txt ; then
            exit 1
        fi
        rm test.txt;
    fi
fi
done
