## Process this file with automake to produce Makefile.in

# Copyright (c) 2016 University of Helsinki
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
# See the file COPYING included with this distribution for more
# information.

noinst_LTLIBRARIES=libhfstparsers.la

XRE_SRCS=xre_lex.ll xre_parse.yy xre_utils.cc XreCompiler.cc
XRE_HDRS=XreCompiler.h xre_utils.h
XRE_BUILT=xre_parse.cc xre_lex.cc

PMATCH_SRCS=pmatch_lex.ll pmatch_parse.yy pmatch_utils.cc PmatchCompiler.cc
PMATCH_HDRS=PmatchCompiler.h pmatch_utils.h
PMATCH_BUILT=pmatch_parse.cc pmatch_lex.cc

LEXC_SRCS=lexc-lexer.ll lexc-parser.yy lexc-utils.cc LexcCompiler.cc
LEXC_HDRS=LexcCompiler.h lexc-utils.h
LEXC_BUILT=lexc-parser.cc lexc-lexer.cc

SFST_SRCS=sfst-scanner.ll sfst-compiler.yy SfstCompiler.cc SfstUtf8.cc SfstBasic.cc SfstAlphabet.cc
SFST_HDRS=SfstCompiler.h SfstUtf8.h SfstBasic.h SfstAlphabet.h
SFST_BUILT=sfst-compiler.cc sfst-scanner.cc

# TODO: hfst-string-conversions.cc
XFST_SRCS=xfst-lexer.ll xfst-parser.yy xfst-utils.cc XfstCompiler.cc xfst_help_message.cc
XFST_HDRS=XfstCompiler.h xfst-utils.h xfst_help_message.h
XFST_BUILT=xfst-parser.cc xfst-lexer.cc

IO_SRC=$(srcdir)/io_src
STRING_SRC=$(srcdir)/string_src
VARIABLE_SRC=$(srcdir)/variable_src
RULE_SRC=$(srcdir)/rule_src
ALPHABET_SRC=$(srcdir)/alphabet_src
CL_SRC=$(srcdir)/commandline_src

TWOLC_SRCS=htwolcpre1-parser.yy htwolcpre1-lexer.ll htwolcpre2-parser.yy htwolcpre2-lexer.ll htwolcpre3-parser.yy htwolcpre3-lexer.ll \
TwolcCompiler.cc \
$(CL_SRC)/CommandLine.cc \
$(ALPHABET_SRC)/Alphabet.cc \
$(IO_SRC)/InputReader.cc \
$(RULE_SRC)/ConflictResolvingLeftArrowRule.cc \
$(RULE_SRC)/ConflictResolvingRightArrowRule.cc \
$(RULE_SRC)/LeftArrowRule.cc \
$(RULE_SRC)/LeftArrowRuleContainer.cc \
$(RULE_SRC)/LeftRestrictionArrowRule.cc \
$(RULE_SRC)/OtherSymbolTransducer.cc \
$(RULE_SRC)/RightArrowRule.cc \
$(RULE_SRC)/RightArrowRuleContainer.cc \
$(RULE_SRC)/Rule.cc \
$(RULE_SRC)/RuleContainer.cc \
$(RULE_SRC)/TwolCGrammar.cc \
$(STRING_SRC)/string_manipulation.cc \
$(VARIABLE_SRC)/RuleSymbolVector.cc \
$(VARIABLE_SRC)/RuleVariables.cc \
$(VARIABLE_SRC)/RuleVariablesConstIterator.cc \
$(VARIABLE_SRC)/VariableValues.cc

# remove: $(IO_SRC)/input_defs.h
TWOLC_HDRS=TwolcCompiler.h \
$(ALPHABET_SRC)/Alphabet.h \
$(CL_SRC)/CommandLine.h \
grammar_defs.h \
HfstTwolcDefs.h \
$(IO_SRC)/InputReader.h \
$(RULE_SRC)/ConflictResolvingLeftArrowRule.h \
$(RULE_SRC)/ConflictResolvingRightArrowRule.h \
$(RULE_SRC)/LeftArrowRuleContainer.h \
$(RULE_SRC)/LeftArrowRule.h \
$(RULE_SRC)/LeftRestrictionArrowRule.h \
$(RULE_SRC)/OtherSymbolTransducer.h \
$(RULE_SRC)/RightArrowRuleContainer.h \
$(RULE_SRC)/RightArrowRule.h \
$(RULE_SRC)/RuleContainer.h \
$(RULE_SRC)/Rule.h \
$(RULE_SRC)/TwolCGrammar.h \
$(STRING_SRC)/string_manipulation.h \
$(VARIABLE_SRC)/ConstContainerIterator.h \
$(VARIABLE_SRC)/MatchedConstContainerIterator.h \
$(VARIABLE_SRC)/MixedConstContainerIterator.h \
$(VARIABLE_SRC)/RuleSymbolVector.h \
$(VARIABLE_SRC)/RuleVariablesConstIterator.h \
$(VARIABLE_SRC)/RuleVariables.h \
$(VARIABLE_SRC)/VariableBlockContainer.h \
$(VARIABLE_SRC)/VariableBlock.h \
$(VARIABLE_SRC)/VariableContainerBase.h \
$(VARIABLE_SRC)/VariableContainer.h \
$(VARIABLE_SRC)/VariableDefs.h \
$(VARIABLE_SRC)/VariableValueIterator.h \
$(VARIABLE_SRC)/VariableValues.h

