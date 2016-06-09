#!/bin/sh
TOOLDIR=../../tools/src

TOOLS="hfst-disjunct hfst-concatenate hfst-conjunct hfst-subtract hfst-compose hfst-shuffle"
# TODO: hfst-compose-intersect, hfst-substitute, hfst-xfst?
NORMOPT="--silent"
STRICTOPT="--silent --do-not-convert"

for type1 in sfst ofst foma;
do
    for type2 in sfst ofst foma;
    do
        for tool in $TOOLS;
        do
            # only test inputs that have mismatching types
            if (test "$type1" != "$type2"); then
                if (ls $TOOLDIR/$tool > /dev/null 2> /dev/null); then
                    # echo "$tool"
                    if ($TOOLDIR/hfst-format --list-formats | grep $type1 > /dev/null); then
                        if ($TOOLDIR/hfst-format --list-formats | grep $type2 > /dev/null); then
                            # (1) two transducers
                            if test -f cat.$type1 -a -f dog.$type2; then
                                # echo "  $type1, $type2"
                                # echo "    normal"
                                if ! $TOOLDIR/$tool $NORMOPT cat.$type1 dog.$type2 > test 2> /dev/null ; then
                                    exit 1
                                fi
                                # echo "    strict"
                                if $TOOLDIR/$tool $STRICTOPT cat.$type1 dog.$type2 > test 2> /dev/null ; then
                                    exit 1
                                fi
                            fi
                            if test -f cat.$type2 -a -f dog.$type1; then
                                # echo "  $type2, $type1"
                                # echo "    normal"
                                if ! $TOOLDIR/$tool $NORMOPT cat.$type2 dog.$type1 > test 2> /dev/null ; then
                                    exit 1
                                fi
                                # echo "    strict"
                                if $TOOLDIR/$tool $STRICTOPT cat.$type2 dog.$type1 > test 2> /dev/null ; then
                                    exit 1
                                fi
                            fi
                            # (2) archives of transducers with equal length
                            if test -f cat.$type1 -a -f cat.$type2 -a -f dog.$type1 -a -f dog.$type2; then
                                cat cat.$type1 dog.$type1 > test1
                                cat cat.$type2 dog.$type2 > test2
                                # echo "  archive $type1, archive $type2"
                                # echo "    normal"
                                if ! $TOOLDIR/$tool $NORMOPT test1 test2 > test 2> /dev/null ; then
                                    exit 1
                                fi
                                # echo "    strict"
                                if $TOOLDIR/$tool $STRICTOPT test1 test2 > test 2> /dev/null ; then
                                    exit 1
                                fi
                            fi
                            # (3) archives of transducers with different lengths
                            if test -f cat.$type1 -a -f cat.$type2 -a -f dog.$type1 -a -f dog.$type2; then
                                cat cat.$type1 dog.$type1 cat.$type1 dog.$type1 > test1
                                cat cat.$type2 > test2
                                # echo "  archive $type1, $type2"
                                # echo "    normal"
                                if ! $TOOLDIR/$tool $NORMOPT test1 test2 > test 2> /dev/null ; then
                                    exit 1
                                fi
                                # echo "    strict"
                                if $TOOLDIR/$tool $STRICTOPT test1 test2 > test 2> /dev/null ; then
                                    exit 1
                                fi
                            fi
                        fi
                    fi
                fi
            fi
        done
    done
done

rm test

