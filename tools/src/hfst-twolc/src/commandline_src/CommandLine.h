#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

//! @file CommandLine.h

//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, version 3 of the Licence.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <iostream>
#include <getopt.h>

#include "HfstTransducer.h"
using hfst::ImplementationType;

/** successful return value for argument parsing routine */
#define EXIT_CONTINUE 42

#if HAVE_XSTRDUP
#  define hfst_strdup xstrdup
#else
#  define hfst_strdup strdup
#endif

const std::string PROGRAM_NAME = "hfst-twolc";
//! @brief Class for parsing commandline arguments.
class CommandLine
{
 protected:
  int parse_options(int argc, char** argv);
 public:
  bool be_verbose;
  bool be_quiet;
  bool has_input_file;
  std::string input_file_name;
  std::istream * input_file;
  bool has_output_file;
  std::string output_file_name;
  std::ostream * output_file;
  ImplementationType format;
  bool resolve_left_conflicts;
  bool resolve_right_conflicts;
  bool help;
  bool version;
  bool usage;
  bool has_debug_file;

  CommandLine(int argc,char * argv[]);
  ~CommandLine(void);
  void print_version(void);
  void print_help(void);
  void print_usage(void);
  std::istream &set_input_file(void);
  std::ostream &set_output_file(void);
};

#ifdef TEST_COMMAND_LINE
std::ostream &operator<<(std::ostream &out,const CommandLine &command_line);
#endif

#endif
