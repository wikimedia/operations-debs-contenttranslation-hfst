#!/bin/sh

if [ "$1" = "-h" -o "$1" = "--help" ]; then
    echo ""
    echo "  Usage:  "$0" [--python PYTHONX.Y]"
    echo ""
    exit 0;
fi

PYTHON=python
if [ "$1" = "--python" ]; then
    PYTHON=$2;
fi

for pytest in \
    test_constructors.py test_flag_diacritics.py \
    test_hfst_basic_transducer.py test_streams.py test_tokenizer.py \
    test_transducer_functions.py test_extensions.py \
    test_examples.py test_xre_compiler.py; # test_lexc.py
    do
    echo $pytest":"
    echo "==================================="
    echo
    if (! $PYTHON $pytest); then
	echo "============================================="
	echo "FAIL: " $pytest;
	echo "============================================="
	exit 1;
    fi;
    echo
done

echo "test_std_streams.sh:"
echo "==================================="
echo
if ! ./test_std_streams.sh --python $PYTHON; then 
    echo "==========================="
    echo "FAIL: test_std_streams.sh";
    echo "==========================="
    exit 1;
fi

echo "====================="
echo "All 10 tests passed."
echo "====================="
