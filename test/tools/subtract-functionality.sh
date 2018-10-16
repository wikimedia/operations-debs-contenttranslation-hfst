#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=
COMPARE_TOOL=
PROJECT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-subtract.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    PROJECT_TOOL="python3 ./hfst-project.py"
else
    TOOL=$TOOLDIR/hfst-subtract
    FORMAT_TOOL=$TOOLDIR/hfst-format
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    PROJECT_TOOL=$TOOLDIR/hfst-project
    for tool in $TOOL $FORMAT_TOOL $COMPARE_TOOL $PROJECT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f cat_or_dog$i -a -f dog$i -a -f cat$i ; then
            if ! $TOOL cat_or_dog$i dog$i > test ; then
                exit 1
            fi
            if ! $COMPARE_TOOL -s test cat$i  ; then
                exit 1
            fi
            rm test;
#    else
#	exit 1 ;
        fi
# test the empty transducer
        if test -f empty$i ; then
	    if ! $TOOL empty$i empty$i > test ; then
	        exit 1
	    fi
	    if ! $COMPARE_TOOL -s test empty$i ; then
	        exit 1
	    fi
#    else
#        echo "FAIL: Missing files in empty transducer tests"
#	exit 1 ;
        fi
# test that the complement [ [ID:ID | UNK:UNK]* - transducer ] works
        if test -f unk_or_id_star$i -a a2b$i -a a2b_complement$i -a a2b_input_projection_complement$i ; then
	    if ! $TOOL -1 unk_or_id_star$i -2 a2b$i > test ; then
	        exit 1
	    fi
	    if ! $COMPARE_TOOL -s test a2b_complement$i ; then
	        echo "FAIL: Complement test" $i
	        exit 1
	    fi
	# the input projection
	    if ! $PROJECT_TOOL -p input a2b$i > a2b_input ; then
	        exit 1
	    fi
	    if ! $TOOL -1 unk_or_id_star$i -2 a2b_input > test ; then
	        exit 1
	    fi
	    if ! $COMPARE_TOOL -s test a2b_input_projection_complement$i ; then
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
    if ! $TOOL -1 cat2dog_0.3.ofst -2 cat2dog_0.5.ofst > test ; then
	exit 1;
    fi
    if ! $COMPARE_TOOL -s empty.ofst test ; then
	exit 1;
    fi
    if ! $TOOL -2 cat2dog_0.3.ofst -1 cat2dog_0.5.ofst > test ; then
	exit 1;
    fi
    if ! $COMPARE_TOOL -s empty.ofst test ; then
	exit 1;
    fi
    rm test;
#else
#    echo "FAIL: Missing files in weight tests"
#    exit 1 ;
fi
