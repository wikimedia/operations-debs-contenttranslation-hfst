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

%{
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WINDOWS
#include <io.h>
#endif

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "io_src/InputReader.h"
#include "grammar_defs.h"
#include "HfstTwolcDefs.h"
#include "rule_src/TwolCGrammar.h"
#include "rule_src/OtherSymbolTransducer.h"
#include "alphabet_src/Alphabet.h"
#include "string_src/string_manipulation.h"
#include "commandline_src/CommandLine.h"
#include <cstdio>
#include "common_globals.h"

#ifdef DEBUG_TWOLC_3_GRAMMAR
#define YYDEBUG 1
#endif

  extern int yylineno;
  extern char * yytext;
  extern int yylineno;
  extern char * yytext;
  extern bool rules_start;
  void yyerror(const char * text );
  void semantic_error(const char * text);
  void warn(const char * warning );
  void message(const std::string &m);
  int yylex();
  int yyparse();
  
  bool silent = false;
  bool verbose = false;

#define YYERROR_VERBOSE 1

  // For reading input one byte at a time.
  size_t line_number = 1;
  InputReader input_reader(line_number);

  // The Alphabet of the grammar
  Alphabet alphabet;

  // A map storing named regular expressions (i.e. definitions).
  HandyMap<std::string,OtherSymbolTransducer> definition_map;

  // The grammar, which compiles rules, resolves conflicts and stores 
  // rule transducers.
  // TwolCGrammar grammar(true,true);
  TwolCGrammar * grammar;

  unsigned int get_number(const std::string &);
  unsigned int get_second_number(const std::string &s);
  std::string get_name(const std::string &s);

%}



%union 
{ 
  int symbol_number;
  OtherSymbolTransducer * regular_expression;
  char * value; 
  SymbolRange * symbol_range;
  SymbolPairVector * symbol_pair_range;
  op::OPERATOR rule_operator;
};


 /* 
    All unary operators have stronger precedence than binary ones.
 */

 /* Binary operators ordered by precedence from lowest to highest. */
%left  <symbol_number> FREELY_INSERT
%left  <symbol_number> DIFFERENCE
%left  <symbol_number> INTERSECTION
%left  <symbol_number> UNION

 /* Unary operators ordered by precedence from lowest to highest. */
%right <symbol_number> STAR PLUS
%left  <symbol_number> CONTAINMENT CONTAINMENT_ONCE TERM_COMPLEMENT COMPLEMENT 
%right <symbol_number> POWER

 /* "[", "]", "(", ")". */
%right <symbol_number> RIGHT_SQUARE_BRACKET RIGHT_PARENTHESIS 
%left  <symbol_number> LEFT_SQUARE_BRACKET LEFT_PARENTHESIS

 /* Twolc rule operators */
%token <symbol_number> LEFT_RESTRICTION_ARROW LEFT_ARROW RIGHT_ARROW 
%token <symbol_number> LEFT_RIGHT_ARROW

 /* Twolc regular expression rule operators */
%token <symbol_number> RE_LEFT_RESTRICTION_ARROW RE_LEFT_ARROW RE_RIGHT_ARROW 
%token <symbol_number> RE_LEFT_RIGHT_ARROW

 /* Twolc regular expression rule center brackets. */
%right <symbol_number> RE_RIGHT_SQUARE_BRACKET
%left  <symbol_number> RE_LEFT_SQUARE_BRACKET

 /* Basic tokens. */
%token <symbol_number>  ALPHABET_DECLARATION DIACRITICS_DECLARATION 
%token <symbol_number>  SETS_DECLARATION DEFINITION_DECLARATION
%token <symbol_number>  RULES_DECLARATION COLON SEMI_COLON
%token <symbol_number>  EQUALS CENTER_MARKER QUESTION_MARK EXCEPT
%token <value>          RULE_NAME SYMBOL DEFINITION_NAME NUMBER NUMBER_RANGE

