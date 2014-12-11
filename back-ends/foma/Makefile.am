AUTOMAKE_OPTIONS=std-options

.NOTPARALLEL:

AM_CPPFLAGS= -Wno-deprecated -std=c99 -D_XOPEN_SOURCE=500

if WANT_MINGW
AM_CPPFLAGS += -DWINDOWS -D__NO_MINGW_LFS
endif

noinst_LTLIBRARIES = libfoma.la
libfoma_la_SOURCES = int_stack.c define.c determinize.c apply.c \
        rewrite.c lexcread.c topsort.c flags.c minimize.c reverse.c \
        extract.c sigma.c structures.c constructions.c \
        coaccessible.c io.c utf8.c spelling.c dynarray.c mem.c stringhash.c \
        trie.c lex.lexc.c lex.yy.c regex.c

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
hfst_foma_SOURCES=foma.c stack.c iface.c lex.interface.c lex.cmatrix.c
AM_CPPFLAGS += -DZLIB
endif

EXTRA_DIST=foma.h fomalibconf.h fomalib.h lexc.h regex.h 
