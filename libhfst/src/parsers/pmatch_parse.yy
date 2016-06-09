%{
// Copyright (c) 2016 University of Helsinki                          
//                                                                    
// This library is free software; you can redistribute it and/or      
// modify it under the terms of the GNU Lesser General Public         
// License as published by the Free Software Foundation; either       
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more      
// information.

#define YYDEBUG 0

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <sstream>
    
#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstXeroxRules.h"
    
#include "pmatch_utils.h"
    using namespace hfst;
    using namespace hfst::pmatch;
    using namespace hfst::xeroxRules;

    extern int pmatcherror(const char * text);
    extern int pmatchlex();
    extern int pmatchlineno;

    %}

%name-prefix="pmatch"
     %error-verbose
     
     %union {
         int value;
         int* values;
         double weight;
         char* label;
         hfst::pmatch::PmatchObject* pmatchObject;
         std::pair<std::string, hfst::pmatch::PmatchObject*>* pmatchDefinition;
         std::vector<hfst::pmatch::PmatchObject *>* pmatchObject_vector;
         std::vector<std::string>* string_vector;

         hfst::pmatch::PmatchParallelRulesContainer * replaceRules;
         hfst::pmatch::PmatchReplaceRuleContainer * replaceRule;
         hfst::pmatch::PmatchMappingPairsContainer * mappings;
         hfst::pmatch::PmatchContextsContainer * parallelContexts;
         hfst::pmatch::PmatchObjectPair * restrictionContext;
         hfst::pmatch::MappingPairVector * restrictionContexts;
         hfst::xeroxRules::ReplaceType replType;
         hfst::xeroxRules::ReplaceArrow replaceArrow; 
     }

%start PMATCH
%type <pmatchDefinition> DEFINITION
%type <pmatchObject> EXPRESSION1 EXPRESSION2 EXPRESSION3 EXPRESSION4 EXPRESSION5 EXPRESSION6 EXPRESSION7 EXPRESSION8 EXPRESSION9 EXPRESSION10 EXPRESSION11 EXPRESSION12 EXPRESSION13
%type <label> SYMBOL QUOTED_LITERAL CURLY_LITERAL SYMBOL_WITH_LEFT_PAREN CONCATENATED_STRING_LIST
%type <string_vector> ARGLIST
%type <pmatchObject_vector> FUNCALL_ARGLIST

%type <replaceArrow> REPLACE_ARROW
%type <replaceRules> PARALLEL_RULES
%type <replaceRule> RULE
%type <mappings> MAPPINGPAIR_VECTOR MAPPINGPAIR

%type <parallelContexts> CONTEXTS_WITH_MARK CONTEXTS_VECTOR CONTEXT
%type <restrictionContext> RESTR_CONTEXT
%type <restrictionContexts> RESTR_CONTEXTS
%type <replType> CONTEXT_MARK
%type <pmatchObject> INSERTION FUNCALL EXPLODE IMPLODE ENDTAG READ_FROM CONTEXT_CONDITION PMATCH_CONTEXT PMATCH_OR_CONTEXT PMATCH_AND_CONTEXT
PMATCH_RIGHT_CONTEXT PMATCH_LEFT_CONTEXT PMATCH_NEGATIVE_RIGHT_CONTEXT PMATCH_NEGATIVE_LEFT_CONTEXT
%type <pmatchObject_vector> PMATCH_CONTEXTS

%left <weight> END_OF_WEIGHTED_EXPRESSION WEIGHT
%nonassoc <pmatchObject> CHARACTER_RANGE

%left CROSS_PRODUCT COMPOSITION LENIENT_COMPOSITION INTERSECTION MERGE_RIGHT_ARROW MERGE_LEFT_ARROW
%left CENTER_MARKER MARKUP_MARKER
%left SHUFFLE BEFORE AFTER
%right LEFT_ARROW RIGHT_ARROW LEFT_RIGHT_ARROW LEFT_RESTRICTION // LEFT_RESTRICTION not implemented
%left  REPLACE_RIGHT REPLACE_LEFT OPTIONAL_REPLACE_RIGHT OPTIONAL_REPLACE_LEFT
REPLACE_LEFT_RIGHT OPTIONAL_REPLACE_LEFT_RIGHT RTL_LONGEST_MATCH RTL_SHORTEST_MATCH
LTR_LONGEST_MATCH LTR_SHORTEST_MATCH 
%right REPLACE_CONTEXT_UU REPLACE_CONTEXT_LU REPLACE_CONTEXT_UL REPLACE_CONTEXT_LL
%left  UNION MINUS UPPER_MINUS LOWER_MINUS UPPER_PRIORITY_UNION LOWER_PRIORITY_UNION
%left  IGNORING IGNORE_INTERNALLY LEFT_QUOTIENT
%left COMMA COMMACOMMA
       
