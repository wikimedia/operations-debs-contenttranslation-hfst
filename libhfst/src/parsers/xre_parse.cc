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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         xreparse
#define yylex           xrelex
#define yyerror         xreerror
#define yylval          xrelval
#define yychar          xrechar
#define yydebug         xredebug
#define yynerrs         xrenerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "xre_parse.yy"

#define YYDEBUG 1 

#include <stdio.h>
#include <assert.h>
#include <iostream>

#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstXeroxRules.h"

using namespace hfst;
using hfst::HfstTransducer;
using namespace hfst::xeroxRules;
using namespace hfst::implementations;

#include "xre_utils.h"

namespace hfst { 
  namespace xre {
    // number of characters read, used for scanning function definition xre for argument symbols
    extern unsigned int cr;
    extern bool harmonize_;
    extern bool harmonize_flags_;
    extern bool allow_extra_text_at_end;

    bool has_weight_been_zeroed = false; // to control how many times a warning is given
    float zero_weights(float f)
    {
        if ((! has_weight_been_zeroed) && (f != 0))
        {
            hfst::xre::warn("warning: ignoring weights in rule context\n");
            has_weight_been_zeroed = true;
        }
        return 0;
    }

    bool is_weighted()
    {   
        return (hfst::xre::format == hfst::TROPICAL_OPENFST_TYPE || 
                hfst::xre::format == hfst::LOG_OPENFST_TYPE);
    }
  }
}

using hfst::xre::harmonize_;
using hfst::xre::harmonize_flags_;

union YYSTYPE;
class yy_buffer_state;
typedef yy_buffer_state * YY_BUFFER_STATE;
typedef void * yyscan_t;

extern int xreparse(yyscan_t);
extern int xrelex_init (yyscan_t*);
extern YY_BUFFER_STATE xre_scan_string (const char *, yyscan_t);
extern void xre_delete_buffer (YY_BUFFER_STATE, yyscan_t);
extern int xrelex_destroy (yyscan_t);

extern int xreerror(yyscan_t, const char*);
extern int xreerror(const char*);
int xrelex ( YYSTYPE * , yyscan_t );



/* Line 268 of yacc.c  */
#line 145 "xre_parse.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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

/* Line 293 of yacc.c  */
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




/* Line 293 of yacc.c  */
#line 375 "xre_parse.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 387 "xre_parse.cc"

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
#define YYFINAL  60
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   663

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  135
/* YYNRULES -- Number of states.  */
#define YYNSTATES  213

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

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
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    14,    16,    20,
      24,    28,    38,    42,    47,    50,    53,    55,    57,    59,
      63,    65,    67,    70,    74,    76,    80,    86,    91,    96,
     101,   107,   112,   118,   121,   123,   127,   131,   134,   137,
     139,   141,   143,   145,   147,   149,   151,   153,   155,   157,
     159,   161,   163,   165,   169,   173,   177,   179,   183,   189,
     195,   197,   201,   205,   208,   211,   213,   215,   219,   223,
     227,   231,   235,   239,   243,   245,   248,   250,   254,   258,
     262,   264,   267,   270,   274,   277,   280,   282,   285,   288,
     291,   294,   297,   300,   303,   306,   309,   312,   314,   317,
     319,   323,   331,   337,   343,   349,   355,   360,   364,   366,
     369,   371,   374,   376,   378,   380,   382,   384,   386,   390,
     393,   396,   398,   402,   406,   408,   412,   416,   418,   420,
     422,   424,   426,   428,   432,   434
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      85,     0,    -1,    86,    -1,    -1,    87,    80,    -1,    87,
       3,    -1,    87,    -1,    91,    -1,    87,     9,    91,    -1,
      87,    10,    91,    -1,    87,     8,    91,    -1,    88,   116,
      81,   116,    42,   116,    81,   116,    68,    -1,    88,    89,
      90,    -1,    46,    67,    91,    42,    -1,   116,    42,    -1,
     112,    68,    -1,    68,    -1,   101,    -1,    92,    -1,    92,
      41,    93,    -1,    93,    -1,    94,    -1,    94,    96,    -1,
      94,    42,    95,    -1,    95,    -1,    91,   100,    91,    -1,
      91,   100,    91,    11,    91,    -1,    91,   100,    91,    11,
      -1,    91,   100,    11,    91,    -1,    71,    72,   100,    91,
      -1,    71,    91,    72,   100,    91,    -1,    91,   100,    71,
      72,    -1,    91,   100,    71,    91,    72,    -1,    99,    97,
      -1,    98,    -1,    97,    42,    98,    -1,    91,    12,    91,
      -1,    91,    12,    -1,    12,    91,    -1,    12,    -1,    31,
      -1,    30,    -1,    29,    -1,    28,    -1,    27,    -1,    25,
      -1,    21,    -1,    20,    -1,    19,    -1,    18,    -1,    26,
      -1,    24,    -1,   102,    -1,   101,    13,   102,    -1,   101,
      44,   102,    -1,   101,    43,   102,    -1,   105,    -1,   102,
      15,   103,    -1,   102,    16,   105,    12,   105,    -1,   102,
      14,   105,    12,   105,    -1,   104,    -1,   103,    42,   104,
      -1,   102,    12,   102,    -1,   102,    12,    -1,    12,   102,
      -1,    12,    -1,   106,    -1,   105,    37,   106,    -1,   105,
       7,   106,    -1,   105,    36,   106,    -1,   105,    35,   106,
      -1,   105,    34,   106,    -1,   105,    33,   106,    -1,   105,
      32,   106,    -1,   107,    -1,   106,   107,    -1,   108,    -1,
     107,    40,   108,    -1,   107,    39,   108,    -1,   107,    38,
     108,    -1,   109,    -1,    50,   108,    -1,    49,   108,    -1,
      49,     4,   108,    -1,    48,   108,    -1,    47,   108,    -1,
     110,    -1,   109,    52,    -1,   109,    51,    -1,   109,    56,
      -1,   109,    55,    -1,   109,    54,    -1,   109,    53,    -1,
     109,    60,    -1,   109,    59,    -1,   109,    58,    -1,   109,
      57,    -1,   111,    -1,    45,   110,    -1,   113,    -1,    67,
      87,    68,    -1,    67,    87,    68,    81,    67,    87,    68,
      -1,    67,    87,    68,    81,     5,    -1,     5,    81,    67,
      87,    68,    -1,    67,    87,    68,    81,   116,    -1,   116,
      81,    67,    87,    68,    -1,    67,    87,    68,     4,    -1,
      69,    87,    70,    -1,   116,    -1,   112,   116,    -1,   114,
      -1,   114,     4,    -1,    65,    -1,    64,    -1,    63,    -1,
      62,    -1,    61,    -1,   116,    -1,   116,    81,   116,    -1,
     116,    74,    -1,    75,   116,    -1,    82,    -1,   116,    81,
       5,    -1,     5,    81,   116,    -1,     5,    -1,     5,    81,
       5,    -1,   118,   117,    70,    -1,     6,    -1,    83,    -1,
     115,    -1,    76,    -1,    77,    -1,    78,    -1,   117,    42,
      87,    -1,    87,    -1,    66,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   166,   166,   168,   174,   185,   196,   208,   213,   237,
     241,   246,   250,   316,   317,   318,   320,   327,   328,   366,
     379,   390,   399,   411,   428,   440,   449,   458,   468,   478,
     488,   495,   503,   513,   518,   526,   534,   556,   572,   588,
     594,   598,   602,   606,   612,   616,   620,   624,   628,   632,
     636,   640,   647,   648,   653,   657,   664,   666,   672,   679,
     687,   695,   704,   709,   719,   725,   733,   734,   738,   743,
     747,   752,   757,   761,   771,   772,   778,   779,   783,   788,
     795,   796,   804,   817,   827,   833,   839,   840,   843,   846,
     849,   852,   855,   858,   861,   865,   868,   874,   875,   889,
     890,   894,   899,   906,   913,   920,   926,   929,   935,   946,
     963,   964,   967,   982,  1006,  1030,  1054,  1098,  1112,  1117,
    1122,  1126,  1129,  1137,  1145,  1149,  1155,  1197,  1198,  1201,
    1210,  1213,  1216,  1221,  1225,  1232
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "END_OF_WEIGHTED_EXPRESSION", "WEIGHT",
  "CURLY_BRACKETS", "SYMBOL", "INTERSECTION", "LENIENT_COMPOSITION",
  "COMPOSITION", "CROSS_PRODUCT", "MARKUP_MARKER", "CENTER_MARKER",
  "SHUFFLE", "LEFT_RIGHT_ARROW", "RIGHT_ARROW", "LEFT_ARROW",
  "LEFT_RESTRICTION", "LTR_SHORTEST_MATCH", "LTR_LONGEST_MATCH",
  "RTL_SHORTEST_MATCH", "RTL_LONGEST_MATCH", "OPTIONAL_REPLACE_LEFT_RIGHT",
  "REPLACE_LEFT_RIGHT", "OPTIONAL_REPLACE_LEFT", "OPTIONAL_REPLACE_RIGHT",
  "REPLACE_LEFT", "REPLACE_RIGHT", "REPLACE_CONTEXT_LL",
  "REPLACE_CONTEXT_UL", "REPLACE_CONTEXT_LU", "REPLACE_CONTEXT_UU",
  "LOWER_PRIORITY_UNION", "UPPER_PRIORITY_UNION", "LOWER_MINUS",
  "UPPER_MINUS", "MINUS", "UNION", "LEFT_QUOTIENT", "IGNORE_INTERNALLY",
  "IGNORING", "COMMACOMMA", "COMMA", "AFTER", "BEFORE", "TERM_COMPLEMENT",
  "SUBSTITUTE_LEFT", "CONTAINMENT_OPT", "CONTAINMENT_ONCE", "CONTAINMENT",
  "COMPLEMENT", "PLUS", "STAR", "LOWER", "UPPER", "INVERT", "REVERSE",
  "CATENATE_N_TO_K", "CATENATE_N_MINUS", "CATENATE_N_PLUS", "CATENATE_N",
  "READ_RE", "READ_PROLOG", "READ_SPACED", "READ_TEXT", "READ_BIN",
  "FUNCTION_NAME", "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PARENTHESIS",
  "RIGHT_PARENTHESIS", "LEFT_BRACKET_DOTTED", "RIGHT_BRACKET_DOTTED",
  "SUBVAL", "PAIR_SEPARATOR_WO_RIGHT", "PAIR_SEPARATOR_WO_LEFT",
  "EPSILON_TOKEN", "ANY_TOKEN", "BOUNDARY_MARKER", "LEXER_ERROR",
  "END_OF_EXPRESSION", "PAIR_SEPARATOR", "PAIR_SEPARATOR_SOLE",
  "QUOTED_LITERAL", "$accept", "XRE", "REGEXP1", "REGEXP2", "SUB1", "SUB2",
  "SUB3", "REPLACE", "PARALLEL_RULES", "RULE", "MAPPINGPAIR_VECTOR",
  "MAPPINGPAIR", "CONTEXTS_WITH_MARK", "CONTEXTS_VECTOR", "CONTEXT",
  "CONTEXT_MARK", "REPLACE_ARROW", "REGEXP3", "REGEXP4",
  "RESTR_CONTEXTS_VECTOR", "RESTR_CONTEXT", "REGEXP5", "REGEXP6",
  "REGEXP7", "REGEXP8", "REGEXP9", "REGEXP10", "REGEXP11", "SYMBOL_LIST",
  "REGEXP12", "LABEL", "SYMBOL_OR_QUOTED", "HALFARC", "REGEXP_LIST",
  "FUNCTION", 0
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
     335,   336,   337,   338
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    86,    86,    86,    87,    87,    87,
      87,    87,    87,    88,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    96,    97,    97,    98,    98,    98,    98,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   101,   101,   102,   102,   102,   102,
     103,   103,   104,   104,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   107,   107,
     108,   108,   108,   108,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   115,   115,   116,
     116,   116,   116,   117,   117,   118
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     1,     3,     3,
       3,     9,     3,     4,     2,     2,     1,     1,     1,     3,
       1,     1,     2,     3,     1,     3,     5,     4,     4,     4,
       5,     4,     5,     2,     1,     3,     3,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     1,     3,     5,     5,
       1,     3,     3,     2,     2,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     3,
       1,     2,     2,     3,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     2,     1,
       3,     7,     5,     5,     5,     5,     4,     3,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     1,     3,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,   124,   127,     0,     0,     0,     0,     0,     0,   116,
     115,   114,   113,   112,   135,     0,     0,     0,     0,   130,
     131,   132,   121,   128,     0,     2,     6,     0,     7,    18,
      20,    21,    24,    17,    52,    56,    66,    74,    76,    80,
      86,    97,    99,   110,   129,   117,     0,     0,    98,     0,
      85,    84,     0,    82,    81,     0,     0,     0,     0,   120,
       1,     5,     0,     0,     0,     4,     0,     0,    49,    48,
      47,    46,    51,    45,    50,    44,     0,     0,    43,    42,
      41,    40,     0,    22,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
       0,     0,    88,    87,    92,    91,    90,    89,    96,    95,
      94,    93,   111,   119,     0,   134,     0,   125,     0,   123,
       0,    83,   100,   107,     0,     0,    10,     8,     9,    16,
      12,     0,   108,    14,     0,     0,     0,    25,     0,    19,
      23,    39,     0,    33,    34,    53,    55,    54,     0,    65,
       0,    57,    60,     0,    68,    73,    72,    71,    70,    69,
      67,    79,    78,    77,   122,     0,   118,     0,   126,     0,
      13,   106,     0,    29,     0,    15,   109,     0,    28,    31,
       0,    27,    38,    37,     0,     0,    64,    63,     0,     0,
       0,   133,   103,   102,     0,   104,    30,     0,    32,    26,
      36,    35,    59,    62,    61,    58,   105,     0,     0,   101,
       0,     0,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    66,   130,    28,    29,    30,
      31,    32,    83,   143,   144,    84,    76,    33,    34,   151,
     152,    35,    36,    37,    38,    39,    40,    41,   131,    42,
      43,    44,    45,   116,    46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -117
