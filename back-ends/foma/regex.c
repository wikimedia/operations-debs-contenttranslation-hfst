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
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 18 "regex.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "foma.h"
#define MAX_F_RECURSION 100
extern int yyerror();
extern int yylex();
extern int my_yyparse(char *my_string, int lineno, struct defined_networks *defined_nets, struct defined_functions *defined_funcs);
struct fsm *current_parse;
int rewrite, rule_direction;
int substituting = 0;
static char *subval1, *subval2;
struct fsmcontexts *contexts;
struct fsmrules *rules;
struct rewrite_set *rewrite_rules;
static struct fsm *fargs[100][MAX_F_RECURSION];  /* Function arguments [number][frec] */
static int frec = -1;                            /* Current depth of function recursion */
static char *fname[MAX_F_RECURSION];             /* Function names */
static int fargptr[MAX_F_RECURSION];             /* Current argument no. */
/* Variable to produce internal symbols */
unsigned int g_internal_sym = 23482342;

void add_function_argument(struct fsm *net) {
    fargs[fargptr[frec]][frec] = net;
    fargptr[frec]++;
}

void declare_function_name(char *s) {
    if (frec > MAX_F_RECURSION) {
        printf("Function stack depth exceeded. Aborting.\n");
        exit(1);
    }
    fname[frec] = xxstrdup(s);
    xxfree(s);
}

struct fsm *function_apply(struct defined_networks *defined_nets, struct defined_functions *defined_funcs) {
    int i, mygsym, myfargptr;
    char *regex;
    char repstr[13], oldstr[13];
    if ((regex = find_defined_function(defined_funcs, fname[frec],fargptr[frec])) == NULL) {
        fprintf(stderr, "***Error: function %s@%i) not defined!\n",fname[frec], fargptr[frec]);
        return NULL;
    }
    regex = xxstrdup(regex);
    mygsym = g_internal_sym;
    myfargptr = fargptr[frec];
    /* Create new regular expression from function def. */
    /* and parse that */
    for (i = 0; i < fargptr[frec]; i++) {
        sprintf(repstr,"%012X",g_internal_sym);
        sprintf(oldstr, "@ARGUMENT%02i@", (i+1));
        streqrep(regex, oldstr, repstr);
        /* We temporarily define a network and save argument there */
        /* The name is a running counter g_internal_sym */
        add_defined(defined_nets, fargs[i][frec], repstr);
        g_internal_sym++;
    }
    my_yyparse(regex,1,defined_nets, defined_funcs);
    for (i = 0; i < myfargptr; i++) {
        sprintf(repstr,"%012X",mygsym);
        /* Remove the temporarily defined network */
        remove_defined(defined_nets, repstr);
        mygsym++;
    }
    xxfree(fname[frec]);
    frec--;
    xxfree(regex);
    return(current_parse);
}

void add_context_pair(struct fsm *L, struct fsm *R) {
    struct fsmcontexts *newcontext;
    newcontext = xxcalloc(1,sizeof(struct fsmcontexts));
    newcontext->left = L;
    newcontext->right = R;
    newcontext->next = contexts;
    contexts = newcontext;
}

void clear_rewrite_ruleset(struct rewrite_set *rewrite_rules) {
    struct rewrite_set *rule, *rulep;
    struct fsmcontexts *contexts, *contextsp;
    struct fsmrules *r, *rp;
    for (rule = rewrite_rules; rule != NULL; rule = rulep) {

	for (r = rule->rewrite_rules ; r != NULL; r = rp) {
	    fsm_destroy(r->left);
	    fsm_destroy(r->right);
	    fsm_destroy(r->right2);
	    fsm_destroy(r->cross_product);
	    rp = r->next;
	    xxfree(r);
	}
	
	for (contexts = rule->rewrite_contexts; contexts != NULL ; contexts = contextsp) {

	    contextsp = contexts->next;
	    fsm_destroy(contexts->left);
	    fsm_destroy(contexts->right);
	    fsm_destroy(contexts->cpleft);
	    fsm_destroy(contexts->cpright);
	    xxfree(contexts);
	}
       	rulep = rule->next;
	//fsm_destroy(rules->cpunion);
	xxfree(rule);
    }
}

void add_rewrite_rule() {
    struct rewrite_set *new_rewrite_rule;
    if (rules != NULL) {
        new_rewrite_rule = xxmalloc(sizeof(struct rewrite_set));
        new_rewrite_rule->rewrite_rules = rules;
        new_rewrite_rule->rewrite_contexts = contexts;
        new_rewrite_rule->next = rewrite_rules;
        new_rewrite_rule->rule_direction = rule_direction;

        rewrite_rules = new_rewrite_rule;
        rules = NULL;
        contexts = NULL;
        rule_direction = 0;
    }
}

void add_eprule(struct fsm *R, struct fsm *R2, int type) {
    struct fsmrules *newrule;
    rewrite = 1;
    newrule = xxmalloc(sizeof(struct fsmrules));
    newrule->left = fsm_empty_string();
    newrule->right = R;
    newrule->right2 = R2;
    newrule->arrow_type = type;
    newrule->next = rules;
    rules = newrule;
}
 
void add_rule(struct fsm *L, struct fsm *R, struct fsm *R2, int type) {
    struct fsm *test;
    struct fsmrules *newrule;
    rewrite = 1;
    newrule = xxmalloc(sizeof(struct fsmrules));

    if ((type & ARROW_DOTTED) != 0) {
        newrule->left = fsm_minus(fsm_copy(L), fsm_empty_string());
    } else {
        newrule->left = L;
    }
    newrule->right = R;
    newrule->right2 = R2;
    newrule->next = rules;
    newrule->arrow_type = type;
    if ((type & ARROW_DOTTED) != 0) {
        newrule->arrow_type = type - ARROW_DOTTED;
    }

    rules = newrule;

    if ((type & ARROW_DOTTED) != 0) {
        /* Add empty [..] -> B for dotted rules (only if LHS contains the empty string) */
        test = fsm_intersect(L,fsm_empty_string());
        if (!fsm_isempty(test)) {
            newrule = xxmalloc(sizeof(struct fsmrules));
            newrule->left = test;
            newrule->right = fsm_copy(R);
            newrule->right2 = fsm_copy(R2);
            newrule->next = rules;
            newrule->arrow_type = type;
            rules = newrule;
        } else {
	    //fsm_destroy(test);
	}
    }
}




/* Line 268 of yacc.c  */
#line 252 "regex.c"

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

/* Line 293 of yacc.c  */
#line 198 "regex.y"

     char *string;
     struct fsm *net;
     int  type;



