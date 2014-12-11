#!/bin/sh

TOOLDIR=../../tools/src

HFST_TOOLS="hfst-affix-guessify hfst-calculate hfst-compare hfst-compose \
hfst-compose-intersect hfst-concatenate hfst-conjunct hfst-determinize \
hfst-disjunct hfst-edit-metadata hfst-format hfst-fst2fst \
hfst-fst2strings hfst-fst2txt hfst-grep hfst-guess hfst-guessify \
hfst-head hfst-info hfst-invert hfst-lexc \
hfst-lookup hfst-minimize hfst-multiply hfst-name \
hfst-optimized-lookup hfst-pair-test hfst-pmatch hfst-pmatch2fst \
hfst-project hfst-prune-alphabet hfst-push-weights hfst-regexp2fst \
hfst-remove-epsilons hfst-repeat hfst-reverse hfst-reweight \
hfst-shuffle hfst-split hfst-strings2fst hfst-substitute \
hfst-subtract hfst-summarize hfst-tail hfst-traverse \
hfst-txt2fst"

for prog in $HFST_TOOLS ; do
    f=$TOOLDIR/$prog
    if [ -x "$f" -a ! -d "$f" ] ; then
        $f < $srcdir/empty-file > /dev/null 2>&1
        rv=$?
        if [ $rv -eq 139 ] ; then
            echo $f received SEGV on empty input file
            exit 1
        elif [ $rv -gt 1 ] ; then
            echo $f did not die with SUCCESS nor FAILURE on empty input
            exit 1
        fi
    fi
done

