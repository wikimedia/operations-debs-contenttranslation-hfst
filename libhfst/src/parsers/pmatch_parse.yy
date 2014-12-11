%{

#define YYDEBUG 0

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <sstream>
    
#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstXeroxRules.h"

    using namespace hfst;
    using hfst::HfstTransducer;
    using namespace hfst::xeroxRules;
    using namespace hfst::implementations;

#include "pmatch_utils.h"
    using hfst::pmatch::PmatchAstNode;
    
    extern void pmatcherror(const char * text);
    extern int pmatchlex();
    extern int pmatchlineno;

    %}

%name-prefix="pmatch"
     %error-verbose
//     %debug

           



     %union {




         int value;
         int* values;
         double weight;
         char* label;
         hfst::HfstTransducer* transducer;
         hfst::HfstTransducerPair* transducerPair;
         hfst::HfstTransducerPairVector* transducerPairVector;
         hfst::HfstTransducerVector* transducerVector;
         std::pair<std::string, hfst::HfstTransducer*>* transducerDefinition;
         std::map<std::string, hfst::HfstTransducer>* transducerDefinitions;
         hfst::pmatch::PmatchAstNode* ast_node;
         std::vector<std::string>* string_vector;
    
         std::pair<hfst::xeroxRules::ReplaceArrow, std::vector<hfst::xeroxRules::Rule> >* replaceRuleVectorWithArrow;
         std::pair< hfst::xeroxRules::ReplaceArrow, hfst::xeroxRules::Rule>* replaceRuleWithArrow;   
         std::pair< hfst::xeroxRules::ReplaceArrow, hfst::HfstTransducerPairVector>* mappingVectorWithArrow;
         std::pair< hfst::xeroxRules::ReplaceArrow, hfst::HfstTransducerPair>* mappingWithArrow;
    
   
         std::pair<hfst::xeroxRules::ReplaceType, hfst::HfstTransducerPairVector>* contextWithMark;
   
         hfst::xeroxRules::ReplaceType replType;
         hfst::xeroxRules::ReplaceArrow replaceArrow; 
    
     
     }

/* some parts have been ripped from foma’s parser now */

%type <replaceArrow> REPLACE_ARROW

%type <transducerDefinitions> PMATCH
%type <transducerDefinition> DEFINITION BINDING FUNCTION
%type <transducer> REGEXP1 REGEXP2 REGEXP4 REGEXP5 REGEXP6 REGEXP7
REGEXP8 REGEXP9 REGEXP10 REGEXP11 REGEXP12 LABEL_PAIR
REPLACE REGEXP3 FUNCALL MAP FUNCALL_ARG
%type <label> LABEL
%type <ast_node> FUNCBODY1 FUNCBODY2 FUNCBODY3 FUNCBODY4 FUNCBODY5 FUNCBODY6 FUNC_LABEL_PAIR
%type <string_vector> ARGLIST
%type <transducerVector> FUNCALL_ARGLIST

%type <replaceRuleVectorWithArrow> PARALLEL_RULES
%type <replaceRuleWithArrow>  RULE
%type <mappingVectorWithArrow> MAPPINGPAIR_VECTOR
%type <mappingWithArrow> MAPPINGPAIR

%type <contextWithMark> CONTEXTS_WITH_MARK
%type <transducerPairVector> CONTEXTS_VECTOR
%type <transducerPair> CONTEXT
%type <replType>  CONTEXT_MARK

%type <transducer> OPTCAP TOLOWER TOUPPER INSERT ANONYMOUS_DEFINITION RIGHT_CONTEXT LEFT_CONTEXT NEGATIVE_RIGHT_CONTEXT NEGATIVE_LEFT_CONTEXT P_CONTEXT CONTEXT_CONDITION OR_CONTEXT AND_CONTEXT
%type <transducerVector> CONTEXT_CONDITIONS
%type <ast_node> FUN_RIGHT_CONTEXT FUN_LEFT_CONTEXT FUN_NEGATIVE_RIGHT_CONTEXT FUN_NEGATIVE_LEFT_CONTEXT
%type <ast_node> FUN_OPTCAP FUN_TOLOWER FUN_TOUPPER

%nonassoc <weight> WEIGHT END_OF_WEIGHTED_EXPRESSION
%nonassoc <label> QUOTED_LITERAL CURLY_LITERAL SYMBOL SYMBOL_WITH_LEFT_PAREN

%left  CROSS_PRODUCT COMPOSITION LENIENT_COMPOSITION INTERSECTION
%left  CENTER_MARKER MARKUP_MARKER
%left  SHUFFLE
%right LEFT_RESTRICTION LEFT_ARROW RIGHT_ARROW LEFT_RIGHT_ARROW
%left  REPLACE_RIGHT REPLACE_LEFT
OPTIONAL_REPLACE_RIGHT OPTIONAL_REPLACE_LEFT
REPLACE_LEFT_RIGHT OPTIONAL_REPLACE_LEFT_RIGHT
RTL_LONGEST_MATCH RTL_SHORTEST_MATCH
LTR_LONGEST_MATCH LTR_SHORTEST_MATCH 
      
%right REPLACE_CONTEXT_UU REPLACE_CONTEXT_LU 
REPLACE_CONTEXT_UL REPLACE_CONTEXT_LL

%left  UNION MINUS UPPER_MINUS LOWER_MINUS UPPER_PRIORITY_UNION
LOWER_PRIORITY_UNION

%left  IGNORING IGNORE_INTERNALLY LEFT_QUOTIENT


%left  COMMACOMMA

 
          
%left  COMMA 
       
%left  BEFORE AFTER


%nonassoc SUBSTITUTE_LEFT TERM_COMPLEMENT
%nonassoc COMPLEMENT CONTAINMENT CONTAINMENT_ONCE CONTAINMENT_OPT
%nonassoc REVERSE INVERT UPPER LOWER STAR PLUS
%nonassoc <values> CATENATE_N_TO_K
%nonassoc <value> CATENATE_N CATENATE_N_PLUS CATENATE_N_MINUS

%nonassoc <label> READ_BIN READ_TEXT READ_SPACED READ_PROLOG READ_RE READ_LEXC
%token LEFT_BRACKET RIGHT_BRACKET LEFT_PARENTHESIS RIGHT_PARENTHESIS
LEFT_BRACKET_DOTTED RIGHT_BRACKET_DOTTED
%token END_OF_EXPRESSION
%token PAIR_SEPARATOR PAIR_SEPARATOR_SOLE 
PAIR_SEPARATOR_WO_RIGHT PAIR_SEPARATOR_WO_LEFT
%token EPSILON_TOKEN ANY_TOKEN BOUNDARY_MARKER
%token LEXER_ERROR

%nonassoc DEFINE REGEX DEFINS DEFFUN ALPHA LOWERALPHA UPPERALPHA NUM PUNCT WHITESPACE
OPTCAP_LEFT TOLOWER_LEFT TOUPPER_LEFT INS_LEFT DEFINE_LEFT ENDTAG_LEFT LC_LEFT
RC_LEFT NLC_LEFT NRC_LEFT MAP_LEFT SYM_LEFT OR_LEFT AND_LEFT
%%