TWOLC_BUILT=htwolcpre1-parser.cc htwolcpre1-lexer.cc htwolcpre2-parser.cc htwolcpre2-lexer.cc htwolcpre3-parser.cc htwolcpre3-lexer.cc

BUILT_SOURCES=$(XRE_BUILT) $(PMATCH_BUILT) $(LEXC_BUILT) $(XFST_BUILT) $(SFST_BUILT) $(TWOLC_BUILT)

# If automake is < 1.12, *.h extension is used instead and build will fail,
# unless pre-yacc-generated *.cc files are used and *.yy source files are not modified.
HEADER=hh

CLEANFILES=$(XRE_BUILT) $(PMATCH_BUILT) $(LEXC_BUILT) $(XFST_BUILT) $(SFST_BUILT) $(TWOLC_BUILT) \
	xre_parse.$(HEADER) pmatch_parse.$(HEADER) lexc-parser.$(HEADER) xfst-parser.$(HEADER) sfst-compiler.$(HEADER) \
	htwolcpre1-parser.$(HEADER) htwolcpre2-parser.$(HEADER) htwolcpre3-parser.$(HEADER)

AM_YFLAGS=-d
AM_LFLAGS=--outfile=$(LEX_OUTPUT_ROOT).c

xre_lex.ll: xre_parse.$(HEADER)
pmatch_lex.ll: pmatch_parse.$(HEADER)
lexc-lexer.ll: lexc-parser.$(HEADER)
xfst-lexer.ll: xfst-parser.$(HEADER)
sfst-scanner.ll: sfst-compiler.$(HEADER)
htwolc1pre-lexer.ll: htwolcpre1-parser.$(HEADER)
htwolc2pre-lexer.ll: htwolcpre2-parser.$(HEADER)
htwolc3pre-lexer.ll: htwolcpre3-parser.$(HEADER)

libhfstparsers_la_SOURCES=$(XRE_SRCS) $(PMATCH_SRCS) $(LEXC_SRCS) $(XFST_SRCS) $(SFST_SRCS) $(TWOLC_SRCS)

AM_CPPFLAGS=-I${top_srcdir}/libhfst/src/parsers -I${top_srcdir}/libhfst/src \
		-Wno-deprecated

if WANT_MINGW
  AM_CPPFLAGS+= -I${top_srcdir}/back-ends/dlfcn -DWINDOWS
endif

# headers of parsers
hfstincludedir = $(includedir)/hfst
extincludedir = $(hfstincludedir)/parsers

extinclude_HEADERS = $(XRE_HDRS) $(PMATCH_HDRS) $(LEXC_HDRS) $(XFST_HDRS) $(SFST_HDRS) $(TWOLC_HDRS)

LIBHFST_PARSER_TSTS=XreCompiler LexcCompiler # PmatchCompiler

HFST_TWOLC_TESTS=string_manipulation InputReader Alphabet \
                 OtherSymbolTransducer Rule LeftArrowRule RightArrowRule \
                 RuleContainer LeftArrowRuleContainer RightArrowRuleContainer \
                 ConflictResolvingLeftArrowRule \
                 ConflictResolvingRightArrowRule TwolCGrammar \
                 LeftRestrictionArrowRule

check_PROGRAMS=$(LIBHFST_PARSER_TSTS) $(HFST_TWOLC_TESTS)

XreCompiler_SOURCES=XreCompiler.cc xre_utils.cc xre_parse.yy xre_lex.ll
XreCompiler_CXXFLAGS=-DUNIT_TEST
XreCompiler_LDADD=../libhfst.la
#PmatchCompiler_SOURCES=PmatchCompiler.cc pmatch_utils.cc pmatch_parse.yy pmatch_lex.ll
#PmatchCompiler_CXXFLAGS=-DUNIT_TEST
##PmatchCompiler_LDADD=../libhfst.la
LexcCompiler_SOURCES=LexcCompiler.cc lexc-utils.cc lexc-parser.yy lexc-lexer.ll
LexcCompiler_CXXFLAGS=-DUNIT_TEST -DDEBUG_MAIN
LexcCompiler_LDADD=../libhfst.la

string_manipulation_SOURCES=$(STRING_SRC)/string_manipulation.cc
string_manipulation_CXXFLAGS=-DSTRING_MANIPULATION_TEST -Wno-deprecated
string_manipulation_LDADD=../libhfst.la

