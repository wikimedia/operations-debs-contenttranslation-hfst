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
#line 13 "htwolcpre1.yy"

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WINDOWS
#include <io.h>
#endif

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "string_src/string_manipulation.h"
#include "io_src/InputReader.h"
#include "grammar_defs.h"
#include "variable_src/RuleSymbolVector.h"
#include "variable_src/RuleVariables.h"
#include "commandline_src/CommandLine.h"
#include "common_globals.h"

  extern int yylineno;
  extern char * yytext;
  extern int yylineno;
  extern char * yytext;
  extern bool regexp_start;
  extern bool rules_start;
  void yyerror(const char * text );
  void warn(const char * warning );
  int yylex();
  int yyparse();
  void reduce_queue(bool variable_symbol=false);
  void set_variable_values(void);
  void reduce_symbol_pair(bool no_definitions = false);
  void increase_line_counter(void);
  std::string &get_symbol_queue_front(void);
  void pop_symbol_queue(void);

#define YYERROR_VERBOSE 1

  // For displaying the line number in error messages and warnings.
  size_t line_number = 1;
 
  // For reading input one byte at a time.
  InputReader input_reader(line_number);

  // For keeping track of values of variables.
  VariableValueMap variable_value_map;
  
  // For storing variable constructions of rules.
  RuleVariables rule_variables;

  // For storing the string representation of rules and replacing
  // rule variables by their values.
  RuleSymbolVector rule_symbol_vector(variable_value_map);

  // The latest symbol that was read is always the last element of this queue.
  HandyDeque<std::string> symbol_queue;

  // Stores symbol set names.
  HandySet<std::string> sets;

  // Stores definition names.
  HandySet<std::string> definitions;

  // Stores set names in "__HFST_TWOLC_SET_NAME=X" format and the set symbols.
  HandyMap<std::string,std::vector<std::string> > set_symbols;

  // The name of the lates set which was defined.
  std::string set_name;
  
  // Pointer to the latest symbol set which is being defined.
  std::vector<std::string> latest_set;

  // Tells whether we are inside a ( .. ). For variable rules.
  bool inside_parenthesis = false;

  // For temporarily storing a rule variable and its values
  StringVector variable_vector;

  // Queue for rule-matchers.
  HandyDeque<Matcher> matcher_queue;


/* Line 268 of yacc.c  */
#line 155 "htwolcpre1.cc"

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

/* Line 293 of yacc.c  */
#line 99 "htwolcpre1.yy"
 int symbol_number; 


