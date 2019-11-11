#!/bin/bash

echo "Running test for finnish-tagtools in local directory:"
echo

TMP="test/tmp.txt"
DIFF="test/diff.txt"
TXT="test/test-input.txt"
TOKENS="test/tokens-input.txt"

function cleanup()
{
    rm -f $TMP
    rm -f $DIFF
}

./finnish-tokenize < $TXT > $TMP
if diff test/tokenize-expected-output.txt $TMP > $DIFF; then
    echo "finnish-tokenize ok"
else
    echo "finnish-tokenize test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

./finnish-postag < $TXT > $TMP
if diff test/postag-expected-output.txt $TMP > $DIFF; then
    echo "finnish-postag ok"
else
    echo "finnish-postag test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

./finnish-postag --no-tokenize < $TOKENS > $TMP
if diff test/postag-no-tokenize-expected-output.txt $TMP > $DIFF; then
    echo "finnish-postag --no-tokenize ok"
else
    echo "finnish-postag --no-tokenize test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

./finnish-nertag < $TXT > $TMP
if diff test/nertag-expected-output.txt $TMP > $DIFF; then
    echo "finnish-nertag ok"
else
    echo "finnish-nertag test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

./finnish-nertag --no-tokenize < $TOKENS > $TMP
if diff test/nertag-no-tokenize-expected-output.txt $TMP > $DIFF; then
    echo "finnish-nertag --no-tokenize ok"
else
    echo "finnish-nertag --no-tokenize test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

./finnish-nertag --show-analyses < $TXT > $TMP
if diff test/nertag-show-analyses-expected-output.txt $TMP > $DIFF; then
    echo "finnish-nertag --show-analyses ok"
else
    echo "finnish-nertag --show-analyses test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

./finnish-nertag --no-tokenize --show-analyses < $TOKENS > $TMP
if diff test/nertag-show-analyses-no-tokenize-expected-output.txt $TMP > $DIFF; then
    echo "finnish-nertag --no-tokenize --show-analyses ok"
else
    echo "finnish-nertag --no-tokenize --show-analyses test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

./finnish-nertag --show-nested < $TXT > $TMP
if diff test/nertag-show-nested-expected-output.txt $TMP > $DIFF; then
    echo "finnish-nertag --show-nested ok"
else
    echo "finnish-nertag --show-nested test failed:"
    cat test/diff.txt
    cleanup
    exit 1
fi

echo "All tests passed."
echo
cleanup
exit 0
