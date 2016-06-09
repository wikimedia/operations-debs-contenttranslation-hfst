//! @file hfst-fst2fst.cc
//!
//! @brief HFST header stripping tool
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

#include <cstdio>
#include <cstdlib>
#include <getopt.h>

#include "hfst-commandline.h"
#include "hfst-program-options.h"

#include "inc/globals-common.h"
#include "inc/globals-unary.h"

void
print_usage()
{
    // c.f. http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dhelp
    fprintf(message_out, "Usage: %s [OPTIONS...] [INFILE]\n"
        "Remove any HFST3 headers\n"
        "\n", program_name);

    print_common_program_options(message_out);
    print_common_unary_program_options(message_out);
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
        {0,0,0,0}
        };
        int option_index = 0;
        // add tool-specific options here 
        char c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             HFST_GETOPT_UNARY_SHORT,
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }


        switch (c)
        {
#include "inc/getopt-cases-common.h"
#include "inc/getopt-cases-unary.h"
#include "inc/getopt-cases-error.h"
        }
    }
    
#include "inc/check-params-common.h"
#include "inc/check-params-unary.h"
    return EXIT_CONTINUE;
}

int
process_stream(FILE* f_in, FILE* f_out)
{
  const char* header = "HFST3";
  int header_loc = 0; // how much of the header has been found
  while(true)
  {
    int c = getc(f_in);
    if(c == EOF)
      return EXIT_SUCCESS;
    verbose_printf("Stripping...\n");
    if(c == header[header_loc])
    {
      if(header_loc == 5) // we've found the whole header (incl. null terminator)
      {
        // eat text until the next null terminator
        do
        {
          c = getc(f_in);
        } while (c != '\0' && c != EOF);
        header_loc = 0;
      }
      else
        header_loc++; // look for the next character now
    }
    else
    {
      if(header_loc > 0)
      { // flush the characters that could have been header but turned out not to be
        for(int i=0; i<header_loc; i++)
          putc(header[i], f_out);
        header_loc = 0;
        
        ungetc(c, f_in); // the character we just grabbed could be the start of the header, so put it back
      }
      else
        putc(c, f_out);
    }
  }
  return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
  hfst_set_program_name(argv[0], "0.1", "HfstStripHeader");
  int retval = parse_options(argc, argv);
  if (retval != EXIT_CONTINUE)
  {
    return retval;
  }
  verbose_printf("Reading from %s, writing to %s\n", 
    inputfilename, outfilename);
  
  retval = process_stream(inputfile, outfile);
    
  free(inputfilename);
  free(outfilename);
  return retval;
}