/* Line 293 of yacc.c  */
#line 301 "htwolcpre1.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 313 "htwolcpre1.cc"

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
#define YYFINAL  26
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   194

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    18,    20,
      23,    25,    28,    30,    32,    35,    36,    39,    46,    52,
      54,    56,    60,    64,    68,    72,    74,    78,    80,    82,
      84,    86,    88,    90,    92,    94,    95,    98,    99,   102,
     104,   106,   108,   109,   114,   115,   119,   121,   125,   128,
     129,   132,   138,   142,   144,   145,   148,   152,   156,   160,
     163,   166,   167,   170,   175,   177,   181,   185,   189,   193,
     194,   197,   199,   203,   206,   209,   212,   215,   218,   221,
     225,   229,   233,   234,   237,   238,   241,   242,   245,   247,
     249,   254,   256,   258,   259,   262,   265,   268,   272,   274,
     276,   280,   282,   284,   286,   288,   290,   291,   294,   296
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      55,     0,    -1,    56,    -1,    82,    57,    -1,    57,    -1,
      83,    58,    -1,    58,    -1,    84,    59,    -1,    59,    -1,
      85,    60,    -1,    60,    -1,    86,    61,    -1,    61,    -1,
      62,    -1,    34,    63,    -1,    -1,    63,    64,    -1,    65,
      66,    69,    71,    72,    75,    -1,    65,    67,    70,    71,
      72,    -1,    48,    -1,   101,    -1,    66,     6,   102,    -1,
      17,    68,    15,    -1,    19,    68,    18,    -1,    29,    89,
      28,    -1,   102,    -1,    68,     6,   102,    -1,    21,    -1,
      22,    -1,    20,    -1,    23,    -1,    25,    -1,    26,    -1,
      24,    -1,    27,    -1,    -1,    71,    74,    -1,    -1,    53,
      71,    -1,    38,    -1,    39,    -1,    40,    -1,    -1,    89,
      47,    89,   106,    -1,    -1,    37,    76,   106,    -1,    77,
      -1,    76,    42,    77,    -1,    78,    73,    -1,    -1,    78,
      79,    -1,    80,    41,    16,    81,    14,    -1,    80,    41,
      80,    -1,   104,    -1,    -1,    81,    80,    -1,    30,   100,
     106,    -1,    31,    94,   106,    -1,    35,   105,   106,    -1,
      32,    92,    -1,    33,    87,    -1,    -1,    87,    88,    -1,
      99,    46,    89,   106,    -1,    90,    -1,    89,     6,    90,
      -1,    89,     5,    90,    -1,    89,     4,    90,    -1,    89,
       3,    90,    -1,    -1,    90,    91,    -1,   101,    -1,    91,
      13,    51,    -1,    91,     8,    -1,    91,     7,    -1,    12,
      91,    -1,    11,    91,    -1,     9,    91,    -1,    10,    91,
      -1,    17,    89,    15,    -1,    19,    89,    18,    -1,    16,
      89,    14,    -1,    -1,    92,    97,    -1,    -1,    93,    95,
      -1,    -1,    94,    96,    -1,   104,    -1,   104,    -1,    98,
      46,    93,   106,    -1,    44,    -1,    44,    -1,    -1,   100,
     102,    -1,   103,    43,    -1,    36,   104,    -1,   103,    36,
     104,    -1,    43,    -1,   104,    -1,   103,    36,   104,    -1,
     104,    -1,    49,    -1,    50,    -1,    44,    -1,    51,    -1,
      -1,   105,   104,    -1,    45,    -1,   106,    45,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   147,   147,   150,   151,   153,   154,   156,   157,   159,
     160,   162,   163,   165,   167,   169,   170,   172,   206,   217,
     223,   224,   225,   226,   228,   230,   231,   233,   234,   235,
     236,   238,   239,   240,   241,   243,   244,   246,   247,   249,
     251,   253,   256,   259,   262,   263,   265,   266,   268,   275,
     276,   279,   281,   284,   287,   288,   290,   292,   294,   296,
     298,   300,   301,   303,   305,   306,   307,   308,   309,   311,
     312,   314,   315,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   331,   332,   334,   335,   337,   338,   340,   365,
     368,   375,   386,   396,   397,   400,   407,   416,   423,   432,
     447,   454,   466,   467,   470,   471,   474,   475,   478,   479
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
  "RIGHT_CURLY_BRACKET", "LEFT_CURLY_BRACKET", "LEFT_RESTRICTION_ARROW",
  "LEFT_ARROW", "RIGHT_ARROW", "LEFT_RIGHT_ARROW",
  "RE_LEFT_RESTRICTION_ARROW", "RE_LEFT_ARROW", "RE_RIGHT_ARROW",
  "RE_LEFT_RIGHT_ARROW", "RE_RIGHT_SQUARE_BRACKET",
  "RE_LEFT_SQUARE_BRACKET", "ALPHABET_DECLARATION",
  "DIACRITICS_DECLARATION", "SETS_DECLARATION", "DEFINITION_DECLARATION",
  "RULES_DECLARATION", "VARIABLE_DECLARATION", "COLON", "WHERE",
  "MATCHED_MATCHER", "MIXED_MATCHER", "FREELY_MATCHER", "IN", "AND",
  "COLON_SPACE", "SYMBOL_SPACE", "SEMI_COLON", "EQUALS", "CENTER_MARKER",
  "RULE_NAME", "SYMBOL", "NUMBER", "NUMBER_SPACE", "QUESTION_MARK",
  "EXCEPT", "$accept", "ALL", "GRAMMAR", "GRAMMAR1", "GRAMMAR2",
  "GRAMMAR3", "GRAMMAR4", "GRAMMAR5", "RULES", "RULE_LIST", "RULE",
  "RULE_NAME_DECL", "RULE_CENTER", "RE_RULE_CENTER", "CENTER_LIST",
  "RULE_OPERATOR", "RE_RULE_OPERATOR", "RULE_CONTEXTS",
  "NEGATIVE_RULE_CONTEXTS", "MATCHER", "RULE_CONTEXT", "RULE_VARIABLES",
  "RULE_VARIABLE_BLOCKS", "RULE_VARIABLE_BLOCK",
  "RULE_VARIABLE_INITIALIZATION_LIST", "RULE_VARIABLE_INITIALIZATION",
  "VAR_SYMBOL", "VAR_SYMBOL_LIST", "ALPHABET", "DIACRITICS", "VARIABLES",
  "SETS", "DEFINITIONS", "DEFINITION_LIST", "DEFINITION",
  "REGULAR_EXPRESSION", "RE_LIST", "RE", "SET_LIST", "SYMBOL_LIST",
  "DIACRITIC_LIST", "SET_SYMBOL", "DIACRITIC_SYMBOL", "SET_DEFINITION",
  "SET_NAME", "DEFINITION_NAME", "ALPHABET_PAIR_LIST", "PAIR",
  "ALPHABET_PAIR", "GRAMMAR_SYMBOL", "GRAMMAR_SYMBOL_SPACE",
  "VARIABLE_LIST", "SEMI_COLON_LIST", 0
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
     305,   306,   307,   308
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    58,    58,    59,
      59,    60,    60,    61,    62,    63,    63,    64,    64,    65,
      66,    66,    66,    66,    67,    68,    68,    69,    69,    69,
      69,    70,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    73,    73,    74,    75,    75,    76,    76,    77,    78,
      78,    79,    79,    80,    81,    81,    82,    83,    84,    85,
      86,    87,    87,    88,    89,    89,    89,    89,    89,    90,
      90,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    92,    93,    93,    94,    94,    95,    96,
      97,    98,    99,   100,   100,   101,   101,   101,   101,   101,
     102,   102,   103,   103,   104,   104,   105,   105,   106,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     1,     2,     0,     2,     6,     5,     1,
       1,     3,     3,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     0,     2,     1,
       1,     1,     0,     4,     0,     3,     1,     3,     2,     0,
       2,     5,     3,     1,     0,     2,     3,     3,     3,     2,
       2,     0,     2,     4,     1,     3,     3,     3,     3,     0,
       2,     1,     3,     2,     2,     2,     2,     2,     2,     3,
       3,     3,     0,     2,     0,     2,     0,     2,     1,     1,
       4,     1,     1,     0,     2,     2,     2,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     0,     2,     1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    93,    86,    82,    61,    15,   106,     0,     2,     4,
       6,     8,    10,    12,    13,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    14,     0,     1,     3,     5,     7,
       9,    11,   104,   108,   102,   103,   105,    94,     0,   101,
      56,    87,    89,    57,    91,    83,     0,    92,    62,     0,
      19,    16,     0,   107,    58,     0,   109,    84,    69,     0,
       0,    69,     0,    98,     0,     0,    20,     0,    99,   100,
       0,     0,    64,     0,    25,     0,     0,    96,     0,    29,
      27,    28,    30,    35,    33,    31,    32,    34,    35,     0,
      95,    85,    88,    90,    69,    69,    69,    69,    63,     0,
       0,     0,     0,    69,    69,    69,    70,    71,     0,    22,
      23,    24,    21,    69,    69,    97,    68,    67,    66,    65,
      77,    78,    76,    75,     0,     0,     0,    74,    73,     0,
      26,    35,    44,    36,     0,    18,    81,    79,    80,    72,
      69,    49,    17,    69,     0,    46,    42,     0,    49,    45,
      39,    40,    41,    48,    50,     0,    53,    43,    47,     0,
      54,    52,     0,    51,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    24,
      51,    52,    64,    65,    73,    83,    88,   113,   132,   153,
     133,   142,   144,   145,   146,   154,   155,   162,    15,    16,
      17,    18,    19,    23,    48,   134,    72,   106,    22,    70,
      21,    91,    41,    45,    46,    49,    20,   107,    74,    67,
      68,    25,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int16 yypact[] =
{
     129,   -76,   -76,   -76,   -76,   -76,   -76,     7,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   134,   138,     0,    73,    25,
     106,    45,     3,    31,    33,    45,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,    47,   -76,
      42,   -76,   -76,    42,   -76,   -76,    52,   -76,   -76,    53,
     -76,   -76,    65,   -76,    42,    35,   -76,   -76,   -76,    80,
      80,   -76,    35,   -76,     8,   150,   -76,    59,   -76,   -76,
      45,    21,    61,    70,   -76,    30,    13,   -76,    80,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,    35,
     -76,   -76,   -76,    42,   -76,   -76,   -76,   -76,    42,    61,
      61,    61,    61,   -76,   -76,   -76,   145,   -76,    80,   -76,
     -76,   -76,   -76,    12,    15,   -76,    61,    61,    61,    61,
     100,   100,   100,   100,   140,   132,   114,   -76,   -76,    82,
     -76,   -76,   103,   -76,    17,   -76,   -76,   -76,   -76,   -76,
       9,   -76,   -76,   -76,    58,   -76,    83,    21,   -76,    42,
     -76,   -76,   -76,   -76,   -76,   107,   -76,    42,   -76,    -6,
     -76,   -76,    23,   -76,   -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   126,   133,   165,   171,   164,   -76,   -76,
     -76,   -76,   -76,   -76,   130,   -76,   -76,   -75,    78,   -76,
     -76,   -76,   -76,    46,   -76,   -76,    29,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -50,    84,    85,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   141,   -17,   -16,
     -20,   -76,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -39
static const yytype_int16 yytable[] =
{
      39,    42,    43,    37,    38,    53,    54,    26,    71,   -38,
     160,    76,   -37,   114,    78,   -37,    94,    95,    96,    97,
      94,    95,    96,    97,    94,    95,    96,    97,    79,    80,
      81,    82,     3,     4,     5,    69,   108,   163,    32,    39,
      39,   111,    77,    38,    38,    36,   -38,    44,   110,   -37,
      92,    93,    98,   124,   125,   126,   140,   -38,    39,     5,
     -37,   112,    38,   -37,   143,   131,    33,    32,   131,   115,
      99,   100,   101,   102,    36,    47,   108,   103,   104,    32,
     105,    50,    59,    55,    60,   109,    36,    56,    39,    32,
      33,   130,    38,   147,    61,    89,    36,    62,    57,    58,
     148,    62,    90,    33,    63,    32,     4,     5,    63,    32,
      34,    35,    36,   129,    34,    35,    36,    94,    95,    96,
      97,   150,   151,   152,    32,   149,   156,    32,   157,    34,
      35,    36,   138,   139,    36,    94,    95,    96,    97,   156,
     141,    27,   156,    94,    95,    96,    97,   137,   159,    28,
      32,    33,   127,   128,   136,    34,    35,    36,   129,     1,
       2,     3,     4,     5,     6,     2,     3,     4,     5,     6,
       3,     4,     5,     6,    84,    85,    86,    87,   116,   117,
     118,   119,    29,    31,   120,   121,   122,   123,   161,    30,
      75,   164,   135,    66,   158
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-76))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
      20,    21,    21,    20,    20,    25,    25,     0,    58,     0,
      16,    61,     0,    88,     6,     0,     3,     4,     5,     6,
       3,     4,     5,     6,     3,     4,     5,     6,    20,    21,
      22,    23,    32,    33,    34,    55,     6,    14,    44,    59,
      60,    28,    62,    59,    60,    51,    37,    44,    18,    37,
      70,    70,    71,   103,   104,   105,   131,    48,    78,    34,
      48,    78,    78,    48,    47,    53,    45,    44,    53,    89,
       9,    10,    11,    12,    51,    44,     6,    16,    17,    44,
      19,    48,    17,    36,    19,    15,    51,    45,   108,    44,
      45,   108,   108,   143,    29,    36,    51,    36,    46,    46,
      42,    36,    43,    45,    43,    44,    33,    34,    43,    44,
      49,    50,    51,    13,    49,    50,    51,     3,     4,     5,
       6,    38,    39,    40,    44,   144,   146,    44,   147,    49,
      50,    51,    18,    51,    51,     3,     4,     5,     6,   159,
      37,    15,   162,     3,     4,     5,     6,    15,    41,    16,
      44,    45,     7,     8,    14,    49,    50,    51,    13,    30,
      31,    32,    33,    34,    35,    31,    32,    33,    34,    35,
      32,    33,    34,    35,    24,    25,    26,    27,    94,    95,
      96,    97,    17,    19,    99,   100,   101,   102,   159,    18,
      60,   162,   114,    52,   148
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    31,    32,    33,    34,    35,    55,    56,    57,
      58,    59,    60,    61,    62,    82,    83,    84,    85,    86,
     100,    94,    92,    87,    63,   105,     0,    57,    58,    59,
      60,    61,    44,    45,    49,    50,    51,   102,   103,   104,
     106,    96,   104,   106,    44,    97,    98,    44,    88,    99,
      48,    64,    65,   104,   106,    36,    45,    46,    46,    17,
      19,    29,    36,    43,    66,    67,   101,   103,   104,   104,
      93,    89,    90,    68,   102,    68,    89,   104,     6,    20,
      21,    22,    23,    69,    24,    25,    26,    27,    70,    36,
      43,    95,   104,   106,     3,     4,     5,     6,   106,     9,
      10,    11,    12,    16,    17,    19,    91,   101,     6,    15,
      18,    28,   102,    71,    71,   104,    90,    90,    90,    90,
      91,    91,    91,    91,    89,    89,    89,     7,     8,    13,
     102,    53,    72,    74,    89,    72,    14,    15,    18,    51,
      71,    37,    75,    47,    76,    77,    78,    89,    42,   106,
      38,    39,    40,    73,    79,    80,   104,   106,    77,    41,
      16,    80,    81,    14,    80
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
#line 147 "htwolcpre1.yy"
    {}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 174 "htwolcpre1.yy"
    {
  // If this rule didn't have variables, display it. Otherwise iterate
  // through its variable value combinations and display the rule using the 
  // different combinations.
  try
    {
      if (rule_variables.empty())
	{ std::cout << rule_symbol_vector.replace_variables(); }
      else
	{
	  for (RuleVariables::const_iterator it = rule_variables.begin();
	       it != rule_variables.end();
	       ++it)
	    { 
	      it.set_values(variable_value_map); 
	      std::cout << rule_symbol_vector.replace_variables();
	    }
	}
    }
  catch (const UnequalSetSize &)
    {      
      std::string error
	("Variable rules with keyword matched have to have equal length "
	 "variable value lists.");
      yyerror(error.c_str());
      exit(1);
    }
  // Clear all containers, so that we'll be ready to handle the next rule.
  rule_symbol_vector.clear();
  variable_value_map.clear();
  rule_variables.clear();
}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 208 "htwolcpre1.yy"
    { 
  std::cout << rule_symbol_vector.replace_variables(); 

  // Clear all containers, so that we'll be ready to handle the next rule.
  rule_symbol_vector.clear();
  variable_value_map.clear();
  rule_variables.clear();
}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 218 "htwolcpre1.yy"
    { 
  // Add the rule name to rule_symbol_vector.
  reduce_queue(); 
}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 250 "htwolcpre1.yy"
    { matcher_queue.push_back(MATCHED); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 252 "htwolcpre1.yy"
    { matcher_queue.push_back(MIXED); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 254 "htwolcpre1.yy"
    { matcher_queue.push_back(FREELY); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 256 "htwolcpre1.yy"
    { matcher_queue.push_back(FREELY); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 269 "htwolcpre1.yy"
    {
  // Set variable block matcher.
  rule_variables.set_matcher
    (matcher_queue.empty() ? FREELY : matcher_queue.get_front_and_pop());
}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 280 "htwolcpre1.yy"
    { set_variable_values(); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 282 "htwolcpre1.yy"
    { set_variable_values(); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 285 "htwolcpre1.yy"
    { reduce_queue(true); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 316 "htwolcpre1.yy"
    { 
  symbol_queue.front() = 
    std::string("__HFST_TWOLC_NUMBER=") + symbol_queue.front(); 
  reduce_queue();
}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 341 "htwolcpre1.yy"
    { 
  // Push the set_symbol into latest_set, which contains symbols in the next
  // set which will be defined.
  if (sets.find(get_symbol_queue_front()) != sets.end())
    {
      for (std::vector<std::string>::iterator it = 
	     set_symbols
	     ["__HFST_TWOLC_SET_NAME=" + get_symbol_queue_front()].begin();
	   it != set_symbols
	     ["__HFST_TWOLC_SET_NAME=" + get_symbol_queue_front()].end();
	   ++it)
	{ 
	  std::cout << *it << " ";
	  latest_set.push_back(*it);
	}
      pop_symbol_queue();
    }
  else
    { 
      latest_set.push_back(unescape(get_symbol_queue_front())); 
      reduce_queue();  
    }
}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 366 "htwolcpre1.yy"
    { reduce_queue(); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 369 "htwolcpre1.yy"
    {
  // Store the set symbols of the set whose name is set_name into set_symbols.
  set_symbols[set_name] = latest_set;
  latest_set.clear();
}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 376 "htwolcpre1.yy"
    { 
  // Store the set name in sets and push it at the back of 
  // symbol_queue. 
  sets.insert(get_symbol_queue_front());
  get_symbol_queue_front() = 
    "__HFST_TWOLC_SET_NAME=" + get_symbol_queue_front();
  set_name = get_symbol_queue_front(); 
  reduce_queue();
}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 387 "htwolcpre1.yy"
    {
  // Store the definition name in definitions and push it at the back of 
  // symbol_queue.
  definitions.insert(get_symbol_queue_front());
  get_symbol_queue_front() = 
    "__HFST_TWOLC_DEFINITION_NAME=" + get_symbol_queue_front();
  reduce_queue();
}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 401 "htwolcpre1.yy"
    { 
  // For pairs "X:" and "X:?".
  // Reduce the first three symbols "X", "__HFST_TWOLC_:" and "__HFST_TWOLC_?"
  // from symbol_queue.
  reduce_symbol_pair(true); 
}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 408 "htwolcpre1.yy"
    {
  // For pairs ":X".
  // Push a "__HFST_TWOLC_?" onto symbol_queue.
  // Reduce the three first symbols "__HFST_TWOLC_?", "__HFST_TWOLC_:" and "X"
  // from symbol_queue.
  symbol_queue.push_front("__HFST_TWOLC_?");
  reduce_symbol_pair(true); 
}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 417 "htwolcpre1.yy"
    { 
  // For pairs "X:Y".
  // Reduce the first three symbols "X", "__HFST_TWOLC_:" and "Y" from
  // symbol_queue.
  reduce_symbol_pair(true); 
}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 424 "htwolcpre1.yy"
    {
  // For pairs ":" and ":?".
  // Push a "__HFST_TWOLC_?" onto symbol_queue.
  // Reduce the three first symbols "__HFST_TWOLC_?", "__HFST_TWOLC_:" and
  // "__HFST_TWOLC_?" from symbol_queue.
  symbol_queue.push_front("__HFST_TWOLC_?");
  reduce_symbol_pair();
}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 433 "htwolcpre1.yy"
    {
  // For pairs "X".
  // Push "X" and "__HFST_TWOLC_:" on top of symbol_queue.
  // Reduce the first three symbols "X", "__HFST_TWOLC_:" and "X" from
  // symbol_queue.
  std::string symbol = get_symbol_queue_front();

  // Add the colon and output symbol.
  symbol_queue.push_front("__HFST_TWOLC_:");
  symbol_queue.push_front(symbol); 
  reduce_symbol_pair();
}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 448 "htwolcpre1.yy"
    { 
  // For pairs "X:Y".
  // Reduce the first three symbols "X", "__HFST_TWOLC_:" and "Y" from
  // symbol_queue.
  reduce_symbol_pair(); 
}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 455 "htwolcpre1.yy"
    {
  // For pairs "X".
  // Push "X" and "__HFST_TWOLC_:" on top of symbol_queue.
  // Reduce the first three symbols "X", "__HFST_TWOLC_:" and "X" from
  // symbol_queue.
  std::string symbol = get_symbol_queue_front();
  symbol_queue.push_back("__HFST_TWOLC_:");
  symbol_queue.push_back(symbol);
  reduce_symbol_pair();
}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 476 "htwolcpre1.yy"
    { pop_symbol_queue(); }
    break;



/* Line 1806 of yacc.c  */
#line 2044 "htwolcpre1.cc"
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
#line 481 "htwolcpre1.yy"


// Print warning. 
void warn(const char * warning) 
{ input_reader.warn(warning); }

// Print error messge and exit 1.
void yyerror(const char * text) 
{ 
  input_reader.error(text); 
  std::cout << "__HFST_TWOLC_DIE";
  exit(1);
}

// Set the variable of this variable initialization and set its values.
// If its value list contains set names, replace them by the set elements.
void set_variable_values(void)
{
  rule_variables.set_variable(variable_vector.front());
  for (StringVector::const_iterator it = variable_vector.begin()+1;
       it != variable_vector.end();
       ++it)
    {
      if (set_symbols.has_key(*it))
	{ rule_variables.add_values(set_symbols[*it]); }
      else
	{ rule_variables.add_value(*it); }
    }
  variable_vector.clear(); 
}

// Pop the queue three times: once for the input symbol, once for the pair
// separator and once for the output symbol.
void reduce_symbol_pair(bool no_definitions)
{
  if (no_definitions)
    {
      if (definitions.has_element(get_symbol_queue_front()))
	{
	  std::string def = get_symbol_queue_front();
	  std::string error = 
	    "Definition name " + def + " can't be used in pair expressions " + 
	    def + ":, :" + def + " and " + def + ":" + def + ".";
	  
	  yyerror(error.c_str());
	}
    }

  reduce_queue();
  reduce_queue();

  if (no_definitions)
    {
      if (definitions.has_element(get_symbol_queue_front()))
	{
	  std::string def = get_symbol_queue_front();
	  std::string error = 
	    "Definition name " + def + " can't be used in pair expressions " + 
	    def + ":, :" + def + " and " + def + ":" + def + ".";
	  
	  yyerror(error.c_str());
	}
    }

  reduce_queue();
}

// Increase line counter for every symbol "__HFST_TWOLC_\\n", which is
// encountered.
void increase_line_counter(void)
{
  while (not symbol_queue.empty() && 
	 symbol_queue.front() == "__HFST_TWOLC_\\n")
    {
      ++line_number;
      symbol_queue.pop_front();
    }
}

// First pop all "__HFST_TWOLC_\\n" in symbol_queue, while incrementing
// line_counter. Then pop the first element != "__HFST_TWOLC_\\n" in 
// symbol_queue.
void pop_symbol_queue(void)
{
  increase_line_counter();
  symbol_queue.pop_front();
}

// First pop all "__HFST_TWOLC_\\n" in symbol_queue, while incrementing
// line_counter. Then return a reference to the first element 
// != "__HFST_TWOLC_\\n" in symbol_queue.
std::string &get_symbol_queue_front(void)
{
  increase_line_counter();
  return symbol_queue.front();
}

// Decide what to do with the next symbol in symbol_queue.
void reduce_queue(bool variable_symbol)
{ 
  increase_line_counter();
  // Test whether the next symbol is a set name and label it a set if it is.
  if (sets.has_element(get_symbol_queue_front()))
    {  get_symbol_queue_front() = 
	std::string("__HFST_TWOLC_SET_NAME=") + get_symbol_queue_front(); }

  // Test whether the next symbol is a definition name and label it a
  // definition if it is. 
  if (definitions.has_element(get_symbol_queue_front()))
    { get_symbol_queue_front() = 
      std::string("__HFST_TWOLC_DEFINITION_NAME=") + get_symbol_queue_front();}

  // Unescape the escaped characters in the symbol.
  get_symbol_queue_front() = unescape(get_symbol_queue_front());
  
  // We treat different symbols differently:
  //
  // 1. We display symbols, which aren't part of a rule.
  // 2. We push back rule symbols into rule_symbol_vector, which stores
  //    string representations of rules.
  // 3. We push back variable symbols into rule_symbol_vector, which stores 
  //    rule-variable names and values.
  if (not variable_symbol)
    {
      if (not rules_start)
	{ 
	  std::cout << get_symbol_queue_front() << " "; 
	  pop_symbol_queue();
	}
      else
	{ 
	  rule_symbol_vector.push_back
	    (StringVector(get_symbol_queue_front()));
	  pop_symbol_queue();
	}
    }
  else
    { 
      variable_vector.push_back(get_symbol_queue_front()); 
      pop_symbol_queue();
    }
}

int main(int argc, char * argv[])
{
#ifdef WINDOWS
  _setmode(1, _O_BINARY);
#endif

  CommandLine command_line(argc,argv);

  if (command_line.help or command_line.version)
    {
      if (command_line.version)
	{ command_line.print_version(); }
      if (command_line.help)
	{ command_line.print_help(); }
      exit(0);
    }
  if (command_line.usage)
    {
      command_line.print_usage();
      exit(0);
    }
  if (not command_line.be_quiet)
    {
      if (not command_line.has_input_file)
	{ std::cerr << "Reading input from STDIN." << std::endl; }
      else
	{ std::cerr << "Reading input from " << command_line.input_file_name
		    << "." << std::endl; }
      if (not command_line.has_output_file)
	{ std::cerr << "Writing output to STDOUT." << std::endl; }
      else
	{ std::cerr << "Writing output to " << command_line.output_file_name
		    << "." << std::endl; }
    }
  if (command_line.be_verbose)
    { std::cerr << "Verbose mode." << std::endl; }

  input_reader.set_input(command_line.set_input_file());

  // Test that the output file is okay.
  (void)command_line.set_output_file();

  //yydebug = 1;

  return yyparse();
}



