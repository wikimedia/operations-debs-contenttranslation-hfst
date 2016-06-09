AM_YFLAGS= -d -o y.tab.c
AM_CXXFLAGS= -Wcast-qual -Wno-deprecated -Wfatal-errors
bin_PROGRAMS=htwolcpre1 htwolcpre2 htwolcpre3 hfst-twolc-system
bin_SCRIPTS=hfst-twolc$(EXEEXT) hfst-twolc-loc$(EXEEXT)
EXTRA_DIST=hfst-twolc.sh hfst-twolc.bat common_globals.h
IO_SRC=$(srcdir)/io_src
STRING_SRC=$(srcdir)/string_src
VARIABLE_SRC=$(srcdir)/variable_src
RULE_SRC=$(srcdir)/rule_src
ALPHABET_SRC=$(srcdir)/alphabet_src
CL_SRC=$(srcdir)/commandline_src
AM_CPPFLAGS = -I${top_srcdir}/libhfst/src
LDADD = $(top_builddir)/libhfst/src/libhfst.la

AM_CPPFLAGS += -I${top_srcdir}/back-ends/foma \
                -I${top_srcdir}/back-ends

if WANT_MINGW
  AM_CPPFLAGS += -I${top_srcdir}/back-ends/openfstwin/src/include \
                 -I${top_srcdir}/back-ends/dlfcn -DWINDOWS
else
  AM_CPPFLAGS += -I${top_srcdir}/back-ends/openfst/src/include
endif

# the preprocessor scripts do not support options per se, so we whitelist
# them here
AM_INSTALLCHECK_STD_OPTIONS_EXEMPT=htwolcpre1 htwolcpre2 htwolcpre3 \
				hfst-twolc$(EXEEXT) hfst-twolc-loc$(EXEEXT) hfst-twolc-system$(EXEEXT)

htwolcpre1_SOURCES=htwolcpre1.yy scanner1.ll HfstTwolcDefs.h \
		   $(CL_SRC)/CommandLine.h $(CL_SRC)/CommandLine.cc \
	           $(IO_SRC)/input_defs.h grammar_defs.h \
                   $(IO_SRC)/InputReader.h $(IO_SRC)/InputReader.cc \
	           $(STRING_SRC)/string_manipulation.cc \
		   $(STRING_SRC)/string_manipulation.h \
		   $(VARIABLE_SRC)/VariableValues.h \
		   $(VARIABLE_SRC)/VariableValues.cc \
		   $(VARIABLE_SRC)/VariableValueIterator.h \
		   $(VARIABLE_SRC)/VariableDefs.h \
		   $(VARIABLE_SRC)/VariableContainerBase.h \
		   $(VARIABLE_SRC)/VariableContainer.h \
		   $(VARIABLE_SRC)/VariableBlockContainer.h \
		   $(VARIABLE_SRC)/VariableBlock.h \
		   $(VARIABLE_SRC)/RuleVariablesConstIterator.cc \
		   $(VARIABLE_SRC)/RuleVariablesConstIterator.h \
		   $(VARIABLE_SRC)/RuleVariables.cc \
		   $(VARIABLE_SRC)/RuleVariables.h \
		   $(VARIABLE_SRC)/RuleSymbolVector.cc \
		   $(VARIABLE_SRC)/RuleSymbolVector.h \
		   $(VARIABLE_SRC)/MatchedConstContainerIterator.h \
		   $(VARIABLE_SRC)/MixedConstContainerIterator.h \
		   $(VARIABLE_SRC)/ConstContainerIterator.h

htwolcpre2_SOURCES=htwolcpre2.yy scanner2.ll HfstTwolcDefs.h \
		   $(CL_SRC)/CommandLine.h $(CL_SRC)/CommandLine.cc \
	           $(IO_SRC)/input_defs.h grammar_defs.h \
                   $(IO_SRC)/InputReader.h $(IO_SRC)/InputReader.cc

