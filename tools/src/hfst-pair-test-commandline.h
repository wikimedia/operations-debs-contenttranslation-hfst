#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <getopt.h>

using std::vector;
using std::ifstream;

static char * program_name = NULL;
static bool debug = false;
static bool verbose = false;
static bool silent = false;
static bool display_help = false;
static bool display_version = false;
static char * fst_file_name = NULL;
static char * output_file_name = NULL;
static char * pair_file_name = NULL;
static bool spaces = false;
static char * alphabet_file_name = NULL;
static char * rule_names_file_name = NULL;
static FILE* message_out = stdout;

typedef vector<char*> RuleNameVector;
static RuleNameVector * rule_transducer_names = NULL;

/* For debug: print the values of all variables storing
   commandline arguments after getopt has been used. */
void display_all_arguments(void)
{
  fprintf(stderr,"\nArguments parsed\n");
  fprintf(stderr,"program name: %s\n",program_name);
  fprintf(stderr,"Debug: ");
  if (debug)
    {
      fprintf(stderr,"true\n");
    }
  else
    {
      fprintf(stderr,"false\n");
    }
  fprintf(stderr,"Verbose: ");
  if (verbose)
    {
      fprintf(stderr,"true\n");
    }
  else
    {
      fprintf(stderr,"false\n");
    }
  fprintf(stderr,"Display help: ");
  if (display_help)
    {
      fprintf(stderr,"true\n");
    }
  else
    {
      fprintf(stderr,"false\n");
    }
  fprintf(stderr,"Display version: ");
  if (display_version)
    {
      fprintf(stderr,"true\n");
    }
  else
    {
      fprintf(stderr,"false\n");
    }
  fprintf(stderr,"Rule file name: %s\n",fst_file_name);
  fprintf(stderr,"Output file name: %s\n",output_file_name);
  fprintf(stderr,"Pair file name: %s\n",pair_file_name);
  fprintf(stderr,"Spaces: ");
  if (spaces)
    {
      fprintf(stderr,"true\n");
    }
  else
    {
      fprintf(stderr,"false\n");
    }
  fprintf(stderr,"Silent: ");
  if (silent)
    {
      fprintf(stderr,"true\n");
    }
  else
    {
      fprintf(stderr,"false\n");
    }
  fprintf(stderr,"Alphabet file name: %s\n",alphabet_file_name);
  fprintf(stderr,"Rule names file name: %s\n",rule_names_file_name);
  fprintf(stderr,"\n");
}
/* Read the rule name file, whose name is char * rule_names_file_name  */
void read_rule_names(size_t number_of_rules)
{
  if (debug)
    {
      assert(rule_names_file_name != NULL);
    }

  rule_transducer_names = new RuleNameVector;
  ifstream rule_name_in(rule_names_file_name,std::ios::in);
  size_t counter = 0;
  char rule_name[1000];
  while (rule_name_in.getline(rule_name,1000) and (counter < number_of_rules)) 
    { 
      ++counter;
      rule_transducer_names->push_back(strdup(rule_name));
    }
  if ( counter < number_of_rules ) {
    fprintf(message_out,"WARNING! The rule name file %s contains less rule names"
        "than there are rules. Using rule numbers instead.\n",
        rule_names_file_name);
    delete rule_transducer_names;
    rule_transducer_names = NULL;
  }
}

/* Return a string, with length given by size_t length,
   whose every character is char c.*/
char * init(char c, size_t length)
{
  char * str = (char*)malloc(sizeof(char)*(length+1));
  for( size_t i = 0; i < length; ++i )
    str[i] = c;
  str[length] = 0;
  return str;
}

/* Return a string of spaces equal in length to the program name. */
char * get_skip(void)
{
  size_t program_name_length = strlen(program_name);
  return init(' ',program_name_length);
}

/* Display program name and possible parameters with their argument types. */
void usage(void) 
{
  fprintf(message_out,"USAGE: %s [ OPTIONS ] [ FSTFILE ]\n",
      program_name);
}

/* Display the version and legal stuff concerning this program. */
void version(void)
{
  fprintf(message_out,
      "HFST-Pair-Test 0.1 (" PACKAGE_STRING ")\n"
      "copyright (C) 2009 University of Helsinki\n"
      "written by Miikka Silfverberg mar 2008\n"
      "License GPLv3: GNU GPL version 3\n"
      "\t<http://gnu.org/licences/gpl.html>\n"
      "This is free software: you are free to change and redistribute it\n"
      "There is NO WARRANTY, to the extent permitted by law.\n\n");
}

