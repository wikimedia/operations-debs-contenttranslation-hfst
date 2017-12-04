//! @file hfst-build-tagger.cc
//!
//! @brief Tool for training taggers.
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
{ /* nothing */ }

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
        int c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             HFST_GETOPT_UNARY_SHORT "wDnf:",
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }

        switch (c)
        {
          // instead of including "inc/getopt-cases-common.h", it is copied here
          // and case 'V' is modified.
        case 'd':
          debug = true;
          break;
        case 'h':
          print_usage();
          return EXIT_SUCCESS;
          break;
        case 'V':
          // do nothing
          return EXIT_SUCCESS;
          break;
        case 'v':
          verbose = true;
          silent = false;
          break;
        case 'q':
        case 's':
          verbose = false;
          silent = true;
          break;
        case 'o':
          outfilename = hfst_strdup(optarg);
          outfile = hfst_fopen(outfilename, "w");
          if (outfile == stdout)
            {
              free(outfilename);
              outfilename = hfst_strdup("<stdout>");
              message_out = stderr;
            }
          outputNamed = true;
          break;
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

int process_input_data(std::string output_file_prefix)
{
  // Read training statistics from STDIN.
  verbose_printf("Compiling word and sequence statistics to transducers.");
  TaggerBuilder tagger_builder;
      
  // Write the result in STDOUT or files depending on command-line args.
  if (std::string(output_file_prefix) == "<stdout>")
    { tagger_builder.store(); }
  else
    { tagger_builder.store(output_file_prefix); }

  return EXIT_SUCCESS;
}

int main( int argc, char **argv )
{
#ifdef WINDOWS
    _setmode(1, _O_BINARY);
#endif
    hfst_set_program_name(argv[0], "0.1", "HfstBuildTagger");
    int retval = parse_options(argc, argv);

    ModelBuilder::verbose = verbose;

    if (retval != EXIT_CONTINUE)
    { return retval; }

    retval = process_input_data(outfilename);

    return retval;
}


