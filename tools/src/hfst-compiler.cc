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
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "hfst-compiler.yy"

/*******************************************************************/
/*                                                                 */
/*  FILE     hfst-compiler.yy                                       */
/*  MODULE   hfst-compiler                                          */
/*  PROGRAM  HFST                                                  */     
/*                                                                 */
/*******************************************************************/

#ifdef WINDOWS
#include <io.h>
#endif

#include <stdio.h>
#include "HfstCompiler.h"
#include "HfstTransducer.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <errno.h>

#include "hfst-commandline.h"
#include "hfst-program-options.h"

#include "inc/globals-common.h"
#include "inc/globals-unary.h"

extern char* FileName;
extern bool Verbose;

char * folder = NULL;

using std::cerr;
using namespace hfst;

extern int  yylineno;
extern char *yytext;

void yyerror(char *text);
void warn(char *text);
void warn2(const char *text, char *text2);
int yylex( void );
int yyparse( void );

static int Switch=0;
HfstCompiler * compiler;
HfstTransducer * Result;

static hfst::ImplementationType output_format = hfst::ERROR_TYPE; // = hfst::UNSPECIFIED_TYPE;
bool DEBUG=false;




/* Line 268 of yacc.c  */
#line 128 "hfst-compiler.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
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
     NEWLINE = 258,
     ALPHA = 259,
     COMPOSE = 260,
     PRINT = 261,
     POS = 262,
     INSERT = 263,
     SUBSTITUTE = 264,
     SWITCH = 265,
     ARROW = 266,
     REPLACE = 267,
     SYMBOL = 268,
     VAR = 269,
     SVAR = 270,
     RVAR = 271,
     RSVAR = 272,
     STRING = 273,
     STRING2 = 274,
     UTF8CHAR = 275,
     CHARACTER = 276,
     SEQ = 277
   };
#endif
/* Tokens.  */
#define NEWLINE 258
#define ALPHA 259
#define COMPOSE 260
#define PRINT 261
#define POS 262
#define INSERT 263
#define SUBSTITUTE 264
#define SWITCH 265
#define ARROW 266
#define REPLACE 267
#define SYMBOL 268
#define VAR 269
#define SVAR 270
#define RVAR 271
#define RSVAR 272
#define STRING 273
#define STRING2 274
#define UTF8CHAR 275
#define CHARACTER 276
#define SEQ 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 58 "hfst-compiler.yy"

  int        number;
  hfst::Twol_Type  type;
  hfst::Repl_Type  rtype;
  char       *name;
  char       *value;
  unsigned char uchar;
  unsigned int  longchar;
  hfst::Character  character;
  hfst::HfstTransducer   *expression;
  hfst::Range      *range;
  hfst::Ranges     *ranges;
  hfst::Contexts   *contexts;