static const yytype_int16 yypact[] =
{
     182,   -69,  -117,    15,   -45,   504,   504,   136,   504,  -117,
    -117,  -117,  -117,  -117,  -117,   182,   182,   228,    11,  -117,
    -117,  -117,  -117,  -117,    24,  -117,    32,    11,   636,   -11,
    -117,   108,  -117,   -10,   158,   234,   504,   169,  -117,   593,
    -117,  -117,  -117,    27,  -117,   -58,   182,    80,  -117,   412,
    -117,  -117,   504,  -117,  -117,    35,    29,   636,   537,  -117,
    -117,  -117,   412,   412,   412,  -117,    99,   -28,  -117,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,   274,   412,  -117,  -117,
    -117,  -117,   412,  -117,   320,   504,   504,   504,   504,   458,
     504,   504,   504,   504,   504,   504,   504,   504,   169,   504,
     504,   504,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,  -117,  -117,  -117,   139,   215,   -23,  -117,   182,  -117,
     580,  -117,    14,  -117,   412,   636,   636,   636,   636,  -117,
    -117,   461,  -117,  -117,    11,   412,   366,   592,   636,  -117,
    -117,   412,   608,     4,  -117,   158,   158,   158,   341,   504,
     179,    10,  -117,   387,   504,   504,   504,   504,   504,   504,
     504,  -117,  -117,  -117,  -117,   182,  -117,   182,  -117,    47,
    -117,  -117,   159,   636,   412,  -117,  -117,    12,   636,   636,
     570,   412,   636,   412,   320,   504,   158,   504,   458,   504,
      57,   215,  -117,  -117,   182,  -117,   636,    11,   636,   636,
     636,  -117,   234,   158,  -117,   234,  -117,    92,   -22,  -117,
      11,    -7,  -117
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -117,  -117,  -117,   -14,  -117,  -117,  -117,   -13,  -117,   -19,
    -117,   -20,  -117,  -117,  -116,  -117,   -52,  -117,   -79,  -117,
    -114,   -75,   221,   -25,    20,  -117,    72,  -117,  -117,  -117,
    -117,  -117,   -18,  -117,  -117
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      59,    55,    56,    85,    58,   124,   145,   146,   147,    67,
     150,    98,    47,   148,   133,   153,   113,     2,   171,   167,
       1,     2,    49,   114,    60,    50,    51,    53,    54,   119,
      77,   112,   115,    86,    87,    61,   120,    62,    63,    64,
      62,    63,    64,    62,    63,    64,   184,   168,   132,   126,
     127,   128,   188,   134,   197,    62,    63,    64,   139,   210,
       3,   212,   140,   137,   138,    62,    63,    64,   201,   138,
     186,   142,   121,   174,   204,    48,     9,    10,    11,    12,
      13,    14,    15,     0,    16,   117,     2,    19,    20,    21,
      18,    19,    20,    21,    23,   172,   166,    22,    23,   123,
      62,    63,    64,   122,   169,     2,     0,     0,   203,   150,
     202,   173,    65,   176,   205,   192,   177,     0,     0,   161,
     162,   163,   178,   180,     0,   206,     0,   124,   182,    98,
      98,    98,    98,    98,    98,    98,    78,    79,    80,    81,
      52,     1,     2,     0,   164,     2,   174,   118,     0,     0,
      82,   190,     0,   191,   195,     0,    19,    20,    21,     0,
     209,   196,     0,    23,   193,     2,     0,   129,   199,     0,
     200,   142,    88,    89,    90,    19,    20,    21,     0,   208,
     207,     3,    23,     5,     6,     7,     8,     1,     2,     0,
       0,   187,   211,    88,    89,    90,     0,     9,    10,    11,
      12,    13,    14,    15,     0,    16,   165,    99,   100,   101,
       0,    18,    19,    20,    21,    19,    20,    21,    22,    23,
       0,     0,    23,    62,    63,    64,   194,     3,     4,     5,
       6,     7,     8,     1,     2,    19,    20,    21,     0,     0,
       0,    91,    23,     9,    10,    11,    12,    13,    14,    15,
       0,    16,     0,    17,     0,     0,     0,    18,    19,    20,
      21,     0,     0,     0,    22,    23,    92,    93,    94,    95,
      96,    97,     0,     3,     0,     5,     6,     7,     8,     1,
       2,     0,     0,     0,     0,   135,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,     0,    16,     0,    17,
      57,     0,     0,    18,    19,    20,    21,     0,     0,     0,
      22,    23,   154,   155,   156,   157,   158,   159,   160,     3,
       0,     5,     6,     7,     8,     1,     2,     0,     0,     0,
       0,     0,   141,     0,     0,     9,    10,    11,    12,    13,
      14,    15,     0,    16,     0,   136,     0,     0,    91,    18,
      19,    20,    21,   185,     0,     0,    22,    23,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     5,     6,     7,
       8,     1,     2,    92,    93,    94,    95,    96,    97,     0,
       0,     9,    10,    11,    12,    13,    14,    15,     0,    16,
       0,    17,     0,     0,    91,    18,    19,    20,    21,   189,
       0,     0,    22,    23,     0,     0,     0,     0,     0,     0,
       0,     3,     0,     5,     6,     7,     8,     1,     2,    92,
      93,    94,    95,    96,    97,     0,     0,     9,    10,    11,
      12,    13,    14,    15,     0,    16,     0,    17,   179,     0,
       0,    18,    19,    20,    21,     0,     0,     0,    22,    23,
       0,     0,     0,     0,     0,     0,     0,     3,     0,     5,
       6,     7,     8,     1,     2,     0,     0,     2,     0,     0,
     149,     0,     0,     9,    10,    11,    12,    13,    14,    15,
       0,    16,     0,    17,     0,     0,     0,    18,    19,    20,
      21,     0,     0,     0,    22,    23,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     5,     6,     7,     8,     1,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,    11,    12,    13,    14,    15,     0,    16,     0,   175,
       0,     0,     0,    18,    19,    20,    21,    19,    20,    21,
      22,    23,     0,     0,    23,     0,     0,     0,     0,     3,
       0,     5,     6,     7,     8,    68,    69,    70,    71,     0,
       0,    72,    73,    74,    75,     9,    10,    11,    12,    13,
      14,    15,     0,    16,     0,     0,     0,     0,     0,    18,
      19,    20,    21,     0,     0,     0,    22,    23,    68,    69,
      70,    71,     0,     0,    72,    73,    74,    75,    68,    69,
      70,    71,     0,   181,    72,    73,    74,    75,     0,   125,
      68,    69,    70,    71,     0,     0,    72,    73,    74,    75,
     183,     0,   170,     0,     0,     0,    68,    69,    70,    71,
       0,     0,    72,    73,    74,    75,     0,     0,     0,     0,
       0,     0,   198,     0,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,    68,    69,    70,    71,     0,     0,
      72,    73,    74,    75
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-117))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      18,    15,    16,    13,    17,    57,    85,    86,    87,    27,
      89,    36,    81,    88,    42,    90,    74,     6,     4,    42,
       5,     6,    67,    81,     0,     5,     6,     7,     8,    47,
      41,     4,    46,    43,    44,     3,    49,     8,     9,    10,
       8,     9,    10,     8,     9,    10,    42,    70,    66,    62,
      63,    64,    42,    81,    42,     8,     9,    10,    77,    81,
      45,    68,    82,    76,    77,     8,     9,    10,   184,    82,
     149,    84,    52,   125,   188,     3,    61,    62,    63,    64,
      65,    66,    67,    -1,    69,     5,     6,    76,    77,    78,
      75,    76,    77,    78,    83,    81,   114,    82,    83,    70,
       8,     9,    10,    68,   118,     6,    -1,    -1,   187,   188,
     185,   124,    80,   131,   189,    68,   134,    -1,    -1,    99,
     100,   101,   135,   136,    -1,    68,    -1,   179,   141,   154,
     155,   156,   157,   158,   159,   160,    28,    29,    30,    31,
       4,     5,     6,    -1,     5,     6,   198,    67,    -1,    -1,
      42,   165,    -1,   167,   172,    -1,    76,    77,    78,    -1,
      68,   174,    -1,    83,     5,     6,    -1,    68,   181,    -1,
     183,   184,    14,    15,    16,    76,    77,    78,    -1,   197,
     194,    45,    83,    47,    48,    49,    50,     5,     6,    -1,
      -1,    12,   210,    14,    15,    16,    -1,    61,    62,    63,
      64,    65,    66,    67,    -1,    69,    67,    38,    39,    40,
      -1,    75,    76,    77,    78,    76,    77,    78,    82,    83,
      -1,    -1,    83,     8,     9,    10,    67,    45,    46,    47,
      48,    49,    50,     5,     6,    76,    77,    78,    -1,    -1,
      -1,     7,    83,    61,    62,    63,    64,    65,    66,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    75,    76,    77,
      78,    -1,    -1,    -1,    82,    83,    32,    33,    34,    35,
      36,    37,    -1,    45,    -1,    47,    48,    49,    50,     5,
       6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    -1,    69,    -1,    71,
      72,    -1,    -1,    75,    76,    77,    78,    -1,    -1,    -1,
      82,    83,    91,    92,    93,    94,    95,    96,    97,    45,
      -1,    47,    48,    49,    50,     5,     6,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    -1,    69,    -1,    71,    -1,    -1,     7,    75,
      76,    77,    78,    12,    -1,    -1,    82,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,    49,
      50,     5,     6,    32,    33,    34,    35,    36,    37,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    -1,    69,
      -1,    71,    -1,    -1,     7,    75,    76,    77,    78,    12,
      -1,    -1,    82,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    47,    48,    49,    50,     5,     6,    32,
      33,    34,    35,    36,    37,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    -1,    69,    -1,    71,    72,    -1,
      -1,    75,    76,    77,    78,    -1,    -1,    -1,    82,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    47,
      48,    49,    50,     5,     6,    -1,    -1,     6,    -1,    -1,
      12,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      -1,    69,    -1,    71,    -1,    -1,    -1,    75,    76,    77,
      78,    -1,    -1,    -1,    82,    83,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    47,    48,    49,    50,     5,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    -1,    69,    -1,    68,
      -1,    -1,    -1,    75,    76,    77,    78,    76,    77,    78,
      82,    83,    -1,    -1,    83,    -1,    -1,    -1,    -1,    45,
      -1,    47,    48,    49,    50,    18,    19,    20,    21,    -1,
      -1,    24,    25,    26,    27,    61,    62,    63,    64,    65,
      66,    67,    -1,    69,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    -1,    -1,    -1,    82,    83,    18,    19,
      20,    21,    -1,    -1,    24,    25,    26,    27,    18,    19,
      20,    21,    -1,    11,    24,    25,    26,    27,    -1,    72,
      18,    19,    20,    21,    -1,    -1,    24,    25,    26,    27,
      12,    -1,    42,    -1,    -1,    -1,    18,    19,    20,    21,
      -1,    -1,    24,    25,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    18,    19,    20,    21,    -1,    -1,
      24,    25,    26,    27
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    45,    46,    47,    48,    49,    50,    61,
      62,    63,    64,    65,    66,    67,    69,    71,    75,    76,
      77,    78,    82,    83,    85,    86,    87,    88,    91,    92,
      93,    94,    95,   101,   102,   105,   106,   107,   108,   109,
     110,   111,   113,   114,   115,   116,   118,    81,   110,    67,
     108,   108,     4,   108,   108,    87,    87,    72,    91,   116,
       0,     3,     8,     9,    10,    80,    89,   116,    18,    19,
      20,    21,    24,    25,    26,    27,   100,    41,    28,    29,
      30,    31,    42,    96,    99,    13,    43,    44,    14,    15,
      16,     7,    32,    33,    34,    35,    36,    37,   107,    38,
      39,    40,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     4,    74,    81,    87,   117,     5,    67,   116,
      91,   108,    68,    70,   100,    72,    91,    91,    91,    68,
      90,   112,   116,    42,    81,    11,    71,    91,    91,    93,
      95,    12,    91,    97,    98,   102,   102,   102,   105,    12,
     102,   103,   104,   105,   106,   106,   106,   106,   106,   106,
     106,   108,   108,   108,     5,    67,   116,    42,    70,    87,
      42,     4,    81,    91,   100,    68,   116,   116,    91,    72,
      91,    11,    91,    12,    42,    12,   102,    12,    42,    12,
      87,    87,    68,     5,    67,   116,    91,    42,    72,    91,
      91,    98,   105,   102,   104,   105,    68,    87,   116,    68,
      81,   116,    68
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
      yyerror (scanner, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, scanner)
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
		  Type, Value, scanner); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void * scanner)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void * scanner;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void * scanner)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void * scanner;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, void * scanner)
