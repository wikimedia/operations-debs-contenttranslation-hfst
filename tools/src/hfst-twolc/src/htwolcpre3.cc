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
#line 13 "htwolcpre3.yy"

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WINDOWS
#include <io.h>
#endif

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "io_src/InputReader.h"
#include "grammar_defs.h"
#include "HfstTwolcDefs.h"
#include "rule_src/TwolCGrammar.h"
#include "rule_src/OtherSymbolTransducer.h"
#include "alphabet_src/Alphabet.h"
#include "string_src/string_manipulation.h"
#include "commandline_src/CommandLine.h"
#include <cstdio>
#include "common_globals.h"

#ifdef DEBUG_TWOLC_3_GRAMMAR
#define YYDEBUG 1
#endif

  extern int yylineno;
  extern char * yytext;
  extern int yylineno;
  extern char * yytext;
  extern bool rules_start;
  void yyerror(const char * text );
  void semantic_error(const char * text);
  void warn(const char * warning );
  void message(const std::string &m);
  int yylex();
  int yyparse();
  
  bool silent = false;
  bool verbose = false;

#define YYERROR_VERBOSE 1

  // For reading input one byte at a time.
  size_t line_number = 1;
  InputReader input_reader(line_number);

  // The Alphabet of the grammar
  Alphabet alphabet;

  // A map storing named regular expressions (i.e. definitions).
  HandyMap<std::string,OtherSymbolTransducer> definition_map;

  // The grammar, which compiles rules, resolves conflicts and stores 
  // rule transducers.
  // TwolCGrammar grammar(true,true);
  TwolCGrammar * grammar;

  unsigned int get_number(const std::string &);
  unsigned int get_second_number(const std::string &s);
  std::string get_name(const std::string &s);



/* Line 268 of yacc.c  */
#line 137 "htwolcpre3.cc"

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
     COLON = 288,
     SEMI_COLON = 289,
     EQUALS = 290,
     CENTER_MARKER = 291,
     QUESTION_MARK = 292,
     EXCEPT = 293,
     RULE_NAME = 294,
     SYMBOL = 295,
     DEFINITION_NAME = 296,
     NUMBER = 297,
     NUMBER_RANGE = 298
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
#define COLON 288
#define SEMI_COLON 289
#define EQUALS 290
#define CENTER_MARKER 291
#define QUESTION_MARK 292
#define EXCEPT 293
#define RULE_NAME 294
#define SYMBOL 295
#define DEFINITION_NAME 296
#define NUMBER 297
#define NUMBER_RANGE 298




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 81 "htwolcpre3.yy"
 
  int symbol_number;
  OtherSymbolTransducer * regular_expression;
  char * value; 
  SymbolRange * symbol_range;
  SymbolPairVector * symbol_pair_range;
  op::OPERATOR rule_operator;



