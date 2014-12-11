#!/bin/sh
TOOLDIR=../../tools/src
HFST_FLAGS="--quiet --output=/dev/null"
VALGRIND="libtool --mode=execute valgrind --leak-check=full"
if ! test -d valgrind-logs ; then
    mkdir valgrind-logs/
fi
if test -z "$srcdir" ; then
    if test $# -eq 1 ; then
        srcdir="$1"
    else
        srcdir="./"
    fi
fi
p=calculate
for i in "" .sfst .ofst .foma; do
    FFLAG=
    case $i in
        .sfst)
            FFLAG="-f sfst";;
        .ofst)
            FFLAG="-f openfst-tropical";;
        .foma)
            FFLAG="-f foma";;
        *)
            FFLAG=;;
    esac
    echo "catcatcat(cat)+" | $VALGRIND --log-file=valgrind-logs/${p}4toINFcats$i.log $TOOLDIR/hfst-calculate $FFLAG $HFST_FLAGS
    echo "{cat}:{dog}" | $VALGRIND --log-file=valgrind-logs/${p}cat2dog$i.log $TOOLDIR/hfst-calculate $FFLAG $HFST_FLAGS
done
p=compare
comparables="cat dog tac cat2dog dog2cat cat_or_dog catdog"
for f in $comparables; do
    $VALGRIND --log-file=valgrind-logs/${p}${f}${f}.log $TOOLDIR/hfst-compare -s $f $f $HFST_FLAGS
    for g in $comparables ; do
        if test $f != $g ; then
            $VALGRIND --log-file=valgrind-logs/${p}${f}${g}-compare -s $f $g
        fi
    done
done

p=compose
for i in "" .sfst .ofst .foma; do 
    if test -f cat$i -a -f cat2dog$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}catcat2dog$i.log $TOOLDIR/hfst-compose cat$i cat2dog$i
        if test -f identity-star$i ; then
            $VALGRIND --log-file=valgrind-logs/${p}catidentity-star$i.log $TOOLDIR/hfst-compose cat$i identity-star$i
        fi
        if test -f unknown-star$i ; then
            $VALGRIND --log-file=valgrind-logs/${p}catunknown-star${i}.log  $TOOLDIR/hfst-compose cat$i identity-star$i 
        fi
    
        if test -f unknown2a$i && test -f identity$i ; then
            $VALGRIND --log-file=valgrind-logs/${p}unknown2aideentity${i}.log  $TOOLDIR/hfst-compose unknown2a$i identity$i 
        fi
    fi
done
p=compose-intersect
for i in "" .sfst .ofst .foma; do
    FFLAG=
    case $i in
        .sfst)
            FFLAG="-f sfst";;
        .ofst)
            FFLAG="-f openfst-tropical";;
        .foma)
            FFLAG="-f foma";;
        *)
            FFLAG=;;
    esac
    if test -f cat$i ; then
        echo "cat|dog" | $TOOLDIR/hfst-calculate $FFLAG > lexicon
        echo "([catdog]|d:D|c:C)*" | $TOOLDIR/hfst-calculate $FFLAG > rules
        echo "([catdog]|d:D|c:C)*" | $TOOLDIR/hfst-calculate $FFLAG >> rules
        $VALGRIND --log-file=valgrind-logs/${p}catordoguppercase${i}.log  $TOOLDIR/hfst-compose-intersect -1 lexicon -2 rules 
        rm lexicon rules
    fi
done
p=concatenate
for i in "" .sfst .ofst .foma; do
    if test -f cat$i -a -f dog$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}catdog${i}.log  $TOOLDIR/hfst-concatenate cat$i dog$i 
    fi
done
p=conjunct
for i in "" .sfst .ofst .foma; do
    if test -f cat_or_dog$i -a -f cat$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}catdog${i}.log  $TOOLDIR/hfst-conjunct cat_or_dog$i cat$i 
    fi
done
p=determinize
for i in "" .sfst .ofst .foma; do
    if test -f non_minimal$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}nonminimal${i}.log  $TOOLDIR/hfst-determinize non_minimal$i 
    fi
done
p=disjunct
for i in "" .sfst .ofst .foma; do
    if test -f cat$i -a -f dog$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}catdog${i}.log  $TOOLDIR/hfst-disjunct cat$i dog$i 
    fi
done
p=fst2strings
for i in "" .sfst .ofst .foma; do
    if test -f cat$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}cat${i}.log  $TOOLDIR/hfst-fst2strings cat$i
    fi
done
p=fst2txt
for i in "" .sfst .ofst .foma; do
    if test -f cat$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}cat${i}.log  $TOOLDIR/hfst-fst2txt -D < cat$i
    fi
done
p=head
for i in "" .sfst .ofst .foma; do
    if test -f cat2dog$i -a -f dog2cat$i ; then
        cat cat2dog$i dog2cat$i | $VALGRIND --log-file=valgrind-logs/${p}2cat2dog${i}.log $TOOLDIR/hfst-head -n 1 
    fi
done
p=invert
for i in "" .sfst .ofst .foma; do
    if test -f cat2dog$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}cat2dog${i}.log  $TOOLDIR/hfst-invert cat2dog$i 
    fi
