//! @file hfst-open-input-file-for-tagger.cc
//!
//! @brief Transducer array printing command line tool
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

#include <iostream>
#include <fstream>

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

#include "build_model_src/TaggerBuilder.h"

void
print_usage()
{
    // c.f. http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dhelp
    fprintf(message_out, "Usage: %s [OPTIONS...] [INFILE]\n"
        "Compile training data file into an hfst part-of-speech tagger.\n"
        "\n", "hfst-train-tagger");

    print_common_program_options(message_out);
    print_common_unary_program_options(message_out);
    fprintf(message_out, "\n");
    fprintf(message_out, "\n");
    print_report_bugs();
    fprintf(message_out, "\n");
    print_more_info();
}

int
parse_options(int argc, char** argv)
{
    extend_options_getenv(&argc, &argv);
    // use of this function requires options are settable on global scope
    while (true)
    {
        static const struct option long_options[] =
        {
        HFST_GETOPT_COMMON_LONG,
        HFST_GETOPT_UNARY_LONG,
          // add tool-specific options here
            {0,0,0,0}
        };
        int option_index = 0;
        // add tool-specific options here 
        char c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             HFST_GETOPT_UNARY_SHORT "wDnf:",
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }

        switch (c)
        {
#include "inc/getopt-cases-common.h"
#include "inc/getopt-cases-unary.h"
          // add tool-specific cases here
        break;
#include "inc/getopt-cases-error.h"
        }
    }

#include "inc/check-params-common.h"
#include "inc/check-params-unary.h"
    return EXIT_CONTINUE;
}

void echo_stream_to_stdout(std::istream &in)
{
  std::string line;

  while (std::getline(in,line))
    { std::cout << line << std::endl; }
}

int main( int argc, char **argv ) 
{
  // This tool is used in a pipeline of commands, so help and version messages
  // cannot be written to stdout.
  message_out = stderr;

  hfst_set_program_name("hfst-train-tagger", "0.1", "HfstTrainTagger");

  int retval = (parse_options(argc, argv));

  if (retval != EXIT_CONTINUE)
    { return retval; }

  std::string input_file_str = std::string(inputfilename);
  std::string output_file_str = std::string(outfilename);
  if (output_file_str != "<stdout>")
    { output_file_str += ".{lex,seq}"; }

  verbose_printf("Reading training data from %s.\n"
                 "Writing tagger to %s\n", 
                 input_file_str.c_str(), output_file_str.c_str());

  if (std::string(inputfilename) == "<stdin>")
    { echo_stream_to_stdout(std::cin); }
  else
    { 
      std::ifstream in(inputfilename);
      echo_stream_to_stdout(in); 
    }
  
  free(inputfilename);
  free(outfilename);
  return EXIT_CONTINUE;
}
