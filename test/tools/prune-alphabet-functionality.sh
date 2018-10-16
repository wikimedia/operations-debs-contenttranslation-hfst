#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-prune-alphabet.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    TOOL=$TOOLDIR/hfst-prune-alphabet
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in  .hfst .sfst .ofst .foma; do

if (([ ".hfst" = "$i" ]) || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then

    if test -f prunable_alphabet$i -a non_prunable_alphabet_1$i -a non_prunable_alphabet_2$i; then

	# Prunable alphabet
	for arg in --safe -S --force -f ""; do 
            if ! $TOOLDIR/hfst-minimize prunable_alphabet$i | $TOOL $arg > test ; then
		exit 1
	    fi
	    if ! $TOOLDIR/hfst-summarize --verbose test 2> /dev/null | grep --after-context 1 "sigma symbols missing from transducer" | tail -1 > tmp; then
		exit 1
	    fi
	    if grep "e, f" tmp > /dev/null; then
		exit 1
	    fi
	done

	# Non-prunable alphabets #1 and #2
	for number in 1 2; do
	    # safe pruning
	    for arg in --safe -S ""; do
		if ! $TOOLDIR/hfst-minimize non_prunable_alphabet_$number$i | $TOOL $arg > test ; then
		    exit 1
		fi
		if ! $TOOLDIR/hfst-summarize --verbose test 2> /dev/null | grep --after-context 1 "sigma symbols missing from transducer" | tail -1 > tmp; then
		    exit 1
		fi
		if ! grep "e, f" tmp > /dev/null; then
		    exit 1
		fi
	    done
	    # forced pruning
	    for arg in --force -f; do
		if ! $TOOLDIR/hfst-minimize non_prunable_alphabet_$number$i | $TOOL $arg > test ; then
		    exit 1
		fi
		if ! $TOOLDIR/hfst-summarize --verbose test 2> /dev/null | grep --after-context 1 "sigma symbols missing from transducer" | tail -1 > tmp; then
		    exit 1
		fi
		if grep "e, f" tmp > /dev/null; then
		    exit 1
		fi
	    done
	done

    fi
fi

done

rm test tmp
