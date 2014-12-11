//! @file hfst-concatenate.cc
//!
//! @brief Transducer concatenation command line tool
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

#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstOutputStream.h"

using hfst::HfstTransducer;
using hfst::HfstInputStream;
using hfst::HfstOutputStream;
using hfst::ImplementationType;


#include "hfst-commandline.h"
#include "hfst-program-options.h"
#include "hfst-tool-metadata.h"
#include "inc/globals-common.h"
#include "inc/globals-binary.h"

static bool harmonize_flags=false;
static bool harmonize=true;

void
print_usage()
{
    // c.f. http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dhelp
    fprintf(message_out, "Usage: %s [OPTIONS...] [INFILE1 [INFILE2]]\n"
             "Concatenate two transducers\n"
        "\n", program_name );
        print_common_program_options(message_out);
        print_common_binary_program_options(message_out);
        fprintf(message_out,
                "Harmonization:\n"
                "  -H, --do-not-harmonize Do not harmonize symbols.\n"
                "  -F, --harmonize-flags  Harmonize flag diacritics.\n");
        fprintf(message_out, "\n");
        print_common_binary_program_parameter_instructions(message_out);
        fprintf(message_out, "\n");
        fprintf(message_out,
            "\n"
            "Examples:\n"
            "  %s -o catdog.hfst cat.hfst dog.hfst\n"
            "concatenates cat.hfst with dog.hfst and writes results to catdog.hfst\n"
            "\n",
            program_name );
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
          HFST_GETOPT_BINARY_LONG,
          {"harmonize-flags", no_argument, 0, 'F'},
          {"do-not-harmonize", no_argument, 0, 'H'},
          {0,0,0,0}
        };
        int option_index = 0;
        char c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             HFST_GETOPT_BINARY_SHORT "FH",
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }
        switch (c)
        {
#include "inc/getopt-cases-common.h"
#include "inc/getopt-cases-binary.h"
        case 'F':
          harmonize_flags=true;
          break;
        case 'H':
          harmonize=false;
          break;
#include "inc/getopt-cases-error.h"
        }
    }

#include "inc/check-params-common.h"
#include "inc/check-params-binary.h"
    return EXIT_CONTINUE;
}

int
concatenate_streams(HfstInputStream& firststream, HfstInputStream& secondstream,
                    HfstOutputStream& outstream)
{
    // there must be at least one transducer in both input streams
    bool continueReading = firststream.is_good() && secondstream.is_good();

    if (firststream.get_type() != secondstream.get_type())
      {
        warning(0, 0, "Tranducer type mismatch in %s and %s; "
              "using former type as output\n",
              firstfilename, secondfilename);
      }
    HfstTransducer * first=0;
    HfstTransducer * second=0;
    size_t transducer_n_first = 0; // transducers read from first stream
    size_t transducer_n_second = 0; // transducers read from second stream

    while (continueReading) {
        first = new HfstTransducer(firststream);
        transducer_n_first++;
        if (secondstream.is_good())
          {
            second = new HfstTransducer(secondstream);
            transducer_n_second++;
          }
        char* firstname = hfst_get_name(*first, firstfilename);
        if (second == 0) { // make scan-build happy, this should not happen
          throw "Error: second stream has a NULL value."; }
        char* secondname = hfst_get_name(*second, secondfilename);
        if (transducer_n_first == 1)
        {
            verbose_printf("Concatenating %s and %s...\n", firstname, 
                        secondname);
        }
        else
        {
            verbose_printf("Concatenating %s and %s... " SIZE_T_SPECIFIER "\n", firstname,
                           secondname, transducer_n_first);
        }
        if (first->has_flag_diacritics() and second->has_flag_diacritics()) 
          {
            if (not harmonize_flags)
              {
                if (not silent) 
                  {
                    warning(0, 0, "The argumentes contain "
                            "flag diacritics. Use -F to harmonize them.", 
                            secondname, firstname);
                  }
              }
            else
              {
                first->harmonize_flag_diacritics(*second,false);
              }
        }
        try
          {
            first->concatenate(*second, harmonize);
          }
        catch (TransducerTypeMismatchException ttme)
          {
            error(EXIT_FAILURE, 0, "Could not concatenate %s and %s [" SIZE_T_SPECIFIER "]\n"
                  "types %s and %s are not compatible for concatenation",
                  firstname, secondname, transducer_n_first,
                  hfst_strformat(firststream.get_type()),
                  hfst_strformat(secondstream.get_type()));
          }

        hfst_set_name(*first, *first, *second, "concatenate");
        hfst_set_formula(*first, *first, *second, "⋅");
        outstream << *first;

        continueReading = firststream.is_good() && 
          (secondstream.is_good() || transducer_n_second == 1);

        delete first;
        first=0;
        // delete the transducer of second stream, unless we continue reading
        // the first stream and there is only one transducer in the second 
        // stream
        if ((continueReading && secondstream.is_good()) || not continueReading)
          {
            delete second;
            second=0;
          }

        free(firstname);
        free(secondname);
    }
    
    if (firststream.is_good())
      {
        error(EXIT_FAILURE, 0, 
              "second input '%s' contains fewer transducers than first input"
              " '%s'; this is only possible if the second input contains"
              " exactly one transducer", 
              secondfilename, firstfilename);
      }

    if (secondstream.is_good())
    {
      error(EXIT_FAILURE, 0, "first input '%s' contains fewer transducers than"
            " second input '%s'",
            firstfilename, secondfilename);
    }

    firststream.close();
    secondstream.close();
    outstream.close();
    return EXIT_SUCCESS;
}


int main( int argc, char **argv ) {
#ifdef WINDOWS
  _setmode(0, _O_BINARY);
  _setmode(1, _O_BINARY);
#endif
    hfst_set_program_name(argv[0], "0.1", "HfstConcatenate");
    int retval = parse_options(argc, argv);
    if (retval != EXIT_CONTINUE)
    {
        return retval;
    }
    // close buffers, we use streams
    if (firstfile != stdin)
    {
        fclose(firstfile);
    }
    if (secondfile != stdin)
    {
        fclose(secondfile);
    }
    if (outfile != stdout)
    {
        fclose(outfile);
    }
    verbose_printf("Reading from %s and %s, writing to %s\n", 
        firstfilename, secondfilename, outfilename);
    // here starts the buffer handling part
    HfstInputStream* firststream = NULL;
    HfstInputStream* secondstream = NULL;
    try {
        firststream = (firstfile != stdin) ?
            new HfstInputStream(firstfilename) : new HfstInputStream();
    } catch(const HfstException e)   {
        error(EXIT_FAILURE, 0, "%s is not a valid transducer file",
              firstfilename);
    }
    try {
        secondstream = (secondfile != stdin) ?
            new HfstInputStream(secondfilename) : new HfstInputStream();
    } catch(const HfstException e)   {
        error(EXIT_FAILURE, 0, "%s is not a valid transducer file",
              secondfilename);
    }
    HfstOutputStream* outstream = (outfile != stdout) ?
        new HfstOutputStream(outfilename, firststream->get_type()) :
        new HfstOutputStream(firststream->get_type());

    if ( is_input_stream_in_ol_format(firststream, "hfst-concatenate") ||
         is_input_stream_in_ol_format(secondstream, "hfst-concatenate") )
      {
        return EXIT_FAILURE;
      }

    retval = concatenate_streams(*firststream, *secondstream, *outstream);
    delete firststream;
    delete secondstream;
    delete outstream;
    free(firstfilename);
    free(secondfilename);
    free(outfilename);
    return retval;
}

