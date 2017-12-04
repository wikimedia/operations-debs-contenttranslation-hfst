%option 8Bit batch yylineno noyywrap nounput prefix="htwolcpre1"

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

  // The parser. Supplies flex with its symbol tables.
  #include "htwolcpre1-parser.hh"

  // Functions for manipulating strings.
  #include "string_src/string_manipulation.h"

  // input_defs.h declares the inputHandler, which is
  // an object that overrides flex' default input reading.
  //#include "io_src/input_defs.h"

extern void htwolcpre1error(const char*);

#undef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) htwolcpre1error(msg);

#include "io_src/InputReader.h"
extern InputReader htwolcpre1_input_reader;
#undef YY_INPUT
#define YY_INPUT( buf, result, max_size ) { \
char c = htwolcpre1_input_reader.input(); \
if (c == 0) { \
result = YY_NULL; \
} \
 else { \
buf[0] = c; \
result = 1; \
} \
}

  // symbol_queue is used to pass strings from Flex to Bison.
  #include "HfstTwolcDefs.h"
  extern HandyDeque<std::string> htwolcpre1_symbol_queue;

  // This tells Bison that regular expression sections commenced.
  bool regexp_start = false;

  // This tells Bison that the rule section commenced.
  bool htwolcpre1_rules_start = false;

  // Tells whether we are in the where-part of a rule or not.
  bool where_seen = false;

  // Tells whether we are inside a ( .. ). For variable rules.
  extern bool htwolcpre1_inside_parenthesis;

  void reduce_queue(bool variable_symbol=false);

namespace hfst {
namespace twolcpre1 {
void reset_lexer()
{
  regexp_start = false;
  htwolcpre1_rules_start = false;
  where_seen = false;
}
}
}

%}

