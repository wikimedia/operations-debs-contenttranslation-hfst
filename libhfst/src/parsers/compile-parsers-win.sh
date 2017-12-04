
if [ "$1" = "--help" -o "$1" = "-h" ]; then
  echo "(For windows) Compile parsers and lexers in this directory."
  echo "Usage:  "$0" PROGDIR [--extension EXT]"
  echo "PROGDIR: Absolute path to directory where programs win_flex.exe"
  echo "         and win_bison.exe are located (can be fetched from"
  echo "         https://sourceforge.net/projects/winflexbison/)"
  echo "EXT:     Extension used for generated C++ files (default: cc)."
  exit 0
fi

if ! [ -d "$1" ]; then
  echo "Error: Directory "$1" does not exist (given as first argument)."
  exit 1
fi

if ! [ -e "$1/win_flex.exe" ]; then
  echo "Error: win_flex.exe was not found in directory "$1" (given as first argument)."
  exit 1
fi

if ! [ -e "$1/win_bison.exe" ]; then
  echo "Error: win_bison.exe was not found in directory "$1" (given as first argument)."
  exit 1
fi

EXT=cc
if [ "$2" = "--extension" ]; then
  EXT=$3
fi

$1/win_flex.exe --outfile=htwolcpre1-lexer.$EXT htwolcpre1-lexer.ll
$1/win_flex.exe --outfile=htwolcpre2-lexer.$EXT htwolcpre2-lexer.ll
$1/win_flex.exe --outfile=htwolcpre3-lexer.$EXT htwolcpre3-lexer.ll
$1/win_flex.exe --outfile=lexc-lexer.$EXT lexc-lexer.ll
$1/win_flex.exe --outfile=pmatch_lex.$EXT pmatch_lex.ll
$1/win_flex.exe --outfile=sfst-scanner.$EXT sfst-scanner.ll
$1/win_flex.exe --outfile=xfst-lexer.$EXT xfst-lexer.ll
$1/win_flex.exe --outfile=xre_lex.$EXT xre_lex.ll

$1/win_bison.exe --defines=htwolcpre1-parser.hh --output=htwolcpre1-parser.$EXT htwolcpre1-parser.yy
$1/win_bison.exe --defines=htwolcpre2-parser.hh --output=htwolcpre2-parser.$EXT htwolcpre2-parser.yy
$1/win_bison.exe --defines=htwolcpre3-parser.hh --output=htwolcpre3-parser.$EXT htwolcpre3-parser.yy
$1/win_bison.exe --defines=lexc-parser.hh --output=lexc-parser.$EXT lexc-parser.yy
$1/win_bison.exe --defines=pmatch_parse.hh --output=pmatch_parse.$EXT pmatch_parse.yy
$1/win_bison.exe --defines=sfst-compiler.hh --output=sfst-compiler.$EXT sfst-compiler.yy
$1/win_bison.exe --defines=xfst-parser.hh --output=xfst-parser.$EXT xfst-parser.yy
$1/win_bison.exe --defines=xre_parse.hh --output=xre_parse.$EXT xre_parse.yy
