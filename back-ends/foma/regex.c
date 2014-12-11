/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 18 "regex.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "foma.h"
#define MAX_F_RECURSION 100
extern int yyerror();
extern int yylex();
extern int my_yyparse(char *my_string);
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

struct fsm *function_apply(void) {
    int i, mygsym, myfargptr;
    char *regex;
    char repstr[13], oldstr[13];
    if ((regex = find_defined_function(fname[frec],fargptr[frec])) == NULL) {
        printf("***Error: function %s@%i) not defined!\n",fname[frec], fargptr[frec]);
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
        add_defined(fargs[i][frec], repstr);
        g_internal_sym++;
    }
    
    my_yyparse(regex);
    for (i = 0; i < myfargptr; i++) {
        sprintf(repstr,"%012X",mygsym);
        /* Remove the temporarily defined network */
        remove_defined(repstr);
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
        new_rewrite_rule->cpunion = NULL;

        rewrite_rules = new_rewrite_rule;
        rules = NULL;
        contexts = NULL;
        rule_direction = 0;
    }
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




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 188 "regex.y"
{
     char *string;
     struct fsm *net;
     int  type;
}
/* Line 193 of yacc.c.  */
#line 438 "regex.tab.c"
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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 463 "regex.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  99
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNRULES -- Number of states.  */
#define YYNSTATES  278

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
     482,   488,   494,   500,   504,   510,   516,   524,   528,   531,
     535,   539,   543,   547
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      85,     0,    -1,    86,    -1,    86,    85,    -1,    87,     4,
      -1,    88,    -1,    87,    74,    88,    -1,    87,    45,    88,
      -1,    87,    73,    88,    -1,    89,    -1,    90,    -1,    89,
      20,    89,    -1,    89,    20,    -1,    89,    20,    26,    89,
      -1,    20,    -1,    20,    25,    89,    -1,    89,    20,    25,
      89,    -1,    20,    26,    89,    -1,    20,    89,    -1,    20,
      89,    26,    89,    -1,    89,    20,    89,    26,    89,    -1,
      89,    11,    89,    -1,    89,    70,    89,    -1,    89,    70,
      -1,    47,    89,    48,    70,    89,    -1,    47,    48,    70,
      89,    -1,    47,    89,    48,    70,    89,    26,    89,    -1,
      47,    48,    70,    89,    26,    89,    -1,    47,    89,    48,
      70,    89,    71,    89,    -1,    47,    48,    70,    89,    71,
      89,    -1,    89,    70,    89,    26,    89,    -1,    89,    70,
      26,    89,    -1,    89,    70,    89,    71,    89,    -1,    89,
      70,    71,    89,    -1,    89,    25,    89,    -1,    89,    70,
      46,    -1,    89,    70,    46,    89,    -1,    89,    70,    89,
      46,    -1,    89,    70,    89,    46,    89,    -1,    89,    70,
      89,    46,    89,    26,    89,    -1,    89,    70,    89,    46,
      26,    89,    -1,    89,    70,    46,    89,    26,    89,    -1,
      89,    70,    46,    26,    89,    -1,    89,    70,    89,    46,
      89,    71,    89,    -1,    89,    70,    46,    89,    71,    89,
      -1,    89,    70,    89,    46,    71,    89,    -1,    89,    70,
      46,    71,    89,    -1,    91,    -1,    90,    27,    91,    -1,
      90,    28,    91,    -1,    90,    29,    91,    -1,    92,    -1,
      93,    -1,    94,    -1,    93,    77,    94,    -1,    93,    43,
      94,    -1,    93,    44,    94,    -1,    93,    76,    94,    -1,
      93,    75,    94,    -1,    93,    37,    94,    -1,    93,    38,
      94,    -1,    95,    -1,    94,    95,    -1,    35,    36,    94,
      -1,    35,    39,    35,    -1,    35,    40,    35,    -1,    35,
      28,    35,    -1,    35,    29,    35,    -1,    96,    -1,    95,
      18,    96,    -1,    95,    19,    96,    -1,    95,    30,    96,
      -1,    95,    31,    96,    -1,    95,    32,    96,    -1,    97,
      -1,    78,    96,    -1,    12,    96,    -1,    14,    96,    -1,
      13,    96,    -1,    98,    -1,    99,    -1,    98,    82,    -1,
      98,    81,    -1,    98,    80,    -1,    98,    79,    -1,    98,
      15,    -1,    98,    16,    -1,    98,    17,    -1,    98,    72,
      99,    -1,    98,    21,    -1,    98,    23,    -1,    98,    24,
      -1,    98,    22,    -1,   100,    -1,    83,    99,    -1,     3,
      -1,   103,    -1,    33,     7,    87,     8,    -1,    34,    87,
      -1,     7,    87,     8,    -1,     5,    87,     6,    -1,    42,
      35,    26,    35,     8,    -1,    42,    35,    26,    87,     8,
      -1,    42,    87,    26,    35,     8,    -1,   101,   102,    -1,
      41,     5,    87,    26,    -1,    50,    26,    50,     6,    -1,
     106,    -1,    52,    87,     8,    -1,    53,    87,     8,    -1,
      51,    87,     8,    -1,    54,    87,     8,    -1,    55,    87,
       8,    -1,    56,    87,     8,    -1,    57,    87,     8,    -1,
      58,    87,     8,    -1,    59,    87,     8,    -1,    60,    87,
       8,    -1,    62,    87,     8,    -1,    63,    87,    26,    87,
       8,    -1,    64,    87,    26,    87,     8,    -1,    65,    87,
      26,    87,     8,    -1,    66,    87,    26,    87,     8,    -1,
      67,    87,     8,    -1,    68,    87,    26,    87,     8,    -1,
      69,    87,    26,    87,     8,    -1,    61,    87,    26,    87,
      26,    87,     8,    -1,    49,    87,    26,    -1,    49,    87,
      -1,   104,    87,    26,    -1,   105,    87,    26,    -1,   105,
      87,     8,    -1,   104,    87,     8,    -1,   104,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   240,   240,   241,   244,   246,   247,   248,   249,   251,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   279,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   295,   296,   297,
     298,   300,   302,   304,   305,   306,   307,   308,   309,   310,
     311,   313,   314,   315,   317,   318,   319,   320,   322,   323,
     324,   325,   326,   327,   329,   330,   331,   332,   333,   335,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   347,
     348,   349,   350,   352,   353,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   366,   367,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   390,   392,   395,
     396,   398,   400,   402
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
  "MARKFSMLOOP", "ADDSINK", "LEFTREWR", "FLATTEN", "ARROW", "DIRECTION",
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
     335,   336,   337,   338
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    86,    87,    87,    87,    87,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    90,    90,    90,
      90,    91,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      95,    95,    95,    95,    96,    96,    96,    96,    96,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    99,    99,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   102,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   104,   105,
     105,   106,   106,   106
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
       5,     5,     5,     3,     5,     5,     7,     3,     2,     3,
       3,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    95,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     0,     5,
       9,    10,    47,    51,    52,    53,    61,    68,    74,    79,
      80,    93,     0,    96,     0,     0,   107,     0,     0,    76,
      78,    77,     0,     0,    18,     0,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    75,    94,     1,
       3,     4,     0,     0,     0,     0,    12,     0,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    62,
       0,     0,     0,     0,     0,    85,    86,    87,    89,    92,
      90,    91,     0,    84,    83,    82,    81,     0,   104,   133,
       0,     0,   100,    99,    15,    17,     0,     0,    66,    67,
      63,    64,    65,     0,     0,     0,     0,     0,   127,   110,
     108,   109,   111,   112,   113,   114,   115,   116,   117,     0,
     118,     0,     0,     0,     0,   123,     0,     0,     7,     8,
       6,    21,     0,     0,    11,    34,     0,    35,     0,    22,
      48,    49,    50,    59,    60,    55,    56,    58,    57,    54,
      69,    70,    71,    72,    73,    88,     0,   132,   129,   131,
     130,    19,    97,   105,     0,     0,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    13,     0,    31,
       0,     0,    36,    33,     0,    37,     0,     0,   101,   102,
     103,     0,     0,    24,     0,   119,   120,   121,   122,   124,
     125,    20,    42,    46,     0,     0,    30,     0,     0,    38,
      32,   106,    27,    29,     0,     0,     0,    41,    44,    40,
      45,     0,     0,    26,    28,   126,    39,    43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,   138,    53,
      54,    55,    56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -46
static const yytype_int16 yypact[] =
{
     718,   -46,   718,   718,   986,   986,   986,   316,     0,   718,
     909,     5,   785,   584,   718,   718,   718,   718,   718,   718,
     718,   718,   718,   718,   718,   718,   718,   718,   718,   718,
     718,   718,   718,   718,   986,  1026,     9,   718,     4,   -46,
       1,    35,   -46,   -46,  1084,   986,   188,   -46,   -46,    36,
     -46,   -46,   -37,   -46,   651,   718,   -46,    16,    20,   -46,
     -46,   -46,   718,   718,   206,   718,    40,   -19,   -16,   919,
     -15,   -12,   718,   -25,    50,   -45,   609,   453,    60,    67,
      84,    98,   120,   122,   129,   140,   165,   170,   654,   197,
     721,   788,   855,   921,   200,   989,  1071,   -46,   -46,   -46,
     -46,   -46,   718,   718,   718,   718,   383,   718,   249,   919,
     919,   919,   919,   919,   919,   919,   919,   919,   919,   188,
     986,   986,   986,   986,   986,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,  1026,   -46,   -46,   -46,   -46,    24,   -46,   -46,
      46,    58,   -46,   -46,     1,     1,   718,   204,   -46,   -46,
     986,   -46,   -46,  1073,   852,    32,   718,     3,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   718,
     -46,   718,   718,   718,   718,   -46,   718,   718,   -46,   -46,
     -46,     1,   718,   718,   602,     1,   718,   450,   718,  1085,
     -46,   -46,   -46,   986,   986,   986,   986,   986,   986,   986,
     -46,   -46,   -46,   -46,   -46,   -46,    29,   -46,   -46,   -46,
     -46,     1,   -46,   -46,   982,   252,    66,   470,   718,  1075,
     279,   286,   346,   348,   353,   415,     1,     1,   718,     1,
     718,   718,   535,     1,   718,   517,   718,    80,   -46,   -46,
     -46,   718,   718,   537,   718,   -46,   -46,   -46,   -46,   -46,
     -46,     1,     1,     1,   718,   718,     1,   718,   718,   590,
       1,   -46,     1,     1,   718,   718,   420,     1,     1,     1,
       1,   718,   718,     1,     1,   -46,     1,     1
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,    59,   -46,    15,    23,    -7,   -46,    51,   -46,   -46,
     627,   -43,    77,   -46,   -46,   -30,   -46,   -46,   -46,   -46,
     -46,   -46,   -46
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      64,   154,   119,    67,    68,    98,    76,    65,   101,    99,
      72,    69,   105,   137,    70,    71,   148,    57,    58,   149,
     151,   106,   142,   152,    66,   156,   107,    74,   143,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,   102,
     206,   125,   126,   127,   207,   144,   145,   128,   129,   130,
     131,   102,   109,   110,   111,   102,   209,   216,   159,   140,
     141,   108,   208,   218,   240,   160,   155,   103,   104,   237,
     147,    59,    60,    61,   210,   102,   261,   153,     0,   103,
     104,   102,   161,   103,   104,   102,   100,     0,   181,   184,
     185,   189,   205,   102,     0,   102,   162,   119,   132,     0,
       0,    97,   102,   103,   104,   133,   134,   135,   136,   103,
     104,     0,     0,   103,   104,   178,   179,   180,   163,   102,
     164,   103,   104,   103,   104,     0,     0,   165,     0,   211,
     103,   104,     0,   102,     0,     0,     0,     0,   166,   217,
     119,   119,   119,   119,   119,   119,   119,   103,   104,     0,
     190,   191,   192,     0,     0,   102,     0,   102,     0,   215,
       0,   103,   104,   167,   102,   226,   227,     0,   168,   229,
     232,   233,     0,     0,   219,   102,   220,   221,   222,   223,
       0,   224,   225,   103,   104,   103,   104,   200,   201,   202,
     203,   204,   103,   104,     0,   170,   120,   121,   175,     0,
     102,   243,   212,   103,   104,   102,     0,   105,   122,   123,
     124,   251,     0,   252,   253,     0,   106,   256,   259,   260,
       0,   107,   146,     0,   262,   263,     0,     0,   103,   104,
       0,     0,   102,   103,   104,   102,     0,   267,   268,   102,
     269,   270,     1,     0,     2,     0,     3,   273,   274,   266,
     239,     4,     5,     6,   276,   277,     0,     0,     0,     7,
     103,   104,     0,   103,   104,   186,   108,   103,   104,     0,
       0,     0,     8,     9,    10,     0,     0,   245,     0,     0,
      11,    12,     0,     0,   246,   187,    13,   102,    14,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     1,
     188,     2,     0,     3,   102,   103,   104,    34,     4,     5,
       6,   102,    35,     0,     0,     0,     7,     0,     0,     0,
       0,    62,    63,     0,     0,     0,     0,     0,     0,     8,
       9,    10,   103,   104,   247,     0,   248,    11,    12,   103,
     104,   249,     0,    13,     0,    14,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     1,     0,     2,     0,
       3,   102,     0,   102,    34,     4,     5,     6,   102,    35,
       0,     0,     0,     7,     0,     0,     0,     0,   182,   183,
       0,     0,     0,     0,     0,     0,     8,     9,    10,   103,
     104,   103,   104,   250,    11,    12,   103,   104,   275,     0,
      13,     0,    14,     0,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     1,     0,     2,     0,     3,     0,     0,
     102,    34,     4,     5,     6,   102,    35,     0,     0,     0,
       7,     0,     0,     0,     0,     0,   230,     0,     0,   158,
       0,   105,     0,     8,     9,    10,     0,     0,   103,   104,
     106,    11,    12,   103,   104,   107,   241,    13,   102,    14,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       1,   231,     2,     0,     3,     0,   103,   104,    34,     4,
       5,     6,     0,    35,     0,     0,     0,     7,     0,     0,
     108,   242,     0,   257,     0,     0,   105,     0,   105,     0,
       8,     9,    10,     0,     0,   106,     0,   106,    11,    12,
     107,   254,   107,   264,    13,     0,    14,     0,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     1,   258,     2,
       0,     3,     0,     0,     0,    34,     4,     5,     6,     0,
      35,   105,     0,     0,     7,   108,   255,   108,   265,     0,
     106,     0,     0,   105,     0,   107,   271,     8,     9,    10,
     105,     0,   106,     0,     0,    11,    12,   107,   228,   106,
       0,    13,    75,    14,   107,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,     1,     0,     2,   157,     3,   139,
     108,   272,    34,     4,     5,     6,     0,    35,     0,     0,
       0,     7,   108,     0,     0,     0,     0,     0,     0,   108,
     169,     0,     0,     0,     8,     9,    10,     0,     0,     0,
       0,     0,    11,    12,     0,     0,   150,     0,    13,   102,
      14,     0,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,     1,     0,     2,     0,     3,     0,   103,   104,    34,
       4,     5,     6,     0,    35,     0,     0,     0,     7,   193,
     194,   195,   196,   197,   198,   199,     0,   171,     0,     0,
       0,     8,     9,    10,     0,     0,     0,     0,     0,    11,
      12,     0,     0,     0,     0,    13,   102,    14,     0,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     1,     0,
       2,     0,     3,     0,   103,   104,    34,     4,     5,     6,
       0,    35,     0,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,   172,     0,     0,     0,     8,     9,
      73,     0,     0,     0,     0,     0,    11,    12,     0,     0,
       0,     0,    13,   102,    14,     0,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,     1,     0,     2,     0,     3,
       0,   103,   104,    34,     4,     5,     6,     0,    35,     0,
       0,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,   173,     0,     0,     0,     8,     9,   214,     0,     0,
       0,     0,     0,    11,    12,     0,     0,     0,     0,    13,
     102,    14,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     1,     0,     2,     0,     3,     0,   103,   104,
      34,     4,     5,     6,     0,    35,     0,    67,    68,     0,
       0,     0,     0,     0,     0,    69,     0,   174,    70,    71,
       0,     0,     8,     9,    10,     0,     0,     0,     0,     0,
      11,    12,     0,     0,     0,     0,   102,     0,    14,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,     1,
     238,     2,     0,     3,   103,   104,     0,    34,     4,     5,
       6,     0,    35,     0,     0,     0,     0,     0,     0,     0,
      67,    68,     0,     0,     0,   176,     0,     0,    69,     8,
       9,    70,    71,     0,     0,     0,     0,    11,    12,     1,
       0,     2,     0,     3,   102,    14,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,     0,     0,     8,
       9,     0,   103,   104,    34,     0,     0,    11,    12,    35,
       0,     0,     0,     0,     0,    14,     0,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   105,   177,     0,   213,
       0,   244,     0,     0,     0,   106,     0,     0,     0,    35,
     107,   234,     0,     0,     0,     0,   102,     0,   102,     0,
     102,   112,   113,     0,     0,     0,     0,   114,   115,     0,
       0,   235,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   103,   104,   103,   104,   103,   104,
       0,     0,     0,     0,     0,   108,   236,     0,     0,   116,
     117,   118
};

static const yytype_int16 yycheck[] =
{
       7,    26,    45,    28,    29,    35,    13,     7,     4,     0,
       5,    36,    11,    50,    39,    40,    35,     2,     3,    35,
      35,    20,     6,    35,     9,    70,    25,    12,     8,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    45,
      26,    15,    16,    17,     8,    62,    63,    21,    22,    23,
      24,    45,    27,    28,    29,    45,     8,    35,     8,    54,
      55,    70,    26,    70,     8,     8,    26,    73,    74,    50,
      65,     4,     5,     6,    26,    45,     6,    72,    -1,    73,
      74,    45,     8,    73,    74,    45,    37,    -1,   105,   106,
     107,   108,   132,    45,    -1,    45,     8,   150,    72,    -1,
      -1,    34,    45,    73,    74,    79,    80,    81,    82,    73,
      74,    -1,    -1,    73,    74,   102,   103,   104,     8,    45,
       8,    73,    74,    73,    74,    -1,    -1,     8,    -1,   146,
      73,    74,    -1,    45,    -1,    -1,    -1,    -1,     8,   156,
     193,   194,   195,   196,   197,   198,   199,    73,    74,    -1,
     109,   110,   111,    -1,    -1,    45,    -1,    45,    -1,   154,
      -1,    73,    74,     8,    45,   182,   183,    -1,     8,   186,
     187,   188,    -1,    -1,   169,    45,   171,   172,   173,   174,
      -1,   176,   177,    73,    74,    73,    74,   120,   121,   122,
     123,   124,    73,    74,    -1,     8,    18,    19,     8,    -1,
      45,   218,     8,    73,    74,    45,    -1,    11,    30,    31,
      32,   228,    -1,   230,   231,    -1,    20,   234,   235,   236,
      -1,    25,    26,    -1,   241,   242,    -1,    -1,    73,    74,
      -1,    -1,    45,    73,    74,    45,    -1,   254,   255,    45,
     257,   258,     3,    -1,     5,    -1,     7,   264,   265,   244,
       8,    12,    13,    14,   271,   272,    -1,    -1,    -1,    20,
      73,    74,    -1,    73,    74,    26,    70,    73,    74,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,     8,    -1,    -1,
      41,    42,    -1,    -1,     8,    46,    47,    45,    49,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     3,
      71,     5,    -1,     7,    45,    73,    74,    78,    12,    13,
      14,    45,    83,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    73,    74,     8,    -1,     8,    41,    42,    73,
      74,     8,    -1,    47,    -1,    49,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,     3,    -1,     5,    -1,
       7,    45,    -1,    45,    78,    12,    13,    14,    45,    83,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    73,
      74,    73,    74,     8,    41,    42,    73,    74,     8,    -1,
      47,    -1,    49,    -1,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,     3,    -1,     5,    -1,     7,    -1,    -1,
      45,    78,    12,    13,    14,    45,    83,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    26,
      -1,    11,    -1,    33,    34,    35,    -1,    -1,    73,    74,
      20,    41,    42,    73,    74,    25,    26,    47,    45,    49,
      -1,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       3,    71,     5,    -1,     7,    -1,    73,    74,    78,    12,
      13,    14,    -1,    83,    -1,    -1,    -1,    20,    -1,    -1,
      70,    71,    -1,    26,    -1,    -1,    11,    -1,    11,    -1,
      33,    34,    35,    -1,    -1,    20,    -1,    20,    41,    42,
      25,    26,    25,    26,    47,    -1,    49,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,     3,    71,     5,
      -1,     7,    -1,    -1,    -1,    78,    12,    13,    14,    -1,
      83,    11,    -1,    -1,    20,    70,    71,    70,    71,    -1,
      20,    -1,    -1,    11,    -1,    25,    26,    33,    34,    35,
      11,    -1,    20,    -1,    -1,    41,    42,    25,    26,    20,
      -1,    47,    48,    49,    25,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     3,    -1,     5,    48,     7,     8,
      70,    71,    78,    12,    13,    14,    -1,    83,    -1,    -1,
      -1,    20,    70,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      26,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    69,    -1,    47,    45,
      49,    -1,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,     3,    -1,     5,    -1,     7,    -1,    73,    74,    78,
      12,    13,    14,    -1,    83,    -1,    -1,    -1,    20,   112,
     113,   114,   115,   116,   117,   118,    -1,    26,    -1,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    -1,    -1,    47,    45,    49,    -1,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     3,    -1,
       5,    -1,     7,    -1,    73,    74,    78,    12,    13,    14,
      -1,    83,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      -1,    -1,    47,    45,    49,    -1,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,     3,    -1,     5,    -1,     7,
      -1,    73,    74,    78,    12,    13,    14,    -1,    83,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    47,
      45,    49,    -1,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,     3,    -1,     5,    -1,     7,    -1,    73,    74,
      78,    12,    13,    14,    -1,    83,    -1,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    26,    39,    40,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    45,    -1,    49,    -1,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,     3,
       8,     5,    -1,     7,    73,    74,    -1,    78,    12,    13,
      14,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    29,    -1,    -1,    -1,    26,    -1,    -1,    36,    33,
      34,    39,    40,    -1,    -1,    -1,    -1,    41,    42,     3,
      -1,     5,    -1,     7,    45,    49,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    33,
      34,    -1,    73,    74,    78,    -1,    -1,    41,    42,    83,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    11,    26,    -1,    26,
      -1,    26,    -1,    -1,    -1,    20,    -1,    -1,    -1,    83,
      25,    26,    -1,    -1,    -1,    -1,    45,    -1,    45,    -1,
      45,    37,    38,    -1,    -1,    -1,    -1,    43,    44,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    73,    74,    73,    74,
      -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,    75,
      76,    77
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,    12,    13,    14,    20,    33,    34,
      35,    41,    42,    47,    49,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    78,    83,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   103,   104,   105,   106,    87,    87,    96,
      96,    96,    25,    26,    89,     7,    87,    28,    29,    36,
      39,    40,     5,    35,    87,    48,    89,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    96,    99,     0,
      85,     4,    45,    73,    74,    11,    20,    25,    70,    27,
      28,    29,    37,    38,    43,    44,    75,    76,    77,    95,
      18,    19,    30,    31,    32,    15,    16,    17,    21,    22,
      23,    24,    72,    79,    80,    81,    82,    50,   102,     8,
      87,    87,     6,     8,    89,    89,    26,    87,    35,    35,
      94,    35,    35,    87,    26,    26,    70,    48,    26,     8,
       8,     8,     8,     8,     8,     8,     8,     8,     8,    26,
       8,    26,    26,    26,    26,     8,    26,    26,    88,    88,
      88,    89,    25,    26,    89,    89,    26,    46,    71,    89,
      91,    91,    91,    94,    94,    94,    94,    94,    94,    94,
      96,    96,    96,    96,    96,    99,    26,     8,    26,     8,
      26,    89,     8,    26,    35,    87,    35,    89,    70,    87,
      87,    87,    87,    87,    87,    87,    89,    89,    26,    89,
      26,    71,    89,    89,    26,    46,    71,    50,     8,     8,
       8,    26,    71,    89,    26,     8,     8,     8,     8,     8,
       8,    89,    89,    89,    26,    71,    89,    26,    71,    89,
      89,     6,    89,    89,    26,    71,    87,    89,    89,    89,
      89,    26,    71,    89,    89,     8,    89,    89
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, scanner, YY_("syntax error: cannot back up")); \
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
		  Type, Value, Location, scanner); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void     *scanner)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void     *scanner;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void     *scanner)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    void     *scanner;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, void     *scanner)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, scanner)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    void     *scanner;
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , scanner);
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, scanner); \
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void     *scanner)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, scanner)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    void     *scanner;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
int yyparse (void     *scanner);
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
yyparse (void     *scanner)
#else
int
yyparse (scanner)
    void     *scanner;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;

  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
  yylloc.first_column = yylloc.last_column = 0;
