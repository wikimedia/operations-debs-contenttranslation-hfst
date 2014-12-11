#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
    if test -f cat$i ; then
        if ! $TOOLDIR/hfst-fst2strings cat$i > test.strings ; then
            echo turning cat$i to strings failed
            exit 1
        fi
        if ! diff test.strings cat.strings > /dev/null 2>&1 ; then
            echo cat$i strings differ from expected
            exit 1
        fi
        rm test.strings;
    fi

    # extract 20 times 5 random strings and check that flags are obeyed
    if test -f unification_flags$i ; then
        for foo in 0 1
        do
            for bar in 0 1 2 3 4 5 6 7 8 9
            do
                if ! $TOOLDIR/hfst-fst2strings --random 5 -X obey-flags \
                    unification_flags$i > test.strings ; then
                    echo extracting random flags from unification_flags$i failed
                    exit 1
                fi
            # flags do not allow [A|B|C] with [a|b|c]
                if (egrep "A|B|C" test.strings | egrep "a|b|c" > tmp); then
                        echo "error in processing flags in "unification_flags$i": the following path is not valid:"
                        cat tmp
                        exit 1
                fi
            done
        done
    fi

    # extract 5 times 100 random strings and check that the flags are obeyed, i.e. no string is accepted
    if test -f unification_flags_fail$i ; then
        for foo in 0 1 2 3 4
        do
            if ! $TOOLDIR/hfst-fst2strings --random 100 -X obey-flags \
                unification_flags_fail$i > test.strings ; then
                echo extracting random flags from unification_flags_fail$i failed
                exit 1
            fi
            if ! (wc -l test.strings | grep '^ *0 ' > /dev/null); then
                echo "error in processing flags in "unification_flags$i": the following paths are not valid:"
                cat test.strings
                exit 1
            fi
        done
    fi
fi
done

for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
    # Test the empty transducer
    if test -f empty$i ; then
	if ! $TOOLDIR/hfst-fst2strings -r 20 empty$i > /dev/null ; then
	    echo "searching for random paths in an empty transducer failed"
	    exit 1
	fi
    fi

    # Test that epsilon paths are not accepted
    if test -f id_star_a_b_c$i ; then

        if ! ($TOOLDIR/hfst-fst2strings -r 10 id_star_a_b_c$i > tmp); then
            echo "extracting random strings from id_star_a_b_c"$i" failed"
            exit 1
        fi

        if (grep '^$' tmp > /dev/null); then
            echo "the empty string should not be recognized: "$i
            exit 1
        fi

    fi
fi
done
