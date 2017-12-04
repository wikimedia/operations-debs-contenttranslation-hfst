#!/bin/sh

if [ "$1" = "--help" -o "$1" = "-h" ]; then
    echo ""
    echo "Copy winopenfst and foma back-ends, libhfst/src and python bindings to a directory."
    echo "The directory can be used for creating python bindings on Windows."
    echo ""
    echo "Usage: copy-for-windows.sh [DESTDIR]"
    echo ""
    echo "DESTDIR: name of the directory where files are copied"
    echo ""
    exit 0
fi

# A script for copying winopenfst and foma backends, libhfst/src and
# python bindings in a directory given as first argument.

# In the destination directory, run:
# C:\PythonXY\python.exe setup.py [ARGS]

if [ -d "$1" ]; then
    echo "Directory $1 exists"
    exit 1
else
    mkdir $1
fi

#openfstdir=
#if [ "$2" = "" ]; then
    openfstdir="back-ends/openfstwin"
#    echo "No second argument given, defaulting to openfst directory '$openfstdir'"
#else
#    openfstdir=$2
#fi

# copy python stuff
for file in docstrings.i libhfst.i \
hfst_extensions.cc hfst_file_extensions.cc hfst_lexc_extensions.cc hfst_lookup_extensions.cc \
hfst_pmatch_extensions.cc hfst_prolog_extensions.cc hfst_regex_extensions.cc \
hfst_rules_extensions.cc hfst_xfst_extensions.cc hfst_sfst_extensions.cc ;
do
    cp python/$file $1/
done

for file in setup.py MANIFEST.in README README.rst setup.cfg config.h COPYING ;
do
    cp python/pypi/$file $1/
done

mkdir $1/hfst
mkdir $1/hfst/exceptions
mkdir $1/hfst/sfst_rules
mkdir $1/hfst/xerox_rules

cp python/hfst/__init__.py $1/hfst/
cp python/hfst/exceptions/__init__.py $1/hfst/exceptions/
cp python/hfst/sfst_rules/__init__.py $1/hfst/sfst_rules/
cp python/hfst/xerox_rules/__init__.py $1/hfst/xerox_rules/

mkdir $1/test
for file in README test.sh test.bat \
    test_fail.xfst testfile.att testfile_fail.att test_pass.xfst test.lexc \
    cats_and_dogs.prolog cats_and_dogs_fail.prolog \
    test_pmatch.py test_prolog.py test_exceptions.py test_dir_hfst.py \
    test_dir_hfst_exceptions.py test_dir_hfst_sfst_rules.py test_tokenizer.py \
    test_read_att_transducer.py test_xre.py test_hfst.py test_examples.py \
    test_att_reader.py test_prolog_reader.py \
    test_streams_1.py test_streams_2.py test_streams_3.py streets.txt \
    test_xerox_rules.py ;
do
    cp python/test/$file $1/test/
done


mkdir $1/back-ends

# foma back-end
mkdir $1/back-ends/foma/

for file in \
apply.c coaccessible.c constructions.c \
define.c determinize.c dynarray.c \
extract.c flags.c int_stack.c io.c \
lex.cmatrix.c lex.yy.c lexcread.c mem.c minimize.c \
regex.c reverse.c rewrite.c sigma.c \
spelling.c stringhash.c structures.c \
topsort.c trie.c utf8.c foma.h fomalib.h \
fomalibconf.h regex.h lexc.h;
do
    cp back-ends/foma/$file $1/back-ends/foma/;
done
# there is a file with the same name in openfstwin
#mv $1/back-ends/foma/flags.c $1/back-ends/foma/_flags.c

# openfstwin back-end
mkdir $1/back-ends/openfstwin
mkdir $1/back-ends/openfstwin/src
mkdir $1/back-ends/openfstwin/src/include
mkdir $1/back-ends/openfstwin/src/include/fst
mkdir $1/back-ends/openfstwin/src/lib

for file in \
compat flags fst properties symbol-table symbol-table-ops util;
do
    cp $openfstdir/src/lib/$file.cc $1/back-ends/openfstwin/src/lib/$file.cpp
done

# file symbol-table-ops.cc not in version 1.2.6
#if [ -f "$openfstdir/src/lib/symbol-table-ops.cc" ]; then
#    cp $openfstdir/src/lib/symbol-table-ops.cc $1/back-ends/openfstwin/src/lib/symbol-table-ops.cpp
#fi