PMATCH: DEFINITION {
    if ($1->first.compare("@_PMATCH_DUMMY_@")) {
        if(hfst::pmatch::definitions.count($1->first) != 0) {
            std::stringstream warning;
            warning << "definition of " << $1->first << " on line "
                    << pmatchlineno << " shadowed by earlier definition\n";
            hfst::pmatch::warn(warning.str());
        }
         hfst::pmatch::definitions.insert(*$1);
         if (hfst::pmatch::verbose) {
             std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(2);
             double duration = (clock() - hfst::pmatch::timer) /
                 (double) CLOCKS_PER_SEC;
             hfst::pmatch::timer = clock();
             std::cerr << "compiled " << $1->first << " in " << duration << " seconds\n";
             hfst::pmatch::print_size_info($1->second);
             std::cerr << std::endl;
         }
    }
    delete $1;
 } |
 PMATCH DEFINITION {
     if ($2->first.compare("@_PMATCH_DUMMY_@")) {
         if(hfst::pmatch::definitions.count($2->first) != 0) {
             std::stringstream warning;
             warning << "definition of " << $2->first << " on line "
                     << pmatchlineno << " shadowed by earlier definition\n";
             hfst::pmatch::warn(warning.str());
         }
         hfst::pmatch::definitions.insert(*$2);
         if (hfst::pmatch::verbose) {
             std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(2);
             double duration = (clock() - hfst::pmatch::timer) /
                 (double) CLOCKS_PER_SEC;
             hfst::pmatch::timer = clock();
             std::cerr << "compiled " << $2->first << " in " << duration << " seconds\n";
             hfst::pmatch::print_size_info($2->second);
             std::cerr << std::endl;
         }
     }
     delete $2;
 }
;

DEFINITION: DEFINE BINDING { $$ = $2; }
| DEFINS BINDING {
    char * Ins_trans = hfst::pmatch::get_Ins_transition($2->first.c_str());
    HfstTransducer * ins_t = new HfstTransducer(
        Ins_trans, Ins_trans, hfst::pmatch::format);
    ins_t->set_name($2->first);
    free(Ins_trans);
    hfst::pmatch::def_insed_transducers[$2->first] = ins_t;
    $$ = $2;
 }
| REGEX REGEXP1 {
    $2->set_name("TOP");
    if (hfst::pmatch::need_delimiters) {
        $2 = hfst::pmatch::add_pmatch_delimiters($2);
    }
    hfst::pmatch::need_delimiters = false;
    $2->minimize();
    $$ = new std::pair<std::string, hfst::HfstTransducer*>("TOP", $2);
 }
| DEFFUN FUNCTION { $$ = $2; }
;

BINDING: SYMBOL REGEXP1 {
    if (hfst::pmatch::need_delimiters) {
        $2 = hfst::pmatch::add_pmatch_delimiters($2);
    }
    hfst::pmatch::need_delimiters = false;
    $2->set_name($1);
    $2->minimize();
    $$ = new std::pair<std::string, hfst::HfstTransducer*>($1, $2);
 }
;

FUNCTION: SYMBOL_WITH_LEFT_PAREN ARGLIST RIGHT_PARENTHESIS FUNCBODY1 END_OF_EXPRESSION {
    PmatchAstNode * function_body;
    if (hfst::pmatch::need_delimiters) {
        function_body = new PmatchAstNode($4, hfst::pmatch::AstAddDelimiters);
    } else {
        function_body = $4;
    }
    hfst::pmatch::need_delimiters = false;
    hfst::pmatch::PmatchFunction fun(* $2, function_body);
    if(hfst::pmatch::functions.count($1) != 0) {
        std::stringstream warning;
        warning << "definition of function" << $1 << " on line "
                << pmatchlineno << " shadowed by earlier definition\n";
        hfst::pmatch::warn(warning.str());
    }
    hfst::pmatch::functions[$1] = fun;
    // Pass a dummy transducer, since function registration is separate
    HfstTransducer * dummy = new HfstTransducer(hfst::pmatch::format);
    dummy->set_name("@_PMATCH_DUMMY_@");
    $$ = new std::pair<std::string, hfst::HfstTransducer*>("@_PMATCH_DUMMY_@", dummy);
    if (hfst::pmatch::verbose) {
        std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(2);
        double duration = (clock() - hfst::pmatch::timer) /
            (double) CLOCKS_PER_SEC;
        hfst::pmatch::timer = clock();
        std::cerr << "defined function" << $1 << " in " << duration << " seconds\n";
        std::cerr << std::endl;
    }
 }
;

ARGLIST: ARGS {
    $$ = new std::vector<std::string>(hfst::pmatch::tmp_collected_funargs);
    hfst::pmatch::tmp_collected_funargs.clear();
 }
|
{
    $$ = new std::vector<std::string>();
    hfst::pmatch::tmp_collected_funargs.clear();
};

ARGS: SYMBOL {
    hfst::pmatch::tmp_collected_funargs.push_back($1);
 };
| SYMBOL COMMA ARGS {
    hfst::pmatch::tmp_collected_funargs.push_back($1);
 }
;

REGEXP1: REGEXP2 END_OF_EXPRESSION { }
| REGEXP2 END_OF_WEIGHTED_EXPRESSION {
    $1->set_final_weights($2);
    $$ = $1;
 }
// | REGEXP2 error {
//     $$ = $1;
//     std::cerr << "pmatch: skipping\n";
//     yyerrok;
//     yyclearin;
//  }
;

FUNCBODY1: FUNCBODY2 { }
| FUNCBODY1 COMPOSITION FUNCBODY2 {
    $$ = new PmatchAstNode($1, $3, hfst::pmatch::AstCompose);
 }
| FUNCBODY1 CROSS_PRODUCT FUNCBODY2 {
    $$ = new PmatchAstNode($1, $3, hfst::pmatch::AstCrossProduct);
 }
| FUNCBODY1 LENIENT_COMPOSITION FUNCBODY2 {
    $$ = new PmatchAstNode($1, $3, hfst::pmatch::AstLenientCompose);
 }
| FUNCBODY1 FUN_RIGHT_CONTEXT {
     $$ = new PmatchAstNode($1, $2, hfst::pmatch::AstConcatenate);
 }
| FUNCBODY1 FUN_LEFT_CONTEXT {
    $$ = new PmatchAstNode($2, $1, hfst::pmatch::AstConcatenate);
 }
| FUNCBODY1 FUN_NEGATIVE_RIGHT_CONTEXT {
    $$ = new PmatchAstNode($1, $2, hfst::pmatch::AstConcatenate);
 }
| FUNCBODY1 FUN_NEGATIVE_LEFT_CONTEXT {
    $$ = new PmatchAstNode($2, $1, hfst::pmatch::AstConcatenate);
 }
;

