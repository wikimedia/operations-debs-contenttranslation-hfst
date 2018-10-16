#!/bin/sh

if [ "$1" = "--help" -o "$1" = "-h" ]; then
    echo "copy-files.sh [--with-c-foma]"
    echo ""
    echo "Copy files needed for pypi distribution on Windows."
    echo ""
    echo "--with-c-foma:   copy the C version of foma backend (instead oc C++)"
    echo ""
    echo "NOTE: flex/bison-generated cc and hh files are copied as such to"
    echo "avoid dependency on swig. Make sure you have a fresh version of them"
    echo "(run 'compile-cc-files-win.sh' in '../../libhfst/src/parsers', if needed)."
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
if ! [ -d "test" ]; then mkdir test; fi

cp -R ../../back-ends/* back-ends/
cp -R ../../libhfst/* libhfst/
cp -R ../hfst/* hfst/
cp -R ../test/* test/

# files under ../
for file in hfst_extensions.cpp hfst_file_extensions.cpp hfst_lexc_extensions.cpp \
hfst_lookup_extensions.cpp hfst_pmatch_extensions.cpp hfst_prolog_extensions.cpp \
hfst_pmatch_tokenize_extensions.cpp hfst_regex_extensions.cpp hfst_rules_extensions.cpp \
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

# unistd.h -> io.h
for file in xfst-lexer htwolcpre1-lexer htwolcpre2-lexer htwolcpre3-lexer sfst-scanner pmatch_lex lexc-lexer xre_lex;
do
    sed -i 's/#include <unistd.h>/#include <io.h>/' libhfst/src/parsers/$file.cpp
done
for file in lex.cmatrix.cpp lex.yy.cpp;
do
    sed -i 's/#include <unistd.h>/#include <io.h>/' back-ends/foma/$file
done

# h.*wrap( ) -> h.*wrap(void)
sed -i 's/hxfstwrap( )/hxfstwrap(void)/' libhfst/src/parsers/xfst-lexer.cpp
sed -i 's/pmatchwrap( )/pmatchwrap(void)/' libhfst/src/parsers/pmatch_lex.cpp
sed -i 's/hlexcwrap( )/hlexcwrap(void)/' libhfst/src/parsers/lexc-lexer.cpp

# copy windows-scpecific headers
cp ../../scripts/windows/stdint.h back-ends/foma/stdint.h
cp ../../scripts/windows/inttypes.h back-ends/foma/inttypes.h
