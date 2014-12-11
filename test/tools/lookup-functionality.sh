#!/bin/sh
TOOLDIR=../../tools/src
if ! $TOOLDIR/hfst-lookup -s cat.hfst < $srcdir/cat.strings > test.lookups ; then
    exit 1
fi

$TOOLDIR/hfst-format -l > TMP;

# test what strings the transducer [a:b (ID:ID)*] recognizes
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
    if test -f abid$i ; then

	if ! echo "aa" | $TOOLDIR/hfst-lookup -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if ! grep -q "inf" test.lookups; then
	    echo "FAIL: string 'aa' should not be recognized"
	    exit 1
	fi
	
	if ! echo "ab" | $TOOLDIR/hfst-lookup -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if ! grep -q "inf" test.lookups; then
	    echo "FAIL: string 'ab' should not be recognized"
	    exit 1
	fi
	
	if ! echo "ac" | $TOOLDIR/hfst-lookup -s abid$i \
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
	
	if ! echo "ad" | $TOOLDIR/hfst-lookup infinitely_ambiguous$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if ! grep -q "infinite" warnings; then
	    echo "FAIL: infinitely ambiguous string 'ad' should give a warning"
	    exit 1;
	fi

	if ! echo "b" | $TOOLDIR/hfst-lookup infinitely_ambiguous$i \
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

	if ! echo "a" | $TOOLDIR/hfst-lookup infinitely_ambiguous_with_flags$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if ! grep -q "infinite" warnings; then
	    echo "FAIL: infinitely ambiguous string 'a' should give a warning"
	    exit 1;
	fi

	if ! echo "b" | $TOOLDIR/hfst-lookup infinitely_ambiguous_with_flags$i \
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
