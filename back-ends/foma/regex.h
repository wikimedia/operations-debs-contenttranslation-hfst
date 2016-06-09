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
     NET = 258,
     END = 259,
     LBRACKET = 260,
     RBRACKET = 261,
     LPAREN = 262,
     RPAREN = 263,
     ENDM = 264,
     ENDD = 265,
     CRESTRICT = 266,
     CONTAINS = 267,
     CONTAINS_OPT_ONE = 268,
     CONTAINS_ONE = 269,
     XUPPER = 270,
     XLOWER = 271,
     FLAG_ELIMINATE = 272,
     IGNORE_ALL = 273,
     IGNORE_INTERNAL = 274,
     CONTEXT = 275,
     NCONCAT = 276,
     MNCONCAT = 277,
     MORENCONCAT = 278,
     LESSNCONCAT = 279,
     DOUBLE_COMMA = 280,
     COMMA = 281,
     SHUFFLE = 282,
     PRECEDES = 283,
     FOLLOWS = 284,
     RIGHT_QUOTIENT = 285,
     LEFT_QUOTIENT = 286,
     INTERLEAVE_QUOTIENT = 287,
     UQUANT = 288,
     EQUANT = 289,
     VAR = 290,
     IN = 291,
     IMPLIES = 292,
     BICOND = 293,
     EQUALS = 294,
     NEQ = 295,
     SUBSTITUTE = 296,
     SUCCESSOR_OF = 297,
     PRIORITY_UNION_U = 298,
     PRIORITY_UNION_L = 299,
     LENIENT_COMPOSE = 300,
     TRIPLE_DOT = 301,
     LDOT = 302,
     RDOT = 303,
     FUNCTION = 304,
     SUBVAL = 305,
     ISUNAMBIGUOUS = 306,
     ISIDENTITY = 307,
     ISFUNCTIONAL = 308,
     NOTID = 309,
     LOWERUNIQ = 310,
     LOWERUNIQEPS = 311,
     ALLFINAL = 312,
     UNAMBIGUOUSPART = 313,
     AMBIGUOUSPART = 314,
     AMBIGUOUSDOMAIN = 315,
     EQSUBSTRINGS = 316,
     LETTERMACHINE = 317,
     MARKFSMTAIL = 318,
     MARKFSMTAILLOOP = 319,
     MARKFSMMIDLOOP = 320,
     MARKFSMLOOP = 321,
     ADDSINK = 322,
     LEFTREWR = 323,
     FLATTEN = 324,
     SUBLABEL = 325,
     CLOSESIGMA = 326,
     CLOSESIGMAUNK = 327,
     ARROW = 328,
     DIRECTION = 329,
     HIGH_CROSS_PRODUCT = 330,
     CROSS_PRODUCT = 331,
     COMPOSE = 332,
     MINUS = 333,
     INTERSECT = 334,
     UNION = 335,
     COMPLEMENT = 336,
     INVERSE = 337,
     REVERSE = 338,
     KLEENE_PLUS = 339,
     KLEENE_STAR = 340,
     TERM_NEGATION = 341
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 186 "regex.y"

     char *string;
     struct fsm *net;
     int  type;



/* Line 2068 of yacc.c  */
#line 144 "regex.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif



#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



