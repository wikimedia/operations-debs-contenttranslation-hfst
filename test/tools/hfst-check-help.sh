#!/bin/sh
TOOLDIR=../../tools/src

HFST_TOOLS="hfst-affix-guessify hfst-calculate hfst-compare hfst-compose \
hfst-compose-intersect hfst-concatenate hfst-conjunct hfst-determinize \
hfst-disjunct hfst-edit-metadata hfst-format hfst-fst2fst \
hfst-fst2strings hfst-fst2txt hfst-grep hfst-guess hfst-guessify \
hfst-head hfst-info hfst-invert hfst-lexc-wrapper hfst-lexc \
hfst-lookup hfst-minimize hfst-multiply hfst-name \
hfst-optimized-lookup hfst-pair-test hfst-pmatch hfst-pmatch2fst \
hfst-project hfst-prune-alphabet hfst-push-weights hfst-regexp2fst \
hfst-remove-epsilons hfst-repeat hfst-reverse hfst-reweight \
hfst-shuffle hfst-split hfst-strings2fst hfst-substitute \
hfst-subtract hfst-summarize hfst-tail hfst-traverse \
hfst-txt2fst"

TWOLC_TOOLS="hfst-twolc/src/hfst-twolc-loc"
TAGGER_TOOLS="hfst-tagger/src/hfst-tag /hfst-tagger/src/hfst-train-tagger-loc"
PROC_TOOLS="hfst-proc/hfst-apertium-proc"
XFST_TOOLS="parsers/hfst-xfst"

# Extension for executables
EXT=
# Check if we are in MinGW environment
if (uname | egrep "MINGW|mingw" 2>1 > /dev/null); then
    # Executables have an exe extension
    EXT=".exe";
    # We use system call version of the shell script
    TWOLC_TOOLS=hfst-twolc/src/hfst-twolc-system
    # Tagger tool shell script not implemented for windows (MinGW)
    TAGGER_TOOLS=
fi

verbose="true"
arg=$1
if [ "$arg" != "--verbose" ]; then
    verbose="false"
fi

# $TOOLDIR/../../scripts/hfst-xfst is excluded from tests as long as 
# it is just a wrapper script around foma that doesn't recognize 
# the switch '--help'.
# The tools hfst-train-tagger and hfst-twolc are scripts that call 
# other tools in a pipeline. That is why we use a local version of them
# when testing. They also print their help messages to standard error
# to avoid giving the message to the next tool in the pipeline.
#
for f in $HFST_TOOLS $PROC_TOOLS $XFST_TOOLS; do
    prog=$TOOLDIR/$f
    if [ -e "$prog" ] ; then
        if ! "$prog" --help > help.out ; then
            rm help.out
            echo $prog has broken help
            exit 1
        fi
        if ! grep -q '^Usage: hfst-' help.out > /dev/null ; then
            rm help.out
            echo $prog has malformed help
            exit 1
        fi
        if [ "$verbose" != "false" ]; then
            echo "PASS: "$prog
        fi
    else
        if [ "$verbose" != "false" ]; then
            echo "Skipping "$prog"..."
        fi
    fi    
done

rm help.out

# We allow twolc and tagger tools to print their help messages to standard error..
for f in $TWOLC_TOOLS $TAGGER_TOOLS; do
    prog=$TOOLDIR/$f
    if [ -e "$prog" ] ; then
        if ! "$prog" --help > help1.out 2> help2.out ; then
            rm -f help1.out help2.out
            echo $prog has broken help
            exit 1
        fi
        if ! grep -q '^Usage: hfst-' help1.out > /dev/null ; then
            if ! grep -q '^Usage: hfst-' help2.out > /dev/null ; then
                rm -f help1.out help2.out
                echo $prog has malformed help
                exit 1
            fi
        fi
        if [ "$verbose" != "false" ]; then
            echo "PASS: "$prog
        fi
    else
        if [ "$verbose" != "fase" ]; then
            echo "Skipping "$prog"..."
        fi
    fi    
done

rm -f help.out1 help.out2