#else
static void
yy_reduce_print (yyvsp, yyrule, scanner)
    YYSTYPE *yyvsp;
    int yyrule;
    void * scanner;
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
		       		       , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, scanner); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void * scanner)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, scanner)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    void * scanner;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (scanner);

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
int yyparse (void * scanner);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


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
yyparse (void * scanner)
#else
int
yyparse (scanner)
    void * scanner;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

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
#line 166 "xre_parse.yy"
    { }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 168 "xre_parse.yy"
    { 
       // only comments
       hfst::xre::contains_only_comments = true;
       return 0;
     }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 174 "xre_parse.yy"
    {
      // std::cerr << "regexp1:regexp2 end of expr \n"<< std::endl;
       // Symbols of form <foo> are not harmonized in xfst, that is why
       // they are escaped as @_<foo>_@ and need to be unescaped finally.  
       // hfst::xre::last_compiled = & hfst::xre::unescape_enclosing_angle_brackets($1)->minimize();
       hfst::xre::last_compiled = & (yyvsp[(1) - (2)].transducer)->minimize();
       (yyval.transducer) = hfst::xre::last_compiled;
       if (hfst::xre::allow_extra_text_at_end) {
         return 0;
       }
   }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 185 "xre_parse.yy"
    {
        //std::cerr << "regexp1:regexp2 end of weighted expr \n"<< std::endl; 
       // Symbols of form <foo> are not harmonized in xfst, that is why
       // they are escaped as @_<foo>_@ and need to be unescaped finally.  
        // hfst::xre::last_compiled = & hfst::xre::unescape_enclosing_angle_brackets($1)->minimize().set_final_weights($2, true);
        hfst::xre::last_compiled = & (yyvsp[(1) - (2)].transducer)->minimize().set_final_weights((yyvsp[(2) - (2)].weight), true);
        (yyval.transducer) = hfst::xre::last_compiled;
        if (hfst::xre::allow_extra_text_at_end) {
          return 0;
        }
   }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 196 "xre_parse.yy"
    {
   
        //std::cerr << "regexp1:regexp2\n"<< *$1 << std::endl; 
       // Symbols of form <foo> are not harmonized in xfst, that is why
       // they are escaped as @_<foo>_@ and need to be unescaped finally.  
        // hfst::xre::last_compiled = & hfst::xre::unescape_enclosing_angle_brackets($1)->minimize();
        hfst::xre::last_compiled = & (yyvsp[(1) - (1)].transducer)->minimize();
        (yyval.transducer) = hfst::xre::last_compiled;
   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 209 "xre_parse.yy"
    { 
            (yyval.transducer) = & (yyvsp[(1) - (1)].transducer)->minimize();
          //  std::cerr << "regexp2:replace \n"<< std::endl; 
         }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 214 "xre_parse.yy"
    {
        if ((yyvsp[(1) - (3)].transducer)->has_flag_diacritics() && (yyvsp[(3) - (3)].transducer)->has_flag_diacritics())
          {
            if (! harmonize_flags_) {
                 hfst::xre::warn("warning: both composition arguments contain flag diacritics that are not harmonized\n");
            }
            else {
                (yyvsp[(1) - (3)].transducer)->harmonize_flag_diacritics(*(yyvsp[(3) - (3)].transducer));
            }
          }

         try {
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->compose(*(yyvsp[(3) - (3)].transducer), harmonize_).minimize();
         }
         catch (const FlagDiacriticsAreNotIdentitiesException & e)
             {
               xreerror("Error: flag diacritics must be identities in composition if flag-is-epsilon is ON.\n"
               "I.e. only FLAG:FLAG is allowed, not FLAG1:FLAG2, FLAG:bar or foo:FLAG\n"
               "Apply twosided flag-diacritics (tfd) before composition.\n");
               YYABORT;
             }
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 237 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->cross_product(*(yyvsp[(3) - (3)].transducer));
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 241 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->lenient_composition(*(yyvsp[(3) - (3)].transducer)).minimize();
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 246 "xre_parse.yy"
    {
            (yyvsp[(1) - (9)].transducer)->substitute(StringPair((yyvsp[(2) - (9)].label),(yyvsp[(4) - (9)].label)), StringPair((yyvsp[(6) - (9)].label),(yyvsp[(8) - (9)].label)));
            (yyval.transducer) = (yyvsp[(1) - (9)].transducer);
       }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 250 "xre_parse.yy"
    {

            StringSet alpha = (yyvsp[(1) - (3)].transducer)->get_alphabet();
            if (hfst::xre::is_definition((yyvsp[(2) - (3)].label)))
            {
                hfst::xre::warn("warning: using definition as an ordinary label, cannot substitute\n");
                (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
            }
            else if (alpha.find((yyvsp[(2) - (3)].label)) == alpha.end())
            {
                (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
            }
            else
            {
                alpha = (yyvsp[(3) - (3)].transducer)->get_alphabet();

                StringPair tmp((yyvsp[(2) - (3)].label), (yyvsp[(2) - (3)].label));
                HfstTransducer * tmpTr = new HfstTransducer(*(yyvsp[(1) - (3)].transducer));

	        bool empty_replace_transducer=false;
	        HfstTransducer empty(hfst::xre::format);
	        if (empty.compare(*(yyvsp[(3) - (3)].transducer)))
	        {
                        empty_replace_transducer=true;
	        }	

	        if (empty_replace_transducer)
	        {
                        // substitute all transitions {b:a, a:b, b:b} with b:b
		        // as they will be removed anyway
		        hfst::xre::set_substitution_function_symbol((yyvsp[(2) - (3)].label));
		        tmpTr->substitute(&hfst::xre::substitution_function);
	        }	

                // `[ a:b, b, x y ]
                // substitute b with x | y
                tmpTr->substitute(tmp, *(yyvsp[(3) - (3)].transducer), false); // no harmonization

	        if (!empty_replace_transducer) 
                {
                        // a:b .o. b -> x | y
                        // [[a:b].i .o. b -> x | y].i - this is for cases when b is on left side

	                // build Replace transducer
                        HfstTransducerPair mappingPair(HfstTransducer((yyvsp[(2) - (3)].label), (yyvsp[(2) - (3)].label), hfst::xre::format), *(yyvsp[(3) - (3)].transducer));
                        HfstTransducerPairVector mappingPairVector;
                        mappingPairVector.push_back(mappingPair);
                        Rule rule(mappingPairVector);
                        HfstTransducer replaceTr(hfst::xre::format);
                        replaceTr = replace(rule, false);

                        tmpTr->compose(replaceTr).minimize();
                        tmpTr->invert().compose(replaceTr).invert();
	        }
            
                if (alpha.find((yyvsp[(2) - (3)].label)) == alpha.end())
                {
                  tmpTr->remove_from_alphabet((yyvsp[(2) - (3)].label));
                }
                tmpTr->minimize();
                (yyval.transducer) = tmpTr;
                delete((yyvsp[(1) - (3)].transducer), (yyvsp[(2) - (3)].label), (yyvsp[(3) - (3)].transducer));
            }
         }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 316 "xre_parse.yy"
    { (yyval.transducer) = (yyvsp[(3) - (4)].transducer); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 317 "xre_parse.yy"
    { (yyval.label) = (yyvsp[(1) - (2)].label); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 318 "xre_parse.yy"
    {  (yyval.transducer) = (yyvsp[(1) - (2)].transducer);  }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 320 "xre_parse.yy"
    { (yyval.transducer) = new HfstTransducer(hfst::xre::format); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 327 "xre_parse.yy"
    { }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 329 "xre_parse.yy"
    {
            switch ( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->first )
            {
               case E_REPLACE_RIGHT:
                 (yyval.transducer) = new HfstTransducer( replace( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second, false ) );
                 break;
               case E_OPTIONAL_REPLACE_RIGHT:
                 (yyval.transducer) = new HfstTransducer( replace( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second, true ) );
                 break;
              case E_REPLACE_LEFT:
                 (yyval.transducer) = new HfstTransducer( replace_left( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second, false ) );
                 break;
               case E_OPTIONAL_REPLACE_LEFT:
                 (yyval.transducer) = new HfstTransducer( replace_left( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second, true ) );
                 break;
               case E_RTL_LONGEST_MATCH:
                 (yyval.transducer) = new HfstTransducer( replace_rightmost_longest_match( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second ) );
                 break;
               case E_RTL_SHORTEST_MATCH:
                 (yyval.transducer) = new HfstTransducer( replace_rightmost_shortest_match((yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second) );
                 break;
               case E_LTR_LONGEST_MATCH:
                 (yyval.transducer) = new HfstTransducer( replace_leftmost_longest_match( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second ) );
                 break;
               case E_LTR_SHORTEST_MATCH:
                 (yyval.transducer) = new HfstTransducer( replace_leftmost_shortest_match( (yyvsp[(1) - (1)].replaceRuleVectorWithArrow)->second ) );
                 break;
               case E_REPLACE_RIGHT_MARKUP:
               default:
                xreerror("Unhandled arrow stuff I suppose");
                break;
            }
       
            delete (yyvsp[(1) - (1)].replaceRuleVectorWithArrow);
         }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 367 "xre_parse.yy"
    {
           //std::cerr << "parallel_rules: parallel_rules ,, rule"<< std::endl;      
           if ((yyvsp[(3) - (3)].replaceRuleWithArrow)->first != (yyvsp[(1) - (3)].replaceRuleVectorWithArrow)->first)
           {
             xreerror("Replace type mismatch in parallel rules");
             YYABORT;
           }
            Rule tmpRule((yyvsp[(3) - (3)].replaceRuleWithArrow)->second);
            (yyvsp[(1) - (3)].replaceRuleVectorWithArrow)->second.push_back(tmpRule);
            (yyval.replaceRuleVectorWithArrow) =  new std::pair< ReplaceArrow, std::vector<Rule> > ((yyvsp[(3) - (3)].replaceRuleWithArrow)->first, (yyvsp[(1) - (3)].replaceRuleVectorWithArrow)->second);
            delete (yyvsp[(3) - (3)].replaceRuleWithArrow);
         }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 380 "xre_parse.yy"
    {
         //std::cerr << "parallel_rules:rule"<< std::endl;        
            std::vector<Rule> * ruleVector = new std::vector<Rule>();
            ruleVector->push_back((yyvsp[(1) - (1)].replaceRuleWithArrow)->second);
            
            (yyval.replaceRuleVectorWithArrow) =  new std::pair< ReplaceArrow, std::vector<Rule> > ((yyvsp[(1) - (1)].replaceRuleWithArrow)->first, *ruleVector);
            delete (yyvsp[(1) - (1)].replaceRuleWithArrow);
         }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 391 "xre_parse.yy"
    {
         // std::cerr << "rule: mapping_vector"<< std::endl;      
        // HfstTransducer allMappingsDisjuncted = disjunctVectorMembers($1->second);
         
         Rule rule( (yyvsp[(1) - (1)].mappingVectorWithArrow)->second );;
         (yyval.replaceRuleWithArrow) =  new std::pair< ReplaceArrow, Rule> ((yyvsp[(1) - (1)].mappingVectorWithArrow)->first, rule);
         delete (yyvsp[(1) - (1)].mappingVectorWithArrow);
      }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 400 "xre_parse.yy"
    {
       //  std::cerr << "rule: mapping_vector contextsWM"<< std::endl;      
     //   HfstTransducer allMappingsDisjuncted = disjunctVectorMembers($1->second);
        
        Rule rule( (yyvsp[(1) - (2)].mappingVectorWithArrow)->second, (yyvsp[(2) - (2)].contextWithMark)->second, (yyvsp[(2) - (2)].contextWithMark)->first );
        (yyval.replaceRuleWithArrow) =  new std::pair< ReplaceArrow, Rule> ((yyvsp[(1) - (2)].mappingVectorWithArrow)->first, rule);
        delete (yyvsp[(1) - (2)].mappingVectorWithArrow), (yyvsp[(2) - (2)].contextWithMark);
      }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 412 "xre_parse.yy"
    {
        // std::cerr << "mapping_vector : mapping_vector comma mapping"<< std::endl;      
         // check if new Arrow is the same as the first one

         if ((yyvsp[(1) - (3)].mappingVectorWithArrow)->first != (yyvsp[(3) - (3)].mappingWithArrow)->first)
         {
            xreerror("Replace arrows should be the same. Calculated as if all replacements had the first arrow.");
            //exit(1);
         }
 
         (yyvsp[(1) - (3)].mappingVectorWithArrow)->second.push_back((yyvsp[(3) - (3)].mappingWithArrow)->second);
         (yyval.mappingVectorWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPairVector> ((yyvsp[(1) - (3)].mappingVectorWithArrow)->first, (yyvsp[(1) - (3)].mappingVectorWithArrow)->second);
         delete (yyvsp[(3) - (3)].mappingWithArrow); 
            
      }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 429 "xre_parse.yy"
    {
         // std::cerr << "mapping_vector : mapping"<< std::endl;      
         HfstTransducerPairVector * mappingPairVector = new HfstTransducerPairVector();
         mappingPairVector->push_back( (yyvsp[(1) - (1)].mappingWithArrow)->second );
         (yyval.mappingVectorWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPairVector> ((yyvsp[(1) - (1)].mappingWithArrow)->first, * mappingPairVector);
         delete (yyvsp[(1) - (1)].mappingWithArrow); 
      }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 441 "xre_parse.yy"
    {
	  hfst::xre::warn_about_special_symbols_in_replace((yyvsp[(1) - (3)].transducer));  
	  hfst::xre::warn_about_special_symbols_in_replace((yyvsp[(3) - (3)].transducer));  
          HfstTransducerPair mappingPair(*(yyvsp[(1) - (3)].transducer), *(yyvsp[(3) - (3)].transducer));
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (3)].replaceArrow), mappingPair);

          delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer);
      }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 450 "xre_parse.yy"
    {
          HfstTransducerPair marks(*(yyvsp[(3) - (5)].transducer), *(yyvsp[(5) - (5)].transducer));
          HfstTransducerPair tmpMappingPair(*(yyvsp[(1) - (5)].transducer), HfstTransducer(hfst::xre::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
          
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (5)].replaceArrow), mappingPair);
          delete (yyvsp[(1) - (5)].transducer), (yyvsp[(3) - (5)].transducer), (yyvsp[(5) - (5)].transducer);
      }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 459 "xre_parse.yy"
    {
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
          HfstTransducerPair marks(*(yyvsp[(3) - (4)].transducer), epsilon);
          HfstTransducerPair tmpMappingPair(*(yyvsp[(1) - (4)].transducer), HfstTransducer(hfst::xre::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
                   
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (4)].replaceArrow), mappingPair);
          delete (yyvsp[(1) - (4)].transducer), (yyvsp[(3) - (4)].transducer);
      }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 469 "xre_parse.yy"
    {
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
          HfstTransducerPair marks(epsilon, *(yyvsp[(4) - (4)].transducer));
          HfstTransducerPair tmpMappingPair(*(yyvsp[(1) - (4)].transducer), HfstTransducer(hfst::xre::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
          
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (4)].replaceArrow), mappingPair);
          delete (yyvsp[(1) - (4)].transducer), (yyvsp[(4) - (4)].transducer);
      }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 479 "xre_parse.yy"
    {
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
          //HfstTransducer mappingTr(epsilon);
          //mappingTr.cross_product(*$4);
          HfstTransducerPair mappingPair(epsilon, *(yyvsp[(4) - (4)].transducer));
          
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(3) - (4)].replaceArrow), mappingPair);
          delete (yyvsp[(4) - (4)].transducer);
      }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 489 "xre_parse.yy"
    {
	  HfstTransducerPair mappingPair(*(yyvsp[(2) - (5)].transducer), *(yyvsp[(5) - (5)].transducer));
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(4) - (5)].replaceArrow), mappingPair);
          delete (yyvsp[(2) - (5)].transducer), (yyvsp[(5) - (5)].transducer);
      }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 496 "xre_parse.yy"
    {
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
          HfstTransducerPair mappingPair(*(yyvsp[(1) - (4)].transducer), epsilon);
          
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (4)].replaceArrow), mappingPair);
          delete (yyvsp[(1) - (4)].transducer);
      }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 504 "xre_parse.yy"
    {
          HfstTransducerPair mappingPair(*(yyvsp[(1) - (5)].transducer), *(yyvsp[(4) - (5)].transducer));
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (5)].replaceArrow), mappingPair);
          delete (yyvsp[(1) - (5)].transducer), (yyvsp[(4) - (5)].transducer);
      }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 514 "xre_parse.yy"
    {       
         (yyval.contextWithMark) =  new std::pair< ReplaceType, HfstTransducerPairVector> ((yyvsp[(1) - (2)].replType), *(yyvsp[(2) - (2)].transducerPairVector));
         }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 519 "xre_parse.yy"
    {
            HfstTransducerPairVector * ContextVector = new HfstTransducerPairVector();
            ContextVector->push_back(*(yyvsp[(1) - (1)].transducerPair));
            (yyval.transducerPairVector) = ContextVector;
            delete (yyvsp[(1) - (1)].transducerPair); 
         }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 527 "xre_parse.yy"
    {
            (yyvsp[(1) - (3)].transducerPairVector)->push_back(*(yyvsp[(3) - (3)].transducerPair));
            (yyval.transducerPairVector) = (yyvsp[(1) - (3)].transducerPairVector);
            delete (yyvsp[(3) - (3)].transducerPair); 
         }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 535 "xre_parse.yy"
    {
             HfstTransducer t1(*(yyvsp[(1) - (3)].transducer));
             HfstTransducer t2(*(yyvsp[(3) - (3)].transducer));

             if (hfst::xre::is_weighted())
             {
               hfst::xre::has_weight_been_zeroed=false;
               t1.transform_weights(&hfst::xre::zero_weights);
             }
             t1.minimize().prune_alphabet(false);

             if (hfst::xre::is_weighted())
             {
               t2.transform_weights(&hfst::xre::zero_weights);
               hfst::xre::has_weight_been_zeroed=false;
             }
             t2.minimize().prune_alphabet(false);

            (yyval.transducerPair) = new HfstTransducerPair(t1, t2);
            delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer); 
         }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 557 "xre_parse.yy"
    {
            HfstTransducer t1(*(yyvsp[(1) - (2)].transducer));

            if (hfst::xre::is_weighted())
            {
              hfst::xre::has_weight_been_zeroed=false;
              t1.transform_weights(&hfst::xre::zero_weights);
              hfst::xre::has_weight_been_zeroed=false;
            }
            t1.minimize().prune_alphabet(false);

            HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);            
            (yyval.transducerPair) = new HfstTransducerPair(t1, epsilon);
            delete (yyvsp[(1) - (2)].transducer); 
         }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 573 "xre_parse.yy"
    {
            HfstTransducer t1(*(yyvsp[(2) - (2)].transducer));

            if (hfst::xre::is_weighted())
            {
              hfst::xre::has_weight_been_zeroed=false;
              t1.transform_weights(&hfst::xre::zero_weights);
              hfst::xre::has_weight_been_zeroed=false;
            }
            t1.minimize().prune_alphabet(false);
             
            HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
            (yyval.transducerPair) = new HfstTransducerPair(epsilon, t1);
            delete (yyvsp[(2) - (2)].transducer); 
         }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 589 "xre_parse.yy"
    {
            HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
            (yyval.transducerPair) = new HfstTransducerPair(epsilon, epsilon);
          }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 595 "xre_parse.yy"
    {
            (yyval.replType) = REPL_UP;
         }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 599 "xre_parse.yy"
    {
            (yyval.replType) = REPL_RIGHT;
         }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 603 "xre_parse.yy"
    {
            (yyval.replType) = REPL_LEFT;
         }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 607 "xre_parse.yy"
    {
            (yyval.replType) = REPL_DOWN;
         }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 613 "xre_parse.yy"
    {
            (yyval.replaceArrow) = E_REPLACE_RIGHT;
         }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 617 "xre_parse.yy"
    {
            (yyval.replaceArrow) = E_OPTIONAL_REPLACE_RIGHT;
         }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 621 "xre_parse.yy"
    {
            (yyval.replaceArrow) = E_RTL_LONGEST_MATCH;
         }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 625 "xre_parse.yy"
    {
            (yyval.replaceArrow) = E_RTL_SHORTEST_MATCH;
         }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 629 "xre_parse.yy"
    {
            (yyval.replaceArrow) = E_LTR_LONGEST_MATCH;
         }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 633 "xre_parse.yy"
    {
            (yyval.replaceArrow) = E_LTR_SHORTEST_MATCH;
         }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 637 "xre_parse.yy"
    {
        	 (yyval.replaceArrow) =  E_REPLACE_LEFT;
         }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 641 "xre_parse.yy"
    {
        	 (yyval.replaceArrow) = E_OPTIONAL_REPLACE_LEFT;
         }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 647 "xre_parse.yy"
    { }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 648 "xre_parse.yy"
    {
            xreerror("No shuffle");
            (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 653 "xre_parse.yy"
    {
            (yyval.transducer) = new HfstTransducer( before (*(yyvsp[(1) - (3)].transducer), *(yyvsp[(3) - (3)].transducer)) );
            delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 657 "xre_parse.yy"
    {
            (yyval.transducer) = new HfstTransducer( after (*(yyvsp[(1) - (3)].transducer), *(yyvsp[(3) - (3)].transducer)) );
            delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 664 "xre_parse.yy"
    { }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 666 "xre_parse.yy"
    {
            (yyval.transducer) = new HfstTransducer( restriction(*(yyvsp[(1) - (3)].transducer), *(yyvsp[(3) - (3)].transducerPairVector)) ) ;
            delete (yyvsp[(1) - (3)].transducer);
            delete (yyvsp[(3) - (3)].transducerPairVector);
        }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 672 "xre_parse.yy"
    {
            xreerror("No Arrows");
            (yyval.transducer) = (yyvsp[(1) - (5)].transducer);
            delete (yyvsp[(3) - (5)].transducer);
            delete (yyvsp[(5) - (5)].transducer);
        }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 679 "xre_parse.yy"
    {
            xreerror("No Arrows");
            (yyval.transducer) = (yyvsp[(1) - (5)].transducer);
            delete (yyvsp[(3) - (5)].transducer);
            delete (yyvsp[(5) - (5)].transducer);
        }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 688 "xre_parse.yy"
    {
            HfstTransducerPairVector * ContextVector = new HfstTransducerPairVector();
            ContextVector->push_back(*(yyvsp[(1) - (1)].transducerPair));
            (yyval.transducerPairVector) = ContextVector;
            delete (yyvsp[(1) - (1)].transducerPair); 
         }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 696 "xre_parse.yy"
    {
            (yyvsp[(1) - (3)].transducerPairVector)->push_back(*(yyvsp[(3) - (3)].transducerPair));
            (yyval.transducerPairVector) = (yyvsp[(1) - (3)].transducerPairVector);
            delete (yyvsp[(3) - (3)].transducerPair); 
         }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 705 "xre_parse.yy"
    {
            (yyval.transducerPair) = new HfstTransducerPair(*(yyvsp[(1) - (3)].transducer), *(yyvsp[(3) - (3)].transducer));
            delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer); 
         }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 710 "xre_parse.yy"
    {
           // std::cerr << "Mapping: \n" << *$1  << std::endl;
            
            HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
            
           // std::cerr << "Epsilon: \n" << epsilon  << std::endl;
            (yyval.transducerPair) = new HfstTransducerPair(*(yyvsp[(1) - (2)].transducer), epsilon);
            delete (yyvsp[(1) - (2)].transducer); 
         }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 720 "xre_parse.yy"
    {
            HfstTransducer epsilon(hfst::internal_epsilon, hfst::xre::format);
            (yyval.transducerPair) = new HfstTransducerPair(epsilon, *(yyvsp[(2) - (2)].transducer));
            delete (yyvsp[(2) - (2)].transducer); 
         }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 726 "xre_parse.yy"
    {
            HfstTransducer empty(hfst::xre::format);
            (yyval.transducerPair) = new HfstTransducerPair(empty, empty);
         }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 733 "xre_parse.yy"
    { }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 734 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->disjunct(*(yyvsp[(3) - (3)].transducer), harmonize_);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 738 "xre_parse.yy"
    {
        // std::cerr << "Intersection: \n"  << std::endl;
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->intersect(*(yyvsp[(3) - (3)].transducer), harmonize_).minimize().prune_alphabet(false);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 743 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->subtract(*(yyvsp[(3) - (3)].transducer), harmonize_).prune_alphabet(false);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 747 "xre_parse.yy"
    {
            xreerror("No upper minus");
            (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 752 "xre_parse.yy"
    {
            xreerror("No lower minus");
            (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 757 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->priority_union(*(yyvsp[(3) - (3)].transducer));
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 761 "xre_parse.yy"
    {
            HfstTransducer* left = new HfstTransducer(*(yyvsp[(1) - (3)].transducer));
            HfstTransducer* right =  new HfstTransducer(*(yyvsp[(3) - (3)].transducer));
            right->invert();
            left->invert();
            (yyval.transducer) = & (left->priority_union(*right).invert());
            delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 771 "xre_parse.yy"
    { }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 772 "xre_parse.yy"
    { 
        (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->concatenate(*(yyvsp[(2) - (2)].transducer), harmonize_);
        delete (yyvsp[(2) - (2)].transducer);
        }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 778 "xre_parse.yy"
    { }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 779 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->insert_freely(*(yyvsp[(3) - (3)].transducer), false); // no harmonization
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 783 "xre_parse.yy"
    {
            xreerror("No ignoring internally");
            (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 788 "xre_parse.yy"
    {
            xreerror("No left quotient");
            (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 795 "xre_parse.yy"
    { }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 796 "xre_parse.yy"
    {
       		// TODO: forbid pair complement (ie ~a:b)
       		HfstTransducer complement = HfstTransducer::identity_pair( hfst::xre::format );
       		complement.repeat_star().minimize();
       		complement.subtract(*(yyvsp[(2) - (2)].transducer)).prune_alphabet(false);
       		(yyval.transducer) = new HfstTransducer(complement);
   			delete (yyvsp[(2) - (2)].transducer);
        }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 804 "xre_parse.yy"
    {
            // std::cerr << "Containment: \n" << std::endl;
            if (hfst::xre::has_non_identity_pairs((yyvsp[(2) - (2)].transducer))) // if non-identity symbols present..
            {
              hfst::xre::warn("warning: using transducer that is non an automaton in containment\n");
              (yyval.transducer) = hfst::xre::contains((yyvsp[(2) - (2)].transducer)); // ..resort to simple containment
            }
            else
            {
              (yyval.transducer) = hfst::xre::contains_with_weight((yyvsp[(2) - (2)].transducer), 0);
            }
            delete (yyvsp[(2) - (2)].transducer);
        }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 817 "xre_parse.yy"
    {
            // std::cerr << "Containment: \n" << std::endl;
            if (hfst::xre::has_non_identity_pairs((yyvsp[(3) - (3)].transducer))) // if non-identity symbols present..
            {
              xreerror("Containment with weight only works with automata");
              YYABORT;
            }
            (yyval.transducer) = hfst::xre::contains_with_weight((yyvsp[(3) - (3)].transducer), (yyvsp[(2) - (3)].weight));
            delete (yyvsp[(3) - (3)].transducer);
        }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 827 "xre_parse.yy"
    {
            //std::cerr << "Contain 1 \n"<< std::endl;

            (yyval.transducer) = hfst::xre::contains_once((yyvsp[(2) - (2)].transducer));
            delete (yyvsp[(2) - (2)].transducer);
        }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 833 "xre_parse.yy"
    {
            (yyval.transducer) = hfst::xre::contains_once_optional((yyvsp[(2) - (2)].transducer));
            delete (yyvsp[(2) - (2)].transducer);
        }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 839 "xre_parse.yy"
    { }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 840 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_star();
        }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 843 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_plus();
        }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 846 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->reverse();
        }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 849 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->invert();
        }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 852 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->input_project();
        }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 855 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->output_project();
        }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 858 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n((yyvsp[(2) - (2)].value));
        }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 861 "xre_parse.yy"
    {
            //std::cerr << "value is ::::: \n"<< $2 << std::endl; 
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n_plus((yyvsp[(2) - (2)].value)+1);
        }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 865 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n_minus((yyvsp[(2) - (2)].value)-1);
        }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 868 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n_to_k((yyvsp[(2) - (2)].values)[0], (yyvsp[(2) - (2)].values)[1]);
            free((yyvsp[(2) - (2)].values));
        }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 874 "xre_parse.yy"
    { }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 875 "xre_parse.yy"
    {
            HfstTransducer* any = new HfstTransducer(hfst::internal_identity,
                                        hfst::xre::format);
            (yyval.transducer) = & ( any->subtract(*(yyvsp[(2) - (2)].transducer)));
            delete (yyvsp[(2) - (2)].transducer);
        }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 889 "xre_parse.yy"
    { }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 890 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(2) - (3)].transducer)->minimize();
        }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 894 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(2) - (7)].transducer)->cross_product(*(yyvsp[(6) - (7)].transducer));
            delete (yyvsp[(6) - (7)].transducer);
        }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 899 "xre_parse.yy"
    {
     	    HfstTransducer * tmp = hfst::xre::xfst_curly_label_to_transducer((yyvsp[(5) - (5)].label),(yyvsp[(5) - (5)].label));
            free((yyvsp[(5) - (5)].label));
            (yyval.transducer) = & (yyvsp[(2) - (5)].transducer)->cross_product(*tmp);
            delete tmp;
        }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 906 "xre_parse.yy"
    {
     	    HfstTransducer * tmp = hfst::xre::xfst_curly_label_to_transducer((yyvsp[(1) - (5)].label),(yyvsp[(1) - (5)].label));
            free((yyvsp[(1) - (5)].label));
            (yyval.transducer) = & (yyvsp[(4) - (5)].transducer)->cross_product(*tmp);
            delete tmp;
        }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 913 "xre_parse.yy"
    {
            HfstTransducer * tmp = hfst::xre::expand_definition((yyvsp[(5) - (5)].label));
            free((yyvsp[(5) - (5)].label));
            (yyval.transducer) = & (yyvsp[(2) - (5)].transducer)->cross_product(*tmp);
            delete tmp;
        }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 920 "xre_parse.yy"
    {
            (yyval.transducer) = hfst::xre::expand_definition((yyvsp[(1) - (5)].label));
            free((yyvsp[(1) - (5)].label));
            (yyval.transducer) = & (yyval.transducer)->cross_product(*(yyvsp[(4) - (5)].transducer));
            delete (yyvsp[(4) - (5)].transducer);
        }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 926 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(2) - (4)].transducer)->set_final_weights((yyvsp[(4) - (4)].weight), true).minimize();
        }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 929 "xre_parse.yy"
    {
            (yyval.transducer) = & (yyvsp[(2) - (3)].transducer)->optionalize();
        }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 935 "xre_parse.yy"
    {
            if (strcmp((yyvsp[(1) - (1)].label), hfst::internal_unknown.c_str()) == 0)
              {
                (yyval.transducer) = new HfstTransducer(hfst::internal_identity, hfst::xre::format);
              }
            else
              {
                (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (1)].label), (yyvsp[(1) - (1)].label), hfst::xre::format);
              }
            free((yyvsp[(1) - (1)].label));
        }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 946 "xre_parse.yy"
    {
            HfstTransducer * tmp ;
            if (strcmp((yyvsp[(2) - (2)].label), hfst::internal_unknown.c_str()) == 0)
              {
                 tmp = new HfstTransducer(hfst::internal_identity, hfst::xre::format);
              }
            else
              {
                 tmp = new HfstTransducer((yyvsp[(2) - (2)].label), (yyvsp[(2) - (2)].label), hfst::xre::format);
              }

            (yyvsp[(1) - (2)].transducer)->disjunct(*tmp, false); // do not harmonize
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->minimize();
            delete (yyvsp[(2) - (2)].label), tmp; 
            }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 963 "xre_parse.yy"
    { }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 964 "xre_parse.yy"
    { 
            (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->set_final_weights((yyvsp[(2) - (2)].weight), true);
        }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 967 "xre_parse.yy"
    {
            try {
              hfst::HfstInputStream instream((yyvsp[(1) - (1)].label));
              (yyval.transducer) = new HfstTransducer(instream);
              instream.close();
              free((yyvsp[(1) - (1)].label));
            }
            catch (const HfstException & e) {
              (void) e; // todo handle the exception
              char msg [256];
              sprintf(msg, "Error reading transducer file '%s'.", (yyvsp[(1) - (1)].label));
              xreerror(msg);
              YYABORT;
            }
        }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 982 "xre_parse.yy"
    {
            FILE * f = NULL;
            f = fopen((yyvsp[(1) - (1)].label), "r");
            if (f == NULL) {
              xreerror("File cannot be opened.\n");
              YYABORT;
            }
            else {
              HfstBasicTransducer tmp;
              HfstTokenizer tok;
              char line [1000];

              while( fgets(line, 1000, f) != NULL )
              {
                hfst::xre::strip_newline(line);
                StringPairVector spv = tok.tokenize(line);
                tmp.disjunct(spv, 0);
              }
              fclose(f);
              HfstTransducer * retval = new HfstTransducer(tmp, hfst::xre::format); 
              retval->minimize();
              (yyval.transducer) = retval;
            }
        }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1006 "xre_parse.yy"
    {
            FILE * f = NULL;
            f = fopen((yyvsp[(1) - (1)].label), "r");
            if (f == NULL) {
              xreerror("File cannot be opened.\n");
              YYABORT;
            }
            else {
              HfstTokenizer tok;
              HfstBasicTransducer tmp;
              char line [1000];

              while( fgets(line, 1000, f) != NULL )
              {
                hfst::xre::strip_newline(line);
                StringPairVector spv = HfstTokenizer::tokenize_space_separated(line);
                tmp.disjunct(spv, 0);
              }
              fclose(f);
              HfstTransducer * retval = new HfstTransducer(tmp, hfst::xre::format); 
              retval->minimize();
              (yyval.transducer) = retval;
            }
        }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 1030 "xre_parse.yy"
    {
            FILE * f = NULL;
            f = fopen((yyvsp[(1) - (1)].label), "r");
            if (f == NULL) {
              xreerror("File cannot be opened.\n");
              YYABORT;
            }
            else {
              try {
                unsigned int linecount = 0;
                HfstBasicTransducer tmp = HfstBasicTransducer::read_in_prolog_format(f, linecount);
                fclose(f);
                HfstTransducer * retval = new HfstTransducer(tmp, hfst::xre::format);
                retval->minimize();
                (yyval.transducer) = retval;
              }
              catch (const HfstException & e) {
                (void) e; // todo handle the exception
                fclose(f);
                xreerror("Error reading prolog file.\n");
                YYABORT;
              }
            }
        }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 1054 "xre_parse.yy"
    {
            FILE * f = NULL;
            f = fopen((yyvsp[(1) - (1)].label), "r");
            if (f == NULL) {
              xreerror("File cannot be opened.\n");
              fclose(f);
              YYABORT;
            }
            else {
              fclose(f);
              // read the regex in a string
              std::ifstream ifs((yyvsp[(1) - (1)].label));
              std::stringstream buffer;
              buffer << ifs.rdbuf();
              char * regex_string = strdup(buffer.str().c_str());

              // create a new scanner for evaluating the regex
              yyscan_t scanner;
              xrelex_init(&scanner);
              YY_BUFFER_STATE bs = xre_scan_string(regex_string, scanner);

              unsigned int chars_read = hfst::xre::cr;
              hfst::xre::cr = 0;

              int parse_retval = xreparse(scanner);

              xre_delete_buffer(bs,scanner);
              xrelex_destroy(scanner);

              free(regex_string);

              hfst::xre::cr = chars_read;

              (yyval.transducer) = hfst::xre::last_compiled;

              if (parse_retval != 0)
              {
                xreerror("Error parsing regex.\n");
                YYABORT;
              }
            }
        }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 1098 "xre_parse.yy"
    {
        if (strcmp((yyvsp[(1) - (1)].label), hfst::internal_unknown.c_str()) == 0)
          {
            (yyval.transducer) = new HfstTransducer(hfst::internal_identity, hfst::xre::format);
          }
        else
          {
            // HfstTransducer * tmp = new HfstTransducer($1, hfst::xre::format);
	    // $$ = hfst::xre::expand_definition(tmp, $1);
            (yyval.transducer) = hfst::xre::expand_definition((yyvsp[(1) - (1)].label));
          }
        free((yyvsp[(1) - (1)].label));
     }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1112 "xre_parse.yy"
    {
     	(yyval.transducer) = hfst::xre::xfst_label_to_transducer((yyvsp[(1) - (3)].label),(yyvsp[(3) - (3)].label));
        free((yyvsp[(1) - (3)].label));
        free((yyvsp[(3) - (3)].label));
     }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1117 "xre_parse.yy"
    {
        (yyval.transducer) = hfst::xre::xfst_label_to_transducer((yyvsp[(1) - (2)].label),hfst::internal_unknown.c_str());
        /*$$ = new HfstTransducer($1, hfst::internal_unknown, hfst::xre::format);*/
        free((yyvsp[(1) - (2)].label));
     }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 1122 "xre_parse.yy"
    {
        (yyval.transducer) = hfst::xre::xfst_label_to_transducer(hfst::internal_unknown.c_str(),(yyvsp[(2) - (2)].label));
        free((yyvsp[(2) - (2)].label));
     }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 1126 "xre_parse.yy"
    {
	(yyval.transducer) = hfst::xre::xfst_label_to_transducer(hfst::internal_unknown.c_str(), hfst::internal_unknown.c_str());
     }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1129 "xre_parse.yy"
    {
        (yyval.transducer) = hfst::xre::xfst_label_to_transducer((yyvsp[(1) - (3)].label),(yyvsp[(1) - (3)].label));
        free((yyvsp[(1) - (3)].label));
        HfstTransducer * tmp = hfst::xre::xfst_curly_label_to_transducer((yyvsp[(3) - (3)].label),(yyvsp[(3) - (3)].label));
        free((yyvsp[(3) - (3)].label));
        (yyval.transducer) = & (yyval.transducer)->cross_product(*tmp);
        delete tmp;
     }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 1137 "xre_parse.yy"
    {
        HfstTransducer * tmp = hfst::xre::xfst_label_to_transducer((yyvsp[(3) - (3)].label),(yyvsp[(3) - (3)].label));
        free((yyvsp[(3) - (3)].label));
        (yyval.transducer) = hfst::xre::xfst_curly_label_to_transducer((yyvsp[(1) - (3)].label),(yyvsp[(1) - (3)].label));
        free((yyvsp[(1) - (3)].label));
        (yyval.transducer) = & (yyval.transducer)->cross_product(*tmp);
        delete tmp;
     }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1145 "xre_parse.yy"
    {
     	(yyval.transducer) = hfst::xre::xfst_curly_label_to_transducer((yyvsp[(1) - (1)].label),(yyvsp[(1) - (1)].label));
        free((yyvsp[(1) - (1)].label));
     }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1149 "xre_parse.yy"
    {
     	(yyval.transducer) = hfst::xre::xfst_curly_label_to_transducer((yyvsp[(1) - (3)].label),(yyvsp[(3) - (3)].label));
        free((yyvsp[(1) - (3)].label));
	free((yyvsp[(3) - (3)].label));
     }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1155 "xre_parse.yy"
    {
            if (! hfst::xre::is_valid_function_call((yyvsp[(1) - (3)].label), (yyvsp[(2) - (3)].transducerVector))) {
              return EXIT_FAILURE;
            }
            else {
              // create a new scanner for evaluating the function
              yyscan_t scanner;
              xrelex_init(&scanner);
              YY_BUFFER_STATE bs = xre_scan_string(hfst::xre::get_function_xre((yyvsp[(1) - (3)].label)),scanner);

              // define special variables so that function arguments get the values given in regexp list
              hfst::xre::define_function_args((yyvsp[(1) - (3)].label), (yyvsp[(2) - (3)].transducerVector));

              // if we are scanning a function definition for argument symbols, 
              // do not include the characters read when evaluating functions inside it 
              unsigned int chars_read = hfst::xre::cr;

              int parse_retval = xreparse(scanner);

              hfst::xre::cr = chars_read;
              hfst::xre::undefine_function_args((yyvsp[(1) - (3)].label));

              xre_delete_buffer(bs,scanner);
              xrelex_destroy(scanner);

              (yyval.transducer) = hfst::xre::last_compiled;

              if (parse_retval != 0)
              {
                YYABORT;
              }
            }
        }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1202 "xre_parse.yy"
    {
       // Symbols of form <foo> are not harmonized in xfst, that is why
       // they need to be escaped as @_<foo>_@.
       // $$ = hfst::xre::escape_enclosing_angle_brackets($1); 
       hfst::xre::warn_about_hfst_special_symbol((yyvsp[(1) - (1)].label));
       hfst::xre::warn_about_xfst_special_symbol((yyvsp[(1) - (1)].label));
       (yyval.label) = (yyvsp[(1) - (1)].label); 
     }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1210 "xre_parse.yy"
    {
        (yyval.label) = strdup(hfst::internal_epsilon.c_str());
     }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1213 "xre_parse.yy"
    {
        (yyval.label) = strdup(hfst::internal_unknown.c_str());
     }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1216 "xre_parse.yy"
    {
        (yyval.label) = strdup("@#@");
     }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1221 "xre_parse.yy"
    { 
       (yyval.transducerVector)->push_back(*((yyvsp[(3) - (3)].transducer)));
       delete (yyvsp[(3) - (3)].transducer); 
     }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 1225 "xre_parse.yy"
    { 
       (yyval.transducerVector) = new hfst::HfstTransducerVector();
       (yyval.transducerVector)->push_back(*((yyvsp[(1) - (1)].transducer))); 
       delete (yyvsp[(1) - (1)].transducer);
     }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 1232 "xre_parse.yy"
    {
        (yyval.label) = strdup((yyvsp[(1) - (1)].label));
    }
    break;



/* Line 1806 of yacc.c  */
#line 3652 "xre_parse.cc"
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
      yyerror (scanner, YY_("syntax error"));
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
        yyerror (scanner, yymsgp);
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
		      yytoken, &yylval, scanner);
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
		  yystos[yystate], yyvsp, scanner);
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
  yyerror (scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, scanner);
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
#line 1236 "xre_parse.yy"



