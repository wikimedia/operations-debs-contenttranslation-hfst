#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
    if test -f cat2dog$i -a -f dog2cat$i ; then
        if ! cat cat2dog$i dog2cat$i | $TOOLDIR/hfst-head -n 1 > test ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -s test cat2dog$i  ; then
            exit 1
        fi
        rm test;
        if ! cat cat2dog$i dog2cat$i | $TOOLDIR/hfst-head -n -1 > test ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -s test cat2dog$i  ; then
            exit 1
        fi
        rm test;
    fi
fi
done
