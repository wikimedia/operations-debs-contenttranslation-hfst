// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#include "./transducer.h"

namespace hfst_ol {

// Define an operation for checking state equivalence for the
// purpose of detecting the same situation happening twice
bool TraversalState::operator==(const TraversalState & rhs) const
{
    if (this->index != rhs.index) {
        return false;
    }
    for (size_t i = 0; i < this->flags.size(); ++i) {
        if (this->flags[i] != rhs.flags[i]) {
            return false;
        }
    }
    return true;
}

bool TraversalState::operator<(const TraversalState & rhs) const
{
    if (this->index < rhs.index) {
        return true;
    }
    if (this->index > rhs.index) {
        return false;
    }
    for (size_t i = 0; i < this->flags.size(); ++i) {
        if (this->flags[i] < rhs.flags[i]) {
            return true;
        }
        if (this->flags[i] > rhs.flags[i]) {
            return false;
        }
    }
    return false;
}

void Transducer::find_loop_epsilon_transitions(
    unsigned int input_pos,
    TransitionTableIndex i)
{
    FlagDiacriticState flags = flag_state.get_values();
    while (true)
    {
        TransitionTableIndex target = tables->get_transition_target(i);
        TraversalState epsilon_reachable(target, flags);
        if (tables->get_transition_input(i) == 0) // epsilon
        {
            // We try to trap non-progressing loops
            if (traversal_states.count(epsilon_reachable) == 1) {
                // We've been here before
                throw true;
            }
            traversal_states.insert(epsilon_reachable);
            find_loop(input_pos, target);
            traversal_states.erase(epsilon_reachable);
            found_transition = true;
            ++i;
        } else if (alphabet->is_flag_diacritic(
                       tables->get_transition_input(i))) {
            
            if (flag_state.apply_operation(
                    *(alphabet->get_operation(
                          tables->get_transition_input(i))))) {
                // flag diacritic allowed
                if (traversal_states.count(epsilon_reachable) == 1) {
                    // We've been here before
                    throw true;
                }
                traversal_states.insert(epsilon_reachable);
                find_loop(input_pos, target);
                traversal_states.erase(epsilon_reachable);
            }
            flag_state.assign_values(flags);
            ++i;
        } else { // it's not epsilon and it's not a flag, so nothing to do
            return;
        }
    }
}

void Transducer::find_loop_epsilon_indices(unsigned int input_pos,
                                                TransitionTableIndex i)
{
    if (tables->get_index_input(i) == 0)
    {
        find_loop_epsilon_transitions(
            input_pos,
            tables->get_index_target(i) - TRANSITION_TARGET_TABLE_START);
        found_transition = true;
    }
}

void Transducer::find_loop_transitions(SymbolNumber input,
                                            unsigned int input_pos,
                                            TransitionTableIndex i)
{

    while (tables->get_transition_input(i) != NO_SYMBOL_NUMBER) {
        if (tables->get_transition_input(i) == input) {
            // We're not going to find an epsilon / flag loop
            traversal_states.clear();
            find_loop(input_pos, tables->get_transition_target(i));
            found_transition = true;
        } else {
            return;
        }
        ++i;
    }
}

void Transducer::find_loop_index(SymbolNumber input,
                                      unsigned int input_pos,
                                      TransitionTableIndex i)
{
    if (tables->get_index_input(i+input) == input)
    {
        find_loop_transitions(input,
                              input_pos,
                              tables->get_index_target(i+input) -
                              TRANSITION_TARGET_TABLE_START);
        found_transition = true;
    }
}




void Transducer::find_loop(unsigned int input_pos,
                           TransitionTableIndex i)
{
    found_transition = false;
    
    if (indexes_transition_table(i))
    {
        i -= TRANSITION_TARGET_TABLE_START;
        find_loop_epsilon_transitions(input_pos, i+1);
        
        // input-string ended.
        if (input_tape[input_pos] == NO_SYMBOL_NUMBER)
        {
            return;
        }
      
        SymbolNumber input = input_tape[input_pos];
        ++input_pos;

        find_loop_transitions(input, input_pos, i+1);
        if (alphabet->get_default_symbol() != NO_SYMBOL_NUMBER &&
            !found_transition) {
            find_loop_transitions(alphabet->get_default_symbol(),
                                  input_pos, i+1);
        }
    }
    else
    {
        find_loop_epsilon_indices(input_pos, i+1);
        
        if (input_tape[input_pos] == NO_SYMBOL_NUMBER)
        { // input-string ended.
            return;
        }
      
        SymbolNumber input = input_tape[input_pos];
        ++input_pos;

        find_loop_index(input, input_pos, i+1);
        // If we have a default symbol defined and we didn't find an index,
        // check for that
        if (alphabet->get_default_symbol() != NO_SYMBOL_NUMBER && !found_transition) {
            find_loop_index(alphabet->get_default_symbol(),
                            input_pos, i+1);
        }
    }
}


}
