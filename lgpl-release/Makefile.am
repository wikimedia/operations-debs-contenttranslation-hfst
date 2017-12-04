## Process this file with automake to produce Makefile.in

# Copyright (c) 2016 University of Helsinki
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 3 of the License, or (at your option) any later version.
# See the file COPYING included with this distribution for more
# information.

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = back-ends libhfst python

# for external projects to use HFST from auto*
m4dir=$(datadir)/aclocal
m4_DATA=hfst.m4

EXTRA_DIST=hfst.m4

if CAN_DOXYGEN
doxygen:
	doxygen Doxyfile
endif
valgrind:
	$(MAKE) -C libhfst/src/ valgrind
	$(MAKE) -C test/tools/ valgrind
