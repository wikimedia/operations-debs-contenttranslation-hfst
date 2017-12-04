AM_CXXFLAGS= -Wcast-qual -Wno-deprecated -Wfatal-errors

if WANT_TWOLC_SCRIPT
  bin_PROGRAMS=hfst-twolc htwolcpre1 htwolcpre2 htwolcpre3
  bin_SCRIPTS=hfst-twolc-script hfst-twolc-local-script
else
  bin_PROGRAMS=hfst-twolc
  bin_SCRIPTS=
endif

AM_CPPFLAGS = -I${top_srcdir}/libhfst/src -I${top_srcdir}/libhfst/src/parsers
LDADD = $(top_builddir)/libhfst/src/libhfst.la

# the preprocessor scripts do not support options per se, so we whitelist
# them here
AM_INSTALLCHECK_STD_OPTIONS_EXEMPT=htwolcpre1 htwolcpre2 htwolcpre3

hfst_twolc_SOURCES=hfst-twolc.cc
if WANT_TWOLC_SCRIPT
  htwolcpre1_SOURCES=htwolcpre1-main.cc
  htwolcpre2_SOURCES=htwolcpre2-main.cc
  htwolcpre3_SOURCES=htwolcpre3-main.cc
endif

if WANT_TWOLC_SCRIPT
hfst-twolc-script: hfst-twolc.sh
	cat $< | sed -e 's|BINDIR|$(bindir)|' > $@
	chmod ogu+rx hfst-twolc-script

hfst-twolc-local-script: hfst-twolc.sh
	cat $< | sed -e 's|BINDIR|$(abs_builddir)|' > $@
	chmod ogu+rx hfst-twolc-local-script

clean-local:
	-rm -f hfst-twolc-script hfst-twolc-loc-script
endif

# Distribute all twolc implementations
EXTRA_DIST=hfst-twolc.sh hfst-twolc.bat \
	   htwolcpre1-main.cc htwolcpre2-main.cc htwolcpre3-main.cc \
	   hfst-twolc.cc
