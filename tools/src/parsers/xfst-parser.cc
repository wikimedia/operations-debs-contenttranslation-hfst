/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         hxfstparse
#define yylex           hxfstlex
#define yyerror         hxfsterror
#define yylval          hxfstlval
#define yychar          hxfstchar
#define yydebug         hxfstdebug
#define yynerrs         hxfstnerrs
#define yylloc          hxfstlloc

/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "xfst-parser.yy"

//! @file xfst-parser.yy
//!
//! @brief A parser for xfst
//!
//! @author Tommi A. Pirinen


//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, version 3 of the License.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <cstdlib>
#include <cstdio>

#include <string>
using std::string;

namespace hfst {
  class HfstTransducer;
}

#include "XfstCompiler.h"
#include "xfst-utils.h"

// obligatory yacc stuff
extern int hxfstlineno;
void hxfsterror(const char *text);
int hxfstlex(void);



/* Line 268 of yacc.c  */
#line 123 "xfst-parser.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 293 of yacc.c  */
#line 52 "xfst-parser.yy"

    char* name;
    char* text;
    char** list;
    char* file;
    void* nothing;



/* Line 293 of yacc.c  */
#line 475 "xfst-parser.cc"
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


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 500 "xfst-parser.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  347
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   925

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  154
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  260
/* YYNRULES -- Number of states.  */
#define YYNSTATES  537

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   408

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    17,    21,    24,
      27,    31,    35,    39,    44,    47,    51,    55,    59,    64,
      68,    72,    77,    80,    83,    86,    89,    92,    97,   103,
     109,   114,   116,   119,   122,   126,   130,   134,   138,   141,
     144,   147,   150,   154,   157,   160,   163,   167,   171,   176,
     179,   182,   186,   189,   191,   193,   195,   199,   201,   204,
     209,   213,   216,   219,   222,   225,   228,   230,   233,   236,
     239,   242,   245,   248,   251,   254,   257,   261,   265,   269,
     273,   277,   281,   285,   289,   293,   297,   301,   305,   311,
     317,   323,   327,   330,   334,   338,   341,   345,   348,   353,
     357,   361,   364,   368,   371,   375,   378,   382,   386,   389,
     393,   396,   401,   405,   409,   412,   416,   419,   423,   426,
     430,   433,   437,   440,   444,   447,   452,   458,   462,   465,
     470,   474,   479,   485,   489,   492,   497,   501,   506,   512,
     516,   519,   524,   528,   533,   539,   543,   546,   551,   555,
     560,   566,   570,   573,   578,   582,   587,   593,   597,   600,
     605,   609,   613,   617,   620,   624,   627,   631,   635,   639,
     642,   646,   649,   653,   657,   660,   664,   668,   671,   675,
     678,   682,   686,   690,   693,   699,   704,   709,   713,   717,
     720,   724,   728,   732,   735,   739,   742,   746,   749,   753,
     756,   760,   763,   766,   770,   775,   779,   783,   787,   791,
     795,   799,   803,   808,   812,   816,   819,   823,   827,   833,
     836,   839,   842,   845,   848,   851,   854,   857,   860,   863,
     866,   869,   872,   875,   878,   881,   884,   887,   890,   893,
     896,   899,   902,   905,   908,   911,   914,   917,   920,   922,
     925,   927,   928,   931,   934,   936,   939,   941,   945,   947,
     950
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     155,     0,    -1,   156,    -1,   156,    68,    -1,   156,   157,
      -1,   157,    -1,   124,    16,   158,    -1,   124,   160,    68,
      -1,   101,   158,    -1,    63,   158,    -1,    63,   153,   158,
      -1,    63,     9,   158,    -1,    63,    16,   158,    -1,    63,
     158,   160,    59,    -1,    79,   158,    -1,    79,   153,   158,
      -1,    79,     9,   158,    -1,    79,    16,   158,    -1,    79,
     158,   160,    59,    -1,    85,     9,   158,    -1,    85,    16,
     158,    -1,    85,   158,   160,    59,    -1,   147,   158,    -1,
     148,   158,    -1,   110,   158,    -1,   104,   158,    -1,    69,
     158,    -1,   105,     9,   159,   158,    -1,   105,     9,   158,
     160,    59,    -1,   134,     9,   160,    70,   158,    -1,   134,
       9,    15,   158,    -1,    13,    -1,    13,   152,    -1,    14,
     152,    -1,    65,   160,   158,    -1,    97,     9,   158,    -1,
     103,     9,   158,    -1,    23,     9,   158,    -1,     3,   158,
      -1,     4,   158,    -1,    73,   158,    -1,    46,   158,    -1,
     140,     9,   158,    -1,   140,   158,    -1,    60,   158,    -1,
      44,   158,    -1,    28,    16,   158,    -1,    28,     9,   158,
      -1,    28,     9,    70,   158,    -1,    41,   158,    -1,   108,
     158,    -1,   100,     9,   158,    -1,   111,   158,    -1,     5,
      -1,     7,    -1,     8,    -1,   109,     9,   158,    -1,     6,
      -1,    22,   158,    -1,    77,     9,     9,   158,    -1,    49,
       9,   158,    -1,    86,   158,    -1,   143,   158,    -1,    51,
     158,    -1,    35,   158,    -1,   118,   158,    -1,   149,    -1,
      83,   158,    -1,   121,   158,    -1,    55,   158,    -1,    40,
     158,    -1,    26,   158,    -1,    89,   158,    -1,    25,   158,
      -1,   120,   158,    -1,    94,   158,    -1,   145,    51,   158,
      -1,   145,    35,   158,    -1,   145,   118,   158,    -1,   145,
      83,   158,    -1,   145,   121,   158,    -1,   145,    55,   158,
      -1,   145,    40,   158,    -1,   145,    26,   158,    -1,   145,
      89,   158,    -1,   145,    25,   158,    -1,   145,   120,   158,
      -1,   145,    94,   158,    -1,    75,     9,    20,     9,   158,
      -1,    98,   162,    20,   161,   158,    -1,    62,   160,    20,
       9,   158,    -1,    30,    17,   158,    -1,    30,   158,    -1,
      87,    17,   158,    -1,    87,     9,   158,    -1,    87,   158,
      -1,    84,    17,   158,    -1,    84,   158,    -1,   133,    11,
      17,   158,    -1,   133,    11,   158,    -1,   133,    17,   158,
      -1,   133,   158,    -1,    57,    17,   158,    -1,    57,   158,
      -1,    76,    17,   158,    -1,    76,   158,    -1,    31,     9,
     158,    -1,    31,    17,   158,    -1,    31,   158,    -1,    24,
      17,   158,    -1,    24,   158,    -1,    61,     9,    17,   158,
      -1,    61,     9,   158,    -1,   119,    17,   158,    -1,   119,
     158,    -1,    91,    17,   158,    -1,    91,   158,    -1,    50,
      17,   158,    -1,    50,   158,    -1,   138,    17,   158,    -1,
     138,   158,    -1,   113,    17,   158,    -1,   113,   158,    -1,
      33,    17,   158,    -1,    33,   158,    -1,    71,     9,     9,
     158,    -1,    71,     9,     9,    17,   158,    -1,    71,     9,
     158,    -1,    71,   158,    -1,    71,     9,    17,   158,    -1,
      71,    17,   158,    -1,   106,     9,     9,   158,    -1,   106,
       9,     9,    17,   158,    -1,   106,     9,   158,    -1,   106,
     158,    -1,   106,     9,    17,   158,    -1,   106,    17,   158,
      -1,   102,     9,     9,   158,    -1,   102,     9,     9,    17,
     158,    -1,   102,     9,   158,    -1,   102,   158,    -1,   102,
       9,    17,   158,    -1,   102,    17,   158,    -1,    90,     9,
       9,   158,    -1,    90,     9,     9,    17,   158,    -1,    90,
       9,   158,    -1,    90,   158,    -1,    90,     9,    17,   158,
      -1,    90,    17,   158,    -1,    45,     9,     9,   158,    -1,
      45,     9,     9,    17,   158,    -1,    45,     9,   158,    -1,
      45,   158,    -1,    45,     9,    17,   158,    -1,    45,    17,
     158,    -1,    67,     9,     9,   158,    -1,    67,     9,     9,
      17,   158,    -1,    67,     9,   158,    -1,    67,   158,    -1,
      67,     9,    17,   158,    -1,    67,    17,   158,    -1,    95,
       9,   158,    -1,    95,    17,   158,    -1,    95,   158,    -1,
     115,     9,   158,    -1,   115,   158,    -1,   115,    17,   158,
      -1,   112,     9,   158,    -1,   112,    17,   158,    -1,   112,
     158,    -1,    74,    17,   158,    -1,    74,   158,    -1,   125,
       9,   158,    -1,   125,    17,   158,    -1,   125,   158,    -1,
      88,     9,   158,    -1,    88,    17,   158,    -1,    88,   158,
      -1,    80,    17,   158,    -1,    80,   158,    -1,    36,    17,
     158,    -1,    54,     9,   158,    -1,    54,    17,   158,    -1,
      54,   158,    -1,    99,     9,   114,    17,   158,    -1,    99,
       9,   114,   158,    -1,    99,     9,    17,   158,    -1,    99,
       9,   158,    -1,    53,    17,   158,    -1,    53,   158,    -1,
      81,     9,   158,    -1,    18,    17,   158,    -1,    18,     9,
     158,    -1,    18,   158,    -1,    47,    17,   158,    -1,    47,
     158,    -1,   128,    17,   158,    -1,   128,   158,    -1,    34,
      16,   158,    -1,    34,   158,    -1,    72,     9,   158,    -1,
      72,   158,    -1,   116,   152,    -1,   116,    16,   158,    -1,
     116,   160,    70,   158,    -1,    39,    16,   158,    -1,    39,
       9,   158,    -1,    39,   160,    68,    -1,    96,    16,   158,
      -1,    96,     9,   158,    -1,    96,   160,    68,    -1,   141,
       9,   158,    -1,   141,     9,    70,   158,    -1,   141,   160,
      68,    -1,   142,     9,   158,    -1,   144,   158,    -1,   144,
      17,   158,    -1,   144,     9,   158,    -1,   144,     9,     9,
       9,   158,    -1,   123,   158,    -1,    56,   158,    -1,    38,
     158,    -1,    27,   158,    -1,   137,   158,    -1,   107,   158,
      -1,   136,   158,    -1,   129,   158,    -1,    66,   158,    -1,
     139,   158,    -1,    93,   158,    -1,    58,   158,    -1,    43,
     158,    -1,    29,   158,    -1,   135,   158,    -1,    92,   158,
      -1,    78,   158,    -1,    64,   158,    -1,    42,   158,    -1,
      32,   158,    -1,    21,   158,    -1,   126,   158,    -1,   130,
     158,    -1,    52,   158,    -1,    37,   158,    -1,   132,   158,
      -1,   146,   158,    -1,   131,   158,    -1,   122,   158,    -1,
     158,    -1,     9,   158,    -1,   151,    -1,    -1,   159,     9,
      -1,   159,    70,    -1,     9,    -1,   160,     9,    -1,     9,
      -1,     9,   127,     9,    -1,     9,    -1,   162,   161,    -1,
     161,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   100,   103,   104,   107,   112,   116,   121,
     124,   127,   131,   136,   140,   143,   146,   150,   155,   159,
     163,   168,   172,   175,   179,   183,   187,   192,   197,   202,
     207,   214,   218,   223,   228,   232,   236,   240,   245,   249,
     253,   256,   259,   263,   266,   269,   272,   276,   280,   285,
     288,   292,   296,   300,   304,   309,   313,   317,   321,   326,
     335,   339,   342,   346,   349,   352,   355,   358,   361,   364,
     367,   370,   373,   376,   379,   382,   386,   389,   392,   395,
     398,   401,   404,   407,   410,   413,   416,   419,   423,   428,
     433,   439,   444,   447,   452,   461,   464,   469,   472,   478,
     482,   487,   490,   495,   498,   503,   506,   510,   515,   518,
     523,   526,   532,   536,   541,   544,   549,   552,   557,   560,
     565,   568,   573,   576,   581,   584,   588,   594,   601,   604,
     613,   618,   622,   628,   635,   638,   647,   652,   656,   662,
     669,   672,   681,   686,   690,   696,   703,   706,   715,   720,
     724,   730,   737,   740,   749,   754,   758,   764,   771,   774,
     783,   788,   792,   797,   800,   804,   807,   812,   816,   821,
     824,   829,   832,   841,   846,   849,   853,   858,   861,   866,
     869,   875,   879,   884,   887,   891,   895,   899,   903,   906,
     909,   913,   918,   923,   926,   931,   934,   939,   943,   948,
     951,   956,   959,   963,   968,   972,   976,   980,   984,   988,
     992,   996,  1000,  1004,  1007,  1011,  1014,  1020,  1026,  1034,
    1037,  1040,  1043,  1046,  1049,  1052,  1055,  1058,  1061,  1064,
    1067,  1070,  1073,  1076,  1079,  1082,  1085,  1088,  1091,  1094,
    1097,  1100,  1103,  1106,  1109,  1112,  1115,  1118,  1121,  1124,
    1130,  1130,  1132,  1153,  1156,  1161,  1182,  1187,  1190,  1195,
    1216
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "APROPOS", "DESCRIBE", "ECHO", "SYSTEM",
  "QUIT", "HFST", "NAMETOKEN", "NAMECHAR", "GLOB", "PROTOTYPE",
  "DEFINE_NAME", "DEFINE_FUNCTION", "RANGE", "REDIRECT_IN", "REDIRECT_OUT",
  "SAVE_PROLOG", "LOWER", "FOR", "REVERSE", "VIEW", "LOADD",
  "PRINT_LABEL_COUNT", "TEST_OVERLAP", "TEST_NONNULL", "CONCATENATE",
  "LOADS", "INVERT", "PRINT_ALIASES", "PRINT_LABELS", "XFST_OPTIONAL",
  "PRINT_SHORTEST_STRING_SIZE", "READ_PROPS", "TEST_FUNCT",
  "PRINT_LABELMAPS", "SUBSTRING", "COMPOSE", "READ_SPACED",
  "TEST_UPPER_UNI", "COLLECT_EPSILON_LOOPS", "ZERO_PLUS", "INSPECT",
  "ROTATE", "PRINT_WORDS", "POP", "SAVE_SPACED", "DEFINE", "SHOW",
  "PRINT_LONGEST_STRING_SIZE", "TEST_EQ", "SORT", "SAVE_DEFINITIONS",
  "SAVE_DOT", "TEST_UPPER_BOUNDED", "COMPLETE", "PRINT_FILE_INFO",
  "INTERSECT", "END_SUB", "TURN", "PRINT_LIST", "SUBSTITUTE_SYMBOL",
  "APPLY_UP", "ONE_PLUS", "UNDEFINE", "EPSILON_REMOVE",
  "PRINT_RANDOM_WORDS", "CTRLD", "EXTRACT_UNAMBIGUOUS", "SEMICOLON",
  "PRINT_LOWER_WORDS", "READ_PROLOG", "CLEAR", "PRINT_SIGMA_COUNT",
  "SUBSTITUTE_NAMED", "PRINT_FLAGS", "SET", "NEGATE", "APPLY_DOWN",
  "PRINT_STACK", "SAVE_STACK", "PUSH", "TEST_LOWER_BOUNDED",
  "PRINT_DEFINED", "APPLY_MED", "SHOW_ALL", "PRINT_ARCCOUNT", "PRINT_SIZE",
  "TEST_NULL", "PRINT_RANDOM_UPPER", "PRINT_LONGEST_STRING", "UPPER_SIDE",
  "XFST_IGNORE", "TEST_UNAMBIGUOUS", "PRINT", "READ_TEXT", "UNLIST",
  "SUBSTITUTE_LABEL", "SAVE_DEFINITION", "ELIMINATE_FLAG", "EDIT_PROPS",
  "PRINT_UPPER_WORDS", "NAME", "EXTRACT_AMBIGUOUS", "DEFINE_ALIAS",
  "PRINT_RANDOM_LOWER", "CROSSPRODUCT", "COMPACT_SIGMA", "SOURCE",
  "AMBIGUOUS", "ELIMINATE_ALL", "PRINT_SIGMA", "PRINT_SHORTEST_STRING",
  "LEFT_PAREN", "PRINT_PROPS", "READ_REGEX", "DEFINE_LIST", "TEST_ID",
  "PRINT_LISTS", "TEST_SUBLANGUAGE", "TEST_LOWER_UNI",
  "COMPILE_REPLACE_UPPER", "CLEANUP", "ADD_PROPS",
  "PRINT_SIGMA_WORD_COUNT", "SHUFFLE", "COLON", "SAVE_TEXT", "DETERMINIZE",
  "SIGMA", "COMPILE_REPLACE_LOWER", "UNION", "PRINT_DIR", "LIST",
  "LOWER_SIDE", "MINIMIZE", "MINUS", "PRINT_NAME", "PRUNE_NET",
  "PUSH_DEFINED", "READ_LEXC", "READ_ATT", "TWOSIDED_FLAGS", "WRITE_ATT",
  "ASSERT", "LABEL_NET", "LOOKUP_OPTIMIZE", "REMOVE_OPTIMIZATION",
  "TEST_INFINITELY_AMBIGUOUS", "XFST_ERROR", "NEWLINE", "REGEX",
  "APPLY_INPUT", "$accept", "XFST_SCRIPT", "COMMAND_LIST", "COMMAND",
  "END_COMMAND", "COMMAND_SEQUENCE", "NAMETOKEN_LIST", "LABEL",
  "LABEL_LIST", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   154,   155,   155,   156,   156,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   157,   157,   157,
     158,   158,   159,   159,   159,   160,   160,   161,   161,   162,
     162
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     3,     3,     2,     2,
       3,     3,     3,     4,     2,     3,     3,     3,     4,     3,
       3,     4,     2,     2,     2,     2,     2,     4,     5,     5,
       4,     1,     2,     2,     3,     3,     3,     3,     2,     2,
       2,     2,     3,     2,     2,     2,     3,     3,     4,     2,
       2,     3,     2,     1,     1,     1,     3,     1,     2,     4,
       3,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     5,
       5,     3,     2,     3,     3,     2,     3,     2,     4,     3,
       3,     2,     3,     2,     3,     2,     3,     3,     2,     3,
       2,     4,     3,     3,     2,     3,     2,     3,     2,     3,
       2,     3,     2,     3,     2,     4,     5,     3,     2,     4,
       3,     4,     5,     3,     2,     4,     3,     4,     5,     3,
       2,     4,     3,     4,     5,     3,     2,     4,     3,     4,
       5,     3,     2,     4,     3,     4,     5,     3,     2,     4,
       3,     3,     3,     2,     3,     2,     3,     3,     3,     2,
       3,     2,     3,     3,     2,     3,     3,     2,     3,     2,
       3,     3,     3,     2,     5,     4,     4,     3,     3,     2,
       3,     3,     3,     2,     3,     2,     3,     2,     3,     2,
       3,     2,     2,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     3,     2,     3,     3,     5,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       1,     0,     2,     2,     1,     2,     1,     3,     1,     2,
       1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     251,   251,   251,    53,    57,    54,    55,   251,    31,     0,
     251,   251,   251,     0,   251,   251,   251,   251,     0,   251,
     251,   251,   251,   251,   251,   251,     0,   251,   251,     0,
     251,   251,   251,   251,   251,   251,   251,   251,     0,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,     0,
       0,   251,   251,     0,   251,   251,   251,   251,   251,   251,
     251,     0,   251,     0,   251,   251,   251,     0,   251,   251,
       0,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,     0,     0,     0,     0,     0,   251,   251,     0,   251,
       0,   251,   251,   251,     0,   251,   251,   251,   251,   251,
       0,   251,   251,   251,   251,   251,   251,     0,   251,   251,
     251,   251,   251,   251,   251,   251,     0,   251,   251,   251,
     251,   251,   251,     0,     0,   251,   251,     0,   251,   251,
     251,    66,   250,     0,     2,     5,   248,    38,    39,   249,
      32,    33,   251,   251,   193,   239,    58,   251,   251,   110,
      73,    71,   222,   251,   251,   232,   251,    92,   251,   251,
     108,   238,   251,   124,   251,   199,    64,   251,   243,   221,
     251,   251,     0,    70,    49,   237,   231,    45,   251,   251,
     152,    41,   251,   195,   251,   251,   118,    63,   242,   251,
     189,   251,   251,   183,    69,   220,   251,   103,   230,    44,
     251,   256,     0,   251,   251,   251,     9,   236,   251,   227,
     251,   251,   158,    26,   251,   251,   128,   251,   201,    40,
     251,   171,     0,   251,   105,     0,   235,   251,   251,   251,
      14,   251,   179,   251,    67,   251,    97,   251,   251,     0,
      61,   251,   251,    95,   251,   251,   177,    72,   251,   251,
     146,   251,   116,   234,   229,    75,   251,   251,   163,   251,
     251,     0,   251,   258,   260,     0,   251,   251,     8,   251,
     251,   140,   251,    25,     0,   251,   251,   134,   224,    50,
     251,    24,    52,   251,   251,   169,   251,   122,   251,   251,
     165,   251,   202,     0,    65,   251,   114,    74,    68,   247,
     219,   251,     0,   251,   251,   174,   240,   251,   197,   226,
     241,   246,   244,   251,   251,   101,     0,   233,   225,   223,
     251,   120,   228,   251,    43,   251,     0,   251,    62,   251,
     251,   215,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   245,    22,    23,     1,     3,     4,
     192,   191,    37,   109,   251,    47,    46,    91,   106,   107,
     123,   198,   180,   206,   205,   255,   207,   251,   251,   151,
     154,   194,    60,   117,   188,   181,   182,   102,   251,   112,
       0,    11,    12,    10,     0,    34,   251,   251,   157,   160,
     251,   251,   127,   130,   200,   170,     0,   104,   251,    16,
      17,    15,     0,   178,   190,    96,    19,    20,     0,    94,
      93,   175,   176,   251,   251,   145,   148,   115,   161,   162,
     209,   208,   210,    35,     0,     0,   259,   251,   251,   187,
      51,   251,   251,   139,   142,    36,   254,     0,   251,   251,
     251,   133,   136,    56,   167,   168,   121,   164,   166,   203,
     251,   113,     6,     7,   172,   173,   196,   251,    99,   100,
     251,     0,   119,    42,   251,   211,   213,   214,     0,   217,
     216,    85,    83,    77,    82,    76,    81,    79,    84,    87,
      78,    86,    80,    48,   251,   149,   153,   111,   251,    13,
     251,   155,   159,   251,   125,   129,   251,    59,    18,    21,
     251,   143,   147,   257,   251,   186,   251,   185,   251,   137,
     141,     0,   252,   253,    27,   251,   131,   135,   204,    98,
      30,   251,   212,   251,   150,    90,   156,   126,    88,   144,
      89,   184,   138,    28,   132,    29,   218
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   133,   134,   135,   136,   438,   172,   264,   265
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -264
static const yytype_int16 yypact[] =
{
     677,  -144,  -144,  -264,  -264,  -264,  -264,  -144,  -104,  -103,
       8,  -144,  -144,    71,    45,  -144,  -144,  -144,   288,  -144,
      67,    43,  -144,    82,   -12,  -144,    -9,  -144,  -144,   359,
    -144,  -144,  -144,  -144,  -144,    72,  -144,   116,    74,   147,
    -144,  -144,   169,   106,  -144,  -144,   198,  -144,  -144,    97,
     117,   127,  -144,   117,  -144,   113,  -144,   156,    -6,  -144,
     214,   151,   221,   188,  -144,   140,   225,   196,  -144,   232,
     135,  -144,   158,   159,  -144,   163,   237,  -144,  -144,  -144,
     165,   365,   197,   242,   254,   362,  -144,   170,   370,  -144,
     371,   176,  -144,  -144,   373,  -144,  -144,   208,   253,   212,
      -4,  -144,   278,  -144,  -144,  -144,  -144,   375,   236,  -144,
     282,  -144,  -144,  -144,  -144,   121,   384,  -144,  -144,  -144,
     284,  -144,    57,   386,   387,  -144,   243,   804,  -144,  -144,
    -144,  -264,  -264,   399,   528,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -144,  -144,  -264,  -264,  -264,  -144,  -144,  -264,
    -264,  -264,  -264,    61,  -144,  -264,  -144,  -264,  -144,  -144,
    -264,  -264,  -144,  -264,  -144,  -264,  -264,  -144,  -264,  -264,
    -144,  -144,    19,  -264,  -264,  -264,  -264,  -264,   267,  -144,
    -264,  -264,  -144,  -264,  -144,  -144,  -264,  -264,  -264,  -144,
    -264,  -144,  -144,  -264,  -264,  -264,  -144,  -264,  -264,  -264,
     291,  -264,   191,  -144,  -144,  -144,   117,  -264,    73,  -264,
     272,  -144,  -264,  -264,   306,  -144,  -264,  -144,  -264,  -264,
    -144,  -264,   380,  -144,  -264,   392,  -264,  -144,  -144,  -144,
     117,  -144,  -264,  -144,  -264,  -144,  -264,  -144,  -144,   117,
    -264,  -144,  -144,  -264,  -144,  -144,  -264,  -264,   334,  -144,
    -264,  -144,  -264,  -264,  -264,  -264,  -144,  -144,  -264,  -144,
    -144,   287,  -144,   275,  -264,   353,    20,  -144,  -264,   335,
    -144,  -264,  -144,  -264,   126,   337,  -144,  -264,  -264,  -264,
    -144,  -264,  -264,  -144,  -144,  -264,  -144,  -264,  -144,  -144,
    -264,  -144,  -264,   128,  -264,  -144,  -264,  -264,  -264,  -264,
    -264,  -144,   296,  -144,  -144,  -264,  -264,  -144,  -264,  -264,
    -264,  -264,  -264,   294,  -144,  -264,   383,  -264,  -264,  -264,
    -144,  -264,  -264,  -144,  -264,   255,   348,  -144,  -264,   141,
    -144,  -264,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -144,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,   300,  -144,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -144,  -264,
     394,  -264,  -264,  -264,   349,  -264,   301,  -144,  -264,  -264,
     313,  -144,  -264,  -264,  -264,  -264,   396,  -264,  -144,  -264,
    -264,  -264,   351,  -264,  -264,  -264,  -264,  -264,   352,  -264,
    -264,  -264,  -264,   330,  -144,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,   398,   242,  -264,  -144,   331,  -264,
    -264,   333,  -144,  -264,  -264,  -264,  -264,   117,    84,   339,
    -144,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -144,  -264,  -264,  -264,  -264,  -264,  -264,  -144,  -264,  -264,
    -144,   131,  -264,  -264,  -144,  -264,  -264,  -264,   400,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -144,  -264,  -264,  -264,  -144,  -264,
    -144,  -264,  -264,  -144,  -264,  -264,  -144,  -264,  -264,  -264,
    -144,  -264,  -264,  -264,  -144,  -264,  -144,  -264,  -144,  -264,
    -264,   361,  -264,  -264,  -264,  -144,  -264,  -264,  -264,  -264,
    -264,  -144,  -264,  -144,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -264,  -264,  -264,   280,    -1,  -264,   139,  -263,  -264
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     137,   138,   426,   217,   164,   201,   139,   132,   167,   144,
     145,   146,   291,   149,   150,   151,   152,   142,   155,   157,
     160,   161,   163,   165,   166,   143,   168,   169,   365,   173,
     174,   175,   176,   177,   180,   181,   183,   427,   186,   187,
     188,   190,   193,   194,   195,   197,   198,   199,   140,   141,
     206,   207,   158,   209,   212,   213,   216,   218,   219,   221,
     159,   224,   148,   226,   230,   232,   323,   234,   236,   239,
     240,   243,   246,   247,   250,   252,   253,   254,   255,   258,
     147,   178,   365,   184,   156,   268,   271,   366,   273,   179,
     277,   278,   279,   512,   281,   282,   285,   287,   290,   162,
     294,   296,   297,   298,   299,   300,   200,   305,   306,   308,
     309,   310,   311,   312,   315,   191,   317,   318,   319,   321,
     322,   324,   210,   192,   328,   331,   201,   344,   345,   346,
     211,   354,   313,   182,   428,   436,   203,   365,   314,   132,
     365,   350,   351,   204,   237,   132,   352,   353,   292,   227,
     468,   238,   355,   356,   513,   357,   228,   358,   359,   132,
     222,   360,   504,   361,   185,   214,   362,   241,   244,   363,
     364,   132,   248,   215,   256,   242,   245,   369,   370,   269,
     249,   371,   257,   372,   373,   275,   189,   270,   374,   202,
     375,   376,   208,   276,   132,   377,   132,   225,   450,   379,
     365,   521,   381,   382,   383,   233,   262,   385,   132,   388,
     389,   380,   132,   392,   393,   196,   394,   283,   132,   395,
     261,   288,   397,   132,   132,   284,   399,   400,   401,   289,
     403,   220,   404,   132,   405,   132,   406,   407,   223,   293,
     409,   410,   231,   411,   412,   303,   302,   415,   416,   235,
     417,   263,   329,   304,   251,   418,   419,   132,   420,   421,
     330,   423,   326,   266,   132,   429,   430,   132,   433,   434,
     286,   435,   132,   437,   441,   442,   367,   132,   132,   443,
     205,   386,   444,   445,   368,   446,   132,   447,   448,   387,
     449,   132,   132,   229,   451,   295,   365,   153,   132,   307,
     452,   320,   454,   455,   154,   365,   456,   132,   378,   132,
     132,   457,   458,   459,   132,   390,   132,   484,   490,   462,
     132,   132,   463,   391,   465,   464,   467,   132,   469,   470,
     493,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   413,   431,   384,   439,   500,   506,   132,
     508,   414,   432,   483,   440,   422,   515,   365,   365,   132,
     365,   365,   263,   132,   453,   132,   485,   486,   170,   402,
     365,   267,   132,   425,   259,   171,   132,   487,   408,   272,
     274,   260,   280,   132,   201,   491,   492,   132,   132,   494,
     495,   301,   201,   316,   132,   325,   327,   497,   460,   347,
     396,   398,   424,   488,   132,   496,   132,   503,   489,   523,
     498,   499,   501,   502,   349,     0,   466,     0,   132,     0,
     533,     0,     0,   132,     0,     0,   505,   507,     0,   132,
     509,   510,     0,   132,     0,   132,     0,   514,   516,   517,
       0,     0,   132,     0,     0,   132,     0,     0,     0,   518,
       0,   132,   132,     0,     0,   461,   519,   132,     0,   520,
       0,     0,     0,   522,   132,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   132,   132,   524,   132,   132,   132,   525,   132,   526,
     132,     0,   527,     0,     0,   528,     0,     0,     0,   529,
       0,     0,     0,   530,     0,   531,     0,   532,     0,     0,
       0,     0,     0,     0,   534,     0,     0,     0,     0,     0,
     535,     0,   536,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     7,     0,     0,
       0,     8,     9,     0,     0,     0,    10,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,   511,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,     0,    48,    49,
      50,    51,    52,    53,    54,    55,   348,    56,     0,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    99,   100,     0,   101,   102,   103,   104,
     105,   106,   107,   108,   109,     0,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,     0,   132,
       1,     2,     3,     4,     5,     6,     7,     0,     0,     0,
       8,     9,     0,     0,     0,    10,     0,     0,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,     0,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,     0,    48,    49,    50,
      51,    52,    53,    54,    55,     0,    56,     0,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,     0,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,    99,   100,     0,   101,   102,   103,   104,   105,
     106,   107,   108,   109,     0,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,     0,   132,   332,
     333,     0,     0,     0,     0,     0,     0,     0,     0,   334,
       0,     0,     0,     0,   335,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   336,     0,     0,     0,   337,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   338,     0,     0,
       0,     0,     0,   339,     0,     0,     0,     0,   340,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   341,     0,   342,   343
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-264))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       1,     2,   265,     9,    16,     9,     7,   151,    17,    10,
      11,    12,    16,    14,    15,    16,    17,     9,    19,    20,
      21,    22,    23,    24,    25,    17,    27,    28,     9,    30,
      31,    32,    33,    34,    35,    36,    37,    17,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,   152,   152,
      51,    52,     9,    54,    55,    56,    57,    58,    59,    60,
      17,    62,    17,    64,    65,    66,     9,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       9,     9,     9,     9,    17,    86,    87,    68,    89,    17,
      91,    92,    93,     9,    95,    96,    97,    98,    99,    17,
     101,   102,   103,   104,   105,   106,     9,   108,   109,   110,
     111,   112,   113,   114,   115,     9,   117,   118,   119,   120,
     121,   122,     9,    17,   125,   126,     9,   128,   129,   130,
      17,    70,    11,    17,   114,     9,     9,     9,    17,   151,
       9,   142,   143,    16,     9,   151,   147,   148,   152,     9,
       9,    16,   153,   154,    70,   156,    16,   158,   159,   151,
       9,   162,   425,   164,    17,     9,   167,     9,     9,   170,
     171,   151,     9,    17,     9,    17,    17,   178,   179,     9,
      17,   182,    17,   184,   185,     9,    17,    17,   189,    50,
     191,   192,    53,    17,   151,   196,   151,     9,    70,   200,
       9,    70,   203,   204,   205,     9,     9,   208,   151,   210,
     211,    20,   151,   214,   215,    17,   217,     9,   151,   220,
      81,     9,   223,   151,   151,    17,   227,   228,   229,    17,
     231,    17,   233,   151,   235,   151,   237,   238,    17,   100,
     241,   242,    17,   244,   245,     9,   107,   248,   249,    17,
     251,     9,     9,    17,    17,   256,   257,   151,   259,   260,
      17,   262,   123,     9,   151,   266,   267,   151,   269,   270,
      17,   272,   151,   274,   275,   276,     9,   151,   151,   280,
     153,     9,   283,   284,    17,   286,   151,   288,   289,    17,
     291,   151,   151,   153,   295,    17,     9,     9,   151,    17,
     301,    17,   303,   304,    16,     9,   307,   151,    17,   151,
     151,    17,   313,   314,   151,     9,   151,    17,    17,   320,
     151,   151,   323,    17,   325,    70,   327,   151,   329,   330,
      17,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,     9,     9,   206,     9,    17,    17,   151,
      17,    17,    17,   354,    17,    68,    17,     9,     9,   151,
       9,     9,     9,   151,    68,   151,   367,   368,     9,   230,
       9,     9,   151,    20,     9,    16,   151,   378,   239,     9,
       9,    16,     9,   151,     9,   386,   387,   151,   151,   390,
     391,    16,     9,     9,   151,     9,     9,   398,    15,     0,
      20,     9,   127,     9,   151,     9,   151,     9,    59,     9,
      59,    59,   413,   414,   134,    -1,    68,    -1,   151,    -1,
      59,    -1,    -1,   151,    -1,    -1,   427,   428,    -1,   151,
     431,   432,    -1,   151,    -1,   151,    -1,   438,   439,   440,
      -1,    -1,   151,    -1,    -1,   151,    -1,    -1,    -1,   450,
      -1,   151,   151,    -1,    -1,   316,   457,   151,    -1,   460,
      -1,    -1,    -1,   464,   151,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   151,   151,   484,   151,   151,   151,   488,   151,   490,
     151,    -1,   493,    -1,    -1,   496,    -1,    -1,    -1,   500,
      -1,    -1,    -1,   504,    -1,   506,    -1,   508,    -1,    -1,
      -1,    -1,    -1,    -1,   515,    -1,    -1,    -1,    -1,    -1,
     521,    -1,   523,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,   437,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    -1,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,    -1,   115,   116,    -1,   118,   119,   120,   121,
     122,   123,   124,   125,   126,    -1,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,    -1,   151,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      13,    14,    -1,    -1,    -1,    18,    -1,    -1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    69,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,    -1,   115,   116,    -1,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,    -1,   151,    25,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,    -1,   120,   121
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    13,    14,
      18,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    60,    61,
      62,    63,    64,    65,    66,    67,    69,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   115,
     116,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   151,   155,   156,   157,   158,   158,   158,   158,
     152,   152,     9,    17,   158,   158,   158,     9,    17,   158,
     158,   158,   158,     9,    16,   158,    17,   158,     9,    17,
     158,   158,    17,   158,    16,   158,   158,    17,   158,   158,
       9,    16,   160,   158,   158,   158,   158,   158,     9,    17,
     158,   158,    17,   158,     9,    17,   158,   158,   158,    17,
     158,     9,    17,   158,   158,   158,    17,   158,   158,   158,
       9,     9,   160,     9,    16,   153,   158,   158,   160,   158,
       9,    17,   158,   158,     9,    17,   158,     9,   158,   158,
      17,   158,     9,    17,   158,     9,   158,     9,    16,   153,
     158,    17,   158,     9,   158,    17,   158,     9,    16,   158,
     158,     9,    17,   158,     9,    17,   158,   158,     9,    17,
     158,    17,   158,   158,   158,   158,     9,    17,   158,     9,
      16,   160,     9,     9,   161,   162,     9,     9,   158,     9,
      17,   158,     9,   158,     9,     9,    17,   158,   158,   158,
       9,   158,   158,     9,    17,   158,    17,   158,     9,    17,
     158,    16,   152,   160,   158,    17,   158,   158,   158,   158,
     158,    16,   160,     9,    17,   158,   158,    17,   158,   158,
     158,   158,   158,    11,    17,   158,     9,   158,   158,   158,
      17,   158,   158,     9,   158,     9,   160,     9,   158,     9,
      17,   158,    25,    26,    35,    40,    51,    55,    83,    89,
      94,   118,   120,   121,   158,   158,   158,     0,    68,   157,
     158,   158,   158,   158,    70,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,     9,    68,     9,    17,   158,
     158,   158,   158,   158,   158,   158,   158,   158,    17,   158,
      20,   158,   158,   158,   160,   158,     9,    17,   158,   158,
       9,    17,   158,   158,   158,   158,    20,   158,     9,   158,
     158,   158,   160,   158,   158,   158,   158,   158,   160,   158,
     158,   158,   158,     9,    17,   158,   158,   158,   158,   158,
     158,   158,    68,   158,   127,    20,   161,    17,   114,   158,
     158,     9,    17,   158,   158,   158,     9,   158,   159,     9,
      17,   158,   158,   158,   158,   158,   158,   158,   158,   158,
      70,   158,   158,    68,   158,   158,   158,    17,   158,   158,
      15,   160,   158,   158,    70,   158,    68,   158,     9,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,    17,   158,   158,   158,     9,    59,
      17,   158,   158,    17,   158,   158,     9,   158,    59,    59,
      17,   158,   158,     9,   161,   158,    17,   158,    17,   158,
     158,   160,     9,    70,   158,    17,   158,   158,   158,   158,
     158,    70,   158,     9,   158,   158,   158,   158,   158,   158,
     158,   158,   158,    59,   158,   158,   158
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:

/* Line 1806 of yacc.c  */
#line 107 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->add_props(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 112 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->add_props((yyvsp[(2) - (3)].text));
            free((yyvsp[(2) - (3)].text));
       }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 116 "xfst-parser.yy"
    {
            hxfsterror("NETWORK PROPERTY EDITOR unimplemented\n");
            return EXIT_FAILURE;
       }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 121 "xfst-parser.yy"
    {
       	    hfst::xfst::xfst_->apply_up(stdin);
       }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 124 "xfst-parser.yy"
    {
       	    hfst::xfst::xfst_->apply_up((yyvsp[(2) - (3)].text));
       }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 127 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->apply_up((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 131 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "r");
            hfst::xfst::xfst_->apply_up(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 136 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->apply_up((yyvsp[(3) - (4)].text));
            free((yyvsp[(3) - (4)].text));
       }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 140 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->apply_down(stdin);
       }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 143 "xfst-parser.yy"
    {
       	    hfst::xfst::xfst_->apply_down((yyvsp[(2) - (3)].text));
       }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 146 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->apply_down((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 150 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "r");
            hfst::xfst::xfst_->apply_down(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 155 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->apply_down((yyvsp[(3) - (4)].text));
            free((yyvsp[(3) - (4)].text));
       }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 159 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->apply_med((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 163 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "r");
            hfst::xfst::xfst_->apply_med(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 168 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->apply_med((yyvsp[(3) - (4)].text));
            free((yyvsp[(3) - (4)].text));
       }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 172 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->lookup_optimize();
       }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 175 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->remove_optimization();
       }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 179 "xfst-parser.yy"
    {
            hxfsterror("unimplemetend ambiguous\n");
            return EXIT_FAILURE;
       }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 183 "xfst-parser.yy"
    {
            hxfsterror("unimplemetend ambiguous\n");
            return EXIT_FAILURE;
       }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 187 "xfst-parser.yy"
    {
            hxfsterror("unimplemetend ambiguous\n");
            return EXIT_FAILURE;
       }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 192 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->define_alias((yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].text));
            free((yyvsp[(2) - (4)].name));
            free((yyvsp[(3) - (4)].text));
       }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 197 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->define_alias((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].text));
            free((yyvsp[(2) - (5)].name));
            free((yyvsp[(4) - (5)].text));
       }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 202 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->define_list((yyvsp[(2) - (5)].name), (yyvsp[(3) - (5)].text));
            free((yyvsp[(2) - (5)].name));
            free((yyvsp[(3) - (5)].text));
       }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 207 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->define_list((yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].list)[0], (yyvsp[(3) - (4)].list)[1]);
            free((yyvsp[(2) - (4)].name));
            free((yyvsp[(3) - (4)].list)[0]);
            free((yyvsp[(3) - (4)].list)[1]);
            free((yyvsp[(3) - (4)].list));
       }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 214 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->define((yyvsp[(1) - (1)].name));
            free((yyvsp[(1) - (1)].name));
       }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 218 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->define((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].text));
            free((yyvsp[(1) - (2)].name));
            free((yyvsp[(2) - (2)].text));
       }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 223 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->define_function((yyvsp[(1) - (2)].name), (yyvsp[(2) - (2)].text));
            free((yyvsp[(1) - (2)].name));
            free((yyvsp[(2) - (2)].text));
       }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 228 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->undefine((yyvsp[(2) - (3)].text));
            free((yyvsp[(2) - (3)].text));
       }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 232 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->unlist((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 236 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->name_net((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 240 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->load_definitions((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 245 "xfst-parser.yy"
    { 
            hfst::xfst::xfst_->apropos((yyvsp[(1) - (2)].text));
            free((yyvsp[(1) - (2)].text));
       }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 249 "xfst-parser.yy"
    { 
            hfst::xfst::xfst_->describe((yyvsp[(1) - (2)].text));
       }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 253 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->clear();
       }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 256 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->pop();
       }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 259 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->push((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 263 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->push();
       }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 266 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->turn();
       }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 269 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->rotate();
       }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 272 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->load_stack((yyvsp[(2) - (3)].file));
            free((yyvsp[(2) - (3)].file));
       }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 276 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->load_stack((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 280 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->load_stack((yyvsp[(2) - (4)].name));
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 285 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->collect_epsilon_loops();
       }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 288 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->compact_sigma();
       }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 292 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->eliminate_flag((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 296 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->eliminate_flags();
       }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 300 "xfst-parser.yy"
    { 
            hfst::xfst::xfst_->echo((yyvsp[(1) - (1)].text));
            free((yyvsp[(1) - (1)].text));
       }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 304 "xfst-parser.yy"
    { 
            hfst::xfst::xfst_->quit((yyvsp[(1) - (1)].text));
            free((yyvsp[(1) - (1)].text));
            return EXIT_SUCCESS;
       }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 309 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->hfst((yyvsp[(1) - (1)].text));
            free((yyvsp[(1) - (1)].text));
       }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 313 "xfst-parser.yy"
    {
            hxfsterror("source not implemented yywrap\n");
            return EXIT_FAILURE;
       }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 317 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->system((yyvsp[(1) - (1)].text));
            free((yyvsp[(1) - (1)].text));
       }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 321 "xfst-parser.yy"
    {
            hxfsterror("view not implemented\n");
            return EXIT_FAILURE;
       }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 326 "xfst-parser.yy"
    {
            int i = hfst::xfst::nametoken_to_number((yyvsp[(3) - (4)].name));
            if (i != -1)
              hfst::xfst::xfst_->set((yyvsp[(2) - (4)].name), i);
            else
              hfst::xfst::xfst_->set((yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].name));
            free((yyvsp[(2) - (4)].name));
            free((yyvsp[(3) - (4)].name));
       }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 335 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->show((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 339 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->show();
       }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 342 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->twosided_flags();
       }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 346 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_eq();
       }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 349 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_funct();
       }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 352 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_id();
       }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 355 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_infinitely_ambiguous();
       }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 358 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_lower_bounded();
       }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 361 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_lower_uni();
       }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 364 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_upper_bounded();
       }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 367 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_upper_uni();
       }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 370 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_nonnull();
       }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 373 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_null();
       }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 376 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_overlap();
       }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 379 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_sublanguage();
       }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 382 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_unambiguous();
       }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 386 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_eq(true);
       }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 389 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_funct(true);
       }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 392 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_id(true);
       }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 395 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_lower_bounded(true);
       }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 398 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_lower_uni(true);
       }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 401 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_upper_bounded(true);
       }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 404 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_upper_uni(true);
       }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 407 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_nonnull(true);
       }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 410 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_null(true);
       }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 413 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_overlap(true);
       }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 416 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_sublanguage(true);
       }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 419 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->test_unambiguous(true);
       }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 423 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->substitute_named((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].name)); // TODO!
            free((yyvsp[(2) - (5)].name));
            free((yyvsp[(4) - (5)].name));
       }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 428 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->substitute_label((yyvsp[(2) - (5)].text), (yyvsp[(4) - (5)].text));
            free((yyvsp[(2) - (5)].text));
            free((yyvsp[(4) - (5)].text));
       }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 433 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->substitute_symbol((yyvsp[(2) - (5)].text), (yyvsp[(4) - (5)].name));
            free((yyvsp[(2) - (5)].text));
            free((yyvsp[(4) - (5)].name));
       }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 439 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "r");
            hfst::xfst::xfst_->print_aliases(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 444 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_aliases(stdout);
       }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 447 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_arc_count(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 452 "xfst-parser.yy"
    {
            if (strcmp((yyvsp[(2) - (3)].name), "upper") && strcmp((yyvsp[(2) - (3)].name), "lower"))
            {
                hxfsterror("should be upper or lower");
                return EXIT_FAILURE;
            }
            hfst::xfst::xfst_->print_arc_count((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 461 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_arc_count(stdout);
       }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 464 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_defined(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 469 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_defined(stdout);
       }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 472 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            hfst::xfst::xfst_->print_dir((yyvsp[(2) - (4)].name), f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
            free((yyvsp[(3) - (4)].file));
       }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 478 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_dir((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 482 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_dir("*", f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 487 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_dir("*", stdout);
       }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 490 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_file_info(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 495 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_file_info(stdout);
       }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 498 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_flags(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 503 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_flags(stdout);
       }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 506 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_labels((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 510 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_labels(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 515 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_labels(stdout);
       }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 518 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_label_count(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 523 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_label_count(stdout);
       }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 526 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            hfst::xfst::xfst_->print_list((yyvsp[(2) - (4)].name), f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 532 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_list((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 536 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_list(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 541 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_list(stdout);
       }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 544 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_longest_string(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 549 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_longest_string(stdout);
       }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 552 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_longest_string_size(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 557 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_longest_string_size(stdout);
       }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 560 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_name(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 565 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_name(stdout);
       }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 568 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_shortest_string(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 573 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_shortest_string(stdout);
       }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 576 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_shortest_string_size(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 581 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_shortest_string_size(stdout);
       }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 584 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_lower_words((yyvsp[(2) - (4)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (4)].name)), stdout);
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 588 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(4) - (5)].file), "w");
            hfst::xfst::xfst_->print_lower_words((yyvsp[(2) - (5)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (5)].name)), f);
            free((yyvsp[(2) - (5)].name));
            hfst::xfst::xfst_fclose(f, (yyvsp[(4) - (5)].file));
       }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 594 "xfst-parser.yy"
    {
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (3)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_lower_words(NULL, i, stdout);
            else
              hfst::xfst::xfst_->print_lower_words((yyvsp[(2) - (3)].name), 0, stdout);
       }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 601 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_lower_words(NULL, 0, stdout);
       }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 604 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (4)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_lower_words(NULL, i, f);
            else
              hfst::xfst::xfst_->print_lower_words((yyvsp[(2) - (4)].name), 0, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
       }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 613 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_lower_words(NULL, 0, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 618 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_random_lower((yyvsp[(2) - (4)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (4)].name)), stdout);
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 622 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(4) - (5)].file), "w");
            hfst::xfst::xfst_->print_random_lower((yyvsp[(2) - (5)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (5)].name)), f);
            free((yyvsp[(2) - (5)].name));
            hfst::xfst::xfst_fclose(f, (yyvsp[(4) - (5)].file));
       }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 628 "xfst-parser.yy"
    {
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (3)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_random_lower(NULL, i, stdout);
            else
              hfst::xfst::xfst_->print_random_lower((yyvsp[(2) - (3)].name), 15, stdout);
       }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 635 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_random_lower(NULL, 15, stdout);
       }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 638 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (4)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_random_lower(NULL, i, f);
            else
              hfst::xfst::xfst_->print_random_lower((yyvsp[(2) - (4)].name), 15, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
       }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 647 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_random_lower(NULL, 15, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 652 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_upper_words((yyvsp[(2) - (4)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (4)].name)), stdout);
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 656 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(4) - (5)].file), "w");
            hfst::xfst::xfst_->print_upper_words((yyvsp[(2) - (5)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (5)].name)), f);
            free((yyvsp[(2) - (5)].name));
            hfst::xfst::xfst_fclose(f, (yyvsp[(4) - (5)].file));
       }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 662 "xfst-parser.yy"
    {
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (3)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_upper_words(NULL, i, stdout);
            else
              hfst::xfst::xfst_->print_upper_words((yyvsp[(2) - (3)].name), 0, stdout);
       }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 669 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_upper_words(NULL, 0, stdout);
       }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 672 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (4)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_upper_words(NULL, i, f);
            else
              hfst::xfst::xfst_->print_upper_words((yyvsp[(2) - (4)].name), 0, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
       }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 681 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_upper_words(NULL, 0, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 686 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_random_upper((yyvsp[(2) - (4)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (4)].name)), stdout);
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 690 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(4) - (5)].file), "w");
            hfst::xfst::xfst_->print_random_upper((yyvsp[(2) - (5)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (5)].name)), f);
            free((yyvsp[(2) - (5)].name));
            hfst::xfst::xfst_fclose(f, (yyvsp[(4) - (5)].file));
       }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 696 "xfst-parser.yy"
    {
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (3)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_random_upper(NULL, i, stdout);
            else
              hfst::xfst::xfst_->print_random_upper((yyvsp[(2) - (3)].name), 15, stdout);
       }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 703 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_random_upper(NULL, 15, stdout);
       }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 706 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (4)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_random_upper(NULL, i, f);
            else
              hfst::xfst::xfst_->print_random_upper((yyvsp[(2) - (4)].name), 15, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
       }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 715 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_random_upper(NULL, 15, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 720 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_words((yyvsp[(2) - (4)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (4)].name)), stdout);
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 724 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(4) - (5)].file), "w");
            hfst::xfst::xfst_->print_words((yyvsp[(2) - (5)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (5)].name)), f);
            free((yyvsp[(2) - (5)].name));
            hfst::xfst::xfst_fclose(f, (yyvsp[(4) - (5)].file));
       }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 730 "xfst-parser.yy"
    {
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (3)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_words(NULL, i, stdout);
            else
              hfst::xfst::xfst_->print_words((yyvsp[(2) - (3)].name), 0, stdout);
       }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 737 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_words(NULL, 0, stdout);
       }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 740 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (4)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_words(NULL, i, f);
            else
              hfst::xfst::xfst_->print_words((yyvsp[(2) - (4)].name), 0, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
       }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 749 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_words(NULL, 0, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 754 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_random_words((yyvsp[(2) - (4)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (4)].name)), stdout);
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 758 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(4) - (5)].file), "w");
            hfst::xfst::xfst_->print_random_words((yyvsp[(2) - (5)].name), hfst::xfst::nametoken_to_number((yyvsp[(3) - (5)].name)), f);
            free((yyvsp[(2) - (5)].name));
            hfst::xfst::xfst_fclose(f, (yyvsp[(4) - (5)].file));
       }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 764 "xfst-parser.yy"
    {
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (3)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_random_words(NULL, i, stdout);
            else
              hfst::xfst::xfst_->print_random_words((yyvsp[(2) - (3)].name), 15, stdout);
       }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 771 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_random_words(NULL, 15, stdout);
       }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 774 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(3) - (4)].file), "w");
            int i = hfst::xfst::nametoken_to_number((yyvsp[(2) - (4)].name));
            if (i != -1)
              hfst::xfst::xfst_->print_random_words(NULL, i, f);
            else
              hfst::xfst::xfst_->print_random_words((yyvsp[(2) - (4)].name), 15, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(3) - (4)].file));
       }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 783 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_random_words(NULL, 15, f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 788 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_net((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 792 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_net(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 797 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_net(stdout);
       }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 800 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_properties((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 804 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_properties(stdout);
       }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 807 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_properties(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 812 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_sigma((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 816 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_sigma(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 821 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_sigma(stdout);
       }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 824 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_sigma_count(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 829 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_sigma_count(stdout);
       }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 832 "xfst-parser.yy"
    {
            if (strcmp((yyvsp[(2) - (3)].name), "upper") && strcmp((yyvsp[(2) - (3)].name), "lower"))
            {
                hxfsterror("must be upper or lower\n");
                return EXIT_FAILURE;
            }
            hfst::xfst::xfst_->print_sigma_word_count((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 841 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_sigma_word_count(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 846 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_sigma_word_count(stdout);
       }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 849 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_size((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 853 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_size(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 858 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_size(stdout);
       }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 861 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_stack(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 866 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->print_stack(stdout);
       }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 869 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->print_labelmaps(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 875 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_dot((yyvsp[(2) - (3)].name), stdout);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 879 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->write_dot(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 884 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_dot(stdout);
       }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 887 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_function((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].file));
            free((yyvsp[(2) - (5)].name));
       }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 891 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_function((yyvsp[(2) - (4)].name), 0);
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 895 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_definition((yyvsp[(2) - (4)].name), (yyvsp[(3) - (4)].file));
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 899 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_definition((yyvsp[(2) - (3)].name), 0);
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 903 "xfst-parser.yy"
    {    
            hfst::xfst::xfst_->write_definitions((yyvsp[(2) - (3)].file));
       }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 906 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_definitions(0);
       }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 909 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_stack((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 913 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->write_prolog(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 918 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].name), "w");
            hfst::xfst::xfst_->write_prolog(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].name));
       }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 923 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_prolog(stdout);
       }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 926 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->write_spaced(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 931 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_spaced(stdout);
       }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 934 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->write_text(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 939 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_text(stdout);
       }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 943 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "r");
            hfst::xfst::xfst_->read_props(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 948 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_props(stdin);
       }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 951 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].name), "r");
            hfst::xfst::xfst_->read_prolog(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].name));
       }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 956 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_prolog(stdin);
       }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 959 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_regex((yyvsp[(2) - (2)].text));
            free((yyvsp[(2) - (2)].text));
       }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 963 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "r");
            hfst::xfst::xfst_->read_regex(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
       }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 968 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_regex((yyvsp[(2) - (4)].text));
            free((yyvsp[(2) - (4)].text));
       }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 972 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_spaced_from_file((yyvsp[(2) - (3)].file));
            free((yyvsp[(2) - (3)].file));
       }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 976 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_spaced_from_file((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 980 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_spaced((yyvsp[(2) - (3)].text));
            free((yyvsp[(2) - (3)].text));
       }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 984 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_text_from_file((yyvsp[(2) - (3)].file));
            free((yyvsp[(2) - (3)].file));
       }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 988 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_text_from_file((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 992 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_text((yyvsp[(2) - (3)].text));
            free((yyvsp[(2) - (3)].text));
       }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 996 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_lexc_from_file((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1000 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_lexc_from_file((yyvsp[(2) - (4)].name));
            free((yyvsp[(2) - (4)].name));
       }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1004 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_lexc_from_file("");
       }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1007 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->read_att_from_file((yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1011 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->write_att(stdout);       
       }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1014 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].file), "w");
            hfst::xfst::xfst_->write_att(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].file));
            free((yyvsp[(2) - (3)].file));
       }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1020 "xfst-parser.yy"
    {
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (3)].name), "w");
            hfst::xfst::xfst_->write_att(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (3)].name));
            free((yyvsp[(2) - (3)].name));
       }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1026 "xfst-parser.yy"
    {
            // todo: handle input and output symbol tables
            FILE * f = hfst::xfst::xfst_fopen((yyvsp[(2) - (5)].name), "w");
            hfst::xfst::xfst_->write_att(f);
            hfst::xfst::xfst_fclose(f, (yyvsp[(2) - (5)].name));
            free((yyvsp[(2) - (5)].name));
       }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1034 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->cleanup_net();
       }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1037 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->complete_net();
       }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1040 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->compose_net();
       }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1043 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->concatenate_net();
       }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 1046 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->minus_net();
       }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 1049 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->crossproduct_net();
       }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1052 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->minimize_net();
       }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 1055 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->determinize_net();
       }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 1058 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->epsilon_remove_net();
       }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 1061 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->prune_net();
       }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1064 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->ignore_net();
       }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1067 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->intersect_net();
       }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1070 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->inspect_net();
       }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1073 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->invert_net();
       }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1076 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->lower_side_net();
       }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1079 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->upper_side_net();
       }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1082 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->negate_net();
       }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1085 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->one_plus_net();
       }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1088 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->zero_plus_net();
       }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1091 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->optional_net();
       }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 1094 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->reverse_net();
       }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1097 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->shuffle_net();
       }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1100 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->sigma_net();
       }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 1103 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->sort_net();
       }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1106 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->substring_net();
       }
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 1109 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->union_net();
       }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 1112 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->label_net();
       }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1115 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->compile_replace_lower_net();
       }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 1118 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->compile_replace_upper_net();
       }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 1121 "xfst-parser.yy"
    {
            hfst::xfst::xfst_->prompt();
       }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 1124 "xfst-parser.yy"
    {
            fprintf(stderr, "Command %s is not recognised.\n", (yyvsp[(1) - (2)].name));
            hfst::xfst::xfst_->prompt();
       }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1132 "xfst-parser.yy"
    {
                    (yyval.text) = static_cast<char*>(malloc(sizeof(char)*strlen((yyvsp[(1) - (2)].text))+strlen((yyvsp[(2) - (2)].name))+2));
                    char* r = (yyval.text);
                    char* s = (yyvsp[(1) - (2)].text);
                    while (*s != '\0')
                    {
                        *r = *s;
                        r++;
                        s++;
                    }
                    *r = ' ';
                    r++;
                    s = (yyvsp[(2) - (2)].name);
                    while (*s != '\0')
                    {
                        *r = *s;
                        r++;
                        s++;
                    }
                    *r = '\0';
                }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 1153 "xfst-parser.yy"
    {
                    (yyval.text) = (yyvsp[(1) - (2)].text);
                }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 1156 "xfst-parser.yy"
    {
                    (yyval.text) = (yyvsp[(1) - (1)].name);
                }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1161 "xfst-parser.yy"
    {
                (yyval.text) = static_cast<char*>(malloc(sizeof(char)*strlen((yyvsp[(1) - (2)].text))+strlen((yyvsp[(2) - (2)].name))+2));
                char* s = (yyvsp[(1) - (2)].text);
                char* r = (yyval.text);
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = ' ';
                r++;
                s = (yyvsp[(2) - (2)].name);
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = '\0';
             }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1182 "xfst-parser.yy"
    {
                (yyval.text) = (yyvsp[(1) - (1)].name);
             }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1187 "xfst-parser.yy"
    {
                (yyval.text) = strdup((std::string((yyvsp[(1) - (3)].name)) + std::string(":") + std::string((yyvsp[(3) - (3)].name))).c_str());
                }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1190 "xfst-parser.yy"
    {
                (yyval.text) = (yyvsp[(1) - (1)].name);
                }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 1195 "xfst-parser.yy"
    {
                (yyval.text) = static_cast<char*>(malloc(sizeof(char)*strlen((yyvsp[(1) - (2)].text))+strlen((yyvsp[(2) - (2)].text))+2));
                char* s = (yyvsp[(1) - (2)].text);
                char* r = (yyval.text);
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = ' ';
                r++;
                s = (yyvsp[(2) - (2)].text);
                while (*s != '\0')
                {
                    *r = *s;
                    r++;
                    s++;
                }
                *r = '\0';
             }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1216 "xfst-parser.yy"
    {
                (yyval.text) = (yyvsp[(1) - (1)].text);
             }
    break;



/* Line 1806 of yacc.c  */
#line 4966 "xfst-parser.cc"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 1220 "xfst-parser.yy"


// oblig. declarations
extern FILE* hxfstin;
int hxfstparse(void);

// gah, bison/flex error mechanism here
void
hxfsterror(const char* text)
{ 
    fprintf(stderr,  "%s\n", text);
}


// vim: set ft=yacc:

