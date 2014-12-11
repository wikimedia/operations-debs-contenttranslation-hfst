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

#include <cstring>
#include <cstdlib>
#include <sstream>
#include "transducer.h"
#include "lookup-path.h"
#include "lookup-state.h"
#include "tokenizer.h"
#include "formatter.h"


static LookupPath* create_initial_path(const ProcTransducer& t) { return new LookupPath(t, 0);}
static LookupPath* create_initial_path_fd(const ProcTransducer& t) { return new LookupPathFd(t, 0);}
static LookupPath* create_initial_path_weighted(const ProcTransducer& t) { return new LookupPathW(t, 0);}
static LookupPath* create_initial_path_weighted_fd(const ProcTransducer& t) { return new LookupPathWFd(t, 0);}

//////////Function definitions for ProcTransducer

InitialPathCreator ProcTransducer::initial_path_creators[2][2] =
    {{create_initial_path, create_initial_path_fd},
     {create_initial_path_weighted, create_initial_path_weighted_fd}};

ProcTransducer::ProcTransducer(std::istream& is): Transducer()
{
  header = new TransducerHeader(is);
  alphabet = new ProcTransducerAlphabet(is, header->symbol_count());
  load_tables(is);
  
  if (header->probe_flag(Has_unweighted_input_epsilon_cycles) ||
      header->probe_flag(Has_input_epsilon_cycles))
  {
    std::cerr << "!! Warning: transducer has epsilon cycles                  !!\n"
              << "!! This is currently not handled - if they are encountered !!\n"
              << "!! program *will* segfault.                                !!\n";
  }
  
  if(check_for_blank())
  {
    std::cerr << "!! Warning: transducer accepts input strings consisting of !!\n"
              << "!! just a blank. This is probably a bug in the transducer  !!\n"
              << "!! and will cause strange behavior.                        !!\n";
  }
}

bool
ProcTransducer::check_for_blank() const
{
  if(verboseFlag)
    std::cout << "Checking whether the transducer accepts a single blank as a word..." << std::endl;
  LookupState state(*this);
  state.step(get_alphabet().get_blank_symbol());
  return state.is_final();
}

bool
ProcTransducer::is_epsilon(const Transition& transition) const
{
  return transition.matches(0) || alphabet->is_flag_diacritic(transition.get_input_symbol());
}

LookupPath*
ProcTransducer::get_initial_path() const
{
  return (*initial_path_creators[header->probe_flag(Weighted)][alphabet->has_flag_diacritics()])(*this);
}

