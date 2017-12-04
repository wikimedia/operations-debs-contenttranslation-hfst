//! @file hfst-lexc.cc
//!
//! @brief Lexc compilation command line tool
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
#include "HfstOutputStream.h"
#include "HfstExceptionDefs.h"
#include "parsers/LexcCompiler.h"

using hfst::HfstTransducer;
using hfst::HfstInputStream;
using hfst::HfstOutputStream;
using hfst::ImplementationType;


#include "hfst-commandline.h"
#include "hfst-program-options.h"
#include "hfst-tool-metadata.h"

#include "inc/globals-common.h"
static char** lexcfilenames = 0;
static FILE** lexcfiles = 0;
static unsigned int lexccount = 0;
static bool is_input_stdin = true;
static ImplementationType format = hfst::UNSPECIFIED_TYPE;
static bool start_readline = false;
static char* tempfilename = 0;

int lexc_readline_loop(ImplementationType format);

void
print_usage()
{
    // c.f. http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dhelp
    fprintf(message_out, "Usage: %s [OPTIONS...] [INFILE1...]]\n"
             "Compile lexc files into transducer or imitate Xerox lexc\n"
             "This is a wrapper around foma lexc, and does not support weights\n"
             "For a native hfst tool with weights, use hfst-lexc instead\n"
        "\n", program_name );
        print_common_program_options(message_out);
        fprintf(message_out, "Input/Output options:\n"
               "  -f, --format=FORMAT       compile into FORMAT transducer\n"
               "  -o, --output=OUTFILE      write result into OUTFILE\n"
               "  -X, --xerox, --readline   imitate Xerox lexc user interface\n"
        );
        fprintf(message_out, "\n");
        fprintf(message_out,
                "If INFILE or OUTFILE are omitted or -, standard streams will "
                "be used\n"
        "The possible values for FORMAT are { sfst, openfst-tropical, "
        "openfst-log,\n"
        "foma, optimized-lookup-unweighted, optimized-lookup-weighted }.\n");
        fprintf(message_out,
            "\n"
            "Examples:\n"
            "  %s -o cat.hfst cat.lexc               Compile single-file "
            "lexicon\n"
            "  %s -o L.hfst Root.lexc 2.lexc 3.lexc  Compile multi-file "
            "lexicon\n"
            "\n",
            program_name, program_name );
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
          {"format",   required_argument, 0, 'f'},
          {"output",   required_argument, 0, 'o'},
          {"latin1",   optional_argument, 0, 'l'},
          {"utf8",     optional_argument, 0, 'u'},
          {"readline", no_argument,       0, 'X'},
          {"xerox",    no_argument,       0, 'X'},
          {0,0,0,0}
        };
        int option_index = 0;
        int c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             "f:o:l::u::X",
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }
        switch (c)
        {
#include "inc/getopt-cases-common.h"
        case 'f':
          format = hfst_parse_format_name(optarg);
          break;
        case 'l':
          error(EXIT_FAILURE, 0, "Latin1 encoding not supported, please use "
                "iconv, recode, uconv or similar utility to convert legacy "
                "lexicons into Unicode UTF-8 format");
          return EXIT_FAILURE;
          break;
        case 'u':
          warning(0, 0, "UTF-8 is always the default in HFST tools");
          break;
        case 'X':
          start_readline = true;
          break;
#include "inc/getopt-cases-error.h"
        }
    }

#include "inc/check-params-common.h"

#if HAVE_FOMA
    if (format == hfst::UNSPECIFIED_TYPE)
      {
        if (!silent)
          {
            warning(0, 0, "Defaulting to foma type "
                    "(since it has native lexc support)\n");
          }
      }
    else
      {
        if (format != hfst::FOMA_TYPE) {
          warning(0, 0, "Using foma type (since it has native lexc support)\n"); }
      }
#else
    error(EXIT_FAILURE, 0, "Foma back-end is not enabled\n");