#endif


  /* User initialization code.  */
#line 199 "regex.y"
{
    clear_quantifiers();
    rewrite = 0;
    contexts = NULL;
    rules = NULL;
    rewrite_rules = NULL;
    rule_direction = 0;
    substituting = 0;
}
/* Line 1078 of yacc.c.  */
#line 1958 "regex.tab.c"
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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 244 "regex.y"
    { current_parse = (yyvsp[(1) - (2)].net);              ;}
    break;

  case 5:
#line 246 "regex.y"
    { ;}
    break;

  case 6:
#line 247 "regex.y"
    { (yyval.net) = fsm_compose((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));         ;}
    break;

  case 7:
#line 248 "regex.y"
    { (yyval.net) = fsm_lenient_compose((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net)); ;}
    break;

  case 8:
#line 249 "regex.y"
    { (yyval.net) = fsm_cross_product((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));   ;}
    break;

  case 9:
#line 251 "regex.y"
    { if (rewrite) { add_rewrite_rule(); (yyval.net) = fsm_rewrite(rewrite_rules); clear_rewrite_ruleset(rewrite_rules); } rewrite = 0; contexts = NULL; rules = NULL; rewrite_rules = NULL; ;}
    break;

  case 10:
#line 253 "regex.y"
    { ;}
    break;

  case 11:
#line 254 "regex.y"
    { (yyval.net) = NULL; add_context_pair((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));;}
    break;

  case 12:
#line 255 "regex.y"
    { add_context_pair((yyvsp[(1) - (2)].net),fsm_empty_string()); ;}
    break;

  case 13:
#line 256 "regex.y"
    { add_context_pair((yyvsp[(1) - (4)].net),fsm_empty_string()); ;}
    break;

  case 14:
#line 257 "regex.y"
    { add_context_pair(fsm_empty_string(),fsm_empty_string());;}
    break;

  case 15:
#line 258 "regex.y"
    { add_rewrite_rule(); add_context_pair(fsm_empty_string(),fsm_empty_string());;}
    break;

  case 16:
#line 259 "regex.y"
    { add_rewrite_rule(); add_context_pair((yyvsp[(1) - (4)].net),fsm_empty_string());;}
    break;

  case 17:
#line 260 "regex.y"
    { add_context_pair(fsm_empty_string(),fsm_empty_string());;}
    break;

  case 18:
#line 261 "regex.y"
    { add_context_pair(fsm_empty_string(),(yyvsp[(2) - (2)].net)); ;}
    break;

  case 19:
#line 262 "regex.y"
    { add_context_pair(fsm_empty_string(),(yyvsp[(2) - (4)].net)); ;}
    break;

  case 20:
#line 263 "regex.y"
    { add_context_pair((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net)); ;}
    break;

  case 21:
#line 264 "regex.y"
    { (yyval.net) = fsm_context_restrict((yyvsp[(1) - (3)].net),contexts); fsm_clear_contexts(contexts);;}
    break;

  case 22:
#line 265 "regex.y"
    { add_rule((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net),NULL,(yyvsp[(2) - (3)].type)); if ((yyvsp[(1) - (3)].net)->arity == 2) { printf("Error: LHS is transducer\n"); YYERROR;};}
    break;

  case 23:
#line 266 "regex.y"
    { add_rule((yyvsp[(1) - (2)].net),NULL,NULL,(yyvsp[(2) - (2)].type)); ;}
    break;

  case 24:
#line 268 "regex.y"
    { add_rule((yyvsp[(2) - (5)].net),(yyvsp[(5) - (5)].net),NULL,(yyvsp[(4) - (5)].type)|ARROW_DOTTED); if ((yyvsp[(5) - (5)].net) == NULL) { YYERROR;};}
    break;

  case 25:
#line 269 "regex.y"
    { add_rule(fsm_empty_string(),(yyvsp[(4) - (4)].net),NULL,(yyvsp[(3) - (4)].type)|ARROW_DOTTED); if ((yyvsp[(4) - (4)].net) == NULL) { YYERROR;};}
    break;

  case 26:
#line 270 "regex.y"
    { add_rule((yyvsp[(2) - (7)].net),(yyvsp[(5) - (7)].net),NULL,(yyvsp[(4) - (7)].type)|ARROW_DOTTED);;}
    break;

  case 27:
#line 271 "regex.y"
    { add_rule(fsm_empty_string(),(yyvsp[(4) - (6)].net),NULL,(yyvsp[(3) - (6)].type)|ARROW_DOTTED);;}
    break;

  case 28:
#line 272 "regex.y"
    { add_rule((yyvsp[(2) - (7)].net),(yyvsp[(5) - (7)].net),NULL,(yyvsp[(4) - (7)].type)|ARROW_DOTTED); rule_direction = (yyvsp[(6) - (7)].type);;}
    break;

  case 29:
#line 273 "regex.y"
    { add_rule(fsm_empty_string(),(yyvsp[(4) - (6)].net),NULL,(yyvsp[(3) - (6)].type)|ARROW_DOTTED); rule_direction = (yyvsp[(5) - (6)].type);;}
    break;

  case 30:
#line 274 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net),NULL,(yyvsp[(2) - (5)].type));;}
    break;

  case 31:
#line 275 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),NULL,NULL,(yyvsp[(2) - (4)].type));;}
    break;

  case 32:
#line 276 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net),NULL,(yyvsp[(2) - (5)].type)); rule_direction = (yyvsp[(4) - (5)].type);;}
    break;

  case 33:
#line 277 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),NULL,NULL,(yyvsp[(2) - (4)].type)); rule_direction = (yyvsp[(3) - (4)].type);;}
    break;

  case 34:
#line 279 "regex.y"
    { add_rewrite_rule();;}
    break;

  case 35:
#line 281 "regex.y"
    { add_rule((yyvsp[(1) - (3)].net),fsm_empty_string(),fsm_empty_string(),(yyvsp[(2) - (3)].type));;}
    break;

  case 36:
#line 282 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),fsm_empty_string(),(yyvsp[(4) - (4)].net),(yyvsp[(2) - (4)].type));;}
    break;

  case 37:
#line 283 "regex.y"
    { add_rule((yyvsp[(1) - (4)].net),(yyvsp[(3) - (4)].net),fsm_empty_string(),(yyvsp[(2) - (4)].type));;}
    break;

  case 38:
#line 284 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),(yyvsp[(3) - (5)].net),(yyvsp[(5) - (5)].net),(yyvsp[(2) - (5)].type));;}
    break;

  case 39:
#line 285 "regex.y"
    { add_rule((yyvsp[(1) - (7)].net),(yyvsp[(3) - (7)].net),(yyvsp[(5) - (7)].net),(yyvsp[(2) - (7)].type));;}
    break;

  case 40:
#line 286 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),(yyvsp[(3) - (6)].net),fsm_empty_string(),(yyvsp[(2) - (6)].type));;}
    break;

  case 41:
#line 287 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),fsm_empty_string(),(yyvsp[(4) - (6)].net),(yyvsp[(2) - (6)].type));;}
    break;

  case 42:
#line 288 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),fsm_empty_string(),fsm_empty_string(),(yyvsp[(2) - (5)].type));;}
    break;

  case 43:
#line 289 "regex.y"
    { add_rule((yyvsp[(1) - (7)].net),(yyvsp[(3) - (7)].net),(yyvsp[(5) - (7)].net),(yyvsp[(2) - (7)].type)); rule_direction = (yyvsp[(6) - (7)].type);;}
    break;

  case 44:
#line 290 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),fsm_empty_string(),(yyvsp[(4) - (6)].net),(yyvsp[(2) - (6)].type)); rule_direction = (yyvsp[(5) - (6)].type);;}
    break;

  case 45:
#line 291 "regex.y"
    { add_rule((yyvsp[(1) - (6)].net),(yyvsp[(3) - (6)].net),fsm_empty_string(),(yyvsp[(2) - (6)].type)); rule_direction = (yyvsp[(5) - (6)].type);;}
    break;

  case 46:
#line 292 "regex.y"
    { add_rule((yyvsp[(1) - (5)].net),fsm_empty_string(),fsm_empty_string(),(yyvsp[(2) - (5)].type)); rule_direction = (yyvsp[(4) - (5)].type);;}
    break;

  case 47:
#line 295 "regex.y"
    { ;}
    break;

  case 48:
#line 296 "regex.y"
    { (yyval.net) = fsm_shuffle((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));  ;}
    break;

  case 49:
#line 297 "regex.y"
    { (yyval.net) = fsm_precedes((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net)); ;}
    break;

  case 50:
#line 298 "regex.y"
    { (yyval.net) = fsm_follows((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));  ;}
    break;

  case 51:
#line 300 "regex.y"
    { ;}
    break;

  case 52:
#line 302 "regex.y"
    { ;}
    break;

  case 53:
#line 304 "regex.y"
    { ;}
    break;

  case 54:
#line 305 "regex.y"
    { (yyval.net) = fsm_union((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                     ;}
    break;

  case 55:
#line 306 "regex.y"
    { (yyval.net) = fsm_priority_union_upper((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));      ;}
    break;

  case 56:
#line 307 "regex.y"
    { (yyval.net) = fsm_priority_union_lower((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));      ;}
    break;

  case 57:
#line 308 "regex.y"
    { (yyval.net) = fsm_intersect((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                 ;}
    break;

  case 58:
#line 309 "regex.y"
    { (yyval.net) = fsm_minus((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                     ;}
    break;

  case 59:
#line 310 "regex.y"
    { (yyval.net) = fsm_union(fsm_complement((yyvsp[(1) - (3)].net)),(yyvsp[(3) - (3)].net));     ;}
    break;

  case 60:
#line 311 "regex.y"
    { (yyval.net) = fsm_intersect(fsm_union(fsm_complement(fsm_copy((yyvsp[(1) - (3)].net))),fsm_copy((yyvsp[(3) - (3)].net))), fsm_union(fsm_complement(fsm_copy((yyvsp[(3) - (3)].net))),fsm_copy((yyvsp[(1) - (3)].net)))); fsm_destroy((yyvsp[(1) - (3)].net)); fsm_destroy((yyvsp[(3) - (3)].net));;}
    break;

  case 61:
#line 313 "regex.y"
    { ;}
    break;

  case 62:
#line 314 "regex.y"
    { (yyval.net) = fsm_concat((yyvsp[(1) - (2)].net),(yyvsp[(2) - (2)].net)); ;}
    break;

  case 63:
#line 315 "regex.y"
    { (yyval.net) = fsm_ignore(fsm_contains(fsm_concat(fsm_symbol((yyvsp[(1) - (3)].string)),fsm_concat((yyvsp[(3) - (3)].net),fsm_symbol((yyvsp[(1) - (3)].string))))),union_quantifiers(),OP_IGNORE_ALL); ;}
    break;

  case 64:
#line 317 "regex.y"
    { (yyval.net) = fsm_logical_eq((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string)); ;}
    break;

  case 65:
#line 318 "regex.y"
    { (yyval.net) = fsm_complement(fsm_logical_eq((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string))); ;}
    break;

  case 66:
#line 319 "regex.y"
    { (yyval.net) = fsm_logical_precedence((yyvsp[(1) - (3)].string),(yyvsp[(3) - (3)].string)); ;}
    break;

  case 67:
#line 320 "regex.y"
    { (yyval.net) = fsm_logical_precedence((yyvsp[(3) - (3)].string),(yyvsp[(1) - (3)].string)); ;}
    break;

  case 68:
#line 322 "regex.y"
    { ;}
    break;

  case 69:
#line 323 "regex.y"
    { (yyval.net) = fsm_ignore((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net), OP_IGNORE_ALL);          ;}
    break;

  case 70:
#line 324 "regex.y"
    { (yyval.net) = fsm_ignore((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net), OP_IGNORE_INTERNAL);     ;}
    break;

  case 71:
#line 325 "regex.y"
    { (yyval.net) = fsm_quotient_right((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                 ;}
    break;

  case 72:
#line 326 "regex.y"
    { (yyval.net) = fsm_quotient_left((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));                  ;}
    break;

  case 73:
#line 327 "regex.y"
    { (yyval.net) = fsm_quotient_interleave((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net));            ;}
    break;

  case 74:
#line 329 "regex.y"
    { ;}
    break;

  case 75:
#line 330 "regex.y"
    { (yyval.net) = fsm_complement((yyvsp[(2) - (2)].net));       ;}
    break;

  case 76:
#line 331 "regex.y"
    { (yyval.net) = fsm_contains((yyvsp[(2) - (2)].net));         ;}
    break;

  case 77:
#line 332 "regex.y"
    { (yyval.net) = fsm_contains_one((yyvsp[(2) - (2)].net));     ;}
    break;

  case 78:
#line 333 "regex.y"
    { (yyval.net) = fsm_contains_opt_one((yyvsp[(2) - (2)].net)); ;}
    break;

  case 79:
#line 335 "regex.y"
    { ;}
    break;

  case 80:
#line 337 "regex.y"
    { ;}
    break;

  case 81:
#line 338 "regex.y"
    { (yyval.net) = fsm_kleene_star(fsm_minimize((yyvsp[(1) - (2)].net))); ;}
    break;

  case 82:
#line 339 "regex.y"
    { (yyval.net) = fsm_kleene_plus((yyvsp[(1) - (2)].net)); ;}
    break;

  case 83:
#line 340 "regex.y"
    { (yyval.net) = fsm_determinize(fsm_reverse((yyvsp[(1) - (2)].net))); ;}
    break;

  case 84:
#line 341 "regex.y"
    { (yyval.net) = fsm_invert((yyvsp[(1) - (2)].net)); ;}
    break;

  case 85:
#line 342 "regex.y"
    { (yyval.net) = fsm_upper((yyvsp[(1) - (2)].net)); ;}
    break;

  case 86:
#line 343 "regex.y"
    { (yyval.net) = fsm_lower((yyvsp[(1) - (2)].net)); ;}
    break;

  case 87:
#line 344 "regex.y"
    { (yyval.net) = flag_eliminate((yyvsp[(1) - (2)].net), NULL); ;}
    break;

  case 88:
#line 345 "regex.y"
    { (yyval.net) = fsm_cross_product((yyvsp[(1) - (3)].net),(yyvsp[(3) - (3)].net)); ;}
    break;

  case 89:
#line 347 "regex.y"
    { (yyval.net) = fsm_concat_n((yyvsp[(1) - (2)].net),atoi((yyvsp[(2) - (2)].string))); ;}
    break;

  case 90:
#line 348 "regex.y"
    { (yyval.net) = fsm_concat(fsm_concat_n(fsm_copy((yyvsp[(1) - (2)].net)), atoi((yyvsp[(2) - (2)].string))),fsm_kleene_plus(fsm_copy((yyvsp[(1) - (2)].net)))); fsm_destroy((yyvsp[(1) - (2)].net)); ;}
    break;

  case 91:
#line 349 "regex.y"
    { (yyval.net) = fsm_concat_m_n((yyvsp[(1) - (2)].net),0,atoi((yyvsp[(2) - (2)].string))-1); ;}
    break;

  case 92:
#line 350 "regex.y"
    { (yyval.net) = fsm_concat_m_n((yyvsp[(1) - (2)].net),atoi((yyvsp[(2) - (2)].string)),atoi(strstr((yyvsp[(2) - (2)].string),",")+1)); ;}
    break;

  case 93:
#line 352 "regex.y"
    { ;}
    break;

  case 94:
#line 353 "regex.y"
    { (yyval.net) = fsm_term_negation((yyvsp[(2) - (2)].net)); ;}
    break;

  case 95:
#line 355 "regex.y"
    { (yyval.net) = (yyvsp[(1) - (1)].net);;}
    break;

  case 96:
#line 356 "regex.y"
    { (yyval.net) = (yyvsp[(1) - (1)].net); ;}
    break;

  case 97:
#line 357 "regex.y"
    { (yyval.net) = fsm_complement(fsm_substitute_symbol(fsm_intersect(fsm_quantifier((yyvsp[(1) - (4)].string)),fsm_complement((yyvsp[(3) - (4)].net))),(yyvsp[(1) - (4)].string),"@_EPSILON_SYMBOL_@")); purge_quantifier((yyvsp[(1) - (4)].string)); ;}
    break;

  case 98:
#line 358 "regex.y"
    {  (yyval.net) = fsm_substitute_symbol(fsm_intersect(fsm_quantifier((yyvsp[(1) - (2)].string)),(yyvsp[(2) - (2)].net)),(yyvsp[(1) - (2)].string),"@_EPSILON_SYMBOL_@"); purge_quantifier((yyvsp[(1) - (2)].string)); ;}
    break;

  case 99:
#line 359 "regex.y"
    { if (count_quantifiers()) (yyval.net) = (yyvsp[(2) - (3)].net); else {(yyval.net) = fsm_optionality((yyvsp[(2) - (3)].net));} ;}
    break;

  case 100:
#line 360 "regex.y"
    { (yyval.net) = (yyvsp[(2) - (3)].net); ;}
    break;

  case 101:
#line 361 "regex.y"
    {(yyval.net) = fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(union_quantifiers(),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_universal())))))))); ;}
    break;

  case 102:
#line 362 "regex.y"
    {(yyval.net) = fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(2) - (5)].string)),fsm_concat(fsm_ignore((yyvsp[(4) - (5)].net),union_quantifiers(),OP_IGNORE_ALL),fsm_universal()))))); ;}
    break;

  case 103:
#line 363 "regex.y"
    {(yyval.net) = fsm_concat(fsm_universal(),fsm_concat(fsm_ignore((yyvsp[(2) - (5)].net),union_quantifiers(),OP_IGNORE_ALL),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_concat(fsm_universal(),fsm_concat(fsm_symbol((yyvsp[(4) - (5)].string)),fsm_universal()))))); ;}
    break;

  case 104:
#line 364 "regex.y"
    {(yyval.net) = fsm_substitute_symbol((yyvsp[(1) - (2)].net),subval1,subval2); substituting = 0; xxfree(subval1); xxfree(subval2); subval1 = subval2 = NULL;;}
    break;

  case 105:
#line 366 "regex.y"
    { (yyval.net) = (yyvsp[(3) - (4)].net); substituting = 1;                      ;}
    break;

  case 106:
#line 367 "regex.y"
    { subval1 = (yyvsp[(2) - (4)].string); subval2 = (yyvsp[(4) - (4)].string); ;}
    break;

  case 107:
#line 369 "regex.y"
    { (yyval.net) = (yyvsp[(1) - (1)].net); ;}
    break;

  case 108:
#line 370 "regex.y"
    { (yyval.net) = fsm_boolean(fsm_isidentity((yyvsp[(2) - (3)].net)));   ;}
    break;

  case 109:
#line 371 "regex.y"
    { (yyval.net) = fsm_boolean(fsm_isfunctional((yyvsp[(2) - (3)].net))); ;}
    break;

  case 110:
#line 372 "regex.y"
    { (yyval.net) = fsm_boolean(fsm_isunambiguous((yyvsp[(2) - (3)].net))); ;}
    break;

  case 111:
#line 373 "regex.y"
    { (yyval.net) = fsm_extract_nonidentity(fsm_copy((yyvsp[(2) - (3)].net))); ;}
    break;

  case 112:
#line 374 "regex.y"
    { (yyval.net) = fsm_lowerdet(fsm_copy((yyvsp[(2) - (3)].net))); ;}
    break;

  case 113:
#line 375 "regex.y"
    { (yyval.net) = fsm_lowerdeteps(fsm_copy((yyvsp[(2) - (3)].net))); ;}
    break;

  case 114:
#line 376 "regex.y"
    { (yyval.net) = fsm_markallfinal(fsm_copy((yyvsp[(2) - (3)].net))); ;}
    break;

  case 115:
#line 377 "regex.y"
    { (yyval.net) = fsm_extract_unambiguous(fsm_copy((yyvsp[(2) - (3)].net)));      ;}
    break;

  case 116:
#line 378 "regex.y"
    { (yyval.net) = fsm_extract_ambiguous(fsm_copy((yyvsp[(2) - (3)].net)));        ;}
    break;

  case 117:
#line 379 "regex.y"
    { (yyval.net) = fsm_extract_ambiguous_domain(fsm_copy((yyvsp[(2) - (3)].net))); ;}
    break;

  case 118:
#line 380 "regex.y"
    { (yyval.net) = fsm_letter_machine(fsm_copy((yyvsp[(2) - (3)].net))); ;}
    break;

  case 119:
#line 381 "regex.y"
    { (yyval.net) = fsm_mark_fsm_tail((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net)); ;}
    break;

  case 120:
#line 382 "regex.y"
    { (yyval.net) = fsm_add_loop((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net),1); ;}
    break;

  case 121:
#line 383 "regex.y"
    { (yyval.net) = fsm_add_loop((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net),0); ;}
    break;

  case 122:
#line 384 "regex.y"
    { (yyval.net) = fsm_add_loop((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net),2); ;}
    break;

  case 123:
#line 385 "regex.y"
    { (yyval.net) = fsm_add_sink((yyvsp[(2) - (3)].net),1); ;}
    break;

  case 124:
#line 386 "regex.y"
    { (yyval.net) = fsm_left_rewr((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net)); ;}
    break;

  case 125:
#line 387 "regex.y"
    { (yyval.net) = fsm_flatten((yyvsp[(2) - (5)].net),(yyvsp[(4) - (5)].net)); ;}
    break;

  case 126:
#line 388 "regex.y"
    { (yyval.net) = fsm_equal_substrings((yyvsp[(2) - (7)].net),(yyvsp[(4) - (7)].net),(yyvsp[(6) - (7)].net)); ;}
    break;

  case 127:
#line 391 "regex.y"
    { frec++; fargptr[frec] = 0 ;declare_function_name((yyvsp[(1) - (3)].string)) ; add_function_argument((yyvsp[(2) - (3)].net)); ;}
    break;

  case 128:
#line 393 "regex.y"
    { frec++; fargptr[frec] = 0 ;declare_function_name((yyvsp[(1) - (2)].string)) ; add_function_argument((yyvsp[(2) - (2)].net)); ;}
    break;

  case 129:
#line 395 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); ;}
    break;

  case 130:
#line 396 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); ;}
    break;

  case 131:
#line 399 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); if (((yyval.net) = function_apply()) == NULL) YYERROR; ;}
    break;

  case 132:
#line 401 "regex.y"
    { add_function_argument((yyvsp[(2) - (3)].net)); if (((yyval.net) = function_apply()) == NULL) YYERROR; ;}
    break;

  case 133:
#line 403 "regex.y"
    { if (((yyval.net) = function_apply()) == NULL) YYERROR;;}
    break;


/* Line 1267 of yacc.c.  */
#line 2793 "regex.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, scanner, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (&yylloc, scanner, yymsg);
	  }
	else
	  {
	    yyerror (&yylloc, scanner, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, &yylloc, scanner);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
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

  yyerror_range[0] = yylsp[1-yylen];
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
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc, scanner);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, scanner);
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


#line 405 "regex.y"


