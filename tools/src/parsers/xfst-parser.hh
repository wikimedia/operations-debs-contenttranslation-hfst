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
     APROPOS = 258,
     DESCRIBE = 259,
     ECHO = 260,
     SYSTEM = 261,
     QUIT = 262,
     HFST = 263,
     NAMETOKEN = 264,
     NAMECHAR = 265,
     GLOB = 266,
     PROTOTYPE = 267,
     DEFINE_NAME = 268,
     DEFINE_FUNCTION = 269,
     RANGE = 270,
     REDIRECT_IN = 271,
     REDIRECT_OUT = 272,
     SAVE_PROLOG = 273,
     LOWER = 274,
     FOR = 275,
     REVERSE = 276,
     VIEW = 277,
     LOADD = 278,
     PRINT_LABEL_COUNT = 279,
     TEST_OVERLAP = 280,
     TEST_NONNULL = 281,
     CONCATENATE = 282,
     LOADS = 283,
     INVERT = 284,
     PRINT_ALIASES = 285,
     PRINT_LABELS = 286,
     XFST_OPTIONAL = 287,
     PRINT_SHORTEST_STRING_SIZE = 288,
     READ_PROPS = 289,
     TEST_FUNCT = 290,
     PRINT_LABELMAPS = 291,
     SUBSTRING = 292,
     COMPOSE = 293,
     READ_SPACED = 294,
     TEST_UPPER_UNI = 295,
     COLLECT_EPSILON_LOOPS = 296,
     ZERO_PLUS = 297,
     INSPECT = 298,
     ROTATE = 299,
     PRINT_WORDS = 300,
     POP = 301,
     SAVE_SPACED = 302,
     DEFINE = 303,
     SHOW = 304,
     PRINT_LONGEST_STRING_SIZE = 305,
     TEST_EQ = 306,
     SORT = 307,
     SAVE_DEFINITIONS = 308,
     SAVE_DOT = 309,
     TEST_UPPER_BOUNDED = 310,
     COMPLETE = 311,
     PRINT_FILE_INFO = 312,
     INTERSECT = 313,
     END_SUB = 314,
     TURN = 315,
     PRINT_LIST = 316,
     SUBSTITUTE_SYMBOL = 317,
     APPLY_UP = 318,
     ONE_PLUS = 319,
     UNDEFINE = 320,
     EPSILON_REMOVE = 321,
     PRINT_RANDOM_WORDS = 322,
     CTRLD = 323,
     EXTRACT_UNAMBIGUOUS = 324,
     SEMICOLON = 325,
     PRINT_LOWER_WORDS = 326,
     READ_PROLOG = 327,
     CLEAR = 328,
     PRINT_SIGMA_COUNT = 329,
     SUBSTITUTE_NAMED = 330,
     PRINT_FLAGS = 331,
     SET = 332,
     NEGATE = 333,
     APPLY_DOWN = 334,
     PRINT_STACK = 335,
     SAVE_STACK = 336,
     PUSH = 337,
     TEST_LOWER_BOUNDED = 338,
     PRINT_DEFINED = 339,
     APPLY_MED = 340,
     SHOW_ALL = 341,
     PRINT_ARCCOUNT = 342,
     PRINT_SIZE = 343,
     TEST_NULL = 344,
     PRINT_RANDOM_UPPER = 345,
     PRINT_LONGEST_STRING = 346,
     UPPER_SIDE = 347,
     XFST_IGNORE = 348,
     TEST_UNAMBIGUOUS = 349,
     PRINT = 350,
     READ_TEXT = 351,
     UNLIST = 352,
     SUBSTITUTE_LABEL = 353,
     SAVE_DEFINITION = 354,
     ELIMINATE_FLAG = 355,
     EDIT_PROPS = 356,
     PRINT_UPPER_WORDS = 357,
     NAME = 358,
     EXTRACT_AMBIGUOUS = 359,
     DEFINE_ALIAS = 360,
     PRINT_RANDOM_LOWER = 361,
     CROSSPRODUCT = 362,
     COMPACT_SIGMA = 363,
     SOURCE = 364,
     AMBIGUOUS = 365,
     ELIMINATE_ALL = 366,
     PRINT_SIGMA = 367,
     PRINT_SHORTEST_STRING = 368,
     LEFT_PAREN = 369,
     PRINT_PROPS = 370,
     READ_REGEX = 371,
     DEFINE_LIST = 372,
     TEST_ID = 373,
     PRINT_LISTS = 374,
     TEST_SUBLANGUAGE = 375,
     TEST_LOWER_UNI = 376,
     COMPILE_REPLACE_UPPER = 377,
     CLEANUP = 378,
     ADD_PROPS = 379,
     PRINT_SIGMA_WORD_COUNT = 380,
     SHUFFLE = 381,
     COLON = 382,
     SAVE_TEXT = 383,
     DETERMINIZE = 384,
     SIGMA = 385,
     COMPILE_REPLACE_LOWER = 386,
     UNION = 387,
     PRINT_DIR = 388,
     LIST = 389,
     LOWER_SIDE = 390,
     MINIMIZE = 391,
     MINUS = 392,
     PRINT_NAME = 393,
     PRUNE_NET = 394,
     PUSH_DEFINED = 395,
     READ_LEXC = 396,
     READ_ATT = 397,
     TWOSIDED_FLAGS = 398,
     WRITE_ATT = 399,
     ASSERT = 400,
     LABEL_NET = 401,
     LOOKUP_OPTIMIZE = 402,
     REMOVE_OPTIMIZATION = 403,
     TEST_INFINITELY_AMBIGUOUS = 404,
     XFST_ERROR = 405,
     NEWLINE = 406,
     REGEX = 407,
     APPLY_INPUT = 408
   };