FUNCBODY2: FUNCBODY3 { }
| FUNCBODY2 UNION FUNCBODY3 {
    $$ = new PmatchAstNode($1, $3, hfst::pmatch::AstDisjunct);
 }
| FUNCBODY2 INTERSECTION FUNCBODY3 {
    $$ = new PmatchAstNode($1, $3, hfst::pmatch::AstIntersect);
 }
| FUNCBODY2 MINUS FUNCBODY3 {
    $$ = new PmatchAstNode($1, $3, hfst::pmatch::AstSubtract);
 }
// | REGEXP5 UPPER_MINUS REGEXP6 {
//     pmatcherror("No upper minus");
//     $$ = $1;
//     delete $3;
//  }
// | REGEXP5 LOWER_MINUS REGEXP6 {
//     pmatcherror("No lower minus");
//     $$ = $1;
//     delete $3;
//  }
// | REGEXP5 UPPER_PRIORITY_UNION REGEXP6 {
//     pmatcherror("No upper priority union");
//     $$ = $1;
//     delete $3;
//  }
// | REGEXP5 LOWER_PRIORITY_UNION REGEXP6 {
//     pmatcherror("No lower priority union");
//     $$ = $1;
//     delete $3;
//  }
;



FUNCBODY3: FUNCBODY4 { }
| FUNCBODY3 FUNCBODY4 {
    $$ = new PmatchAstNode($1, $2, hfst::pmatch::AstConcatenate);
 };

FUNCBODY4: FUNCBODY5
| LEFT_BRACKET FUNCBODY1 RIGHT_BRACKET {
    $$ = $2;
 }
| LEFT_PARENTHESIS FUNCBODY1 RIGHT_PARENTHESIS {
    $$ = new PmatchAstNode($2, hfst::pmatch::AstOptionalize);
 }
| ALPHA {
    $$ = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_alpha_acceptor);
 }
| LOWERALPHA {
    $$ = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_lowercase_acceptor);
 }
| UPPERALPHA {
    $$ = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_uppercase_acceptor);
 }
| NUM {
    $$ = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_numeral_acceptor);
 }
| PUNCT {
    $$ = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_punct_acceptor);
 }
| WHITESPACE {
    $$ = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_whitespace_acceptor);
 }
| INSERT { $$ = new PmatchAstNode($1); }
| FUN_OPTCAP { }
| FUN_TOUPPER { }
| FUN_TOLOWER { }

;

FUNCBODY5: FUNCBODY6 { }
| FUNCBODY5 STAR {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstRepeatStar);
 }
| FUNCBODY5 PLUS {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstRepeatPlus);
 }
| FUNCBODY5 REVERSE {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstReverse);
 }
| FUNCBODY5 INVERT {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstInvert);
 }
| FUNCBODY5 UPPER {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstInputProject);
  }
| FUNCBODY5 LOWER {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstOutputProject);
 }
| FUNCBODY5 CATENATE_N {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstRepeatN);
    $$->push_numeric_arg($2);
 }
| FUNCBODY5 CATENATE_N_PLUS {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstRepeatNPlus);
    $$->push_numeric_arg($2 + 1);
 }
| FUNCBODY5 CATENATE_N_MINUS {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstRepeatNMinus);
    $$->push_numeric_arg($2 - 1);
 }
| FUNCBODY5 CATENATE_N_TO_K {
    $$ = new PmatchAstNode($1, hfst::pmatch::AstRepeatNToK);
    $$->push_numeric_arg($2[0]);
    $$->push_numeric_arg($2[1]);
    free($2);
 }
;



FUNCBODY6: FUNC_LABEL_PAIR { }
| SYMBOL {
    $$ = new PmatchAstNode($1);
    free($1);
 }
| BOUNDARY_MARKER {
    $$ = new PmatchAstNode(new HfstTransducer("@BOUNDARY@", "@BOUNDARY@", hfst::pmatch::format));
  }
| ENDTAG_LEFT SYMBOL RIGHT_PARENTHESIS {
    $$ = new PmatchAstNode(hfst::pmatch::make_end_tag($2));
    hfst::pmatch::need_delimiters = true;
    free($2);
 }
| ENDTAG_LEFT QUOTED_LITERAL RIGHT_PARENTHESIS {
    $$ = new PmatchAstNode(hfst::pmatch::make_end_tag($2));
    hfst::pmatch::need_delimiters = true;
    free($2);
 }
| READ_BIN {
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
    $$ = new PmatchAstNode(read);
    free($1);
  }
| READ_TEXT {
    $$ = new PmatchAstNode(hfst::pmatch::read_text($1));
    free($1);
  }
| READ_LEXC {
    $$ = new PmatchAstNode(hfst::HfstTransducer::read_lexc_ptr($1, hfst::TROPICAL_OPENFST_TYPE, hfst::pmatch::verbose));
    free($1);
  }
;

 FUNC_LABEL_PAIR:
LABEL {
    $$ = new PmatchAstNode(new HfstTransducer($1, hfst::pmatch::format));
    free($1);
} |
CURLY_LITERAL {
    HfstTokenizer tok;
    $$ = new PmatchAstNode(new HfstTransducer($1, tok, hfst::pmatch::format));
    free($1);
}
;


REGEXP2: REPLACE
{ }
| REGEXP2 COMPOSITION REPLACE {
       
    $$ = & $1->compose(*$3);
    delete $3;
 }
| REGEXP2 CROSS_PRODUCT REPLACE {
    $$ = & $1->cross_product(*$3);
    delete $3;
 }
| REGEXP2 LENIENT_COMPOSITION REPLACE {
    $$ = $1;
    delete $3;
 }

;

////////////////////////////
// Replace operators
///////////////////////////

REPLACE : REGEXP3 {}
|  PARALLEL_RULES
{
    // std::cerr << "replace:parallel_rules"<< std::endl;        
    switch ( $1->first )
    {
    case E_REPLACE_RIGHT:
        $$ = new HfstTransducer( replace( $1->second, false ) );
        break;
    case E_OPTIONAL_REPLACE_RIGHT:
        $$ = new HfstTransducer( replace( $1->second, true ) );
        break;
    case E_REPLACE_LEFT:
        $$ = new HfstTransducer( replace_left( $1->second, false ) );
        break;
    case E_OPTIONAL_REPLACE_LEFT:
        $$ = new HfstTransducer( replace_left( $1->second, true ) );
        break;
    case E_RTL_LONGEST_MATCH:
        $$ = new HfstTransducer( replace_rightmost_longest_match( $1->second ) );
        break;
    case E_RTL_SHORTEST_MATCH:
        $$ = new HfstTransducer( replace_rightmost_shortest_match($1->second) );
        break;
    case E_LTR_LONGEST_MATCH:
        $$ = new HfstTransducer( replace_leftmost_longest_match( $1->second ) );
        break;
    case E_LTR_SHORTEST_MATCH:
        $$ = new HfstTransducer( replace_leftmost_shortest_match( $1->second ) );
        break;
    }
       
    delete $1;
}
;

