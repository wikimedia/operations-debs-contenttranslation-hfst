#!/bin/sh
TOOLDIR=../../tools/src
ext=""
lang=""
if [ "$1" = "--python" ]; then
    TOOLDIR="."
    ext=".py"
    lang="python3"
fi
for f in "" .sfst .foma .openfst; do
    for g in "" .sfst .foma .openfst; do
        if test cat$f != cat$g ; then
            if test -f cat$f -a -f cat$g ; then
                for p in compare compose concatenate conjunct disjunct subtract ; do
                    if $lang $TOOLDIR/hfst-$p$ext cat$f cat$g 2> /dev/null > /dev/null; then
                        echo $p does not fail cat$f cat$g
                        exit 0
                    fi
                done
            fi
        fi
    done
done
exit 2