cp $openfstdir/src/include/fst/*.h $1/back-ends/openfstwin/src/include/fst/

# libhfst/src and subdirectories
mkdir $1/libhfst
mkdir $1/libhfst/src
mkdir $1/libhfst/src/implementations
mkdir $1/libhfst/src/implementations/compose_intersect
mkdir $1/libhfst/src/implementations/optimized-lookup
mkdir $1/libhfst/src/parsers
mkdir $1/libhfst/src/parsers/alphabet_src
mkdir $1/libhfst/src/parsers/commandline_src
mkdir $1/libhfst/src/parsers/io_src
mkdir $1/libhfst/src/parsers/rule_src
mkdir $1/libhfst/src/parsers/string_src
mkdir $1/libhfst/src/parsers/variable_src


# libhfst/src without subdirectories
for file in \
FormatSpecifiers.h HarmonizeUnknownAndIdentitySymbols.h \
HfstDataTypes.h HfstEpsilonHandler.h HfstExceptionDefs.h \
HfstExtractStrings.h HfstFlagDiacritics.h \
HfstInputStream.h HfstLookupFlagDiacritics.h HfstOutputStream.h \
HfstSymbolDefs.h HfstTokenizer.h HfstTransducer.h HfstXeroxRules.h \
HfstStrings2FstTokenizer.h hfst.h hfst.hpp.in hfst_apply_schemas.h hfstdll.h \
hfst-string-conversions.h HfstPrintDot.h HfstPrintPCKimmo.h \
string-utils.h;
do
    cp libhfst/src/$file $1/libhfst/src/
done

for file in \
HarmonizeUnknownAndIdentitySymbols HfstApply HfstDataTypes \
HfstEpsilonHandler HfstExceptionDefs HfstFlagDiacritics \
HfstInputStream HfstLookupFlagDiacritics HfstOutputStream HfstRules \
HfstSymbolDefs HfstTokenizer HfstTransducer HfstXeroxRules \
hfst-string-conversions \
HfstStrings2FstTokenizer HfstXeroxRulesTest HfstPrintDot HfstPrintPCKimmo \
string-utils;
do
    cp libhfst/src/$file.cc $1/libhfst/src/$file.cpp
done

# libhfst/src/implementations without subdirectories
for file in \
ConvertTransducerFormat.h FomaTransducer.h \
HfstOlTransducer.h HfstBasicTransition.h HfstBasicTransducer.h \
HfstTropicalTransducerTransitionData.h LogWeightTransducer.h \
TropicalWeightTransducer.h;
do
    cp libhfst/src/implementations/$file $1/libhfst/src/implementations/
done

for file in \
ConvertFomaTransducer ConvertLogWeightTransducer ConvertOlTransducer \
ConvertTransducerFormat ConvertTropicalWeightTransducer FomaTransducer \
HfstOlTransducer HfstBasicTransducer HfstBasicTransition HfstTropicalTransducerTransitionData \
LogWeightTransducer TropicalWeightTransducer;
do
    cp libhfst/src/implementations/$file.cc $1/libhfst/src/implementations/$file.cpp
done

# implementations/compose_intersect
for file in \
ComposeIntersectFst ComposeIntersectLexicon ComposeIntersectRule \
ComposeIntersectRulePair ComposeIntersectUtilities;
do
    cp libhfst/src/implementations/compose_intersect/$file.cc \
        $1/libhfst/src/implementations/compose_intersect/$file.cpp
    cp libhfst/src/implementations/compose_intersect/$file.h \
        $1/libhfst/src/implementations/compose_intersect/$file.h
done

# implementations/optimized-lookup
for file in \
convert pmatch transducer;
do
    cp libhfst/src/implementations/optimized-lookup/$file.cc \
        $1/libhfst/src/implementations/optimized-lookup/$file.cpp
    cp libhfst/src/implementations/optimized-lookup/$file.h \
        $1/libhfst/src/implementations/optimized-lookup/$file.h
done
for file in \
find_epsilon_loops ospell;
do
    cp libhfst/src/implementations/optimized-lookup/$file.cc \
        $1/libhfst/src/implementations/optimized-lookup/$file.cpp
done

# libhfst/src/parsers
for file in \
LexcCompiler PmatchCompiler XreCompiler XfstCompiler xfst_help_message \
TwolcCompiler \
lexc-utils pmatch_utils xre_utils xfst-utils SfstCompiler SfstAlphabet SfstBasic SfstUtf8;
do
    cp libhfst/src/parsers/$file.cc \
        $1/libhfst/src/parsers/$file.cpp
    cp libhfst/src/parsers/$file.h \
        $1/libhfst/src/parsers/$file.h
done
for file in \
lexc-lexer pmatch_lex xre_lex xfst-lexer sfst-scanner htwolcpre1-lexer htwolcpre2-lexer htwolcpre3-lexer;
do
    cp libhfst/src/parsers/$file.cc \
        $1/libhfst/src/parsers/$file.cpp
done
for file in \
lexc-parser pmatch_parse xre_parse xfst-parser sfst-compiler htwolcpre1-parser htwolcpre2-parser htwolcpre3-parser;
do
    cp libhfst/src/parsers/$file.cc \
        $1/libhfst/src/parsers/$file.cpp
    cp libhfst/src/parsers/$file.hh \
        $1/libhfst/src/parsers/$file.hh
done

for file in xfst-lexer htwolcpre1-lexer htwolcpre2-lexer htwolcpre3-lexer sfst-scanner;
do
    sed -i 's/#include <unistd.h>/#include <io.h>/' $1/libhfst/src/parsers/$file.cpp
    sed -i 's/hxfstwrap( )/hxfstwrap(void)/' $1/libhfst/src/parsers/$file.cpp
done

for file in HfstTwolcDefs.h common_globals.h grammar_defs.h;
do
    cp libhfst/src/parsers/$file $1/libhfst/src/parsers/$file
done

PARSERDIR=libhfst/src/parsers

cp $PARSERDIR/alphabet_src/Alphabet.cc $1/$PARSERDIR/alphabet_src/Alphabet.cpp
cp $PARSERDIR/alphabet_src/Alphabet.h $1/$PARSERDIR/alphabet_src/Alphabet.h
cp $PARSERDIR/commandline_src/CommandLine.cc $1/$PARSERDIR/commandline_src/CommandLine.cpp
cp $PARSERDIR/commandline_src/CommandLine.h $1/$PARSERDIR/commandline_src/CommandLine.h
cp $PARSERDIR/io_src/InputReader.cc $1/$PARSERDIR/io_src/InputReader.cpp
cp $PARSERDIR/io_src/InputReader.h $1/$PARSERDIR/io_src/InputReader.h
cp $PARSERDIR/io_src/input_defs.h $1/$PARSERDIR/io_src/input_defs.h

for file in ConflictResolvingLeftArrowRule ConflictResolvingRightArrowRule \
					   LeftArrowRule LeftArrowRuleContainer LeftRestrictionArrowRule OtherSymbolTransducer \
					   RightArrowRule RightArrowRuleContainer Rule RuleContainer TwolCGrammar;
do
    cp $PARSERDIR/rule_src/$file.h $1/$PARSERDIR/rule_src/$file.h
    cp $PARSERDIR/rule_src/$file.cc $1/$PARSERDIR/rule_src/$file.cpp
done

cp $PARSERDIR/string_src/string_manipulation.cc $1/$PARSERDIR/string_src/string_manipulation.cpp
cp $PARSERDIR/string_src/string_manipulation.h $1/$PARSERDIR/string_src/string_manipulation.h

for file in ConstContainerIterator.h MatchedConstContainerIterator.h MixedConstContainerIterator.h \
				     RuleSymbolVector.h RuleVariables.h RuleVariablesConstIterator.h VariableBlock.h VariableBlockContainer.h \
				     VariableContainer.h VariableContainerBase.h VariableDefs.h VariableValueIterator.h VariableValues.h;
do
    cp $PARSERDIR/variable_src/$file $1/$PARSERDIR/variable_src/
done

for file in RuleSymbolVector RuleVariables RuleVariablesConstIterator VariableValues;
do
    cp $PARSERDIR/variable_src/$file.cc $1/$PARSERDIR/variable_src/$file.cpp
done


cp scripts/windows/make-python-bindings.bat $1/libhfst/src/
cp scripts/windows/make-python-package.bat $1/make-python-package.bat
cp scripts/readmes/README_python_win.txt $1/README_python_win.txt
unix2dos $1/README_python_win.txt

for file in libhfst.i docstrings.i hfst_extensions.cc \
hfst_file_extensions.cc hfst_lexc_extensions.cc hfst_lookup_extensions.cc \
hfst_pmatch_extensions.cc hfst_prolog_extensions.cc hfst_regex_extensions.cc \
hfst_rules_extensions.cc hfst_xfst_extensions.cc
do
    cp python/$file $1/libhfst/src/
done

mkdir $1/libhfst/src/hfst
mkdir $1/libhfst/src/hfst/exceptions
mkdir $1/libhfst/src/hfst/sfst_rules
mkdir $1/libhfst/src/hfst/xerox_rules

cp python/hfst/__init__.py $1/libhfst/src/hfst/
cp python/hfst/exceptions/__init__.py $1/libhfst/src/hfst/exceptions/
cp python/hfst/sfst_rules/__init__.py $1/libhfst/src/hfst/sfst_rules/
cp python/hfst/xerox_rules/__init__.py $1/libhfst/src/hfst/xerox_rules/

# todo: python/test/

cp scripts/windows/make-hfst-xfst.bat $1/libhfst/src/
cp scripts/windows/make-hfst-proc.bat $1/libhfst/src/
cp scripts/windows/make-hfst-lexc.bat $1/libhfst/src/
cp scripts/windows/make-hfst-tool.bat $1/libhfst/src/
cp scripts/windows/make-hfst-tools.bat $1/libhfst/src/
cp scripts/windows/make-htwolcpre1.bat $1/libhfst/src/
cp scripts/windows/make-htwolcpre2.bat $1/libhfst/src/
cp scripts/windows/make-htwolcpre3.bat $1/libhfst/src/

for file in test.lexc test.pmatch test.twolc test.xfst \
test_xfst_result.txt test_twolc_result.txt test_pmatch_result.txt test_lexc_result.txt;
do
    cp scripts/windows_tests/$file $1/libhfst/src/
done

cp scripts/windows/test-hfst-tools.bat $1/libhfst/src/
cp scripts/readmes/README_xfst_win.txt $1/libhfst/src/
cp scripts/readmes/README_eight_tools_win.txt $1/libhfst/src/

# copy missing headers and change some headers included
cp scripts/windows/stdint.h $1/back-ends/foma/
cp scripts/windows/inttypes.h $1/back-ends/foma/
# unistd.h is included in some generated files
for file in \
$1/libhfst/src/parsers/pmatch_lex.cpp \
$1/libhfst/src/parsers/xre_lex.cpp \
$1/libhfst/src/parsers/lexc-lexer.cpp \
$1/back-ends/foma/lex.cmatrix.c \
$1/back-ends/foma/lex.yy.c
do
    sed -i 's/#include <unistd.h>/#include <io.h>/' $file
done
sed -i 's/pmatchwrap( )/pmatchwrap(void)/' $1/libhfst/src/parsers/pmatch_lex.cpp
sed -i 's/hlexcwrap( )/hlexcwrap(void)/' $1/libhfst/src/parsers/lexc-lexer.cpp

# copy files for tools

# create subdirectories
mkdir $1/tools
mkdir $1/tools/src
mkdir $1/tools/src/parsers
mkdir $1/tools/src/hfst-proc
mkdir $1/tools/src/inc
mkdir $1/tools/src/hfst-twolc
mkdir $1/tools/src/hfst-twolc/src

# tools/src/parsers
for file in hfst-xfst init_help;
do
    cp tools/src/parsers/$file.cc $1/tools/src/parsers/$file.cpp
done
for file in cmd.h abbrcmd.h;
do
    cp tools/src/parsers/$file $1/tools/src/parsers/
done

# twolc
cp tools/src/hfst-twolc/src/hfst-twolc.cc $1/tools/src/hfst-twolc/src/hfst-twolc.cpp 

# compare, strings2fst and txt2fst are needed for testing hfst-xfst
for file in \
hfst-program-options hfst-commandline hfst-tool-metadata \
hfst-file-to-mem hfst-getopt \
hfst-lexc-compiler hfst-compare hfst-strings2fst hfst-txt2fst hfst-pmatch hfst-pmatch2fst \
hfst-lookup hfst-optimized-lookup hfst-flookup;
do
    cp tools/src/$file.cc $1/tools/src/$file.cpp
done

# hfst-proc
for file in \
hfst-proc formatter lookup-path lookup-state tokenizer transducer applicators alphabet;
do
    cp tools/src/hfst-proc/$file.cc $1/tools/src/hfst-proc/$file.cpp
done

for file in \
hfst-proc.h formatter.h lookup-path.h lookup-state.h tokenizer.h \
transducer.h buffer.h applicators.h alphabet.h;
do
    cp tools/src/hfst-proc/$file $1/tools/src/hfst-proc/
done

for file in \
hfst-commandline.h hfst-program-options.h hfst-tool-metadata.h \
hfst-file-to-mem.h hfst-getopt.h hfst-optimized-lookup.h;
do
    cp tools/src/$file $1/tools/src/
done

for file in \
check-params-binary.h check-params-common.h check-params-unary.h getopt-cases-binary.h \
getopt-cases-common.h getopt-cases-error.h getopt-cases-unary.h globals-binary.h \
globals-common.h globals-unary.h;
do
    cp tools/src/inc/$file $1/tools/src/inc/
done
