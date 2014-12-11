#!/bin/sh
TOOLDIR=../../tools/src
for i in  .hfst .sfst .ofst .foma; do

if (([ ".hfst" = "$i" ]) || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then

    if test -f prunable_alphabet$i -a non_prunable_alphabet_1$i -a non_prunable_alphabet_2$i; then

	# Prunable alphabet
	for arg in --safe -S --force -f ""; do 
            if ! $TOOLDIR/hfst-minimize prunable_alphabet$i | $TOOLDIR/hfst-prune-alphabet $arg > test ; then
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
		if ! $TOOLDIR/hfst-minimize non_prunable_alphabet_$number$i | $TOOLDIR/hfst-prune-alphabet $arg > test ; then
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
		if ! $TOOLDIR/hfst-minimize non_prunable_alphabet_$number$i | $TOOLDIR/hfst-prune-alphabet $arg > test ; then
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
