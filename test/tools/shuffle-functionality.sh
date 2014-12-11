#!/bin/sh
TOOLDIR=../../tools/src
if ! [ -x $TOOLDIR/hfst-shuffle ]; then
    exit 0;
fi

for i in .sfst .ofst .foma; do
    if ! $TOOLDIR/hfst-format --test-format `echo $i | sed "s/.//"`; then
	continue;
    fi

    if ! $TOOLDIR/hfst-shuffle ab$i bc$i > TMP; then
	rm TMP;
	exit 1;
    else
	if ! $TOOLDIR/hfst-compare TMP ab_shuffle_bc$i > /dev/null 2>&1; then
	    rm TMP;
	    exit 1;
	fi
    fi
    if ! $TOOLDIR/hfst-shuffle id$i id$i > TMP; then
	rm TMP;
	exit 1;
    else
	if ! $TOOLDIR/hfst-compare TMP id_shuffle_id$i > /dev/null 2>&1; then
	    rm TMP;
	    exit 1;
	fi
    fi
    if ! $TOOLDIR/hfst-shuffle aid$i idb$i > TMP; then
	rm TMP;
	exit 1;
    else
	if ! $TOOLDIR/hfst-compare TMP aid_shuffle_idb$i > /dev/null 2>&1; then
	    rm TMP;
	    exit 1;
	fi
    fi
    if $TOOLDIR/hfst-shuffle a2b$i ab$i > /dev/null 2>&1; then
	rm TMP;
	exit 1;
    fi
    rm TMP;
done
