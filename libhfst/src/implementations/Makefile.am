## Process this file with automake to produce Makefile.in

## Copyright (C) 2010 University of Helsinki

## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS=subdir-objects
noinst_LTLIBRARIES=libhfstimplementations.la

# HFST bridge specific stuff
IMPLEMENTATION_SRCS=HfstTransitionGraph.cc \
		    ConvertTransducerFormat.cc \
		    HfstTropicalTransducerTransitionData.cc \
		    ConvertSfstTransducer.cc ConvertTropicalWeightTransducer.cc \
		    ConvertLogWeightTransducer.cc ConvertFomaTransducer.cc \
	  	    ConvertOlTransducer.cc \
                    compose_intersect/ComposeIntersectRulePair.cc \
                    compose_intersect/ComposeIntersectLexicon.cc \
                    compose_intersect/ComposeIntersectRule.cc \
                    compose_intersect/ComposeIntersectFst.cc \
                    compose_intersect/ComposeIntersectUtilities.cc

AM_CXXFLAGS=-Wno-deprecated -g
AM_CPPFLAGS = -I${top_srcdir}/libhfst/src -I${top_srcdir}/back-ends/foma \
		-I${top_srcdir}/back-ends

if WANT_MINGW
  AM_CPPFLAGS += -I${top_srcdir}/back-ends/openfstwin/src/include \
		-I${top_srcdir}/back-ends/dlfcn -DWINDOWS
else
  AM_CPPFLAGS += -I${top_srcdir}/back-ends/openfst/src/include
endif

# the bridges
if WANT_SFST
MAYBE_SFST=SfstTransducer.cc
endif
if WANT_OPENFST
MAYBE_OPENFST=TropicalWeightTransducer.cc
if WANT_OPENFST_LOG
MAYBE_OPENFST += LogWeightTransducer.cc
endif
endif
if WANT_FOMA
MAYBE_FOMA=FomaTransducer.cc
endif
# Add here your transducer library
#if WANT_MY_TRANSDUCER_LIBRARY
#MAYBE_MY_TRANSDUCER_LIBRARY=MyTransducerLibraryTransducer.cc
#endif
if WANT_HFSTOL
MAYBE_HFSTOL=HfstOlTransducer.cc
endif

BRIDGE_SRCS=$(MAYBE_SFST) $(MAYBE_OPENFST) $(MAYBE_FOMA) $(MAYBE_HFSTOL) # $(MAYBE_MY_TRANSDUCER_LIBRARY)

if WANT_HFSTOL
HFST_OL_SRCS=\
optimized-lookup/transducer.cc optimized-lookup/convert.cc \
	optimized-lookup/ospell.cc optimized-lookup/pmatch.cc \
	optimized-lookup/find_epsilon_loops.cc
endif

libhfstimplementations_la_SOURCES=$(IMPLEMENTATION_SRCS) $(BRIDGE_SRCS) \
								  $(SFST_SRCS) $(HFST_OL_SRCS)


# headers of implementation bridge to reveal to public
hfstincludedir = $(includedir)/hfst
implincludedir = $(hfstincludedir)/implementations
compisectincludedir = $(implincludedir)/compose_intersect

implinclude_HEADERS = \
		ConvertTransducerFormat.h \
		FomaTransducer.h \
		LogWeightTransducer.h \
		SfstTransducer.h TropicalWeightTransducer.h \
		HfstOlTransducer.h HfstTransitionGraph.h HfstTransition.h \
		HfstTropicalTransducerTransitionData.h \
		HfstFastTransitionData.h \
		compose_intersect/ComposeIntersectRulePair.h \
		compose_intersect/ComposeIntersectLexicon.h \
		compose_intersect/ComposeIntersectRule.h \
		compose_intersect/ComposeIntersectFst.h \
		compose_intersect/ComposeIntersectUtilities.h

compisectinclude_HEADERS=\
		compose_intersect/ComposeIntersectRulePair.h \
		compose_intersect/ComposeIntersectLexicon.h \
		compose_intersect/ComposeIntersectRule.h \
		compose_intersect/ComposeIntersectFst.h \
		compose_intersect/ComposeIntersectUtilities.h


### Add here your library ###
#		MyTransducerLibraryTransducer.h


if WANT_HFSTOL
hfstolincludedir = $(implincludedir)/optimized-lookup
hfstolinclude_HEADERS = \
		optimized-lookup/transducer.h \
		optimized-lookup/convert.h \
		optimized-lookup/pmatch.h
endif

if WANT_FOMA
FOMA_TSTS=FomaTransducer
endif
if WANT_HFSTOL
HFSTOL_TSTS=HfstOlTransducer optimized-lookup/transducer optimized-lookup/convert
endif
if WANT_OPENFST
OFST_TSTS=TropicalWeightTransducer
if WANT_OPENFST_LOG
OFST_TSTS += LogWeightTransducer
endif
endif
if WANT_SFST
SFST_TSTS=SfstTransducer
endif

LIBHFST_TSTS=HfstTransitionGraph ConvertTransducerFormat \
		ConvertSfstTransducer ConvertTropicalWeightTransducer \
		ConvertLogWeightTransducer ConvertFomaTransducer \
		ConvertOlTransducer \
		compose_intersect/ComposeIntersectRulePair \
		compose_intersect/ComposeIntersectLexicon \
		compose_intersect/ComposeIntersectRule \
		compose_intersect/ComposeIntersectFst \
		compose_intersect/ComposeIntersectUtilities
