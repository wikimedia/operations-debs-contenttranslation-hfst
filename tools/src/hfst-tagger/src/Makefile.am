AM_CXXFLAGS= -O3 -g -Wall -Wextra -Wcast-qual -Wno-deprecated -Wfatal-errors -Wno-sign-compare\
             -I$(top_builddir)/tools/src/inc -I$(top_builddir)/tools/src 

bin_PROGRAMS=hfst-build-tagger$(EXEEXT) hfst-open-input-file-for-tagger$(EXEEXT) hfst-tag \
hfst-reweight-tagger$(EXEEXT) hfst-train-tagger-system$(EXEEXT)
bin_SCRIPTS=hfst_tagger_compute_data_statistics.py hfst-train-tagger$(EXEEXT) \
hfst-train-tagger-loc$(EXEEXT)
EXTRA_DIST=hfst-train-tagger.sh hfst-train-tagger.bat
BUILD_MODEL_SRC=$(srcdir)/build_model_src
USE_MODEL_SRC=$(srcdir)/use_model_src
AM_CPPFLAGS=-I${top_srcdir}/libhfst/src -Wno-sign-compare -Wno-unused-parameter
LDADD = $(top_builddir)/libhfst/src/libhfst.la

AM_CPPFLAGS += -I${top_srcdir}/back-ends/foma \
		-I${top_srcdir}/back-ends

if WANT_MINGW
  AM_CPPFLAGS += -I${top_srcdir}/back-ends/openfstwin/src/include \
		-I${top_srcdir}/back-ends/dlfcn -DWINDOWS
else
  AM_CPPFLAGS += -I${top_srcdir}/back-ends/openfst/src/include
endif

python_PYTHON=$(BUILD_MODEL_SRC)/tagger_aux.py \
              hfst_tagger_compute_data_statistics.py

HFST_COMMON_SRC=$(top_srcdir)/tools/src/hfst-program-options.cc \
                $(top_srcdir)/tools/src/hfst-commandline.cc \
	        $(top_srcdir)/tools/src/hfst-tool-metadata.cc

AM_INSTALLCHECK_STD_OPTIONS_EXEMPT=hfst_tagger_compute_data_statistics.py \
                                   hfst-build-tagger \
                                   hfst-open-input-file-for-tagger \
                                   hfst-train-tagger hfst-train-tagger-loc \
				   hfst-train-tagger-system

hfst_build_tagger_SOURCES=hfst-build-tagger.cc \
			  $(BUILD_MODEL_SRC)/FstBuilder.cc \
			  $(BUILD_MODEL_SRC)/LexicalModelBuilder.cc \
			  $(BUILD_MODEL_SRC)/ModelBuilder.cc \
			  $(BUILD_MODEL_SRC)/SequenceModelBuilder.cc \
			  $(BUILD_MODEL_SRC)/TaggerBuilder.cc \
			  $(BUILD_MODEL_SRC)/WeightedStringVectorCollection.cc\
			  $(BUILD_MODEL_SRC)/string_handling.cc \
			  $(HFST_COMMON_SRC)

hfst_tag_SOURCES=hfst-tag.cc \
	         $(USE_MODEL_SRC)/DelayedSequenceModelComponent.cc \
                 $(USE_MODEL_SRC)/AcyclicAutomaton.cc \
	         $(USE_MODEL_SRC)/NewLexicalModel.cc \
                 $(USE_MODEL_SRC)/SentenceTagger.cc \
                 $(USE_MODEL_SRC)/SentenceTransducer.cc \
	         $(USE_MODEL_SRC)/SequenceModelComponent.cc \
	         $(USE_MODEL_SRC)/SequenceModelComponentPair.cc \
                 $(USE_MODEL_SRC)/SequenceTagger.cc \
		 $(HFST_COMMON_SRC)

hfst_reweight_tagger_SOURCES=hfst-reweight-tagger.cc \
		             $(HFST_COMMON_SRC)

hfst_train_tagger_system_SOURCES=hfst-train-tagger-system.cc

hfst-train-tagger$(EXEEXT): hfst-train-tagger.sh
	cat $< | sed -e 's|BINDIR|$(bindir)|' > $@
	chmod ogu+rx $@

