#!/bin/sh
TOOLDIR=../../tools/src
PMATCH2FST=
PMATCH=

if [ "$1" = '--python' ]; then
    PMATCH2FST="python3 ./hfst-pmatch2fst.py"
    PMATCH="python3 ./hfst-pmatch.py"
else
    PMATCH2FST=$TOOLDIR/hfst-pmatch2fst
    PMATCH=$TOOLDIR/hfst-pmatch
    for tool in $TOOL $PMATCH2FST;
    do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

if [ "$srcdir" = "" ] ; then
    srcdir=. ;
fi

if ! $PMATCH2FST $srcdir/pmatch_blanks.txt > test.pmatch ; then
    exit 1
fi
# Test with any old string
if ! $PMATCH --newline test.pmatch < $srcdir/cat.strings > pmatch.out ; then
    exit 1
fi

echo 'set need-separators off regex [\Whitespace]+ EndTag(Q);' | $PMATCH2FST > test.pmatch

echo 'a b  c' | $PMATCH --newline test.pmatch > pmatch.out
if ! echo '<Q>a</Q> <Q>b</Q>  <Q>c</Q>' | diff pmatch.out - > /dev/null ; then
    exit 1
fi

# printf to workaround a weird bug with \x22 when bash is called as /bin/sh on macos:
printf '%s\n' 'set need-separators off regex "\x22" EndTag(Q);' | $PMATCH2FST > test.pmatch

echo 'a "b"  c' | $PMATCH --newline test.pmatch > pmatch.out
if ! echo 'a <Q>"</Q>b<Q>"</Q>  c' | diff pmatch.out - > /dev/null ; then
    exit 1
fi

echo 'set need-separators off regex "\"" EndTag(Q);' | $PMATCH2FST > test.pmatch

echo 'a "b"  c' | $PMATCH --newline test.pmatch > pmatch.out
if ! echo 'a <Q>"</Q>b<Q>"</Q>  c' | diff pmatch.out - > /dev/null ; then
    exit 1
fi

echo 'set need-separators off regex {"} EndTag(Q);' | $PMATCH2FST > test.pmatch

echo 'a "b"  c' | $PMATCH --newline test.pmatch > pmatch.out
if ! echo 'a <Q>"</Q>b<Q>"</Q>  c' | diff pmatch.out - > /dev/null ; then
    exit 1
fi

echo 'set need-separators off regex %" EndTag(Q);' | $PMATCH2FST > test.pmatch

echo 'a "b"  c' | $PMATCH --newline test.pmatch > pmatch.out
if ! echo 'a <Q>"</Q>b<Q>"</Q>  c' | diff pmatch.out - > /dev/null ; then
    exit 1
fi

rm -f pmatch.out test.pmatch
exit 0
