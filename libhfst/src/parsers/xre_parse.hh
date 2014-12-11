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
     CURLY_BRACKETS = 260,
     SYMBOL = 261,
     INTERSECTION = 262,
     LENIENT_COMPOSITION = 263,
     COMPOSITION = 264,
     CROSS_PRODUCT = 265,
     MARKUP_MARKER = 266,
     CENTER_MARKER = 267,
     SHUFFLE = 268,
     LEFT_RIGHT_ARROW = 269,
     RIGHT_ARROW = 270,
     LEFT_ARROW = 271,
     LEFT_RESTRICTION = 272,
     LTR_SHORTEST_MATCH = 273,
     LTR_LONGEST_MATCH = 274,
     RTL_SHORTEST_MATCH = 275,
     RTL_LONGEST_MATCH = 276,
     OPTIONAL_REPLACE_LEFT_RIGHT = 277,
     REPLACE_LEFT_RIGHT = 278,
     OPTIONAL_REPLACE_LEFT = 279,
     OPTIONAL_REPLACE_RIGHT = 280,
     REPLACE_LEFT = 281,
     REPLACE_RIGHT = 282,
     REPLACE_CONTEXT_LL = 283,
     REPLACE_CONTEXT_UL = 284,
     REPLACE_CONTEXT_LU = 285,
     REPLACE_CONTEXT_UU = 286,
     LOWER_PRIORITY_UNION = 287,
     UPPER_PRIORITY_UNION = 288,
     LOWER_MINUS = 289,
     UPPER_MINUS = 290,
     MINUS = 291,
     UNION = 292,
     LEFT_QUOTIENT = 293,
     IGNORE_INTERNALLY = 294,
     IGNORING = 295,
     COMMACOMMA = 296,
     COMMA = 297,
     AFTER = 298,
     BEFORE = 299,
     TERM_COMPLEMENT = 300,
     SUBSTITUTE_LEFT = 301,
     CONTAINMENT_OPT = 302,
     CONTAINMENT_ONCE = 303,
     CONTAINMENT = 304,
     COMPLEMENT = 305,
     PLUS = 306,
     STAR = 307,
     LOWER = 308,
     UPPER = 309,
     INVERT = 310,
     REVERSE = 311,
     CATENATE_N_TO_K = 312,
     CATENATE_N_MINUS = 313,
     CATENATE_N_PLUS = 314,
     CATENATE_N = 315,
     READ_RE = 316,
     READ_PROLOG = 317,
     READ_SPACED = 318,
     READ_TEXT = 319,
     READ_BIN = 320,
     FUNCTION_NAME = 321,
     LEFT_BRACKET = 322,
     RIGHT_BRACKET = 323,
     LEFT_PARENTHESIS = 324,
     RIGHT_PARENTHESIS = 325,
     LEFT_BRACKET_DOTTED = 326,
     RIGHT_BRACKET_DOTTED = 327,
     SUBVAL = 328,
     PAIR_SEPARATOR_WO_RIGHT = 329,
     PAIR_SEPARATOR_WO_LEFT = 330,
     EPSILON_TOKEN = 331,
     ANY_TOKEN = 332,
     BOUNDARY_MARKER = 333,
     LEXER_ERROR = 334,
     END_OF_EXPRESSION = 335,
     PAIR_SEPARATOR = 336,
     PAIR_SEPARATOR_SOLE = 337,
     QUOTED_LITERAL = 338
   };
#endif
/* Tokens.  */
#define END_OF_WEIGHTED_EXPRESSION 258
#define WEIGHT 259
#define CURLY_BRACKETS 260
#define SYMBOL 261
#define INTERSECTION 262
#define LENIENT_COMPOSITION 263
#define COMPOSITION 264
#define CROSS_PRODUCT 265
#define MARKUP_MARKER 266
#define CENTER_MARKER 267
#define SHUFFLE 268
#define LEFT_RIGHT_ARROW 269
#define RIGHT_ARROW 270
#define LEFT_ARROW 271
#define LEFT_RESTRICTION 272
#define LTR_SHORTEST_MATCH 273
#define LTR_LONGEST_MATCH 274
#define RTL_SHORTEST_MATCH 275
#define RTL_LONGEST_MATCH 276
#define OPTIONAL_REPLACE_LEFT_RIGHT 277
#define REPLACE_LEFT_RIGHT 278
#define OPTIONAL_REPLACE_LEFT 279
#define OPTIONAL_REPLACE_RIGHT 280
#define REPLACE_LEFT 281
#define REPLACE_RIGHT 282
#define REPLACE_CONTEXT_LL 283
#define REPLACE_CONTEXT_UL 284
#define REPLACE_CONTEXT_LU 285
#define REPLACE_CONTEXT_UU 286
#define LOWER_PRIORITY_UNION 287
#define UPPER_PRIORITY_UNION 288
#define LOWER_MINUS 289
#define UPPER_MINUS 290
#define MINUS 291
#define UNION 292
#define LEFT_QUOTIENT 293
#define IGNORE_INTERNALLY 294
#define IGNORING 295
#define COMMACOMMA 296
#define COMMA 297
#define AFTER 298
#define BEFORE 299
#define TERM_COMPLEMENT 300
#define SUBSTITUTE_LEFT 301
#define CONTAINMENT_OPT 302
#define CONTAINMENT_ONCE 303
#define CONTAINMENT 304
#define COMPLEMENT 305
#define PLUS 306
#define STAR 307
#define LOWER 308
#define UPPER 309
#define INVERT 310
#define REVERSE 311
#define CATENATE_N_TO_K 312
#define CATENATE_N_MINUS 313
#define CATENATE_N_PLUS 314
#define CATENATE_N 315
#define READ_RE 316
#define READ_PROLOG 317
#define READ_SPACED 318
#define READ_TEXT 319
#define READ_BIN 320
#define FUNCTION_NAME 321
#define LEFT_BRACKET 322
#define RIGHT_BRACKET 323
#define LEFT_PARENTHESIS 324
#define RIGHT_PARENTHESIS 325
#define LEFT_BRACKET_DOTTED 326
#define RIGHT_BRACKET_DOTTED 327
#define SUBVAL 328
#define PAIR_SEPARATOR_WO_RIGHT 329
#define PAIR_SEPARATOR_WO_LEFT 330
#define EPSILON_TOKEN 331
#define ANY_TOKEN 332
#define BOUNDARY_MARKER 333
#define LEXER_ERROR 334
#define END_OF_EXPRESSION 335
#define PAIR_SEPARATOR 336
#define PAIR_SEPARATOR_SOLE 337
#define QUOTED_LITERAL 338




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 73 "xre_parse.yy"


    int value;
    int* values;
    double weight;
    char* label;
    
    char *subval1, *subval2;
    
    hfst::HfstTransducer* transducer;
    hfst::HfstTransducerPair* transducerPair;
    hfst::HfstTransducerPairVector* transducerPairVector;
    hfst::HfstTransducerVector* transducerVector;

   std::pair<hfst::xeroxRules::ReplaceArrow, std::vector<hfst::xeroxRules::Rule> >* replaceRuleVectorWithArrow;
   std::pair< hfst::xeroxRules::ReplaceArrow, hfst::xeroxRules::Rule>* replaceRuleWithArrow;   
   std::pair< hfst::xeroxRules::ReplaceArrow, hfst::HfstTransducerPairVector>* mappingVectorWithArrow;
   std::pair< hfst::xeroxRules::ReplaceArrow, hfst::HfstTransducerPair>* mappingWithArrow;
       
   std::pair<hfst::xeroxRules::ReplaceType, hfst::HfstTransducerPairVector>* contextWithMark;
   
   hfst::xeroxRules::ReplaceType replType;
   hfst::xeroxRules::ReplaceArrow replaceArrow; 




/* Line 2068 of yacc.c  */
#line 244 "xre_parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




