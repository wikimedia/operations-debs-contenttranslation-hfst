#!/bin/sh

# A script to download openfst

if ! (mkdir tmp); then
    echo "Error when making temporary directory tmp!";
    exit 1;
fi

cd tmp;

if ! (wget http://openfst.cs.nyu.edu/twiki/pub/Contrib/OpenFstWin/openfstwin-1.3.1.zip); then
    echo "Error when retrieving openfst!";
    exit 1;
fi

if ! (unzip openfstwin-1.3.1.zip); then
    echo "Error when extracting files!";
    exit 1;
fi

# test that src/lib exists

cd src/lib;

cp *.cc ../../../src/lib/

cd ../..

# test that src/include/fst exists

cd src/include/fst;

cp *.h ../../../../src/include/fst

cd ../../..

rm -fR *;

cd ..

rmdir tmp