/* Line 293 of yacc.c  */
#line 225 "hfst-compiler.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 237 "hfst-compiler.cc"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   998

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNRULES -- Number of states.  */
#define YYNSTATES  166

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,     2,     2,     2,     2,    24,     2,
      33,    34,    29,    30,    41,    23,    40,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    37,     2,
       2,    31,     2,    32,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,    27,    28,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,    22,    36,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    13,    14,    18,    22,    26,
      30,    34,    37,    41,    46,    51,    55,    60,    65,    71,
      77,    82,    87,    91,    95,   103,   109,   115,   121,   125,
     131,   141,   150,   154,   156,   158,   160,   163,   166,   169,
     172,   175,   178,   181,   184,   188,   192,   196,   200,   202,
     204,   207,   208,   212,   217,   221,   223,   225,   227,   231,
     235,   237,   239,   243,   247,   250,   253,   256,   258,   262,
     264,   266,   268,   270,   272,   274,   276,   278,   280,   282,
     284,   286,   288,   290,   292,   294,   296,   298,   300,   302,
     304,   306,   308,   310,   312,   314,   316,   319
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      43,     0,    -1,    44,    46,    58,    -1,    44,    45,    -1,
      44,     3,    -1,    -1,    14,    31,    46,    -1,    16,    31,
      46,    -1,    15,    31,    53,    -1,    17,    31,    53,    -1,
      46,     6,    18,    -1,     4,    46,    -1,    46,    11,    49,
      -1,    46,    27,    11,    49,    -1,    46,    28,    11,    49,
      -1,    46,    12,    51,    -1,    46,    12,    32,    51,    -1,
      46,    12,    33,    34,    -1,    46,    12,    32,    33,    34,
      -1,    46,    48,    11,    48,    46,    -1,    46,    48,    11,
      48,    -1,    48,    11,    48,    46,    -1,    48,    11,    48,
      -1,    46,     5,    46,    -1,    35,    47,    36,    37,    35,
      47,    36,    -1,    48,    37,    35,    47,    36,    -1,    35,
      47,    36,    37,    48,    -1,    46,     8,    56,    37,    56,
      -1,    46,     8,    56,    -1,    46,     9,    56,    37,    56,
      -1,    46,     9,    56,    37,    56,    37,    56,    37,    56,
      -1,    46,     9,    56,    37,    56,    33,    46,    34,    -1,
      48,    37,    48,    -1,    48,    -1,    14,    -1,    16,    -1,
      46,    29,    -1,    46,    30,    -1,    46,    32,    -1,    46,
      46,    -1,    26,    46,    -1,    10,    46,    -1,    27,    46,
      -1,    28,    46,    -1,    46,    24,    46,    -1,    46,    23,
      46,    -1,    46,    22,    46,    -1,    33,    46,    34,    -1,
      18,    -1,    19,    -1,    48,    47,    -1,    -1,    38,    53,
      39,    -1,    38,    27,    53,    39,    -1,    38,    17,    39,
      -1,    40,    -1,    56,    -1,    50,    -1,    33,    50,    34,
      -1,    52,    41,    50,    -1,    52,    -1,    52,    -1,    33,
      52,    34,    -1,    46,     7,    46,    -1,     7,    46,    -1,
      46,     7,    -1,    54,    53,    -1,    54,    -1,    55,    23,
      55,    -1,    15,    -1,    55,    -1,    56,    -1,    57,    -1,
      21,    -1,    20,    -1,    57,    -1,    21,    -1,    20,    -1,
      13,    -1,    40,    -1,    26,    -1,    32,    -1,    35,    -1,
      36,    -1,    34,    -1,    33,    -1,    24,    -1,    22,    -1,
      29,    -1,    30,    -1,    37,    -1,    41,    -1,    31,    -1,
      28,    -1,    27,    -1,    23,    -1,     3,    58,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    99,    99,   102,   103,   104,   107,   108,   109,   110,
     111,   112,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     155,   156,   159,   160,   161,   162,   163,   166,   167,   170,
     171,   174,   175,   178,   179,   180,   183,   184,   187,   188,
     189,   190,   191,   194,   195,   196,   199,   200,   201,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   223,   224
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NEWLINE", "ALPHA", "COMPOSE", "PRINT",
  "POS", "INSERT", "SUBSTITUTE", "SWITCH", "ARROW", "REPLACE", "SYMBOL",
  "VAR", "SVAR", "RVAR", "RSVAR", "STRING", "STRING2", "UTF8CHAR",
  "CHARACTER", "'|'", "'-'", "'&'", "SEQ", "'!'", "'^'", "'_'", "'*'",
  "'+'", "'='", "'?'", "'('", "')'", "'{'", "'}'", "':'", "'['", "']'",
  "'.'", "','", "$accept", "ALL", "ASSIGNMENTS", "ASSIGNMENT", "RE",
  "RANGES", "RANGE", "CONTEXTS2", "CONTEXTS", "CONTEXT2", "CONTEXT",
  "VALUES", "VALUE", "LCHAR", "CODE", "SCHAR", "NEWLINES", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   124,    45,    38,   277,    33,    94,    95,    42,
      43,    61,    63,    40,    41,   123,   125,    58,    91,    93,
      46,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    44,    45,    45,    45,    45,
      45,    45,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    48,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    53,    53,    54,    54,
      54,    54,    54,    55,    55,    55,    56,    56,    56,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    58,    58
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     0,     3,     3,     3,     3,
       3,     2,     3,     4,     4,     3,     4,     4,     5,     5,
       4,     4,     3,     3,     7,     5,     5,     5,     3,     5,
       9,     8,     3,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     3,     3,     1,     1,
       2,     0,     3,     4,     3,     1,     1,     1,     3,     3,
       1,     1,     3,     3,     2,     2,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     1,     4,     0,     0,    78,    34,     0,
      35,     0,    48,    49,    77,    76,     0,     0,     0,     0,
      51,     0,    55,     3,    97,    33,    56,    34,    35,    11,
      41,     0,     0,     0,     0,    40,    42,    43,     0,     0,
      51,    69,     0,    74,    73,    87,    95,    86,    80,    94,
      93,    88,    89,    92,    81,    85,    84,    82,    83,    90,
      79,    91,     0,    67,    70,    71,    72,    97,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      37,    38,    39,    33,     2,     0,     0,     6,    94,     8,
       7,     9,    47,     0,    50,    54,     0,    52,    66,     0,
      96,    23,    10,    28,     0,     0,     0,     0,    12,    57,
      60,     0,     0,    15,    61,    46,    45,    44,     0,     0,
       0,    22,    51,    32,     0,    53,    74,    73,    68,    75,
       0,     0,    64,     0,     0,    65,     0,     0,    16,    17,
       0,    13,    14,    20,    21,     0,    51,    26,    27,    29,
      58,    63,    59,    18,    62,    19,    25,     0,     0,     0,
      24,     0,     0,    31,     0,    30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    23,    82,    39,    25,   108,   109,   113,
     110,    62,    63,    64,    26,    66,    84
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -105
static const yytype_int16 yypact[] =
{
    -105,     9,   244,  -105,  -105,   824,   824,  -105,   -19,   -12,
      10,    11,  -105,  -105,  -105,  -105,   824,   824,   824,   824,
      85,   877,  -105,  -105,   211,    -4,  -105,  -105,  -105,   414,
     414,   824,   906,   824,   906,   853,   853,   853,   312,    12,
      85,  -105,     6,  -105,  -105,  -105,  -105,  -105,  -105,   935,
    -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,     7,   906,    24,  -105,  -105,    46,   824,    32,
       5,     5,   559,   472,   824,   824,   824,   764,   795,  -105,
    -105,  -105,   733,    -1,  -105,    85,     0,   414,  -105,  -105,
     414,  -105,  -105,    14,  -105,  -105,    13,  -105,  -105,   957,
    -105,   646,  -105,    17,    18,   824,   588,   346,  -105,  -105,
      15,   617,   501,  -105,  -105,   675,   704,   733,   559,   559,
      85,   824,    85,  -105,    44,  -105,  -105,  -105,  -105,  -105,
       5,     5,   414,   278,    25,   824,   588,   530,  -105,  -105,
      28,  -105,  -105,   824,   443,    22,    85,  -105,  -105,    -3,
    -105,   414,  -105,  -105,  -105,   443,  -105,    27,   824,     5,
    -105,   380,    30,  -105,     5,  -105
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -105,  -105,  -105,  -105,    -2,   -39,    57,   -91,  -104,   -43,
     -68,   -26,  -105,   -21,   -10,   -14,    21
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      24,    94,   134,    29,    30,   114,    89,    85,    91,     3,
     120,    65,    31,     7,    35,    36,    37,    38,     7,    32,
      14,    15,    65,    96,    65,    14,    15,   141,   142,    87,
     158,    90,   152,    86,   159,   122,    86,    98,    21,    65,
      22,    33,    34,   114,   140,    95,    97,    99,    93,    67,
     102,   124,   125,    65,   130,   131,   136,     7,   156,   150,
     103,   104,   154,   160,    14,    15,   101,   164,   138,   140,
     107,   107,   115,   116,   117,    36,    37,    40,   128,   146,
       0,    83,    21,   145,    22,   129,    83,    83,   100,     0,
       0,     0,    83,    83,    83,    83,     0,    40,     7,     0,
       0,     0,     0,   132,   133,    14,    15,   157,     0,   107,
     133,     0,     0,     0,     0,     0,   107,   107,     0,   144,
     148,   149,     0,    21,     0,    22,     0,     0,     0,     0,
       0,     0,     0,   151,   107,   133,     0,     0,     0,    83,
       0,   155,   121,   123,    83,     0,     0,    83,     0,   162,
       0,     0,     0,     0,   165,     0,   161,     0,    83,     0,
       0,     0,     0,     0,    83,     0,     0,     0,     0,     0,
       0,     0,    83,    83,    83,     0,     0,   143,     0,    40,
       0,   147,     0,     0,     0,     0,     0,     0,     0,    83,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    83,     0,    40,     0,     0,     0,     0,    83,     0,
       0,     0,    83,     0,    67,     0,    68,    69,    83,    70,
      71,     6,    72,    73,     7,    27,     0,    28,     0,    12,
      13,    14,    15,    74,    75,    76,     0,    16,    77,    78,
      79,    80,     0,    81,    19,     0,    20,     4,     5,    21,
       0,    22,     0,     0,     6,     0,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,     0,     0,     0,     0,
      16,    17,    18,     0,     0,     0,     0,    19,     0,    20,
       0,     0,    21,    68,    22,   135,    70,    71,     6,    72,
      73,     7,    27,     0,    28,     0,    12,    13,    14,    15,
      74,    75,    76,     0,    16,    77,    78,    79,    80,     0,
      81,    19,    92,    20,     0,     0,    21,    68,    22,     0,
      70,    71,     6,    72,    73,     7,    27,     0,    28,     0,
      12,    13,    14,    15,    74,    75,    76,     0,    16,    77,
      78,    79,    80,     0,    81,    19,    92,    20,     0,     0,
      21,    68,    22,   135,    70,    71,     6,    72,    73,     7,
      27,     0,    28,     0,    12,    13,    14,    15,    74,    75,
      76,     0,    16,    77,    78,    79,    80,     0,    81,    19,
       0,    20,     0,     0,    21,    68,    22,     0,    70,    71,
       6,    72,    73,     7,    27,     0,    28,     0,    12,    13,
      14,    15,    74,    75,    76,     0,    16,    77,    78,    79,
      80,     0,    81,    19,   163,    20,     0,     0,    21,    68,
      22,     0,    70,    71,     6,    72,    73,     7,    27,     0,
      28,     0,    12,    13,    14,    15,    74,    75,    76,     0,
      16,    77,    78,    79,    80,     0,    81,    19,    68,    20,
       0,     0,    21,     6,    22,     0,     7,    27,     0,    28,
       0,    12,    13,    14,    15,    74,    75,    76,     0,    16,
      77,    78,    79,    80,     0,    81,    19,     0,    20,   105,
       0,    21,     6,    22,     0,     7,    27,     0,    28,     0,
      12,    13,    14,    15,     0,     0,     0,     0,    16,    17,
      18,     0,     0,     0,   111,   112,     0,    20,   105,     0,
      21,     6,    22,     0,     7,    27,     0,    28,     0,    12,
      13,    14,    15,     0,     0,     0,     0,    16,    17,    18,
       0,     0,     0,     0,    19,   139,    20,   105,     0,    21,
       6,    22,     0,     7,    27,     0,    28,     0,    12,    13,
      14,    15,     0,     0,     0,     0,    16,    17,    18,     0,
       0,     0,     0,    19,   153,    20,   105,     0,    21,     6,
      22,     0,     7,    27,     0,    28,     0,    12,    13,    14,
      15,     0,     0,     0,     0,    16,    17,    18,     0,     0,
       0,     0,   106,     0,    20,   105,     0,    21,     6,    22,
       0,     7,    27,     0,    28,     0,    12,    13,    14,    15,
       0,     0,     0,     0,    16,    17,    18,     0,     0,     0,
       0,    19,     0,    20,   105,     0,    21,     6,    22,     0,
       7,    27,     0,    28,     0,    12,    13,    14,    15,     0,
       0,     0,     0,    16,    17,    18,     0,     0,     0,     0,
     137,     0,    20,     0,     0,    21,     6,    22,     0,     7,
      27,     0,    28,     0,    12,    13,    14,    15,    74,    75,
      76,     0,    16,    77,    78,    79,    80,     0,    81,    19,
       0,    20,     0,     0,    21,     6,    22,     0,     7,    27,
       0,    28,     0,    12,    13,    14,    15,     0,    75,    76,
       0,    16,    77,    78,    79,    80,     0,    81,    19,     0,
      20,     0,     0,    21,     6,    22,     0,     7,    27,     0,
      28,     0,    12,    13,    14,    15,     0,     0,    76,     0,
      16,    77,    78,    79,    80,     0,    81,    19,     0,    20,
       0,     0,    21,     6,    22,     0,     7,    27,     0,    28,
       0,    12,    13,    14,    15,     0,     0,     0,     0,    16,
      77,    78,    79,    80,     0,    81,    19,     0,    20,     0,
       0,    21,     0,    22,     6,   118,     0,     7,    27,     0,
      28,     0,    12,    13,    14,    15,     0,     0,     0,     0,
      16,    17,    18,     0,     0,     0,     0,    19,     0,    20,
       0,     0,    21,     0,    22,     6,   119,     0,     7,    27,
       0,    28,     0,    12,    13,    14,    15,     0,     0,     0,
       0,    16,    17,    18,     0,     0,     0,     0,    19,     0,
      20,     0,     0,    21,     6,    22,     0,     7,    27,     0,
      28,     0,    12,    13,    14,    15,     0,     0,     0,     0,
      16,    17,    18,     0,     0,     0,     0,    19,     0,    20,
       0,     0,    21,     6,    22,     0,     7,    27,     0,    28,
       0,    12,    13,    14,    15,     0,     0,     0,     0,     0,
       0,     0,    79,    80,     0,    81,    19,     0,    20,     0,
       7,    21,    41,    22,    42,     0,     0,    43,    44,    45,
      46,    47,     0,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,     0,    60,    61,     7,
       0,    41,     0,     0,     0,     0,    43,    44,    45,    46,
      47,     0,    48,    88,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     0,     0,    60,    61,     7,     0,
      41,     0,     0,     0,     0,    43,    44,     0,     0,     0,
       0,     0,     0,     0,    51,    52,    53,    54,    55,    56,
      57,    58,    59,     0,     0,    60,    61,   126,   127,    45,
      46,    47,     0,    48,    88,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,     0,    60,    61
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-105))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    40,   106,     5,     6,    73,    32,    11,    34,     0,
      11,    21,    31,    13,    16,    17,    18,    19,    13,    31,
      20,    21,    32,    49,    34,    20,    21,   118,   119,    31,
      33,    33,   136,    37,    37,    35,    37,    63,    38,    49,
      40,    31,    31,   111,   112,    39,    39,    23,    36,     3,
      18,    37,    39,    63,    37,    37,    41,    13,    36,    34,
      70,    71,    34,    36,    20,    21,    68,    37,   111,   137,
      72,    73,    74,    75,    76,    77,    78,    20,    99,    35,
      -1,    24,    38,   122,    40,    99,    29,    30,    67,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    40,    13,    -1,
      -1,    -1,    -1,   105,   106,    20,    21,   146,    -1,   111,
     112,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,   121,
     130,   131,    -1,    38,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   135,   136,   137,    -1,    -1,    -1,    82,
      -1,   143,    85,    86,    87,    -1,    -1,    90,    -1,   159,
      -1,    -1,    -1,    -1,   164,    -1,   158,    -1,   101,    -1,
      -1,    -1,    -1,    -1,   107,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   115,   116,   117,    -1,    -1,   120,    -1,   122,
      -1,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   132,
     133,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   144,    -1,   146,    -1,    -1,    -1,    -1,   151,    -1,
      -1,    -1,   155,    -1,     3,    -1,     5,     6,   161,     8,
       9,    10,    11,    12,    13,    14,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    26,    27,    28,
      29,    30,    -1,    32,    33,    -1,    35,     3,     4,    38,
      -1,    40,    -1,    -1,    10,    -1,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,
      -1,    -1,    38,     5,    40,     7,     8,     9,    10,    11,
      12,    13,    14,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    26,    27,    28,    29,    30,    -1,
      32,    33,    34,    35,    -1,    -1,    38,     5,    40,    -1,
       8,     9,    10,    11,    12,    13,    14,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    26,    27,
      28,    29,    30,    -1,    32,    33,    34,    35,    -1,    -1,
      38,     5,    40,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    -1,    32,    33,
      -1,    35,    -1,    -1,    38,     5,    40,    -1,     8,     9,
      10,    11,    12,    13,    14,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    26,    27,    28,    29,
      30,    -1,    32,    33,    34,    35,    -1,    -1,    38,     5,
      40,    -1,     8,     9,    10,    11,    12,    13,    14,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      26,    27,    28,    29,    30,    -1,    32,    33,     5,    35,
      -1,    -1,    38,    10,    40,    -1,    13,    14,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    26,
      27,    28,    29,    30,    -1,    32,    33,    -1,    35,     7,
      -1,    38,    10,    40,    -1,    13,    14,    -1,    16,    -1,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    26,    27,
      28,    -1,    -1,    -1,    32,    33,    -1,    35,     7,    -1,
      38,    10,    40,    -1,    13,    14,    -1,    16,    -1,    18,
      19,    20,    21,    -1,    -1,    -1,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    33,    34,    35,     7,    -1,    38,
      10,    40,    -1,    13,    14,    -1,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,
      -1,    -1,    -1,    33,    34,    35,     7,    -1,    38,    10,
      40,    -1,    13,    14,    -1,    16,    -1,    18,    19,    20,
      21,    -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    -1,    35,     7,    -1,    38,    10,    40,
      -1,    13,    14,    -1,    16,    -1,    18,    19,    20,    21,
      -1,    -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,
      -1,    33,    -1,    35,     7,    -1,    38,    10,    40,    -1,
      13,    14,    -1,    16,    -1,    18,    19,    20,    21,    -1,
      -1,    -1,    -1,    26,    27,    28,    -1,    -1,    -1,    -1,
      33,    -1,    35,    -1,    -1,    38,    10,    40,    -1,    13,
      14,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    -1,    32,    33,
      -1,    35,    -1,    -1,    38,    10,    40,    -1,    13,    14,
      -1,    16,    -1,    18,    19,    20,    21,    -1,    23,    24,
      -1,    26,    27,    28,    29,    30,    -1,    32,    33,    -1,
      35,    -1,    -1,    38,    10,    40,    -1,    13,    14,    -1,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    24,    -1,
      26,    27,    28,    29,    30,    -1,    32,    33,    -1,    35,
      -1,    -1,    38,    10,    40,    -1,    13,    14,    -1,    16,
      -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    -1,    32,    33,    -1,    35,    -1,
      -1,    38,    -1,    40,    10,    11,    -1,    13,    14,    -1,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,
      -1,    -1,    38,    -1,    40,    10,    11,    -1,    13,    14,
      -1,    16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    33,    -1,
      35,    -1,    -1,    38,    10,    40,    -1,    13,    14,    -1,
      16,    -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,
      -1,    -1,    38,    10,    40,    -1,    13,    14,    -1,    16,
      -1,    18,    19,    20,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    -1,    32,    33,    -1,    35,    -1,
      13,    38,    15,    40,    17,    -1,    -1,    20,    21,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    40,    41,    13,
      -1,    15,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    40,    41,    13,    -1,
      15,    -1,    -1,    -1,    -1,    20,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    40,    41,    20,    21,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    -1,    40,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    43,    44,     0,     3,     4,    10,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    26,    27,    28,    33,
      35,    38,    40,    45,    46,    48,    56,    14,    16,    46,
      46,    31,    31,    31,    31,    46,    46,    46,    46,    47,
      48,    15,    17,    20,    21,    22,    23,    24,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      40,    41,    53,    54,    55,    56,    57,     3,     5,     6,
       8,     9,    11,    12,    22,    23,    24,    27,    28,    29,
      30,    32,    46,    48,    58,    11,    37,    46,    27,    53,
      46,    53,    34,    36,    47,    39,    53,    39,    53,    23,
      58,    46,    18,    56,    56,     7,    33,    46,    49,    50,
      52,    32,    33,    51,    52,    46,    46,    46,    11,    11,
      11,    48,    35,    48,    37,    39,    20,    21,    55,    57,
      37,    37,    46,    46,    50,     7,    41,    33,    51,    34,
      52,    49,    49,    48,    46,    47,    35,    48,    56,    56,
      34,    46,    50,    34,    34,    46,    36,    47,    33,    37,
      36,    46,    56,    34,    37,    56
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 99 "hfst-compiler.yy"
    { Result=compiler->result((yyvsp[(2) - (3)].expression), Switch); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 102 "hfst-compiler.yy"
    {}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 103 "hfst-compiler.yy"
    {}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 104 "hfst-compiler.yy"
    {}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 107 "hfst-compiler.yy"
    { if (DEBUG) { printf("defining transducer variable \"%s\"..\n", (yyvsp[(1) - (3)].name)); }; if (compiler->def_var((yyvsp[(1) - (3)].name),(yyvsp[(3) - (3)].expression))) warn2("assignment of empty transducer to",(yyvsp[(1) - (3)].name)); if(DEBUG) printf("done\n"); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 108 "hfst-compiler.yy"
    { if (DEBUG) { printf("defining agreement transducer variable \"%s\"..\n", (yyvsp[(1) - (3)].name)); }; if (compiler->def_rvar((yyvsp[(1) - (3)].name),(yyvsp[(3) - (3)].expression))) warn2("assignment of empty transducer to",(yyvsp[(1) - (3)].name)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 109 "hfst-compiler.yy"
    { if (DEBUG) { printf("defining range variable \"%s\"..\n", (yyvsp[(1) - (3)].name)); }; if (compiler->def_svar((yyvsp[(1) - (3)].name),(yyvsp[(3) - (3)].range))) warn2("assignment of empty symbol range to",(yyvsp[(1) - (3)].name)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 110 "hfst-compiler.yy"
    { if (DEBUG) { printf("defining agreement range variable \"%s\"..\n", (yyvsp[(1) - (3)].name)); }; if (compiler->def_svar((yyvsp[(1) - (3)].name),(yyvsp[(3) - (3)].range))) warn2("assignment of empty symbol range to",(yyvsp[(1) - (3)].name)); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 111 "hfst-compiler.yy"
    { compiler->write_to_file((yyvsp[(1) - (3)].expression), folder, (yyvsp[(3) - (3)].value)); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 112 "hfst-compiler.yy"
    { if (DEBUG) { printf("defining alphabet..\n"); }; compiler->def_alphabet((yyvsp[(2) - (2)].expression)); delete (yyvsp[(2) - (2)].expression); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 115 "hfst-compiler.yy"
    { (yyval.expression) = compiler->restriction((yyvsp[(1) - (3)].expression),(yyvsp[(2) - (3)].type),(yyvsp[(3) - (3)].contexts),0); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 116 "hfst-compiler.yy"
    { (yyval.expression) = compiler->restriction((yyvsp[(1) - (4)].expression),(yyvsp[(3) - (4)].type),(yyvsp[(4) - (4)].contexts),1); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 117 "hfst-compiler.yy"
    { (yyval.expression) = compiler->restriction((yyvsp[(1) - (4)].expression),(yyvsp[(3) - (4)].type),(yyvsp[(4) - (4)].contexts),-1); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 118 "hfst-compiler.yy"
    { (yyvsp[(1) - (3)].expression) = compiler->explode((yyvsp[(1) - (3)].expression)); (yyvsp[(1) - (3)].expression)->minimize(); (yyval.expression) = compiler->replace_in_context((yyvsp[(1) - (3)].expression), (yyvsp[(2) - (3)].rtype), (yyvsp[(3) - (3)].contexts), false); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 119 "hfst-compiler.yy"
    { (yyvsp[(1) - (4)].expression) = compiler->explode((yyvsp[(1) - (4)].expression)); (yyvsp[(1) - (4)].expression)->minimize(); (yyval.expression) = compiler->replace_in_context((yyvsp[(1) - (4)].expression), (yyvsp[(2) - (4)].rtype), (yyvsp[(4) - (4)].contexts), true); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 120 "hfst-compiler.yy"
    { (yyvsp[(1) - (4)].expression) = compiler->explode((yyvsp[(1) - (4)].expression)); (yyvsp[(1) - (4)].expression)->minimize(); (yyval.expression) = compiler->replace((yyvsp[(1) - (4)].expression), (yyvsp[(2) - (4)].rtype), false); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 121 "hfst-compiler.yy"
    { (yyvsp[(1) - (5)].expression) = compiler->explode((yyvsp[(1) - (5)].expression)); (yyvsp[(1) - (5)].expression)->minimize(); (yyval.expression) = compiler->replace((yyvsp[(1) - (5)].expression), (yyvsp[(2) - (5)].rtype), true); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 122 "hfst-compiler.yy"
    { (yyval.expression) = compiler->make_rule((yyvsp[(1) - (5)].expression),(yyvsp[(2) - (5)].range),(yyvsp[(3) - (5)].type),(yyvsp[(4) - (5)].range),(yyvsp[(5) - (5)].expression), output_format); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 123 "hfst-compiler.yy"
    { (yyval.expression) = compiler->make_rule((yyvsp[(1) - (4)].expression),(yyvsp[(2) - (4)].range),(yyvsp[(3) - (4)].type),(yyvsp[(4) - (4)].range),NULL, output_format); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 124 "hfst-compiler.yy"
    { (yyval.expression) = compiler->make_rule(NULL,(yyvsp[(1) - (4)].range),(yyvsp[(2) - (4)].type),(yyvsp[(3) - (4)].range),(yyvsp[(4) - (4)].expression), output_format); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 125 "hfst-compiler.yy"
    { (yyval.expression) = compiler->make_rule(NULL,(yyvsp[(1) - (3)].range),(yyvsp[(2) - (3)].type),(yyvsp[(3) - (3)].range),NULL, output_format); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 126 "hfst-compiler.yy"
    { (yyvsp[(1) - (3)].expression)->compose(*(yyvsp[(3) - (3)].expression)); delete (yyvsp[(3) - (3)].expression); (yyval.expression) = (yyvsp[(1) - (3)].expression); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 127 "hfst-compiler.yy"
    { (yyval.expression) = compiler->make_mapping((yyvsp[(2) - (7)].ranges),(yyvsp[(6) - (7)].ranges),output_format); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 128 "hfst-compiler.yy"
    { (yyval.expression) = compiler->make_mapping(compiler->add_range((yyvsp[(1) - (5)].range),NULL),(yyvsp[(4) - (5)].ranges),output_format); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 129 "hfst-compiler.yy"
    { (yyval.expression) = compiler->make_mapping((yyvsp[(2) - (5)].ranges),compiler->add_range((yyvsp[(5) - (5)].range),NULL),output_format); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 130 "hfst-compiler.yy"
    { (yyval.expression) = compiler->insert_freely((yyvsp[(1) - (5)].expression),(yyvsp[(3) - (5)].character),(yyvsp[(5) - (5)].character)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 131 "hfst-compiler.yy"
    { (yyval.expression) = compiler->insert_freely((yyvsp[(1) - (3)].expression),(yyvsp[(3) - (3)].character),(yyvsp[(3) - (3)].character)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 132 "hfst-compiler.yy"
    { (yyval.expression) = compiler->substitute((yyvsp[(1) - (5)].expression),(yyvsp[(3) - (5)].character),(yyvsp[(5) - (5)].character)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 133 "hfst-compiler.yy"
    { (yyval.expression) = compiler->substitute((yyvsp[(1) - (9)].expression),(yyvsp[(3) - (9)].character),(yyvsp[(5) - (9)].character),(yyvsp[(7) - (9)].character),(yyvsp[(9) - (9)].character)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 134 "hfst-compiler.yy"
    { (yyval.expression) = compiler->substitute((yyvsp[(1) - (8)].expression),(yyvsp[(3) - (8)].character),(yyvsp[(5) - (8)].character),(yyvsp[(7) - (8)].expression)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 135 "hfst-compiler.yy"
    { (yyval.expression) = compiler->new_transducer((yyvsp[(1) - (3)].range),(yyvsp[(3) - (3)].range),output_format); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 136 "hfst-compiler.yy"
    { (yyval.expression) = compiler->new_transducer((yyvsp[(1) - (1)].range),(yyvsp[(1) - (1)].range),output_format); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 137 "hfst-compiler.yy"
    { if (DEBUG) { printf("calling transducer variable \"%s\"\n", (yyvsp[(1) - (1)].name)); }; (yyval.expression) = compiler->var_value((yyvsp[(1) - (1)].name)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 138 "hfst-compiler.yy"
    { if (DEBUG) { printf("calling agreement transducer variable \"%s\"\n", (yyvsp[(1) - (1)].name)); }; (yyval.expression) = compiler->rvar_value((yyvsp[(1) - (1)].name),output_format); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 139 "hfst-compiler.yy"
    { (yyvsp[(1) - (2)].expression)->repeat_star(); (yyval.expression) = (yyvsp[(1) - (2)].expression); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 140 "hfst-compiler.yy"
    { (yyvsp[(1) - (2)].expression)->repeat_plus(); (yyval.expression) = (yyvsp[(1) - (2)].expression); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 141 "hfst-compiler.yy"
    { (yyvsp[(1) - (2)].expression)->optionalize(); (yyval.expression) = (yyvsp[(1) - (2)].expression); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 142 "hfst-compiler.yy"
    { (yyvsp[(1) - (2)].expression)->concatenate(*(yyvsp[(2) - (2)].expression)); delete (yyvsp[(2) - (2)].expression); (yyval.expression) = (yyvsp[(1) - (2)].expression); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 143 "hfst-compiler.yy"
    { (yyval.expression) = compiler->negation((yyvsp[(2) - (2)].expression)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 144 "hfst-compiler.yy"
    { (yyvsp[(2) - (2)].expression)->invert(); (yyval.expression) = (yyvsp[(2) - (2)].expression); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 145 "hfst-compiler.yy"
    { (yyvsp[(2) - (2)].expression)->output_project(); (yyval.expression) = (yyvsp[(2) - (2)].expression); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 146 "hfst-compiler.yy"
    { (yyvsp[(2) - (2)].expression)->input_project(); (yyval.expression) = (yyvsp[(2) - (2)].expression); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 147 "hfst-compiler.yy"
    { (yyvsp[(1) - (3)].expression)->intersect(*(yyvsp[(3) - (3)].expression)); delete (yyvsp[(3) - (3)].expression); (yyval.expression) = (yyvsp[(1) - (3)].expression); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 148 "hfst-compiler.yy"
    { (yyvsp[(1) - (3)].expression)->subtract(*(yyvsp[(3) - (3)].expression)); delete (yyvsp[(3) - (3)].expression); (yyval.expression) = (yyvsp[(1) - (3)].expression); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 149 "hfst-compiler.yy"
    { (yyvsp[(1) - (3)].expression)->disjunct(*(yyvsp[(3) - (3)].expression)); delete (yyvsp[(3) - (3)].expression); (yyval.expression) = (yyvsp[(1) - (3)].expression); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 150 "hfst-compiler.yy"
    { (yyval.expression) = (yyvsp[(2) - (3)].expression); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 151 "hfst-compiler.yy"
    { (yyval.expression) = compiler->read_words(folder, (yyvsp[(1) - (1)].value), output_format); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 152 "hfst-compiler.yy"
    { try { (yyval.expression) = compiler->read_transducer(folder, (yyvsp[(1) - (1)].value), output_format); } catch (HfstException e) { printf("\nAn error happened when reading file \"%s\"\n", (yyvsp[(1) - (1)].value)); exit(1); } }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 155 "hfst-compiler.yy"
    { (yyval.ranges) = compiler->add_range((yyvsp[(1) - (2)].range),(yyvsp[(2) - (2)].ranges)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 156 "hfst-compiler.yy"
    { (yyval.ranges) = NULL; }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 159 "hfst-compiler.yy"
    { (yyval.range)=(yyvsp[(2) - (3)].range); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 160 "hfst-compiler.yy"
    { (yyval.range)=compiler->complement_range((yyvsp[(3) - (4)].range)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 161 "hfst-compiler.yy"
    { if (DEBUG) { printf("calling agreement range variable \"%s\"\n", (yyvsp[(2) - (3)].name)); }; (yyval.range)=compiler->rsvar_value((yyvsp[(2) - (3)].name)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 162 "hfst-compiler.yy"
    { (yyval.range)=NULL; }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 163 "hfst-compiler.yy"
    { (yyval.range)=compiler->add_value((yyvsp[(1) - (1)].character),NULL); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 166 "hfst-compiler.yy"
    { (yyval.contexts) = (yyvsp[(1) - (1)].contexts); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 167 "hfst-compiler.yy"
    { (yyval.contexts) = (yyvsp[(2) - (3)].contexts); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 170 "hfst-compiler.yy"
    { (yyval.contexts) = compiler->add_context((yyvsp[(1) - (3)].contexts),(yyvsp[(3) - (3)].contexts)); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 171 "hfst-compiler.yy"
    { (yyval.contexts) = (yyvsp[(1) - (1)].contexts); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 174 "hfst-compiler.yy"
    { (yyval.contexts) = (yyvsp[(1) - (1)].contexts); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 175 "hfst-compiler.yy"
    { (yyval.contexts) = (yyvsp[(2) - (3)].contexts); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 178 "hfst-compiler.yy"
    { (yyval.contexts) = compiler->make_context((yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression)); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 179 "hfst-compiler.yy"
    { (yyval.contexts) = compiler->make_context(NULL, (yyvsp[(2) - (2)].expression)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 180 "hfst-compiler.yy"
    { (yyval.contexts) = compiler->make_context((yyvsp[(1) - (2)].expression), NULL); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 183 "hfst-compiler.yy"
    { (yyval.range)=compiler->append_values((yyvsp[(1) - (2)].range),(yyvsp[(2) - (2)].range)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 184 "hfst-compiler.yy"
    { (yyval.range) = (yyvsp[(1) - (1)].range); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 187 "hfst-compiler.yy"
    { (yyval.range)=compiler->add_values((yyvsp[(1) - (3)].longchar),(yyvsp[(3) - (3)].longchar),NULL); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 188 "hfst-compiler.yy"
    { if (DEBUG) { printf("calling range variable \"%s\"", (yyvsp[(1) - (1)].name)); }; (yyval.range)=compiler->svar_value((yyvsp[(1) - (1)].name)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 189 "hfst-compiler.yy"
    { (yyval.range)=compiler->add_value(compiler->character_code((yyvsp[(1) - (1)].longchar)),NULL); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 190 "hfst-compiler.yy"
    { (yyval.range)=compiler->add_value((yyvsp[(1) - (1)].character),NULL); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 191 "hfst-compiler.yy"
    { (yyval.range)=compiler->add_value((yyvsp[(1) - (1)].uchar),NULL); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 194 "hfst-compiler.yy"
    { (yyval.longchar)=(yyvsp[(1) - (1)].uchar); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 195 "hfst-compiler.yy"
    { (yyval.longchar)=compiler->utf8toint((yyvsp[(1) - (1)].value)); free((yyvsp[(1) - (1)].value)); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 196 "hfst-compiler.yy"
    { (yyval.longchar)=(yyvsp[(1) - (1)].uchar); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 199 "hfst-compiler.yy"
    { (yyval.character)=compiler->character_code((yyvsp[(1) - (1)].uchar)); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 200 "hfst-compiler.yy"
    { (yyval.character)=compiler->symbol_code((yyvsp[(1) - (1)].value)); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 201 "hfst-compiler.yy"
    { (yyval.character)=compiler->symbol_code((yyvsp[(1) - (1)].name)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 204 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('.'); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 205 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('!'); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 206 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('?'); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 207 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('{'); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 208 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('}'); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 209 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code(')'); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 210 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('('); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 211 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('&'); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 212 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('|'); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 213 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('*'); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 214 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('+'); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 215 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code(':'); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 216 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code(','); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 217 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('='); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 218 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('_'); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 219 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('^'); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 220 "hfst-compiler.yy"
    { (yyval.uchar)=(unsigned char)compiler->character_code('-'); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 223 "hfst-compiler.yy"
    {}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 224 "hfst-compiler.yy"
    {}
    break;



/* Line 1806 of yacc.c  */
#line 2445 "hfst-compiler.cc"
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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
#line 227 "hfst-compiler.yy"


extern FILE  *yyin;
static int Compact=0;
static int LowMem=0;

/*******************************************************************/
/*                                                                 */
/*  yyerror                                                        */
/*                                                                 */
/*******************************************************************/

void yyerror(char *text)

{
  cerr << "\n" << FileName << ":" << yylineno << ": " << text << " at: ";
  cerr << yytext << "\naborted.\n";
  exit(1);
}


/*******************************************************************/
/*                                                                 */
/*  warn                                                           */
/*                                                                 */
/*******************************************************************/

void warn(char *text)

{
  cerr << "\n" << FileName << ":" << yylineno << ": warning: " << text << "!\n";
}


/*******************************************************************/
/*                                                                 */
/*  warn2                                                          */
/*                                                                 */
/*******************************************************************/

void warn2(const char *text, char *text2)  // HFST: added const

{
  cerr << "\n" << FileName << ":" << yylineno << ": warning: " << text << ": ";
  cerr << text2 << "\n";
}


/* print_usage */

void
print_usage()
{
    // c.f. http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dhelp
    fprintf(message_out, "Usage: %s %s [OPTIONS...] [INFILE]\n"
        "Compile a file written with SFST programming language into a transducer.\n"
        "\n", program_name, "(alias hfst-calculate)"); 
        print_common_program_options(message_out);
	fprintf(message_out, "Input/Output options:\n"
                "  -i, --input=INFILE     Read input from INFILE\n"
                "  -o, --output=OUTFILE   Write output transducer to OUTFILE\n");	      
        fprintf(message_out, "String and format options:\n"
                "  -f, --format=FMT       Write result in FMT format\n");
        fprintf(message_out, "\n");

        fprintf(message_out, 
            "If OUTFILE or INFILE is missing or -, standard streams will be used.\n"
            "FMT must be one of the following: "
            "{foma, sfst, openfst-tropical, openfst-log}\n"
            );
        fprintf(message_out, "\n");
        fprintf(message_out, "Examples:\n"
            "  echo \"[a-z]*\" | %s -f foma > az.foma\n"
	    "    create a foma transducer accepting any number of consecutive\n"
	    "    characters between a and z, inclusive\n"
	    "\n"
            "  echo \"a:b (a:<>)+\" > ab.sfst-pl ; %s -f openfst-tropical \\\n"
	    "   -i ab.sfst-pl -o ab.tropical\n"
	    "    create a tropical OpenFst transducer that accepts two or more\n"
	    "    consecutive 'a's and maps them into string \"b\"\n"
             "\n", program_name, program_name);
        print_report_bugs();
        print_more_info();
        fprintf(message_out, "\n");
}


int
parse_options(int argc, char** argv)
{
    // use of this function requires options are settable on global scope
    while (true)
    {
        static const struct option long_options[] =
        {
        HFST_GETOPT_COMMON_LONG,
        HFST_GETOPT_UNARY_LONG,
          {"format", required_argument, 0, 'f'},
	  {"harmonize-smaller", no_argument, 0, 'H'},
	  {"weighted", no_argument, 0, 'w'},
          {0,0,0,0}
        };
        int option_index = 0;
        char c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             HFST_GETOPT_UNARY_SHORT "f:Hw",
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }

        switch (c)
        {
#include "inc/getopt-cases-common.h"
#include "inc/getopt-cases-unary.h"
        case 'f':
            output_format = hfst_parse_format_name(optarg);
            break;
	case 'H':
	    hfst::set_harmonize_smaller(true);
	    break;
	case'w':
            verbose_printf(
	    "Interpreting deprecated -w switch as openfst tropical format\n");
	    output_format = hfst::TROPICAL_OPENFST_TYPE;
	    break;
	    	 
#include "inc/getopt-cases-error.h"
        }
    }

#include "inc/check-params-common.h"
#include "inc/check-params-unary.h"
    Verbose = verbose;	 
    if (output_format == hfst::ERROR_TYPE)
      {
        verbose_printf("Output format not specified, "
             "defaulting to openfst tropical\n");
        output_format = hfst::TROPICAL_OPENFST_TYPE;
      }
    FileName = strdup(inputfilename);        

    if (NULL != inputfilename && strcmp(inputfilename, "<stdin>") != 0)
    {
	std::string str(inputfilename);
	size_t found = str.find_last_of("/\\");
	if (found != std::string::npos)
  	  folder = strdup(str.substr(0,found).c_str());
    }

    return EXIT_CONTINUE;
}


/*******************************************************************/
/*                                                                 */
/*  get_flags                                                      */
/*                                                                 */
/*******************************************************************/

void get_flags( int *argc, char **argv )

{
  for( int i=1; i<*argc; i++ ) {
    if (strcmp(argv[i],"-c") == 0) {
      Compact = 1;
      argv[i] = NULL;
    }
    else if (strcmp(argv[i],"-l") == 0) {
      LowMem = 1;
      argv[i] = NULL;
    }
    else if (strcmp(argv[i],"-q") == 0) {
      Verbose = 0;
      argv[i] = NULL;
    }
    else if (strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0) {
      print_usage();
      exit(0);
    }
    else if (strcmp(argv[i],"-v") == 0 || strcmp(argv[i],"--version") == 0) {
      fprintf(stdout, "hfst-sfstpl2fst 0.1 (hfst 3.0)\n");
      exit(0);
    }
    else if (strcmp(argv[i],"-s") == 0) {
      Switch = 1;
      argv[i] = NULL;
    }
    // hfst addition
    else if (strcmp(argv[i],"-sfst") == 0) {
      output_format = SFST_TYPE;
      argv[i] = NULL;
    }
    else if (strcmp(argv[i],"-tropical") == 0) {
      output_format = TROPICAL_OPENFST_TYPE;
      argv[i] = NULL;
    }
    else if (strcmp(argv[i],"-log") == 0) {
      output_format = LOG_OPENFST_TYPE;
      argv[i] = NULL;
    }
    else if (strcmp(argv[i],"-foma") == 0) {
      output_format = FOMA_TYPE;
      argv[i] = NULL;
    }
  }
  // remove flags from the argument list
  int k;
  for( int i=k=1; i<*argc; i++)
    if (argv[i] != NULL)
      argv[k++] = argv[i];
  *argc = k;
}


/*******************************************************************/
/*                                                                 */
/*  main                                                           */
/*                                                                 */
/*******************************************************************/

int main( int argc, char *argv[] )

{
#ifdef WINDOWS
  _setmode(1, _O_BINARY);
#endif

  //FILE *file;

  hfst_set_program_name(argv[0], "0.1", "HfstSfstPl2Fst");
  int retval = parse_options(argc, argv);
  if (retval != EXIT_CONTINUE)
    return retval;

  yyin = inputfile;  
  if (strcmp(outfilename,"<stdout>") != 0)
    fclose(outfile); // stream is used when writing the result

  // Unknown symbols cannot be used in SFST-PL syntax.
  // If the HFST library is aware of this, some optimization can be done.
  hfst::set_unknown_symbols_in_use(false);
  compiler = new HfstCompiler(output_format, Verbose);

  try {
    yyparse();
    fclose(inputfile);
      try {
        if (strcmp(outfilename,"<stdout>") == 0)
          compiler->write_to_file(Result, NULL, "");
	else
          compiler->write_to_file(Result, NULL, strdup(outfilename));
      } catch (HfstException e) {
          printf("\nAn error happened when writing to file \"%s\"\n", outfilename); }
    //printf("type is: %i\n", Result->get_type());
    delete Result;
    // fprintf(stderr, "seconds spent in SFST::harmonize: %f\n", HfstTransducer::get_profile_seconds(output_format));
    // delete compiler;
  }
  catch(const char* p) {
      cerr << "\n" << p << "\n\n";
      exit(1);
  }
  if (NULL != folder)
    free(folder);

  exit(0);
}