void help(void)
{

  usage();
  fprintf(message_out,
      "HFST-Pair-Test a utility for testing "
      "HFST-TwolC grammars using pair-strings.\n\n"
      );
  
  
  fprintf(message_out,
      "  -v, --verbose          Verbose mode, display all kind of information.\n"
      "  -q, --quiet            Output nothing except warnings and errors.\n"
      "  -s, --silent           Output nothing except warnings and errors.\n"
      "  -d, --debug            Display debug information (mainly for development).\n"
      "  -h, --help             Display this help-messageand exit.\n"
      "  -V, --version          Display the version of the program and exit.\n"
      "  -i, --input F          The file with the input rule transducers.\n"
      "  -o, --output F         The file where the test results are stored.\n"
      "  -p, --pairs F          The file with the symbol-pair strings.\n"
      "  -n, --names F          The file with the input rule-transducer names.\n"
      "  -R, --spaces           Give symbol-pairs in the input strings separated by\n"
      "                         spaces.\n"
      "  -R --read-symbols F    Give the symbol coding file for the input rule\n"
      "                         transducers in case the coding hasn't been stored with the\n"
      "                         rule-transducers.\n\n");

  fprintf(message_out,
      "The program can be used to test a set of rules with a test-file\n"
      "containing the valid and non-valid symbol-pair strings.\n"
      "Alternatively it can be used interactively by giving test cases\n"
      "when the program prompts for them. This is toggled by the\n"
      "parameter -p ( --pairs ), which suplies the test case file to the\n"
      "program. If it is omitted, the program will run interactively.\n\n"
      "More info on "
"<https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstPairTest>\n\n"
      "Report bugs to <hfst-bugs@helsinki.fi>\n"
);
}  
/* Parse the command line argument list. */
void parse_options(int argc, char * argv[])
{
  program_name = strdup(argv[0]);
  while (true)
    {
      static const struct option long_options[] =
    {
      {"debug",no_argument,NULL,'d'},
      {"verbose",no_argument,NULL,'v'},
      {"silent",no_argument,NULL,'s'},
      {"quiet",no_argument,NULL,'q'},
      {"help",no_argument,NULL,'h'},
      {"version",no_argument,NULL,'V'},
      {"input",required_argument,NULL,'i'},
      {"output",required_argument,NULL,'o'},
      {"spaces",no_argument,NULL,'S'},
      {"read-symbols",required_argument,NULL,'R'},
      {"names",required_argument,NULL,'n'},
      {"pairs",required_argument,NULL,'p'},
      {0,0,0,0}
    };
      int option_index = 0;
      int c = getopt_long(argc,argv,":SR:do:vhVi:sqa:n:p:",
              long_options, &option_index);
      // End of argument list.
      if ( c == EOF )
    break;

      switch (c)
    {
    case 'd': /* debug */ 
      debug = true;
      fprintf(stderr,
          "Debug mode.\n");
      break;
    case 'v': /* debug */ 
      verbose = true;
      fprintf(stderr,
          "Verbose mode.\n");
      break;
    case 'h': /* help */
      help();
      if (verbose or debug)
        fprintf(stderr,
            "Display help.\n");
      exit(0);
      break;
    case 'V': /* version */
      version();
      if (verbose or debug)
        fprintf(stderr,
            "Display version.\n");
      exit(0);
      break;
    case 'i': /* input FILE */
      fst_file_name = strdup(optarg);
      if (verbose or debug)
        fprintf(stderr,
            "Reading rule-transducers from the file %s.\n",
            fst_file_name);
      break;
    case 'o': /* input FILE */
      output_file_name = strdup(optarg);
      if (verbose or debug)
        fprintf(stderr,
            "Storint test results into the file %s.\n",
            fst_file_name);
      break;
    case 'p': /* pairs FILE */
      pair_file_name = strdup(optarg);
      if (verbose or debug)
        fprintf(stderr,
            "Reading symbol-pair strings from the file %s.\n",
            fst_file_name);
      break;
    case 'S': /* spaces */ 
      spaces = true;
      if (verbose or debug)
        fprintf(stderr,
            "Input string pairs separated by spaces.\n");
      break;
    case 's': /* silent */ 
      silent = true;
      break;
    case 'q': /* quiet */ 
      silent = true;
      break;
    case 'R': /* read-symbols FILE */
      alphabet_file_name = strdup(optarg);
      if (verbose or debug)
        fprintf(stderr,
            "Reading the alphabet from the file %s.\n",
            alphabet_file_name);
      break;
    case 'n':
      rule_names_file_name = strdup(optarg);
      if ( verbose or debug)
        fprintf(stderr,
            "Reading the rule transducer names from file %s\n",
            rule_names_file_name);
      break;
    case '?': /* Unknown option encountered */
      fprintf(stderr,
          "Error: Commandline argument %i %s is unknown.\n",
          optind,argv[optind-1]);
      usage();
      exit(1);
    case ':': /* Option with required argument missing encountered. */
      fprintf(stderr,
          "Error: Commandline argument %s is\n"
          "missing a file name\n",argv[optind-1]);
      usage();
      exit(1);
    }      

    }
  if (output_file_name == NULL)
  {
      message_out = stderr;
  }
      // Read fst_file_name as free argument
      if ((argc - optind) != 0) {
    if (fst_file_name == NULL)
      fst_file_name = strdup(argv[optind]);
      }

} 
