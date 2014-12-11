## Process this file with automake to produce Makefile.in

## Copyright (C) 2011 University of Helsinki

## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program. If not, see <http://www.gnu.org/licenses/>.

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

BUILT_SOURCES=$(XRE_BUILT) $(PMATCH_BUILT) $(LEXC_BUILT)

CLEANFILES=$(XRE_BUILT) $(PMATCH_BUILT) $(LEXC_BUILT) \
             xre_parse.hh pmatch_parse.hh lexc-parser.hh

AM_YFLAGS=-d
AM_LFLAGS=--outfile=$(LEX_OUTPUT_ROOT).c

CLEANFILES+=xre_parse.hh  pmatch_parse.hh  lexc-parser.hh
xre_lex.ll: xre_parse.hh
pmatch_lex.ll: pmatch_parse.hh
lexc-lexer.ll: lexc-parser.hh

libhfstparsers_la_SOURCES=$(SFST_SRCS) $(XRE_SRCS) $(PMATCH_SRCS) $(LEXC_SRCS)

AM_CPPFLAGS=-I${top_srcdir}/libhfst/src/parsers -I${top_srcdir}/libhfst/src \
		-I${top_srcdir}/back-ends/foma -I${top_srcdir}/back-ends \
		-Wno-deprecated

if WANT_MINGW
  AM_CPPFLAGS+= -I${top_srcdir}/back-ends/openfstwin/src/include -I${top_srcdir}/back-ends/dlfcn -DWINDOWS
else
  AM_CPPFLAGS+= -I${top_srcdir}/back-ends/openfst/src/include
endif

# headers of parsers
hfstincludedir = $(includedir)/hfst
extincludedir = $(hfstincludedir)/parsers

extinclude_HEADERS = $(XRE_HDRS) $(PMATCH_HDRS) $(LEXC_HDRS)

LIBHFST_PARSER_TSTS=XreCompiler LexcCompiler # PmatchCompiler

check_PROGRAMS=$(LIBHFST_PARSER_TSTS)

XreCompiler_SOURCES=XreCompiler.cc xre_utils.cc xre_parse.yy xre_lex.ll
XreCompiler_CXXFLAGS=-DUNIT_TEST
XreCompiler_LDADD=../libhfst.la
#PmatchCompiler_SOURCES=PmatchCompiler.cc pmatch_utils.cc pmatch_parse.yy pmatch_lex.ll
#PmatchCompiler_CXXFLAGS=-DUNIT_TEST
##PmatchCompiler_LDADD=../libhfst.la
LexcCompiler_SOURCES=LexcCompiler.cc lexc-utils.cc lexc-parser.yy lexc-lexer.ll
LexcCompiler_CXXFLAGS=-DUNIT_TEST -DDEBUG_MAIN
LexcCompiler_LDADD=../libhfst.la

TESTS=$(LIBHFST_PARSER_TSTS)

EXTRA_DIST=xre_parse.hh pmatch_parse.hh lexc-parser.hh $(BUILT_SOURCES)
