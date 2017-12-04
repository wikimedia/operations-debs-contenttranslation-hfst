## Process this file with automake to produce Makefile.in

## Copyright (C) 2013 University of Helsinki

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

SUBDIRS=test

hfst_xfst_SOURCES = hfst-xfst.cc $(HFST_COMMON_SRC)

AM_CPPFLAGS = -I${top_srcdir}/libhfst/src -I${top_srcdir}/libhfst/src/parsers -I${top_srcdir}/tools/src $(GLIB_CPPFLAGS) -Wno-deprecated

if WANT_XFST
MAYBE_XFST=hfst-xfst
endif

HFST_COMMON_SRC=../hfst-program-options.cc ../hfst-commandline.cc ../hfst-tool-metadata.cc ../hfst-file-to-mem.cc

bin_PROGRAMS=$(MAYBE_XFST)

if WANT_READLINE
  hfst_xfst_LDADD = $(top_builddir)/libhfst/src/libhfst.la $(GLIB_LIBS) -lreadline
else
  hfst_xfst_LDADD = $(top_builddir)/libhfst/src/libhfst.la $(GLIB_LIBS)
endif

EXTRA_DIST=init_help.cc cmd.h abbrcmd.h

