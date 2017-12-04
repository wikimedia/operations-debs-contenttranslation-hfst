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

#include "commandline_src/CommandLine.h"

namespace hfst {
  namespace twolcpre1 {
    int parse();
    void set_input(std::istream & istr);
    void set_output(std::ostream & ostr);
    void set_warning_stream(std::ostream & ostr);
    void set_error_stream(std::ostream & ostr);
  }
}

int main(int argc, char * argv[])
{
#ifdef WINDOWS
  _setmode(1, _O_BINARY);
#endif

  CommandLine command_line(argc,argv);

  if (command_line.help || command_line.version)
    {
      if (command_line.version)
	{ command_line.print_version(); }
      if (command_line.help)
	{ command_line.print_help(); }
      exit(0);
    }
  if (command_line.usage)
    {
      command_line.print_usage();
      exit(0);
    }
  if (! command_line.be_quiet)
    {
      if (! command_line.has_input_file)
	{ std::cerr << "Reading input from STDIN." << std::endl; }
      else
	{ std::cerr << "Reading input from " << command_line.input_file_name
		    << "." << std::endl; }
      if (! command_line.has_output_file)
	{ std::cerr << "Writing output to STDOUT." << std::endl; }
      else
	{ std::cerr << "Writing output to " << command_line.output_file_name
		    << "." << std::endl; }
    }
  if (command_line.be_verbose)
    { std::cerr << "Verbose mode." << std::endl; }

  hfst::twolcpre1::set_input(command_line.set_input_file());

  // Test that the output file is okay.
  (void)command_line.set_output_file();
  hfst::twolcpre1::set_output(std::cout);
  hfst::twolcpre1::set_warning_stream(std::cerr);
  hfst::twolcpre1::set_error_stream(std::cerr);
  return hfst::twolcpre1::parse();
}