/* Line 293 of yacc.c  */
#line 270 "htwolcpre3.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 282 "htwolcpre3.cc"

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
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNRULES -- Number of states.  */
#define YYNSTATES  131

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    18,    20,
      23,    25,    27,    30,    32,    33,    36,    42,    48,    50,
      54,    58,    62,    64,    68,    72,    74,    76,    78,    80,
      82,    84,    86,    88,    90,    92,    93,    96,    97,   100,
     105,   109,   111,   115,   117,   120,   122,   125,   127,   128,
     131,   136,   138,   142,   146,   150,   154,   155,   158,   160,
     164,   168,   171,   174,   177,   180,   183,   186,   190,   194,
     195,   198,   199,   202,   207,   208,   211,   215,   219,   221,
     223,   227,   229
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    -1,    65,    47,    -1,    47,    -1,
      67,    48,    -1,    48,    -1,    69,    49,    -1,    49,    -1,
      71,    50,    -1,    50,    -1,    51,    -1,    52,    53,    -1,
      32,    -1,    -1,    53,    54,    -1,    39,    55,    60,    62,
      63,    -1,    39,    56,    61,    62,    63,    -1,    58,    -1,
      55,     6,    58,    -1,    17,    57,    15,    -1,    27,    75,
      26,    -1,    58,    -1,    57,     6,    58,    -1,    59,    33,
      59,    -1,    40,    -1,    37,    -1,    19,    -1,    20,    -1,
      18,    -1,    21,    -1,    23,    -1,    24,    -1,    22,    -1,
      25,    -1,    -1,    62,    64,    -1,    -1,    38,    62,    -1,
      75,    36,    75,    85,    -1,    66,    81,    85,    -1,    28,
      -1,    68,    79,    85,    -1,    29,    -1,    70,    78,    -1,
      30,    -1,    72,    73,    -1,    31,    -1,    -1,    73,    74,
      -1,    41,    35,    75,    85,    -1,    76,    -1,    75,     6,
      76,    -1,    75,     5,    76,    -1,    75,     4,    76,    -1,
      75,     3,    76,    -1,    -1,    76,    77,    -1,    82,    -1,
      77,    13,    42,    -1,    77,    13,    43,    -1,    77,     8,
      -1,    77,     7,    -1,    12,    77,    -1,    11,    77,    -1,
       9,    77,    -1,    10,    77,    -1,    17,    75,    15,    -1,
      16,    75,    14,    -1,    -1,    78,    80,    -1,    -1,    79,
      40,    -1,    40,    35,    79,    85,    -1,    -1,    81,    84,
      -1,    83,    33,    83,    -1,    41,    33,    41,    -1,    40,
      -1,    37,    -1,    40,    33,    40,    -1,    34,    -1,    85,
      34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   142,   143,   145,   146,   148,   149,   151,
     152,   154,   156,   158,   161,   162,   164,   181,   194,   196,
     202,   205,   208,   210,   217,   223,   225,   228,   230,   232,
     234,   237,   239,   241,   243,   247,   248,   255,   256,   259,
     267,   270,   273,   280,   283,   285,   288,   290,   293,   294,
     296,   303,   305,   310,   315,   320,   337,   338,   344,   346,
     351,   357,   359,   361,   363,   365,   367,   369,   371,   374,
     375,   378,   379,   386,   393,   394,   396,   458,   465,   467,
     470,   477,   478
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FREELY_INSERT", "DIFFERENCE",
  "INTERSECTION", "UNION", "PLUS", "STAR", "COMPLEMENT", "TERM_COMPLEMENT",
  "CONTAINMENT_ONCE", "CONTAINMENT", "POWER", "RIGHT_PARENTHESIS",
  "RIGHT_SQUARE_BRACKET", "LEFT_PARENTHESIS", "LEFT_SQUARE_BRACKET",
  "LEFT_RESTRICTION_ARROW", "LEFT_ARROW", "RIGHT_ARROW",
  "LEFT_RIGHT_ARROW", "RE_LEFT_RESTRICTION_ARROW", "RE_LEFT_ARROW",
  "RE_RIGHT_ARROW", "RE_LEFT_RIGHT_ARROW", "RE_RIGHT_SQUARE_BRACKET",
  "RE_LEFT_SQUARE_BRACKET", "ALPHABET_DECLARATION",
  "DIACRITICS_DECLARATION", "SETS_DECLARATION", "DEFINITION_DECLARATION",
  "RULES_DECLARATION", "COLON", "SEMI_COLON", "EQUALS", "CENTER_MARKER",
  "QUESTION_MARK", "EXCEPT", "RULE_NAME", "SYMBOL", "DEFINITION_NAME",
  "NUMBER", "NUMBER_RANGE", "$accept", "ALL", "GRAMMAR", "GRAMMAR1",
  "GRAMMAR2", "GRAMMAR3", "GRAMMAR4", "RULES", "RULES_HEADER", "RULE_LIST",
  "RULE", "RULE_CENTER", "RE_RULE_CENTER", "CENTER_LIST", "CENTER_PAIR",
  "CENTER_SYMBOL", "RULE_OPERATOR", "RE_RULE_OPERATOR", "RULE_CONTEXTS",
  "NEGATIVE_RULE_CONTEXTS", "RULE_CONTEXT", "ALPHABET", "ALPHABET_HEADER",
  "DIACRITICS", "DIACRITICS_HEADER", "SETS", "SETS_HEADER", "DEFINITIONS",
  "DEFINITION_HEADER", "DEFINITION_LIST", "DEFINITION",
  "REGULAR_EXPRESSION", "RE_LIST", "RE", "SET_LIST", "SYMBOL_LIST",
  "SET_DEFINITION", "ALPHABET_PAIR_LIST", "PAIR", "PAIR_SYMBOL",
  "ALPHABET_PAIR", "SEMI_COLON_LIST", 0
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
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    48,    48,    49,
      49,    50,    51,    52,    53,    53,    54,    54,    55,    55,
      55,    56,    57,    57,    58,    59,    59,    60,    60,    60,
      60,    61,    61,    61,    61,    62,    62,    63,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    73,
      74,    75,    75,    75,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      78,    79,    79,    80,    81,    81,    82,    82,    83,    83,
      84,    85,    85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     1,     2,     1,     0,     2,     5,     5,     1,     3,
       3,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     0,     2,     4,
       3,     1,     3,     1,     2,     1,     2,     1,     0,     2,
       4,     1,     3,     3,     3,     3,     0,     2,     1,     3,
       3,     2,     2,     2,     2,     2,     2,     3,     3,     0,
       2,     0,     2,     4,     0,     2,     3,     3,     1,     1,
       3,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    41,    43,    45,    47,    13,     0,     2,     4,     6,
       8,    10,    11,    14,     0,    74,     0,    71,     0,    69,
       0,    48,     1,    12,     3,     0,     5,     0,     7,    44,
       9,    46,     0,    15,    81,     0,    75,    40,    72,    42,
       0,    70,     0,    49,     0,    56,    26,    25,     0,     0,
      18,     0,     0,    82,    71,    56,     0,    22,     0,    51,
       0,    29,    27,    28,    30,    35,    33,    31,    32,    34,
      35,     0,    80,     0,     0,     0,    20,    56,    56,    56,
      56,    21,     0,     0,     0,     0,    56,    56,    79,    78,
       0,    57,    58,     0,    19,    56,    56,    24,    73,    50,
      23,    55,    54,    53,    52,    65,    66,    64,    63,     0,
       0,     0,    62,    61,     0,     0,    35,    16,    36,     0,
      17,    68,    67,    77,    59,    60,    76,    56,    56,     0,
      39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    23,
      33,    48,    49,    56,    50,    51,    65,    70,    95,   117,
     118,    14,    15,    16,    17,    18,    19,    20,    21,    31,
      43,   119,    59,    91,    29,    27,    41,    25,    92,    93,
      36,    37
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -69
static const yytype_int8 yypact[] =
{
      64,   -69,   -69,   -69,   -69,   -69,    13,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,    74,   -69,    -2,   -69,    31,   -69,
       7,   -69,   -69,     2,   -69,   -19,   -69,   -18,   -69,    33,
     -69,    29,    34,   -69,   -69,    21,   -69,    45,   -69,    45,
      46,   -69,    48,   -69,     0,   -69,   -69,   -69,    47,    86,
     -69,    49,    57,   -69,   -69,   -69,    -3,   -69,    54,    15,
       0,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,     0,   -69,   -18,    30,     0,   -69,   -69,   -69,   -69,
     -69,   -69,    15,    15,    15,    15,   -69,   -69,   -69,   -69,
      52,     1,   -69,    53,   -69,     6,     6,   -69,    45,    45,
     -69,    15,    15,    15,    15,    87,    87,    87,    87,    85,
      72,    60,   -69,   -69,   -38,    32,   -69,   -69,   -69,    14,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,    10,   -69,    30,
      45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   -69,    84,    91,    98,    97,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -37,    51,   -69,   -69,   -68,    27,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -44,    35,    36,   -69,    70,   -69,   -69,   -69,    11,
     -69,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -39
static const yytype_int16 yytable[] =
{
      39,    58,    96,    75,   124,   125,   -37,    57,   112,   113,
     -38,    74,    76,    22,   114,    34,    34,    77,    78,    79,
      80,    35,    38,    94,    82,    83,    84,    85,     3,     4,
       5,    86,    87,    77,    78,    79,    80,    46,   100,     5,
      47,    32,   109,   110,   116,   -37,    98,    99,   127,   -38,
     128,    44,    88,    60,    52,    89,    90,    77,    78,    79,
      80,    45,     4,     5,    34,    61,    62,    63,    64,    88,
      42,    46,    89,    40,    47,    77,    78,    79,    80,    53,
      81,    54,    71,    55,   129,   111,   115,   122,    77,    78,
      79,    80,     1,     2,     3,     4,     5,    72,    24,   121,
     114,   123,   130,     2,     3,     4,     5,    26,    66,    67,
      68,    69,   101,   102,   103,   104,    28,    30,   105,   106,
     107,   108,    97,   120,    73,     0,   126
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-69))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      27,    45,    70,     6,    42,    43,     0,    44,     7,     8,
       0,    55,    15,     0,    13,    34,    34,     3,     4,     5,
       6,    40,    40,    60,     9,    10,    11,    12,    30,    31,
      32,    16,    17,     3,     4,     5,     6,    37,    75,    32,
      40,    39,    86,    87,    38,    39,    73,    74,   116,    39,
      36,    17,    37,     6,    33,    40,    41,     3,     4,     5,
       6,    27,    31,    32,    34,    18,    19,    20,    21,    37,
      41,    37,    40,    40,    40,     3,     4,     5,     6,    34,
      26,    35,    33,    35,   128,    33,    33,    15,     3,     4,
       5,     6,    28,    29,    30,    31,    32,    40,    14,    14,
      13,    41,   129,    29,    30,    31,    32,    16,    22,    23,
      24,    25,    77,    78,    79,    80,    18,    20,    82,    83,
      84,    85,    71,    96,    54,    -1,   115
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    29,    30,    31,    32,    45,    46,    47,    48,
      49,    50,    51,    52,    65,    66,    67,    68,    69,    70,
      71,    72,     0,    53,    47,    81,    48,    79,    49,    78,
      50,    73,    39,    54,    34,    40,    84,    85,    40,    85,
      40,    80,    41,    74,    17,    27,    37,    40,    55,    56,
      58,    59,    33,    34,    35,    35,    57,    58,    75,    76,
       6,    18,    19,    20,    21,    60,    22,    23,    24,    25,
      61,    33,    40,    79,    75,     6,    15,     3,     4,     5,
       6,    26,     9,    10,    11,    12,    16,    17,    37,    40,
      41,    77,    82,    83,    58,    62,    62,    59,    85,    85,
      58,    76,    76,    76,    76,    77,    77,    77,    77,    75,
      75,    33,     7,     8,    13,    33,    38,    63,    64,    75,
      63,    14,    15,    41,    42,    43,    83,    62,    36,    75,
      85
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
#line 139 "htwolcpre3.yy"
    {}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 159 "htwolcpre3.yy"
    { message("Reading rules and compiling their contexts and centers."); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 165 "htwolcpre3.yy"
    { 
  // Subtract negative contexts from positive contexts.
  (yyvsp[(4) - (5)].regular_expression)->apply(&HfstTransducer::subtract,*(yyvsp[(5) - (5)].regular_expression));

  if (verbose)
    { message(std::string("Processing: ")+ get_name((yyvsp[(1) - (5)].value))); }

  if ((yyvsp[(2) - (5)].symbol_pair_range)->size() == 1)
    { grammar->add_rule((yyvsp[(1) - (5)].value),(*(yyvsp[(2) - (5)].symbol_pair_range))[0],(yyvsp[(3) - (5)].rule_operator),OtherSymbolTransducerVector(1,*(yyvsp[(4) - (5)].regular_expression))); }
  else
    { grammar->add_rule((yyvsp[(1) - (5)].value),*(yyvsp[(2) - (5)].symbol_pair_range),(yyvsp[(3) - (5)].rule_operator),OtherSymbolTransducerVector(1,*(yyvsp[(4) - (5)].regular_expression))); }
  free((yyvsp[(1) - (5)].value));
  delete (yyvsp[(2) - (5)].symbol_pair_range);
  delete (yyvsp[(4) - (5)].regular_expression);
  delete (yyvsp[(5) - (5)].regular_expression);
}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 183 "htwolcpre3.yy"
    {
  // Subtract negative contexts from positive contexts.
  (yyvsp[(4) - (5)].regular_expression)->apply(&HfstTransducer::subtract,*(yyvsp[(5) - (5)].regular_expression));

  grammar->add_rule((yyvsp[(1) - (5)].value),*(yyvsp[(2) - (5)].regular_expression),(yyvsp[(3) - (5)].rule_operator),OtherSymbolTransducerVector(1,*(yyvsp[(4) - (5)].regular_expression)));
  free((yyvsp[(1) - (5)].value));
  delete (yyvsp[(2) - (5)].regular_expression);
  delete (yyvsp[(4) - (5)].regular_expression);
  delete (yyvsp[(5) - (5)].regular_expression);
}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 195 "htwolcpre3.yy"
    { (yyval.symbol_pair_range) = (yyvsp[(1) - (1)].symbol_pair_range); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 197 "htwolcpre3.yy"
    {
  (yyval.symbol_pair_range) = (yyvsp[(1) - (3)].symbol_pair_range);
  (yyval.symbol_pair_range)->push_back(*(yyvsp[(3) - (3)].symbol_pair_range)->begin());
  delete (yyvsp[(3) - (3)].symbol_pair_range);
}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 203 "htwolcpre3.yy"
    { (yyval.symbol_pair_range) = (yyvsp[(2) - (3)].symbol_pair_range); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 206 "htwolcpre3.yy"
    { (yyval.regular_expression) = (yyvsp[(2) - (3)].regular_expression); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 209 "htwolcpre3.yy"
    { (yyval.symbol_pair_range) = (yyvsp[(1) - (1)].symbol_pair_range); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 211 "htwolcpre3.yy"
    { 
  (yyval.symbol_pair_range) = (yyvsp[(1) - (3)].symbol_pair_range);
  (yyval.symbol_pair_range)->push_back(*(yyvsp[(3) - (3)].symbol_pair_range)->begin());
  delete (yyvsp[(3) - (3)].symbol_pair_range);
}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 218 "htwolcpre3.yy"
    { 
  (yyval.symbol_pair_range) = alphabet.get_symbol_pair_vector(SymbolPair((yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value))); 
  free((yyvsp[(1) - (3)].value)); free((yyvsp[(3) - (3)].value));
}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 224 "htwolcpre3.yy"
    { (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 226 "htwolcpre3.yy"
    { (yyval.value) = string_copy("__HFST_TWOLC_?"); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 229 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::LEFT; }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 231 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::RIGHT; }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 233 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::NOT_LEFT; }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 235 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::LEFT_RIGHT; }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 238 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::RE_LEFT; }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 240 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::RE_RIGHT; }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 242 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::RE_NOT_LEFT; }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 244 "htwolcpre3.yy"
    { (yyval.rule_operator) = op::RE_LEFT_RIGHT; }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 247 "htwolcpre3.yy"
    { (yyval.regular_expression) = new OtherSymbolTransducer(); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 249 "htwolcpre3.yy"
    { 
  (yyval.regular_expression) = &(yyvsp[(1) - (2)].regular_expression)->apply(&HfstTransducer::disjunct,*(yyvsp[(2) - (2)].regular_expression));
  delete (yyvsp[(2) - (2)].regular_expression);
}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 255 "htwolcpre3.yy"
    { (yyval.regular_expression) = new OtherSymbolTransducer(); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 257 "htwolcpre3.yy"
    { (yyval.regular_expression) = (yyvsp[(2) - (2)].regular_expression); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 261 "htwolcpre3.yy"
    {
  (yyval.regular_expression) = new OtherSymbolTransducer(OtherSymbolTransducer::get_context(*(yyvsp[(1) - (4)].regular_expression),*(yyvsp[(3) - (4)].regular_expression)));
  delete (yyvsp[(1) - (4)].regular_expression);
  delete (yyvsp[(3) - (4)].regular_expression);
}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 268 "htwolcpre3.yy"
    { alphabet.alphabet_done(); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 271 "htwolcpre3.yy"
    { message("Reading alphabet."); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 274 "htwolcpre3.yy"
    { 
  grammar->define_diacritics(*(yyvsp[(2) - (3)].symbol_range));
  alphabet.define_diacritics(*(yyvsp[(2) - (3)].symbol_range));
  delete (yyvsp[(2) - (3)].symbol_range);
}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 281 "htwolcpre3.yy"
    { message("Reading diacritics."); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 286 "htwolcpre3.yy"
    { message("Reading sets."); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 291 "htwolcpre3.yy"
    { message("Reading and compiling definitions."); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 297 "htwolcpre3.yy"
    {
  definition_map[(yyvsp[(1) - (4)].value)] = *(yyvsp[(3) - (4)].regular_expression);
  free((yyvsp[(1) - (4)].value));
  delete (yyvsp[(3) - (4)].regular_expression);
}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 304 "htwolcpre3.yy"
    { (yyval.regular_expression) = (yyvsp[(1) - (1)].regular_expression); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 306 "htwolcpre3.yy"
    { 
  (yyval.regular_expression) = &(yyvsp[(1) - (3)].regular_expression)->apply(&HfstTransducer::disjunct,*(yyvsp[(3) - (3)].regular_expression));
  delete (yyvsp[(3) - (3)].regular_expression);
}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 311 "htwolcpre3.yy"
    {
  (yyval.regular_expression) = &(yyvsp[(1) - (3)].regular_expression)->apply(&HfstTransducer::intersect,*(yyvsp[(3) - (3)].regular_expression));
  delete (yyvsp[(3) - (3)].regular_expression);
}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 316 "htwolcpre3.yy"
    {
  (yyval.regular_expression) = &(yyvsp[(1) - (3)].regular_expression)->apply(&HfstTransducer::subtract,*(yyvsp[(3) - (3)].regular_expression));
  delete (yyvsp[(3) - (3)].regular_expression);
}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 321 "htwolcpre3.yy"
    {
  (yyvsp[(1) - (3)].regular_expression)->apply
    (&HfstTransducer::insert_freely,
     SymbolPair(TWOLC_FREELY_INSERT,TWOLC_FREELY_INSERT),
     true);
  (yyvsp[(1) - (3)].regular_expression)->apply
    (&HfstTransducer::substitute,
     SymbolPair(TWOLC_FREELY_INSERT,TWOLC_FREELY_INSERT),
     *(yyvsp[(3) - (3)].regular_expression),
     true);
  (yyval.regular_expression) = (yyvsp[(1) - (3)].regular_expression);

  delete (yyvsp[(3) - (3)].regular_expression);
}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 337 "htwolcpre3.yy"
    { (yyval.regular_expression) = new OtherSymbolTransducer(HFST_EPSILON); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 339 "htwolcpre3.yy"
    { 
  (yyval.regular_expression) = &(yyvsp[(1) - (2)].regular_expression)->apply(&HfstTransducer::concatenate,*(yyvsp[(2) - (2)].regular_expression));
  delete (yyvsp[(2) - (2)].regular_expression);
}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 345 "htwolcpre3.yy"
    { (yyval.regular_expression) = (yyvsp[(1) - (1)].regular_expression); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 347 "htwolcpre3.yy"
    { 
  (yyval.regular_expression) = &(yyvsp[(1) - (3)].regular_expression)->apply(&HfstTransducer::repeat_n,get_number((yyvsp[(3) - (3)].value)));
  free((yyvsp[(3) - (3)].value));
}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 352 "htwolcpre3.yy"
    { 
  (yyval.regular_expression) = &(yyvsp[(1) - (3)].regular_expression)->apply(&HfstTransducer::repeat_n_to_k,
          get_number((yyvsp[(3) - (3)].value)),get_second_number((yyvsp[(3) - (3)].value)));
  free((yyvsp[(3) - (3)].value));
}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 358 "htwolcpre3.yy"
    { (yyval.regular_expression) = &(yyvsp[(1) - (2)].regular_expression)->apply(&HfstTransducer::repeat_star); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 360 "htwolcpre3.yy"
    { (yyval.regular_expression) = &(yyvsp[(1) - (2)].regular_expression)->apply(&HfstTransducer::repeat_plus); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 362 "htwolcpre3.yy"
    { (yyval.regular_expression) = &(yyvsp[(2) - (2)].regular_expression)->contained(); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 364 "htwolcpre3.yy"
    { (yyval.regular_expression) = &(yyvsp[(2) - (2)].regular_expression)->contained_once(); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 366 "htwolcpre3.yy"
    { (yyval.regular_expression) = &(yyvsp[(2) - (2)].regular_expression)->negated(); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 368 "htwolcpre3.yy"
    { (yyval.regular_expression) = &(yyvsp[(2) - (2)].regular_expression)->term_complemented(); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 370 "htwolcpre3.yy"
    { (yyval.regular_expression) = (yyvsp[(2) - (3)].regular_expression); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 372 "htwolcpre3.yy"
    { (yyval.regular_expression) = &(yyvsp[(2) - (3)].regular_expression)->apply(&HfstTransducer::optionalize); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 378 "htwolcpre3.yy"
    { (yyval.symbol_range) = new SymbolRange; }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 380 "htwolcpre3.yy"
    {
  (yyvsp[(1) - (2)].symbol_range)->push_back((yyvsp[(2) - (2)].value));
  (yyval.symbol_range) = (yyvsp[(1) - (2)].symbol_range);
  free((yyvsp[(2) - (2)].value));
}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 387 "htwolcpre3.yy"
    {
  alphabet.define_set((yyvsp[(1) - (4)].value),*(yyvsp[(3) - (4)].symbol_range));
  free((yyvsp[(1) - (4)].value));
  delete (yyvsp[(3) - (4)].symbol_range);
}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 397 "htwolcpre3.yy"
    { 
  if (std::string("__HFST_TWOLC_0") == (yyvsp[(1) - (3)].value) and 
      std::string("__HFST_TWOLC_0") == (yyvsp[(3) - (3)].value))
    { (yyval.regular_expression) = new OtherSymbolTransducer(HFST_EPSILON); }
  else if (std::string("__HFST_TWOLC_#") == (yyvsp[(1) - (3)].value))
    { 
      // __HFST_TWOLC_# corresponds to the #-symbol in grammars. It should
      // be split into an absolute word boundary "__HFST_TWOLC_.#." and a
      // relative word boundary "#". On the surface the relative word-boundary
      // may correspond to whatever it did correspond to in the rule file.
      // The absolute word boundary surface realization is treated the same as
      // the surface realizations of other absolute word boundaries.
      OtherSymbolTransducer wb = 
    alphabet.get_transducer(SymbolPair
                ("__HFST_TWOLC_.#.","__HFST_TWOLC_.#."));
      OtherSymbolTransducer alt_wb = 
    alphabet.get_transducer
    (SymbolPair
     ("#",(yyvsp[(3) - (3)].value) == std::string("__HFST_TWOLC_#") ? "#" : (yyvsp[(3) - (3)].value)));      
      wb.apply(&HfstTransducer::disjunct,alt_wb);

      (yyval.regular_expression) = new OtherSymbolTransducer(wb);
    }  
  else
    { (yyval.regular_expression) = new OtherSymbolTransducer
    (alphabet.get_transducer(SymbolPair((yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value)))); 
      if (alphabet.is_empty_pair(SymbolPair((yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value))))
    {
      std::string error;
      if (std::string((yyvsp[(1) - (3)].value)) == std::string((yyvsp[(3) - (3)].value)))
        {
          std::string symbol = Rule::get_print_name((yyvsp[(1) - (3)].value));

          error = std::string("The pair set ") + symbol + " is empty.";
        }
      else
        {
          std::string symbol1 = Rule::get_print_name((yyvsp[(1) - (3)].value));
          std::string symbol2 = Rule::get_print_name((yyvsp[(3) - (3)].value));

          error = std::string("The pair set ") + symbol1 + ":" + symbol2 + 
        " is empty.";
        }
      error +=  std::string("\n\n") +

        "Note that a pair set X:Y can be empty, even if the sets X and\n"+
            "Y are non-empty, since every symbol pair has to be declared in\n"+
        "the alphabet or it has to be the center of a rule, or be in\n"  +
        "the context of a rule or result from substituting values for\n" +
        "variables in a rule with variables.\n\n" +

        "Compilation is terminated because a rule context, definition\n" + 
        "or rule center becomes empty.\n\n";

      semantic_error(error.c_str());
    }
    }

  free((yyvsp[(1) - (3)].value));
  free((yyvsp[(3) - (3)].value));
}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 459 "htwolcpre3.yy"
    { 
  (yyval.regular_expression) = new OtherSymbolTransducer(definition_map[(yyvsp[(1) - (3)].value)]); 
  free((yyvsp[(1) - (3)].value));
  free((yyvsp[(3) - (3)].value));
}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 466 "htwolcpre3.yy"
    { (yyval.value) = (yyvsp[(1) - (1)].value); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 468 "htwolcpre3.yy"
    { (yyval.value) = string_copy("__HFST_TWOLC_?"); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 471 "htwolcpre3.yy"
    { 
  alphabet.define_alphabet_pair(SymbolPair((yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value)));
  free((yyvsp[(1) - (3)].value));
  free((yyvsp[(3) - (3)].value));
}
    break;



/* Line 1806 of yacc.c  */
#line 2215 "htwolcpre3.cc"
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
#line 480 "htwolcpre3.yy"


// Print warning.
void warn(const char * warning) 
{ 
#ifdef DEBUG_TWOLC_3_GRAMMAR
  std::cerr << warning << std::endl;
#else
  (void)warning; 
#endif
}

// Print error messge and exit 1.
void yyerror(const char * text) 
{ 
  (void)text;
  input_reader.error(text);
  exit(1); 
}

// Print error messge and exit 1.
void semantic_error(const char * text) 
{ 
  std::cerr << std::endl << "Error: " << text << std::endl;
  exit(1);
}

unsigned int get_number(const std::string &s)
{
  // skip yhe prefix "HFST_TWOLC_NUMBER=".
  std::istringstream i(s.substr(20));
  unsigned int number;
  i >> number;
  return number;
}

unsigned int get_second_number(const std::string &s)
{
  // skip yhe prefix "HFST_TWOLC_NUMBER=".
  std::istringstream i(s.substr(s.find(',')+1));
  unsigned int number;
  i >> number;
  return number;
}

void message(const std::string &m)
{
  if (not silent)
    { std::cerr << m << std::endl; }
}

std::string get_name(const std::string &s)
{
  std::string ss = s;
  size_t pos = 0;
  while ((pos = ss.find("__HFST_TWOLC_RULE_NAME=")) != std::string::npos)
    { ss.replace(pos,std::string("__HFST_TWOLC_RULE_NAME=").size(),""); }
  while ((pos = ss.find("__HFST_TWOLC_SPACE")) != std::string::npos)
    { ss.replace(pos,std::string("__HFST_TWOLC_SPACE").size()," "); }
  return ss;
}

int main(int argc, char * argv[])
{
#ifdef WINDOWS
  _setmode(0, _O_BINARY);
  _setmode(1, _O_BINARY);
#endif

#ifdef DEBUG_TWOLC_3_GRAMMAR
  yydebug = 1;
#endif

  try 
    {
      CommandLine command_line(argc,argv);
      if (command_line.help or command_line.usage or command_line.version)
    { exit(0); }
      if (command_line.has_debug_file)
    { input_reader.set_input(command_line.set_input_file()); }
      else
    { input_reader.set_input(std::cin); }
      
      OtherSymbolTransducer::set_transducer_type(command_line.format);
      silent = command_line.be_quiet;
      verbose = command_line.be_verbose;
      
      TwolCGrammar twolc_grammar(command_line.be_quiet,
				 command_line.be_verbose,
				 command_line.resolve_left_conflicts,
				 command_line.resolve_right_conflicts);
      grammar = &twolc_grammar;
      int exit_code = yyparse();
      if (exit_code != 0)
    { exit(exit_code); }
      
      message("Compiling and storing rules.");
      if (not command_line.has_output_file)
    {
      HfstOutputStream stdout_(command_line.format);
      grammar->compile_and_store(stdout_);
    }
      else
    {
      HfstOutputStream out
        (command_line.output_file_name,command_line.format);
      grammar->compile_and_store(out);
    }
      exit(0);
    }
  catch (const HfstException e)
    {
      std::cerr << "This is an hfst interface bug:" << std::endl
        << e() << std::endl;
      exit(1);
    }
  catch (const char * s)
    {
      std::cerr << "This is an a bug probably from sfst:" << std::endl
        << s << std::endl;
      exit(1);
    }
}



