=============================================
 HFST-lexc: Lexc compatible lexicon compiler
=============================================

This package contains free and open source implementation of lexicon compiler
for finite state tools using Helsinki Finite State Technology APIs. HFST-lexc
is a clone of Xerox lexc [BEE2003]_ made for legacy support.  For faster
lexicon compilation refer to HFST utilities.  For techinical paper on how to
implement lexicons in finite state calculus, see [LSP2009]_.

This package is licenced under GNU GPL version 3 (other licences may be
available at request).  Licence can be found from file ``COPYING``.  Other
licences are possible, and can be given by authors found in ``AUTHORS`` file.

When reading this ``README`` assume that words *must*, and *should* are used
here as in RFC and IETF jargon whenever *emphasized*.

Downloading
-----------

Fresh source code is available from `corpus cvs repository`_.
Stable versions can be found from `hfst download directory`_.
Report bugs to `HFST team <hfst-bugs@helsinki.fi>`_.

Dependencies
------------

Compilation requirements:

- compiler *must* be able to find hfst headers (e.g. ``hfst2/hfst.h``)

- linker *must* be able to find library named hfst (e.g. ``libhfst.so``,
  ``libhfst.dylib``, ``libhfst.dll``, or ``libhfst.a``)

- linker *should* be able to find library named readline, if readline interface
  will be used

- GNU flex 2.5.35 and bison x.x.xx or compatible. Especially flex 2.5.33 will
  choke on perfectly valid rules used in the lexc lexer.

- Underlying transducer libraries *may* impose further restrictions; e.g.
  OpenFST may require pthreads library

- Versions loaded from version control systems require relatively new autotool
  chain to build: autoconf >=2.60, autoconf, libtool >=2.2, >=gettext-0.17.

Runtime requirements:

- If the executable is dynamically linked (almost always), the operating system
  *must* be able to find hfst and readline libraries.

Installation
------------

Installation uses standard autotools system::

  ./configure && make && make install

If configure has hard time finding HFST data, you may need to tell it
manually. Configure’s helps usually provide information on accomplishing this::

  ./configure --help

Autotools system supports installation to e.g. home directory::

  ./configure --prefix=${HOME}

To force statically linked binaries for distribution you can::

  ./configure --enable-static

For systems which only support static linkage, it is used by default. Should
static linkage fail in linking errors, do ensure correct ordering of -l flags
passed to compiler.

In CVS or SVN version you must create necessary autotools
files in host system::

  ./autogen.sh

It is common practice to keep `generated files out of CVS
<http://www.gnu.org/software/automake/manual/automake.html#CVS>`_.

For further installation instruction refer to file ``INSTALL``, which contains
the standard installation instructions for GNU autoconf based software.

Usage
-----

The executable is typically called ``hfst-lexc``. It can read
lexc files and produce HFST binary transducers. For basic operation you may use
either ``hfst-lexc -o output.hfst input.hlexc`` or
``hfst-lexc -q < input.hlexc > output.hfsta``. If readline support was compiled
in, you may also use Xerox lexc lookalike user interface by simply calling
command ``hfst-lexc`` without any arguments. For more options say
``hfst-lexc --help``::

  Usage: hfst-lexc [OPTIONS] [INFILE...]

  Compile lexc file to HFST transducer

-h, --help                   Print this help message
-V, --version                Print version info
-v, --verbose                Print verbosely while compiling
-q, --quiet                  Do not print verbosely while compiling
-o, --output=OUTFILE         Write output to OUTFILE
-w, --weighted               Use weighted transducer format
-u, --unweighted             Use unweighted transducer format
-t, --time                   Time all stuff
-d, --debug                  Print very verbosely
-y, --yydebug                Use yacc debugging routines
-X, --xerox                  Imitate xerox output

::

  If either INFILE... or OUTFILE is missing or -, standard streams will be used.

Any number of input files may be specified. If there are more than one files,
the processing works almost as if the files were concatenated together. This
means that the first file must contain the definitions of multichar symbols.
If no input files are given on command line, program will expect input from
standard input stream.

Most of the command line parameters should be self explanatory; the
``--verbose``, ``--quiet``, ``--time``, ``--debug`` and ``--yydebug`` control
how noisy the program is. Debug is not for general consumption, and may not be
available in all release versions. Timing mode may be disabled from certain
release versions as well; It merely displays ``clock(3)`` outputs after each
step of lexicon building.