%type<regular_expression> PAIR REGULAR_EXPRESSION RE_LIST RE RULE_CONTEXT
%type<regular_expression> RE_RULE_CENTER
%type<regular_expression> RULE_CONTEXTS NEGATIVE_RULE_CONTEXTS
%type<symbol_range>       SYMBOL_LIST 
%type<symbol_pair_range>  CENTER_PAIR CENTER_LIST RULE_CENTER
%type<rule_operator>      RULE_OPERATOR RE_RULE_OPERATOR
%type<value>              CENTER_SYMBOL PAIR_SYMBOL

%%

ALL: GRAMMAR {}
;

GRAMMAR: ALPHABET GRAMMAR1 
| GRAMMAR1

GRAMMAR1: DIACRITICS GRAMMAR2 
| GRAMMAR2

GRAMMAR2: SETS GRAMMAR3 
| GRAMMAR3

GRAMMAR3: DEFINITIONS GRAMMAR4
| GRAMMAR4

GRAMMAR4: RULES

RULES:RULES_HEADER RULE_LIST

RULES_HEADER:RULES_DECLARATION
{ message("Reading rules and compiling their contexts and centers."); }

RULE_LIST: /* empty */
| RULE_LIST RULE

RULE: RULE_NAME RULE_CENTER RULE_OPERATOR RULE_CONTEXTS NEGATIVE_RULE_CONTEXTS
{ 
  // Subtract negative contexts from positive contexts.
  $4->apply(&HfstTransducer::subtract,*$5);

  if (verbose)
    { message(std::string("Processing: ")+ get_name($1)); }

  if ($2->size() == 1)
    { grammar->add_rule($1,(*$2)[0],$3,OtherSymbolTransducerVector(1,*$4)); }
  else
    { grammar->add_rule($1,*$2,$3,OtherSymbolTransducerVector(1,*$4)); }
  free($1);
  delete $2;
  delete $4;
  delete $5;
}
| RULE_NAME RE_RULE_CENTER RE_RULE_OPERATOR RULE_CONTEXTS 
NEGATIVE_RULE_CONTEXTS
{
  // Subtract negative contexts from positive contexts.
  $4->apply(&HfstTransducer::subtract,*$5);

  grammar->add_rule($1,*$2,$3,OtherSymbolTransducerVector(1,*$4));
  free($1);
  delete $2;
  delete $4;
  delete $5;
}

RULE_CENTER: CENTER_PAIR
{ $$ = $1; }
| RULE_CENTER UNION CENTER_PAIR
{
  $$ = $1;
  $$->push_back(*$3->begin());
  delete $3;
}
| LEFT_SQUARE_BRACKET CENTER_LIST RIGHT_SQUARE_BRACKET
{ $$ = $2; }

RE_RULE_CENTER: RE_LEFT_SQUARE_BRACKET REGULAR_EXPRESSION RE_RIGHT_SQUARE_BRACKET
{ $$ = $2; }

CENTER_LIST: CENTER_PAIR
{ $$ = $1; }
| CENTER_LIST UNION CENTER_PAIR
{ 
  $$ = $1;
  $$->push_back(*$3->begin());
  delete $3;
}

CENTER_PAIR: CENTER_SYMBOL COLON CENTER_SYMBOL
{ 
  $$ = alphabet.get_symbol_pair_vector(SymbolPair($1,$3)); 
  free($1); free($3);
}

CENTER_SYMBOL: SYMBOL
{ $$ = $1; }
| QUESTION_MARK
{ $$ = string_copy("__HFST_TWOLC_?"); }

RULE_OPERATOR:LEFT_ARROW
{ $$ = op::LEFT; }
| RIGHT_ARROW
{ $$ = op::RIGHT; }
| LEFT_RESTRICTION_ARROW
{ $$ = op::NOT_LEFT; }
| LEFT_RIGHT_ARROW
{ $$ = op::LEFT_RIGHT; }

