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

if GENERATE_FOMA_WRAPPER
bin_SCRIPTS = hfst-foma-wrapper.sh hfst-foma ${top_srcdir}/back-ends/foma/hfst_foma
EXTRA_DIST=hfst-foma generate-cc-files.sh
AM_INSTALLCHECK_STD_OPTIONS_EXEMPT=hfst-foma-wrapper.sh hfst-foma ${top_srcdir}/back-ends/foma/hfst_foma
endif
