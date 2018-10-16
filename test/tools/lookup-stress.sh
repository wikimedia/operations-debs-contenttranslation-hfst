#!/bin/sh
TOOLDIR=../../tools/src
TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-lookup.py"
else
    TOOL=$TOOLDIR/hfst-lookup
    if ! test -x $TOOL; then
	exit 0;
    fi
fi

for i in "" ol .sfst .ofst .foma; do
    if test -f cat2dog$i ; then
        for c in 1 256 65536 16777216 ; do
            echo doing $c times cat in $i
            if ! yes cat | head -n $c | $TOOL cat2dog$i > /dev/null ; then
                echo "died with $? ($PIPESTATUS)"
                exit 1
            fi
        done
    fi
done