hfst-train-tagger-loc$(EXEEXT): hfst-train-tagger.sh
	cat $< | sed -e 's|BINDIR|$(PWD)|' > $@
	chmod ogu+rx $@

clean-local:
	-rm -f hfst-train-tagger$(EXEEXT) hfst-train-tagger-loc$(EXEEXT) hfst-train-tagger-system$(EXEEXT)

unit_test_aux.o:$(srcdir)/unit_test_aux.cc

hfst_open_input_file_for_tagger_SOURCES=hfst-open-input-file-for-tagger.cc \
			  $(HFST_COMMON_SRC)

check_PROGRAMS=FstBuilder LexicalModelBuilder ModelBuilder \
               SequenceModelBuilder TaggerBuilder \
               WeightedStringVectorCollection \
               string_handling DelayedSequenceModelComponent \
               AcyclicAutomaton NewLexicalModel SentenceTagger \
               SentenceTransducer SequenceModelComponent \
               SequenceModelComponentPair SequenceTagger

FstBuilder_SOURCES=$(BUILD_MODEL_SRC)/FstBuilder.cc
FstBuilder_LDADD=string_handling.o FstBuilder.o \
                 $(top_srcdir)/libhfst/src/libhfst.la
FstBuilder_CXXFLAGS=-DMAIN_TEST

LexicalModelBuilder_SOURCES=$(BUILD_MODEL_SRC)/LexicalModelBuilder.cc
LexicalModelBuilder_LDADD=string_handling.o FstBuilder.o ModelBuilder.o \
			  WeightedStringVectorCollection.o \
	                  LexicalModelBuilder.o \
                          $(top_srcdir)/libhfst/src/libhfst.la
LexicalModelBuilder_CXXFLAGS=-DMAIN_TEST

SequenceModelBuilder_SOURCES=$(BUILD_MODEL_SRC)/SequenceModelBuilder.cc
SequenceModelBuilder_LDADD=string_handling.o FstBuilder.o ModelBuilder.o \
			  WeightedStringVectorCollection.o \
	                  SequenceModelBuilder.o \
                          $(top_srcdir)/libhfst/src/libhfst.la
SequenceModelBuilder_CXXFLAGS=-DMAIN_TEST

ModelBuilder_SOURCES=$(BUILD_MODEL_SRC)/ModelBuilder.cc
ModelBuilder_LDADD=string_handling.o FstBuilder.o ModelBuilder.o \
		   WeightedStringVectorCollection.o \
                   $(top_srcdir)/libhfst/src/libhfst.la
ModelBuilder_CXXFLAGS=-DMAIN_TEST

WeightedStringVectorCollection_SOURCES=\
	$(BUILD_MODEL_SRC)/WeightedStringVectorCollection.cc
WeightedStringVectorCollection_LDADD=string_handling.o \
	WeightedStringVectorCollection.o \
	$(top_srcdir)/libhfst/src/libhfst.la
WeightedStringVectorCollection_CXXFLAGS=-DMAIN_TEST

TaggerBuilder_SOURCES=$(BUILD_MODEL_SRC)/TaggerBuilder.cc
TaggerBuilder_LDADD=string_handling.o TaggerBuilder.o \
	LexicalModelBuilder.o SequenceModelBuilder.o \
	WeightedStringVectorCollection.o ModelBuilder.o FstBuilder.o \
	$(top_srcdir)/libhfst/src/libhfst.la
TaggerBuilder_CXXFLAGS=-DMAIN_TEST

string_handling_SOURCES=$(BUILD_MODEL_SRC)/string_handling.cc

string_handling_LDADD=string_handling.o $(top_srcdir)/libhfst/src/libhfst.la \
		      unit_test_aux.o
string_handling_CXXFLAGS=-DMAIN_TEST

AcyclicAutomaton_SOURCES=$(USE_MODEL_SRC)/AcyclicAutomaton.cc

AcyclicAutomaton_LDADD=AcyclicAutomaton.o $(top_srcdir)/libhfst/src/libhfst.la\
		       SequenceModelComponent.o unit_test_aux.o
AcyclicAutomaton_CXXFLAGS=-DMAIN_TEST

