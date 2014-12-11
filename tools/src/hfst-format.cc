//! @file hfst-format.cc
//!
//! @brief Format checking command line tool
//!
//! @author HFST Team


//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, version 3 of the License.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WINDOWS
#include <io.h>
#endif


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>

#include "hfst-commandline.h"
#include "hfst-program-options.h"
#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstOutputStream.h"

#include "inc/globals-common.h"
#include "inc/globals-unary.h"

using std::ifstream;
using std::ios;

using hfst::HfstTransducer;

static bool list_formats = false;
static char * format_to_test = NULL;

void
print_usage()
{
  // c.f. 
  // http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dhelp
  fprintf(message_out, "Usage: %s [OPTIONS...] [INFILE]\n"
          "determine HFST transducer format\n"
          "\n", program_name);
  
  print_common_program_options(message_out);
  print_common_unary_program_options(message_out);
  fprintf
    (message_out, 
     "Tool-specific options:\n"
     "  -l, --list-formats     List available transducer formats\n"
     "                         and print them to standard output\n");
  fprintf
    (message_out, 
     "  -t, --test-format FMT  Whether the format FMT is available,\n"
     "                         exits with 0 if it is, else with 1\n");
  fprintf(message_out, "\n");
  print_common_unary_program_parameter_instructions(message_out);
  fprintf(message_out, "\n");
  print_report_bugs();
  fprintf(message_out, "\n");
  print_more_info();
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
          {"input1", required_argument, 0, '1'},
          {"input2", required_argument, 0, '2'},
          {"list-formats", no_argument, 0, 'l'},
          {"test-format", required_argument, 0, 't'},
          {0,0,0,0}
        };
        int option_index = 0;
        char c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             HFST_GETOPT_UNARY_SHORT "1:2:lt:",
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }
        switch (c)
        {
#include "inc/getopt-cases-common.h"
#include "inc/getopt-cases-unary.h"
        case '1':
          inputfilename = strdup(optarg);
          break;
        case '2':
          inputfilename = strdup(optarg);
          break;
          /*case 'l':
          inputfilename = strdup(optarg);
          break;*/
        case 'l':
          list_formats=true;
          break;
        case 't':
          format_to_test= strdup(optarg);
          break;
        default:
          // I suppose it's crucial for this tool to ignore other options
          break;
        }
    }

    if (format_to_test != NULL)
      {
        if ((strcmp(format_to_test, "sfst") == 0 &&
             HfstTransducer::is_implementation_type_available
             (hfst::SFST_TYPE))
            ||
            (strcmp(format_to_test, "openfst-tropical") == 0 &&
             HfstTransducer::is_implementation_type_available
             (hfst::TROPICAL_OPENFST_TYPE))
            ||
            (strcmp(format_to_test, "openfst-log") == 0 &&
             HfstTransducer::is_implementation_type_available
             (hfst::LOG_OPENFST_TYPE))
            ||
            (strcmp(format_to_test, "foma") == 0 &&
             HfstTransducer::is_implementation_type_available
             (hfst::FOMA_TYPE))
            ||
            (strcmp(format_to_test, "optimized-lookup-unweighted") == 0 &&
             HfstTransducer::is_implementation_type_available
             (hfst::HFST_OL_TYPE))
            ||
            (strcmp(format_to_test, "optimized-lookup-weighted") == 0 &&
             HfstTransducer::is_implementation_type_available
             (hfst::HFST_OLW_TYPE))
            )
          exit(0);
        exit(1);
        }

    if (list_formats)
      {
        fprintf(stdout,   " Backend                         "
                "Names recognized\n\n");

        if (HfstTransducer::is_implementation_type_available
            (hfst::SFST_TYPE))
          fprintf(stdout, " SFST                            "
                  "sfst\n");

        if (HfstTransducer::is_implementation_type_available
            (hfst::TROPICAL_OPENFST_TYPE))
          fprintf(stdout, " OpenFst (tropical weights)      "
                  "openfst-tropical, openfst, ofst, ofst-tropical\n");
        
        if (HfstTransducer::is_implementation_type_available
            (hfst::LOG_OPENFST_TYPE))
          fprintf(stdout, " OpenFst (logarithmic weights)   "
                  "openfst-log, ofst-log\n");
        
        if (HfstTransducer::is_implementation_type_available
            (hfst::FOMA_TYPE))
          fprintf(stdout, " foma                            "
                  "foma\n");
        
        if (HfstTransducer::is_implementation_type_available
            (hfst::HFST_OL_TYPE))
          fprintf(stdout, " Optimized lookup (weighted)     "
                  "optimized-lookup-unweighted, olu\n");              
        
        if (HfstTransducer::is_implementation_type_available
            (hfst::HFST_OLW_TYPE))
          fprintf(stdout, " Optimized lookup (unweighted)   "
                  "optimized-lookup-weighted, olw, optimized-lookup, ol\n");
        
        exit(0);
      }

    (void)inputfilename;
    (void)inputNamed;

    try {

      if (inputfilename == NULL)
    {
      if ((argc - optind) == 0)
        {
          inputfilename = strdup("<stdin>");
          hfst::HfstInputStream is("");
          return is.get_type();
        }
      else if ((argc - optind) == 1)
        {
          inputfilename = argv[optind];
        }     
    }
      hfst::HfstInputStream is(inputfilename);
      return is.get_type();
    } // NotTransducerStreamException
    catch (const HfstException e) {
      fprintf(stderr, "ERROR: The file/stream does not contain transducers.\n");
      exit(1);
    }
}


int main (int argc, char * argv[])
{
#ifdef WINDOWS
  _setmode(0, _O_BINARY);
#endif

  hfst_set_program_name(argv[0], "0.1", "HfstFormat");
  verbose = true;
  hfst::ImplementationType type = static_cast<hfst::ImplementationType>(parse_options(argc,argv));
  verbose_printf("Transducers in %s are of type %s\n", inputfilename,
                 hfst_strformat(type));
}
