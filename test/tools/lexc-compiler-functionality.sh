#!/bin/sh

TOOLDIR=../../tools/src
LEXCTESTS="basic.cat-dog-bird.lexc basic.colons.lexc basic.comments.lexc 
          basic.empty-sides.lexc basic.escapes.lexc 
          basic.infostrings.lexc basic.initial-lexicon-empty.lexc 
          basic.multichar-symbols.lexc
          basic.no-Root.lexc
          basic.multi-entry-lines.lexc basic.no-newline-at-end.lexc 
          basic.punctuation.lexc basic.root-loop.lexc 
          basic.spurious-lexicon.lexc basic.string-pairs.lexc 
          basic.two-lexicons.lexc basic.UTF-8.lexc basic.zeros-epsilons.lexc
          basic.lowercase-lexicon-end.lexc
          basic.multichar-escaped-zero.lexc
          basic.almost-reserved-words.lexc
          basic.regexps.lexc
          hfst.weights.lexc
          xre.automatic-multichar-symbols.lexc xre.basic.lexc 
          xre.definitions.lexc xre.months.lexc xre.nested-definitions.lexc 
          xre.numeric-star.lexc xre.sharp.lexc xre.quotations.lexc
          xre.star-plus-optional.lexc
          xre.any-variations.lexc
          no-newline-before-sublexicon.lexc"

          # basic.end.lexc -hfst doesn't parse till end
          # xre.any-variations.lexc -foma ?:? problem
          # basic.multichar-symbol-with-0.lexc  - hfst works fine, foma wrong
          # basic.multichar-flag-with-zero.lexc - foma wrong

          
                    
          
LEXCXFAIL="xfail.bogus.lexc xfail.ISO-8859-1.lexc xfail.lexicon-semicolon.lexc"

LEXCWARN="warn.sublexicon-mentioned-but-not-defined.lexc"

if test "$srcdir" = ""; then
    srcdir="./"
fi


if ! test -x $TOOLDIR/hfst-lexc ; then
    echo "missing hfst-lexc, assuming configured off, skipping"
    exit 73
fi

for i in .sfst .ofst .foma ; do
    FFLAG=
    FNAME=
    case $i in
        .sfst)
            FNAME="sfst";
            FFLAG="-f sfst";;
        .ofst)
            FNAME="openfst-tropical";
            FFLAG="-f openfst-tropical";;
        .foma)
            FNAME="foma";
            FFLAG="-f foma";;
        *)
            FNAME=;
            FFLAG=;;
    esac
    
    #echo "---- $FNAME --------"

    if ! ($TOOLDIR/hfst-format --test-format $FNAME ) ; then
        continue;
    fi

    if test -f cat$i ; then
        if ! $TOOLDIR/hfst-lexc $FFLAG $srcdir/cat.lexc -o test 2> /dev/null; then
            echo lexc $FFLAG cat.lexc failed with $?
            exit 1
        fi
        if ! $TOOLDIR/hfst-compare -e -s cat$i test ; then
        echo "results differ: " "cat"$i" test"
            exit 1
        fi
        rm test
    fi
    for f in $LEXCTESTS $LEXCWARN ; do
        
        #check non-flag result
        if ! $TOOLDIR/hfst-lexc $FFLAG $srcdir/$f -o test 2> /dev/null; then
            echo lexc $FFLAG $f failed with $?
            exit 1
        fi
        
        RESULT="$f.result"

     # create foma result     
     #   RESULT_GZ="$RESULT.gz"
     #       echo "read lexc $srcdir/$f \n
     #       save stack test.foma.gz \n
     #       quit \n" > tmp-foma-script
     #       foma -q < tmp-foma-script
     #   gunzip test.foma.gz
     #   mv test.foma $RESULT
     #   rm tmp-foma-script
     
        $TOOLDIR/hfst-fst2fst $FFLAG $RESULT -o $RESULT.tmp
           
         #echo "comparing file: $f"
         if ! $TOOLDIR/hfst-compare -e -s $RESULT.tmp test ; then
             echo "results differ: $f"
             exit 1
         fi
        rm $RESULT.tmp
        rm test
        
        
        # check flag results
        RESULT="$f.flag.result"
 

        if ! $TOOLDIR/hfst-lexc -F $FFLAG $srcdir/$f -o test 2> /dev/null; then
            echo lexc2fst -F $FFLAG $f failed with $?
            exit 1
        fi
        
        $TOOLDIR/hfst-fst2fst $FFLAG $RESULT -o $RESULT.tmp
           
         #echo "comparing flag file: $f"
         if ! $TOOLDIR/hfst-compare -e -s $RESULT.tmp test ; then
             echo "results differ: $f"
             exit 1
         fi
        rm $RESULT.tmp
        rm test
        
        
        
    done

    for f in $LEXCWARN ; do
        if $TOOLDIR/hfst-lexc --Werror $FFLAG $srcdir/$f -o test 2> /dev/null; then
            echo lexc $FFLAG $f passed although --Werror was used
            exit 1
        fi        
    done

    if ! $TOOLDIR/hfst-lexc $FFLAG $srcdir/basic.multi-file-1.lexc \
        $srcdir/basic.multi-file-2.lexc \
        $srcdir/basic.multi-file-3.lexc -o test 2> /dev/null; then
        echo lexc2fst $FFLAG basic.multi-file-{1,2,3}.lexc failed with $?
        exit 1
    fi
    if ! $TOOLDIR/hfst-compare -e -s walk_or_dog$i test ; then
        exit 1
    fi
done

exit 77
