AUTOMAKE_OPTIONS=std-options

.NOTPARALLEL:

#AM_CPPFLAGS= -Wno-deprecated -std=c99 -D_XOPEN_SOURCE=500
AM_CPPFLAGS= -Wno-deprecated -D_XOPEN_SOURCE=500 -fpermissive -std=c++11

if WANT_MINGW
AM_CPPFLAGS += -D__NO_MINGW_LFS
endif

noinst_LTLIBRARIES = libfoma.la
libfoma_la_SOURCES = int_stack.cc define.cc determinize.cc apply.cc \
        rewrite.cc lexcread.cc topsort.cc flags.cc minimize.cc reverse.cc \
        extract.cc sigma.cc structures.cc constructions.cc \
        coaccessible.cc io.cc utf8.cc spelling.cc dynarray.cc mem.cc stringhash.cc \
        trie.cc lex.lexc.cc lex.yy.cc regex.cc

hfst_foma_LDADD = $(top_builddir)/back-ends/foma/libfoma.la

if WANT_READLINE
hfst_foma_LDFLAGS=-lreadline -lz
else
hfst_foma_LDFLAGS=-lz
endif

if HAVE_TERMCAP
hfst_foma_LDFLAGS += -ltermcap
else
if HAVE_NCURSES
hfst_foma_LDFLAGS += -lncurses
else
if HAVE_CURSES
hfst_foma_LDFLAGS += -lcurses
endif
endif
endif

if GENERATE_FOMA_WRAPPER
bin_PROGRAMS=hfst_foma
hfst_foma_SOURCES=foma.cc stack.cc iface.cc lex.interface.cc lex.ccmatrix.cc
AM_CPPFLAGS += -DZLIB
endif

EXTRA_DIST=foma.h fomalibconf.h fomalib.h lexc.h regex.h