PARALLEL_RULES: RULE
{
    //   std::cerr << "parallel_rules:rule"<< std::endl;        
    std::vector<Rule> * ruleVector = new std::vector<Rule>();
    ruleVector->push_back($1->second);
            
    $$ =  new std::pair< ReplaceArrow, std::vector<Rule> > ($1->first, *ruleVector);
    delete $1;
}
| PARALLEL_RULES COMMACOMMA RULE
{
    // std::cerr << "parallel_rules: parallel_rules ,, rule"<< std::endl;      
    Rule tmpRule($3->second);
    $1->second.push_back(tmpRule);
    $$ =  new std::pair< ReplaceArrow, std::vector<Rule> > ($3->first, $1->second);
    delete $3;
}
;

RULE: MAPPINGPAIR_VECTOR
  {
     // std::cerr << "rule: mapping_vector"<< std::endl;      
    // HfstTransducer allMappingsDisjuncted = disjunctVectorMembers($1->second);
     
     Rule rule( $1->second );;
     $$ =  new std::pair< ReplaceArrow, Rule> ($1->first, rule);
     delete $1;
  }
  | MAPPINGPAIR_VECTOR CONTEXTS_WITH_MARK
  {
    // std::cerr << "rule: mapping_vector contextsWM"<< std::endl;      
 //   HfstTransducer allMappingsDisjuncted = disjunctVectorMembers($1->second);
    
    Rule rule( $1->second, $2->second, $2->first );
    $$ =  new std::pair< ReplaceArrow, Rule> ($1->first, rule);
    delete $1, $2;
  }
  ;
;
      
// Mappings: ( ie. a -> b , c -> d , ... , g -> d)
MAPPINGPAIR_VECTOR: MAPPINGPAIR_VECTOR COMMA MAPPINGPAIR
{
    // std::cerr << "mapping_vector : mapping_vector comma mapping"<< std::endl;      
    // check if new Arrow is the same as the first one

    if ($1->first != $3->first)
    {
        pmatcherror("Replace arrows should be the same. Calculated as if all replacements had the fist arrow.");
        //exit(1);
    }

	$1->second.push_back($3->second);
    $$ =  new std::pair< ReplaceArrow, HfstTransducerPairVector> ($1->first, $1->second);
    delete $3;
            
}
      
| MAPPINGPAIR
{
    // std::cerr << "mapping_vector : mapping"<< std::endl;      
	 HfstTransducerPairVector * mappingPairVector = new HfstTransducerPairVector();
	 mappingPairVector->push_back( $1->second );
	 $$ =  new std::pair< ReplaceArrow, HfstTransducerPairVector> ($1->first, * mappingPairVector);
	 delete $1; 
}
     
