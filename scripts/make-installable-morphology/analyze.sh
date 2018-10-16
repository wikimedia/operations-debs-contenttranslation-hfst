#!/bin/bash
trdir=TRPATH
if [ ! -d "$trdir" ] ; then
    echo $trdir not found
    exit 1
fi
if [ ! -e "$trdir"/LANGNAME-tokenize.pmatch ] ; then
    echo "$trdir/LANGNAME-tokenize.pmatch not found"
    exit 1
fi
if ! command -v hfst-tokenize > /dev/null; then
    echo "hfst-tokenize not found on your system"
    echo "HFST is available from https://github.com/hfst/hfst"
    exit 1
fi
if [ "$1" == "--help" ] ; then
    echo "Provides a morphological analysis of text from standard input."
    echo "Input can be running text, in which case it is tokenized first."
    exit 0
fi

hfst-tokenize --unique --xerox $trdir/LANGNAME-tokenize.pmatch
