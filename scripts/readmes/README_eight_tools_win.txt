
This package contains the following command line tools for 64-bit Windows:

  - hfst-xfst
  - hfst-lexc
  - hfst-twolc.bat
  - hfst-lookup
  - hfst-optimized-lookup
  - hfst-proc
  - hfst-pmatch
  - hfst-pmatch2fst


For more info about the tools, see their KitWiki pages:

  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstXfst>
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstLexc>
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstTwolC>
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstLookUp>
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstOptimizedLookup>
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstProc>
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstPmatch>
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstPmatch2Fst>

or run hfst-TOOLNAME --help in command prompt.


For more info about the HFST project, see:
  <http://hfst.sourceforge.net/>


Usage
-----

The tools hfst-xfst, hfst-lookup, hfst-optimized-lookup and hfst-pmatch work
by default in an interactive mode. They can be started either by
double-clicking the icon (opens up a new console window) or executing
'hfst-[xfst|lookup|optimized-lookup|pmatch]' in command prompt (runs the
program in the same window). They read input from the console, i.e. line by
line from the user and print their output to the console. Both control+D and
control+Z can be used to signal end of user input and exit the program.

The tools hfst-lexc, hfst-twolc.bat and hfst-pmatch2fst are meant to be used
from the command prompt. They take their input from a file and write their
input to a file. The files can be given as a command line arguments or via
standard streams. hfst-proc has currently no support for UTF-8 in interactive
mode on windows, so it should also be used in the same way.

Note that hfst-twolc.bat is a script that uses programs htwolcpre1, htwolcpre2
and htwolcpre3, so they should all be located in the same directory.


Character encodings
-------------------

All HFST tools work in a UTF-8 mode. When they are used in interactive mode,
they set the console code point to 65001, i.e. UTF-8. Input text files must be
encoded as UTF-8 with no BOM (byte order mark) included.


Input and output via standard streams
-------------------------------------

As windows separates between console input and standard input as well as
console output and standard output, some of the tools have an option
--pipe-mode. It specifies if input is redirected from a file or output
redirected to a file or both (the default for this option). --pipe-mode is
relevant only for text streams, binary streams work as such. It is always
possible to specify input and output text files also as command line arguments.


hfst-xfst
---------

A prompt 'hfst[N]:' is shown when the program runs, N being the number of
transducers in the stack at the moment. All read and write commands happen in
the directory where the program was started.

When an interactive command is run inside hfst-xfst (e.g. 'apply up'), both
control+D and control+Z can be used to exit that command.

The command 'exit' exits the program and closes the console (if a new one was
opened) or returns to the console where the program was started.

When run from the command line, a number of options are available. For more
info, see the page <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstXfst>.
Two important options related to input and output processing are:

  -F, --scriptfile=FILE      Read commands from FILE, and quit
  -l, --startupfile=FILE     Read commands from FILE on startup

