/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END_OF_WEIGHTED_EXPRESSION = 258,
     WEIGHT = 259,
     SYMBOL_WITH_LEFT_PAREN = 260,
     SYMBOL = 261,
     CURLY_LITERAL = 262,
     QUOTED_LITERAL = 263,
     INTERSECTION = 264,
     LENIENT_COMPOSITION = 265,
     COMPOSITION = 266,
     CROSS_PRODUCT = 267,
     MARKUP_MARKER = 268,
     CENTER_MARKER = 269,
     SHUFFLE = 270,
     LEFT_RIGHT_ARROW = 271,
     RIGHT_ARROW = 272,
     LEFT_ARROW = 273,
     LEFT_RESTRICTION = 274,
     LTR_SHORTEST_MATCH = 275,
     LTR_LONGEST_MATCH = 276,
     RTL_SHORTEST_MATCH = 277,
     RTL_LONGEST_MATCH = 278,
     OPTIONAL_REPLACE_LEFT_RIGHT = 279,
     REPLACE_LEFT_RIGHT = 280,
     OPTIONAL_REPLACE_LEFT = 281,
     OPTIONAL_REPLACE_RIGHT = 282,
     REPLACE_LEFT = 283,
     REPLACE_RIGHT = 284,
     REPLACE_CONTEXT_LL = 285,
     REPLACE_CONTEXT_UL = 286,
     REPLACE_CONTEXT_LU = 287,
     REPLACE_CONTEXT_UU = 288,
     LOWER_PRIORITY_UNION = 289,
     UPPER_PRIORITY_UNION = 290,
     LOWER_MINUS = 291,
     UPPER_MINUS = 292,
     MINUS = 293,
     UNION = 294,
     LEFT_QUOTIENT = 295,
     IGNORE_INTERNALLY = 296,
     IGNORING = 297,
     COMMACOMMA = 298,
     COMMA = 299,
     AFTER = 300,
     BEFORE = 301,
     TERM_COMPLEMENT = 302,
     SUBSTITUTE_LEFT = 303,
     CONTAINMENT_OPT = 304,
     CONTAINMENT_ONCE = 305,
     CONTAINMENT = 306,
     COMPLEMENT = 307,
     PLUS = 308,
     STAR = 309,
     LOWER = 310,
     UPPER = 311,
     INVERT = 312,
     REVERSE = 313,
     CATENATE_N_TO_K = 314,
     CATENATE_N_MINUS = 315,
     CATENATE_N_PLUS = 316,
     CATENATE_N = 317,
     READ_LEXC = 318,
     READ_RE = 319,
     READ_PROLOG = 320,
     READ_SPACED = 321,
     READ_TEXT = 322,
     READ_BIN = 323,
     LEFT_BRACKET = 324,
     RIGHT_BRACKET = 325,
     LEFT_PARENTHESIS = 326,
     RIGHT_PARENTHESIS = 327,
     LEFT_BRACKET_DOTTED = 328,
     RIGHT_BRACKET_DOTTED = 329,
     END_OF_EXPRESSION = 330,
     PAIR_SEPARATOR = 331,
     PAIR_SEPARATOR_SOLE = 332,
     PAIR_SEPARATOR_WO_RIGHT = 333,
     PAIR_SEPARATOR_WO_LEFT = 334,
     EPSILON_TOKEN = 335,
     ANY_TOKEN = 336,
     BOUNDARY_MARKER = 337,
     LEXER_ERROR = 338,
     AND_LEFT = 339,
     OR_LEFT = 340,
     SYM_LEFT = 341,
     MAP_LEFT = 342,
     NRC_LEFT = 343,
     NLC_LEFT = 344,
     RC_LEFT = 345,
     LC_LEFT = 346,
     ENDTAG_LEFT = 347,
     DEFINE_LEFT = 348,
     INS_LEFT = 349,
     TOUPPER_LEFT = 350,
     TOLOWER_LEFT = 351,
     OPTCAP_LEFT = 352,
     WHITESPACE = 353,
     PUNCT = 354,
     NUM = 355,
     UPPERALPHA = 356,
     LOWERALPHA = 357,
     ALPHA = 358,
     DEFFUN = 359,
     DEFINS = 360,
     REGEX = 361,
     DEFINE = 362
   };