;

    
MAPPINGPAIR: REPLACE REPLACE_ARROW REPLACE
{
        // std::cerr << "mapping : r2 arrow r2"<< std::endl;      

          HfstTransducerPair mappingPair(*$1, *$3);
          $$ =  new std::pair< ReplaceArrow, HfstTransducerPair> ($2, mappingPair);

          delete $1, $3;
      }
  	| REPLACE REPLACE_ARROW REPLACE MARKUP_MARKER REPLACE
      {
      
          HfstTransducerPair marks(*$3, *$5);
          HfstTransducerPair tmpMappingPair(*$1, HfstTransducer(hfst::pmatch::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
          
          $$ =  new std::pair< ReplaceArrow, HfstTransducerPair> ($2, mappingPair);
         delete $1, $3, $5;
      }
      | REPLACE REPLACE_ARROW REPLACE MARKUP_MARKER
      {
   
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
          HfstTransducerPair marks(*$3, epsilon);
          HfstTransducerPair tmpMappingPair(*$1, HfstTransducer(hfst::pmatch::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
                   
          $$ =  new std::pair< ReplaceArrow, HfstTransducerPair> ($2, mappingPair);
         delete $1, $3;
      }
      | REPLACE REPLACE_ARROW MARKUP_MARKER REPLACE
      {
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
          HfstTransducerPair marks(epsilon, *$4);
          HfstTransducerPair tmpMappingPair(*$1, HfstTransducer(hfst::pmatch::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
          
          $$ =  new std::pair< ReplaceArrow, HfstTransducerPair> ($2, mappingPair);
         delete $1, $4;
      }     
      
| LEFT_BRACKET_DOTTED RIGHT_BRACKET_DOTTED REPLACE_ARROW REPLACE
  {
      HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
      //HfstTransducer mappingTr(epsilon);
      //mappingTr.cross_product(*$4);
      HfstTransducerPair mappingPair(epsilon, *$4);
      
      $$ =  new std::pair< ReplaceArrow, HfstTransducerPair> ($3, mappingPair);
      delete $4;
  }
  | LEFT_BRACKET_DOTTED REPLACE RIGHT_BRACKET_DOTTED REPLACE_ARROW REPLACE
  {
    //  HfstTransducer mappingTr(*$2);
    //  mappingTr.cross_product(*$5);
	  HfstTransducerPair mappingPair(*$2, *$5);
      $$ =  new std::pair< ReplaceArrow, HfstTransducerPair> ($4, mappingPair);
      delete $2, $5;
  }
;    
  
   
      

        
// Contexts: ( ie. || k _ f , ... , f _ s )
CONTEXTS_WITH_MARK:  CONTEXT_MARK CONTEXTS_VECTOR
{
       
    //std::cerr << "context w mark: conMark conVect"<< std::endl;      
         
    $$ =  new std::pair< ReplaceType, HfstTransducerPairVector> ($1, *$2);
    //$$ = $2;
    //std::cerr << "Context Mark: \n" << $1  << std::endl;
   
}  
;
CONTEXTS_VECTOR: CONTEXT
{
    HfstTransducerPairVector * ContextVector = new HfstTransducerPairVector();
    ContextVector->push_back(*$1);
    $$ = ContextVector;
    delete $1; 
}

| CONTEXTS_VECTOR COMMA CONTEXT
{
    $1->push_back(*$3);
    $$ = $1;
    delete $3; 
}
      
;
CONTEXT: REPLACE CENTER_MARKER REPLACE 
{
    $$ = new HfstTransducerPair(*$1, *$3);
    delete $1, $3; 
}
| REPLACE CENTER_MARKER
{
    // std::cerr << "Mapping: \n" << *$1  << std::endl;
            
    HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
            
    // std::cerr << "Epsilon: \n" << epsilon  << std::endl;
    $$ = new HfstTransducerPair(*$1, epsilon);
    delete $1; 
}
| CENTER_MARKER REPLACE
{
    HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
    $$ = new HfstTransducerPair(epsilon, *$2);
    delete $2; 
}
;
      


CONTEXT_MARK: REPLACE_CONTEXT_UU
{
    $$ = REPL_UP;
}
| REPLACE_CONTEXT_LU 
{
    $$ = REPL_RIGHT;
}
| REPLACE_CONTEXT_UL
{
    $$ = REPL_LEFT;
}
| REPLACE_CONTEXT_LL
{
    $$ = REPL_DOWN;
}
;
     
     
     
     


REPLACE_ARROW: REPLACE_RIGHT
{
    $$ = E_REPLACE_RIGHT;
}
| OPTIONAL_REPLACE_RIGHT
{
    $$ = E_OPTIONAL_REPLACE_RIGHT;
}
| RTL_LONGEST_MATCH
{
    $$ = E_RTL_LONGEST_MATCH;
}
| RTL_SHORTEST_MATCH
{
    $$ = E_RTL_SHORTEST_MATCH;
}
| LTR_LONGEST_MATCH
{
    $$ = E_LTR_LONGEST_MATCH;
}
| LTR_SHORTEST_MATCH
{
    $$ = E_LTR_SHORTEST_MATCH;
}
;








////////////////



REGEXP3: REGEXP4 { }
| REGEXP3 SHUFFLE REGEXP4 {
    pmatcherror("No shuffle");
    $$ = $1;
    delete $3;
 }
| REGEXP3 BEFORE REGEXP4 {
    pmatcherror("No before");
    $$ = $1;
    delete $3;
 }
| REGEXP3 AFTER REGEXP4 {
    pmatcherror("No after");
    $$ = $1;
    delete $3;
 }

;

REGEXP4: REGEXP5 { }
| REGEXP4 LEFT_ARROW REGEXP5 CENTER_MARKER REGEXP5 {
    pmatcherror("No Arrows");
    $$ = $1;
    delete $3;
    delete $5;
 }
| REGEXP4 RIGHT_ARROW REGEXP5 CENTER_MARKER REGEXP5 {
    pmatcherror("No Arrows");
    $$ = $1;
    delete $3;
    delete $5;
 }
| REGEXP4 LEFT_RIGHT_ARROW REGEXP5 CENTER_MARKER REGEXP5 {
    pmatcherror("No Arrows");
    $$ = $1;
    delete $3;
    delete $5;
 }
;

REGEXP5: REGEXP6 { }
| REGEXP5 UNION REGEXP6 {
    $$ = & $1->disjunct(*$3);
    delete $3;
 }
| REGEXP5 INTERSECTION REGEXP6 {
    $$ = & $1->intersect(*$3);
    delete $3;
 }
| REGEXP5 MINUS REGEXP6 {
    $$ = & $1->subtract(*$3);
    delete $3;
 }
| REGEXP5 UPPER_MINUS REGEXP6 {
    pmatcherror("No upper minus");
    $$ = $1;
    delete $3;
 }
| REGEXP5 LOWER_MINUS REGEXP6 {
    pmatcherror("No lower minus");
    $$ = $1;
    delete $3;
 }
| REGEXP5 UPPER_PRIORITY_UNION REGEXP6 {
    pmatcherror("No upper priority union");
    $$ = $1;
    delete $3;
 }
| REGEXP5 LOWER_PRIORITY_UNION REGEXP6 {
    pmatcherror("No lower priority union");
    $$ = $1;
    delete $3;
 }
;

REGEXP6: REGEXP7 { }
| REGEXP6 REGEXP7 { 
    $$ = & $1->concatenate(*$2);
    delete $2;
 }
;

REGEXP7: REGEXP8 { }
| REGEXP7 IGNORING REGEXP8 {
    pmatcherror("No ignoring");
    $$ = $1;
    delete $3;
 }
| REGEXP7 IGNORE_INTERNALLY REGEXP8 {
    pmatcherror("No ignoring internally");
    $$ = $1;
    delete $3;
 }
| REGEXP7 LEFT_QUOTIENT REGEXP8 {
    pmatcherror("No left quotient");
    $$ = $1;
    delete $3;
 }

;

REGEXP8: REGEXP9 { }
| COMPLEMENT REGEXP8 {
    pmatcherror("No complement");
    $$ = $2;
 }
| CONTAINMENT REGEXP8 {
    HfstTransducer* left = new HfstTransducer(hfst::internal_unknown,
                                              hfst::internal_unknown,
                                              hfst::pmatch::format);
    HfstTransducer* right = new HfstTransducer(hfst::internal_unknown,
                                               hfst::internal_unknown,
                                               hfst::pmatch::format);
    right->repeat_star();
    left->repeat_star();
    HfstTransducer* contain_once = 
        & ((right->concatenate(*$2).concatenate(*left)));
    $$ = & (contain_once->repeat_star());
    delete $2;
    delete left;
 }
| CONTAINMENT_ONCE REGEXP8 {
    HfstTransducer* left = new HfstTransducer(hfst::internal_unknown,
                                              hfst::internal_unknown,
                                              hfst::pmatch::format);
    HfstTransducer* right = new HfstTransducer(hfst::internal_unknown,
                                               hfst::internal_unknown,
                                               hfst::pmatch::format);
    right->repeat_star();
    left->repeat_star();
    HfstTransducer* contain_once = 
        & ((right->concatenate(*$2).concatenate(*left)));
    $$ = contain_once;
    delete $2;
    delete left;
 }
| CONTAINMENT_OPT REGEXP8 {
    HfstTransducer* left = new HfstTransducer(hfst::internal_unknown,
                                              hfst::internal_unknown,
                                              hfst::pmatch::format);
    HfstTransducer* right = new HfstTransducer(hfst::internal_unknown,
                                               hfst::internal_unknown,
                                               hfst::pmatch::format);
    right->repeat_star();
    left->repeat_star();
    HfstTransducer* contain_once = 
        & ((right->concatenate(*$2).concatenate(*left)));
    $$ = & (contain_once->optionalize());
    delete $2;
    delete left;
 }
;

REGEXP9: REGEXP10 { }
| REGEXP9 STAR {
    $$ = & $1->repeat_star();
 }
| REGEXP9 PLUS {
    $$ = & $1->repeat_plus();
 }
| REGEXP9 REVERSE {
    $$ = & $1->reverse();
 }
| REGEXP9 INVERT {
    $$ = & $1->invert();
 }
| REGEXP9 UPPER {
    $$ = & $1->input_project();
 }
| REGEXP9 LOWER {
    $$ = & $1->output_project();
 }
| REGEXP9 CATENATE_N {
    $$ = & $1->repeat_n($2);
 }
| REGEXP9 CATENATE_N_PLUS {
    $$ = & $1->repeat_n_plus($2 + 1);
 }
| REGEXP9 CATENATE_N_MINUS {
    $$ = & $1->repeat_n_minus($2 - 1);
 }
| REGEXP9 CATENATE_N_TO_K {
    $$ = & $1->repeat_n_to_k($2[0], $2[1]);
    free($2);
 }
;

REGEXP10: REGEXP11 { }
| TERM_COMPLEMENT REGEXP10 {
    HfstTransducer* any = new HfstTransducer(hfst::internal_identity,
                                             hfst::internal_identity,
                                             hfst::pmatch::format);
    $$ = & ( any->subtract(*$2));
    delete $2;
 }
| SUBSTITUTE_LEFT REGEXP10 COMMA REGEXP10 COMMA REGEXP10 RIGHT_BRACKET {
    pmatcherror("no substitute");
    $$ = $2;
 }
;

REGEXP11: REGEXP12 { }
| REGEXP11 WEIGHT { 
    $$ = & $1->set_final_weights($2);
 }
| LEFT_BRACKET REGEXP2 RIGHT_BRACKET {
    $$ = $2;
 }
| LEFT_PARENTHESIS REGEXP2 RIGHT_PARENTHESIS {
    $$ = & $2->optionalize();
 }
| ALPHA {
    $$ = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_alpha_acceptor);
 }
| LOWERALPHA {
    $$ = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_lowercase_acceptor);
 }
| UPPERALPHA {
    $$ = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_uppercase_acceptor);
 }
| NUM {
    $$ = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_numeral_acceptor);
 }
| PUNCT {
    $$ = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_punct_acceptor);
 }
| WHITESPACE {
    $$ = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_whitespace_acceptor);
 }
