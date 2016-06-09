
This package contains the command line tool hfst-xfst.exe for 64-bit Windows.

For more info about the tool, see: 
  <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstXfst>

For more info about the HFST project, see: 
  <http://hfst.sourceforge.net/>


Usage
-----

The tool works by default in an interactive mode. It can be started either by
double-clicking the icon (opens up a new console window) or executing 
'hfst-xfst' in command prompt (runs the program in the same window).

A prompt 'hfst[N]:' is shown when the program runs, N being the number of
transducers in the stack at the moment. All read and write commands happen in
the directory where the program was started.

When an interactive command is run inside hfst-xfst (e.g. 'apply up'), both
control+D and control+Z can be used to exit that command.

The command 'exit' exits the program and closes the console (if a new one was
opened) or returns to the console where the program was started.


Character encodings
-------------------

All HFST tools work in a UTF-8 mode. When hfst-xfst starts, it sets the console
code point to 65001, i.e. UTF-8. Scriptfiles must be encoded as UTF-8 with no
BOM (byte order mark) included.


Options
-------

When run from the command line, a number of options are available. For more
info, see the page <https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstXfst>.
Some important options related to input and output processing are:

  -F, --scriptfile=FILE      Read commands from FILE, and quit
  -l, --startupfile=FILE     Read commands from FILE on startup
  -p, --pipe-mode[=STREAM]   Control input and output streams

In interactive mode, all commands are read from console window, i.e. line by
line from the user and all output is printed to the console. If input comes
from a file or output is redirected to a file, the option --pipe-mode (or the
short form -p) must be used:

  type input.xfst | hfst-xfst.exe --pipe-mode=input
  hfst-xfst.exe --pipe-mode=output > output.txt
  type input.xfst | hfst-xfst.exe --pipe-mode[=both] > output.txt

(--pipe-mode with no argument is the same as --pipe-mode=both)