done
p=lookup
$VALGRIND --log-file=valgrind-logs/${p}cat${i}.log  $TOOLDIR/hfst-lookup cat < $srcdir/cat.strings

# test what strings the transducer [a:b (ID:ID)*] recognizes
for i in "" .sfst .ofst .foma; do

    echo "aa" | $VALGRIND --log-file=valgrind-logs/${p}abid${i}.log  $TOOLDIR/hfst-lookup abid$i
    echo "ac" | $VALGRIND --log-file=valgrind-logs/${p}name${i}.log  $TOOLDIR/hfst-lookup abid$i 
done

p=minimize
for i in "" .sfst .ofst .foma; do
    if test -f non_minimal$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}nonminimal${i}.log  $TOOLDIR/hfst-minimize non_minimal$i 
    fi
done
p=proc
echo "cat" | $VALGRIND --log-file=valgrind-logs/${p}cat${i}.log  $TOOLDIR/hfst-proc-apertium-proc cat2dog.ol
echo "^dog$" | $VALGRIND --log-file=valgrind-logs/${p}gen${i}.log  $TOOLDIR/hfst-apertium-proc-apertium-proc -g cat2dog.gen.ol
echo "cat" | $VALGRIND --log-file=valgrind-logs/${p}weight${i}.log  $TOOLDIR/hfst-proc-apertium-proc -W cat_weight_final.ol 
$VALGRIND --log-file=valgrind-logs/${p}caps${i}.log  $TOOLDIR/hfst-apertium-proc-proc proc-caps.ol < $srcdir/proc-caps-in.strings
$VALGRIND --log-file=valgrind-logs/${p}capsgen${i}.log -apertium-proc -g proc-caps.gen.ol < $srcdir/proc-caps-gen.strings
$VALGRIND --log-file=valgrind-logs/${p}capsc${i}.log  $TOOLDIR/hfst-apertium-proc-proc -c proc-caps.ol < $srcdir/proc-caps-in.strings
$VALGRIND --log-file=valgrind-logs/${p}capsw${i}.log  $TOOLDIR/hfst-apertium-proc-proc -w proc-caps.ol < $srcdir/proc-caps-in.strings
$VALGRIND --log-file=valgrind-logs/${p}rawcg${i}.log  $TOOLDIR/hfst-apertium-proc-proc --cg --raw proc-caps.ol < $srcdir/proc-caps-in.strings
p=project
for i in "" .sfst .ofst .foma; do
    if test -f cat2dog$i -a cat$i -a dog$i ; then
        for j in input output; do
            $VALGRIND --log-file=valgrind-logs/${p}cat2dog${j}${i}.log  $TOOLDIR/hfst-project -p $j cat2dog$i 
            $TOOLDIR/hfst-concatenate cat2dog$i unk2unk$i > concatenation
            $VALGRIND --log-file=valgrind-logs/${p}unkcat2dog${i}.log  $TOOLDIR/hfst-project -p $j concatenation
            rm concatenation
        done
    fi
done
p=push-weights
$VALGRIND --log-file=valgrind-logs/${p}cat2doginitial${i}.log  $TOOLDIR/hfst-push-weights -p initial cat2dog 
$VALGRIND --log-file=valgrind-logs/${p}cat2dogfinal${i}.log  $TOOLDIR/hfst-push-weights -p final cat2dog 
p=regexp2fst
for i in sfst openfst-tropical foma; do
    $VALGRIND --log-file=valgrind-logs/${p}catanddog${i}.log  $TOOLDIR/hfst-regexp2fst -f $i $srcdir/cats_and_dogs.xre 
    $VALGRIND --log-file=valgrind-logs/${p}catanddogsemicolon${i}.log  $TOOLDIR/hfst-regexp2fst -S -f $i $srcdir/cats_and_dogs_semicolon.xre 
done
p=remove-epsilons
for i in "" .sfst .ofst .foma; do
    if test -f non_minimal$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}nonminimal${i}.log  $TOOLDIR/hfst-remove-epsilons non_minimal$i 
    fi
done
p=repeat
for i in "" .sfst .ofst .foma; do
    if test -f cat$i -a -f 2to4cats$i -a -f 0to3cats$i \
        -a -f 4cats$i -a -f 4toINFcats$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}2to4cats${i}.log  $TOOLDIR/hfst-repeat -f 2 -t 4 cat$i 
        $VALGRIND --log-file=valgrind-logs/${p}0to3cats${i}.log  $TOOLDIR/hfst-repeat -t 3 cat$i 
        $VALGRIND --log-file=valgrind-logs/${p}4cats${i}.log  $TOOLDIR/hfst-repeat -f 4 -t 4 cat$i 
        $VALGRIND --log-file=valgrind-logs/${p}4toinfcats${i}.log  $TOOLDIR/hfst-repeat -f 4 cat$i 
    fi
done
p=reverse-functionality.sh
for i in "" .sfst .ofst .foma; do
    if test -f cat2dog$i -a dog2cat$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}cat2dog${i}.log  $TOOLDIR/hfst-invert cat2dog$i 
    fi