| INSERT { }
| ANONYMOUS_DEFINITION { }
| OPTCAP { }
| TOUPPER { }
| TOLOWER { }
;

OPTCAP: OPTCAP_LEFT REGEXP11 RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::get_utils()->optcap(* $2);
}
;

TOLOWER: TOLOWER_LEFT REGEXP11 RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::get_utils()->tolower(* $2);
}
;

TOUPPER: TOUPPER_LEFT REGEXP11 RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::get_utils()->toupper(* $2);
}
;

FUN_OPTCAP: OPTCAP_LEFT FUNCBODY4 RIGHT_PARENTHESIS {
    $$ = new PmatchAstNode($2, hfst::pmatch::AstOptCap);
}
;

FUN_TOLOWER: TOLOWER_LEFT FUNCBODY4 RIGHT_PARENTHESIS {
    $$ = new PmatchAstNode($2, hfst::pmatch::AstToLower);
}
;

FUN_TOUPPER: TOUPPER_LEFT FUNCBODY4 RIGHT_PARENTHESIS {
    $$ = new PmatchAstNode($2, hfst::pmatch::AstToUpper);
}
;

REGEXP12: LABEL_PAIR { }
| READ_BIN {
    try {
        hfst::HfstInputStream instream($1);
        $$ = new HfstTransducer(instream);
        instream.close();
    } catch(HfstException) {
        std::string ermsg =
            std::string("Couldn't read transducer from ") +
            std::string($1);
        free($1);
        pmatcherror(ermsg.c_str());
    }
    if ($$->get_type() != hfst::pmatch::format) {
        $$->convert(hfst::pmatch::format);
    }
    free($1);
  }
| READ_TEXT {
  $$ = hfst::pmatch::read_text($1);
  free($1);
  }
| READ_SPACED {
    pmatcherror("no read spaced");
  }
| READ_PROLOG {
    pmatcherror("no read prolog");
  }
| READ_RE {
    pmatcherror("Definitely no read regex");
  }
| READ_LEXC {
    $$ = hfst::HfstTransducer::read_lexc_ptr($1, hfst::TROPICAL_OPENFST_TYPE, hfst::pmatch::verbose);
    free($1);
  }
;

LABEL_PAIR: LABEL PAIR_SEPARATOR LABEL {
    $$ = new HfstTransducer($1, $3, hfst::pmatch::format);
    free($1); free($3);
}

| ANY_TOKEN PAIR_SEPARATOR ANY_TOKEN {
    $$ = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
 }
| LABEL PAIR_SEPARATOR ANY_TOKEN {
    $$ = new HfstTransducer($1, hfst::internal_unknown, hfst::pmatch::format);
    free($1);
 }
| ANY_TOKEN PAIR_SEPARATOR LABEL {
    $$ = new HfstTransducer(hfst::internal_unknown, $3, hfst::pmatch::format);
    free($3);
}
| LABEL PAIR_SEPARATOR_WO_RIGHT {
    $$ = new HfstTransducer($1, hfst::internal_unknown, hfst::pmatch::format);
    free($1);
 }
| ANY_TOKEN PAIR_SEPARATOR_WO_RIGHT {
    $$ = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
 }
| PAIR_SEPARATOR_WO_LEFT LABEL {
    $$ = new HfstTransducer(hfst::internal_unknown, $2, hfst::pmatch::format);
    free($2);
 }
| PAIR_SEPARATOR_WO_LEFT ANY_TOKEN {
    $$ = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
 }
| SYMBOL {
    if (hfst::pmatch::definitions.count($1) != 0) {
        if (!hfst::pmatch::flatten &&
            hfst::pmatch::def_insed_transducers.count($1) == 1) {
            $$ = new HfstTransducer(*hfst::pmatch::def_insed_transducers[$1]);
            hfst::pmatch::inserted_transducers.insert($1);
            if (hfst::pmatch::verbose) {
                hfst::pmatch::used_definitions.insert($1);
            }
        } else {
            if (hfst::pmatch::verbose) {
                std::cerr << "including " <<
                    hfst::pmatch::definitions[$1]->get_name() << " with ";
                hfst::pmatch::print_size_info(hfst::pmatch::definitions[$1]);
                hfst::pmatch::used_definitions.insert($1);
            }
            $$ = new HfstTransducer(*hfst::pmatch::definitions[$1]);
        }
    } else {
        if (strlen($1) == 0) {
            $$ = new HfstTransducer(hfst::pmatch::format);
        } else {
            std::string errstring = "Unknown symbol: " + std::string($1);
            pmatcherror(errstring.c_str());
        }
    }
    free($1);
 }
| PAIR_SEPARATOR_SOLE {
    $$ = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
  }
| LABEL {
    $$ = new HfstTransducer($1, $1,
                            hfst::pmatch::format);
    free($1);
  }
| ANY_TOKEN {
    $$ = new HfstTransducer(hfst::internal_identity,
                            hfst::pmatch::format);
  }
| CURLY_LITERAL {
    HfstTokenizer tok;
    $$ = new HfstTransducer($1, tok, hfst::pmatch::format);
    free($1);
 }