#endif
/* Tokens.  */
#define APROPOS 258
#define DESCRIBE 259
#define ECHO 260
#define SYSTEM 261
#define QUIT 262
#define HFST 263
#define NAMETOKEN 264
#define NAMECHAR 265
#define GLOB 266
#define PROTOTYPE 267
#define DEFINE_NAME 268
#define DEFINE_FUNCTION 269
#define RANGE 270
#define REDIRECT_IN 271
#define REDIRECT_OUT 272
#define SAVE_PROLOG 273
#define LOWER 274
#define FOR 275
#define REVERSE 276
#define VIEW 277
#define LOADD 278
#define PRINT_LABEL_COUNT 279
#define TEST_OVERLAP 280
#define TEST_NONNULL 281
#define CONCATENATE 282
#define LOADS 283
#define INVERT 284
#define PRINT_ALIASES 285
#define PRINT_LABELS 286
#define XFST_OPTIONAL 287
#define PRINT_SHORTEST_STRING_SIZE 288
#define READ_PROPS 289
#define TEST_FUNCT 290
#define PRINT_LABELMAPS 291
#define SUBSTRING 292
#define COMPOSE 293
#define READ_SPACED 294
#define TEST_UPPER_UNI 295
#define COLLECT_EPSILON_LOOPS 296
#define ZERO_PLUS 297
#define INSPECT 298
#define ROTATE 299
#define PRINT_WORDS 300
#define POP 301
#define SAVE_SPACED 302
#define DEFINE 303
#define SHOW 304
#define PRINT_LONGEST_STRING_SIZE 305
#define TEST_EQ 306
#define SORT 307
#define SAVE_DEFINITIONS 308
#define SAVE_DOT 309
#define TEST_UPPER_BOUNDED 310
#define COMPLETE 311
#define PRINT_FILE_INFO 312
#define INTERSECT 313
#define END_SUB 314
#define TURN 315
#define PRINT_LIST 316
#define SUBSTITUTE_SYMBOL 317
#define APPLY_UP 318
#define ONE_PLUS 319
#define UNDEFINE 320
#define EPSILON_REMOVE 321
#define PRINT_RANDOM_WORDS 322
#define CTRLD 323
#define EXTRACT_UNAMBIGUOUS 324
#define SEMICOLON 325
#define PRINT_LOWER_WORDS 326
#define READ_PROLOG 327
#define CLEAR 328
#define PRINT_SIGMA_COUNT 329
#define SUBSTITUTE_NAMED 330
#define PRINT_FLAGS 331
#define SET 332
#define NEGATE 333
#define APPLY_DOWN 334
#define PRINT_STACK 335
#define SAVE_STACK 336
#define PUSH 337
#define TEST_LOWER_BOUNDED 338
#define PRINT_DEFINED 339
#define APPLY_MED 340
#define SHOW_ALL 341
#define PRINT_ARCCOUNT 342
#define PRINT_SIZE 343
#define TEST_NULL 344
#define PRINT_RANDOM_UPPER 345
#define PRINT_LONGEST_STRING 346
#define UPPER_SIDE 347
#define XFST_IGNORE 348
#define TEST_UNAMBIGUOUS 349
#define PRINT 350
#define READ_TEXT 351
#define UNLIST 352
#define SUBSTITUTE_LABEL 353
#define SAVE_DEFINITION 354
#define ELIMINATE_FLAG 355
#define EDIT_PROPS 356
#define PRINT_UPPER_WORDS 357
#define NAME 358
#define EXTRACT_AMBIGUOUS 359
#define DEFINE_ALIAS 360
#define PRINT_RANDOM_LOWER 361
#define CROSSPRODUCT 362
#define COMPACT_SIGMA 363
#define SOURCE 364
#define AMBIGUOUS 365
#define ELIMINATE_ALL 366
#define PRINT_SIGMA 367
#define PRINT_SHORTEST_STRING 368
#define LEFT_PAREN 369
#define PRINT_PROPS 370
#define READ_REGEX 371
#define DEFINE_LIST 372
#define TEST_ID 373
#define PRINT_LISTS 374
#define TEST_SUBLANGUAGE 375
#define TEST_LOWER_UNI 376
#define COMPILE_REPLACE_UPPER 377
#define CLEANUP 378
#define ADD_PROPS 379
#define PRINT_SIGMA_WORD_COUNT 380
#define SHUFFLE 381
#define COLON 382
#define SAVE_TEXT 383
#define DETERMINIZE 384
#define SIGMA 385
#define COMPILE_REPLACE_LOWER 386
#define UNION 387
#define PRINT_DIR 388
#define LIST 389
#define LOWER_SIDE 390
#define MINIMIZE 391
#define MINUS 392
#define PRINT_NAME 393
#define PRUNE_NET 394
#define PUSH_DEFINED 395
#define READ_LEXC 396
#define READ_ATT 397
#define TWOSIDED_FLAGS 398
#define WRITE_ATT 399
#define ASSERT 400
#define LABEL_NET 401
#define LOOKUP_OPTIMIZE 402
#define REMOVE_OPTIMIZATION 403
#define TEST_INFINITELY_AMBIGUOUS 404
#define XFST_ERROR 405
#define NEWLINE 406
#define REGEX 407
#define APPLY_INPUT 408




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 52 "xfst-parser.yy"

    char* name;
    char* text;
    char** list;
    char* file;
    void* nothing;



/* Line 2068 of yacc.c  */
#line 366 "xfst-parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE hxfstlval;

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

extern YYLTYPE hxfstlloc;

