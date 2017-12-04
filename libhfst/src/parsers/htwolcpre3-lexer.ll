%option 8Bit batch yylineno noyywrap nounput prefix="htwolcpre3"

%{
  //   This program is free software: you can redistribute it and/or modify
  //   it under the terms of the GNU General Public License as published by
  //   the Free Software Foundation, version 3 of the Licence.
  //
  //   This program is distributed in the hope that it will be useful,
  //   but WITHOUT ANY WARRANTY; without even the implied warranty of
  //   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  //   GNU General Public License for more details.
  //
  //   You should have received a copy of the GNU General Public License
  //   along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  // Autotools stuff
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

  // input_defs.h declares the inputHandler, which is
  // an object that overrides flex' default input reading.
//#include "io_src/input_defs.h"

extern void htwolcpre3error(const char*);

#undef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) htwolcpre3error(msg);

#include "io_src/InputReader.h"
extern InputReader htwolcpre3_input_reader;
#undef YY_INPUT
#define YY_INPUT( buf, result, max_size ) { \
char c = htwolcpre3_input_reader.input(); \
if (c == 0) { \
result = YY_NULL; \
} \
 else { \
buf[0] = c; \
result = 1; \
} \
}

#include "string_src/string_manipulation.h"

#include "rule_src/TwolCGrammar.h"

#include "htwolcpre3-parser.hh"

  /*
#include "io_src/InputReader.h"



#include "alphabet_src/Alphabet.h"


  */
%}

%%

__HFST_TWOLC_Alphabet { return ALPHABET_DECLARATION; }
__HFST_TWOLC_Diacritics { return DIACRITICS_DECLARATION; }
__HFST_TWOLC_Definitions { return DEFINITION_DECLARATION; }
__HFST_TWOLC_Sets { return SETS_DECLARATION; }
__HFST_TWOLC_Rules { return RULES_DECLARATION; }
__HFST_TWOLC_DIE {
  // If this symbol is seen, exit quietly.
  HFST_THROW(HfstException);
}
[ \t\n] { /* space: ignore */ }

__HFST_TWOLC_RULE_NAME=\"[^\"]+\" {
  htwolcpre3lval.value = string_copy(htwolcpre3text);
  return RULE_NAME;
}
__HFST_TWOLC_except { return EXCEPT; }
__HFST_TWOLC_[*] { return STAR; }
__HFST_TWOLC_[+] { return PLUS; }
__HFST_TWOLC_[/] { return FREELY_INSERT; }
__HFST_TWOLC_[~] { return COMPLEMENT; }
__HFST_TWOLC_[\\] { return TERM_COMPLEMENT; }
__HFST_TWOLC_[$][.] { return CONTAINMENT_ONCE; }
__HFST_TWOLC_[$] { return CONTAINMENT; }
__HFST_TWOLC_[?] { return QUESTION_MARK; }
__HFST_TWOLC_[0] {
  htwolcpre3lval.value = string_copy(htwolcpre3text);
  return SYMBOL;
}
__HFST_TWOLC_[|] { return UNION; }
__HFST_TWOLC_[&] { return INTERSECTION; }
__HFST_TWOLC_[\^] { return POWER; }
__HFST_TWOLC_[\-] { return DIFFERENCE; }
__HFST_TWOLC_NUMBER=[0-9]+ {
  htwolcpre3lval.value = string_copy(htwolcpre3text);
  return NUMBER;
}
__HFST_TWOLC_NUMBER=[0-9]+,[0-9]+ {
  htwolcpre3lval.value = string_copy(htwolcpre3text);
  return NUMBER_RANGE;
}
__HFST_TWOLC_\[ { return LEFT_SQUARE_BRACKET; }
__HFST_TWOLC_\] { return RIGHT_SQUARE_BRACKET; }
__HFST_TWOLC_\[\[ { return RE_LEFT_SQUARE_BRACKET; }
__HFST_TWOLC_\]\] { return RE_RIGHT_SQUARE_BRACKET; }
__HFST_TWOLC_\( { return LEFT_PARENTHESIS; }
__HFST_TWOLC_\) { return RIGHT_PARENTHESIS; }
__HFST_TWOLC_[/][<][=] { return LEFT_RESTRICTION_ARROW; }
__HFST_TWOLC_[<][=] { return LEFT_ARROW; }
__HFST_TWOLC_[=][>] { return RIGHT_ARROW; }
__HFST_TWOLC_[<][=][>] { return LEFT_RIGHT_ARROW; }
__HFST_TWOLC_[/][<][=][=] { return RE_LEFT_RESTRICTION_ARROW; }
__HFST_TWOLC_[<][=][=] { return RE_LEFT_ARROW; }
__HFST_TWOLC_[=][=][>] { return RE_RIGHT_ARROW; }
__HFST_TWOLC_[<][=][=][>] { return RE_LEFT_RIGHT_ARROW; }
__HFST_TWOLC_[:] { return COLON; }
__HFST_TWOLC_[;] { return SEMI_COLON; }
__HFST_TWOLC_[=] { return EQUALS; }
__HFST_TWOLC__ { return CENTER_MARKER; }

__HFST_TWOLC_SET_NAME=[^ ]+ {
  htwolcpre3lval.value = string_copy(htwolcpre3text);
  return SYMBOL;
}
__HFST_TWOLC_DEFINITION_NAME=[^ ]+ {
  htwolcpre3lval.value = string_copy(htwolcpre3text);
  return DEFINITION_NAME;
}
[^ ]+ {
  htwolcpre3lval.value = string_copy(htwolcpre3text);
  return SYMBOL;
}

%%
