#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
    if test -f cat$i -a -f dog$i ; then
        if ! $TOOLDIR/hfst-substitute -s cat$i -F $srcdir/cat2dog.substitute > test ; then
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -s test dog$i  ; then
            exit 1
        fi
        rm test
        $TOOLDIR/hfst-substitute -s cat$i -f c -t d |\
            $TOOLDIR/hfst-substitute -s -f a -t o |\
            $TOOLDIR/hfst-substitute -s -f t -t g > test
        if test $? -ne 0 ; then 
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -s test dog$i ; then
            exit 1
        fi
    fi
    if test -f another_epsilon$i -a -f epsilon$i ; then
        if ! $TOOLDIR/hfst-substitute -s -i another_epsilon$i -f '@@ANOTHER_EPSILON@@' -t '@0@' > test ; then
            echo "fail: could not substitute"
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -s test epsilon$i  ; then
            echo "fail: test and epsilon"$i" differ"
            exit 1
        fi
        if $TOOLDIR/hfst-summarize --verbose test 2> /dev/null | grep "sigma" | grep '@@ANOTHER_EPSILON@@' > /dev/null ; then
            echo "fail: @@ANOTHER_EPSILON@@ is still in the alphabet after substitution"
            exit 1
        fi
        rm test
    fi
fi
done
