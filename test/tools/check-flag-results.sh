#!/bin/sh

# skip tests
# exit 77

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
          
          hfst.weights.lexc      
          xre.automatic-multichar-symbols.lexc xre.basic.lexc 
          xre.definitions.lexc xre.months.lexc xre.nested-definitions.lexc 
          xre.numeric-star.lexc xre.sharp.lexc xre.quotations.lexc
          xre.star-plus-optional.lexc
          xre.any-variations.lexc"
          
          # basic.lowercase-lexicon-end.lexc -compare -e doesn't work properly 
          # basic.end.lexc  -hfst doesn't parse till end
          # xre.any-variations.lexc -foma ?:? problem
          # basic.multichar-symbol-with-0.lexc  - hfst works fine, foma wrong
          # basic.multichar-flag-with-zero.lexc - foma wrong
          
          

 # create foma result     
 #       echo "read lexc $srcdir/$f \n
 #       save stack test.foma.gz \n
 #       quit \n" > tmp-foma-script
 #       foma -q < tmp-foma-script
 #   gunzip test.foma.gz
 #   mv test.foma $RESULT
 #   rm tmp-foma-script
 
 
  for f in $LEXCTESTS ; do
  
    ORIGINAL="$f.result"
    FLAGGED="$f.flag.result"
        
      
        hfst-fst2fst -t $ORIGINAL -o $ORIGINAL.tmp
        
     # echo "comparing eliminated file: $f"
     if ! $TOOLDIR/hfst-compare -e -s $ORIGINAL.tmp $FLAGGED ; then
         echo "results differ: $f"
         exit 1
     fi
     
     rm $ORIGINAL.tmp
     
 done
 
 #   mv test.foma $RESULT
 #   rm tmp-foma-script