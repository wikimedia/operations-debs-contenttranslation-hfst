#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-regexp2fst.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    TOOL=$TOOLDIR/hfst-regexp2fst
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

if [ "$srcdir" = "" ] ; then
    srcdir=. ;
fi

for i in sfst openfst-tropical foma; do
    
    if ! ($FORMAT_TOOL --list-formats | grep $i > /dev/null) ; then
	continue;
    fi

    # Newline-separated
    if ! $TOOL -f $i $srcdir/cats_and_dogs.xre > test.fst ; then
        exit 1
    fi
    if ! $TOOL -f $i $srcdir/at_file_quote.$i.xre > test.fst ; then
        exit 1
    fi    
    if ! $TOOL -f $i $srcdir/not-contains-a.xre > test.fst ; then
        exit 1
    fi
    if ! $TOOL -f $i $srcdir/parallel-left-arrow.xre > test.fst ; then
        exit 1
    fi

    # Space-separated
    if ! $TOOL -S -f $i $srcdir/cats_and_dogs_semicolon.xre > test ; then
        exit 1
    fi
    if ! $TOOL -S -f $i $srcdir/not-contains-a-comment-emptyline.xre > test.fst ; then
        exit 1
    fi
    if ! $TOOL -S -f $i $srcdir/parallel-left-arrow-multicom-emptyline.xre > test.fst ; then
        exit 1
    fi
    if ! $TOOL -S -f $i $srcdir/left-arrow-with-semicolon-comment.xre > test.fst ; then
        exit 1
    fi
    if ! $TOOL -S -f $i $srcdir/left-arrow-with-semicolon-many-comments.xre > test.fst ; then
        exit 1
    fi

    # Empty input and input containing only comments
    if (echo "" | $TOOL -f $i > test.fst 2> /dev/null) ; then
        exit 1
    fi
    if (echo "" | $TOOL -S -f $i > test.fst 2> /dev/null) ; then
        exit 1
    fi
    if (echo ";" | $TOOL -S -f $i > test.fst 2> /dev/null) ; then
        exit 1
    fi
    if (echo "! A comment" | $TOOL -S -f $i > test.fst 2> /dev/null) ; then
        exit 1
    fi
    if (echo "  ! A comment" | $TOOL -S -f $i > test.fst 2> /dev/null) ; then
        exit 1
    fi
    if (echo "! A comment" | $TOOL -f $i > test.fst 2> /dev/null) ; then
        exit 1
    fi
    if (echo "  ! A comment" | $TOOL -f $i > test.fst 2> /dev/null) ; then
        exit 1
    fi

done

rm -f test.fst
exit 0