| CURLY_LITERAL PAIR_SEPARATOR CURLY_LITERAL {
    HfstTokenizer tok;
    HfstTransducer * left = new HfstTransducer($1, tok, hfst::pmatch::format);
    HfstTransducer * right = new HfstTransducer($3, tok, hfst::pmatch::format);
    HfstTransducer * destroy = new HfstTransducer(
        hfst::internal_unknown, hfst::internal_epsilon, hfst::pmatch::format);
    HfstTransducer * construct = new HfstTransducer(
        hfst::internal_epsilon, hfst::internal_unknown, hfst::pmatch::format);
    left->compose(destroy->repeat_star());
    left->compose(construct->repeat_star());
    left->compose(*right);
    $$ = left;
    delete destroy; delete construct; delete right;
    free($1); free($3);
}
| LABEL PAIR_SEPARATOR CURLY_LITERAL {
    HfstTokenizer tok;
    HfstTransducer * left = new HfstTransducer(
        $1, hfst::internal_epsilon, hfst::pmatch::format);
    HfstTransducer * right = new HfstTransducer($3, tok, hfst::pmatch::format);
    HfstTransducer * construct = new HfstTransducer(
        hfst::internal_epsilon, hfst::internal_unknown, hfst::pmatch::format);
    left->compose(construct->repeat_star());
    left->compose(*right);
    $$ = left;
    delete construct; delete right;
    free($1); free($3);
}
| CURLY_LITERAL PAIR_SEPARATOR LABEL {
    HfstTokenizer tok;
    HfstTransducer * left = new HfstTransducer($1, tok, hfst::pmatch::format);
    HfstTransducer * right = new HfstTransducer(
        hfst::internal_epsilon, $3, hfst::pmatch::format);
    HfstTransducer * destroy = new HfstTransducer(
        hfst::internal_unknown, hfst::internal_epsilon, hfst::pmatch::format);
    left->compose(destroy->repeat_star());
    left->compose(*right);
    $$ = left;
    delete destroy; delete right;
    free($1); free($3);
}
| FUNCALL { }
| MAP { }
| CONTEXT_CONDITION { }
| ENDTAG_LEFT SYMBOL RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::make_end_tag($2);
    hfst::pmatch::need_delimiters = true;
 }
| ENDTAG_LEFT QUOTED_LITERAL RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::make_end_tag($2);
    hfst::pmatch::need_delimiters = true;
 }

;

LABEL: QUOTED_LITERAL { }
| EPSILON_TOKEN { $$ = strdup(hfst::internal_epsilon.c_str()); }
| BOUNDARY_MARKER { $$ = strdup("@BOUNDARY@"); }
;

CONTEXT_CONDITION:
P_CONTEXT { $$ = $1; hfst::pmatch::need_delimiters = true; }
| OR_CONTEXT { }
| AND_CONTEXT { };

P_CONTEXT:
RIGHT_CONTEXT { }
| NEGATIVE_RIGHT_CONTEXT { }
| LEFT_CONTEXT { }
| NEGATIVE_LEFT_CONTEXT { };

OR_CONTEXT: OR_LEFT CONTEXT_CONDITIONS RIGHT_PARENTHESIS
{
    $$ = new HfstTransducer(hfst::pmatch::format);
    for(hfst::HfstTransducerVector::reverse_iterator it = $2->rbegin();
        it != $2->rend(); ++it) {
        $$->disjunct(*it);
    }
    delete $2;
    // Zero the counter for making minimization
    // guards for disjuncted negative contexts
    hfst::pmatch::zero_minimization_guard();
};

AND_CONTEXT: AND_LEFT CONTEXT_CONDITIONS RIGHT_PARENTHESIS
{
    $$ = new HfstTransducer(hfst::internal_epsilon, hfst::internal_epsilon, hfst::pmatch::format);
    for(hfst::HfstTransducerVector::reverse_iterator it = $2->rbegin();
        it != $2->rend(); ++it) {
        $$->concatenate(*it);
    }
    delete $2;
};

CONTEXT_CONDITIONS:
CONTEXT_CONDITION {
    $$ = new hfst::HfstTransducerVector(1, *$1);
    delete $1;
}
| CONTEXT_CONDITION COMMA CONTEXT_CONDITIONS {
    $3->push_back(*$1);
    delete $1;
    $$ = $3;
};

FUNCALL: SYMBOL_WITH_LEFT_PAREN FUNCALL_ARGLIST RIGHT_PARENTHESIS {
    if (hfst::pmatch::functions.count($1) == 0) {
        std::string errstring = "Function not defined: " + std::string($1);
        pmatcherror(errstring.c_str());
    }
    std::vector<string> & callee_args = hfst::pmatch::functions[$1].args;
    if (callee_args.size() != $2->size()) {
        std::string errstring = "Function " + std::string($1) +
            " expected NN arguments, received NN";// + $2->size());
        pmatcherror(errstring.c_str());
    }
    std::map<std::string, HfstTransducer*> caller_args;
    for (int i = 0; i < $2->size(); ++i) {
        caller_args[callee_args[i]] = new HfstTransducer($2->at(i));
    }
    $$ = hfst::pmatch::functions[$1].evaluate(caller_args);
    delete $2;
};

FUNCALL_ARGLIST:
FUNCALL_ARG {
    $$ = new HfstTransducerVector();
    $$->push_back(HfstTransducer(*$1));
    delete $1;
}
| FUNCALL_ARG COMMA FUNCALL_ARGLIST {
    $3->push_back(HfstTransducer(*$1));
    delete $1;
}
| { $$ = new HfstTransducerVector(); }
;

FUNCALL_ARG:
SYMBOL {
    if (hfst::pmatch::definitions.count($1) == 1) {
        $$ = new HfstTransducer(* hfst::pmatch::definitions[$1]);
    } else if (hfst::pmatch::def_insed_transducers.count($1) == 0) {
        $$ = new HfstTransducer(* hfst::pmatch::def_insed_transducers[$1]);
    } else {
        std::string errstring = "Unknown definition: " + std::string($1);
        free($1);
        pmatcherror(errstring.c_str());
    }
    free($1);
}
| CURLY_LITERAL {
    HfstTokenizer tok;
    $$ = new HfstTransducer($1, tok, hfst::pmatch::format);
    free($1);
  }
| QUOTED_LITERAL {
    $$ = new HfstTransducer($1, hfst::pmatch::format);
    free($1);
  }
;

MAP: MAP_LEFT SYMBOL COMMA READ_TEXT RIGHT_PARENTHESIS {
    if (hfst::pmatch::functions.count($2) == 0) {
        std::string errstring = "Function not defined: " + std::string($2);
        pmatcherror(errstring.c_str());
    }
    std::vector<string> & callee_args = hfst::pmatch::functions[$2].args;
    std::vector<std::vector<std::string> > caller_strings =
        hfst::pmatch::read_args($4, callee_args.size());
    std::map<std::string, HfstTransducer*> caller_args;
    HfstTokenizer tok;
    $$ = new HfstTransducer(hfst::pmatch::format);
    for (std::vector<std::vector<std::string> >::iterator it =
             caller_strings.begin(); it != caller_strings.end(); ++it) {
        for (int i = 0; i < it->size(); ++i) {
            caller_args[callee_args[i]] = new HfstTransducer(it->at(i), tok, hfst::pmatch::format);
        }
        $$->disjunct(*hfst::pmatch::functions[$2].evaluate(caller_args));
        // Clean up the string transducers we allocated each time 
        for (std::map<std::string, HfstTransducer *>::iterator it = caller_args.begin();
             it != caller_args.end(); ++it) {
            delete it->second;
        }
        caller_args.clear();
    }
    $$->minimize();
};

