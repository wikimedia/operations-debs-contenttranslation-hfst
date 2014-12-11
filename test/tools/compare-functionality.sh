#!/bin/sh
TOOLDIR=../../tools/src

comparables="cat dog tac cat2dog dog2cat cat_or_dog catdog"
for f in $comparables; do
    if ! $TOOLDIR/hfst-compare -s $f.hfst $f.hfst  ; then
        echo "compare -s mismatches" $f.hfst $f.hfst
        exit 1
    fi
    for g in $comparables ; do
        if test $f != $g ; then
            if $TOOLDIR/hfst-compare -s $f.hfst $g.hfst  ; then
                echo "compare -s matches" $f.hfst $g.hfst
                exit 1
            fi
        fi
    done
    # [a|?] and [?] are equal if harmonized
    if ! $TOOLDIR/hfst-compare -s a_or_id.hfst id.hfst ; then
	echo "compare -s mismatches" "a_or_id.hfst" "id.hfst"
	exit 1
    fi
    # [a|?] and [?] are not equal if not harmonized
    if $TOOLDIR/hfst-compare -H -s a_or_id.hfst id.hfst ; then
	echo "compare -H -s matches" "a_or_id.hfst" "id.hfst"
	exit 1
    fi
done

for format in sfst openfst-tropical foma
do
    if ($TOOLDIR/hfst-format --list-formats | grep $format > /dev/null) ; then
    
        # [?] with empty sigma and [?] with sigma {a} are not equal
        echo "[?]" | $TOOLDIR/hfst-regexp2fst -f $format > tmp1;
        echo "[?-a]" | $TOOLDIR/hfst-regexp2fst -f $format > tmp2;
        $TOOLDIR/hfst-fst2txt tmp1 > tmp1.txt;
        $TOOLDIR/hfst-fst2txt tmp2 > tmp2.txt;
        if ! (diff tmp1.txt tmp2.txt); then
	    echo "not equal #1"
	    exit 1;
        fi
        if $TOOLDIR/hfst-compare -s tmp1 tmp2; then
	    echo "not equal #2"
	    exit 1;
        fi
    fi
done
