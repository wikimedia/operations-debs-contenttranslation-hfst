#!/bin/sh
TOOLDIR=../../tools/src
TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    TOOL="python3 ./hfst-lookup.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    TOOL=$TOOLDIR/hfst-lookup
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $TOOL $FORMAT_TOOL; do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

if ! $TOOL -s cat.hfst < $srcdir/cat.strings > test.lookups ; then
    exit 1
fi

$FORMAT_TOOL -l > TMP;

# test what strings the transducer [a:b (ID:ID)*] recognizes
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
    if test -f abid$i ; then

	if ! echo "aa" | $TOOL -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if ! grep -q "inf" test.lookups; then
	    echo "FAIL: string 'aa' should not be recognized"
	    exit 1
	fi
	
	if ! echo "ab" | $TOOL -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if ! grep -q "inf" test.lookups; then
	    echo "FAIL: string 'ab' should not be recognized"
	    exit 1
	fi
	
	if ! echo "ac" | $TOOL -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if grep -q "inf" test.lookups; then
	    echo "FAIL: string 'ac' should be recognized"
	    exit 1
	fi

    fi

    if test -f infinitely_ambiguous$i ; then
	
	if ! echo "ad" | $TOOL infinitely_ambiguous$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if ! grep -q "infinite" warnings; then
	    echo "FAIL: infinitely ambiguous string 'ad' should give a warning"
	    exit 1;
	fi

	if ! echo "b" | $TOOL infinitely_ambiguous$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if grep -q "infinite" warnings; then
	    echo "FAIL: unambiguous string 'b' should not give a warning"
	    exit 1;
	fi

    fi

    if test -f infinitely_ambiguous_with_flags$i ; then

	if ! echo "a" | $TOOL infinitely_ambiguous_with_flags$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if ! grep -q "infinite" warnings; then
	    echo "FAIL: infinitely ambiguous string 'a' should give a warning"
	    exit 1;
	fi

	if ! echo "b" | $TOOL infinitely_ambiguous_with_flags$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if grep -q "infinite" warnings; then
	    echo "FAIL: unambiguous string 'b' should not give a warning"
	    exit 1;
	fi

    fi
fi
done

rm TMP
rm test.lookups
rm warnings
