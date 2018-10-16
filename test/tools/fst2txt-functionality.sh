#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-fst2txt.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    TOOL=$TOOLDIR/hfst-fst2txt
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

if [ "$srcdir" = "" ]; then
    srcdir="./";
fi

TOOLDIR=$TOOLDIR

cat $srcdir/cat.txt | tr -d '\r' > TMP;
mv TMP $srcdir/cat.txt;

for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
    if test -f cat$i ; then
        if ! $TOOL -D < cat$i > test.txt 2> /dev/null ; then
            exit 1
        fi
        if ! diff test.txt $srcdir/cat.txt > /dev/null 2>&1 ; then
            exit 1
        fi
	if ! $TOOL -f prolog < cat$i > test.txt 2> /dev/null ; then
            exit 1
        fi
	if [ "$1" != '--python' ]; then
            if ! $TOOL -f dot < cat$i > test.txt 2> /dev/null ; then
		exit 1
            fi
            if which dot > /dev/null 2>&1 ; then
		if ! dot test.txt > /dev/null 2>&1 ; then
                    exit 1
		fi
            fi
            if ! $TOOL -f pckimmo < cat$i > test.txt 2> /dev/null ; then
		exit 1
            fi
	fi
        rm test.txt
    fi
fi
done
