AM_CPPFLAGS=-Wno-deprecated

if WANT_SFST
noinst_LTLIBRARIES = libsfst.la
endif
if WANT_LEAN_SFST
noinst_LTLIBRARIES = libsfst.la
endif

libsfst_la_SOURCES = alphabet.cc basic.cc utf8.cc compact.cc fst.cc \
        operators.cc determinise.cc generate.cc hopcroft.cc

EXTRA_DIST=alphabet.h basic.h compact.h fst.h interface.h mem.h sgi.h utf8.h