/* Line 293 of yacc.c  */
#line 382 "regex.c"
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
#line 407 "regex.c"

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
#define YYFINAL  105
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1207

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNRULES -- Number of states.  */
#define YYNSTATES  291

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

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
      85,    86
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    17,    21,    25,
      27,    29,    33,    36,    41,    43,    47,    52,    56,    59,
      64,    70,    74,    78,    81,    87,    92,   100,   107,   115,
     122,   128,   133,   139,   144,   148,   152,   157,   162,   168,
     176,   183,   190,   196,   204,   211,   218,   224,   226,   230,
     234,   238,   240,   242,   244,   248,   252,   256,   260,   264,
     268,   272,   274,   277,   281,   285,   289,   293,   297,   299,
     303,   307,   311,   315,   319,   321,   324,   327,   330,   333,
     335,   337,   340,   343,   346,   349,   352,   355,   358,   362,
     365,   368,   371,   374,   376,   379,   381,   383,   388,   391,
     395,   399,   405,   411,   417,   420,   425,   430,   432,   436,
     440,   444,   448,   452,   456,   460,   464,   468,   472,   476,
     482,   488,   494,   500,   504,   510,   516,   524,   528,   532,
     540,   544,   547,   551,   555,   559,   563
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      88,     0,    -1,    89,    -1,    89,    88,    -1,    90,     4,
      -1,    91,    -1,    90,    77,    91,    -1,    90,    45,    91,
      -1,    90,    76,    91,    -1,    92,    -1,    93,    -1,    92,
      20,    92,    -1,    92,    20,    -1,    92,    20,    26,    92,
      -1,    20,    -1,    20,    25,    92,    -1,    92,    20,    25,
      92,    -1,    20,    26,    92,    -1,    20,    92,    -1,    20,
      92,    26,    92,    -1,    92,    20,    92,    26,    92,    -1,
      92,    11,    92,    -1,    92,    73,    92,    -1,    92,    73,
      -1,    47,    92,    48,    73,    92,    -1,    47,    48,    73,
      92,    -1,    47,    92,    48,    73,    92,    26,    92,    -1,
      47,    48,    73,    92,    26,    92,    -1,    47,    92,    48,
      73,    92,    74,    92,    -1,    47,    48,    73,    92,    74,
      92,    -1,    92,    73,    92,    26,    92,    -1,    92,    73,
      26,    92,    -1,    92,    73,    92,    74,    92,    -1,    92,
      73,    74,    92,    -1,    92,    25,    92,    -1,    92,    73,
      46,    -1,    92,    73,    46,    92,    -1,    92,    73,    92,
      46,    -1,    92,    73,    92,    46,    92,    -1,    92,    73,
      92,    46,    92,    26,    92,    -1,    92,    73,    92,    46,
      26,    92,    -1,    92,    73,    46,    92,    26,    92,    -1,
      92,    73,    46,    26,    92,    -1,    92,    73,    92,    46,
      92,    74,    92,    -1,    92,    73,    46,    92,    74,    92,
      -1,    92,    73,    92,    46,    74,    92,    -1,    92,    73,
      46,    74,    92,    -1,    94,    -1,    93,    27,    94,    -1,
      93,    28,    94,    -1,    93,    29,    94,    -1,    95,    -1,
      96,    -1,    97,    -1,    96,    80,    97,    -1,    96,    43,
      97,    -1,    96,    44,    97,    -1,    96,    79,    97,    -1,
      96,    78,    97,    -1,    96,    37,    97,    -1,    96,    38,
      97,    -1,    98,    -1,    97,    98,    -1,    35,    36,    97,
      -1,    35,    39,    35,    -1,    35,    40,    35,    -1,    35,
      28,    35,    -1,    35,    29,    35,    -1,    99,    -1,    98,
      18,    99,    -1,    98,    19,    99,    -1,    98,    30,    99,
      -1,    98,    31,    99,    -1,    98,    32,    99,    -1,   100,
      -1,    81,    99,    -1,    12,    99,    -1,    14,    99,    -1,
      13,    99,    -1,   101,    -1,   102,    -1,   101,    85,    -1,
     101,    84,    -1,   101,    83,    -1,   101,    82,    -1,   101,
      15,    -1,   101,    16,    -1,   101,    17,    -1,   101,    75,
     102,    -1,   101,    21,    -1,   101,    23,    -1,   101,    24,
      -1,   101,    22,    -1,   103,    -1,    86,   102,    -1,     3,
      -1,   106,    -1,    33,     7,    90,     8,    -1,    34,    90,
      -1,     7,    90,     8,    -1,     5,    90,     6,    -1,    42,
      35,    26,    35,     8,    -1,    42,    35,    26,    90,     8,
      -1,    42,    90,    26,    35,     8,    -1,   104,   105,    -1,
      41,     5,    90,    26,    -1,    50,    26,    50,     6,    -1,
     109,    -1,    52,    90,     8,    -1,    53,    90,     8,    -1,
      51,    90,     8,    -1,    54,    90,     8,    -1,    55,    90,
       8,    -1,    56,    90,     8,    -1,    57,    90,     8,    -1,
      58,    90,     8,    -1,    59,    90,     8,    -1,    60,    90,
       8,    -1,    62,    90,     8,    -1,    63,    90,    26,    90,
       8,    -1,    64,    90,    26,    90,     8,    -1,    65,    90,
      26,    90,     8,    -1,    66,    90,    26,    90,     8,    -1,
      67,    90,     8,    -1,    68,    90,    26,    90,     8,    -1,
      69,    90,    26,    90,     8,    -1,    70,    90,    26,    90,
      26,    90,     8,    -1,    71,    90,     8,    -1,    72,    90,
       8,    -1,    61,    90,    26,    90,    26,    90,     8,    -1,
      49,    90,    26,    -1,    49,    90,    -1,   107,    90,    26,
      -1,   108,    90,    26,    -1,   108,    90,     8,    -1,   107,
      90,     8,    -1,   107,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   252,   252,   253,   256,   258,   259,   260,   261,   263,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   291,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   307,   308,   309,
     310,   312,   314,   316,   317,   318,   319,   320,   321,   322,
     323,   325,   326,   327,   329,   330,   331,   332,   334,   335,
     336,   337,   338,   339,   341,   342,   343,   344,   345,   347,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   359,
     360,   361,   362,   364,   365,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   378,   379,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     405,   407,   410,   411,   413,   415,   417
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NET", "END", "LBRACKET", "RBRACKET",
  "LPAREN", "RPAREN", "ENDM", "ENDD", "CRESTRICT", "CONTAINS",
  "CONTAINS_OPT_ONE", "CONTAINS_ONE", "XUPPER", "XLOWER", "FLAG_ELIMINATE",
  "IGNORE_ALL", "IGNORE_INTERNAL", "CONTEXT", "NCONCAT", "MNCONCAT",
  "MORENCONCAT", "LESSNCONCAT", "DOUBLE_COMMA", "COMMA", "SHUFFLE",
  "PRECEDES", "FOLLOWS", "RIGHT_QUOTIENT", "LEFT_QUOTIENT",
  "INTERLEAVE_QUOTIENT", "UQUANT", "EQUANT", "VAR", "IN", "IMPLIES",
  "BICOND", "EQUALS", "NEQ", "SUBSTITUTE", "SUCCESSOR_OF",
  "PRIORITY_UNION_U", "PRIORITY_UNION_L", "LENIENT_COMPOSE", "TRIPLE_DOT",
  "LDOT", "RDOT", "FUNCTION", "SUBVAL", "ISUNAMBIGUOUS", "ISIDENTITY",
  "ISFUNCTIONAL", "NOTID", "LOWERUNIQ", "LOWERUNIQEPS", "ALLFINAL",
  "UNAMBIGUOUSPART", "AMBIGUOUSPART", "AMBIGUOUSDOMAIN", "EQSUBSTRINGS",
  "LETTERMACHINE", "MARKFSMTAIL", "MARKFSMTAILLOOP", "MARKFSMMIDLOOP",
  "MARKFSMLOOP", "ADDSINK", "LEFTREWR", "FLATTEN", "SUBLABEL",
  "CLOSESIGMA", "CLOSESIGMAUNK", "ARROW", "DIRECTION",
  "HIGH_CROSS_PRODUCT", "CROSS_PRODUCT", "COMPOSE", "MINUS", "INTERSECT",
  "UNION", "COMPLEMENT", "INVERSE", "REVERSE", "KLEENE_PLUS",
  "KLEENE_STAR", "TERM_NEGATION", "$accept", "start", "regex", "network",
  "networkA", "n0", "network1", "network2", "network3", "network4",
  "network5", "network6", "network7", "network8", "network9", "network10",
  "network11", "sub1", "sub2", "network12", "fstart", "fmid", "fend", 0
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
     335,   336,   337,   338,   339,   340,   341
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    88,    89,    90,    90,    90,    90,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    93,    93,    93,
      93,    94,    95,    96,    96,    96,    96,    96,    96,    96,
      96,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      98,    98,    98,    98,    99,    99,    99,    99,    99,   100,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   104,   105,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     107,   107,   108,   108,   109,   109,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     3,     3,     3,     1,
       1,     3,     2,     4,     1,     3,     4,     3,     2,     4,
       5,     3,     3,     2,     5,     4,     7,     6,     7,     6,
       5,     4,     5,     4,     3,     3,     4,     4,     5,     7,
       6,     6,     5,     7,     6,     6,     5,     1,     3,     3,
       3,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     1,     2,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     1,     2,     2,     2,     2,     1,
       1,     2,     2,     2,     2,     2,     2,     2,     3,     2,
       2,     2,     2,     1,     2,     1,     1,     4,     2,     3,
       3,     5,     5,     5,     2,     4,     4,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       5,     5,     5,     3,     5,     5,     7,     3,     3,     7,
       3,     2,     3,     3,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    95,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     0,     5,     9,    10,    47,    51,    52,    53,    61,
      68,    74,    79,    80,    93,     0,    96,     0,     0,   107,
       0,     0,    76,    78,    77,     0,     0,    18,     0,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    75,    94,     1,     3,     4,     0,     0,
       0,     0,    12,     0,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,     0,     0,     0,     0,
       0,    85,    86,    87,    89,    92,    90,    91,     0,    84,
      83,    82,    81,     0,   104,   136,     0,     0,   100,    99,
      15,    17,     0,     0,    66,    67,    63,    64,    65,     0,
       0,     0,     0,     0,   130,   110,   108,   109,   111,   112,
     113,   114,   115,   116,   117,     0,   118,     0,     0,     0,
       0,   123,     0,     0,     0,   127,   128,     7,     8,     6,
      21,     0,     0,    11,    34,     0,    35,     0,    22,    48,
      49,    50,    59,    60,    55,    56,    58,    57,    54,    69,
      70,    71,    72,    73,    88,     0,   135,   132,   134,   133,
      19,    97,   105,     0,     0,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    13,     0,    31,
       0,     0,    36,    33,     0,    37,     0,     0,   101,   102,
     103,     0,     0,    24,     0,   119,   120,   121,   122,   124,
     125,     0,    20,    42,    46,     0,     0,    30,     0,     0,
      38,    32,   106,    27,    29,     0,     0,     0,     0,    41,
      44,    40,    45,     0,     0,    26,    28,   129,   126,    39,
      43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,   144,    56,
      57,    58,    59
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -42
static const yytype_int16 yypact[] =
{
     750,   -42,   750,   750,    68,    68,    68,   330,     2,   750,
     207,     5,   820,   610,   750,   750,   750,   750,   750,   750,
     750,   750,   750,   750,   750,   750,   750,   750,   750,   750,
     750,   750,   750,   750,   750,   750,   750,    68,  1001,    12,
     750,     0,   -42,   133,    60,   -42,   -42,  1127,    68,   413,
     -42,   -42,   200,   -42,   -42,   -12,   -42,   680,   750,   -42,
      66,   142,   -42,   -42,   -42,   750,   750,    43,   750,   -40,
       8,     9,   960,    15,    20,   750,    13,   333,   -33,  1090,
     403,   152,   263,   291,   361,   431,   501,   571,   641,   711,
     781,   473,   851,   543,   683,   753,   823,   921,  1057,  1066,
    1069,   962,  1002,   -42,   -42,   -42,   -42,   -42,   750,   750,
     750,   750,   400,   750,   260,   960,   960,   960,   960,   960,
     960,   960,   960,   960,   960,   413,    68,    68,    68,    68,
      68,   -42,   -42,   -42,   -42,   -42,   -42,   -42,  1001,   -42,
     -42,   -42,   -42,    35,   -42,   -42,   149,   165,   -42,   -42,
     133,   133,   750,  1029,   -42,   -42,    68,   -42,   -42,  1073,
     890,    27,   750,    -9,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   750,   -42,   750,   750,   750,
     750,   -42,   750,   750,   750,   -42,   -42,   -42,   -42,   -42,
     133,   750,   750,   350,   133,   750,   470,   750,    40,   -42,
     -42,   -42,    68,    68,    68,    68,    68,    68,    68,   -42,
     -42,   -42,   -42,   -42,   -42,    28,   -42,   -42,   -42,   -42,
     133,   -42,   -42,  1158,  1032,    62,    73,   750,  1096,  1036,
    1040,  1043,  1076,  1078,  1081,  1099,   133,   133,   750,   133,
     750,   750,   175,   133,   750,   540,   750,    77,   -42,   -42,
     -42,   750,   750,   182,   750,   -42,   -42,   -42,   -42,   -42,
     -42,   750,   133,   133,   133,   750,   750,   133,   750,   750,
     278,   133,   -42,   133,   133,   750,   750,  1083,  1085,   133,
     133,   133,   133,   750,   750,   133,   133,   -42,   -42,   133,
     133
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -42,    45,   -42,    -1,   -18,    -7,   -42,   -21,   -42,   -42,
     513,   -41,    42,   -42,   -42,   -35,   -42,   -42,   -42,   -42,
     -42,   -42,   -42
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      67,    60,    61,   104,   107,   108,    79,   125,    69,    68,
      75,    77,   105,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   109,   110,   143,   160,
     162,    70,    71,   154,   155,   108,    62,    63,    64,    72,
     157,   111,    73,    74,   111,   158,   146,   147,   150,   151,
     112,   215,   225,   112,   227,   113,   244,   153,   113,   152,
     250,     1,   148,     2,   159,     3,   109,   110,   247,   103,
       4,     5,     6,   272,   111,   106,   245,   115,   116,   117,
     187,   188,   189,   112,   199,   200,   201,     0,   113,   251,
       0,     8,     9,   214,   190,   193,   194,   198,     0,    11,
      12,   108,     0,   114,   246,   125,   114,    14,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,     0,   109,   110,   111,   220,   114,   252,     0,    37,
     149,     0,     0,   112,    38,   226,     0,   216,   113,   224,
     165,   125,   125,   125,   125,   125,   125,   125,   209,   210,
     211,   212,   213,   218,   228,   217,   229,   230,   231,   232,
       0,   233,   234,   235,   236,   237,   111,   108,   239,   242,
     243,   219,     0,   111,   108,   112,     0,   108,     0,     0,
     113,   265,   112,     0,     0,     0,   114,   113,   275,     0,
     108,     0,     0,     0,     0,   131,   132,   133,   109,   110,
     253,   134,   135,   136,   137,   109,   110,     0,   109,   110,
       0,   262,     0,   263,   264,    70,    71,   267,   270,   271,
       0,   109,   110,    72,   273,   274,    73,    74,   114,   266,
       0,     0,     0,   277,     0,   114,   276,     0,   279,   280,
     278,   281,   282,     1,     0,     2,     0,     3,   285,   286,
       0,   166,     4,     5,     6,   138,   289,   290,     0,     0,
       7,     0,   139,   140,   141,   142,   195,     0,     0,   111,
       0,     0,     0,     8,     9,    10,     0,     0,   112,   167,
       0,    11,    12,   113,   283,     0,   196,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,   197,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,   114,   284,     0,     0,    65,    66,     0,     0,   161,
       0,   111,     0,     8,     9,    10,     0,   109,   110,   168,
     112,    11,    12,     0,     0,   113,   238,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,     0,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,     0,     0,   114,     0,   191,   192,     0,     0,   164,
       0,   126,   127,     8,     9,    10,     0,   109,   110,   169,
       0,    11,    12,   128,   129,   130,     0,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,     0,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,     0,     0,     0,     0,     0,   240,     0,     0,   175,
       0,     0,     0,     8,     9,    10,     0,   109,   110,   170,
       0,    11,    12,     0,     0,     0,     0,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,   241,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,     0,     0,     0,     0,     0,   268,     0,     0,   177,
       0,     0,     0,     8,     9,    10,     0,   109,   110,   171,
       0,    11,    12,     0,     0,   156,     0,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,   269,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,   202,   203,   204,   205,   206,   207,   208,     0,     0,
       0,     0,     0,     8,     9,    10,     0,   109,   110,   172,
       0,    11,    12,     0,     0,     0,     0,    13,    78,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,     0,     2,   108,     3,   145,     0,
       0,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,   178,
       0,     0,     0,     8,     9,    10,     0,   109,   110,   173,
       0,    11,    12,     0,     0,     0,     0,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,     0,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,     0,     8,     9,    10,     0,   109,   110,   174,
       0,    11,    12,     0,     0,     0,     0,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,     0,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,   180,
       0,     0,     0,     8,     9,    76,     0,   109,   110,   176,
       0,    11,    12,     0,     0,     0,     0,    13,   108,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,     0,     2,   108,     3,     0,   109,
     110,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     9,   223,     0,   109,   110,   181,
       0,    11,    12,     0,     0,     0,     0,    13,     0,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     1,     0,     2,   108,     3,     0,     0,
     185,    37,     4,     5,     6,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     9,    10,     0,   109,   110,     0,
       0,    11,    12,     0,     1,     0,     2,   108,     3,    14,
     186,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,     0,     8,     9,     0,   221,   109,   110,
     249,    37,    11,    12,   255,     0,    38,   108,   256,     0,
      14,   257,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,   108,     0,     0,   108,   109,   110,
       0,   108,     0,   182,   258,   108,   259,    38,   108,   260,
       0,   287,   183,   288,     0,   184,     0,     0,     0,   222,
       0,   111,   108,     0,     0,   109,   110,     0,   109,   110,
     112,   108,   109,   110,   108,   113,   109,   110,   108,   109,
     110,   108,   254,   108,     0,   261,   108,     0,   108,     0,
     108,     0,     0,   109,   110,     0,     0,     0,   163,     0,
       0,   108,   109,   110,   108,   109,   110,     0,     0,   109,
     110,     0,   109,   110,   109,   110,     0,   109,   110,   109,
     110,   109,   110,   114,   118,   119,   248,     0,     0,     0,
     120,   121,   109,   110,     0,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,    71,     0,     0,
       0,     0,     0,     0,    72,     0,     0,    73,    74,     0,
       0,     0,     0,     0,     0,   122,   123,   124
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-42))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       7,     2,     3,    38,     4,    45,    13,    48,     9,     7,
       5,    12,     0,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    76,    77,    50,    26,
      73,    28,    29,    35,    35,    45,     4,     5,     6,    36,
      35,    11,    39,    40,    11,    35,    57,    58,    65,    66,
      20,    26,    35,    20,    73,    25,    26,    68,    25,    26,
       8,     3,     6,     5,    75,     7,    76,    77,    50,    37,
      12,    13,    14,     6,    11,    40,    46,    27,    28,    29,
     108,   109,   110,    20,   115,   116,   117,    -1,    25,    26,
      -1,    33,    34,   138,   111,   112,   113,   114,    -1,    41,
      42,    45,    -1,    73,    74,   156,    73,    49,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    76,    77,    11,   152,    73,    74,    -1,    81,
       8,    -1,    -1,    20,    86,   162,    -1,     8,    25,   160,
       8,   202,   203,   204,   205,   206,   207,   208,   126,   127,
     128,   129,   130,     8,   175,    26,   177,   178,   179,   180,
      -1,   182,   183,   184,   191,   192,    11,    45,   195,   196,
     197,    26,    -1,    11,    45,    20,    -1,    45,    -1,    -1,
      25,    26,    20,    -1,    -1,    -1,    73,    25,    26,    -1,
      45,    -1,    -1,    -1,    -1,    15,    16,    17,    76,    77,
     227,    21,    22,    23,    24,    76,    77,    -1,    76,    77,
      -1,   238,    -1,   240,   241,    28,    29,   244,   245,   246,
      -1,    76,    77,    36,   251,   252,    39,    40,    73,    74,
      -1,    -1,    -1,   254,    -1,    73,    74,    -1,   265,   266,
     261,   268,   269,     3,    -1,     5,    -1,     7,   275,   276,
      -1,     8,    12,    13,    14,    75,   283,   284,    -1,    -1,
      20,    -1,    82,    83,    84,    85,    26,    -1,    -1,    11,
      -1,    -1,    -1,    33,    34,    35,    -1,    -1,    20,     8,
      -1,    41,    42,    25,    26,    -1,    46,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    74,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    73,    74,    -1,    -1,    25,    26,    -1,    -1,    26,
      -1,    11,    -1,    33,    34,    35,    -1,    76,    77,     8,
      20,    41,    42,    -1,    -1,    25,    26,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    -1,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    -1,    -1,    73,    -1,    25,    26,    -1,    -1,    26,
      -1,    18,    19,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    30,    31,    32,    -1,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    -1,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    26,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    74,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    26,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    -1,    -1,    72,    -1,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    74,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,   118,   119,   120,   121,   122,   123,   124,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    48,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    -1,     5,    45,     7,     8,    -1,
      -1,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    -1,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    -1,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    -1,     5,    45,     7,    -1,    76,
      77,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,     8,
      -1,    41,    42,    -1,    -1,    -1,    -1,    47,    -1,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     3,    -1,     5,    45,     7,    -1,    -1,
       8,    81,    12,    13,    14,    -1,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    -1,    76,    77,    -1,
      -1,    41,    42,    -1,     3,    -1,     5,    45,     7,    49,
       8,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    -1,    33,    34,    -1,     8,    76,    77,
       8,    81,    41,    42,     8,    -1,    86,    45,     8,    -1,
      49,     8,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    45,    -1,    -1,    45,    76,    77,
      -1,    45,    -1,    26,     8,    45,     8,    86,    45,     8,
      -1,     8,    26,     8,    -1,    26,    -1,    -1,    -1,    26,
      -1,    11,    45,    -1,    -1,    76,    77,    -1,    76,    77,
      20,    45,    76,    77,    45,    25,    76,    77,    45,    76,
      77,    45,    26,    45,    -1,    26,    45,    -1,    45,    -1,
      45,    -1,    -1,    76,    77,    -1,    -1,    -1,    48,    -1,
      -1,    45,    76,    77,    45,    76,    77,    -1,    -1,    76,
      77,    -1,    76,    77,    76,    77,    -1,    76,    77,    76,
      77,    76,    77,    73,    37,    38,     8,    -1,    -1,    -1,
      43,    44,    76,    77,    -1,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    79,    80
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,    12,    13,    14,    20,    33,    34,
      35,    41,    42,    47,    49,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    81,    86,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   106,   107,   108,   109,
      90,    90,    99,    99,    99,    25,    26,    92,     7,    90,
      28,    29,    36,    39,    40,     5,    35,    90,    48,    92,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    99,   102,     0,    88,     4,    45,    76,
      77,    11,    20,    25,    73,    27,    28,    29,    37,    38,
      43,    44,    78,    79,    80,    98,    18,    19,    30,    31,
      32,    15,    16,    17,    21,    22,    23,    24,    75,    82,
      83,    84,    85,    50,   105,     8,    90,    90,     6,     8,
      92,    92,    26,    90,    35,    35,    97,    35,    35,    90,
      26,    26,    73,    48,    26,     8,     8,     8,     8,     8,
       8,     8,     8,     8,     8,    26,     8,    26,    26,    26,
      26,     8,    26,    26,    26,     8,     8,    91,    91,    91,
      92,    25,    26,    92,    92,    26,    46,    74,    92,    94,
      94,    94,    97,    97,    97,    97,    97,    97,    97,    99,
      99,    99,    99,    99,   102,    26,     8,    26,     8,    26,
      92,     8,    26,    35,    90,    35,    92,    73,    90,    90,
      90,    90,    90,    90,    90,    90,    92,    92,    26,    92,
      26,    74,    92,    92,    26,    46,    74,    50,     8,     8,
       8,    26,    74,    92,    26,     8,     8,     8,     8,     8,
       8,    26,    92,    92,    92,    26,    74,    92,    26,    74,
      92,    92,     6,    92,    92,    26,    74,    90,    90,    92,
      92,    92,    92,    26,    74,    92,    92,     8,     8,    92,
      92
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
      yyerror (&yylloc, scanner, defined_nets, defined_funcs, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
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
		  Type, Value, Location, scanner, defined_nets, defined_funcs); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct defined_networks *defined_nets, struct defined_functions *defined_funcs)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, defined_nets, defined_funcs)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void *scanner;
    struct defined_networks *defined_nets;
    struct defined_functions *defined_funcs;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (defined_nets);
  YYUSE (defined_funcs);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct defined_networks *defined_nets, struct defined_functions *defined_funcs)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, defined_nets, defined_funcs)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void *scanner;
    struct defined_networks *defined_nets;
    struct defined_functions *defined_funcs;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner, defined_nets, defined_funcs);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, void *scanner, struct defined_networks *defined_nets, struct defined_functions *defined_funcs)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, scanner, defined_nets, defined_funcs)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    void *scanner;
    struct defined_networks *defined_nets;
    struct defined_functions *defined_funcs;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , scanner, defined_nets, defined_funcs);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, scanner, defined_nets, defined_funcs); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner, struct defined_networks *defined_nets, struct defined_functions *defined_funcs)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, scanner, defined_nets, defined_funcs)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    void *scanner;
    struct defined_networks *defined_nets;
    struct defined_functions *defined_funcs;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (scanner);
  YYUSE (defined_nets);
  YYUSE (defined_funcs);

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
int yyparse (void *scanner, struct defined_networks *defined_nets, struct defined_functions *defined_funcs);
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
yyparse (void *scanner, struct defined_networks *defined_nets, struct defined_functions *defined_funcs)
#else
int
yyparse (scanner, defined_nets, defined_funcs)
    void *scanner;
    struct defined_networks *defined_nets;
    struct defined_functions *defined_funcs;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

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

