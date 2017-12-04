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
#include <cstdio>

// All programs
void print_common_program_options(FILE *file);
// Use in getopt arguments
#define HFST_GETOPT_COMMON_SHORT ":hVvqsd"
#define HFST_GETOPT_COMMON_LONG  {"help", no_argument, 0, 'h'},\
  {"version", no_argument, 0, 'V'},\
  {"verbose", no_argument, 0, 'v'},\
  {"quiet", no_argument, 0, 'q'},\
  {"silent", no_argument, 0, 's'},\
  {"debug", no_argument, 0, 'd'}


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
void print_common_unary_program_options(FILE *file);
void print_common_unary_program_parameter_instructions(FILE *file);
// use for getopt parameters for
#define HFST_GETOPT_UNARY_SHORT "i:o:"
#define HFST_GETOPT_UNARY_LONG {"input", required_argument, 0, 'i'},\
  {"output", required_argument, 0, 'o'}

// One transducer to text:
//   fst2txt
//   fst2strings
void print_common_unary_string_program_options(FILE *file);

// Text to one transducer: txt2fst
// Text to transducer(s): strings2fst
//        "  -i, --input=FILENAME       Read input text-file from FILENAME\n"
//        "  -o, --output=FILENAME      Write output transducer(s) to FILENAME\n"
//        "  -R, --symbols=FILENAME     Read symbol table from FILENAME\n"
//        "  -D, --do-not-write-symbols         Do not write symbol table with the output transducer(s)\n"
//        "  -W, --write-symbols-to=FILENAME    Write symbol table to file FILENAME\n"


// Two transducers to one transducer: compose, concatenate, conjunct, disjunct,
void print_common_binary_program_options(FILE *file);
void print_common_binary_program_parameter_instructions(FILE *file);
#define HFST_GETOPT_BINARY_SHORT "1:2:o:C"
#define HFST_GETOPT_BINARY_LONG {"input1", required_argument, 0, '1'},\
    {"input2", required_argument, 0, '1'},\
    {"output", required_argument, 0, 'o'},\
    {"do-not-convert", no_argument, 0, 'C'}

// Write separate commandline helps: compare, split, strings2fst, summarize, txt2fst