%nonassoc SUBSTITUTE_LEFT TERM_COMPLEMENT COMPLEMENT CONTAINMENT CONTAINMENT_ONCE CONTAINMENT_OPT
%nonassoc STAR PLUS REVERSE INVERT UPPER_PROJECT LOWER_PROJECT
%nonassoc <label> READ_BIN READ_TEXT READ_SPACED READ_PROLOG READ_RE READ_LEXC
%nonassoc <values> CATENATE_N_TO_K
%nonassoc <value> CATENATE_N CATENATE_N_PLUS CATENATE_N_MINUS

%token LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACKET_DOTTED RIGHT_BRACKET_DOTTED
%token PAIR_SEPARATOR PAIR_SEPARATOR_SOLE PAIR_SEPARATOR_WO_RIGHT PAIR_SEPARATOR_WO_LEFT
%token EPSILON_TOKEN ANY_TOKEN BOUNDARY_MARKER
%token LEXER_ERROR SYMBOL SYMBOL_WITH_LEFT_PAREN QUOTED_LITERAL CURLY_LITERAL
%token ALPHA LOWERALPHA UPPERALPHA NUM PUNCT WHITESPACE
//  MAP_LEFT
%right DEFINE LIT_LEFT INS_LEFT REGEX DEFINS DEFINED_LIST CAP_LEFT OPTCAP_LEFT OPT_TOLOWER_LEFT TOLOWER_LEFT
OPT_TOUPPER_LEFT TOUPPER_LEFT ANY_CASE_LEFT IMPLODE_LEFT EXPLODE_LEFT DEFINE_LEFT ENDTAG_LEFT LC_LEFT RC_LEFT NLC_LEFT NRC_LEFT OR_LEFT AND_LEFT
TAG_LEFT LST_LEFT EXC_LEFT INTERPOLATE_LEFT SIGMA_LEFT COUNTER_LEFT
%%

PMATCH: //empty
| PMATCH DEFINITION {
    if (verbose) {
        std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(2);
        double duration = (clock() - timer) /
            (double) CLOCKS_PER_SEC;
        timer = clock();
        std::cerr << "defined " << $2->first << " in " << duration << " seconds\n";
    }
    if (definitions.count($2->first) != 0) {
        std::stringstream warning;
        warning << "definition of " << $2->first << " on line " << pmatchlineno
                << " shadows earlier definition\n";
        warn(warning.str());
        delete definitions[$2->first];
    }
    definitions.insert(*$2);
 };

DEFINITION: DEFINE SYMBOL EXPRESSION1 {
    $$ = new std::pair<std::string, PmatchObject*>($2, $3);
    $3->name = $2;
    free($2);
 } |
 DEFINS SYMBOL EXPRESSION1 {
     $$ = new std::pair<std::string, PmatchObject*>(
         $2, new PmatchString(get_Ins_transition($2)));
     def_insed_expressions[$2] = $3;
     $3->name = $2;
     free($2);
 } |
 REGEX EXPRESSION1 {
     $$ = new std::pair<std::string, PmatchObject*>("TOP", $2);
     $2->name = "TOP";
 } |
 DEFINE SYMBOL_WITH_LEFT_PAREN ARGLIST RIGHT_PARENTHESIS EXPRESSION1 {
     PmatchFunction * fun = new PmatchFunction(*$3, $5);
     fun->name = $2;
     $$ = new std::pair<std::string, PmatchObject*>(std::string($2), fun);
     function_names.insert($2);
     free($2);
 } |
 DEFINED_LIST SYMBOL EXPRESSION1 {
     $$ = new std::pair<std::string, PmatchObject *>(
         $2, new PmatchUnaryOperation(MakeSigma, $3));
     $3->name = $2;
 };

ARGLIST:
SYMBOL COMMA ARGLIST { $$ = $3; $$->push_back(std::string($1));
 } | SYMBOL { $$ = new std::vector<std::string>(1, std::string($1)); }
| { $$ = new std::vector<std::string>(); };

EXPRESSION1: EXPRESSION2 END_OF_WEIGHTED_EXPRESSION {
     $1->weight += $2;
     if (need_delimiters) {
         $$ = new PmatchUnaryOperation(AddDelimiters, $1);
     } else {
         $$ = $1;
     }
     need_delimiters = false;
};

EXPRESSION2: EXPRESSION3 {} |
EXPRESSION2 COMPOSITION EXPRESSION3 { $$ = new PmatchBinaryOperation(Compose, $1, $3); } |
EXPRESSION2 CROSS_PRODUCT EXPRESSION3 { $$ = new PmatchBinaryOperation(CrossProduct, $1, $3); } |
EXPRESSION2 LENIENT_COMPOSITION EXPRESSION3 { $$ = new PmatchBinaryOperation(LenientCompose, $1, $3); } |
EXPRESSION2 MERGE_RIGHT_ARROW EXPRESSION3 { $$ = new PmatchBinaryOperation(Merge, $1, $3);} |
EXPRESSION2 MERGE_LEFT_ARROW EXPRESSION3 { $$ = new PmatchBinaryOperation(Merge, $3, $1); } |
SUBSTITUTE_LEFT LEFT_BRACKET EXPRESSION3 COMMA EXPRESSION3 COMMA EXPRESSION3 RIGHT_BRACKET {
    $$ = new PmatchTernaryOperation(Substitute, $3, $5, $7);
} |
EXPRESSION2 PAIR_SEPARATOR_WO_RIGHT {
    $$ = new PmatchBinaryOperation(CrossProduct, $1, new PmatchQuestionMark); } |
PAIR_SEPARATOR_WO_LEFT EXPRESSION2 {
    $$ = new PmatchBinaryOperation(CrossProduct, new PmatchQuestionMark, $2); } |
PAIR_SEPARATOR_SOLE {
    $$ = new PmatchQuestionMark;
};

EXPRESSION3: EXPRESSION4 { } |
PARALLEL_RULES { };

PARALLEL_RULES: PARALLEL_RULES COMMACOMMA RULE
{
    if ($3->arrow != $1->arrow) {
        pmatcherror("Replace type mismatch in parallel rules");
    }
    $$ = dynamic_cast<PmatchParallelRulesContainer *>($$);
    $1->rules.push_back($3);
} | RULE {
    $$ = new PmatchParallelRulesContainer($1);
};

RULE: MAPPINGPAIR_VECTOR
{ $$ = new PmatchReplaceRuleContainer($1); } |
MAPPINGPAIR_VECTOR CONTEXTS_WITH_MARK
{ $$ = new PmatchReplaceRuleContainer($1, $2); };
      
// Mappings: ( ie. a -> b , c -> d , ... , g -> d)
MAPPINGPAIR_VECTOR: MAPPINGPAIR_VECTOR COMMA MAPPINGPAIR
      {
          if ($1->arrow != $3->arrow) {
             pmatcherror("Replace type mismatch in parallel rules.");
          }
         $1->push_back($3);
      }
| MAPPINGPAIR { $$ = $1; };
    
MAPPINGPAIR: EXPRESSION3 REPLACE_ARROW EXPRESSION3
{
    $$ = new PmatchMappingPairsContainer($2, $1, $3); }
| EXPRESSION3 REPLACE_ARROW EXPRESSION3 MARKUP_MARKER EXPRESSION3 {
    PmatchMarkupContainer * markup = new PmatchMarkupContainer($3, $5);
    $$ = new PmatchMappingPairsContainer($2, $1, markup); }
| EXPRESSION3 REPLACE_ARROW EXPRESSION3 MARKUP_MARKER {
    PmatchTransducerContainer * epsilon = new PmatchTransducerContainer(
        new HfstTransducer(hfst::internal_epsilon, format));
    PmatchMarkupContainer * markup = new PmatchMarkupContainer($3, epsilon);
    $$ = new PmatchMappingPairsContainer($2, $1, markup);
} | EXPRESSION3 REPLACE_ARROW MARKUP_MARKER EXPRESSION3 {
    PmatchMarkupContainer * markup = new PmatchMarkupContainer(new PmatchEpsilonArc, $4);
    $$ = new PmatchMappingPairsContainer($2, $1, markup);
} | LEFT_BRACKET_DOTTED RIGHT_BRACKET_DOTTED REPLACE_ARROW EXPRESSION3 {
    $$ = new PmatchMappingPairsContainer($3, new PmatchEpsilonArc, $4);
} | LEFT_BRACKET_DOTTED EXPRESSION3 RIGHT_BRACKET_DOTTED REPLACE_ARROW EXPRESSION3 {
    $$ = new PmatchMappingPairsContainer($4, $2, $5);
} | EXPRESSION3 REPLACE_ARROW LEFT_BRACKET_DOTTED RIGHT_BRACKET_DOTTED {
    $$ = new PmatchMappingPairsContainer($2, $1, new PmatchEpsilonArc);
} | EXPRESSION3 REPLACE_ARROW LEFT_BRACKET_DOTTED EXPRESSION3 RIGHT_BRACKET_DOTTED {
    $$ = new PmatchMappingPairsContainer($2, $1, $4); };

// Contexts: ( ie. || k _ f , ... , f _ s )
CONTEXTS_WITH_MARK: CONTEXT_MARK CONTEXTS_VECTOR
{
    $$ = new PmatchContextsContainer($1, $2);
};
CONTEXTS_VECTOR: CONTEXT
{
    $$ = new PmatchContextsContainer($1);
} | CONTEXTS_VECTOR COMMA CONTEXT {
    $1->push_back($3);
    $$ = $1;
};

CONTEXT:
EXPRESSION3 CENTER_MARKER EXPRESSION3  { $$ = new PmatchContextsContainer($1, $3); } |
EXPRESSION3 CENTER_MARKER { $$ = new PmatchContextsContainer($1, new PmatchEpsilonArc); } |
CENTER_MARKER EXPRESSION3 { $$ = new PmatchContextsContainer(new PmatchEpsilonArc, $2); } |
CENTER_MARKER { $$ = new PmatchContextsContainer(new PmatchEpsilonArc, new PmatchEpsilonArc);
};

CONTEXT_MARK:
REPLACE_CONTEXT_UU { $$ = REPL_UP; } |
REPLACE_CONTEXT_LU { $$ = REPL_RIGHT; } |
REPLACE_CONTEXT_UL { $$ = REPL_LEFT; } |
REPLACE_CONTEXT_LL { $$ = REPL_DOWN; };
     
REPLACE_ARROW:
REPLACE_RIGHT { $$ = E_REPLACE_RIGHT; } |
OPTIONAL_REPLACE_RIGHT { $$ = E_OPTIONAL_REPLACE_RIGHT; } |
RTL_LONGEST_MATCH { $$ = E_RTL_LONGEST_MATCH; } |
RTL_SHORTEST_MATCH { $$ = E_RTL_SHORTEST_MATCH; } |
LTR_LONGEST_MATCH { $$ = E_LTR_LONGEST_MATCH; } |
LTR_SHORTEST_MATCH { $$ = E_LTR_SHORTEST_MATCH; } |
REPLACE_LEFT { $$ =  E_REPLACE_LEFT; } |
OPTIONAL_REPLACE_LEFT { $$ = E_OPTIONAL_REPLACE_LEFT;
};

EXPRESSION4: EXPRESSION5 { } |
EXPRESSION4 SHUFFLE EXPRESSION5 { $$ = new PmatchBinaryOperation(Shuffle, $1, $3); } |
EXPRESSION4 BEFORE EXPRESSION5 { $$ = new PmatchBinaryOperation(Before, $1, $3);} |
EXPRESSION4 AFTER EXPRESSION5 { $$ = new PmatchBinaryOperation(After, $1, $3); };

EXPRESSION5: EXPRESSION6 { } |
EXPRESSION6 RIGHT_ARROW RESTR_CONTEXTS { $$ = new PmatchRestrictionContainer($1, $3); } |
EXPRESSION6 LEFT_ARROW EXPRESSION6 CENTER_MARKER EXPRESSION6 { pmatcherror("Left arrow with contexts not implemented"); } |
EXPRESSION6 LEFT_RIGHT_ARROW EXPRESSION6 CENTER_MARKER EXPRESSION6 { pmatcherror("Left-right arrow with contexts not implemented"); };

RESTR_CONTEXTS: RESTR_CONTEXT {
    $$ = new MappingPairVector();
    $$->push_back(*$1);
    delete $1;
} |
RESTR_CONTEXTS COMMA RESTR_CONTEXT {
     $1->push_back(*$3);
     $$ = $1;
     delete $3;
};

RESTR_CONTEXT:
EXPRESSION6 CENTER_MARKER EXPRESSION6 { $$ = new PmatchObjectPair($1, $3); } |
EXPRESSION6 CENTER_MARKER { $$ = new PmatchObjectPair($1, new PmatchEpsilonArc); } |
CENTER_MARKER EXPRESSION6 { $$ = new PmatchObjectPair(new PmatchEpsilonArc, $2); } |
CENTER_MARKER { $$ = new PmatchObjectPair(new PmatchEmpty, new PmatchEmpty); };

EXPRESSION6: EXPRESSION7 { } |
EXPRESSION6 UNION EXPRESSION7 { $$ = new PmatchBinaryOperation(Disjunct, $1, $3); } |
EXPRESSION6 INTERSECTION EXPRESSION7 { $$ = new PmatchBinaryOperation(Intersect, $1, $3); } |
EXPRESSION6 MINUS EXPRESSION7 { $$ = new PmatchBinaryOperation(Subtract, $1, $3); } |
EXPRESSION6 UPPER_MINUS EXPRESSION7 { $$ = new PmatchBinaryOperation(UpperSubtract, $1, $3); } |
EXPRESSION6 LOWER_MINUS EXPRESSION7 { $$ = new PmatchBinaryOperation(LowerSubtract, $1, $3); } |
EXPRESSION6 UPPER_PRIORITY_UNION EXPRESSION7 { $$ = new PmatchBinaryOperation(UpperPriorityUnion, $1, $3); } |
EXPRESSION6 LOWER_PRIORITY_UNION EXPRESSION7 { $$ = new PmatchBinaryOperation(LowerPriorityUnion, $1, $3); };

EXPRESSION7: EXPRESSION8 { } |
EXPRESSION7 EXPRESSION7 { $$ = new PmatchBinaryOperation(Concatenate, $1, $2); };

EXPRESSION8: EXPRESSION9 { } |
EXPRESSION8 IGNORING EXPRESSION9 { $$ = new PmatchBinaryOperation(InsertFreely, $1, $3); } |
EXPRESSION8 IGNORE_INTERNALLY EXPRESSION9 { $$ = new PmatchBinaryOperation(IgnoreInternally, $1, $3); } |
EXPRESSION8 LEFT_QUOTIENT EXPRESSION9 { pmatcherror("Left quotient not implemented"); };

EXPRESSION9: EXPRESSION10 { } |
COMPLEMENT EXPRESSION10 { $$ = new PmatchUnaryOperation(Complement, $2); } |
CONTAINMENT EXPRESSION10 { $$ = new PmatchUnaryOperation(Containment, $2); } |
CONTAINMENT_ONCE EXPRESSION10 { $$ = new PmatchUnaryOperation(ContainmentOnce, $2); } |
CONTAINMENT_OPT EXPRESSION10 { $$ = new PmatchUnaryOperation(ContainmentOptional, $2); };

EXPRESSION10: EXPRESSION11 { } |
EXPRESSION11 STAR { $$ = new PmatchUnaryOperation(RepeatStar, $1); } |
EXPRESSION11 PLUS { $$ = new PmatchUnaryOperation(RepeatPlus, $1); } |
EXPRESSION11 REVERSE { $$ = new PmatchUnaryOperation(Reverse, $1); } |
EXPRESSION11 INVERT { $$ = new PmatchUnaryOperation(Invert, $1); } |
EXPRESSION11 UPPER_PROJECT { $$ = new PmatchUnaryOperation(InputProject, $1); } |
EXPRESSION11 LOWER_PROJECT { $$ = new PmatchUnaryOperation(OutputProject, $1); } |
EXPRESSION11 CATENATE_N {
    $$ = new PmatchNumericOperation(RepeatN, $1);
    (dynamic_cast<PmatchNumericOperation *>($$))->values.push_back($2);
} |
EXPRESSION11 CATENATE_N_PLUS {
    $$ = new PmatchNumericOperation(RepeatNPlus, $1);
    (dynamic_cast<PmatchNumericOperation *>($$))->values.push_back($2 + 1);
} |
EXPRESSION11 CATENATE_N_MINUS {
    $$ = new PmatchNumericOperation(RepeatNMinus, $1);
    (dynamic_cast<PmatchNumericOperation *>($$))->values.push_back($2 - 1);
} |
EXPRESSION11 CATENATE_N_TO_K {
    $$ = new PmatchNumericOperation(RepeatNToK, $1);
    (dynamic_cast<PmatchNumericOperation *>($$))->values.push_back($2[0]);
    (dynamic_cast<PmatchNumericOperation *>($$))->values.push_back($2[1]);
    free($2);
};

EXPRESSION11: EXPRESSION12 { } |
TERM_COMPLEMENT EXPRESSION12 { $$ = new PmatchUnaryOperation(TermComplement, $2); };

EXPRESSION12: EXPRESSION13 { } |
LEFT_BRACKET EXPRESSION2 RIGHT_BRACKET { $$ = $2; } |
EXPRESSION12 PAIR_SEPARATOR EXPRESSION13 { $$ = new PmatchBinaryOperation(CrossProduct, $1, $3); } |
LEFT_PARENTHESIS EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(Optionalize, $2); } |
EXPRESSION12 WEIGHT { $$ = $1; $$->weight += $2; } |
LEFT_BRACKET EXPRESSION2 RIGHT_BRACKET TAG_LEFT SYMBOL RIGHT_PARENTHESIS {
    $$ = new PmatchUnaryOperation(AddDelimiters,
                                  new PmatchBinaryOperation(Concatenate, $2,
                                                            new PmatchString($5)));
    free($5); } |
LEFT_BRACKET EXPRESSION2 RIGHT_BRACKET TAG_LEFT QUOTED_LITERAL RIGHT_PARENTHESIS {
    $$ = new PmatchUnaryOperation(AddDelimiters,
                                  new PmatchBinaryOperation(Concatenate, $2,
                                                            new PmatchString($5)));
    free($5); };

EXPRESSION13:
QUOTED_LITERAL { $$ = new PmatchString(std::string($1)); free($1); } |
EPSILON_TOKEN { $$ = new PmatchString(hfst::internal_epsilon); } |
BOUNDARY_MARKER { $$ = new PmatchString("@BOUNDARY@"); } |
LIT_LEFT SYMBOL RIGHT_PARENTHESIS { $$ = new PmatchString(std::string($2)); free($2); } |
CURLY_LITERAL {
    PmatchString * retval = new PmatchString(std::string($1));
    retval->multichar = true;
    $$ = retval; free($1);
} |
ANY_TOKEN { $$ = new PmatchQuestionMark; } |
EXPLODE { } |
IMPLODE { } |
FUNCALL { } |
//MAP { } |
INSERTION { } |
ALPHA { $$ = new PmatchAcceptor(Alpha); } |
LOWERALPHA { $$ = new PmatchAcceptor(LowercaseAlpha); } |
UPPERALPHA { $$ = new PmatchAcceptor(UppercaseAlpha); } |
NUM { $$ = new PmatchAcceptor(Numeral); } |
PUNCT { $$ = new PmatchAcceptor(Punctuation); } |
WHITESPACE { $$ = new PmatchAcceptor(Whitespace); } |
CAP_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(Cap, $2); } |
OPTCAP_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(OptCap, $2); } |
TOLOWER_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(ToLower, $2); } |
TOUPPER_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(ToUpper, $2); } |
OPT_TOLOWER_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(OptToLower, $2); } |
OPT_TOUPPER_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(OptToUpper, $2); } |
ANY_CASE_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(AnyCase, $2); } |
DEFINE_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(AddDelimiters, $2); } |
READ_FROM { } |
CHARACTER_RANGE { $$ = $1; } |
LST_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(MakeList, $2); } |
EXC_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(MakeExcList, $2); } |
INTERPOLATE_LEFT FUNCALL_ARGLIST RIGHT_PARENTHESIS { $$ = new PmatchBuiltinFunction(Interpolate, $2); } |
SIGMA_LEFT EXPRESSION2 RIGHT_PARENTHESIS { $$ = new PmatchUnaryOperation(MakeSigma, $2); } |
COUNTER_LEFT SYMBOL RIGHT_PARENTHESIS { $$ = hfst::pmatch::make_counter($2); free($2); } |
ENDTAG { $$ = $1; hfst::pmatch::need_delimiters = true; } |
CONTEXT_CONDITION { $$ = $1; hfst::pmatch::need_delimiters = true; } |
SYMBOL {
    std::string sym($1);
    free($1);
    if (sym.size() == 0) {
        $$ = new PmatchEmpty;
    } else {
        $$ = new PmatchSymbol(sym);
    }
};

EXPLODE: EXPLODE_LEFT CONCATENATED_STRING_LIST RIGHT_PARENTHESIS
{
    $$ = new PmatchString($2, true);
    free($2);
};

IMPLODE: IMPLODE_LEFT CONCATENATED_STRING_LIST RIGHT_PARENTHESIS
{
    $$ = new PmatchString($2);
    free($2);
};

CONCATENATED_STRING_LIST: SYMBOL
{ $$ = $1; } |
SYMBOL COMMA CONCATENATED_STRING_LIST
{
    $$ = static_cast<char*>(malloc(sizeof(char)*(strlen($1) + strlen($3)+1)));
    strcpy($$, $1);
    strcat($$, $3);
    free($1); free($3);
};

FUNCALL: SYMBOL_WITH_LEFT_PAREN FUNCALL_ARGLIST RIGHT_PARENTHESIS
{
    std::string sym($1);
    if (function_names.count($1) == 0) {
        std::stringstream ss;
        ss << "Function " << sym << " hasn't been defined\n";
        pmatcherror(ss.str().c_str());
        $$ = new PmatchString("");
    } else {
        $$ = new PmatchFuncall(
            $2,
            dynamic_cast<PmatchFunction *>(symbol_from_global_context(sym)));
    }
    used_definitions.insert(sym);
    free($1);
};

FUNCALL_ARGLIST: EXPRESSION2 COMMA FUNCALL_ARGLIST {
$$ = $3; $$->push_back($1); } |
EXPRESSION2 { $$ = new std::vector<PmatchObject *>(1, $1); } |
{ $$ = new std::vector<PmatchObject *>; };

INSERTION: INS_LEFT SYMBOL RIGHT_PARENTHESIS {
    if (!hfst::pmatch::flatten) {
        if(hfst::pmatch::definitions.count($2) == 0) {
            hfst::pmatch::unsatisfied_insertions.insert($2);
        }
        $$ = new PmatchString(hfst::pmatch::get_Ins_transition($2));
        hfst::pmatch::inserted_names.insert($2);
        hfst::pmatch::used_definitions.insert($2);
    } else if(hfst::pmatch::definitions.count($2) != 0) {
        $$ = hfst::pmatch::definitions[$2];
    } else {
        $$ = new PmatchEmpty;
        std::stringstream ss;
        ss << "Insertion of " << $2 << " on line " << pmatchlineno << " is undefined and --flatten is in use\n";
        pmatcherror(ss.str().c_str());
    }
    free($2);
};

ENDTAG: ENDTAG_LEFT SYMBOL RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::make_end_tag($2);
    free($2);
} | ENDTAG_LEFT QUOTED_LITERAL RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::make_end_tag($2);
    free($2);
};

READ_FROM: READ_BIN {
    HfstTransducer * read;
    try {
        hfst::HfstInputStream instream($1);
        read = new HfstTransducer(instream);
        instream.close();
    } catch(HfstException) {
        std::string ermsg =
            std::string("Couldn't read transducer from ") +
            std::string($1);
        free($1);
        pmatcherror(ermsg.c_str());
    }
    if (read->get_type() != hfst::pmatch::format) {
        read->convert(hfst::pmatch::format);
    }
    $$ = new PmatchTransducerContainer(read);
    free($1);
} | READ_TEXT {
    $$ = new PmatchTransducerContainer(hfst::pmatch::read_text($1));
    free($1);
} | READ_SPACED {
    FILE * f = NULL;
    f = fopen($1, "r");
    if (f == NULL) {
        pmatcherror("File cannot be opened.\n");
    } else {
        HfstTokenizer tok;
        HfstBasicTransducer tmp;
        char line [1000];
        while( fgets(line, 1000, f) != NULL )
        {
            hfst::pmatch::strip_newline(line);
            StringPairVector spv = HfstTokenizer::tokenize_space_separated(line);
            tmp.disjunct(spv, 0);
        }
        fclose(f);
        HfstTransducer * t = new HfstTransducer(tmp, hfst::pmatch::format); 
        t->minimize();
        $$ = new PmatchTransducerContainer(t);
    }
} | READ_PROLOG {
    FILE * f = NULL;
    f = fopen($1, "r");
    if (f == NULL) {
        pmatcherror("File cannot be opened.\n");
    } else {
        try {
            unsigned int linecount = 0;
            HfstBasicTransducer tmp = HfstBasicTransducer::read_in_prolog_format(f, linecount);
            fclose(f);
            HfstTransducer * t = new HfstTransducer(tmp, hfst::pmatch::format);
            t->minimize();
            $$ = new PmatchTransducerContainer(t);
        }
        catch (const HfstException & e) {
            (void) e;
            fclose(f);
            pmatcherror("Error reading prolog file.\n");
        }
    }
} | READ_LEXC {
    $$ = new PmatchTransducerContainer(hfst::HfstTransducer::read_lexc_ptr($1, format, hfst::pmatch::verbose));
    free($1);
} | READ_RE {
    std::string regex;
    std::string tmp;
    std::ifstream regexfile($1);
    if (regexfile.is_open()) {
        while (getline(regexfile, tmp)) {
            regex.append(tmp);
        }
    }
    if (regex.size() == 0) {
        std::stringstream err;
        err << "Failed to read regex from " << $1 << ".\n";
        pmatcherror(err.str().c_str());
    }
    hfst::xre::XreCompiler xre_compiler;
    $$ = new PmatchTransducerContainer(xre_compiler.compile(regex));
    };

CONTEXT_CONDITION:
PMATCH_CONTEXT { } |
PMATCH_OR_CONTEXT { } |
PMATCH_AND_CONTEXT { };

PMATCH_CONTEXT:
PMATCH_RIGHT_CONTEXT { } |
PMATCH_NEGATIVE_RIGHT_CONTEXT { } |
PMATCH_LEFT_CONTEXT { } |
PMATCH_NEGATIVE_LEFT_CONTEXT { };

