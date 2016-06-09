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
          basic.lowercase-lexicon-end.lexc 
          hfst.weights.lexc      
          xre.automatic-multichar-symbols.lexc xre.basic.lexc 
          xre.definitions.lexc xre.months.lexc xre.nested-definitions.lexc 
          xre.numeric-star.lexc xre.sharp.lexc xre.quotations.lexc
          xre.star-plus-optional.lexc
          xre.any-variations.lexc"
          
          # basic.end.lexc  -hfst doesn't parse till end
          # xre.any-variations.lexc -foma ?:? problem
          # basic.multichar-symbol-with-0.lexc  - hfst works fine, foma wrong
          # basic.multichar-flag-with-zero.lexc - foma wrong

          
LEXCXFAIL="xfail.bogus.lexc xfail.ISO-8859-1.lexc xfail.lexicon-semicolon.lexc"




FNAME="openfst-tropical";
FFLAG="-f openfst-tropical";

for f in $LEXCTESTS ; do
     # echo "file: $f"
    
     RESULT="$f.flag.result"
     
     # echo "result: $RESULT"
 
    if ! $TOOLDIR/hfst-lexc -F $FFLAG $f -o $RESULT 2> /dev/null; then
        echo "$TOOLDIR/hfst-lexc -F $FFLAG $f -o $RESULT failed with $?"
        exit 1
    fi
    
           
done