INSERT: INS_LEFT SYMBOL RIGHT_PARENTHESIS {
    if (!hfst::pmatch::flatten) {
        if(hfst::pmatch::definitions.count($2) == 0) {
            hfst::pmatch::unsatisfied_insertions.insert($2);
        }
        char * Ins_trans = hfst::pmatch::get_Ins_transition($2);
        $$ = new HfstTransducer(
            Ins_trans, Ins_trans, hfst::pmatch::format);
        $$->set_name(Ins_trans);
        free(Ins_trans);
        hfst::pmatch::inserted_transducers.insert($2);
        if (hfst::pmatch::verbose) {
            std::cerr << "inserting " << $2;
            if (hfst::pmatch::definitions.count($2) != 0) {
                std::cerr << " with ";
                hfst::pmatch::print_size_info(hfst::pmatch::definitions[$2]);
            } else {
                std::cerr << std::endl;
            }
            hfst::pmatch::used_definitions.insert($2);
        }
    } else if(hfst::pmatch::definitions.count($2) == 1) {
        if (hfst::pmatch::verbose) {
            std::cerr << "including " <<
                hfst::pmatch::definitions[$2]->get_name() << " with ";
            hfst::pmatch::print_size_info(hfst::pmatch::definitions[$2]);
            hfst::pmatch::used_definitions.insert($2);
        }
        $$ = new HfstTransducer(* hfst::pmatch::definitions[$2]);
    } else {
        // error?
        if (strlen($2) == 0) {
            $$ = new HfstTransducer(hfst::pmatch::format);
        } else {
            $$ = new HfstTransducer($2, $2, hfst::pmatch::format);
        }
    }
    free($2);

}
;

ANONYMOUS_DEFINITION: DEFINE_LEFT REPLACE RIGHT_PARENTHESIS
{
    $$ = hfst::pmatch::add_pmatch_delimiters($2);
};

RIGHT_CONTEXT: RC_LEFT REPLACE RIGHT_PARENTHESIS {
    HfstTransducer * rc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::RC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * rc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::RC_EXIT_SYMBOL, hfst::pmatch::format);
    rc_entry->concatenate(*$2);
    rc_entry->concatenate(*rc_exit);
    $$ = rc_entry;
    delete $2;
    delete rc_exit;
 }
;

NEGATIVE_RIGHT_CONTEXT: NRC_LEFT REPLACE RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::get_minimization_guard();
    HfstTransducer * nrc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NRC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * nrc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NRC_EXIT_SYMBOL, hfst::pmatch::format);
    nrc_entry->concatenate(*$2);
    nrc_entry->concatenate(*nrc_exit);
    nrc_entry->disjunct(HfstTransducer("@PMATCH_PASSTHROUGH@",
                                       hfst::internal_epsilon, hfst::pmatch::format));
    $$->concatenate(*nrc_entry);
    delete $2; delete nrc_entry; delete nrc_exit;
 }
;

LEFT_CONTEXT: LC_LEFT REPLACE RIGHT_PARENTHESIS {
    HfstTransducer * lc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * lc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_EXIT_SYMBOL, hfst::pmatch::format);
    lc_entry->concatenate($2->reverse());
    lc_entry->concatenate(*lc_exit);
    $$ = lc_entry;
    delete $2; delete lc_exit;
 }
;

NEGATIVE_LEFT_CONTEXT: NLC_LEFT REPLACE RIGHT_PARENTHESIS {
    $$ = hfst::pmatch::get_minimization_guard();
    HfstTransducer * nlc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * nlc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_EXIT_SYMBOL, hfst::pmatch::format);
    nlc_entry->concatenate($2->reverse());
    nlc_entry->concatenate(*nlc_exit);
    nlc_entry->disjunct(HfstTransducer("@PMATCH_PASSTHROUGH@",
                                       hfst::internal_epsilon, hfst::pmatch::format));
    $$->concatenate(*nlc_entry);
    delete $2; delete nlc_entry; delete nlc_exit;
 }
;

FUN_RIGHT_CONTEXT: RC_LEFT FUNCBODY2 RIGHT_PARENTHESIS {
    PmatchAstNode * rc_entry =
        new PmatchAstNode(
            new HfstTransducer(hfst::internal_epsilon,
                               hfst::pmatch::RC_ENTRY_SYMBOL,
                               hfst::pmatch::format),
            $2, hfst::pmatch::AstConcatenate);
    $$ = new PmatchAstNode(rc_entry,
                                         new HfstTransducer(
                                             hfst::internal_epsilon,
                                             hfst::pmatch::RC_EXIT_SYMBOL,
                                             hfst::pmatch::format),
                                         hfst::pmatch::AstConcatenate);
 }
;

FUN_NEGATIVE_RIGHT_CONTEXT: NRC_LEFT FUNCBODY2 RIGHT_PARENTHESIS {
    PmatchAstNode * nrc_entry =
        new PmatchAstNode(
            new HfstTransducer(hfst::internal_epsilon,
                               hfst::pmatch::NRC_ENTRY_SYMBOL,
                               hfst::pmatch::format),
            $2, hfst::pmatch::AstConcatenate);
    PmatchAstNode * nrc_main_branch =
        new PmatchAstNode(nrc_entry,
                                        new HfstTransducer(
                                            hfst::internal_epsilon,
                                            hfst::pmatch::NRC_EXIT_SYMBOL,
                                            hfst::pmatch::format),
                                        hfst::pmatch::AstConcatenate);
    $$ = new PmatchAstNode(
        nrc_main_branch,
        new HfstTransducer("@PMATCH_PASSTHROUGH@",
                           hfst::internal_epsilon, hfst::pmatch::format),
        hfst::pmatch::AstDisjunct);
 }
;

FUN_LEFT_CONTEXT: LC_LEFT FUNCBODY2 RIGHT_PARENTHESIS {
    PmatchAstNode * reverse = new PmatchAstNode(
        $2, hfst::pmatch::AstReverse);
    
    HfstTransducer * lc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * lc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_EXIT_SYMBOL, hfst::pmatch::format);

    PmatchAstNode * entry = new PmatchAstNode(
        lc_entry, reverse, hfst::pmatch::AstConcatenate);
    $$ = new PmatchAstNode(
        entry, lc_exit, hfst::pmatch::AstConcatenate);
 }
;

FUN_NEGATIVE_LEFT_CONTEXT: NLC_LEFT FUNCBODY2 RIGHT_PARENTHESIS {
    PmatchAstNode * reverse = new PmatchAstNode(
        $2, hfst::pmatch::AstReverse);
    
    HfstTransducer * nlc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * nlc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_EXIT_SYMBOL, hfst::pmatch::format);
    
    PmatchAstNode * entry = new PmatchAstNode(
        nlc_entry, reverse, hfst::pmatch::AstConcatenate);
    PmatchAstNode * main_branch = new PmatchAstNode(
        entry, nlc_exit, hfst::pmatch::AstConcatenate);
    
    $$ = new PmatchAstNode(main_branch,
                           new HfstTransducer("@PMATCH_PASSTHROUGH@",
                                              hfst::internal_epsilon, hfst::pmatch::format),
                           hfst::pmatch::AstDisjunct);
}
;

%%