#endif

    if (outfile == stdout)
      {
        /*error(EXIT_FAILURE, 0, "Cannot write result to <stdout> since backend "
              "libraries will pollute it;\n"
              "Use command-line option --output meanwhile");*/
      }
    if (start_readline && (argc - optind > 0))
      {
        error(EXIT_FAILURE, 0, "Trailing arguments not allowed for interactive "
              "mode");
        return EXIT_FAILURE;
      }
    else if (!start_readline && (argc == optind))
      {
#if AT_END_OF_DEPRECATION_PERIOD
        if (!silent) {
          warning(0, 0, "Reading lexc script (not a lexicon) "
                  "from stdin with readline");
        }
        start_readline = true;
#else
        if (!silent) {
          warning(0, 0, "Reading lexicons from stdin is deprecated and will "
                  "be removed in next versions;\n"
                  "this is not even supported by the original lexc");
        }
        char* tempfilename = hfst_strdup("/tmp/hfst-lexcXXXXXX");
        int temporary_fd = hfst_mkstemp(tempfilename);
        verbose_printf("Copying data from <stdin> to temporary file\n");
        char* fdata = 0;
        size_t len = 0;
        while (hfst_getline(&fdata, &len, stdin) != -1)
          {
            hfst_write(temporary_fd, fdata, strlen(fdata));
          }
        hfst_close(temporary_fd);
        lexccount = 1;
        lexcfiles = static_cast<FILE**>(malloc(sizeof(FILE*) * lexccount));
        lexcfilenames = static_cast<char**>(malloc(sizeof(char*) * lexccount));
        lexcfiles[0] = hfst_fopen(tempfilename, "r");
        lexcfilenames[0] = hfst_strdup(tempfilename);
#endif
      }
    else if (argc - optind > 0)
      {
        lexcfilenames = static_cast<char**>(malloc(sizeof(char*)*(argc-optind)));
        lexcfiles = static_cast<FILE**>(malloc(sizeof(char*)*(argc-optind)));
        while (optind < argc)
          {
            lexcfilenames[lexccount] = hfst_strdup(argv[optind]);
            lexcfiles[lexccount] = hfst_fopen(argv[optind], "r");
            lexccount++;
            optind++;
          }
        is_input_stdin = false;
      }
    else
      {
        lexcfilenames = static_cast<char**>(malloc(sizeof(char*)));
        lexcfiles = static_cast<FILE**>(malloc(sizeof(FILE*)));
        lexcfilenames[0] = hfst_strdup("<stdin>");
        lexcfiles[0] = stdin;
        is_input_stdin = true;
        lexccount++;
      }

    if (lexccount > 1)
      {
#ifdef WINDOWS
        error(EXIT_FAILURE, 0, "multiple file handling not supported on "
              "Windows;\n"
              "use a single file");
#else
        if (!silent) {
          warning(0, 0, "multiple file handling is not supported by all "
                  "backends;\n"
                  "concatenating to temporary file");
        }
        tempfilename = hfst_strdup("/tmp/hfst-lexcXXXXXX");
        int temporary_fd = hfst_mkstemp(tempfilename);
        for (unsigned int i = 0; i < lexccount; i++)
          {
            verbose_printf("Copying data from %s to temporary file\n",
                           lexcfilenames[i]);
            hfst_fseek(lexcfiles[i], -1, SEEK_END);
            long file_length = hfst_ftell(lexcfiles[i]);
            rewind(lexcfiles[i]);
            char* fdata = static_cast<char*>(malloc(sizeof(char) *
                                                    (file_length +1)));
            hfst_fread(fdata, sizeof(char), file_length,
                                   lexcfiles[i]);
            fdata[file_length] = '\0';
            fclose(lexcfiles[i]);
            free(lexcfilenames[i]);
            hfst_write(temporary_fd, fdata, file_length);
          }
        hfst_close(temporary_fd);
        lexccount = 1;
        lexcfiles[0] = hfst_fopen(tempfilename, "r");
        lexcfilenames[0] = hfst_strdup(tempfilename);
#endif
      }
    return EXIT_CONTINUE;
}

int
lexc_streams(HfstOutputStream& outstream)
{
    HfstTransducer* trans = 0;
    for (unsigned int i = 0; i < lexccount; i++)
      {
        verbose_printf("Parsing lexc file %s\n", lexcfilenames[i]);
        if (lexcfiles[i] == stdin)
          {
            error(EXIT_FAILURE, 0, "Cannot read from stdin");
          }
        else
          {
            trans = HfstTransducer::read_lexc_ptr(lexcfilenames[i], hfst::FOMA_TYPE, verbose);
            if (0 == trans)
              {
                error(EXIT_FAILURE, 0, "Could not parse %s correctly.\n"
                      "If there is no further info about the error, try "
                      "-v or -d.", lexcfilenames[i]);
              }
          }
      }
    assert(trans != NULL);
    trans->convert(format);
    hfst_set_name(*trans, lexcfilenames[0], "lexc");
    hfst_set_formula(*trans, lexcfilenames[0], "L");
    verbose_printf("\nWriting... ");
    outstream << *trans;
    verbose_printf("done\n");
    delete trans;
    outstream.close();
    return EXIT_SUCCESS;
}


int main( int argc, char **argv ) {
#ifdef WINDOWS
  _setmode(1, _O_BINARY);
#endif

    hfst_set_program_name(argv[0], "0.1", "HfstLexcWrapper");
    int retval = parse_options(argc, argv);
    if (retval != EXIT_CONTINUE)
    {
        return retval;
    }
    // close buffers, we use filenames
    for (unsigned int i = 0; i < lexccount; i++)
      {
        if (lexcfiles[i] != stdin)
          {
            fclose(lexcfiles[i]);
          }
      }
    if (outfile != stdout)
    {
        fclose(outfile);
    }
    if (start_readline)
      {
        lexc_readline_loop(format);
        return EXIT_FAILURE;
      }
    verbose_printf("Reading from ");
    for (unsigned int i = 0; i < lexccount; i++)
      {
        verbose_printf("%s, ", lexcfilenames[i]);
      }
    verbose_printf("writing to %s\n", outfilename);
    // here starts the buffer handling part
    try
      {
        HfstOutputStream* outstream = (outfile != stdout) ?
            new HfstOutputStream(outfilename, format) :
            new HfstOutputStream(format);
        retval = lexc_streams(*outstream);
        delete outstream;
      }
    catch (ImplementationTypeNotAvailableException itnae)
      {
        verbose_printf("Caught exception like this:\n%s\n",
                       itnae().c_str());
        error(EXIT_FAILURE, 0, "You were trying to compile with format "
              "that has been turned off from libhfst\n"
              "try using (other) -f argument, such as openfst:\n");
      }
    free(lexcfilenames);
    free(outfilename);
    if (tempfilename != 0)
      {
        verbose_printf("Deleting temporary files on successful exit\n");
        hfst_remove(tempfilename);
      }
    return retval;
}