RE_RULE_OPERATOR: RE_LEFT_ARROW
{ $$ = op::RE_LEFT; }
| RE_RIGHT_ARROW
{ $$ = op::RE_RIGHT; }
| RE_LEFT_RESTRICTION_ARROW
{ $$ = op::RE_NOT_LEFT; }
| RE_LEFT_RIGHT_ARROW
{ $$ = op::RE_LEFT_RIGHT; }

RULE_CONTEXTS: /* empty */
{ $$ = new OtherSymbolTransducer(); }
| RULE_CONTEXTS RULE_CONTEXT
{ 
  $$ = &$1->apply(&HfstTransducer::disjunct,*$2);
  delete $2;
}

NEGATIVE_RULE_CONTEXTS: /* empty */
{ $$ = new OtherSymbolTransducer(); }
| EXCEPT RULE_CONTEXTS
{ $$ = $2; }

RULE_CONTEXT: REGULAR_EXPRESSION CENTER_MARKER REGULAR_EXPRESSION
SEMI_COLON_LIST
{
  $$ = new OtherSymbolTransducer(OtherSymbolTransducer::get_context(*$1,*$3));
  delete $1;
  delete $3;
}

ALPHABET: ALPHABET_HEADER ALPHABET_PAIR_LIST SEMI_COLON_LIST
{ alphabet.alphabet_done(); }

ALPHABET_HEADER:ALPHABET_DECLARATION
{ message("Reading alphabet."); }

DIACRITICS: DIACRITICS_HEADER SYMBOL_LIST SEMI_COLON_LIST
{ 
  grammar->define_diacritics(*$2);
  alphabet.define_diacritics(*$2);
  delete $2;
}

DIACRITICS_HEADER:DIACRITICS_DECLARATION
{ message("Reading diacritics."); }

SETS: SETS_HEADER SET_LIST 

SETS_HEADER:SETS_DECLARATION
{ message("Reading sets."); }

DEFINITIONS: DEFINITION_HEADER DEFINITION_LIST

DEFINITION_HEADER:DEFINITION_DECLARATION
{ message("Reading and compiling definitions."); }

DEFINITION_LIST: /* empty */
| DEFINITION_LIST DEFINITION

DEFINITION: DEFINITION_NAME EQUALS REGULAR_EXPRESSION SEMI_COLON_LIST
{
  definition_map[$1] = *$3;
  free($1);
  delete $3;
}

REGULAR_EXPRESSION: RE_LIST
{ $$ = $1; }
| REGULAR_EXPRESSION UNION RE_LIST
{ 
  $$ = &$1->apply(&HfstTransducer::disjunct,*$3);
  delete $3;
}
| REGULAR_EXPRESSION INTERSECTION RE_LIST
{
  $$ = &$1->apply(&HfstTransducer::intersect,*$3);
  delete $3;
}
| REGULAR_EXPRESSION DIFFERENCE RE_LIST
{
  $$ = &$1->apply(&HfstTransducer::subtract,*$3);
  delete $3;
}
| REGULAR_EXPRESSION FREELY_INSERT RE_LIST
{
  $1->apply
    (&HfstTransducer::insert_freely,
     SymbolPair(TWOLC_FREELY_INSERT,TWOLC_FREELY_INSERT),
     true);
  $1->apply
    (&HfstTransducer::substitute,
     SymbolPair(TWOLC_FREELY_INSERT,TWOLC_FREELY_INSERT),
     *$3,
     true);
  $$ = $1;

  delete $3;
}

RE_LIST: /* empty */
{ $$ = new OtherSymbolTransducer(HFST_EPSILON); }
| RE_LIST RE
{ 
  $$ = &$1->apply(&HfstTransducer::concatenate,*$2);
  delete $2;
}

RE: PAIR
{ $$ = $1; }
| RE POWER NUMBER
{ 
  $$ = &$1->apply(&HfstTransducer::repeat_n,get_number($3));
  free($3);
}
| RE POWER NUMBER_RANGE
{ 
  $$ = &$1->apply(&HfstTransducer::repeat_n_to_k,
          get_number($3),get_second_number($3));
  free($3);
}
| RE STAR
{ $$ = &$1->apply(&HfstTransducer::repeat_star); }
| RE PLUS
{ $$ = &$1->apply(&HfstTransducer::repeat_plus); }
| CONTAINMENT RE
{ $$ = &$2->contained(); }
| CONTAINMENT_ONCE RE
{ $$ = &$2->contained_once(); }
| COMPLEMENT RE
{ $$ = &$2->negated(); }
| TERM_COMPLEMENT RE
{ $$ = &$2->term_complemented(); }
| LEFT_SQUARE_BRACKET REGULAR_EXPRESSION RIGHT_SQUARE_BRACKET
{ $$ = $2; }
| LEFT_PARENTHESIS REGULAR_EXPRESSION RIGHT_PARENTHESIS
{ $$ = &$2->apply(&HfstTransducer::optionalize); }

SET_LIST: /* empty */ 
| SET_LIST SET_DEFINITION 

SYMBOL_LIST: /* empty */
{ $$ = new SymbolRange; }
| SYMBOL_LIST SYMBOL
{
  $1->push_back($2);
  $$ = $1;
  free($2);
}

SET_DEFINITION: SYMBOL EQUALS SYMBOL_LIST SEMI_COLON_LIST
{
  alphabet.define_set($1,*$3);
  free($1);
  delete $3;
}

ALPHABET_PAIR_LIST: /* empty */
| ALPHABET_PAIR_LIST ALPHABET_PAIR

PAIR: PAIR_SYMBOL COLON PAIR_SYMBOL
{ 
  if (std::string("__HFST_TWOLC_0") == $1 and 
      std::string("__HFST_TWOLC_0") == $3)
    { $$ = new OtherSymbolTransducer(HFST_EPSILON); }
  else if (std::string("__HFST_TWOLC_#") == $1)
    { 
      // __HFST_TWOLC_# corresponds to the #-symbol in grammars. It should
      // be split into an absolute word boundary "__HFST_TWOLC_.#." and a
      // relative word boundary "#". On the surface the relative word-boundary
      // may correspond to whatever it did correspond to in the rule file.
      // The absolute word boundary surface realization is treated the same as
      // the surface realizations of other absolute word boundaries.
      OtherSymbolTransducer wb = 
    alphabet.get_transducer(SymbolPair
                ("__HFST_TWOLC_.#.","__HFST_TWOLC_.#."));
      OtherSymbolTransducer alt_wb = 
    alphabet.get_transducer
    (SymbolPair
     ("#",$3 == std::string("__HFST_TWOLC_#") ? "#" : $3));      
      wb.apply(&HfstTransducer::disjunct,alt_wb);

      $$ = new OtherSymbolTransducer(wb);
    }  
  else
    { $$ = new OtherSymbolTransducer
    (alphabet.get_transducer(SymbolPair($1,$3))); 
      if (alphabet.is_empty_pair(SymbolPair($1,$3)))
    {
      std::string error;
      if (std::string($1) == std::string($3))
        {
          std::string symbol = Rule::get_print_name($1);

          error = std::string("The pair set ") + symbol + " is empty.";
        }
      else
        {
          std::string symbol1 = Rule::get_print_name($1);
          std::string symbol2 = Rule::get_print_name($3);

          error = std::string("The pair set ") + symbol1 + ":" + symbol2 + 
        " is empty.";
        }
      error +=  std::string("\n\n") +

        "Note that a pair set X:Y can be empty, even if the sets X and\n"+
            "Y are non-empty, since every symbol pair has to be declared in\n"+
        "the alphabet or it has to be the center of a rule, or be in\n"  +
        "the context of a rule or result from substituting values for\n" +
        "variables in a rule with variables.\n\n" +

        "Compilation is terminated because a rule context, definition\n" + 
        "or rule center becomes empty.\n\n";

      semantic_error(error.c_str());
    }
    }

  free($1);
  free($3);
}
| DEFINITION_NAME COLON DEFINITION_NAME
{ 
  $$ = new OtherSymbolTransducer(definition_map[$1]); 
  free($1);
  free($3);
}