PMATCH_OR_CONTEXT: OR_LEFT PMATCH_CONTEXTS RIGHT_PARENTHESIS
{
    $$ = NULL;
    for (std::vector<PmatchObject *>::reverse_iterator it = $2->rbegin();
         it != $2->rend(); ++it) {
        if ($$ == NULL) {
            $$ = *it;
        } else {
            PmatchObject * tmp = $$;
            $$ = new PmatchBinaryOperation(Disjunct, tmp, *it);
        }
    }
    delete $2;
    // Zero the counter for making minimization
    // guards for disjuncted negative contexts
    hfst::pmatch::zero_minimization_guard();
};

PMATCH_AND_CONTEXT: AND_LEFT PMATCH_CONTEXTS RIGHT_PARENTHESIS
{
    $$ = NULL;
    for (std::vector<PmatchObject *>::reverse_iterator it = $2->rbegin();
         it != $2->rend(); ++it) {
        if ($$ = NULL) {
            $$ = *it;
        } else {
            PmatchObject * tmp = $$;
            $$ = new PmatchBinaryOperation(Concatenate, tmp, *it);
        }
    }
    delete $2;
};

PMATCH_CONTEXTS:
PMATCH_CONTEXT {
    $$ = new std::vector<PmatchObject *>(1, $1);
} |
PMATCH_CONTEXT COMMA PMATCH_CONTEXTS {
    $3->push_back($1);
    $$ = $3;
};

PMATCH_RIGHT_CONTEXT: RC_LEFT EXPRESSION2 RIGHT_PARENTHESIS {
    $$ = new PmatchBinaryOperation(Concatenate, make_rc_entry(),
                                   new PmatchBinaryOperation(
                                       Concatenate, $2, make_rc_exit()));
};

PMATCH_NEGATIVE_RIGHT_CONTEXT: NRC_LEFT EXPRESSION2 RIGHT_PARENTHESIS {
    $$ = new PmatchBinaryOperation(
        Concatenate, make_minimization_guard(),
        new PmatchBinaryOperation(
            Disjunct, make_passthrough(),
            new PmatchBinaryOperation(
                Concatenate, make_nrc_entry(),
                new PmatchBinaryOperation(Concatenate, $2, make_nrc_exit()))));
};

PMATCH_LEFT_CONTEXT: LC_LEFT EXPRESSION2 RIGHT_PARENTHESIS {
    $$ = new PmatchBinaryOperation(
        Concatenate, make_lc_entry(),
        new PmatchBinaryOperation(
            Concatenate, new PmatchUnaryOperation(
                Reverse, $2), make_lc_exit()));
};

PMATCH_NEGATIVE_LEFT_CONTEXT: NLC_LEFT EXPRESSION2 RIGHT_PARENTHESIS {
    $$ = new PmatchBinaryOperation(
        Concatenate, make_minimization_guard(),
        new PmatchBinaryOperation(
            Disjunct, make_passthrough(),
            new PmatchBinaryOperation(
                Concatenate, make_nlc_entry(),
                new PmatchBinaryOperation(Concatenate, new PmatchUnaryOperation(
                                              Reverse, $2), make_nlc_exit()))));
};


// MAP: MAP_LEFT SYMBOL COMMA READ_TEXT RIGHT_PARENTHESIS {
//     if (hfst::pmatch::functions.count($2) == 0) {
//         std::string errstring = "Function not defined: " + std::string($2);
//         pmatcherror(errstring.c_str());
//     }
//     std::vector<string> & callee_args = hfst::pmatch::functions[$2].args;
//     std::vector<std::vector<std::string> > caller_strings =
//         hfst::pmatch::read_args($4, callee_args.size());
//     std::map<std::string, HfstTransducer*> caller_args;
//     HfstTokenizer tok;
//     $$ = new HfstTransducer(hfst::pmatch::format);
//     for (std::vector<std::vector<std::string> >::iterator it =
//              caller_strings.begin(); it != caller_strings.end(); ++it) {
//         for (int i = 0; i < it->size(); ++i) {
//             caller_args[callee_args[i]] = new HfstTransducer(it->at(i), tok, hfst::pmatch::format);
//         }
//         $$->disjunct(*hfst::pmatch::functions[$2].evaluate(caller_args));
//         // Clean up the string transducers we allocated each time 
//         for (std::map<std::string, HfstTransducer *>::iterator it = caller_args.begin();
//              it != caller_args.end(); ++it) {
//             delete it->second;
//         }
//         caller_args.clear();
//     }
//     $$->minimize();
// };

%%
