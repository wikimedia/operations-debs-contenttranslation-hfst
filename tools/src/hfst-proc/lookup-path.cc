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

#include "lookup-path.h"

//////////Function definitions for class LookupPath

void
LookupPath::follow(const TransitionIndex& index)
{
  this->index = index.get_target();
  final = index.final();
  if(indexes_transition_index_table(this->index))
    final = transducer.get_index(this->index).final();
  else
    final = transducer.get_transition(this->index).final();
}

bool
LookupPath::follow(const Transition& transition)
{
  index = transition.get_target();
  if(indexes_transition_index_table(index))
    final = transducer.get_index(index).final();
  else
    final = transducer.get_transition(index).final();

  if(transducer.get_alphabet().symbol_to_string(transition.get_output_symbol()) != "")
    output_symbols.push_back(transition.get_output_symbol());

  return true;
}

bool
LookupPath::operator<(const LookupPath& o) const
{
  return output_symbols < o.output_symbols;
}


//////////Function definitions for class PathFd

bool
PathFd::evaluate_flag_diacritic(SymbolNumber s)
{
  return fd_state.apply_operation(s);
}


//////////Function definitions for class LookupPathFd

bool
LookupPathFd::follow(const Transition& transition)
{
  if(evaluate_flag_diacritic(transition.get_input_symbol()))
    return LookupPath::follow(transition);
  return false;
}


//////////Function definitions for class LookupPathW

void
LookupPathW::follow(const TransitionIndex& index)
{
  LookupPath::follow(index);
  if(indexes_transition_index_table(this->index))
    final_weight = static_cast<const TransitionWIndex&>(transducer.get_index(this->index)).final_weight();
  else
    final_weight = static_cast<const TransitionW&>(transducer.get_transition(this->index)).get_weight();
}

bool
LookupPathW::follow(const Transition& transition)
{
  weight += static_cast<const TransitionW&>(transition).get_weight();
  bool res = LookupPath::follow(transition);
  //**is this right? I'm not so sure about the precise semantics of weights
  //  and finals in this system**
  if(indexes_transition_index_table(index))
    final_weight = static_cast<const TransitionWIndex&>(transducer.get_index(index)).final_weight();
  else
    final_weight = static_cast<const TransitionW&>(transducer.get_transition(index)).get_weight();
  return res;
}

bool
LookupPathW::operator<(const LookupPathW& o) const
{
    if (get_weight() == o.get_weight()) {
	return this->LookupPath::operator<(o);
    } else {
	return get_weight() < o.get_weight();
    }
}


//////////Function definitions for class LookupPathWFd

bool
LookupPathWFd::follow(const Transition& transition)
{
  if(evaluate_flag_diacritic(transition.get_input_symbol()))
    return LookupPathW::follow(transition);
  return false;
}

