%{
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


%}

/* Slight Hfst addition SFST::... */
%union {
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
}

%token <number> NEWLINE ALPHA COMPOSE PRINT POS INSERT SUBSTITUTE SWITCH
%token <type>   ARROW
%token <rtype>  REPLACE
%token <name>   SYMBOL VAR SVAR RVAR RSVAR
%token <value>  STRING STRING2 UTF8CHAR
%token <uchar>  CHARACTER

%type  <uchar>      SCHAR
%type  <longchar>   LCHAR
%type  <character>  CODE
%type  <expression> RE
%type  <range>      RANGE VALUE VALUES
%type  <ranges>     RANGES
%type  <contexts>   CONTEXT CONTEXT2 CONTEXTS CONTEXTS2

%left PRINT INSERT SUBSTITUTE
%left ARROW REPLACE
%left COMPOSE
%left '|'
%left '-'
%left '&'
%left SEQ
%left '!' '^' '_'
%left '*' '+'
%%

ALL:        ASSIGNMENTS RE NEWLINES { Result=compiler->result($2, Switch); }
          ;

ASSIGNMENTS: ASSIGNMENTS ASSIGNMENT {}
          | ASSIGNMENTS NEWLINE     {}
          | /* nothing */           {}
          ;

ASSIGNMENT: VAR '=' RE              { if (DEBUG) { printf("defining transducer variable \"%s\"..\n", $1); }; if (compiler->def_var($1,$3)) warn2("assignment of empty transducer to",$1); if(DEBUG) printf("done\n"); }
          | RVAR '=' RE             { if (DEBUG) { printf("defining agreement transducer variable \"%s\"..\n", $1); }; if (compiler->def_rvar($1,$3)) warn2("assignment of empty transducer to",$1); }
          | SVAR '=' VALUES         { if (DEBUG) { printf("defining range variable \"%s\"..\n", $1); }; if (compiler->def_svar($1,$3)) warn2("assignment of empty symbol range to",$1); }
          | RSVAR '=' VALUES        { if (DEBUG) { printf("defining agreement range variable \"%s\"..\n", $1); }; if (compiler->def_svar($1,$3)) warn2("assignment of empty symbol range to",$1); }
          | RE PRINT STRING         { compiler->write_to_file($1, folder, $3); }
          | ALPHA RE                { if (DEBUG) { printf("defining alphabet..\n"); }; compiler->def_alphabet($2); delete $2; }
          ;

RE:         RE ARROW CONTEXTS2      { $$ = compiler->restriction($1,$2,$3,0); }
	  | RE '^' ARROW CONTEXTS2  { $$ = compiler->restriction($1,$3,$4,1); }
	  | RE '_' ARROW CONTEXTS2  { $$ = compiler->restriction($1,$3,$4,-1); }
          | RE REPLACE CONTEXT2     { $1 = compiler->explode($1); $1->minimize(); $$ = compiler->replace_in_context($1, $2, $3, false); }
          | RE REPLACE '?' CONTEXT2 { $1 = compiler->explode($1); $1->minimize(); $$ = compiler->replace_in_context($1, $2, $4, true); }
          | RE REPLACE '(' ')'      { $1 = compiler->explode($1); $1->minimize(); $$ = compiler->replace($1, $2, false); }
          | RE REPLACE '?' '(' ')'  { $1 = compiler->explode($1); $1->minimize(); $$ = compiler->replace($1, $2, true); }
          | RE RANGE ARROW RANGE RE { $$ = compiler->make_rule($1,$2,$3,$4,$5, output_format); }
          | RE RANGE ARROW RANGE    { $$ = compiler->make_rule($1,$2,$3,$4,NULL, output_format); }
          | RANGE ARROW RANGE RE    { $$ = compiler->make_rule(NULL,$1,$2,$3,$4, output_format); }
          | RANGE ARROW RANGE       { $$ = compiler->make_rule(NULL,$1,$2,$3,NULL, output_format); }
          | RE COMPOSE RE    { $1->compose(*$3); delete $3; $$ = $1; }
          | '{' RANGES '}' ':' '{' RANGES '}' { $$ = compiler->make_mapping($2,$6,output_format); }
          | RANGE ':' '{' RANGES '}' { $$ = compiler->make_mapping(compiler->add_range($1,NULL),$4,output_format); }
          | '{' RANGES '}' ':' RANGE { $$ = compiler->make_mapping($2,compiler->add_range($5,NULL),output_format); }
          | RE INSERT CODE ':' CODE  { $$ = compiler->insert_freely($1,$3,$5); }
          | RE INSERT CODE           { $$ = compiler->insert_freely($1,$3,$3); }
	  | RE SUBSTITUTE CODE ':' CODE  { $$ = compiler->substitute($1,$3,$5); }
	  | RE SUBSTITUTE CODE ':' CODE ':' CODE ':' CODE { $$ = compiler->substitute($1,$3,$5,$7,$9); }
	  | RE SUBSTITUTE CODE ':' CODE '(' RE ')' { $$ = compiler->substitute($1,$3,$5,$7); }
          | RANGE ':' RANGE  { $$ = compiler->new_transducer($1,$3,output_format); } 
          | RANGE            { $$ = compiler->new_transducer($1,$1,output_format); }
          | VAR              { if (DEBUG) { printf("calling transducer variable \"%s\"\n", $1); }; $$ = compiler->var_value($1); }
          | RVAR             { if (DEBUG) { printf("calling agreement transducer variable \"%s\"\n", $1); }; $$ = compiler->rvar_value($1,output_format); }
          | RE '*'           { $1->repeat_star(); $$ = $1; }
          | RE '+'           { $1->repeat_plus(); $$ = $1; }
          | RE '?'           { $1->optionalize(); $$ = $1; }
          | RE RE %prec SEQ  { $1->concatenate(*$2); delete $2; $$ = $1; }
          | '!' RE           { $$ = compiler->negation($2); }
          | SWITCH RE        { $2->invert(); $$ = $2; }
          | '^' RE           { $2->output_project(); $$ = $2; }
          | '_' RE           { $2->input_project(); $$ = $2; }
          | RE '&' RE        { $1->intersect(*$3); delete $3; $$ = $1; }
          | RE '-' RE        { $1->subtract(*$3); delete $3; $$ = $1; }
          | RE '|' RE        { $1->disjunct(*$3); delete $3; $$ = $1; }
          | '(' RE ')'       { $$ = $2; }
          | STRING           { $$ = compiler->read_words(folder, $1, output_format); }
          | STRING2          { try { $$ = compiler->read_transducer(folder, $1, output_format); } catch (HfstException e) { printf("\nAn error happened when reading file \"%s\"\n", $1); exit(1); } }
          ;