#		HfstConstantTransducer

check_PROGRAMS=$(FOMA_TSTS) $(HFSTOL_TSTS) $(OFST_TSTS) $(SFST_TSTS) $(LIBHFST_TSTS)

FomaTransducer_SOURCES=FomaTransducer.cc
FomaTransducer_CXXFLAGS=-DMAIN_TEST
FomaTransducer_LDADD=../libhfst.la
HfstOlTransducer_SOURCES=HfstOlTransducer.cc
HfstOlTransducer_CXXFLAGS=-DMAIN_TEST
HfstOlTransducer_LDADD=../libhfst.la
LogWeightTransducer_SOURCES=LogWeightTransducer.cc
LogWeightTransducer_CXXFLAGS=-DMAIN_TEST
LogWeightTransducer_LDADD=../libhfst.la
TropicalWeightTransducer_SOURCES=TropicalWeightTransducer.cc
TropicalWeightTransducer_CXXFLAGS=-DMAIN_TEST
TropicalWeightTransducer_LDADD=../libhfst.la
SfstTransducer_SOURCES=SfstTransducer.cc
SfstTransducer_CXXFLAGS=-DMAIN_TEST
SfstTransducer_LDADD=../libhfst.la
HfstTransitionGraph_SOURCES=HfstTransitionGraph.cc
HfstTransitionGraph_CXXFLAGS=-DMAIN_TEST
HfstTransitionGraph_LDADD=../libhfst.la
ConvertTransducerFormat_SOURCES=ConvertTransducerFormat.cc
ConvertTransducerFormat_CXXFLAGS=-DMAIN_TEST
ConvertTransducerFormat_LDADD=../libhfst.la
ConvertSfstTransducer_SOURCES=ConvertSfstTransducer.cc
ConvertSfstTransducer_CXXFLAGS=-DMAIN_TEST
ConvertSfstTransducer_LDADD=../libhfst.la
ConvertTropicalWeightTransducer_SOURCES=ConvertTropicalWeightTransducer.cc
ConvertTropicalWeightTransducer_CXXFLAGS=-DMAIN_TEST
ConvertTropicalWeightTransducer_LDADD=../libhfst.la
ConvertLogWeightTransducer_SOURCES=ConvertLogWeightTransducer.cc
ConvertLogWeightTransducer_CXXFLAGS=-DMAIN_TEST
ConvertLogWeightTransducer_LDADD=../libhfst.la
ConvertFomaTransducer_SOURCES=ConvertFomaTransducer.cc
ConvertFomaTransducer_CXXFLAGS=-DMAIN_TEST
ConvertFomaTransducer_LDADD=../libhfst.la
ConvertOlTransducer_SOURCES=ConvertOlTransducer.cc
ConvertOlTransducer_CXXFLAGS=-DMAIN_TEST
ConvertOlTransducer_LDADD=../libhfst.la
optimized_lookup_transducer_SOURCES=optimized-lookup/transducer.cc \
	optimized-lookup/ospell.cc optimized-lookup/pmatch.cc optimized-lookup/find_epsilon_loops.cc
optimized_lookup_transducer_CXXFLAGS=-DMAIN_TEST
optimized_lookup_transducer_LDADD=../libhfst.la
optimized_lookup_convert_SOURCES=optimized-lookup/convert.cc
optimized_lookup_convert_CXXFLAGS=-DMAIN_TEST
optimized_lookup_convert_LDADD=../libhfst.la
compose_intersect_ComposeIntersectRulePair_SOURCES=compose_intersect/ComposeIntersectRulePair.cc
compose_intersect_ComposeIntersectRulePair_CXXFLAGS=-DMAIN_TEST
compose_intersect_ComposeIntersectRulePair_LDADD=../libhfst.la
compose_intersect_ComposeIntersectLexicon_SOURCES=compose_intersect/ComposeIntersectLexicon.cc
compose_intersect_ComposeIntersectLexicon_CXXFLAGS=-DMAIN_TEST
compose_intersect_ComposeIntersectLexicon_LDADD=../libhfst.la
compose_intersect_ComposeIntersectRule_SOURCES=compose_intersect/ComposeIntersectRule.cc
compose_intersect_ComposeIntersectRule_CXXFLAGS=-DMAIN_TEST
compose_intersect_ComposeIntersectRule_LDADD=../libhfst.la
compose_intersect_ComposeIntersectFst_SOURCES=compose_intersect/ComposeIntersectFst.cc
compose_intersect_ComposeIntersectFst_CXXFLAGS=-DMAIN_TEST
compose_intersect_ComposeIntersectFst_LDADD=../libhfst.la
compose_intersect_ComposeIntersectUtilities_SOURCES=compose_intersect/ComposeIntersectUtilities.cc
compose_intersect_ComposeIntersectUtilities_CXXFLAGS=-DMAIN_TEST
compose_intersect_ComposeIntersectUtilities_LDADD=../libhfst.la
#HfstConstantTransducer_SOURCES=HfstConstantTransducer.cc
#HfstConstantTransducer_CXXFLAGS=-DMAIN_TEST
#HfstConstantTransducer_LDADD=../libhfst.la

TESTS=$(FOMA_TSTS) $(HFSTOL_TSTS) $(OFST_TSTS) $(SFST_TSTS) $(LIBHFST_TSTS)