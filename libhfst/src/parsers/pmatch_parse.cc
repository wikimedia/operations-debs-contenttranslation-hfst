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

/* Substitute the variable and function names.  */
#define yyparse         pmatchparse
#define yylex           pmatchlex
#define yyerror         pmatcherror
#define yylval          pmatchlval
#define yychar          pmatchchar
#define yydebug         pmatchdebug
#define yynerrs         pmatchnerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "pmatch_parse.yy"


#define YYDEBUG 0

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <sstream>
    
#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstXeroxRules.h"

    using namespace hfst;
    using hfst::HfstTransducer;
    using namespace hfst::xeroxRules;
    using namespace hfst::implementations;

#include "pmatch_utils.h"
    using hfst::pmatch::PmatchAstNode;
    
    extern void pmatcherror(const char * text);
    extern int pmatchlex();
    extern int pmatchlineno;

    

/* Line 268 of yacc.c  */
#line 107 "pmatch_parse.cc"

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

/* Line 293 of yacc.c  */
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
    
     
     


/* Line 293 of yacc.c  */
#line 391 "pmatch_parse.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 403 "pmatch_parse.cc"

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
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   914

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  108
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  219
/* YYNRULES -- Number of states.  */
#define YYNSTATES  349

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   362

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
     105,   106,   107
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    23,
      29,    31,    32,    34,    38,    41,    44,    46,    50,    54,
      58,    61,    64,    67,    70,    72,    76,    80,    84,    86,
      89,    91,    95,    99,   101,   103,   105,   107,   109,   111,
     113,   115,   117,   119,   121,   124,   127,   130,   133,   136,
     139,   142,   145,   148,   151,   153,   155,   157,   161,   165,
     167,   169,   171,   173,   175,   177,   181,   185,   189,   191,
     193,   195,   199,   201,   204,   208,   210,   214,   220,   225,
     230,   235,   241,   244,   246,   250,   254,   257,   260,   262,
     264,   266,   268,   270,   272,   274,   276,   278,   280,   282,
     286,   290,   294,   296,   302,   308,   314,   316,   320,   324,
     328,   332,   336,   340,   344,   346,   349,   351,   355,   359,
     363,   365,   368,   371,   374,   377,   379,   382,   385,   388,
     391,   394,   397,   400,   403,   406,   409,   411,   414,   422,
     424,   427,   431,   435,   437,   439,   441,   443,   445,   447,
     449,   451,   453,   455,   457,   461,   465,   469,   473,   477,
     481,   483,   485,   487,   489,   491,   493,   495,   499,   503,
     507,   511,   514,   517,   520,   523,   525,   527,   529,   531,
     533,   537,   541,   545,   547,   549,   551,   555,   559,   561,
     563,   565,   567,   569,   571,   573,   575,   577,   579,   583,
     587,   589,   593,   597,   599,   603,   604,   606,   608,   610,
     616,   620,   624,   628,   632,   636,   640,   644,   648,   652
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     109,     0,    -1,   110,    -1,   109,   110,    -1,   107,   111,
      -1,   105,   111,    -1,   106,   115,    -1,   104,   112,    -1,
       6,   115,    -1,     5,   113,    72,   116,    75,    -1,   114,
      -1,    -1,     6,    -1,     6,    44,   114,    -1,   123,    75,
      -1,   123,     3,    -1,   117,    -1,   116,    11,   117,    -1,
     116,    12,   117,    -1,   116,    10,   117,    -1,   116,   167,
      -1,   116,   169,    -1,   116,   168,    -1,   116,   170,    -1,
     118,    -1,   117,    39,   118,    -1,   117,     9,   118,    -1,
     117,    38,   118,    -1,   119,    -1,   118,   119,    -1,   120,
      -1,    69,   116,    70,    -1,    71,   116,    72,    -1,   103,
      -1,   102,    -1,   101,    -1,   100,    -1,    99,    -1,    98,
      -1,   161,    -1,   146,    -1,   148,    -1,   147,    -1,   121,
      -1,   120,    54,    -1,   120,    53,    -1,   120,    58,    -1,
     120,    57,    -1,   120,    56,    -1,   120,    55,    -1,   120,
      62,    -1,   120,    61,    -1,   120,    60,    -1,   120,    59,
      -1,   122,    -1,     6,    -1,    82,    -1,    92,     6,    72,
      -1,    92,     8,    72,    -1,    68,    -1,    67,    -1,    63,
      -1,   151,    -1,     7,    -1,   124,    -1,   123,    11,   124,
      -1,   123,    12,   124,    -1,   123,    10,   124,    -1,   134,
      -1,   125,    -1,   126,    -1,   125,    43,   126,    -1,   127,
      -1,   127,   129,    -1,   127,    44,   128,    -1,   128,    -1,
     124,   133,   124,    -1,   124,   133,   124,    13,   124,    -1,
     124,   133,   124,    13,    -1,   124,   133,    13,   124,    -1,
      73,    74,   133,   124,    -1,    73,   124,    74,   133,   124,
      -1,   132,   130,    -1,   131,    -1,   130,    44,   131,    -1,
     124,    14,   124,    -1,   124,    14,    -1,    14,   124,    -1,
      33,    -1,    32,    -1,    31,    -1,    30,    -1,    29,    -1,
      27,    -1,    23,    -1,    22,    -1,    21,    -1,    20,    -1,
     135,    -1,   134,    15,   135,    -1,   134,    46,   135,    -1,
     134,    45,   135,    -1,   136,    -1,   135,    18,   136,    14,
     136,    -1,   135,    17,   136,    14,   136,    -1,   135,    16,
     136,    14,   136,    -1,   137,    -1,   136,    39,   137,    -1,
     136,     9,   137,    -1,   136,    38,   137,    -1,   136,    37,
     137,    -1,   136,    36,   137,    -1,   136,    35,   137,    -1,
     136,    34,   137,    -1,   138,    -1,   137,   138,    -1,   139,
      -1,   138,    42,   139,    -1,   138,    41,   139,    -1,   138,
      40,   139,    -1,   140,    -1,    52,   139,    -1,    51,   139,
      -1,    50,   139,    -1,    49,   139,    -1,   141,    -1,   140,
      54,    -1,   140,    53,    -1,   140,    58,    -1,   140,    57,
      -1,   140,    56,    -1,   140,    55,    -1,   140,    62,    -1,
     140,    61,    -1,   140,    60,    -1,   140,    59,    -1,   142,
      -1,    47,   141,    -1,    48,   141,    44,   141,    44,   141,
      70,    -1,   149,    -1,   142,     4,    -1,    69,   123,    70,
      -1,    71,   123,    72,    -1,   103,    -1,   102,    -1,   101,
      -1,   100,    -1,    99,    -1,    98,    -1,   161,    -1,   162,
      -1,   143,    -1,   145,    -1,   144,    -1,    97,   142,    72,
      -1,    96,   142,    72,    -1,    95,   142,    72,    -1,    97,
     119,    72,    -1,    96,   119,    72,    -1,    95,   119,    72,
      -1,   150,    -1,    68,    -1,    67,    -1,    66,    -1,    65,
      -1,    64,    -1,    63,    -1,   151,    76,   151,    -1,    81,
      76,    81,    -1,   151,    76,    81,    -1,    81,    76,   151,
      -1,   151,    78,    -1,    81,    78,    -1,    79,   151,    -1,
      79,    81,    -1,     6,    -1,    77,    -1,   151,    -1,    81,
      -1,     7,    -1,     7,    76,     7,    -1,   151,    76,     7,
      -1,     7,    76,   151,    -1,   157,    -1,   160,    -1,   152,
      -1,    92,     6,    72,    -1,    92,     8,    72,    -1,     8,
      -1,    80,    -1,    82,    -1,   153,    -1,   154,    -1,   155,
      -1,   163,    -1,   164,    -1,   165,    -1,   166,    -1,    85,
     156,    72,    -1,    84,   156,    72,    -1,   152,    -1,   152,
      44,   156,    -1,     5,   158,    72,    -1,   159,    -1,   159,
      44,   158,    -1,    -1,     6,    -1,     7,    -1,     8,    -1,
      87,     6,    44,    67,    72,    -1,    94,     6,    72,    -1,
      93,   124,    72,    -1,    90,   124,    72,    -1,    88,   124,
      72,    -1,    91,   124,    72,    -1,    89,   124,    72,    -1,
      90,   117,    72,    -1,    88,   117,    72,    -1,    91,   117,
      72,    -1,    89,   117,    72,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   151,   151,   172,   195,   196,   205,   214,   217,   228,
     259,   264,   269,   272,   277,   278,   290,   291,   294,   297,
     300,   303,   306,   309,   314,   315,   318,   321,   348,   349,
     353,   354,   357,   360,   363,   366,   369,   372,   375,   378,
     379,   380,   381,   385,   386,   389,   392,   395,   398,   401,
     404,   408,   412,   416,   426,   427,   431,   434,   439,   444,
     463,   467,   474,   478,   486,   488,   493,   497,   508,   509,
     544,   553,   563,   572,   585,   602,   614,   623,   633,   644,
     655,   665,   680,   691,   699,   707,   712,   722,   732,   736,
     740,   744,   755,   759,   763,   767,   771,   775,   792,   793,
     798,   803,   811,   812,   818,   824,   832,   833,   837,   841,
     845,   850,   855,   860,   867,   868,   874,   875,   880,   885,
     893,   894,   898,   913,   928,   945,   946,   949,   952,   955,
     958,   961,   964,   967,   970,   973,   979,   980,   987,   993,
     994,   997,  1000,  1003,  1006,  1009,  1012,  1015,  1018,  1021,
    1022,  1023,  1024,  1025,  1028,  1033,  1038,  1043,  1048,  1053,
    1058,  1059,  1076,  1080,  1083,  1086,  1089,  1095,  1100,  1104,
    1108,  1112,  1116,  1120,  1124,  1128,  1156,  1160,  1165,  1169,
    1174,  1189,  1202,  1215,  1216,  1217,  1218,  1222,  1229,  1230,
    1231,  1235,  1236,  1237,  1240,  1241,  1242,  1243,  1245,  1258,
    1269,  1273,  1279,  1299,  1304,  1308,  1312,  1324,  1329,  1335,
    1362,  1404,  1409,  1422,  1437,  1449,  1464,  1480,  1502,  1518
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "END_OF_WEIGHTED_EXPRESSION", "WEIGHT",
  "SYMBOL_WITH_LEFT_PAREN", "SYMBOL", "CURLY_LITERAL", "QUOTED_LITERAL",
  "INTERSECTION", "LENIENT_COMPOSITION", "COMPOSITION", "CROSS_PRODUCT",
  "MARKUP_MARKER", "CENTER_MARKER", "SHUFFLE", "LEFT_RIGHT_ARROW",
  "RIGHT_ARROW", "LEFT_ARROW", "LEFT_RESTRICTION", "LTR_SHORTEST_MATCH",
  "LTR_LONGEST_MATCH", "RTL_SHORTEST_MATCH", "RTL_LONGEST_MATCH",
  "OPTIONAL_REPLACE_LEFT_RIGHT", "REPLACE_LEFT_RIGHT",
  "OPTIONAL_REPLACE_LEFT", "OPTIONAL_REPLACE_RIGHT", "REPLACE_LEFT",
  "REPLACE_RIGHT", "REPLACE_CONTEXT_LL", "REPLACE_CONTEXT_UL",
  "REPLACE_CONTEXT_LU", "REPLACE_CONTEXT_UU", "LOWER_PRIORITY_UNION",
  "UPPER_PRIORITY_UNION", "LOWER_MINUS", "UPPER_MINUS", "MINUS", "UNION",
  "LEFT_QUOTIENT", "IGNORE_INTERNALLY", "IGNORING", "COMMACOMMA", "COMMA",
  "AFTER", "BEFORE", "TERM_COMPLEMENT", "SUBSTITUTE_LEFT",
  "CONTAINMENT_OPT", "CONTAINMENT_ONCE", "CONTAINMENT", "COMPLEMENT",
  "PLUS", "STAR", "LOWER", "UPPER", "INVERT", "REVERSE", "CATENATE_N_TO_K",
  "CATENATE_N_MINUS", "CATENATE_N_PLUS", "CATENATE_N", "READ_LEXC",
  "READ_RE", "READ_PROLOG", "READ_SPACED", "READ_TEXT", "READ_BIN",
  "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS",
  "LEFT_BRACKET_DOTTED", "RIGHT_BRACKET_DOTTED", "END_OF_EXPRESSION",
  "PAIR_SEPARATOR", "PAIR_SEPARATOR_SOLE", "PAIR_SEPARATOR_WO_RIGHT",
  "PAIR_SEPARATOR_WO_LEFT", "EPSILON_TOKEN", "ANY_TOKEN",
  "BOUNDARY_MARKER", "LEXER_ERROR", "AND_LEFT", "OR_LEFT", "SYM_LEFT",
  "MAP_LEFT", "NRC_LEFT", "NLC_LEFT", "RC_LEFT", "LC_LEFT", "ENDTAG_LEFT",
  "DEFINE_LEFT", "INS_LEFT", "TOUPPER_LEFT", "TOLOWER_LEFT", "OPTCAP_LEFT",
  "WHITESPACE", "PUNCT", "NUM", "UPPERALPHA", "LOWERALPHA", "ALPHA",
  "DEFFUN", "DEFINS", "REGEX", "DEFINE", "$accept", "PMATCH", "DEFINITION",
  "BINDING", "FUNCTION", "ARGLIST", "ARGS", "REGEXP1", "FUNCBODY1",
  "FUNCBODY2", "FUNCBODY3", "FUNCBODY4", "FUNCBODY5", "FUNCBODY6",
  "FUNC_LABEL_PAIR", "REGEXP2", "REPLACE", "PARALLEL_RULES", "RULE",
  "MAPPINGPAIR_VECTOR", "MAPPINGPAIR", "CONTEXTS_WITH_MARK",
  "CONTEXTS_VECTOR", "CONTEXT", "CONTEXT_MARK", "REPLACE_ARROW", "REGEXP3",
  "REGEXP4", "REGEXP5", "REGEXP6", "REGEXP7", "REGEXP8", "REGEXP9",
  "REGEXP10", "REGEXP11", "OPTCAP", "TOLOWER", "TOUPPER", "FUN_OPTCAP",
  "FUN_TOLOWER", "FUN_TOUPPER", "REGEXP12", "LABEL_PAIR", "LABEL",
  "CONTEXT_CONDITION", "P_CONTEXT", "OR_CONTEXT", "AND_CONTEXT",
  "CONTEXT_CONDITIONS", "FUNCALL", "FUNCALL_ARGLIST", "FUNCALL_ARG", "MAP",
  "INSERT", "ANONYMOUS_DEFINITION", "RIGHT_CONTEXT",
  "NEGATIVE_RIGHT_CONTEXT", "LEFT_CONTEXT", "NEGATIVE_LEFT_CONTEXT",
  "FUN_RIGHT_CONTEXT", "FUN_NEGATIVE_RIGHT_CONTEXT", "FUN_LEFT_CONTEXT",
  "FUN_NEGATIVE_LEFT_CONTEXT", 0
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
     355,   356,   357,   358,   359,   360,   361,   362
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   108,   109,   109,   110,   110,   110,   110,   111,   112,
     113,   113,   114,   114,   115,   115,   116,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   117,   117,   118,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   122,   123,   123,   123,   123,   124,   124,
     125,   125,   126,   126,   127,   127,   128,   128,   128,   128,
     128,   128,   129,   130,   130,   131,   131,   131,   132,   132,
     132,   132,   133,   133,   133,   133,   133,   133,   134,   134,
     134,   134,   135,   135,   135,   135,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   138,   138,   138,   138,
     139,   139,   139,   139,   139,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   141,   141,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   143,   144,   145,   146,   147,   148,
     149,   149,   149,   149,   149,   149,   149,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   151,   151,
     151,   152,   152,   152,   153,   153,   153,   153,   154,   155,
     156,   156,   157,   158,   158,   158,   159,   159,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     5,
       1,     0,     1,     3,     2,     2,     1,     3,     3,     3,
       2,     2,     2,     2,     1,     3,     3,     3,     1,     2,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     1,     1,
       1,     3,     1,     2,     3,     1,     3,     5,     4,     4,
       4,     5,     2,     1,     3,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     1,     5,     5,     5,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     3,
       1,     2,     2,     2,     2,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     7,     1,
       2,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     3,     3,     1,     3,     0,     1,     1,     1,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,    11,     7,     0,
       5,   205,   175,   179,   188,     0,     0,     0,     0,     0,
       0,   166,   165,   164,   163,   162,   161,     0,     0,     0,
     176,     0,   189,   178,   190,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   148,   147,
     146,   145,   144,   143,     6,     0,    64,    69,    70,    72,
      75,    68,    98,   102,   106,   114,   116,   120,   125,   136,
     151,   153,   152,   139,   160,   177,   185,   191,   192,   193,
     183,   184,   149,   150,   194,   195,   196,   197,     4,     1,
       3,    12,     0,    10,     8,   206,   207,   208,     0,   203,
       0,   137,     0,   124,   123,   122,   121,     0,     0,     0,
       0,   174,   173,     0,   172,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,     0,     0,     0,    14,    97,    96,    95,    94,    93,
      92,     0,     0,    91,    90,    89,    88,     0,    73,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,     0,     0,     0,   127,   126,   131,
     130,   129,   128,   135,   134,   133,   132,   140,     0,   171,
       0,     0,   202,   205,   180,   182,     0,   141,   142,     0,
       0,   168,   170,     0,   199,   198,     0,   213,   215,   212,
     214,   186,   187,   211,   210,   156,   155,   154,    67,    65,
      66,     0,    76,     0,    71,    74,     0,     0,    82,    83,
      99,   101,   100,     0,     0,     0,   108,   113,   112,   111,
     110,   109,   107,   119,   118,   117,   181,   169,   167,    13,
      55,    63,    61,    60,    59,     0,     0,    56,     0,     0,
       0,     0,    38,    37,    36,    35,    34,    33,     0,    16,
      24,    28,    30,    43,    54,    40,    42,    41,    62,    39,
     204,     0,    80,     0,   201,     0,    79,    78,    87,    86,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,     0,     0,     0,     0,    20,
      22,    21,    23,     0,     0,     0,    29,    45,    44,    49,
      48,    47,    46,    53,    52,    51,    50,     0,    81,   209,
      77,    85,    84,   105,   104,   103,    31,    32,    57,    58,
     159,   158,   157,    19,    17,    18,     0,     0,     0,     0,
      26,    27,    25,     0,   217,   219,   216,   218,   138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    10,     8,    92,    93,    54,   258,   259,
     260,   261,   262,   263,   264,    55,    56,    57,    58,    59,
      60,   148,   218,   219,   149,   141,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,   265,   266,
     267,    73,    74,    75,    76,    77,    78,    79,   116,    80,
      98,    99,    81,    82,    83,    84,    85,    86,    87,   299,
     300,   301,   302
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -228
static const yytype_int16 yypact[] =
{
     -55,    42,     3,   547,     3,    20,  -228,    55,  -228,   547,
    -228,   145,  -228,   -10,  -228,   713,   713,   646,   646,   646,
     646,  -228,  -228,  -228,  -228,  -228,  -228,   547,   547,   250,
    -228,    60,  -228,   -42,  -228,   579,   579,    56,   547,   547,
     547,   547,    66,   547,    61,   757,   757,   757,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,    43,   580,    40,  -228,   447,
    -228,    25,   177,   254,   646,   208,  -228,   519,  -228,    80,
    -228,  -228,  -228,  -228,  -228,    -1,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,    44,    15,  -228,  -228,  -228,  -228,  -228,    23,    50,
      37,  -228,    64,  -228,  -228,  -228,  -228,    31,    48,   580,
     201,  -228,  -228,   106,  -228,    78,    27,    41,    90,   180,
     256,   338,   351,    77,   111,   363,   112,     1,     4,     6,
    -228,   547,   547,   547,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,   349,   547,  -228,  -228,  -228,  -228,   547,  -228,   448,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   208,   646,   646,   646,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,    22,  -228,
      55,   811,  -228,   145,  -228,  -228,   713,  -228,  -228,   547,
     580,  -228,  -228,   579,  -228,  -228,   122,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,   580,   580,
     580,   547,   481,   580,   446,  -228,   547,   542,   152,  -228,
     177,   177,   177,   202,   368,   449,   646,   646,   646,   646,
     646,   646,   646,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,   811,   811,  -228,   140,   811,
     811,   811,  -228,  -228,  -228,  -228,  -228,  -228,    21,    54,
     811,  -228,   529,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,   160,   580,   547,  -228,   127,   580,   547,   580,   547,
     448,   646,   646,   646,    69,   155,   134,   136,   138,   141,
     154,   811,   811,   811,  -228,   811,   811,   811,   811,  -228,
    -228,  -228,  -228,   811,   811,   811,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,   713,   580,  -228,
     580,   580,  -228,   254,   254,   254,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,    54,    54,    54,    26,   153,   159,   196,
     811,   811,   811,   142,  -228,  -228,  -228,  -228,  -228
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -228,  -228,   212,   228,  -228,  -228,    53,   233,  -227,   364,
     -34,  -212,  -228,  -228,  -228,    29,   -26,  -228,   117,  -228,
     137,  -228,  -228,     7,  -228,   -93,  -228,   130,  -127,   515,
     -53,     5,  -228,   -14,   249,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,   -31,   -29,  -228,  -228,  -228,   -32,  -228,
     103,  -228,  -228,  -160,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -71
static const yytype_int16 yytable[] =
{
     112,   101,   102,   110,   117,   177,   115,   115,   177,     9,
     177,   163,   119,   120,   121,   122,   189,   125,   284,   285,
      89,   269,   103,   104,   105,   106,   223,   224,   225,   236,
      14,   291,   292,   293,   113,   303,   114,   288,   289,   290,
     150,   131,   132,   133,   184,    14,   130,     7,   306,     1,
       2,     3,     4,   131,   132,   133,   107,   108,   131,   132,
     133,    91,   118,   303,   304,   305,   100,   126,    14,   185,
     151,   152,   123,   205,   124,   178,   206,   179,   207,   291,
     292,   293,   192,   142,   177,   269,   269,   181,   180,   269,
     269,   269,   304,   305,   183,   182,   294,   273,   344,   194,
     269,   187,    32,   237,    34,   208,   209,   210,   186,   295,
     296,   297,   298,   195,    14,   212,   213,    32,   134,    34,
     188,   213,   193,   217,     1,     2,     3,     4,   306,   306,
     306,   269,   269,   269,   196,   269,   269,   269,   269,   326,
      32,   111,    34,   269,   269,   269,   286,   238,   287,   201,
     268,    95,    96,    97,   323,   324,   325,   295,   296,   297,
     298,   274,   303,   272,   115,   291,   292,   293,   303,   233,
     234,   235,   271,   163,   163,   163,   163,   163,   163,   163,
     269,   269,   269,   202,   204,   276,    32,   191,    34,   275,
     278,   304,   305,   153,   154,   155,   280,   304,   305,   319,
     135,   136,   137,   138,   317,   303,   328,   139,   329,   140,
     330,   156,   348,   331,   268,   268,   281,    90,   268,   268,
     268,   135,   136,   137,   138,   345,   332,   327,   139,   268,
     140,   346,    88,   239,   304,   305,   157,   158,   159,   160,
     161,   162,    94,   295,   296,   297,   298,   318,   164,   165,
     166,   320,   197,   321,   217,    11,    12,    13,    14,   214,
     268,   268,   268,   156,   268,   268,   268,   268,   347,   340,
     341,   342,   268,   268,   268,   190,   135,   136,   137,   138,
     220,   221,   222,   139,   215,   140,   270,   322,   157,   158,
     159,   160,   161,   162,   127,   128,   129,    15,    16,    17,
      18,    19,    20,   343,     0,     0,     0,     0,     0,   268,
     268,   268,     0,    21,    22,    23,    24,    25,    26,    27,
       0,    28,     0,    29,   109,     0,     0,    30,   198,    31,
      32,    33,    34,     0,    35,    36,     0,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    11,    12,    13,    14,   135,   136,
     137,   138,   211,     0,     0,   139,     0,   140,     0,     0,
       0,   135,   136,   137,   138,     0,     0,   156,   139,     0,
     140,     0,   282,   135,   136,   137,   138,     0,     0,     0,
     139,     0,   140,     0,     0,     0,    15,    16,    17,    18,
      19,    20,   157,   158,   159,   160,   161,   162,     0,     0,
     199,     0,    21,    22,    23,    24,    25,    26,    27,     0,
      28,     0,    29,   200,     0,     0,    30,     0,    31,    32,
      33,    34,     0,    35,    36,   203,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    11,    12,    13,    14,     0,   156,     0,
       0,     0,   216,   283,     0,     0,   -70,   -70,   -70,   -70,
       0,     0,     0,   -70,     0,   -70,     0,   143,   144,   145,
     146,     0,     0,   157,   158,   159,   160,   161,   162,   -70,
       0,   147,     0,     0,   277,    15,    16,    17,    18,    19,
      20,   135,   136,   137,   138,     0,     0,     0,   139,     0,
     140,    21,    22,    23,    24,    25,    26,    27,     0,    28,
       0,    29,     0,     0,     0,    30,     0,    31,    32,    33,
      34,     0,    35,    36,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    11,    12,    13,    14,   279,     0,     0,     0,
       0,     0,   135,   136,   137,   138,     0,     0,     0,   139,
       0,   140,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,     0,     0,    15,    16,    17,    18,    19,    20,
     135,   136,   137,   138,     0,     0,     0,   139,     0,   140,
      21,    22,    23,    24,    25,    26,    27,     0,    28,     0,
      29,     0,     0,     0,    30,     0,    31,    32,    33,    34,
       0,    35,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    11,    12,    13,    14,   333,   334,   335,     0,   336,
     337,   338,   339,    35,    36,     0,     0,    38,    39,    40,
      41,   226,   227,   228,   229,   230,   231,   232,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,    16,    17,    18,    19,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    25,    26,    27,     0,    28,    11,    12,
      13,    14,     0,    30,     0,    31,    32,    33,    34,     0,
      35,    36,     0,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,    16,    11,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,    24,
      25,    26,    27,     0,    28,     0,     0,     0,     0,     0,
      30,     0,    31,    32,    33,    34,     0,    35,    36,     0,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,   240,   241,    14,
      21,    22,    23,    24,    25,    26,    27,     0,    28,     0,
       0,     0,     0,     0,    30,     0,    31,    32,    33,    34,
       0,    35,    36,     0,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   242,     0,     0,     0,   243,   244,
     245,     0,   246,     0,     0,     0,     0,     0,     0,     0,
       0,    32,     0,   247,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   248,     0,    44,   249,   250,   251,   252,
     253,   254,   255,   256,   257
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-228))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      31,    15,    16,    29,    36,     4,    35,    36,     4,     6,
       4,    64,    38,    39,    40,    41,   109,    43,   245,   246,
       0,   181,    17,    18,    19,    20,   153,   154,   155,     7,
       8,    10,    11,    12,    76,     9,    78,   249,   250,   251,
      15,    10,    11,    12,     7,     8,     3,     5,   260,   104,
     105,   106,   107,    10,    11,    12,    27,    28,    10,    11,
      12,     6,     6,     9,    38,    39,    76,     6,     8,   100,
      45,    46,     6,    72,     8,    76,    72,    78,    72,    10,
      11,    12,   113,    43,     4,   245,   246,    72,    44,   249,
     250,   251,    38,    39,    44,    72,    75,   190,    72,    72,
     260,    70,    80,    81,    82,   131,   132,   133,    44,    88,
      89,    90,    91,    72,     8,   141,   142,    80,    75,    82,
      72,   147,    44,   149,   104,   105,   106,   107,   340,   341,
     342,   291,   292,   293,    44,   295,   296,   297,   298,    70,
      80,    81,    82,   303,   304,   305,     6,   178,     8,    72,
     181,     6,     7,     8,   281,   282,   283,    88,    89,    90,
      91,   193,     9,   189,   193,    10,    11,    12,     9,   164,
     165,   166,   186,   226,   227,   228,   229,   230,   231,   232,
     340,   341,   342,    72,    72,   211,    80,    81,    82,    67,
     216,    38,    39,    16,    17,    18,    44,    38,    39,    72,
      20,    21,    22,    23,    44,     9,    72,    27,    72,    29,
      72,     9,    70,    72,   245,   246,    14,     5,   249,   250,
     251,    20,    21,    22,    23,    72,    72,    72,    27,   260,
      29,    72,     4,   180,    38,    39,    34,    35,    36,    37,
      38,    39,     9,    88,    89,    90,    91,   273,    40,    41,
      42,   277,    72,   279,   280,     5,     6,     7,     8,   142,
     291,   292,   293,     9,   295,   296,   297,   298,    72,   303,
     304,   305,   303,   304,   305,    74,    20,    21,    22,    23,
     150,   151,   152,    27,   147,    29,   183,   280,    34,    35,
      36,    37,    38,    39,    45,    46,    47,    47,    48,    49,
      50,    51,    52,   317,    -1,    -1,    -1,    -1,    -1,   340,
     341,   342,    -1,    63,    64,    65,    66,    67,    68,    69,
      -1,    71,    -1,    73,    74,    -1,    -1,    77,    72,    79,
      80,    81,    82,    -1,    84,    85,    -1,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     5,     6,     7,     8,    20,    21,
      22,    23,    13,    -1,    -1,    27,    -1,    29,    -1,    -1,
      -1,    20,    21,    22,    23,    -1,    -1,     9,    27,    -1,
      29,    -1,    14,    20,    21,    22,    23,    -1,    -1,    -1,
      27,    -1,    29,    -1,    -1,    -1,    47,    48,    49,    50,
      51,    52,    34,    35,    36,    37,    38,    39,    -1,    -1,
      72,    -1,    63,    64,    65,    66,    67,    68,    69,    -1,
      71,    -1,    73,    72,    -1,    -1,    77,    -1,    79,    80,
      81,    82,    -1,    84,    85,    72,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,     5,     6,     7,     8,    -1,     9,    -1,
      -1,    -1,    14,    14,    -1,    -1,    20,    21,    22,    23,
      -1,    -1,    -1,    27,    -1,    29,    -1,    30,    31,    32,
      33,    -1,    -1,    34,    35,    36,    37,    38,    39,    43,
      -1,    44,    -1,    -1,    13,    47,    48,    49,    50,    51,
      52,    20,    21,    22,    23,    -1,    -1,    -1,    27,    -1,
      29,    63,    64,    65,    66,    67,    68,    69,    -1,    71,
      -1,    73,    -1,    -1,    -1,    77,    -1,    79,    80,    81,
      82,    -1,    84,    85,    -1,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     5,     6,     7,     8,    14,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    23,    -1,    -1,    -1,    27,
      -1,    29,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    -1,    47,    48,    49,    50,    51,    52,
      20,    21,    22,    23,    -1,    -1,    -1,    27,    -1,    29,
      63,    64,    65,    66,    67,    68,    69,    -1,    71,    -1,
      73,    -1,    -1,    -1,    77,    -1,    79,    80,    81,    82,
      -1,    84,    85,    -1,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,     5,     6,     7,     8,   291,   292,   293,    -1,   295,
     296,   297,   298,    84,    85,    -1,    -1,    88,    89,    90,
      91,   156,   157,   158,   159,   160,   161,   162,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    69,    -1,    71,     5,     6,
       7,     8,    -1,    77,    -1,    79,    80,    81,    82,    -1,
      84,    85,    -1,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,
      67,    68,    69,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    79,    80,    81,    82,    -1,    84,    85,    -1,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,     6,     7,     8,
      63,    64,    65,    66,    67,    68,    69,    -1,    71,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    79,    80,    81,    82,
      -1,    84,    85,    -1,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    67,    68,
      69,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    92,    -1,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   104,   105,   106,   107,   109,   110,     5,   112,     6,
     111,     5,     6,     7,     8,    47,    48,    49,    50,    51,
      52,    63,    64,    65,    66,    67,    68,    69,    71,    73,
      77,    79,    80,    81,    82,    84,    85,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   115,   123,   124,   125,   126,   127,
     128,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   149,   150,   151,   152,   153,   154,   155,
     157,   160,   161,   162,   163,   164,   165,   166,   111,     0,
     110,     6,   113,   114,   115,     6,     7,     8,   158,   159,
      76,   141,   141,   139,   139,   139,   139,   123,   123,    74,
     124,    81,   151,    76,    78,   152,   156,   156,     6,   124,
     124,   124,   124,     6,     8,   124,     6,   142,   142,   142,
       3,    10,    11,    12,    75,    20,    21,    22,    23,    27,
      29,   133,    43,    30,    31,    32,    33,    44,   129,   132,
      15,    45,    46,    16,    17,    18,     9,    34,    35,    36,
      37,    38,    39,   138,    40,    41,    42,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,     4,    76,    78,
      44,    72,    72,    44,     7,   151,    44,    70,    72,   133,
      74,    81,   151,    44,    72,    72,    44,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,   124,   124,
     124,    13,   124,   124,   126,   128,    14,   124,   130,   131,
     135,   135,   135,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   137,   139,   139,   139,     7,    81,   151,   114,
       6,     7,    63,    67,    68,    69,    71,    82,    92,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   116,   117,
     118,   119,   120,   121,   122,   146,   147,   148,   151,   161,
     158,   141,   124,   133,   156,    67,   124,    13,   124,    14,
      44,    14,    14,    14,   116,   116,     6,     8,   119,   119,
     119,    10,    11,    12,    75,    88,    89,    90,    91,   167,
     168,   169,   170,     9,    38,    39,   119,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    44,   124,    72,
     124,   124,   131,   136,   136,   136,    70,    72,    72,    72,
      72,    72,    72,   117,   117,   117,   117,   117,   117,   117,
     118,   118,   118,   141,    72,    72,    72,    72,    70
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
#line 151 "pmatch_parse.yy"
    {
    if ((yyvsp[(1) - (1)].transducerDefinition)->first.compare("@_PMATCH_DUMMY_@")) {
        if(hfst::pmatch::definitions.count((yyvsp[(1) - (1)].transducerDefinition)->first) != 0) {
            std::stringstream warning;
            warning << "definition of " << (yyvsp[(1) - (1)].transducerDefinition)->first << " on line "
                    << pmatchlineno << " shadowed by earlier definition\n";
            hfst::pmatch::warn(warning.str());
        }
         hfst::pmatch::definitions.insert(*(yyvsp[(1) - (1)].transducerDefinition));
         if (hfst::pmatch::verbose) {
             std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(2);
             double duration = (clock() - hfst::pmatch::timer) /
                 (double) CLOCKS_PER_SEC;
             hfst::pmatch::timer = clock();
             std::cerr << "compiled " << (yyvsp[(1) - (1)].transducerDefinition)->first << " in " << duration << " seconds\n";
             hfst::pmatch::print_size_info((yyvsp[(1) - (1)].transducerDefinition)->second);
             std::cerr << std::endl;
         }
    }
    delete (yyvsp[(1) - (1)].transducerDefinition);
 }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 172 "pmatch_parse.yy"
    {
     if ((yyvsp[(2) - (2)].transducerDefinition)->first.compare("@_PMATCH_DUMMY_@")) {
         if(hfst::pmatch::definitions.count((yyvsp[(2) - (2)].transducerDefinition)->first) != 0) {
             std::stringstream warning;
             warning << "definition of " << (yyvsp[(2) - (2)].transducerDefinition)->first << " on line "
                     << pmatchlineno << " shadowed by earlier definition\n";
             hfst::pmatch::warn(warning.str());
         }
         hfst::pmatch::definitions.insert(*(yyvsp[(2) - (2)].transducerDefinition));
         if (hfst::pmatch::verbose) {
             std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(2);
             double duration = (clock() - hfst::pmatch::timer) /
                 (double) CLOCKS_PER_SEC;
             hfst::pmatch::timer = clock();
             std::cerr << "compiled " << (yyvsp[(2) - (2)].transducerDefinition)->first << " in " << duration << " seconds\n";
             hfst::pmatch::print_size_info((yyvsp[(2) - (2)].transducerDefinition)->second);
             std::cerr << std::endl;
         }
     }
     delete (yyvsp[(2) - (2)].transducerDefinition);
 }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 195 "pmatch_parse.yy"
    { (yyval.transducerDefinition) = (yyvsp[(2) - (2)].transducerDefinition); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 196 "pmatch_parse.yy"
    {
    char * Ins_trans = hfst::pmatch::get_Ins_transition((yyvsp[(2) - (2)].transducerDefinition)->first.c_str());
    HfstTransducer * ins_t = new HfstTransducer(
        Ins_trans, Ins_trans, hfst::pmatch::format);
    ins_t->set_name((yyvsp[(2) - (2)].transducerDefinition)->first);
    free(Ins_trans);
    hfst::pmatch::def_insed_transducers[(yyvsp[(2) - (2)].transducerDefinition)->first] = ins_t;
    (yyval.transducerDefinition) = (yyvsp[(2) - (2)].transducerDefinition);
 }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 205 "pmatch_parse.yy"
    {
    (yyvsp[(2) - (2)].transducer)->set_name("TOP");
    if (hfst::pmatch::need_delimiters) {
        (yyvsp[(2) - (2)].transducer) = hfst::pmatch::add_pmatch_delimiters((yyvsp[(2) - (2)].transducer));
    }
    hfst::pmatch::need_delimiters = false;
    (yyvsp[(2) - (2)].transducer)->minimize();
    (yyval.transducerDefinition) = new std::pair<std::string, hfst::HfstTransducer*>("TOP", (yyvsp[(2) - (2)].transducer));
 }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 214 "pmatch_parse.yy"
    { (yyval.transducerDefinition) = (yyvsp[(2) - (2)].transducerDefinition); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 217 "pmatch_parse.yy"
    {
    if (hfst::pmatch::need_delimiters) {
        (yyvsp[(2) - (2)].transducer) = hfst::pmatch::add_pmatch_delimiters((yyvsp[(2) - (2)].transducer));
    }
    hfst::pmatch::need_delimiters = false;
    (yyvsp[(2) - (2)].transducer)->set_name((yyvsp[(1) - (2)].label));
    (yyvsp[(2) - (2)].transducer)->minimize();
    (yyval.transducerDefinition) = new std::pair<std::string, hfst::HfstTransducer*>((yyvsp[(1) - (2)].label), (yyvsp[(2) - (2)].transducer));
 }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 228 "pmatch_parse.yy"
    {
    PmatchAstNode * function_body;
    if (hfst::pmatch::need_delimiters) {
        function_body = new PmatchAstNode((yyvsp[(4) - (5)].ast_node), hfst::pmatch::AstAddDelimiters);
    } else {
        function_body = (yyvsp[(4) - (5)].ast_node);
    }
    hfst::pmatch::need_delimiters = false;
    hfst::pmatch::PmatchFunction fun(* (yyvsp[(2) - (5)].string_vector), function_body);
    if(hfst::pmatch::functions.count((yyvsp[(1) - (5)].label)) != 0) {
        std::stringstream warning;
        warning << "definition of function" << (yyvsp[(1) - (5)].label) << " on line "
                << pmatchlineno << " shadowed by earlier definition\n";
        hfst::pmatch::warn(warning.str());
    }
    hfst::pmatch::functions[(yyvsp[(1) - (5)].label)] = fun;
    // Pass a dummy transducer, since function registration is separate
    HfstTransducer * dummy = new HfstTransducer(hfst::pmatch::format);
    dummy->set_name("@_PMATCH_DUMMY_@");
    (yyval.transducerDefinition) = new std::pair<std::string, hfst::HfstTransducer*>("@_PMATCH_DUMMY_@", dummy);
    if (hfst::pmatch::verbose) {
        std::cerr << std::setiosflags(std::ios::fixed) << std::setprecision(2);
        double duration = (clock() - hfst::pmatch::timer) /
            (double) CLOCKS_PER_SEC;
        hfst::pmatch::timer = clock();
        std::cerr << "defined function" << (yyvsp[(1) - (5)].label) << " in " << duration << " seconds\n";
        std::cerr << std::endl;
    }
 }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 259 "pmatch_parse.yy"
    {
    (yyval.string_vector) = new std::vector<std::string>(hfst::pmatch::tmp_collected_funargs);
    hfst::pmatch::tmp_collected_funargs.clear();
 }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 264 "pmatch_parse.yy"
    {
    (yyval.string_vector) = new std::vector<std::string>();
    hfst::pmatch::tmp_collected_funargs.clear();
}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 269 "pmatch_parse.yy"
    {
    hfst::pmatch::tmp_collected_funargs.push_back((yyvsp[(1) - (1)].label));
 }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 272 "pmatch_parse.yy"
    {
    hfst::pmatch::tmp_collected_funargs.push_back((yyvsp[(1) - (3)].label));
 }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 277 "pmatch_parse.yy"
    { }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 278 "pmatch_parse.yy"
    {
    (yyvsp[(1) - (2)].transducer)->set_final_weights((yyvsp[(2) - (2)].weight));
    (yyval.transducer) = (yyvsp[(1) - (2)].transducer);
 }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 290 "pmatch_parse.yy"
    { }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 291 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), hfst::pmatch::AstCompose);
 }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 294 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), hfst::pmatch::AstCrossProduct);
 }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 297 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), hfst::pmatch::AstLenientCompose);
 }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 300 "pmatch_parse.yy"
    {
     (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), hfst::pmatch::AstConcatenate);
 }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 303 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(2) - (2)].ast_node), (yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstConcatenate);
 }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 306 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), hfst::pmatch::AstConcatenate);
 }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 309 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(2) - (2)].ast_node), (yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstConcatenate);
 }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 314 "pmatch_parse.yy"
    { }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 315 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), hfst::pmatch::AstDisjunct);
 }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 318 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), hfst::pmatch::AstIntersect);
 }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 321 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (3)].ast_node), (yyvsp[(3) - (3)].ast_node), hfst::pmatch::AstSubtract);
 }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 348 "pmatch_parse.yy"
    { }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 349 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), (yyvsp[(2) - (2)].ast_node), hfst::pmatch::AstConcatenate);
 }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 354 "pmatch_parse.yy"
    {
    (yyval.ast_node) = (yyvsp[(2) - (3)].ast_node);
 }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 357 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstOptionalize);
 }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 360 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_alpha_acceptor);
 }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 363 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_lowercase_acceptor);
 }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 366 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_uppercase_acceptor);
 }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 369 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_numeral_acceptor);
 }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 372 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_punct_acceptor);
 }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 375 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::get_utils()->latin1_whitespace_acceptor);
 }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 378 "pmatch_parse.yy"
    { (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (1)].transducer)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 379 "pmatch_parse.yy"
    { }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 380 "pmatch_parse.yy"
    { }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 381 "pmatch_parse.yy"
    { }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 385 "pmatch_parse.yy"
    { }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 386 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstRepeatStar);
 }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 389 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstRepeatPlus);
 }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 392 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstReverse);
 }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 395 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstInvert);
 }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 398 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstInputProject);
  }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 401 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstOutputProject);
 }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 404 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstRepeatN);
    (yyval.ast_node)->push_numeric_arg((yyvsp[(2) - (2)].value));
 }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 408 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstRepeatNPlus);
    (yyval.ast_node)->push_numeric_arg((yyvsp[(2) - (2)].value) + 1);
 }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 412 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstRepeatNMinus);
    (yyval.ast_node)->push_numeric_arg((yyvsp[(2) - (2)].value) - 1);
 }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 416 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (2)].ast_node), hfst::pmatch::AstRepeatNToK);
    (yyval.ast_node)->push_numeric_arg((yyvsp[(2) - (2)].values)[0]);
    (yyval.ast_node)->push_numeric_arg((yyvsp[(2) - (2)].values)[1]);
    free((yyvsp[(2) - (2)].values));
 }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 426 "pmatch_parse.yy"
    { }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 427 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(1) - (1)].label));
    free((yyvsp[(1) - (1)].label));
 }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 431 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(new HfstTransducer("@BOUNDARY@", "@BOUNDARY@", hfst::pmatch::format));
  }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 434 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::make_end_tag((yyvsp[(2) - (3)].label)));
    hfst::pmatch::need_delimiters = true;
    free((yyvsp[(2) - (3)].label));
 }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 439 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::make_end_tag((yyvsp[(2) - (3)].label)));
    hfst::pmatch::need_delimiters = true;
    free((yyvsp[(2) - (3)].label));
 }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 444 "pmatch_parse.yy"
    {
    HfstTransducer * read;
    try {
        hfst::HfstInputStream instream((yyvsp[(1) - (1)].label));
        read = new HfstTransducer(instream);
        instream.close();
    } catch(HfstException) {
        std::string ermsg =
            std::string("Couldn't read transducer from ") +
            std::string((yyvsp[(1) - (1)].label));
        free((yyvsp[(1) - (1)].label));
        pmatcherror(ermsg.c_str());
    }
    if (read->get_type() != hfst::pmatch::format) {
        read->convert(hfst::pmatch::format);
    }
    (yyval.ast_node) = new PmatchAstNode(read);
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 463 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::pmatch::read_text((yyvsp[(1) - (1)].label)));
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 467 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(hfst::HfstTransducer::read_lexc_ptr((yyvsp[(1) - (1)].label), hfst::TROPICAL_OPENFST_TYPE, hfst::pmatch::verbose));
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 474 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode(new HfstTransducer((yyvsp[(1) - (1)].label), hfst::pmatch::format));
    free((yyvsp[(1) - (1)].label));
}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 478 "pmatch_parse.yy"
    {
    HfstTokenizer tok;
    (yyval.ast_node) = new PmatchAstNode(new HfstTransducer((yyvsp[(1) - (1)].label), tok, hfst::pmatch::format));
    free((yyvsp[(1) - (1)].label));
}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 487 "pmatch_parse.yy"
    { }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 488 "pmatch_parse.yy"
    {
       
    (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->compose(*(yyvsp[(3) - (3)].transducer));
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 493 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->cross_product(*(yyvsp[(3) - (3)].transducer));
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 497 "pmatch_parse.yy"
    {
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 508 "pmatch_parse.yy"
    {}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 510 "pmatch_parse.yy"
    {
    // std::cerr << "replace:parallel_rules"<< std::endl;        
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
    }
       
    delete (yyvsp[(1) - (1)].replaceRuleVectorWithArrow);
}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 545 "pmatch_parse.yy"
    {
    //   std::cerr << "parallel_rules:rule"<< std::endl;        
    std::vector<Rule> * ruleVector = new std::vector<Rule>();
    ruleVector->push_back((yyvsp[(1) - (1)].replaceRuleWithArrow)->second);
            
    (yyval.replaceRuleVectorWithArrow) =  new std::pair< ReplaceArrow, std::vector<Rule> > ((yyvsp[(1) - (1)].replaceRuleWithArrow)->first, *ruleVector);
    delete (yyvsp[(1) - (1)].replaceRuleWithArrow);
}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 554 "pmatch_parse.yy"
    {
    // std::cerr << "parallel_rules: parallel_rules ,, rule"<< std::endl;      
    Rule tmpRule((yyvsp[(3) - (3)].replaceRuleWithArrow)->second);
    (yyvsp[(1) - (3)].replaceRuleVectorWithArrow)->second.push_back(tmpRule);
    (yyval.replaceRuleVectorWithArrow) =  new std::pair< ReplaceArrow, std::vector<Rule> > ((yyvsp[(3) - (3)].replaceRuleWithArrow)->first, (yyvsp[(1) - (3)].replaceRuleVectorWithArrow)->second);
    delete (yyvsp[(3) - (3)].replaceRuleWithArrow);
}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 564 "pmatch_parse.yy"
    {
     // std::cerr << "rule: mapping_vector"<< std::endl;      
    // HfstTransducer allMappingsDisjuncted = disjunctVectorMembers($1->second);
     
     Rule rule( (yyvsp[(1) - (1)].mappingVectorWithArrow)->second );;
     (yyval.replaceRuleWithArrow) =  new std::pair< ReplaceArrow, Rule> ((yyvsp[(1) - (1)].mappingVectorWithArrow)->first, rule);
     delete (yyvsp[(1) - (1)].mappingVectorWithArrow);
  }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 573 "pmatch_parse.yy"
    {
    // std::cerr << "rule: mapping_vector contextsWM"<< std::endl;      
 //   HfstTransducer allMappingsDisjuncted = disjunctVectorMembers($1->second);
    
    Rule rule( (yyvsp[(1) - (2)].mappingVectorWithArrow)->second, (yyvsp[(2) - (2)].contextWithMark)->second, (yyvsp[(2) - (2)].contextWithMark)->first );
    (yyval.replaceRuleWithArrow) =  new std::pair< ReplaceArrow, Rule> ((yyvsp[(1) - (2)].mappingVectorWithArrow)->first, rule);
    delete (yyvsp[(1) - (2)].mappingVectorWithArrow), (yyvsp[(2) - (2)].contextWithMark);
  }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 586 "pmatch_parse.yy"
    {
    // std::cerr << "mapping_vector : mapping_vector comma mapping"<< std::endl;      
    // check if new Arrow is the same as the first one

    if ((yyvsp[(1) - (3)].mappingVectorWithArrow)->first != (yyvsp[(3) - (3)].mappingWithArrow)->first)
    {
        pmatcherror("Replace arrows should be the same. Calculated as if all replacements had the fist arrow.");
        //exit(1);
    }

	(yyvsp[(1) - (3)].mappingVectorWithArrow)->second.push_back((yyvsp[(3) - (3)].mappingWithArrow)->second);
    (yyval.mappingVectorWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPairVector> ((yyvsp[(1) - (3)].mappingVectorWithArrow)->first, (yyvsp[(1) - (3)].mappingVectorWithArrow)->second);
    delete (yyvsp[(3) - (3)].mappingWithArrow);
            
}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 603 "pmatch_parse.yy"
    {
    // std::cerr << "mapping_vector : mapping"<< std::endl;      
	 HfstTransducerPairVector * mappingPairVector = new HfstTransducerPairVector();
	 mappingPairVector->push_back( (yyvsp[(1) - (1)].mappingWithArrow)->second );
	 (yyval.mappingVectorWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPairVector> ((yyvsp[(1) - (1)].mappingWithArrow)->first, * mappingPairVector);
	 delete (yyvsp[(1) - (1)].mappingWithArrow); 
}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 615 "pmatch_parse.yy"
    {
        // std::cerr << "mapping : r2 arrow r2"<< std::endl;      

          HfstTransducerPair mappingPair(*(yyvsp[(1) - (3)].transducer), *(yyvsp[(3) - (3)].transducer));
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (3)].replaceArrow), mappingPair);

          delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer);
      }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 624 "pmatch_parse.yy"
    {
      
          HfstTransducerPair marks(*(yyvsp[(3) - (5)].transducer), *(yyvsp[(5) - (5)].transducer));
          HfstTransducerPair tmpMappingPair(*(yyvsp[(1) - (5)].transducer), HfstTransducer(hfst::pmatch::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
          
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (5)].replaceArrow), mappingPair);
         delete (yyvsp[(1) - (5)].transducer), (yyvsp[(3) - (5)].transducer), (yyvsp[(5) - (5)].transducer);
      }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 634 "pmatch_parse.yy"
    {
   
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
          HfstTransducerPair marks(*(yyvsp[(3) - (4)].transducer), epsilon);
          HfstTransducerPair tmpMappingPair(*(yyvsp[(1) - (4)].transducer), HfstTransducer(hfst::pmatch::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
                   
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (4)].replaceArrow), mappingPair);
         delete (yyvsp[(1) - (4)].transducer), (yyvsp[(3) - (4)].transducer);
      }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 645 "pmatch_parse.yy"
    {
          HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
          HfstTransducerPair marks(epsilon, *(yyvsp[(4) - (4)].transducer));
          HfstTransducerPair tmpMappingPair(*(yyvsp[(1) - (4)].transducer), HfstTransducer(hfst::pmatch::format));
          HfstTransducerPair mappingPair = create_mapping_for_mark_up_replace( tmpMappingPair, marks );
          
          (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(2) - (4)].replaceArrow), mappingPair);
         delete (yyvsp[(1) - (4)].transducer), (yyvsp[(4) - (4)].transducer);
      }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 656 "pmatch_parse.yy"
    {
      HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
      //HfstTransducer mappingTr(epsilon);
      //mappingTr.cross_product(*$4);
      HfstTransducerPair mappingPair(epsilon, *(yyvsp[(4) - (4)].transducer));
      
      (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(3) - (4)].replaceArrow), mappingPair);
      delete (yyvsp[(4) - (4)].transducer);
  }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 666 "pmatch_parse.yy"
    {
    //  HfstTransducer mappingTr(*$2);
    //  mappingTr.cross_product(*$5);
	  HfstTransducerPair mappingPair(*(yyvsp[(2) - (5)].transducer), *(yyvsp[(5) - (5)].transducer));
      (yyval.mappingWithArrow) =  new std::pair< ReplaceArrow, HfstTransducerPair> ((yyvsp[(4) - (5)].replaceArrow), mappingPair);
      delete (yyvsp[(2) - (5)].transducer), (yyvsp[(5) - (5)].transducer);
  }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 681 "pmatch_parse.yy"
    {
       
    //std::cerr << "context w mark: conMark conVect"<< std::endl;      
         
    (yyval.contextWithMark) =  new std::pair< ReplaceType, HfstTransducerPairVector> ((yyvsp[(1) - (2)].replType), *(yyvsp[(2) - (2)].transducerPairVector));
    //$$ = $2;
    //std::cerr << "Context Mark: \n" << $1  << std::endl;
   
}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 692 "pmatch_parse.yy"
    {
    HfstTransducerPairVector * ContextVector = new HfstTransducerPairVector();
    ContextVector->push_back(*(yyvsp[(1) - (1)].transducerPair));
    (yyval.transducerPairVector) = ContextVector;
    delete (yyvsp[(1) - (1)].transducerPair); 
}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 700 "pmatch_parse.yy"
    {
    (yyvsp[(1) - (3)].transducerPairVector)->push_back(*(yyvsp[(3) - (3)].transducerPair));
    (yyval.transducerPairVector) = (yyvsp[(1) - (3)].transducerPairVector);
    delete (yyvsp[(3) - (3)].transducerPair); 
}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 708 "pmatch_parse.yy"
    {
    (yyval.transducerPair) = new HfstTransducerPair(*(yyvsp[(1) - (3)].transducer), *(yyvsp[(3) - (3)].transducer));
    delete (yyvsp[(1) - (3)].transducer), (yyvsp[(3) - (3)].transducer); 
}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 713 "pmatch_parse.yy"
    {
    // std::cerr << "Mapping: \n" << *$1  << std::endl;
            
    HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
            
    // std::cerr << "Epsilon: \n" << epsilon  << std::endl;
    (yyval.transducerPair) = new HfstTransducerPair(*(yyvsp[(1) - (2)].transducer), epsilon);
    delete (yyvsp[(1) - (2)].transducer); 
}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 723 "pmatch_parse.yy"
    {
    HfstTransducer epsilon(hfst::internal_epsilon, hfst::pmatch::format);
    (yyval.transducerPair) = new HfstTransducerPair(epsilon, *(yyvsp[(2) - (2)].transducer));
    delete (yyvsp[(2) - (2)].transducer); 
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 733 "pmatch_parse.yy"
    {
    (yyval.replType) = REPL_UP;
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 737 "pmatch_parse.yy"
    {
    (yyval.replType) = REPL_RIGHT;
}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 741 "pmatch_parse.yy"
    {
    (yyval.replType) = REPL_LEFT;
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 745 "pmatch_parse.yy"
    {
    (yyval.replType) = REPL_DOWN;
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 756 "pmatch_parse.yy"
    {
    (yyval.replaceArrow) = E_REPLACE_RIGHT;
}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 760 "pmatch_parse.yy"
    {
    (yyval.replaceArrow) = E_OPTIONAL_REPLACE_RIGHT;
}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 764 "pmatch_parse.yy"
    {
    (yyval.replaceArrow) = E_RTL_LONGEST_MATCH;
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 768 "pmatch_parse.yy"
    {
    (yyval.replaceArrow) = E_RTL_SHORTEST_MATCH;
}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 772 "pmatch_parse.yy"
    {
    (yyval.replaceArrow) = E_LTR_LONGEST_MATCH;
}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 776 "pmatch_parse.yy"
    {
    (yyval.replaceArrow) = E_LTR_SHORTEST_MATCH;
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 792 "pmatch_parse.yy"
    { }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 793 "pmatch_parse.yy"
    {
    pmatcherror("No shuffle");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 798 "pmatch_parse.yy"
    {
    pmatcherror("No before");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 803 "pmatch_parse.yy"
    {
    pmatcherror("No after");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 811 "pmatch_parse.yy"
    { }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 812 "pmatch_parse.yy"
    {
    pmatcherror("No Arrows");
    (yyval.transducer) = (yyvsp[(1) - (5)].transducer);
    delete (yyvsp[(3) - (5)].transducer);
    delete (yyvsp[(5) - (5)].transducer);
 }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 818 "pmatch_parse.yy"
    {
    pmatcherror("No Arrows");
    (yyval.transducer) = (yyvsp[(1) - (5)].transducer);
    delete (yyvsp[(3) - (5)].transducer);
    delete (yyvsp[(5) - (5)].transducer);
 }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 824 "pmatch_parse.yy"
    {
    pmatcherror("No Arrows");
    (yyval.transducer) = (yyvsp[(1) - (5)].transducer);
    delete (yyvsp[(3) - (5)].transducer);
    delete (yyvsp[(5) - (5)].transducer);
 }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 832 "pmatch_parse.yy"
    { }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 833 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->disjunct(*(yyvsp[(3) - (3)].transducer));
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 837 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->intersect(*(yyvsp[(3) - (3)].transducer));
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 841 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (3)].transducer)->subtract(*(yyvsp[(3) - (3)].transducer));
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 845 "pmatch_parse.yy"
    {
    pmatcherror("No upper minus");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 850 "pmatch_parse.yy"
    {
    pmatcherror("No lower minus");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 855 "pmatch_parse.yy"
    {
    pmatcherror("No upper priority union");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 860 "pmatch_parse.yy"
    {
    pmatcherror("No lower priority union");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 867 "pmatch_parse.yy"
    { }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 868 "pmatch_parse.yy"
    { 
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->concatenate(*(yyvsp[(2) - (2)].transducer));
    delete (yyvsp[(2) - (2)].transducer);
 }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 874 "pmatch_parse.yy"
    { }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 875 "pmatch_parse.yy"
    {
    pmatcherror("No ignoring");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 880 "pmatch_parse.yy"
    {
    pmatcherror("No ignoring internally");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 885 "pmatch_parse.yy"
    {
    pmatcherror("No left quotient");
    (yyval.transducer) = (yyvsp[(1) - (3)].transducer);
    delete (yyvsp[(3) - (3)].transducer);
 }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 893 "pmatch_parse.yy"
    { }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 894 "pmatch_parse.yy"
    {
    pmatcherror("No complement");
    (yyval.transducer) = (yyvsp[(2) - (2)].transducer);
 }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 898 "pmatch_parse.yy"
    {
    HfstTransducer* left = new HfstTransducer(hfst::internal_unknown,
                                              hfst::internal_unknown,
                                              hfst::pmatch::format);
    HfstTransducer* right = new HfstTransducer(hfst::internal_unknown,
                                               hfst::internal_unknown,
                                               hfst::pmatch::format);
    right->repeat_star();
    left->repeat_star();
    HfstTransducer* contain_once = 
        & ((right->concatenate(*(yyvsp[(2) - (2)].transducer)).concatenate(*left)));
    (yyval.transducer) = & (contain_once->repeat_star());
    delete (yyvsp[(2) - (2)].transducer);
    delete left;
 }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 913 "pmatch_parse.yy"
    {
    HfstTransducer* left = new HfstTransducer(hfst::internal_unknown,
                                              hfst::internal_unknown,
                                              hfst::pmatch::format);
    HfstTransducer* right = new HfstTransducer(hfst::internal_unknown,
                                               hfst::internal_unknown,
                                               hfst::pmatch::format);
    right->repeat_star();
    left->repeat_star();
    HfstTransducer* contain_once = 
        & ((right->concatenate(*(yyvsp[(2) - (2)].transducer)).concatenate(*left)));
    (yyval.transducer) = contain_once;
    delete (yyvsp[(2) - (2)].transducer);
    delete left;
 }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 928 "pmatch_parse.yy"
    {
    HfstTransducer* left = new HfstTransducer(hfst::internal_unknown,
                                              hfst::internal_unknown,
                                              hfst::pmatch::format);
    HfstTransducer* right = new HfstTransducer(hfst::internal_unknown,
                                               hfst::internal_unknown,
                                               hfst::pmatch::format);
    right->repeat_star();
    left->repeat_star();
    HfstTransducer* contain_once = 
        & ((right->concatenate(*(yyvsp[(2) - (2)].transducer)).concatenate(*left)));
    (yyval.transducer) = & (contain_once->optionalize());
    delete (yyvsp[(2) - (2)].transducer);
    delete left;
 }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 945 "pmatch_parse.yy"
    { }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 946 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_star();
 }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 949 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_plus();
 }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 952 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->reverse();
 }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 955 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->invert();
 }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 958 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->input_project();
 }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 961 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->output_project();
 }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 964 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n((yyvsp[(2) - (2)].value));
 }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 967 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n_plus((yyvsp[(2) - (2)].value) + 1);
 }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 970 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n_minus((yyvsp[(2) - (2)].value) - 1);
 }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 973 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->repeat_n_to_k((yyvsp[(2) - (2)].values)[0], (yyvsp[(2) - (2)].values)[1]);
    free((yyvsp[(2) - (2)].values));
 }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 979 "pmatch_parse.yy"
    { }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 980 "pmatch_parse.yy"
    {
    HfstTransducer* any = new HfstTransducer(hfst::internal_identity,
                                             hfst::internal_identity,
                                             hfst::pmatch::format);
    (yyval.transducer) = & ( any->subtract(*(yyvsp[(2) - (2)].transducer)));
    delete (yyvsp[(2) - (2)].transducer);
 }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 987 "pmatch_parse.yy"
    {
    pmatcherror("no substitute");
    (yyval.transducer) = (yyvsp[(2) - (7)].transducer);
 }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 993 "pmatch_parse.yy"
    { }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 994 "pmatch_parse.yy"
    { 
    (yyval.transducer) = & (yyvsp[(1) - (2)].transducer)->set_final_weights((yyvsp[(2) - (2)].weight));
 }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 997 "pmatch_parse.yy"
    {
    (yyval.transducer) = (yyvsp[(2) - (3)].transducer);
 }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1000 "pmatch_parse.yy"
    {
    (yyval.transducer) = & (yyvsp[(2) - (3)].transducer)->optionalize();
 }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1003 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_alpha_acceptor);
 }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1006 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_lowercase_acceptor);
 }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1009 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_uppercase_acceptor);
 }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1012 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_numeral_acceptor);
 }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1015 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_punct_acceptor);
 }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 1018 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(*hfst::pmatch::get_utils()->latin1_whitespace_acceptor);
 }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1021 "pmatch_parse.yy"
    { }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1022 "pmatch_parse.yy"
    { }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1023 "pmatch_parse.yy"
    { }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1024 "pmatch_parse.yy"
    { }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1025 "pmatch_parse.yy"
    { }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1028 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::get_utils()->optcap(* (yyvsp[(2) - (3)].transducer));
}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1033 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::get_utils()->tolower(* (yyvsp[(2) - (3)].transducer));
}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 1038 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::get_utils()->toupper(* (yyvsp[(2) - (3)].transducer));
}
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 1043 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstOptCap);
}
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1048 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstToLower);
}
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 1053 "pmatch_parse.yy"
    {
    (yyval.ast_node) = new PmatchAstNode((yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstToUpper);
}
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1058 "pmatch_parse.yy"
    { }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 1059 "pmatch_parse.yy"
    {
    try {
        hfst::HfstInputStream instream((yyvsp[(1) - (1)].label));
        (yyval.transducer) = new HfstTransducer(instream);
        instream.close();
    } catch(HfstException) {
        std::string ermsg =
            std::string("Couldn't read transducer from ") +
            std::string((yyvsp[(1) - (1)].label));
        free((yyvsp[(1) - (1)].label));
        pmatcherror(ermsg.c_str());
    }
    if ((yyval.transducer)->get_type() != hfst::pmatch::format) {
        (yyval.transducer)->convert(hfst::pmatch::format);
    }
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1076 "pmatch_parse.yy"
    {
  (yyval.transducer) = hfst::pmatch::read_text((yyvsp[(1) - (1)].label));
  free((yyvsp[(1) - (1)].label));
  }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1080 "pmatch_parse.yy"
    {
    pmatcherror("no read spaced");
  }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 1083 "pmatch_parse.yy"
    {
    pmatcherror("no read prolog");
  }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 1086 "pmatch_parse.yy"
    {
    pmatcherror("Definitely no read regex");
  }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 1089 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::HfstTransducer::read_lexc_ptr((yyvsp[(1) - (1)].label), hfst::TROPICAL_OPENFST_TYPE, hfst::pmatch::verbose);
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 1095 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (3)].label), (yyvsp[(3) - (3)].label), hfst::pmatch::format);
    free((yyvsp[(1) - (3)].label)); free((yyvsp[(3) - (3)].label));
}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 1100 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
 }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 1104 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (3)].label), hfst::internal_unknown, hfst::pmatch::format);
    free((yyvsp[(1) - (3)].label));
 }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 1108 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_unknown, (yyvsp[(3) - (3)].label), hfst::pmatch::format);
    free((yyvsp[(3) - (3)].label));
}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 1112 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (2)].label), hfst::internal_unknown, hfst::pmatch::format);
    free((yyvsp[(1) - (2)].label));
 }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 1116 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
 }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 1120 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_unknown, (yyvsp[(2) - (2)].label), hfst::pmatch::format);
    free((yyvsp[(2) - (2)].label));
 }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1124 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
 }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 1128 "pmatch_parse.yy"
    {
    if (hfst::pmatch::definitions.count((yyvsp[(1) - (1)].label)) != 0) {
        if (!hfst::pmatch::flatten &&
            hfst::pmatch::def_insed_transducers.count((yyvsp[(1) - (1)].label)) == 1) {
            (yyval.transducer) = new HfstTransducer(*hfst::pmatch::def_insed_transducers[(yyvsp[(1) - (1)].label)]);
            hfst::pmatch::inserted_transducers.insert((yyvsp[(1) - (1)].label));
            if (hfst::pmatch::verbose) {
                hfst::pmatch::used_definitions.insert((yyvsp[(1) - (1)].label));
            }
        } else {
            if (hfst::pmatch::verbose) {
                std::cerr << "including " <<
                    hfst::pmatch::definitions[(yyvsp[(1) - (1)].label)]->get_name() << " with ";
                hfst::pmatch::print_size_info(hfst::pmatch::definitions[(yyvsp[(1) - (1)].label)]);
                hfst::pmatch::used_definitions.insert((yyvsp[(1) - (1)].label));
            }
            (yyval.transducer) = new HfstTransducer(*hfst::pmatch::definitions[(yyvsp[(1) - (1)].label)]);
        }
    } else {
        if (strlen((yyvsp[(1) - (1)].label)) == 0) {
            (yyval.transducer) = new HfstTransducer(hfst::pmatch::format);
        } else {
            std::string errstring = "Unknown symbol: " + std::string((yyvsp[(1) - (1)].label));
            pmatcherror(errstring.c_str());
        }
    }
    free((yyvsp[(1) - (1)].label));
 }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1156 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_unknown, hfst::internal_unknown,
                            hfst::pmatch::format);
  }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 1160 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (1)].label), (yyvsp[(1) - (1)].label),
                            hfst::pmatch::format);
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 1165 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_identity,
                            hfst::pmatch::format);
  }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1169 "pmatch_parse.yy"
    {
    HfstTokenizer tok;
    (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (1)].label), tok, hfst::pmatch::format);
    free((yyvsp[(1) - (1)].label));
 }
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 1174 "pmatch_parse.yy"
    {
    HfstTokenizer tok;
    HfstTransducer * left = new HfstTransducer((yyvsp[(1) - (3)].label), tok, hfst::pmatch::format);
    HfstTransducer * right = new HfstTransducer((yyvsp[(3) - (3)].label), tok, hfst::pmatch::format);
    HfstTransducer * destroy = new HfstTransducer(
        hfst::internal_unknown, hfst::internal_epsilon, hfst::pmatch::format);
    HfstTransducer * construct = new HfstTransducer(
        hfst::internal_epsilon, hfst::internal_unknown, hfst::pmatch::format);
    left->compose(destroy->repeat_star());
    left->compose(construct->repeat_star());
    left->compose(*right);
    (yyval.transducer) = left;
    delete destroy; delete construct; delete right;
    free((yyvsp[(1) - (3)].label)); free((yyvsp[(3) - (3)].label));
}
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1189 "pmatch_parse.yy"
    {
    HfstTokenizer tok;
    HfstTransducer * left = new HfstTransducer(
        (yyvsp[(1) - (3)].label), hfst::internal_epsilon, hfst::pmatch::format);
    HfstTransducer * right = new HfstTransducer((yyvsp[(3) - (3)].label), tok, hfst::pmatch::format);
    HfstTransducer * construct = new HfstTransducer(
        hfst::internal_epsilon, hfst::internal_unknown, hfst::pmatch::format);
    left->compose(construct->repeat_star());
    left->compose(*right);
    (yyval.transducer) = left;
    delete construct; delete right;
    free((yyvsp[(1) - (3)].label)); free((yyvsp[(3) - (3)].label));
}
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1202 "pmatch_parse.yy"
    {
    HfstTokenizer tok;
    HfstTransducer * left = new HfstTransducer((yyvsp[(1) - (3)].label), tok, hfst::pmatch::format);
    HfstTransducer * right = new HfstTransducer(
        hfst::internal_epsilon, (yyvsp[(3) - (3)].label), hfst::pmatch::format);
    HfstTransducer * destroy = new HfstTransducer(
        hfst::internal_unknown, hfst::internal_epsilon, hfst::pmatch::format);
    left->compose(destroy->repeat_star());
    left->compose(*right);
    (yyval.transducer) = left;
    delete destroy; delete right;
    free((yyvsp[(1) - (3)].label)); free((yyvsp[(3) - (3)].label));
}
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 1215 "pmatch_parse.yy"
    { }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1216 "pmatch_parse.yy"
    { }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1217 "pmatch_parse.yy"
    { }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 1218 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::make_end_tag((yyvsp[(2) - (3)].label));
    hfst::pmatch::need_delimiters = true;
 }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 1222 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::make_end_tag((yyvsp[(2) - (3)].label));
    hfst::pmatch::need_delimiters = true;
 }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1229 "pmatch_parse.yy"
    { }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1230 "pmatch_parse.yy"
    { (yyval.label) = strdup(hfst::internal_epsilon.c_str()); }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1231 "pmatch_parse.yy"
    { (yyval.label) = strdup("@BOUNDARY@"); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 1235 "pmatch_parse.yy"
    { (yyval.transducer) = (yyvsp[(1) - (1)].transducer); hfst::pmatch::need_delimiters = true; }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1236 "pmatch_parse.yy"
    { }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 1237 "pmatch_parse.yy"
    { }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 1240 "pmatch_parse.yy"
    { }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 1241 "pmatch_parse.yy"
    { }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 1242 "pmatch_parse.yy"
    { }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 1243 "pmatch_parse.yy"
    { }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1246 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::pmatch::format);
    for(hfst::HfstTransducerVector::reverse_iterator it = (yyvsp[(2) - (3)].transducerVector)->rbegin();
        it != (yyvsp[(2) - (3)].transducerVector)->rend(); ++it) {
        (yyval.transducer)->disjunct(*it);
    }
    delete (yyvsp[(2) - (3)].transducerVector);
    // Zero the counter for making minimization
    // guards for disjuncted negative contexts
    hfst::pmatch::zero_minimization_guard();
}
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1259 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer(hfst::internal_epsilon, hfst::internal_epsilon, hfst::pmatch::format);
    for(hfst::HfstTransducerVector::reverse_iterator it = (yyvsp[(2) - (3)].transducerVector)->rbegin();
        it != (yyvsp[(2) - (3)].transducerVector)->rend(); ++it) {
        (yyval.transducer)->concatenate(*it);
    }
    delete (yyvsp[(2) - (3)].transducerVector);
}
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1269 "pmatch_parse.yy"
    {
    (yyval.transducerVector) = new hfst::HfstTransducerVector(1, *(yyvsp[(1) - (1)].transducer));
    delete (yyvsp[(1) - (1)].transducer);
}
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1273 "pmatch_parse.yy"
    {
    (yyvsp[(3) - (3)].transducerVector)->push_back(*(yyvsp[(1) - (3)].transducer));
    delete (yyvsp[(1) - (3)].transducer);
    (yyval.transducerVector) = (yyvsp[(3) - (3)].transducerVector);
}
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1279 "pmatch_parse.yy"
    {
    if (hfst::pmatch::functions.count((yyvsp[(1) - (3)].label)) == 0) {
        std::string errstring = "Function not defined: " + std::string((yyvsp[(1) - (3)].label));
        pmatcherror(errstring.c_str());
    }
    std::vector<string> & callee_args = hfst::pmatch::functions[(yyvsp[(1) - (3)].label)].args;
    if (callee_args.size() != (yyvsp[(2) - (3)].transducerVector)->size()) {
        std::string errstring = "Function " + std::string((yyvsp[(1) - (3)].label)) +
            " expected NN arguments, received NN";// + $2->size());
        pmatcherror(errstring.c_str());
    }
    std::map<std::string, HfstTransducer*> caller_args;
    for (int i = 0; i < (yyvsp[(2) - (3)].transducerVector)->size(); ++i) {
        caller_args[callee_args[i]] = new HfstTransducer((yyvsp[(2) - (3)].transducerVector)->at(i));
    }
    (yyval.transducer) = hfst::pmatch::functions[(yyvsp[(1) - (3)].label)].evaluate(caller_args);
    delete (yyvsp[(2) - (3)].transducerVector);
}
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1299 "pmatch_parse.yy"
    {
    (yyval.transducerVector) = new HfstTransducerVector();
    (yyval.transducerVector)->push_back(HfstTransducer(*(yyvsp[(1) - (1)].transducer)));
    delete (yyvsp[(1) - (1)].transducer);
}
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1304 "pmatch_parse.yy"
    {
    (yyvsp[(3) - (3)].transducerVector)->push_back(HfstTransducer(*(yyvsp[(1) - (3)].transducer)));
    delete (yyvsp[(1) - (3)].transducer);
}
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1308 "pmatch_parse.yy"
    { (yyval.transducerVector) = new HfstTransducerVector(); }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 1312 "pmatch_parse.yy"
    {
    if (hfst::pmatch::definitions.count((yyvsp[(1) - (1)].label)) == 1) {
        (yyval.transducer) = new HfstTransducer(* hfst::pmatch::definitions[(yyvsp[(1) - (1)].label)]);
    } else if (hfst::pmatch::def_insed_transducers.count((yyvsp[(1) - (1)].label)) == 0) {
        (yyval.transducer) = new HfstTransducer(* hfst::pmatch::def_insed_transducers[(yyvsp[(1) - (1)].label)]);
    } else {
        std::string errstring = "Unknown definition: " + std::string((yyvsp[(1) - (1)].label));
        free((yyvsp[(1) - (1)].label));
        pmatcherror(errstring.c_str());
    }
    free((yyvsp[(1) - (1)].label));
}
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1324 "pmatch_parse.yy"
    {
    HfstTokenizer tok;
    (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (1)].label), tok, hfst::pmatch::format);
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1329 "pmatch_parse.yy"
    {
    (yyval.transducer) = new HfstTransducer((yyvsp[(1) - (1)].label), hfst::pmatch::format);
    free((yyvsp[(1) - (1)].label));
  }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1335 "pmatch_parse.yy"
    {
    if (hfst::pmatch::functions.count((yyvsp[(2) - (5)].label)) == 0) {
        std::string errstring = "Function not defined: " + std::string((yyvsp[(2) - (5)].label));
        pmatcherror(errstring.c_str());
    }
    std::vector<string> & callee_args = hfst::pmatch::functions[(yyvsp[(2) - (5)].label)].args;
    std::vector<std::vector<std::string> > caller_strings =
        hfst::pmatch::read_args((yyvsp[(4) - (5)].label), callee_args.size());
    std::map<std::string, HfstTransducer*> caller_args;
    HfstTokenizer tok;
    (yyval.transducer) = new HfstTransducer(hfst::pmatch::format);
    for (std::vector<std::vector<std::string> >::iterator it =
             caller_strings.begin(); it != caller_strings.end(); ++it) {
        for (int i = 0; i < it->size(); ++i) {
            caller_args[callee_args[i]] = new HfstTransducer(it->at(i), tok, hfst::pmatch::format);
        }
        (yyval.transducer)->disjunct(*hfst::pmatch::functions[(yyvsp[(2) - (5)].label)].evaluate(caller_args));
        // Clean up the string transducers we allocated each time 
        for (std::map<std::string, HfstTransducer *>::iterator it = caller_args.begin();
             it != caller_args.end(); ++it) {
            delete it->second;
        }
        caller_args.clear();
    }
    (yyval.transducer)->minimize();
}
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1362 "pmatch_parse.yy"
    {
    if (!hfst::pmatch::flatten) {
        if(hfst::pmatch::definitions.count((yyvsp[(2) - (3)].label)) == 0) {
            hfst::pmatch::unsatisfied_insertions.insert((yyvsp[(2) - (3)].label));
        }
        char * Ins_trans = hfst::pmatch::get_Ins_transition((yyvsp[(2) - (3)].label));
        (yyval.transducer) = new HfstTransducer(
            Ins_trans, Ins_trans, hfst::pmatch::format);
        (yyval.transducer)->set_name(Ins_trans);
        free(Ins_trans);
        hfst::pmatch::inserted_transducers.insert((yyvsp[(2) - (3)].label));
        if (hfst::pmatch::verbose) {
            std::cerr << "inserting " << (yyvsp[(2) - (3)].label);
            if (hfst::pmatch::definitions.count((yyvsp[(2) - (3)].label)) != 0) {
                std::cerr << " with ";
                hfst::pmatch::print_size_info(hfst::pmatch::definitions[(yyvsp[(2) - (3)].label)]);
            } else {
                std::cerr << std::endl;
            }
            hfst::pmatch::used_definitions.insert((yyvsp[(2) - (3)].label));
        }
    } else if(hfst::pmatch::definitions.count((yyvsp[(2) - (3)].label)) == 1) {
        if (hfst::pmatch::verbose) {
            std::cerr << "including " <<
                hfst::pmatch::definitions[(yyvsp[(2) - (3)].label)]->get_name() << " with ";
            hfst::pmatch::print_size_info(hfst::pmatch::definitions[(yyvsp[(2) - (3)].label)]);
            hfst::pmatch::used_definitions.insert((yyvsp[(2) - (3)].label));
        }
        (yyval.transducer) = new HfstTransducer(* hfst::pmatch::definitions[(yyvsp[(2) - (3)].label)]);
    } else {
        // error?
        if (strlen((yyvsp[(2) - (3)].label)) == 0) {
            (yyval.transducer) = new HfstTransducer(hfst::pmatch::format);
        } else {
            (yyval.transducer) = new HfstTransducer((yyvsp[(2) - (3)].label), (yyvsp[(2) - (3)].label), hfst::pmatch::format);
        }
    }
    free((yyvsp[(2) - (3)].label));

}
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1405 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::add_pmatch_delimiters((yyvsp[(2) - (3)].transducer));
}
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1409 "pmatch_parse.yy"
    {
    HfstTransducer * rc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::RC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * rc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::RC_EXIT_SYMBOL, hfst::pmatch::format);
    rc_entry->concatenate(*(yyvsp[(2) - (3)].transducer));
    rc_entry->concatenate(*rc_exit);
    (yyval.transducer) = rc_entry;
    delete (yyvsp[(2) - (3)].transducer);
    delete rc_exit;
 }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1422 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::get_minimization_guard();
    HfstTransducer * nrc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NRC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * nrc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NRC_EXIT_SYMBOL, hfst::pmatch::format);
    nrc_entry->concatenate(*(yyvsp[(2) - (3)].transducer));
    nrc_entry->concatenate(*nrc_exit);
    nrc_entry->disjunct(HfstTransducer("@PMATCH_PASSTHROUGH@",
                                       hfst::internal_epsilon, hfst::pmatch::format));
    (yyval.transducer)->concatenate(*nrc_entry);
    delete (yyvsp[(2) - (3)].transducer); delete nrc_entry; delete nrc_exit;
 }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1437 "pmatch_parse.yy"
    {
    HfstTransducer * lc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * lc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_EXIT_SYMBOL, hfst::pmatch::format);
    lc_entry->concatenate((yyvsp[(2) - (3)].transducer)->reverse());
    lc_entry->concatenate(*lc_exit);
    (yyval.transducer) = lc_entry;
    delete (yyvsp[(2) - (3)].transducer); delete lc_exit;
 }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1449 "pmatch_parse.yy"
    {
    (yyval.transducer) = hfst::pmatch::get_minimization_guard();
    HfstTransducer * nlc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * nlc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_EXIT_SYMBOL, hfst::pmatch::format);
    nlc_entry->concatenate((yyvsp[(2) - (3)].transducer)->reverse());
    nlc_entry->concatenate(*nlc_exit);
    nlc_entry->disjunct(HfstTransducer("@PMATCH_PASSTHROUGH@",
                                       hfst::internal_epsilon, hfst::pmatch::format));
    (yyval.transducer)->concatenate(*nlc_entry);
    delete (yyvsp[(2) - (3)].transducer); delete nlc_entry; delete nlc_exit;
 }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1464 "pmatch_parse.yy"
    {
    PmatchAstNode * rc_entry =
        new PmatchAstNode(
            new HfstTransducer(hfst::internal_epsilon,
                               hfst::pmatch::RC_ENTRY_SYMBOL,
                               hfst::pmatch::format),
            (yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstConcatenate);
    (yyval.ast_node) = new PmatchAstNode(rc_entry,
                                         new HfstTransducer(
                                             hfst::internal_epsilon,
                                             hfst::pmatch::RC_EXIT_SYMBOL,
                                             hfst::pmatch::format),
                                         hfst::pmatch::AstConcatenate);
 }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1480 "pmatch_parse.yy"
    {
    PmatchAstNode * nrc_entry =
        new PmatchAstNode(
            new HfstTransducer(hfst::internal_epsilon,
                               hfst::pmatch::NRC_ENTRY_SYMBOL,
                               hfst::pmatch::format),
            (yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstConcatenate);
    PmatchAstNode * nrc_main_branch =
        new PmatchAstNode(nrc_entry,
                                        new HfstTransducer(
                                            hfst::internal_epsilon,
                                            hfst::pmatch::NRC_EXIT_SYMBOL,
                                            hfst::pmatch::format),
                                        hfst::pmatch::AstConcatenate);
    (yyval.ast_node) = new PmatchAstNode(
        nrc_main_branch,
        new HfstTransducer("@PMATCH_PASSTHROUGH@",
                           hfst::internal_epsilon, hfst::pmatch::format),
        hfst::pmatch::AstDisjunct);
 }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1502 "pmatch_parse.yy"
    {
    PmatchAstNode * reverse = new PmatchAstNode(
        (yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstReverse);
    
    HfstTransducer * lc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * lc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::LC_EXIT_SYMBOL, hfst::pmatch::format);

    PmatchAstNode * entry = new PmatchAstNode(
        lc_entry, reverse, hfst::pmatch::AstConcatenate);
    (yyval.ast_node) = new PmatchAstNode(
        entry, lc_exit, hfst::pmatch::AstConcatenate);
 }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1518 "pmatch_parse.yy"
    {
    PmatchAstNode * reverse = new PmatchAstNode(
        (yyvsp[(2) - (3)].ast_node), hfst::pmatch::AstReverse);
    
    HfstTransducer * nlc_entry = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_ENTRY_SYMBOL, hfst::pmatch::format);
    HfstTransducer * nlc_exit = new HfstTransducer(
        hfst::internal_epsilon, hfst::pmatch::NLC_EXIT_SYMBOL, hfst::pmatch::format);
    
    PmatchAstNode * entry = new PmatchAstNode(
        nlc_entry, reverse, hfst::pmatch::AstConcatenate);
    PmatchAstNode * main_branch = new PmatchAstNode(
        entry, nlc_exit, hfst::pmatch::AstConcatenate);
    
    (yyval.ast_node) = new PmatchAstNode(main_branch,
                           new HfstTransducer("@PMATCH_PASSTHROUGH@",
                                              hfst::internal_epsilon, hfst::pmatch::format),
                           hfst::pmatch::AstDisjunct);
}
    break;



/* Line 1806 of yacc.c  */
#line 4581 "pmatch_parse.cc"
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
#line 1539 "pmatch_parse.yy"



