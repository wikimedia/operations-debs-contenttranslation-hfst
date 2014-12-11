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
     LEFT_RESTRICTION_ARROW = 273,
     LEFT_ARROW = 274,
     RIGHT_ARROW = 275,
     LEFT_RIGHT_ARROW = 276,
     RE_LEFT_RESTRICTION_ARROW = 277,
     RE_LEFT_ARROW = 278,
     RE_RIGHT_ARROW = 279,
     RE_LEFT_RIGHT_ARROW = 280,
     RE_RIGHT_SQUARE_BRACKET = 281,
     RE_LEFT_SQUARE_BRACKET = 282,
     ALPHABET_DECLARATION = 283,
     DIACRITICS_DECLARATION = 284,
     SETS_DECLARATION = 285,
     DEFINITION_DECLARATION = 286,
     RULES_DECLARATION = 287,
     PAIR_SEPARATOR = 288,
     SYMBOL = 289,
     SEMI_COLON = 290,
     SET_NAME = 291,
     DEFINITION_NAME = 292,
     EQUALS = 293,
     CENTER_MARKER = 294,
     RULE_NAME = 295,
     NUMBER = 296,
     QUESTION_MARK = 297,
     EXCEPT = 298
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
#define LEFT_RESTRICTION_ARROW 273
#define LEFT_ARROW 274
#define RIGHT_ARROW 275
#define LEFT_RIGHT_ARROW 276
#define RE_LEFT_RESTRICTION_ARROW 277
#define RE_LEFT_ARROW 278
#define RE_RIGHT_ARROW 279
#define RE_LEFT_RIGHT_ARROW 280
#define RE_RIGHT_SQUARE_BRACKET 281
#define RE_LEFT_SQUARE_BRACKET 282
#define ALPHABET_DECLARATION 283
#define DIACRITICS_DECLARATION 284
#define SETS_DECLARATION 285
#define DEFINITION_DECLARATION 286
#define RULES_DECLARATION 287
#define PAIR_SEPARATOR 288
#define SYMBOL 289
#define SEMI_COLON 290
#define SET_NAME 291
#define DEFINITION_NAME 292
#define EQUALS 293
#define CENTER_MARKER 294
#define RULE_NAME 295
#define NUMBER 296
#define QUESTION_MARK 297
#define EXCEPT 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 68 "htwolcpre2.yy"
 int symbol_number; 


/* Line 2068 of yacc.c  */
#line 140 "htwolcpre2.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


