//       This program is free software: you can redistribute it and/or modify
//       it under the terms of the GNU General Public License as published by
//       the Free Software Foundation, version 3 of the License.
//
//       This program is distributed in the hope that it will be useful,
//       but WITHOUT ANY WARRANTY; without even the implied warranty of
//       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//       GNU General Public License for more details.
//
//       You should have received a copy of the GNU General Public License
//       along with this program.  If not, see <http://www.gnu.org/licenses/>.

#if HAVE_CONFIG_H
#  include <config.h>
#endif
#include "hfst-program-options.h"

// All programs
void print_common_program_options(FILE *file) {

  fprintf(file, "Common options:\n"
          "  -h, --help             Print help message\n"
          "  -V, --version          Print version info\n"
          "  -v, --verbose          Print verbosely while processing\n"
          "  -q, --quiet            Only print fatal erros and requested "
          "output\n"
          "  -s, --silent           Alias of --quiet\n");
   
}

// One transducer to one transducer:
//   compatible
//   determinize
//   head
//   invert
//   minimize
//   project
//   push-weights
//   remove-epsilons
//   repeat
//   reverse
//   symbols
//   tail
//   unweighted2weighted
//   weighted2unweighted
void print_common_unary_program_options(FILE *file) {

  fprintf(file, "Input/Output options:\n"
        "  -i, --input=INFILE     Read input transducer from INFILE\n"
        "  -o, --output=OUTFILE   Write output transducer to OUTFILE\n"
  );
}

void print_common_unary_program_parameter_instructions(FILE *file) {

  fprintf(file,
      "If OUTFILE or INFILE is missing or -, standard streams will be used.\n"
      "Format of result depends on format of INFILE\n"
      );

}

// Two transducers to one transducer
//   compose
//   concatenate
//   conjunct
//   disjunct,
void print_common_binary_program_options(FILE *file) {

  fprintf(file, "Input/Output options:\n"
          "  -1, --input1=INFILE1   Read first input transducer from INFILE1\n"
          "  -2, --input2=INFILE2   Read second input transducer from INFILE2\n"
          "  -C, --do-not-convert   Do not allow transducers to be converted into the same type\n"
          "  -o, --output=OUTFILE   Write results to OUTFILE\n");
}

void print_common_binary_program_parameter_instructions(FILE *file) {

  fprintf(file,
      "If OUTFILE, or either INFILE1 or INFILE2 is missing or -,\n"
      "standard streams will be used.\n"
      "INFILE1, INFILE2, or both, must be specified.\n"
      "Format of result depends on format of INFILE1 and INFILE2;\n"
      "both should have the same format.\n"
      );

  fprintf(file,
      "\n"
      "The operation is applied pairwise for INFILE1 and INFILE2\n"
      "that must have the same number of transducers.\n"
      "If INFILE2 has only one transducer, the operation is applied for\n"
      "each transducer in INFILE1 keeping the second transducer constant.\n"
      );

}

