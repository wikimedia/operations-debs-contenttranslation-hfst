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

TWOLC_TOOLS="$TOOLDIR/hfst-twolc/src/hfst-twolc"
TAGGER_TOOLS="hfst-tagger/src/hfst-tag"
PROC_TOOLS="hfst-proc/hfst-apertium-proc"
XFST_TOOLS="parsers/hfst-xfst"

# Extension for executables
EXT=
# Check if we are in MinGW environment
if (uname | egrep "MINGW|mingw" 2> /dev/null > /dev/null); then
    # Executables have an exe extension
    EXT=".exe";
    # TODO: implement these for windows
    TAGGER_TOOLS=
    TWOLC_TOOLS=
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
for prog in $HFST_TOOLS $PROC_TOOLS $XFST_TOOLS; do
    f=$TOOLDIR/$prog
    if [ -e "$f" ] ; then
        if [ "$verbose" != "false" ]; then
            echo $f
        fi
        if ! "$f" --version > version.out ; then
            rm version.out
            echo $f has broken version
            exit 1
        fi
        if ! grep -q 'hfst-[^ ]\+ [0-9.]\+' version.out > /dev/null \
            ; then
            rm version.out
            echo $f has malformed version
            exit 1
        fi        
    else
        if [ "$verbose" != "false" ]; then
            echo "Skipping "$f"..."
        fi
    fi    
done

rm version.out

# We allow twolc and tagger tools to print their help messages to standard error..
for prog in $TWOLC_TOOLS $TAGGER_TOOLS; do
    f=$TOOLDIR/$prog
    if [ -e "$f" ] ; then
        if [ "$verbose" != "false" ]; then
            echo $f
        fi
        if ! "$f" --version > version1.out 2> version2.out; then
            rm -f version1.out version2.out
            echo $f has broken version
            exit 1
        fi
        if ! grep -q 'hfst-[^ ]\+ [0-9.]\+' version1.out > /dev/null \
            ; then
            if ! grep -q 'hfst-[^ ]\+ [0-9.]\+' version2.out > /dev/null \
                ; then
                rm -f version1.out version2.out
                echo $f has malformed version
                exit 1
            fi        
        fi
    else
        if [ "$verbose" != "false" ]; then
            echo "Skipping "$f"..."
        fi
    fi    
done

rm -f version1.out version2.out
