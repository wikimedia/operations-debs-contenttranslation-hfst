#!/bin/sh
TOOLDIR=../../tools/src

if [ "$srcdir" = "" ]; then
    srcdir="./";
fi

TOOLDIR=$TOOLDIR

cat $srcdir/cat.txt | tr -d '\r' > TMP;
mv TMP $srcdir/cat.txt;

for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
    if test -f cat$i ; then
        if ! $TOOLDIR/hfst-fst2txt -D < cat$i > test.txt ; then
            exit 1
        fi
        if ! diff test.txt $srcdir/cat.txt > /dev/null 2>&1 ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-fst2txt -f dot < cat$i > test.txt ; then
            exit 1
        fi
        if which dot > /dev/null 2>&1 ; then
            if ! dot test.txt > /dev/null 2>&1 ; then
                exit 1
            fi
        fi
        if ! $TOOLDIR/hfst-fst2txt -f pckimmo < cat$i > test.txt ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-fst2txt -f prolog < cat$i > test.txt ; then
            exit 1
        fi
        rm test.txt
    fi
fi
done