htwolcpre3_SOURCES=htwolcpre3.yy scanner3.ll HfstTwolcDefs.h \
		   $(CL_SRC)/CommandLine.h $(CL_SRC)/CommandLine.cc \
	           $(IO_SRC)/input_defs.h grammar_defs.h \
                   $(IO_SRC)/InputReader.cc $(IO_SRC)/InputReader.h \
	           $(STRING_SRC)/string_manipulation.cc \
		   $(STRING_SRC)/string_manipulation.h \
		   $(ALPHABET_SRC)/Alphabet.cc $(ALPHABET_SRC)/Alphabet.h \
		   $(RULE_SRC)/ConflictResolvingLeftArrowRule.cc \
		   $(RULE_SRC)/ConflictResolvingLeftArrowRule.h \
		   $(RULE_SRC)/ConflictResolvingRightArrowRule.cc \
		   $(RULE_SRC)/ConflictResolvingRightArrowRule.h \
		   $(RULE_SRC)/LeftArrowRule.cc \
		   $(RULE_SRC)/LeftArrowRule.h \
		   $(RULE_SRC)/LeftArrowRuleContainer.cc \
		   $(RULE_SRC)/LeftArrowRuleContainer.h \
		   $(RULE_SRC)/LeftRestrictionArrowRule.cc \
		   $(RULE_SRC)/LeftRestrictionArrowRule.h \
		   $(RULE_SRC)/OtherSymbolTransducer.cc \
		   $(RULE_SRC)/OtherSymbolTransducer.h \
		   $(RULE_SRC)/RightArrowRule.cc \
		   $(RULE_SRC)/RightArrowRule.h \
		   $(RULE_SRC)/RightArrowRuleContainer.cc \
		   $(RULE_SRC)/RightArrowRuleContainer.h \
		   $(RULE_SRC)/Rule.cc \
		   $(RULE_SRC)/Rule.h \
		   $(RULE_SRC)/RuleContainer.cc \
		   $(RULE_SRC)/RuleContainer.h \
		   $(RULE_SRC)/TwolCGrammar.cc \
		   $(RULE_SRC)/TwolCGrammar.h

hfst_twolc_system_SOURCES=hfst-twolc-system.cc

# some systems might require all these
BUILT_SOURCES=htwolcpre1.cc htwolcpre2.cc htwolcpre3.cc

if YACC_USE_PARSER_H_EXTENSION
  HEADER=h
else
  HEADER=hh
endif

CLEANFILES=htwolcpre1.$(HEADER) htwolcpre2.$(HEADER) htwolcpre3.$(HEADER) \
	   htwolcpre1.cc htwolcpre2.cc htwolcpre3.cc

hfst-twolc$(EXEEXT): hfst-twolc.sh
	cat $< | sed -e 's|BINDIR|$(bindir)|' > $@
	chmod ogu+rx hfst-twolc$(EXEEXT)

hfst-twolc-loc$(EXEEXT): hfst-twolc.sh
	cat $< | sed -e 's|BINDIR|$(abs_builddir)|' > $@
	chmod ogu+rx hfst-twolc-loc$(EXEEXT)

clean-local:
	-rm -f hfst-twolc$(EXEEXT) hfst-twolc-loc$(EXEEXT) hfst-twolc-system$(EXEEXT)

CLEANFILES+=htwolcpre1.$(HEADER) htwolcpre2.$(HEADER) htwolcpre3.$(HEADER)

scanner1.ll: htwolcpre1.$(HEADER)
scanner2.ll: htwolcpre2.$(HEADER)
scanner3.ll: htwolcpre3.$(HEADER)

HFST_TWOLC_TESTS=string_manipulation InputReader Alphabet \
                 OtherSymbolTransducer Rule LeftArrowRule RightArrowRule \
                 RuleContainer LeftArrowRuleContainer RightArrowRuleContainer \
                 ConflictResolvingLeftArrowRule \
                 ConflictResolvingRightArrowRule TwolCGrammar \
                 LeftRestrictionArrowRule

check_PROGRAMS=$(HFST_TWOLC_TESTS)

string_manipulation_SOURCES=$(STRING_SRC)/string_manipulation.cc
string_manipulation_CXXFLAGS=-DSTRING_MANIPULATION_TEST

InputReader_SOURCES=$(IO_SRC)/InputReader.cc
InputReader_CXXFLAGS=-DINPUT_READER_TEST

Alphabet_SOURCES=$(ALPHABET_SRC)/Alphabet.cc \
                 $(RULE_SRC)/OtherSymbolTransducer.cc
Alphabet_CXXFLAGS=-DTEST_ALPHABET

OtherSymbolTransducer_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc
OtherSymbolTransducer_CXXFLAGS=-DTEST_OTHER_SYMBOL_TRANSDUCER

Rule_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc $(RULE_SRC)/Rule.cc \
             $(STRING_SRC)/string_manipulation.cc
Rule_CXXFLAGS=-DTEST_RULE

LeftArrowRule_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                      $(STRING_SRC)/string_manipulation.cc \
                      $(RULE_SRC)/Rule.cc $(RULE_SRC)/LeftArrowRule.cc	