#endif
/* Tokens.  */
#define END_OF_WEIGHTED_EXPRESSION 258
#define WEIGHT 259
#define SYMBOL_WITH_LEFT_PAREN 260
#define SYMBOL 261
#define CURLY_LITERAL 262
#define QUOTED_LITERAL 263
#define INTERSECTION 264
#define LENIENT_COMPOSITION 265
#define COMPOSITION 266
#define CROSS_PRODUCT 267
#define MARKUP_MARKER 268
#define CENTER_MARKER 269
#define SHUFFLE 270
#define LEFT_RIGHT_ARROW 271
#define RIGHT_ARROW 272
#define LEFT_ARROW 273
#define LEFT_RESTRICTION 274
#define LTR_SHORTEST_MATCH 275
#define LTR_LONGEST_MATCH 276
#define RTL_SHORTEST_MATCH 277
#define RTL_LONGEST_MATCH 278
#define OPTIONAL_REPLACE_LEFT_RIGHT 279
#define REPLACE_LEFT_RIGHT 280
#define OPTIONAL_REPLACE_LEFT 281
#define OPTIONAL_REPLACE_RIGHT 282
#define REPLACE_LEFT 283
#define REPLACE_RIGHT 284
#define REPLACE_CONTEXT_LL 285
#define REPLACE_CONTEXT_UL 286
#define REPLACE_CONTEXT_LU 287
#define REPLACE_CONTEXT_UU 288
#define LOWER_PRIORITY_UNION 289
#define UPPER_PRIORITY_UNION 290
#define LOWER_MINUS 291
#define UPPER_MINUS 292
#define MINUS 293
#define UNION 294
#define LEFT_QUOTIENT 295
#define IGNORE_INTERNALLY 296
#define IGNORING 297
#define COMMACOMMA 298
#define COMMA 299
#define AFTER 300
#define BEFORE 301
#define TERM_COMPLEMENT 302
#define SUBSTITUTE_LEFT 303
#define CONTAINMENT_OPT 304
#define CONTAINMENT_ONCE 305
#define CONTAINMENT 306
#define COMPLEMENT 307
#define PLUS 308
#define STAR 309
#define LOWER 310
#define UPPER 311
#define INVERT 312
#define REVERSE 313
#define CATENATE_N_TO_K 314
#define CATENATE_N_MINUS 315
#define CATENATE_N_PLUS 316
#define CATENATE_N 317
#define READ_LEXC 318
#define READ_RE 319
#define READ_PROLOG 320
#define READ_SPACED 321
#define READ_TEXT 322
#define READ_BIN 323
#define LEFT_BRACKET 324
#define RIGHT_BRACKET 325
#define LEFT_PARENTHESIS 326
#define RIGHT_PARENTHESIS 327
#define LEFT_BRACKET_DOTTED 328
#define RIGHT_BRACKET_DOTTED 329
#define END_OF_EXPRESSION 330
#define PAIR_SEPARATOR 331
#define PAIR_SEPARATOR_SOLE 332
#define PAIR_SEPARATOR_WO_RIGHT 333
#define PAIR_SEPARATOR_WO_LEFT 334
#define EPSILON_TOKEN 335
#define ANY_TOKEN 336
#define BOUNDARY_MARKER 337
#define LEXER_ERROR 338
#define AND_LEFT 339
#define OR_LEFT 340
#define SYM_LEFT 341
#define MAP_LEFT 342
#define NRC_LEFT 343
#define NLC_LEFT 344
#define RC_LEFT 345
#define LC_LEFT 346
#define ENDTAG_LEFT 347
#define DEFINE_LEFT 348
#define INS_LEFT 349
#define TOUPPER_LEFT 350
#define TOLOWER_LEFT 351
#define OPTCAP_LEFT 352
#define WHITESPACE 353
#define PUNCT 354
#define NUM 355
#define UPPERALPHA 356
#define LOWERALPHA 357
#define ALPHA 358
#define DEFFUN 359
#define DEFINS 360
#define REGEX 361
#define DEFINE 362




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 36 "pmatch_parse.yy"





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
    
     
     


/* Line 2068 of yacc.c  */
#line 298 "pmatch_parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE pmatchlval;