RESERVED_SYMBOL	   [*+/\\=\"$?|&^\-\{\}\[\]\(\):;_!%\r\t\n~ ]
RESERVED_EXC_COL   [*+/\\=\"$?|&^\-\{\}\[\]\(\):;_!%\r\t\n~ ]{-}[:]
RESERVED_EXC_PERC_AND_Q_MARK  [*+/\\=\"$?|&^\-\{\}\[\]\(\):;_!%\r\t\n~ ]{-}[%?]
FREE_SYMBOL	   [^*+/\\=\"$?|&^\-\{\}\[\]\(\):;_!%\r\t\n~ ]

%%

Alphabet/{RESERVED_SYMBOL} {
  // Alphabet declaration.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_Alphabet");
  reduce_queue();
  return ALPHABET_DECLARATION;
}
Diacritics/{RESERVED_SYMBOL} {
  // Diacritics declaration.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_Diacritics");
  reduce_queue();
  return DIACRITICS_DECLARATION;
}
Rule-variables/{RESERVED_SYMBOL} {
  // Rule-variables declaration, is not necessary,
  // but is supported for backwards compatibility.
  return VARIABLE_DECLARATION;
}
Definitions/{RESERVED_SYMBOL} {
  // Definitions declaration.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_Definitions");
  reduce_queue();
  regexp_start = true;
  return DEFINITION_DECLARATION;
}
Sets/{RESERVED_SYMBOL} {
  // Sets declaration.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_Sets");
  reduce_queue();
  return SETS_DECLARATION;
}
Rules/{RESERVED_SYMBOL} {
  // Rules declaration.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_Rules");
  reduce_queue();
  htwolcpre1_rules_start = true;
  regexp_start = true;
  return RULES_DECLARATION;
}
where/{RESERVED_SYMBOL} {
  // The symbols until AND occur in rules with variables.
  // When the symbols are encountered, nothing is printed,
  // since the purpose is to reduce rules with variables
  // into sub-case rules without variables.
  where_seen = true;
  return WHERE;
}
except/{RESERVED_SYMBOL} {
  // Separates negative contexts from positive contexts.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_except");
  reduce_queue();
  return EXCEPT;
}
matched/{RESERVED_SYMBOL} { return MATCHED_MATCHER; }
mixed/{RESERVED_SYMBOL} { return MIXED_MATCHER; }
freely/{RESERVED_SYMBOL} { return FREELY_MATCHER; }
in/{RESERVED_SYMBOL} { return IN; }
[a]nd/{RESERVED_SYMBOL} { return AND; }

[!].* { /* comments: ignore */ }
[ \t\r] { /* spaces and tabs: ignore */ }
\n {
  // For counting lines. Since flex skips ahead with reading symbols,
  // it's better to increase the line count in the function reduce_queue().
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_\\n");
}
\"[^\"]+\" {
  // Rule name.
  htwolcpre1_symbol_queue.push_back
    (std::string("__HFST_TWOLC_RULE_NAME=")+
     replace_substr(htwolcpre1text," ","__HFST_TWOLC_SPACE"));
  // reduce_queue();
  return RULE_NAME;
}
[*] {
  // Kleene star operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_*");
  reduce_queue();
  return STAR;
}
[+] {
  // Kleene plus operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_+");
  reduce_queue();
  return PLUS;
}
[/] {
  // Freely insert operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_/");
  reduce_queue();
  return FREELY_INSERT;
}
[~] {
  // Complement operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_~");
  reduce_queue();
  return COMPLEMENT;
}
[\\] {
  // Term complement operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_\\");
  reduce_queue();
  return TERM_COMPLEMENT;
}
[$][.] {
  // Containment once operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_$.");
  reduce_queue();
  return CONTAINMENT_ONCE;
}
[$] {
  // Containment at least once operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_$");
  reduce_queue();
  return CONTAINMENT;
}
[?] {
  // Any symbol.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_?");
  return SYMBOL;
}
[?]/[:] {
  if (! regexp_start)
    { return QUESTION_MARK; }
  // Any symbol.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_?");
  return SYMBOL;
}
[?]/{RESERVED_EXC_COL} {
  if (! regexp_start)
    { return QUESTION_MARK; }
  // Any symbol.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_?");
  return SYMBOL_SPACE;
}

[0]/[:] {
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_0");
  return SYMBOL;
}
[0]/{RESERVED_EXC_COL} {
  // Zero symbol.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_0");
  return SYMBOL_SPACE;
}
[|] {
  // Or.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_|");
  reduce_queue();
  return UNION;
}
[&] {
  // And.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_&");
  reduce_queue();
  return INTERSECTION;
}
[\^] {
  // Power operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_^");
  reduce_queue();
  return POWER;
}
[\-] {
  // Difference operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_-");
  reduce_queue();
  return DIFFERENCE;
}
[0-9],[0-9]+/{RESERVED_EXC_COL} {
  // Number.
  htwolcpre1_symbol_queue.push_back(+htwolcpre1text);
  return NUMBER_SPACE;
}
[0-9]+/{RESERVED_EXC_COL} {
  // Number.
  htwolcpre1_symbol_queue.push_back(htwolcpre1text);
  return NUMBER_SPACE;
}
[0-9]+/[:] {
  // Number.
  htwolcpre1_symbol_queue.push_back(htwolcpre1text);
  return NUMBER;
}
[.][#][.]/{RESERVED_SYMBOL} {
  // Word boundary.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_.#.");
  return SYMBOL_SPACE;
}
\[ {
  // Beginning of a bracketed regex.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_[");
  reduce_queue();
  return LEFT_SQUARE_BRACKET;
}
\] {
  // End of a bracketed regex.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_]");
  reduce_queue();
  return RIGHT_SQUARE_BRACKET;
}
\<\[ {
  // Beginning of a bracketed regex.
  //
  // For some bizarre reason [[ can't occur in the string-literal here...
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_[" "[");
  reduce_queue();
  return RE_LEFT_SQUARE_BRACKET;
}
\]\> {
  // End of a bracketed regex.
  //
  // For some bizarre reason ]] can't occur in the string-literal here...
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_]" "]");
  reduce_queue();
  return RE_RIGHT_SQUARE_BRACKET;
}
\{ {
  // Beginning of a bracketed regex.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_[");
  reduce_queue();
  return LEFT_CURLY_BRACKET;
}
\} {
  // End of a bracketed regex.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_]");
  reduce_queue();
  return RIGHT_CURLY_BRACKET;
}
\( {
  // Beginning of an optional bracketed regex.
  if (! where_seen)
    {
      htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_(");
      reduce_queue();
    }
  return LEFT_PARENTHESIS;
}
\) {
  // End of an optional bracketed regex.
  if (! where_seen)
    {
      htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_)");
      reduce_queue();
    }
  BEGIN 0;
  return RIGHT_PARENTHESIS;
}
[/][<][=] {
  // Restriction rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_/<=");
  reduce_queue();
  return LEFT_RESTRICTION_ARROW;
}
[<][=] {
  // Left rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_<=");
  reduce_queue();
  return LEFT_ARROW;
}
[=][>] {
  // Right rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_=>");
  reduce_queue();
  return RIGHT_ARROW;
}
[<][=][>] {
  // Equivalence rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_<=>");
  reduce_queue();
  return LEFT_RIGHT_ARROW;
}
[/][<][=][=] {
  // Restriction regular expression rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_/<==");
  reduce_queue();
  return RE_LEFT_RESTRICTION_ARROW;
}
[<][=][=] {
  // Left regular expression rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_<==");
  reduce_queue();
  return RE_LEFT_ARROW;
}
[=][=][>] {
  // Right regular expression rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_==>");
  reduce_queue();
  return RE_RIGHT_ARROW;
}
[<][=][=][>] {
  // Equivalence regular expression rule operator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_<==>");
  reduce_queue();
  return RE_LEFT_RIGHT_ARROW;
}
[:]/{RESERVED_EXC_PERC_AND_Q_MARK} {
  // Pair separator in expressions like "[a:]".
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_: ");
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_?");
  return COLON_SPACE;
}
[:] {
  // Pair separator.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_:");
  return COLON;
}
[;] {
  // End-of-line symbol.
  if (where_seen)
    { where_seen = false; }
  else
    {
      htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_;");
      reduce_queue();
    }
  return SEMI_COLON;
}
[=] {
  // Equals sign used when defining sets and making definitions.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_=");
  reduce_queue();
  return EQUALS;
}
[_] {
  // Center-marker in a rule context.
  htwolcpre1_symbol_queue.push_back("__HFST_TWOLC__");
  reduce_queue();
  return CENTER_MARKER;
}
(([%]({RESERVED_SYMBOL}|{FREE_SYMBOL}))|{FREE_SYMBOL})+/[:] {
  // A symbol which is the left side of a pair e.g. "a" in "a:b".
  std::string symbol =
    remove_white_space(replace_substr(htwolcpre1text,"\n","__HFST_TWOLC_\\n"));
  if (symbol == "#")
    { htwolcpre1_symbol_queue.push_back("__HFST_TWOLC_#"); }
  else
    { htwolcpre1_symbol_queue.push_back(symbol); }
  return SYMBOL;
}

(([%]({RESERVED_SYMBOL}|{FREE_SYMBOL}))|{FREE_SYMBOL})+/{RESERVED_EXC_COL} {
  // A symbol which is not the left side of a pair e.g. "b" in "a:b" or "[b]".
  std::string symbol =
    remove_white_space(replace_substr(htwolcpre1text,"\n","__HFST_TWOLC_\\n"));
  if (symbol == "#")
    { symbol = "__HFST_TWOLC_#"; }
  htwolcpre1_symbol_queue.push_back(symbol);
  return SYMBOL_SPACE;
 }

%%
