#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
        if test -f cat$i -a -f dog$i ; then
            if ! $TOOLDIR/hfst-disjunct cat$i dog$i > test ; then
                exit 1
            fi
            if ! $TOOLDIR/hfst-compare -s test cat_or_dog$i  ; then
                exit 1
            fi
            rm test;
        fi
    fi
done
