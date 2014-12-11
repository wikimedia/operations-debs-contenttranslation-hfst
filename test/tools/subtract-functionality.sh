#!/bin/sh
TOOLDIR=../../tools/src
for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
        if test -f cat_or_dog$i -a -f dog$i -a -f cat$i ; then
            if ! $TOOLDIR/hfst-subtract cat_or_dog$i dog$i > test ; then
                exit 1
            fi
            if ! $TOOLDIR/hfst-compare -s test cat$i  ; then
                exit 1
            fi
            rm test;
#    else
#	exit 1 ;
        fi
# test the empty transducer
        if test -f empty$i ; then
	    if ! $TOOLDIR/hfst-subtract empty$i empty$i > test ; then
	        exit 1
	    fi
	    if ! $TOOLDIR/hfst-compare -s test empty$i ; then
	        exit 1
	    fi
#    else
#        echo "FAIL: Missing files in empty transducer tests"
#	exit 1 ;
        fi
# test that the complement [ [ID:ID | UNK:UNK]* - transducer ] works
        if test -f unk_or_id_star$i -a a2b$i -a a2b_complement$i -a a2b_input_projection_complement$i ; then
	    if ! $TOOLDIR/hfst-subtract -1 unk_or_id_star$i -2 a2b$i > test ; then
	        exit 1
	    fi
	    if ! $TOOLDIR/hfst-compare -s test a2b_complement$i ; then
	        echo "FAIL: Complement test" $i
	        exit 1
	    fi
	# the input projection
	    if ! $TOOLDIR/hfst-project -p input a2b$i > a2b_input ; then
	        exit 1
	    fi
	    if ! $TOOLDIR/hfst-subtract -1 unk_or_id_star$i -2 a2b_input > test ; then
	        exit 1
	    fi
	    if ! $TOOLDIR/hfst-compare -s test a2b_input_projection_complement$i ; then
	        echo "FAIL: Complement test, input projection" $i ;
	        exit 1
	    fi
	    rm a2b_input
	    rm test;
#    else
#	echo "FAIL: Missing files in complement tests"
#	exit 1 ;
        fi
    fi
done

# test weight handling for tropical transducers
if test -f cat2dog_0.3.ofst -a -f cat2dog_0.5.ofst ; then
    if ! $TOOLDIR/hfst-subtract -1 cat2dog_0.3.ofst -2 cat2dog_0.5.ofst > test ; then
	exit 1;
    fi
    if ! $TOOLDIR/hfst-compare -s empty.ofst test ; then
	exit 1;
    fi
    if ! $TOOLDIR/hfst-subtract -2 cat2dog_0.3.ofst -1 cat2dog_0.5.ofst > test ; then
	exit 1;
    fi
    if ! $TOOLDIR/hfst-compare -s empty.ofst test ; then
	exit 1;
    fi
    rm test;
#else
#    echo "FAIL: Missing files in weight tests"
#    exit 1 ;
fi
