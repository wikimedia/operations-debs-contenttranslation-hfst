#!/bin/sh
TOOLDIR=../../tools/src
FORMAT_TOOL=$TOOLDIR/hfst-format
FLOOKUP_TOOL=$TOOLDIR/hfst-flookup

if [ "$1" = "--python" ]; then
    exit 77 # not yet implemented
    FORMAT_TOOL="python3 ./hfst-format.py"
    FLOOKUP_TOOL="python3 ./hfst-flookup.py"
fi

if ! $FLOOKUP_TOOL -R -s cat.hfst < $srcdir/cat.strings > test.lookups ; then
    exit 1
fi

$FORMAT_TOOL -l > TMP;

# test what strings the transducer [a:b (ID:ID)*] recognizes
for i in "" .sfst .ofst .foma; do
if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
    if test -f abid$i ; then

	if ! echo "aa" | $FLOOKUP_TOOL -R -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if ! grep -q "inf" test.lookups; then
	    echo "FAIL: string 'aa' should not be recognized"
	    exit 1
	fi
	
	if ! echo "ab" | $FLOOKUP_TOOL -R -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if ! grep -q "inf" test.lookups; then
	    echo "FAIL: string 'ab' should not be recognized"
	    exit 1
	fi
	
	if ! echo "ac" | $FLOOKUP_TOOL -R -s abid$i \
	    > test.lookups; 
	then
	    exit 1
	fi
	if grep -q "inf" test.lookups; then
	    echo "FAIL: string 'ac' should be recognized"
	    exit 1
	fi

        if ! echo "aa" | $FLOOKUP_TOOL -s abid$i \
            > test.lookups;
        then
            exit 1
        fi
        if ! grep -q "inf" test.lookups; then
	    echo "FAIL: string 'aa' should not be recognized"
	    exit 1
        fi
        
        if ! echo "bc" | $FLOOKUP_TOOL -s abid$i \
	    > test.lookups; 
        then
	    exit 1
        fi
        if grep -q "inf" test.lookups; then
	    echo "FAIL: string 'bc' should be recognized"
	    exit 1
        fi
    fi

    if test -f infinitely_ambiguous$i ; then
	
	if ! echo "ad" | $FLOOKUP_TOOL -R infinitely_ambiguous$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if ! grep -q "infinite" warnings; then
	    echo "FAIL: infinitely ambiguous string 'ad' should give a warning"
	    exit 1;
	fi

	if ! echo "b" | $FLOOKUP_TOOL -R infinitely_ambiguous$i \
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

	if ! echo "a" | $FLOOKUP_TOOL -R infinitely_ambiguous_with_flags$i \
	    2> warnings > test.lookups;
	then
	    exit 1
	fi
	
	if ! grep -q "infinite" warnings; then
	    echo "FAIL: infinitely ambiguous string 'a' should give a warning"
	    exit 1;
	fi

	if ! echo "b" | $FLOOKUP_TOOL -R infinitely_ambiguous_with_flags$i \
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
