#ifdef WINDOWS
#include <io.h>
#endif

#include <stdio.h>
#include "SfstCompiler.h"
#include "HfstTransducer.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>

#include "hfst-commandline.h"
#include "hfst-program-options.h"

#include "inc/globals-common.h"
#include "inc/globals-unary.h"

bool verbose_ = false;
std::string filename = "";
std::string foldername = "";

using std::cerr;
using namespace hfst;

int switch_=0;
hfst::ImplementationType output_format = ERROR_TYPE;

int Compact=0;
int LowMem=0;

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
        int c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
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
    verbose_ = verbose;
    if (output_format == hfst::ERROR_TYPE)
      {
        verbose_printf("Output format not specified, "
             "defaulting to openfst tropical\n");
        output_format = hfst::TROPICAL_OPENFST_TYPE;
      }
    filename = std::string(inputfilename);

    if (NULL != inputfilename && strcmp(inputfilename, "<stdin>") != 0)
    {
	std::string str(inputfilename);
	size_t found = str.find_last_of("/\\");
	if (found != std::string::npos)
  	  foldername = std::string(str.substr(0,found).c_str());
    }

    return EXIT_CONTINUE;
}

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
      verbose_ = 0;
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
      switch_ = 1;
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

int main( int argc, char *argv[] )

{
#ifdef WINDOWS
  _setmode(1, _O_BINARY);
#endif

  hfst_set_program_name(argv[0], "0.1", "HfstSfstPl2Fst");
  int retval = parse_options(argc, argv);
  if (retval != EXIT_CONTINUE)
    return retval;

  if (strcmp(outfilename,"<stdout>") != 0)
    fclose(outfile); // stream is used when writing the result

  // Unknown symbols cannot be used in SFST-PL syntax.
  // If the HFST library is aware of this, some optimization can be done.
  hfst::set_unknown_symbols_in_use(false);
  SfstCompiler * compiler = new SfstCompiler(output_format, verbose_);
  compiler->set_input(inputfile);
  compiler->set_filename(filename);
  compiler->set_foldername(foldername);
  compiler->set_switch(switch_);

  char * strarg = NULL;
  try {
    compiler->parse();
    fclose(inputfile);
      try {
        if (strcmp(outfilename,"<stdout>") == 0)
        {
          strarg = strdup("");
          compiler->write_to_file(compiler->get_result(), NULL, strarg);
        }
	else
        {
          strarg = strdup(outfilename);
          compiler->write_to_file(compiler->get_result(), NULL, strarg);
        }
      } catch (HfstException e) {
          printf("\nAn error happened when writing to file \"%s\"\n", outfilename); }

      delete compiler->get_result();

  }
  catch(const char* p) {
      cerr << "\n" << p << "\n\n";
      if (strarg != NULL) { free(strarg); }
      exit(1);
  }
  catch (HfstException e) {
    cerr << "\n" << e.what() << "\n\n";
    if (strarg != NULL) { free(strarg); }
    exit(1);
  }

  if (strarg != NULL) { free(strarg); }
  exit(0);
}