/* User initialization code.  */

/* Line 1590 of yacc.c  */
#line 211 "regex.y"
{
    clear_quantifiers();
    rewrite = 0;
    contexts = NULL;
    rules = NULL;
    rewrite_rules = NULL;
    rule_direction = 0;
    substituting = 0;
}

/* Line 1590 of yacc.c  */
#line 1986 "regex.c"

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
        case 4:

/* Line 1806 of yacc.c  */
#line 256 "regex.y"
    { current_parse = (yyvsp[(1) - (2)].net);              }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 258 "regex.y"
    { }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 259 "regex.y"
    { (yyval.net) = fsm_compose((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));         }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 260 "regex.y"
    { (yyval.net) = fsm_lenient_compose((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 261 "regex.y"
    { (yyval.net) = fsm_cross_product((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));   }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 263 "regex.y"
    { if (rewrite) { add_rewrite_rule(); (yyval.net) = fsm_rewrite(rewrite_rules); clear_rewrite_ruleset(rewrite_rules); } rewrite = 0; contexts = NULL; rules = NULL; rewrite_rules = NULL; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 265 "regex.y"
    { }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 266 "regex.y"
    { (yyval.net) = NULL; add_context_pair((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 267 "regex.y"
    { add_context_pair((yyvsp[(1) - (2)].net),fsm_empty_string()); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 268 "regex.y"
    { add_context_pair((yyvsp[(1) - (4)].net),fsm_empty_string()); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 269 "regex.y"
    { add_context_pair(fsm_empty_string(),fsm_empty_string());}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 270 "regex.y"
    { add_rewrite_rule(); add_context_pair(fsm_empty_string(),fsm_empty_string());}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 271 "regex.y"
    { add_rewrite_rule(); add_context_pair((yyvsp[(1) - (4)].net),fsm_empty_string());}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 272 "regex.y"
    { add_context_pair(fsm_empty_string(),fsm_empty_string());}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 273 "regex.y"
    { add_context_pair(fsm_empty_string(),(yyvsp[(2) - (2)].net)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 274 "regex.y"
    { add_context_pair(fsm_empty_string(),(yyvsp[(2) - (4)].net)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 275 "regex.y"
    { add_context_pair((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 276 "regex.y"
    { (yyval.net) = fsm_context_restrict((yyvsp[(1) - (3)].net),contexts); fsm_clear_contexts(contexts);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 277 "regex.y"
    { add_rule((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net),NULL,(yyvsp[(2) - (3)].type)); if ((yyvsp[(1) - (3)].net)->arity == 2) { printf("Error: LHS is transducer\n"); YYERROR;}}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 278 "regex.y"
    { add_rule((yyvsp[(1) - (2)].net),NULL,NULL,(yyvsp[(2) - (2)].type)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 280 "regex.y"
    { add_rule((yyvsp[(2) - (5)].net),(yyvsp[(5) - (5)].net),NULL,(yyvsp[(4) - (5)].type)|ARROW_DOTTED); if ((yyvsp[(5) - (5)].net) == NULL) { YYERROR;}}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 281 "regex.y"
    { add_eprule((yyvsp[(4) - (4)].net),NULL,(yyvsp[(3) - (4)].type)|ARROW_DOTTED); if ((yyvsp[(4) - (4)].net) == NULL) { YYERROR;}}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 282 "regex.y"
    { add_rule((yyvsp[(2) - (7)].net),(yyvsp[(5) - (7)].net),NULL,(yyvsp[(4) - (7)].type)|ARROW_DOTTED);}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 283 "regex.y"
    { add_eprule((yyvsp[(4) - (6)].net),NULL,(yyvsp[(3) - (6)].type)|ARROW_DOTTED);}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 284 "regex.y"
    { add_rule((yyvsp[(2) - (7)].net),(yyvsp[(5) - (7)].net),NULL,(yyvsp[(4) - (7)].type)|ARROW_DOTTED); rule_direction = (yyvsp[(6) - (7)].type);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 285 "regex.y"
    { add_eprule((yyvsp[(4) - (6)].net),NULL,(yyvsp[(3) - (6)].type)|ARROW_DOTTED); rule_direction = (yyvsp[(5) - (6)].type);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 286 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net),NULL,(yyvsp[(2) - (5)].type));}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 287 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),NULL,NULL,(yyvsp[(2) - (4)].type));}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 288 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net),NULL,(yyvsp[(2) - (5)].type)); rule_direction = (yyvsp[(4) - (5)].type);}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 289 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),NULL,NULL,(yyvsp[(2) - (4)].type)); rule_direction = (yyvsp[(3) - (4)].type);}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 291 "regex.y"
    { add_rewrite_rule();}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 293 "regex.y"
    { add_rule((yyvsp[(1) - (3)].net),fsm_empty_string(),fsm_empty_string(),(yyvsp[(2) - (3)].type));}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 294 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),fsm_empty_string(),(yyvsp[(4) - (4)].net),(yyvsp[(2) - (4)].type));}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 295 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),(yyvsp[(3) - (4)].net),fsm_empty_string(),(yyvsp[(2) - (4)].type));}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 296 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net),(yyvsp[(5) - (5)].net),(yyvsp[(2) - (5)].type));}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 297 "regex.y"
    { add_rule((yyvsp[(1) - (7)].net),(yyvsp[(3) - (7)].net),(yyvsp[(5) - (7)].net),(yyvsp[(2) - (7)].type));}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 298 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),(yyvsp[(3) - (6)].net),fsm_empty_string(),(yyvsp[(2) - (6)].type));}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 299 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),fsm_empty_string(),(yyvsp[(4) - (6)].net),(yyvsp[(2) - (6)].type));}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 300 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),fsm_empty_string(),fsm_empty_string(),(yyvsp[(2) - (5)].type));}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 301 "regex.y"
    { add_rule((yyvsp[(1) - (7)].net),(yyvsp[(3) - (7)].net),(yyvsp[(5) - (7)].net),(yyvsp[(2) - (7)].type)); rule_direction = (yyvsp[(6) - (7)].type);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 302 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),fsm_empty_string(),(yyvsp[(4) - (6)].net),(yyvsp[(2) - (6)].type)); rule_direction = (yyvsp[(5) - (6)].type);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 303 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),(yyvsp[(3) - (6)].net),fsm_empty_string(),(yyvsp[(2) - (6)].type)); rule_direction = (yyvsp[(5) - (6)].type);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 304 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),fsm_empty_string(),fsm_empty_string(),(yyvsp[(2) - (5)].type)); rule_direction = (yyvsp[(4) - (5)].type);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 307 "regex.y"
    { }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 308 "regex.y"
    { (yyval.net) = fsm_shuffle((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));  }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 309 "regex.y"
    { (yyval.net) = fsm_precedes((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 310 "regex.y"
    { (yyval.net) = fsm_follows((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));  }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 312 "regex.y"
    { }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 314 "regex.y"
    { }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 316 "regex.y"
    { }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 317 "regex.y"
    { (yyval.net) = fsm_union((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                     }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 318 "regex.y"
    { (yyval.net) = fsm_priority_union_upper((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));      }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 319 "regex.y"
    { (yyval.net) = fsm_priority_union_lower((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));      }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 320 "regex.y"
    { (yyval.net) = fsm_intersect((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                 }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 321 "regex.y"
    { (yyval.net) = fsm_minus((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                     }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 322 "regex.y"
    { (yyval.net) = fsm_union(fsm_complement((yyvsp[(1) - (3)].net)),(yyvsp[(3) - (3)].net));     }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 323 "regex.y"
    { (yyval.net) = fsm_intersect(fsm_union(fsm_complement(fsm_copy((yyvsp[(1) - (3)].net))),fsm_copy((yyvsp[(3) - (3)].net))), fsm_union(fsm_complement(fsm_copy((yyvsp[(3) - (3)].net))),fsm_copy((yyvsp[(1) - (3)].net)))); fsm_destroy((yyvsp[(1) - (3)].net)); fsm_destroy((yyvsp[(3) - (3)].net));}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 325 "regex.y"
    { }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 326 "regex.y"
    { (yyval.net) = fsm_concat((yyvsp[(1) - (2)].net),(yyvsp[(2) - (2)].net)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 327 "regex.y"
    { (yyval.net) = fsm_ignore(fsm_contains(fsm_concat(fsm_symbol((yyvsp[(1) - (3)].string)),fsm_concat((yyvsp[(3) - (3)].net),fsm_symbol((yyvsp[(1) - (3)].string))))),union_quantifiers(),OP_IGNORE_ALL); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 329 "regex.y"
    { (yyval.net) = fsm_logical_eq((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 330 "regex.y"
    { (yyval.net) = fsm_complement(fsm_logical_eq((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string))); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 331 "regex.y"
    { (yyval.net) = fsm_logical_precedence((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 332 "regex.y"
    { (yyval.net) = fsm_logical_precedence((yyvsp[(3) - (3)].string),(yyvsp[(1) - (3)].string)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 334 "regex.y"
    { }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 335 "regex.y"
    { (yyval.net) = fsm_ignore((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net), OP_IGNORE_ALL);          }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 336 "regex.y"
    { (yyval.net) = fsm_ignore((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net), OP_IGNORE_INTERNAL);     }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 337 "regex.y"
    { (yyval.net) = fsm_quotient_right((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                 }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 338 "regex.y"
    { (yyval.net) = fsm_quotient_left((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                  }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 339 "regex.y"
    { (yyval.net) = fsm_quotient_interleave((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));            }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 341 "regex.y"
    { }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 342 "regex.y"
    { (yyval.net) = fsm_complement((yyvsp[(2) - (2)].net));       }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 343 "regex.y"
    { (yyval.net) = fsm_contains((yyvsp[(2) - (2)].net));         }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 344 "regex.y"
    { (yyval.net) = fsm_contains_one((yyvsp[(2) - (2)].net));     }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 345 "regex.y"
    { (yyval.net) = fsm_contains_opt_one((yyvsp[(2) - (2)].net)); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 347 "regex.y"
    { }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 349 "regex.y"
    { }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 350 "regex.y"
    { (yyval.net) = fsm_kleene_star(fsm_minimize((yyvsp[(1) - (2)].net))); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 351 "regex.y"
    { (yyval.net) = fsm_kleene_plus((yyvsp[(1) - (2)].net)); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 352 "regex.y"
    { (yyval.net) = fsm_determinize(fsm_reverse((yyvsp[(1) - (2)].net))); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 353 "regex.y"
    { (yyval.net) = fsm_invert((yyvsp[(1) - (2)].net)); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 354 "regex.y"
    { (yyval.net) = fsm_upper((yyvsp[(1) - (2)].net)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 355 "regex.y"
    { (yyval.net) = fsm_lower((yyvsp[(1) - (2)].net)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 356 "regex.y"
    { (yyval.net) = flag_eliminate((yyvsp[(1) - (2)].net), NULL); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 357 "regex.y"
    { (yyval.net) = fsm_cross_product((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 359 "regex.y"
    { (yyval.net) = fsm_concat_n((yyvsp[(1) - (2)].net),atoi((yyvsp[(2) - (2)].string))); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 360 "regex.y"
    { (yyval.net) = fsm_concat(fsm_concat_n(fsm_copy((yyvsp[(1) - (2)].net)), atoi((yyvsp[(2) - (2)].string))),fsm_kleene_plus(fsm_copy((yyvsp[(1) - (2)].net)))); fsm_destroy((yyvsp[(1) - (2)].net)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 361 "regex.y"
    { (yyval.net) = fsm_concat_m_n((yyvsp[(1) - (2)].net),0,atoi((yyvsp[(2) - (2)].string))-1); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 362 "regex.y"
    { (yyval.net) = fsm_concat_m_n((yyvsp[(1) - (2)].net),atoi((yyvsp[(2) - (2)].string)),atoi(strstr((yyvsp[(2) - (2)].string),",")+1)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 364 "regex.y"
    { }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 365 "regex.y"
    { (yyval.net) = fsm_term_negation((yyvsp[(2) - (2)].net)); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 367 "regex.y"
    { (yyval.net) = (yyvsp[(1) - (1)].net);}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 368 "regex.y"
    { (yyval.net) = (yyvsp[(1) - (1)].net); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 369 "regex.y"
    { (yyval.net) = fsm_complement(fsm_substitute_symbol(fsm_intersect(fsm_quantifier((yyvsp[(1) - (4)].string)),fsm_complement((yyvsp[(3) - (4)].net))),(yyvsp[(1) - (4)].string),"@_EPSILON_SYMBOL_@")); purge_quantifier((yyvsp[(1) - (4)].string)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 370 "regex.y"
    {  (yyval.net) = fsm_substitute_symbol(fsm_intersect(fsm_quantifier((yyvsp[(1) - (2)].string)),(yyvsp[(2) - (2)].net)),(yyvsp[(1) - (2)].string),"@_EPSILON_SYMBOL_@"); purge_quantifier((yyvsp[(1) - (2)].string)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 371 "regex.y"
    { if (count_quantifiers()) (yyval.net) = (yyvsp[(2) - (3)].net); else {(yyval.net) = fsm_optionality((yyvsp[(2) - (3)].net));} }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 372 "regex.y"
    { (yyval.net) = (yyvsp[(2) - (3)].net); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 373 "regex.y"
    {(yyval.net) = fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(union_quantifiers(),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_universal())))))))); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 374 "regex.y"
    {(yyval.net) = fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(fsm_ignore((yyvsp[(4) - (5)].net),union_quantifiers(),OP_IGNORE_ALL),fsm_universal()))))); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 375 "regex.y"
    {(yyval.net) = fsm_concat(fsm_universal(),fsm_concat(fsm_ignore((yyvsp[(2) - (5)].net),union_quantifiers(),OP_IGNORE_ALL),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_universal()))))); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 376 "regex.y"
    {(yyval.net) = fsm_substitute_symbol((yyvsp[(1) - (2)].net),subval1,subval2); substituting = 0; xxfree(subval1); xxfree(subval2); subval1 = subval2 = NULL;}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 378 "regex.y"
    { (yyval.net) = (yyvsp[(3) - (4)].net); substituting = 1;                      }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 379 "regex.y"
    { subval1 = (yyvsp[(2) - (4)].string); subval2 = (yyvsp[(4) - (4)].string); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 381 "regex.y"
    { (yyval.net) = (yyvsp[(1) - (1)].net); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 382 "regex.y"
    { (yyval.net) = fsm_boolean(fsm_isidentity((yyvsp[(2) - (3)].net)));   }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 383 "regex.y"
    { (yyval.net) = fsm_boolean(fsm_isfunctional((yyvsp[(2) - (3)].net))); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 384 "regex.y"
    { (yyval.net) = fsm_boolean(fsm_isunambiguous((yyvsp[(2) - (3)].net))); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 385 "regex.y"
    { (yyval.net) = fsm_extract_nonidentity(fsm_copy((yyvsp[(2) - (3)].net))); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 386 "regex.y"
    { (yyval.net) = fsm_lowerdet(fsm_copy((yyvsp[(2) - (3)].net))); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 387 "regex.y"
    { (yyval.net) = fsm_lowerdeteps(fsm_copy((yyvsp[(2) - (3)].net))); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 388 "regex.y"
    { (yyval.net) = fsm_markallfinal(fsm_copy((yyvsp[(2) - (3)].net))); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 389 "regex.y"
    { (yyval.net) = fsm_extract_unambiguous(fsm_copy((yyvsp[(2) - (3)].net)));      }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 390 "regex.y"
    { (yyval.net) = fsm_extract_ambiguous(fsm_copy((yyvsp[(2) - (3)].net)));        }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 391 "regex.y"
    { (yyval.net) = fsm_extract_ambiguous_domain(fsm_copy((yyvsp[(2) - (3)].net))); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 392 "regex.y"
    { (yyval.net) = fsm_letter_machine(fsm_copy((yyvsp[(2) - (3)].net))); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 393 "regex.y"
    { (yyval.net) = fsm_mark_fsm_tail((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net)); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 394 "regex.y"
    { (yyval.net) = fsm_add_loop((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net),1); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 395 "regex.y"
    { (yyval.net) = fsm_add_loop((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net),0); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 396 "regex.y"
    { (yyval.net) = fsm_add_loop((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net),2); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 397 "regex.y"
    { (yyval.net) = fsm_add_sink((yyvsp[(2) - (3)].net),1); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 398 "regex.y"
    { (yyval.net) = fsm_left_rewr((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net)); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 399 "regex.y"
    { (yyval.net) = fsm_flatten((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 400 "regex.y"
    { (yyval.net) = fsm_substitute_label((yyvsp[(2) - (7)].net), fsm_network_to_char((yyvsp[(4) - (7)].net)), (yyvsp[(6) - (7)].net)); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 401 "regex.y"
    { (yyval.net) = fsm_close_sigma(fsm_copy((yyvsp[(2) - (3)].net)), 0); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 402 "regex.y"
    { (yyval.net) = fsm_close_sigma(fsm_copy((yyvsp[(2) - (3)].net)), 1); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 403 "regex.y"
    { (yyval.net) = fsm_equal_substrings((yyvsp[(2) - (7)].net),(yyvsp[(4) - (7)].net),(yyvsp[(6) - (7)].net)); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 406 "regex.y"
    { frec++; fargptr[frec] = 0 ;declare_function_name((yyvsp[(1) - (3)].string)) ; add_function_argument((yyvsp[(2) - (3)].net)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 408 "regex.y"
    { frec++; fargptr[frec] = 0 ;declare_function_name((yyvsp[(1) - (2)].string)) ; add_function_argument((yyvsp[(2) - (2)].net)); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 410 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 411 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 414 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); if (((yyval.net) = function_apply(defined_nets, defined_funcs)) == NULL) YYERROR; }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 416 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); if (((yyval.net) = function_apply(defined_nets, defined_funcs)) == NULL) YYERROR; }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 418 "regex.y"
    { if (((yyval.net) = function_apply(defined_nets, defined_funcs)) == NULL) YYERROR;}
    break;



/* Line 1806 of yacc.c  */
#line 3104 "regex.c"
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
      yyerror (&yylloc, scanner, defined_nets, defined_funcs, YY_("syntax error"));
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
        yyerror (&yylloc, scanner, defined_nets, defined_funcs, yymsgp);
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
		      yytoken, &yylval, &yylloc, scanner, defined_nets, defined_funcs);
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
		  yystos[yystate], yyvsp, yylsp, scanner, defined_nets, defined_funcs);
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
  yyerror (&yylloc, scanner, defined_nets, defined_funcs, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, scanner, defined_nets, defined_funcs);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, scanner, defined_nets, defined_funcs);
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
#line 420 "regex.y"


