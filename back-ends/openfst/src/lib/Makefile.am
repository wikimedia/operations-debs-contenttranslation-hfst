## Process this file with automake to produce Makefile.in

# Copyright (c) 2016 University of Helsinki
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
# See the file COPYING included with this distribution for more
# information.

AUTOMAKE_OPTIONS=subdir-objects
AM_CPPFLAGS = -I $(srcdir)/../include $(ICU_CPPFLAGS)
noinst_LTLIBRARIES = libfst.la
libfst_la_SOURCES = compat.cc flags.cc fst.cc properties.cc \
	symbol-table.cc symbol-table-ops.cc util.cc
