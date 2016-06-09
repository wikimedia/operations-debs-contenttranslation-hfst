#!/bin/sh

TOOLDIR=../../tools/src

if [ "$srcdir" = "" ]; then
    srcdir="./";
fi

# basic lookup
if ! echo "cat" | $TOOLDIR/hfst-proc/hfst-apertium-proc cat2dog.hfstol | tr -d '\r' > test.strings ; then
    echo cat fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-cat-out.strings ; then
    echo cat diffs
    exit 1
fi

# basic generation (reverse-lookup)
if ! echo "^dog$" | $TOOLDIR/hfst-proc/hfst-apertium-proc -g cat2dog.genhfstol | tr -d '\r' > test.strings ; then
    echo dog fail
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/cat.strings ; then
    echo dog diffs
    exit 1
fi

# weighted lookup
if ! echo "cat" | $TOOLDIR/hfst-proc/hfst-apertium-proc -W cat_weight_final.hfstol | tr -d '\r' > test.strings ; then
    echo heavy cat fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-cat-weighted-out.strings ; then
    echo heavy cat diffs
    exit 1
fi

# capitalization checks
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc proc-caps.hfstol < $srcdir/proc-caps-in.strings | tr -d '\r' > test.strings ; then
    echo uppercase 1 fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-caps-out1.strings ; then
    echo uppercase 1 diffs
    exit 1
fi
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc -g proc-caps.genhfstol < $srcdir/proc-caps-gen.strings | tr -d '\r' > test.strings ; then
    echo uppercase roundtrip fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-caps-out2.strings  ; then
    echo uppercase roundtrip diffs
    exit 1
fi
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc -c proc-caps.hfstol < $srcdir/proc-caps-in.strings | tr -d '\r' > test.strings ; then
    echo uppercase 2 fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-caps-out3.strings ; then
    echo uppercase 2 diffs
    exit 1
fi
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc -w proc-caps.hfstol < $srcdir/proc-caps-in.strings | tr -d '\r' > test.strings ; then
    echo uppercase 3 fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-caps-out4.strings ; then
    echo uppercase 3 diffs
    exit 1
fi
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc --cg --raw proc-caps.hfstol < $srcdir/proc-caps-in.strings | tr -d '\r' > test.strings ; then
    echo raw cg fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-caps-out5.strings ; then
    echo raw cg diffs
    exit 1
fi

# Xerox format tests:
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc --xerox cat_weight_ambig.hfstol < $srcdir/cat_cat.strings | tr -d '\r' > test.strings ; then
    echo xeroc fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/cat_weight_ambig_xerox.strings ; then
    echo xerox cat_weight_ambig diffs
    exit 1
fi
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc -W --xerox cat_weight_ambig.hfstol < $srcdir/cat_cat.strings | tr -d '\r' > test.strings ; then
    echo xeroc -W fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/cat_weight_ambig_W_xerox.strings ; then
    echo xerox cat_weight_ambig_W diffs
    exit 1
fi
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc -W --weight-classes 1 --xerox cat_weight_ambig.hfstol < $srcdir/cat_cat.strings | tr -d '\r' > test.strings ; then
    echo xeroc -W --weight-classes 1 fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/cat_weight_ambig_W1_xerox.strings ; then
    echo xerox --weight-classes 1 cat_weight_ambig_W diffs
    exit 1
fi

# weight-classes checks
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc --weight-classes 1 cat_weight_ambig.hfstol < $srcdir/cat.strings | tr -d '\r' > test.strings ; then
    echo cat_weight_ambig fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/cat_weight_ambig_out.strings ; then
    echo cat_weight_ambig diffs
    exit 1
fi
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc --weight-classes 2 -W cat_weight_ambig.hfstol < $srcdir/cat.strings | tr -d '\r' > test.strings ; then
    echo cat_weight_ambig_W fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/cat_weight_ambig_W_out.strings ; then
    echo cat_weight_ambig_W diffs
    exit 1
fi

# NUL flush checks
if ! printf 'cat.[][\n]\0cat.[][\n]\0' | $TOOLDIR/hfst-proc/hfst-apertium-proc -z cat2dog.hfstol | tr -d '\r' > test.strings ; then
    echo NUL flush fail:
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-cat-NUL.strings ; then
    echo NUL flush diffs
    exit 1
fi


# compounding / space handling checks
if ! $TOOLDIR/hfst-proc/hfst-apertium-proc compounds.hfstol < $srcdir/proc-compounds.strings | tr -d '\r' > test.strings ; then
    echo compound fail
    cat test.strings
    exit 1
fi
if ! diff test.strings $srcdir/proc-compounds-out.strings ; then
    echo compound diffs
    exit 1
fi
rm test.strings

## skip new test introduced in version 3014...
exit 0

#if ! $TOOLDIR/hfst-proc/hfst-apertium-proc compounds2.hfstol < $srcdir/proc-compounds2.strings | tr -d '\r' > test.strings ; then
#    echo compound fail
#    cat test.strings
#    exit 1
#fi
#if ! diff test.strings $srcdir/proc-compounds2-out.strings ; then
#    exit 1
#fi
#rm test.strings
