#!/bin/sh
TOOLDIR=../../tools/src
if [ -x $TOOLDIR/hfst-compare ] ; then
    # well, not all permutations, but reasonable
    if $TOOLDIR/hfst-compare -s -1 cat.hfst -2 dog.hfst  ; then
       exit 1
    fi
    if $TOOLDIR/hfst-compare -s -1 cat.hfst dog.hfst  ; then
       exit 1
    fi
    if $TOOLDIR/hfst-compare -s -2 dog.hfst cat.hfst  ; then
       exit 1
    fi
    if $TOOLDIR/hfst-compare -s dog.hfst -1 cat.hfst  ; then
       exit 1
    fi
    if $TOOLDIR/hfst-compare -s cat.hfst -2 dog.hfst  ; then
       exit 1
    fi
    if $TOOLDIR/hfst-compare -s cat.hfst < dog.hfst  ; then
        exit 1
    fi
    if $TOOLDIR/hfst-compare -s -1 cat.hfst < dog.hfst  ; then
        exit 1
    fi
    if $TOOLDIR/hfst-compare -s -2 dog.hfst < cat.hfst  ; then
        exit 1
    fi
fi
rm -f test_*
for operator in conjunct disjunct compose subtract compose compose-intersect ; do
    f=$TOOLDIR/"hfst-"$operator" -q"
    if [ -x "$f" ] ; then
        # well, not all permutations, but reasonable
        $f -1 cat.hfst -2 dog.hfst > test_named1named2stdout || exit 1
        $f cat.hfst dog.hfst > test_file1file2stdout || exit 1
        $f -1 cat.hfst dog.hfst > test_named1file2stdout || exit 1
        $f -2 dog.hfst cat.hfst > test_named2file1stdout || exit 1
        $f cat.hfst -2 dog.hfst > test_file1named2stdout || exit 1
        $f dog.hfst -1 cat.hfst > test_file2named1stdout || exit 1
        $f dog.hfst < cat.hfst > test_file1stdin2stdout || exit 1
        $f -1 cat.hfst < dog.hfst > test_named1stdin2stdout || exit 1
        $f -2 dog.hfst < cat.hfst > test_named2stdin1stdout || exit 1
        $f -1 cat.hfst -2 dog.hfst -o test_named1named2namedout || exit 1
        $f cat.hfst dog.hfst -o test_file1file2namedout || exit 1
        $f -1 cat.hfst dog.hfst -o test_named1file2namedout || exit 1
        $f -2 dog.hfst cat.hfst -o test_named2file1namedout || exit 1
        $f cat.hfst -2 dog.hfst -o test_file1named2namedout || exit 1
        $f dog.hfst -1 cat.hfst -o test_file2named1namedout || exit 1
        $f dog.hfst -o test_file1stdin2stdout  < cat.hfst || exit 1
        $f -1 cat.hfst -o test_named1stdin2namedout < dog.hfst  || exit 1
        $f -2 dog.hfst -o test_named2stdin1namedout < cat.hfst  || exit 1
        for g in test_* ; do
            for h in test_* ; do
                if ! $TOOLDIR/hfst-compare -s $g $h  ; then
                    echo "$f builds $g and $h differently from same sources"
                    exit 1
                fi
            done
        done
        rm -f test_*
    fi
done

for operator in determinize invert minimize remove-epsilons reverse ; do
    f=$TOOLDIR/hfst-$operator
    if [ -x $f ] ; then
        $f -i cat.hfst > test_namedinstdout || exit 1
        $f cat.hfst > test_fileinstdout || exit 1
        $f -i cat.hfst -o test_namedinnamedout || exit 1
        $f cat.hfst -o test_fileinnamedout || exit 1
        for g in test_* ; do
            for h in test_* ; do
                if ! $TOOLDIR/hfst-compare -s $g $h  ; then
                    echo "$f builds $g and $h differently from same sources"
                    exit 1
                fi
            done
        done
        rm -f test_*
    fi
done

for operator in fst2strings fst2txt ; do
    f=$TOOLDIR/hfst-$operator
    if [ -x $f ] ; then
        $f -i cat.hfst > test_namedinstdout.txt || exit 1
        $f cat.hfst > test_fileinstdout.txt || exit 1
        $f -i cat.hfst -o test_namedinnamedout.txt || exit 1
        $f cat.hfst -o test_fileinnamedout.txt || exit 1
        for g in test_*.txt ; do
            for h in test_*.txt ; do
                if ! cmp $g $h ; then
                    echo "$f builds $g and $h differently from same sources"
                    exit 1
                fi
            done
        done
        rm -f test_*.txt
    fi
done


