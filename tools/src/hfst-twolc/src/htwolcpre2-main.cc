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

#include "HfstTwolcDefs.h"
#include "io_src/InputReader.h"
#include "commandline_src/CommandLine.h"
#include "grammar_defs.h"

namespace hfst {
  namespace twolcpre2 {
    int parse();
    void set_input(std::istream & istr);
    void complete_alphabet(void);
    const HandyDeque<std::string> & get_total_alphabet_symbol_queue();
    const HandyDeque<std::string> & get_non_alphabet_symbol_queue();
    void set_warning_stream(std::ostream & ostr);
    void set_error_stream(std::ostream & ostr);
  }
}

int main(int argc, char * argv[])
{
#ifdef WINDOWS
  _setmode(0, _O_BINARY);
  _setmode(1, _O_BINARY);
#endif

  CommandLine command_line(argc,argv);
  if (command_line.help || command_line.usage || command_line.version)
    { exit(0); }
  hfst::twolcpre2::set_input(std::cin);
  hfst::twolcpre2::set_warning_stream(std::cerr);
  hfst::twolcpre2::set_error_stream(std::cerr);

  int exit_code = hfst::twolcpre2::parse();
  hfst::twolcpre2::complete_alphabet();
  std::cout << hfst::twolcpre2::get_total_alphabet_symbol_queue() << " ";
  std::cout << hfst::twolcpre2::get_non_alphabet_symbol_queue();
  return exit_code;
}