InputReader_SOURCES=$(IO_SRC)/InputReader.cc
InputReader_CXXFLAGS=-DINPUT_READER_TEST -Wno-deprecated
InputReader_LDADD=../libhfst.la

Alphabet_SOURCES=$(ALPHABET_SRC)/Alphabet.cc
Alphabet_CXXFLAGS=-DTEST_ALPHABET -Wno-deprecated
Alphabet_LDADD=../libhfst.la

OtherSymbolTransducer_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc
OtherSymbolTransducer_CXXFLAGS=-DTEST_OTHER_SYMBOL_TRANSDUCER -Wno-deprecated
OtherSymbolTransducer_LDADD=../libhfst.la

Rule_SOURCES=$(RULE_SRC)/Rule.cc
Rule_CXXFLAGS=-DTEST_RULE -Wno-deprecated
Rule_LDADD=../libhfst.la

LeftArrowRule_SOURCES=$(RULE_SRC)/LeftArrowRule.cc
LeftArrowRule_CXXFLAGS=-DTEST_LEFT_ARROW_RULE -Wno-deprecated
LeftArrowRule_LDADD=../libhfst.la

LeftRestrictionArrowRule_SOURCES=$(RULE_SRC)/LeftRestrictionArrowRule.cc
LeftRestrictionArrowRule_CXXFLAGS=-DTEST_LEFT_RESTRICTION_ARROW_RULE -Wno-deprecated
LeftRestrictionArrowRule_LDADD=../libhfst.la

RightArrowRule_SOURCES=$(RULE_SRC)/RightArrowRule.cc
RightArrowRule_CXXFLAGS=-DTEST_RIGHT_ARROW_RULE -Wno-deprecated
RightArrowRule_LDADD=../libhfst.la

RuleContainer_SOURCES=$(RULE_SRC)/RuleContainer.cc
RuleContainer_CXXFLAGS=-DTEST_RULE_CONTAINER -Wno-deprecated
RuleContainer_LDADD=../libhfst.la

LeftArrowRuleContainer_SOURCES=$(RULE_SRC)/LeftArrowRuleContainer.cc
LeftArrowRuleContainer_CXXFLAGS=-DTEST_LEFT_ARROW_RULE_CONTAINER -Wno-deprecated
LeftArrowRuleContainer_LDADD=../libhfst.la

RightArrowRuleContainer_SOURCES=$(RULE_SRC)/RightArrowRuleContainer.cc
RightArrowRuleContainer_CXXFLAGS=-DTEST_RIGHT_ARROW_RULE_CONTAINER -Wno-deprecated
RightArrowRuleContainer_LDADD=../libhfst.la

ConflictResolvingLeftArrowRule_SOURCES=$(RULE_SRC)/ConflictResolvingLeftArrowRule.cc
ConflictResolvingLeftArrowRule_CXXFLAGS=-DTEST_CONFLICT_RESOLVING_LEFT_ARROW_RULE -Wno-deprecated
ConflictResolvingLeftArrowRule_LDADD=../libhfst.la

ConflictResolvingRightArrowRule_SOURCES=$(RULE_SRC)/ConflictResolvingRightArrowRule.cc
ConflictResolvingRightArrowRule_CXXFLAGS=-DTEST_CONFLICT_RESOLVING_RIGHT_ARROW_RULE -Wno-deprecated
ConflictResolvingRightArrowRule_LDADD=../libhfst.la

TwolCGrammar_SOURCES=$(RULE_SRC)/TwolCGrammar.cc
TwolCGrammar_CXXFLAGS=-DTEST_TWOL_C_GRAMMAR -Wno-deprecated
TwolCGrammar_LDADD=../libhfst.la

TESTS=$(LIBHFST_PARSER_TSTS) $(HFST_TWOLC_TESTS)

EXTRA_DIST=xre_parse.$(HEADER) pmatch_parse.$(HEADER) lexc-parser.$(HEADER) xfst-parser.$(HEADER) sfst-compiler.$(HEADER) \
	   htwolcpre1-parser.$(HEADER) htwolcpre2-parser.$(HEADER) htwolcpre3-parser.$(HEADER) $(BUILT_SOURCES) common_globals.h


# some systems might require all these
# BUILT_SOURCES=htwolcpre1-parser.cc htwolcpre2-parser.cc htwolcpre3-parser.cc

#htwolcpre1-parser.$(HEADER): htwolcpre1-parser.yy
#htwolcpre2-parser.$(HEADER): htwolcpre2-parser.yy
#htwolcpre3-parser.$(HEADER): htwolcpre3-parser.yy

#htwolcpre1-lexer.ll: htwolcpre1-parser.$(HEADER)
#htwolcpre2-lexer.ll: htwolcpre2-parser.$(HEADER)
#htwolcpre3-lexer.ll: htwolcpre3-parser.$(HEADER)

