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
     FREELY_INSERT = 258,
     DIFFERENCE = 259,
     INTERSECTION = 260,
     UNION = 261,
     PLUS = 262,
     STAR = 263,
     COMPLEMENT = 264,
     TERM_COMPLEMENT = 265,
     CONTAINMENT_ONCE = 266,
     CONTAINMENT = 267,
     POWER = 268,
     RIGHT_PARENTHESIS = 269,
     RIGHT_SQUARE_BRACKET = 270,
     LEFT_PARENTHESIS = 271,
     LEFT_SQUARE_BRACKET = 272,
     RIGHT_CURLY_BRACKET = 273,
     LEFT_CURLY_BRACKET = 274,
     LEFT_RESTRICTION_ARROW = 275,
     LEFT_ARROW = 276,
     RIGHT_ARROW = 277,
     LEFT_RIGHT_ARROW = 278,
     RE_LEFT_RESTRICTION_ARROW = 279,
     RE_LEFT_ARROW = 280,
     RE_RIGHT_ARROW = 281,
     RE_LEFT_RIGHT_ARROW = 282,
     RE_RIGHT_SQUARE_BRACKET = 283,
     RE_LEFT_SQUARE_BRACKET = 284,
     ALPHABET_DECLARATION = 285,
     DIACRITICS_DECLARATION = 286,
     SETS_DECLARATION = 287,
     DEFINITION_DECLARATION = 288,
     RULES_DECLARATION = 289,
     VARIABLE_DECLARATION = 290,
     COLON = 291,
     WHERE = 292,
     MATCHED_MATCHER = 293,
     MIXED_MATCHER = 294,
     FREELY_MATCHER = 295,
     IN = 296,
     AND = 297,
     COLON_SPACE = 298,
     SYMBOL_SPACE = 299,
     SEMI_COLON = 300,
     EQUALS = 301,
     CENTER_MARKER = 302,
     RULE_NAME = 303,
     SYMBOL = 304,
     NUMBER = 305,
     NUMBER_SPACE = 306,
     QUESTION_MARK = 307,
     EXCEPT = 308
   };
#endif
/* Tokens.  */
#define FREELY_INSERT 258
#define DIFFERENCE 259
#define INTERSECTION 260
#define UNION 261
#define PLUS 262
#define STAR 263
#define COMPLEMENT 264
#define TERM_COMPLEMENT 265
#define CONTAINMENT_ONCE 266
#define CONTAINMENT 267
#define POWER 268
#define RIGHT_PARENTHESIS 269
#define RIGHT_SQUARE_BRACKET 270
#define LEFT_PARENTHESIS 271
#define LEFT_SQUARE_BRACKET 272
#define RIGHT_CURLY_BRACKET 273
#define LEFT_CURLY_BRACKET 274
#define LEFT_RESTRICTION_ARROW 275
#define LEFT_ARROW 276
#define RIGHT_ARROW 277
#define LEFT_RIGHT_ARROW 278
#define RE_LEFT_RESTRICTION_ARROW 279
#define RE_LEFT_ARROW 280
#define RE_RIGHT_ARROW 281
#define RE_LEFT_RIGHT_ARROW 282
#define RE_RIGHT_SQUARE_BRACKET 283
#define RE_LEFT_SQUARE_BRACKET 284
#define ALPHABET_DECLARATION 285
#define DIACRITICS_DECLARATION 286
#define SETS_DECLARATION 287
#define DEFINITION_DECLARATION 288
#define RULES_DECLARATION 289
#define VARIABLE_DECLARATION 290
#define COLON 291
#define WHERE 292
#define MATCHED_MATCHER 293
#define MIXED_MATCHER 294
#define FREELY_MATCHER 295
#define IN 296
#define AND 297
#define COLON_SPACE 298
#define SYMBOL_SPACE 299
#define SEMI_COLON 300
#define EQUALS 301
#define CENTER_MARKER 302
#define RULE_NAME 303
#define SYMBOL 304
#define NUMBER 305
#define NUMBER_SPACE 306
#define QUESTION_MARK 307
#define EXCEPT 308




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 99 "htwolcpre1.yy"
 int symbol_number; 


/* Line 2068 of yacc.c  */
#line 160 "htwolcpre1.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


