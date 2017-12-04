#!/bin/sh

TOOLDIR=../../tools/src

if [ "$srcdir" = "" ]; then
    srcdir="./";
fi

if ! command -V timeout >/dev/null 2>/dev/null; then
    # require /usr/bin/timeout, since it could hang if there's a bug
    exit 77
fi

# Prerequisites
if ! $TOOLDIR/hfst-lexc -q < $srcdir/tokenize-dog-in.lexc > $srcdir/tokenize-dog-gen.hfst; then
    echo lexc dog fail
    exit 1
fi
if ! $TOOLDIR/hfst-invert < $srcdir/tokenize-dog-gen.hfst > $srcdir/tokenize-dog.hfst; then
    echo invert dog fail
    exit 1
fi
if ! $TOOLDIR/hfst-pmatch2fst < $srcdir/tokenize-dog.pmscript > $srcdir/tokenize-dog.pmhfst; then
    echo pmatch2fst tokenize-dog fail
    exit 1
fi

tmpd=$(mktemp -d -t hfst-tokenize-tests.XXXXXXXX)
to="${tmpd}/to"
from="${tmpd}/from"
mkfifo "${to}" "${from}"

# Server:
$TOOLDIR/hfst-tokenize --giella-cg --superblanks $srcdir/tokenize-dog.pmhfst <"${to}" >"${from}" &
pid=$!
trap 'kill $pid; wait $pid 2>/dev/null; rm -rf "${tmpd}"' EXIT


# Client:
exec 3>"${to}"
exec 4<"${from}"
for _ in test a couple times; do
    timeout 1 printf 'dog[\\\n<\\\\>]cat !and \ndogs[][\n]\0' >&3
    case $? in
        0) : ;;
        124) echo tokenize --giella-cg flushing write timed out
             exit 1
             ;;
        *) echo tokenize --giella-cg flushing write failed with "$?"
           exit 1
           ;;
    esac
    timeout 1 sed '/^<STREAMCMD:FLUSH>$/{q}' <&4 >test.strings
    case $? in
        0) : ;;
        124) echo tokenize --giella-cg flushing read timed out
             exit 1
             ;;
        *) echo tokenize --giella-cg flushing read failed with "$?", output is:
           cat test.strings
           exit 1
           ;;
    esac
    if ! diff test.strings $srcdir/tokenize-dog-out-giella-cg-flushing.strings ; then
        echo diff test.strings $srcdir/tokenize-dog-out-giella-cg-flushing.strings
        exit 1
    fi
done

rm test.strings tokenize-dog.pmhfst tokenize-dog.hfst tokenize-dog-gen.hfst
exit 0