DelayedSequenceModelComponent_SOURCES= \
                       $(USE_MODEL_SRC)/DelayedSequenceModelComponent.cc

DelayedSequenceModelComponent_LDADD=DelayedSequenceModelComponent.o \
                       $(top_srcdir)/libhfst/src/libhfst.la \
		       SequenceModelComponent.o unit_test_aux.o
DelayedSequenceModelComponent_CXXFLAGS=-DMAIN_TEST

NewLexicalModel_SOURCES=$(USE_MODEL_SRC)/NewLexicalModel.cc

NewLexicalModel_LDADD=NewLexicalModel.o $(top_srcdir)/libhfst/src/libhfst.la \
		      unit_test_aux.o
NewLexicalModel_CXXFLAGS=-DMAIN_TEST

SentenceTagger_SOURCES=$(USE_MODEL_SRC)/SentenceTagger.cc

SentenceTagger_LDADD=SentenceTagger.o $(top_srcdir)/libhfst/src/libhfst.la \
		     DelayedSequenceModelComponent.o SequenceModelComponent.o \
		     SentenceTransducer.o NewLexicalModel.o \
                     SequenceModelComponentPair.o unit_test_aux.o \
                     SequenceTagger.o AcyclicAutomaton.o

SentenceTagger_CXXFLAGS=-DMAIN_TEST

SentenceTransducer_SOURCES=$(USE_MODEL_SRC)/SentenceTransducer.cc

SentenceTransducer_LDADD=SentenceTransducer.o \
                       $(top_srcdir)/libhfst/src/libhfst.la \
		       SequenceModelComponent.o unit_test_aux.o
SentenceTransducer_CXXFLAGS=-DMAIN_TEST

SequenceModelComponent_SOURCES=$(USE_MODEL_SRC)/SequenceModelComponent.cc\
			       unit_test_aux.cc
SequenceModelComponent_LDADD=SequenceModelComponent.o \
                             $(top_srcdir)/libhfst/src/libhfst.la
SequenceModelComponent_CXXFLAGS=-DMAIN_TEST

SequenceModelComponentPair_SOURCES= \
                                $(USE_MODEL_SRC)/SequenceModelComponentPair.cc

SequenceModelComponentPair_LDADD=SequenceModelComponentPair.o \
                                 $(top_srcdir)/libhfst/src/libhfst.la \
                                 DelayedSequenceModelComponent.o \
				 SequenceModelComponent.o unit_test_aux.o
SequenceModelComponentPair_CXXFLAGS=-DMAIN_TEST

SequenceTagger_SOURCES=$(USE_MODEL_SRC)/SequenceTagger.cc

SequenceTagger_LDADD=SequenceTagger.o $(top_srcdir)/libhfst/src/libhfst.la\
		     SequenceModelComponent.o SentenceTransducer.o \
                     unit_test_aux.o AcyclicAutomaton.o \
                     SequenceModelComponentPair.o \
		     DelayedSequenceModelComponent.o
SequenceTagger_CXXFLAGS=-DMAIN_TEST

TESTS=$(check_PROGRAMS)

EXTRA_DIST +=$(BUILD_MODEL_SRC)/FstBuilder.h \
$(BUILD_MODEL_SRC)/LexicalModelBuilder.h \
$(BUILD_MODEL_SRC)/ModelBuilder.h \
$(BUILD_MODEL_SRC)/SequenceModelBuilder.h \
$(BUILD_MODEL_SRC)/string_handling.h \
$(BUILD_MODEL_SRC)/TaggerBuilder.h \
$(BUILD_MODEL_SRC)/WeightedStringVectorCollection.h \
unit_test_aux.h \
$(USE_MODEL_SRC)/AcyclicAutomaton.h \
$(USE_MODEL_SRC)/DataTypes.h \
$(USE_MODEL_SRC)/DelayedSequenceModelComponent.h \
$(USE_MODEL_SRC)/NewLexicalModel.h \
$(USE_MODEL_SRC)/SentenceTagger.h \
$(USE_MODEL_SRC)/SentenceTransducer.h \
$(USE_MODEL_SRC)/SequenceModelComponent.h \
$(USE_MODEL_SRC)/SequenceModelComponentPair.h \
$(USE_MODEL_SRC)/SequenceTagger.h
