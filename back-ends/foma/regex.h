/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     ARROW = 325,
     DIRECTION = 326,
     HIGH_CROSS_PRODUCT = 327,
     CROSS_PRODUCT = 328,
     COMPOSE = 329,
     MINUS = 330,
     INTERSECT = 331,
     UNION = 332,
     COMPLEMENT = 333,
     INVERSE = 334,
     REVERSE = 335,
     KLEENE_PLUS = 336,
     KLEENE_STAR = 337,
     TERM_NEGATION = 338
   };
#endif
/* Tokens.  */
#define NET 258
#define END 259
#define LBRACKET 260
#define RBRACKET 261
#define LPAREN 262
#define RPAREN 263
#define ENDM 264
#define ENDD 265
#define CRESTRICT 266
#define CONTAINS 267
#define CONTAINS_OPT_ONE 268
#define CONTAINS_ONE 269
#define XUPPER 270
#define XLOWER 271
#define FLAG_ELIMINATE 272
#define IGNORE_ALL 273
#define IGNORE_INTERNAL 274
#define CONTEXT 275
#define NCONCAT 276
#define MNCONCAT 277
#define MORENCONCAT 278
#define LESSNCONCAT 279
#define DOUBLE_COMMA 280
#define COMMA 281
#define SHUFFLE 282
#define PRECEDES 283
#define FOLLOWS 284
#define RIGHT_QUOTIENT 285
#define LEFT_QUOTIENT 286
#define INTERLEAVE_QUOTIENT 287
#define UQUANT 288
#define EQUANT 289
#define VAR 290
#define IN 291
#define IMPLIES 292
#define BICOND 293
#define EQUALS 294
#define NEQ 295
#define SUBSTITUTE 296
#define SUCCESSOR_OF 297
#define PRIORITY_UNION_U 298
#define PRIORITY_UNION_L 299
#define LENIENT_COMPOSE 300
#define TRIPLE_DOT 301
#define LDOT 302
#define RDOT 303
#define FUNCTION 304
#define SUBVAL 305
#define ISUNAMBIGUOUS 306
#define ISIDENTITY 307
#define ISFUNCTIONAL 308
#define NOTID 309
#define LOWERUNIQ 310
#define LOWERUNIQEPS 311
#define ALLFINAL 312
#define UNAMBIGUOUSPART 313
#define AMBIGUOUSPART 314
#define AMBIGUOUSDOMAIN 315
#define EQSUBSTRINGS 316
#define LETTERMACHINE 317
#define MARKFSMTAIL 318
#define MARKFSMTAILLOOP 319
#define MARKFSMMIDLOOP 320
#define MARKFSMLOOP 321
#define ADDSINK 322
#define LEFTREWR 323
#define FLATTEN 324
#define ARROW 325
#define DIRECTION 326
#define HIGH_CROSS_PRODUCT 327
#define CROSS_PRODUCT 328
#define COMPOSE 329
#define MINUS 330
#define INTERSECT 331
#define UNION 332
#define COMPLEMENT 333
#define INVERSE 334
#define REVERSE 335
#define KLEENE_PLUS 336
#define KLEENE_STAR 337
#define TERM_NEGATION 338




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 188 "regex.y"
{
     char *string;
     struct fsm *net;
     int  type;
}
/* Line 1529 of yacc.c.  */
#line 221 "regex.h"
        YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
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