The options ``--weighted`` and ``--unweighted`` control which finite state
backend is used when building lexicons.

If you want to automate FST building in your Makefiles, the following suffix
rule (or similar) may be useful::

  %.lexc.hfst: %.hlexc
      $(HFSTLEXC) --verbose --output=$@ $<

Error messages and warnings
---------------------------

Many of the messages are modelled after xerox’s lexc utility. For more thorough
understanding you may wish to refer *The Black Book* [BEE2003]_.
The errors have been assigned unique codenames to improve traceability and help
bug tracking.  Following is sorted according in order of error codenames:

* ``E1``: cannot open input file for reading. Make sure that file exists and is
  readable.

* ``E2``: cannot open output file for writing. Make sure that file exists and
  is writable.

* ``E3``: command line option was not recognised. Read ``hfst-lexc --help``.

* ``E8``: syntax error. Comes from the parsing framework used. This means that
  the parser cannot find reasonable parse for input. Might be followed by
  something like:
    
    * *unexpected ULSTRING, expecting LEXICON_NAME [near: `Nouns']*. This
      often means that there is a missing semicolon at the end of lexicon line.
    
    * *unexpected ';', expecting LEXICON_NAME or ULSTRING or
      XEROX_REGEXP or ':' [near: `;']*. Usually from extraneous
      semicolon at end of lexicon declaration.

    * many others, usually line numbers give good indication.

* ``E9``: stray % escape in string. String *must* not be ended in single %.

Warnings are not fatal, but usually mean something is wrong and needs to be
fixed:

* ``W1``: result is empty transducer.

* ``W2``: first lexicon is not named Root. The initial lexicons is one named
  Root or first one encountered if no Root lexicons are present.

* ``W3``: lexicon named Root is not the first. See also W2; hfst-lexc uses first
  lexicon in file as entry point even if it finds lexicon named ``Root``
  elsewhere.

* ``W7``: lexicons defined but not used. Happens when you have
  ``LEXICON foo`` in your file but no entry pointing to ``foo``. Ensure
  spelling is correct. The whole lexicon definition will be dropped from
  final transducer as no path will lead to it!

* ``W8``: lexicons used but not defined. Happens when you have entry
  ``x:y foo ;`` but no ``LEXICON foo`` in your file. Ensure spelling is
  correct. The whole string entry will be dropped since it points to
  non-existent lexicon!

* ``W9``: info strings ignored. When faced with an entry with extra info such as
  ``kalja # "beer" ;``  hfst-lexc discards the "beer" part. If you want to
  gloss your entries use e.g. gloss lexicon and composition.

* ``W11``: when using option ``--unweighted`` with lexicon that contains
  weights, the weights will be discarded.

* ``W12``: entry contains characters that are not in Alphabet. The whole
  entry may be dropped.

* ``W13``: changing weightedness in interactive interface may break under
  many conditions.

Do note that, if you do not specify ``--verbose`` nor ``--quiet``, warnings and
errors will still be printed, but little else. If absolutely no output needs to
be printed, ``--quiet`` may be used to suppress non-fatal warnings.


.. [KOS1983] *Koskenniemi, Kimmo* (1983). Two-level morphology:
   A general computational model of word-form recognition and production.
.. [BEE2003] *Beesley, Kenneth R.*, *Karttunen, Lauri* (2003). Finite State
   Morphology.
.. [LSP2009] *Linden, K.*, *Silfverberg, M.*, *Pirinen, T.* (2009)
   HFST Tools for Morphology -- An Efficient Open-Source Package for
   Construction of Morphological Analyzers in Proceedings of SFCM 2009

.. _ABNF: http://tools.ietf.org/html/rfc5234
.. _RFC 2822: http://www.faqs.org/rfcs/rfc2822.html
.. _corpus cvs repository: https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstCvsRepository
.. _GNU programming standards: http://www.gnu.org/prep/standards/standards.html
.. _HFST: http://www.ling.helsinki.fi/kieliteknologia/tutkimus/hfst/
.. _hfst download directory: http://www.ling.helsinki.fi/kieliteknologia/tutkimus/hfst/downloads.shtml
.. _lexc: http://www.xrce.xerox.com/competencies/content-analysis/fssoft/docs/lexc-93/lexc93.html
.. _Xerox: http://www.xerox.com
.. _xfst: http://www.xrce.xerox.com/competencies/content-analysis/fst/

.. vim: set ft=rst:
