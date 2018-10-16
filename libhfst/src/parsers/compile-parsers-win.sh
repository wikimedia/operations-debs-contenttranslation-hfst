
if [ "$1" = "--help" -o "$1" = "-h" ]; then
  echo "(For windows) Compile parsers and lexers in this directory."
  exit 0
fi

EXT=cpp

win_flex.exe --outfile=htwolcpre1-lexer.$EXT htwolcpre1-lexer.ll
win_flex.exe --outfile=htwolcpre2-lexer.$EXT htwolcpre2-lexer.ll
win_flex.exe --outfile=htwolcpre3-lexer.$EXT htwolcpre3-lexer.ll
win_flex.exe --outfile=lexc-lexer.$EXT lexc-lexer.ll
win_flex.exe --outfile=pmatch_lex.$EXT pmatch_lex.ll
win_flex.exe --outfile=sfst-scanner.$EXT sfst-scanner.ll
win_flex.exe --outfile=xfst-lexer.$EXT xfst-lexer.ll
win_flex.exe --outfile=xre_lex.$EXT xre_lex.ll

win_bison.exe --defines=htwolcpre1-parser.hh --output=htwolcpre1-parser.$EXT htwolcpre1-parser.yy
win_bison.exe --defines=htwolcpre2-parser.hh --output=htwolcpre2-parser.$EXT htwolcpre2-parser.yy
win_bison.exe --defines=htwolcpre3-parser.hh --output=htwolcpre3-parser.$EXT htwolcpre3-parser.yy
win_bison.exe --defines=lexc-parser.hh --output=lexc-parser.$EXT lexc-parser.yy
win_bison.exe --defines=pmatch_parse.hh --output=pmatch_parse.$EXT pmatch_parse.yy
win_bison.exe --defines=sfst-compiler.hh --output=sfst-compiler.$EXT sfst-compiler.yy
win_bison.exe --defines=xfst-parser.hh --output=xfst-parser.$EXT xfst-parser.yy
win_bison.exe --defines=xre_parse.hh --output=xre_parse.$EXT xre_parse.yy