PAIR_SYMBOL: SYMBOL
{ $$ = $1; }
| QUESTION_MARK
{ $$ = string_copy("__HFST_TWOLC_?"); }

ALPHABET_PAIR: SYMBOL COLON SYMBOL
{ 
  alphabet.define_alphabet_pair(SymbolPair($1,$3));
  free($1);
  free($3);
}

SEMI_COLON_LIST: SEMI_COLON
| SEMI_COLON_LIST SEMI_COLON

%%

// Print warning.
void warn(const char * warning) 
{ 
#ifdef DEBUG_TWOLC_3_GRAMMAR
  std::cerr << warning << std::endl;
#else
  (void)warning; 
#endif
}

// Print error messge and exit 1.
void yyerror(const char * text) 
{ 
  (void)text;
  input_reader.error(text);
  exit(1); 
}

// Print error messge and exit 1.
void semantic_error(const char * text) 
{ 
  std::cerr << std::endl << "Error: " << text << std::endl;
  exit(1);
}

unsigned int get_number(const std::string &s)
{
  // skip yhe prefix "HFST_TWOLC_NUMBER=".
  std::istringstream i(s.substr(20));
  unsigned int number;
  i >> number;
  return number;
}

unsigned int get_second_number(const std::string &s)
{
  // skip yhe prefix "HFST_TWOLC_NUMBER=".
  std::istringstream i(s.substr(s.find(',')+1));
  unsigned int number;
  i >> number;
  return number;
}

void message(const std::string &m)
{
  if (not silent)
    { std::cerr << m << std::endl; }
}

std::string get_name(const std::string &s)
{
  std::string ss = s;
  size_t pos = 0;
  while ((pos = ss.find("__HFST_TWOLC_RULE_NAME=")) != std::string::npos)
    { ss.replace(pos,std::string("__HFST_TWOLC_RULE_NAME=").size(),""); }
  while ((pos = ss.find("__HFST_TWOLC_SPACE")) != std::string::npos)
    { ss.replace(pos,std::string("__HFST_TWOLC_SPACE").size()," "); }
  return ss;
}

int main(int argc, char * argv[])
{
#ifdef WINDOWS
  _setmode(0, _O_BINARY);
  _setmode(1, _O_BINARY);
#endif

#ifdef DEBUG_TWOLC_3_GRAMMAR
  yydebug = 1;
#endif

  try 
    {
      CommandLine command_line(argc,argv);
      if (command_line.help or command_line.usage or command_line.version)
    { exit(0); }
      if (command_line.has_debug_file)
    { input_reader.set_input(command_line.set_input_file()); }
      else
    { input_reader.set_input(std::cin); }
      
      OtherSymbolTransducer::set_transducer_type(command_line.format);
      silent = command_line.be_quiet;
      verbose = command_line.be_verbose;
      
      TwolCGrammar twolc_grammar(command_line.be_quiet,
				 command_line.be_verbose,
				 command_line.resolve_left_conflicts,
				 command_line.resolve_right_conflicts);
      grammar = &twolc_grammar;
      int exit_code = yyparse();
      if (exit_code != 0)
    { exit(exit_code); }
      
      message("Compiling and storing rules.");
      if (not command_line.has_output_file)
    {
      HfstOutputStream stdout_(command_line.format);
      grammar->compile_and_store(stdout_);
    }
      else
    {
      HfstOutputStream out
        (command_line.output_file_name,command_line.format);
      grammar->compile_and_store(out);
    }
      exit(0);
    }
  catch (const HfstException e)
    {
      std::cerr << "This is an hfst interface bug:" << std::endl
        << e() << std::endl;
      exit(1);
    }
  catch (const char * s)
    {
      std::cerr << "This is an a bug probably from sfst:" << std::endl
        << s << std::endl;
      exit(1);
    }
}