done
p=split
for i in "" .sfst .ofst .foma; do
    if test -f cat2dog$i -a -f dog2cat$i ; then
        cat cat2dog$i dog2cat$i | $VALGRIND --log-file=valgrind-logs/${p}cat2dog2cat${i}.log  $TOOLDIR/hfst-split
        rm 1 2;
    fi
done
p=strings2fst
for i in "" .sfst .ofst .foma; do
    FFLAG=
    case $i in
        .sfst)
            FFLAG="-f sfst";;
        .ofst)
            FFLAG="-f openfst-tropical";;
        .foma)
            FFLAG="-f foma";;
        *)
            FFLAG=;;
    esac
    $VALGRIND --log-file=valgrind-logs/${p}cat${i}.log  $TOOLDIR/hfst-strings2fst $FFLAG $srcdir/cat.strings 
    $VALGRIND --log-file=valgrind-logs/${p}c_a_t${i}.log  $TOOLDIR/hfst-strings2fst $FFLAG -S $srcdir/c_a_t.strings 
    $VALGRIND --log-file=valgrind-logs/${p}heavycat${i}.log  $TOOLDIR/hfst-strings2fst $FFLAG $srcdir/heavycat.strings 
    $VALGRIND --log-file=valgrind-logs/${p}cat2dog${i}.log  $TOOLDIR/hfst-strings2fst $FFLAG $srcdir/cat2dog.strings 
    $VALGRIND --log-file=valgrind-logs/${p}c_a_t2d_o_g${i}.log  $TOOLDIR/hfst-strings2fst $FFLAG -S $srcdir/cat2dog.spaces 
    $VALGRIND --log-file=valgrind-logs/${p}cat2dogpairs${i}.log  $TOOLDIR/hfst-strings2fst $FFLAG -p -S $srcdir/cat2dog.pairs 
    $VALGRIND --log-file=valgrind-logs/${p}cat2dogps${i}.log  $TOOLDIR/hfst-strings2fst $FFLAG -p $srcdir/cat2dog.pairstring 
    $VALGRIND --log-file=valgrind-logs/${p}name${i}.log  $TOOLDIR/hfst-strings2fst $srcdir/utf-8.strings 
done

p=substitute
for i in "" .sfst .ofst .foma; do
    if test -f cat$i -a -f dog$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}cat2dog${i}.log  $TOOLDIR/hfst-substitute cat$i -F $srcdir/cat2dog.substitute 
        $VALGRIND --log-file=valgrind-logs/${p}c2d${i}.log $TOOLDIR/hfst-substitute cat$i -f c -t d 
    fi
done
p=subtract
for i in "" .sfst .ofst .foma; do
    if test -f cat_or_dog$i -a -f dog$i -a cat$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}sutractcatdog${i}.log  $TOOLDIR/hfst-subtract cat_or_dog$i dog$i
    fi 
    if test -f empty$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}empty${i}.log  $TOOLDIR/hfst-subtract empty$i empty$i 
    fi
    if test -f unk_or_id_star$i -a -f a2b$i -a -f a2b_complement$i -a -f a2b_input_projection_complement$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}unkida2b${i}.log  $TOOLDIR/hfst-subtract -1 unk_or_id_star$i -2 a2b$i 
        $TOOLDIR/hfst-project -p input a2b$i > a2b_input
        $VALGRIND --log-file=valgrind-logs/${p}unkida2binput${i}.log  $TOOLDIR/hfst-subtract -1 unk_or_id_star$i -2 a2b_input 
        rm a2b_input
    fi
done
if test -f cat2dog_0.3.ofst -a -f cat2dog_0.5.ofst ; then
    $VALGRIND --log-file=valgrind-logs/${p}cat2dog0305${i}.log  $TOOLDIR/hfst-subtract -1 cat2dog_0.3.ofst -2 cat2dog_0.5.ofst 
    $VALGRIND --log-file=valgrind-logs/${p}cat2dog0503${i}.log  $TOOLDIR/hfst-subtract -2 cat2dog_0.3.ofst -1 cat2dog_0.5.ofst 
fi
p=summarize
for i in "" .sfst .ofst .foma; do
    if test -f cat$i ; then
        $VALGRIND --log-file=valgrind-logs/${p}cat${i}.log  $TOOLDIR/hfst-summarize cat$i
    fi
done
p=tail
for i in "" .sfst .ofst .foma; do
    if test -f cat2dog$i -a -dog2cat$i ; then
        cat cat2dog$i dog2cat$i | $VALGRIND --log-file=valgrind-logs/${p}name${i}.log  $TOOLDIR/hfst-tail -n 1 
    fi
done
p=txt2fst
for i in "" .sfst .ofst .foma; do
    FFLAG=
    case $i in
        .sfst)
            FFLAG="-f sfst";;
        .ofst)
            FFLAG="-f openfst-tropical";;
        .foma)
            FFLAG="-f foma";;
        *)
            FFLAG=;;
    esac
    $VALGRIND --log-file=valgrind-logs/${p}cat${i}.log  $TOOLDIR/hfst-txt2fst $FFLAG $srcdir/cat.txt 
done
# valgrind.sh