LeftArrowRule_CXXFLAGS=-DTEST_LEFT_ARROW_RULE

LeftRestrictionArrowRule_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                      $(STRING_SRC)/string_manipulation.cc \
                      $(RULE_SRC)/Rule.cc $(RULE_SRC)/LeftArrowRule.cc \
                      $(RULE_SRC)/LeftRestrictionArrowRule.cc
LeftRestrictionArrowRule_CXXFLAGS=-DTEST_LEFT_RESTRICTION_ARROW_RULE

RightArrowRule_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                       $(STRING_SRC)/string_manipulation.cc \
                       $(RULE_SRC)/Rule.cc $(RULE_SRC)/RightArrowRule.cc
RightArrowRule_CXXFLAGS=-DTEST_RIGHT_ARROW_RULE

RuleContainer_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                      $(RULE_SRC)/Rule.cc $(RULE_SRC)/RuleContainer.cc \
                      $(STRING_SRC)/string_manipulation.cc
RuleContainer_CXXFLAGS=-DTEST_RULE_CONTAINER

LeftArrowRuleContainer_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                               $(RULE_SRC)/Rule.cc \
                               $(RULE_SRC)/RuleContainer.cc \
                               $(STRING_SRC)/string_manipulation.cc \
                               $(RULE_SRC)/ConflictResolvingLeftArrowRule.cc \
                               $(RULE_SRC)/LeftArrowRuleContainer.cc \
                               $(RULE_SRC)/LeftArrowRule.cc

LeftArrowRuleContainer_CXXFLAGS=-DTEST_LEFT_ARROW_RULE_CONTAINER

RightArrowRuleContainer_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                                $(RULE_SRC)/Rule.cc \
                                $(RULE_SRC)/RuleContainer.cc \
                                $(STRING_SRC)/string_manipulation.cc \
                                $(RULE_SRC)/ConflictResolvingRightArrowRule.cc\
                                $(RULE_SRC)/RightArrowRuleContainer.cc \
                                $(RULE_SRC)/RightArrowRule.cc
RightArrowRuleContainer_CXXFLAGS=-DTEST_RIGHT_ARROW_RULE_CONTAINER

ConflictResolvingLeftArrowRule_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                                        $(RULE_SRC)/Rule.cc \
                                        $(RULE_SRC)/RuleContainer.cc \
                                        $(STRING_SRC)/string_manipulation.cc \
                                $(RULE_SRC)/ConflictResolvingLeftArrowRule.cc\
                                        $(RULE_SRC)/LeftArrowRule.cc
ConflictResolvingLeftArrowRule_CXXFLAGS=\
-DTEST_CONFLICT_RESOLVING_LEFT_ARROW_RULE

ConflictResolvingRightArrowRule_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                                        $(RULE_SRC)/Rule.cc \
                                        $(RULE_SRC)/RuleContainer.cc \
                                        $(STRING_SRC)/string_manipulation.cc \
                                $(RULE_SRC)/ConflictResolvingRightArrowRule.cc\
                                        $(RULE_SRC)/RightArrowRule.cc
ConflictResolvingRightArrowRule_CXXFLAGS=\
-DTEST_CONFLICT_RESOLVING_RIGHT_ARROW_RULE

TwolCGrammar_SOURCES=$(RULE_SRC)/OtherSymbolTransducer.cc \
                     $(RULE_SRC)/Rule.cc $(RULE_SRC)/RuleContainer.cc \
                     $(STRING_SRC)/string_manipulation.cc \
                     $(RULE_SRC)/ConflictResolvingLeftArrowRule.cc \
                     $(RULE_SRC)/LeftArrowRule.cc \
                     $(RULE_SRC)/ConflictResolvingRightArrowRule.cc\
                     $(RULE_SRC)/RightArrowRule.cc \
                     $(RULE_SRC)/RightArrowRuleContainer.cc \
                     $(RULE_SRC)/LeftArrowRuleContainer.cc \
                     $(RULE_SRC)/TwolCGrammar.cc \
                     $(RULE_SRC)/LeftRestrictionArrowRule.cc \
                     $(ALPHABET_SRC)/Alphabet.cc
TwolCGrammar_CXXFLAGS=-DTEST_TWOL_C_GRAMMAR

TESTS=$(HFST_TWOLC_TESTS)

EXTRA_DIST += htwolcpre1.$(HEADER) htwolcpre2.$(HEADER) htwolcpre3.$(HEADER) \
	   htwolcpre1.cc htwolcpre2.cc htwolcpre3.cc \
	   scanner1.cc scanner2.cc scanner3.cc
