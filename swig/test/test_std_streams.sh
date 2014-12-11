#!/bin/sh
#
# Test writing to and reading from standard input and output streams
# using swig bindings. The python used can be defined with option
# '--python PYTHON'. The test depends on tools hfst-strings2fst and
# hfst-compare as well as on the script test_std_streams.py.
#

# Check that these tools are found
for tool in hfst-strings2fst hfst-compare hfst-format;
do
    if (which $tool | grep "not found" ); then
	echo "ERROR: the tool "$tool" was not found, install it before running this test (test_std_streams.sh)"
	exit 1;
    fi
done

# Use silent mode
STRINGS2FST=hfst-strings2fst" -s"
COMPARE=hfst-compare" -s"

# Define python
PYTHON=python
if [ "$1" = "--python" ]; then
    PYTHON=$2;
fi

# Convert these strings into transducers

STRING1="abcdefghijklmnopqrstuvwxyz"
STRING2="ABCDEFGHIJKLMNOPQRSTUVWXYZ"

if (hfst-format --list | grep 'sfst' > /dev/null); then
    echo $STRING1 | $STRINGS2FST -f sfst > tr1.sfst
    echo $STR1NG2 | $STRINGS2FST -f sfst > tr2.sfst
    cat tr1.sfst tr2.sfst > tr.sfst
    rm tr1.sfst tr2.sfst
else
    echo "warning: sfst back-end not available, assumed switched off and skipping"
fi

echo $STRING1 | $STRINGS2FST -f openfst-tropical > tr1.ofst
echo $STRING2 | $STRINGS2FST -f openfst-tropical > tr2.ofst
cat tr1.ofst tr2.ofst > tr.ofst
rm tr1.ofst tr2.ofst

if (hfst-format --list | grep 'foma' > /dev/null); then
    echo $STRING1 | $STRINGS2FST -f foma > tr1.foma
    echo $STRING2 | $STRINGS2FST -f foma > tr2.foma
    cat tr1.foma tr2.foma > tr.foma
    rm tr1.foma tr2.foma
else
    echo "warning: foma back-end not available, assumed switched off and skipping"
fi


# Perform the tests for all transducer types:

# SFST
if (hfst-format --list | grep 'sfst' > /dev/null); then
    if ! (cat tr.sfst | $PYTHON ./test_std_streams.py sfst 2 > tmp.sfst); then
	echo "ERROR: in sfst"
	rm tr.sfst
	exit 1
    fi
    if ! ($COMPARE tr.sfst tmp.sfst); then
	echo "ERROR in sfst"
	rm tr.sfst tmp.sfst
	exit 1
    fi
    rm tr.sfst tmp.sfst
fi

# OPENFST
if ! (cat tr.ofst | $PYTHON ./test_std_streams.py openfst 2 > tmp.ofst); then
    echo "ERROR: in openfst"
    rm tr.ofst
    exit 1
fi
if ! ($COMPARE tr.ofst tmp.ofst); then
    echo "ERROR: in openfst"
    rm tr.ofst tmp.ofst
    exit 1
fi
rm tr.ofst tmp.ofst

# FOMA
if (hfst-format --list | grep 'foma' > /dev/null); then
    if ! (cat tr.foma | $PYTHON ./test_std_streams.py foma 2 > tmp.foma); then
	rm tr.foma
	echo "ERROR: in foma"
	exit 1
    fi  
    if ! ($COMPARE tr.foma tmp.foma); then
	echo "ERROR: in foma"
	rm tr.foma tmp.foma
	exit 1
    fi  
    rm tr.foma tmp.foma
fi
