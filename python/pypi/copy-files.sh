#!/bin/sh

## Copy files needed for a pypi distribution for linux or os x.
## copy-files-win.sh is the equivalent script for windows environment.

if [ "$1" = "--help" -o "$1" = "-h" ]; then
    echo "copy-files.sh [--with-c-foma]"
    echo ""
    echo "Copy files needed for a pypi distribution on linux and OS X."
    echo ""
    echo "--with-c-foma:   copy the C version of foma backend (instead of C++)"
    echo ""
    echo "NOTE: flex/bison-generated cc and hh files are copied as such to"
    echo "avoid dependency on swig. Make sure you have a fresh version of them"
    echo "(run 'make' in top directory, if needed)."
    echo ""
    exit 0
fi

CPP_FOMA="true"
if [ "$1" = "--with-c-foma" ]; then
    CPP_FOMA="false"
fi

if ! [ -d "back-ends" ]; then mkdir back-ends; fi
if ! [ -d "libhfst" ]; then mkdir libhfst; fi
if ! [ -d "hfst" ]; then mkdir hfst; fi

cp -R ../../back-ends/* back-ends/
cp -R ../../libhfst/* libhfst/
cp -R ../hfst/* hfst/

for file in hfst_extensions.cpp hfst_file_extensions.cpp hfst_lexc_extensions.cpp \
hfst_lookup_extensions.cpp hfst_pmatch_extensions.cpp hfst_pmatch_tokenize_extensions.cpp \
hfst_prolog_extensions.cpp hfst_regex_extensions.cpp hfst_rules_extensions.cpp \
hfst_xfst_extensions.cpp hfst_sfst_extensions.cpp libhfst.i docstrings.i ;
do
    cp ../$file $file
done

# Copy all files that have a c++ version as backend files to be compiled.
if [ "$CPP_FOMA" = "true" ]; then
    cp back-ends/foma/cpp-version/* back-ends/foma/
fi

# .cc -> .cpp
for dir in back-ends libhfst;
do
    find $dir -name "*.cc" | sed 's/\(.*\).cc/mv \1.cc \1.cpp/' | sh
done
