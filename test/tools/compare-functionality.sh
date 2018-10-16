#!/bin/sh
TOOLDIR=../../tools/src
COMPARE_TOOL=
FORMAT_TOOL=
REGEXP_TOOL=$TOOLDIR/hfst-regexp2fst
FSTTOOL=$TOOLDIR/hfst-fst2txt

if [ "$1" = '--python' ]; then
    COMPARE_TOOL="python3 ./hfst-compare.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $COMPARE_TOOL $FORMAT_TOOL $REGEXP_TOOL $FSTTOOL;
    do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

comparables="cat dog tac cat2dog dog2cat cat_or_dog catdog"
for f in $comparables; do
    if ! $COMPARE_TOOL -s $f.hfst $f.hfst  ; then
        echo "compare -s mismatches" $f.hfst $f.hfst
        exit 1
    fi
    for g in $comparables ; do
        if test $f != $g ; then
            if $COMPARE_TOOL -s $f.hfst $g.hfst  ; then
                echo "compare -s matches" $f.hfst $g.hfst
                exit 1
            fi
        fi
    done
    # [a|?] and [?] are equal if harmonized
    if ! $COMPARE_TOOL -s a_or_id.hfst id.hfst ; then
	echo "compare -s mismatches" "a_or_id.hfst" "id.hfst"
	exit 1
    fi
    # [a|?] and [?] are not equal if not harmonized
    if $COMPARE_TOOL -H -s a_or_id.hfst id.hfst ; then
	echo "compare -H -s matches" "a_or_id.hfst" "id.hfst"
	exit 1
    fi
done

for format in sfst openfst-tropical foma
do
    if ($FORMAT_TOOL --list-formats | grep $format > /dev/null) ; then
    
        # [?] with empty sigma and [?] with sigma {a} are not equal
        echo "[?]" | $REGEXP_TOOL -f $format > tmp1;
        echo "[?-a]" | $REGEXP_TOOL -f $format > tmp2;
        $FSTTOOL tmp1 > tmp1.txt;
        $FSTTOOL tmp2 > tmp2.txt;
        if ! (diff tmp1.txt tmp2.txt); then
	    echo "not equal #1"
	    exit 1;
        fi
        if $COMPARE_TOOL -s tmp1 tmp2; then
	    echo "not equal #2"
	    exit 1;
        fi
    fi
done

rm -f tmp1 tmp2 tmp1.txt tmp2.txt