RANGES:     RANGE RANGES     { $$ = compiler->add_range($1,$2); }
          |                  { $$ = NULL; }
          ;

RANGE:      '[' VALUES ']'   { $$=$2; }
          | '[' '^' VALUES ']' { $$=compiler->complement_range($3); }
          | '[' RSVAR ']'    { if (DEBUG) { printf("calling agreement range variable \"%s\"\n", $2); }; $$=compiler->rsvar_value($2); }
          | '.'              { $$=NULL; }
          | CODE             { $$=compiler->add_value($1,NULL); }
          ;

CONTEXTS2:  CONTEXTS               { $$ = $1; }
          | '(' CONTEXTS ')'       { $$ = $2; }
          ;

CONTEXTS:   CONTEXT ',' CONTEXTS   { $$ = compiler->add_context($1,$3); }
          | CONTEXT                { $$ = $1; }
          ;

CONTEXT2:   CONTEXT                { $$ = $1; }
          | '(' CONTEXT ')'        { $$ = $2; }
          ;

CONTEXT :   RE POS RE              { $$ = compiler->make_context($1, $3); }
          |    POS RE              { $$ = compiler->make_context(NULL, $2); }
          | RE POS                 { $$ = compiler->make_context($1, NULL); }
          ;

VALUES:     VALUE VALUES           { $$=compiler->append_values($1,$2); }
          | VALUE                  { $$ = $1; }
          ;

VALUE:      LCHAR '-' LCHAR	   { $$=compiler->add_values($1,$3,NULL); }
          | SVAR                   { if (DEBUG) { printf("calling range variable \"%s\"", $1); }; $$=compiler->svar_value($1); }
          | LCHAR  	           { $$=compiler->add_value(compiler->character_code($1),NULL); }
          | CODE		   { $$=compiler->add_value($1,NULL); }
	  | SCHAR		   { $$=compiler->add_value($1,NULL); }
          ;

LCHAR:      CHARACTER	{ $$=$1; }
          | UTF8CHAR	{ $$=compiler->utf8toint($1); free($1); }
	  | SCHAR       { $$=$1; }
          ;

CODE:       CHARACTER	{ $$=compiler->character_code($1); }
          | UTF8CHAR	{ $$=compiler->symbol_code($1); }
          | SYMBOL	{ $$=compiler->symbol_code($1); }
          ;

SCHAR:      '.'		{ $$=(unsigned char)compiler->character_code('.'); }
          | '!'		{ $$=(unsigned char)compiler->character_code('!'); }
          | '?'		{ $$=(unsigned char)compiler->character_code('?'); }
          | '{'		{ $$=(unsigned char)compiler->character_code('{'); }
          | '}'		{ $$=(unsigned char)compiler->character_code('}'); }
          | ')'		{ $$=(unsigned char)compiler->character_code(')'); }
          | '('		{ $$=(unsigned char)compiler->character_code('('); }
          | '&'		{ $$=(unsigned char)compiler->character_code('&'); }
          | '|'		{ $$=(unsigned char)compiler->character_code('|'); }
          | '*'		{ $$=(unsigned char)compiler->character_code('*'); }
          | '+'		{ $$=(unsigned char)compiler->character_code('+'); }
          | ':'		{ $$=(unsigned char)compiler->character_code(':'); }
          | ','		{ $$=(unsigned char)compiler->character_code(','); }
          | '='		{ $$=(unsigned char)compiler->character_code('='); }
          | '_'		{ $$=(unsigned char)compiler->character_code('_'); }
          | '^'		{ $$=(unsigned char)compiler->character_code('^'); }
          | '-'		{ $$=(unsigned char)compiler->character_code('-'); }
          ;

NEWLINES:   NEWLINE NEWLINES     {}
          | /* nothing */        {}
          ;

%%

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
