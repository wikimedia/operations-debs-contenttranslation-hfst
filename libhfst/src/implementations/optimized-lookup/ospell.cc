// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.
#include "transducer.h"

namespace hfst_ol {

int nByte_utf8(unsigned char c)
{
    /* utility function to determine how many bytes to peel off as
       a utf-8 character for representing as OTHER */
    if (c <= 127) {
        return 1;
    } else if ( (c & (128 + 64 + 32 + 16)) == (128 + 64 + 32 + 16) ) {
        return 4;
    } else if ( (c & (128 + 64 + 32 )) == (128 + 64 + 32) ) {
        return 3;
    } else if ( (c & (128 + 64 )) == (128 + 64)) {
        return 2;
    } else {
        return 0;
    }
}

bool InputString::initialize(const Encoder & encoder,
                             char * input,
                             SymbolNumber other)
{
    // Initialize the symbol vector to the tokenization given by encoder.
    // In the case of tokenization failure, valid utf-8 characters
    // are tokenized as "other" and tokenization is reattempted from
    // such a character onwards. The empty string is tokenized as an
    // empty vector; there is no end marker.
    
    s.clear();
    SymbolNumber k = NO_SYMBOL_NUMBER;
    char ** inpointer = &input;
    char * oldpointer;
    
    while (**inpointer != '\0') {
        oldpointer = *inpointer;
        k = const_cast<Encoder&>(encoder).find_key(inpointer);
        
        if (k == NO_SYMBOL_NUMBER) { // no tokenization from alphabet
            int n = nByte_utf8(static_cast<unsigned char>(*oldpointer));
            if (n == 0) {
                return false; // can't parse utf-8 character, admit failure
            } else {
                if (other == NO_SYMBOL_NUMBER) {
                    return false; // if we don't have an "other" symbol
                }
                oldpointer += n;
                *inpointer = oldpointer;
                s.push_back(other);
                continue;
            }
        } else {
            s.push_back(k);
        }
    }
    
    return true;
}

TreeNode TreeNode::update_lexicon(SymbolNumber next_symbol,
                                  TransitionTableIndex next_lexicon,
                                  Weight weight)
{
    SymbolNumberVector str(this->string);
    str.push_back(next_symbol);
    return TreeNode(str,
                    this->input_state,
                    this->mutator_state,
                    next_lexicon,
                    this->flag_state,
                    this->weight + weight);
}

TreeNode TreeNode::update_mutator(SymbolNumber next_symbol,
                                  TransitionTableIndex next_mutator,
                                  Weight weight)
{
    SymbolNumberVector str(this->string);
    str.push_back(next_symbol);
    return TreeNode(str,
                    this->input_state,
                    next_mutator,
                    this->lexicon_state,
                    this->flag_state,
                    this->weight + weight);
}

TreeNode TreeNode::update(SymbolNumber next_symbol,
                          unsigned int next_input,
                          TransitionTableIndex next_mutator,
                          TransitionTableIndex next_lexicon,
                          Weight weight)
{
    SymbolNumberVector str(this->string);
    str.push_back(next_symbol);
    return TreeNode(str,
                    next_input,
                    next_mutator,
                    next_lexicon,
                    this->flag_state,
                    this->weight + weight);
}

TreeNode TreeNode::update(SymbolNumber next_symbol,
                          TransitionTableIndex next_mutator,
                          TransitionTableIndex next_lexicon,
                          Weight weight)
{
    SymbolNumberVector str(this->string);
    str.push_back(next_symbol);
    return TreeNode(str,
                    this->input_state,
                    next_mutator,
                    next_lexicon,
                    this->flag_state,
                    this->weight + weight);
}

void Speller::lexicon_epsilons(void)
{
    if (!lexicon->has_epsilons_or_flags(queue.front().lexicon_state + 1)) {
        return;
    }
    TransitionTableIndex next = lexicon->next(queue.front().lexicon_state, 0);
    STransition i_s = lexicon->take_epsilons_and_flags(next);
    
    while (i_s.symbol != NO_SYMBOL_NUMBER) {
        if (lexicon->get_transition(next).get_input_symbol() == 0) {
            queue.push_back(queue.front().update_lexicon(i_s.symbol,
                                                         i_s.index,
                                                         i_s.weight));
        } else {
            TreeNode front = queue.front();
            if (front.flag_state.apply_operation(
                    lexicon->get_transition(next).get_input_symbol())) {
                queue.push_back(front.update_lexicon(i_s.symbol,
                                                     i_s.index,
                                                     i_s.weight));
            }
        }
        ++next;
        i_s = lexicon->take_epsilons_and_flags(next);
    }
}

void Speller::lexicon_consume(void)
{
    unsigned int input_state = queue.front().input_state;
    if (input_state >= input.len()||
        !lexicon->has_transitions(
            queue.front().lexicon_state + 1, input[input_state])) {
        return;
    }

    TransitionTableIndex next = lexicon->next(queue.front().lexicon_state,
                                              input[input_state]);
    STransition i_s = lexicon->take_non_epsilons(next,
                                                 input[input_state]);

    while (i_s.symbol != NO_SYMBOL_NUMBER) {
        queue.push_back(queue.front().update(
                            i_s.symbol,
                            input_state + 1,
                            queue.front().mutator_state,
                            i_s.index,
                            i_s.weight));
        
        ++next;
        i_s = lexicon->take_non_epsilons(next, input[input_state]);
    }
    
}

void Speller::mutator_epsilons(void)
{
    if (!mutator->has_transitions(queue.front().mutator_state + 1, 0)) {
        return;
    }
    TransitionTableIndex next_m = mutator->next(queue.front().mutator_state, 0);
    STransition mutator_i_s = mutator->take_epsilons(next_m);
   
    while (mutator_i_s.symbol != NO_SYMBOL_NUMBER) {
        if (mutator_i_s.symbol == 0) {
            queue.push_back(queue.front().update_mutator(mutator_i_s.symbol,
                                                         mutator_i_s.index,
                                                         mutator_i_s.weight));
        } else {
            if (!lexicon->has_transitions(
                    queue.front().lexicon_state + 1,
                    alphabet_translator[mutator_i_s.symbol])) {
                ++next_m;
                mutator_i_s = mutator->take_epsilons(next_m);
                continue;
            }
            TransitionTableIndex next_l = lexicon->next(
                queue.front().lexicon_state,
                alphabet_translator[mutator_i_s.symbol]);
            STransition lexicon_i_s = lexicon->take_non_epsilons(
                next_l,
                alphabet_translator[mutator_i_s.symbol]);
            
            while (lexicon_i_s.symbol != NO_SYMBOL_NUMBER) {
                queue.push_back(queue.front().update(
                                    lexicon_i_s.symbol,
                                    mutator_i_s.index,
                                    lexicon_i_s.index,
                                    lexicon_i_s.weight + mutator_i_s.weight));
                ++next_l;
                lexicon_i_s = lexicon->take_non_epsilons(
                    next_l,
                    alphabet_translator[mutator_i_s.symbol]);
            }
        }
        ++next_m;
        mutator_i_s = mutator->take_epsilons(next_m);
    }
}

void Speller::consume_input(void)
{
    unsigned int input_state = queue.front().input_state;
    if (input_state >= input.len()||
        !mutator->has_transitions(queue.front().mutator_state + 1,
                                  input[input_state])) {
        return; // not enough input to consume of no suitable transitions
    }
    
    TransitionTableIndex next_m = mutator->next(queue.front().mutator_state,
                                                input[input_state]);
    
    STransition mutator_i_s = mutator->take_non_epsilons(next_m,
                                                         input[input_state]);
    
    while (mutator_i_s.symbol != NO_SYMBOL_NUMBER) {

        if (mutator_i_s.symbol == 0) {
            
            queue.push_back(queue.front().update(0,
                                                 input_state + 1,
                                                 mutator_i_s.index,
                                                 queue.front().lexicon_state,
                                                 mutator_i_s.weight));
        } else {
            if (!lexicon->has_transitions(
                    queue.front().lexicon_state + 1,
                    alphabet_translator[mutator_i_s.symbol])) {
                ++next_m;
                mutator_i_s = mutator->take_non_epsilons(next_m,
                                                         input[input_state]);
                continue;
            }
            TransitionTableIndex next_l = lexicon->next(
                queue.front().lexicon_state,
                alphabet_translator[mutator_i_s.symbol]);
            
            STransition lexicon_i_s = lexicon->take_non_epsilons(
                next_l,
                alphabet_translator[mutator_i_s.symbol]);
            
            while (lexicon_i_s.symbol != NO_SYMBOL_NUMBER) {
                queue.push_back(
                    queue.front().update(lexicon_i_s.symbol,
                                         input_state + 1,
                                         mutator_i_s.index,
                                         lexicon_i_s.index,
                                         lexicon_i_s.weight + mutator_i_s.weight));
                ++next_l;
                lexicon_i_s = lexicon->take_non_epsilons(
                    next_l,
                    alphabet_translator[mutator_i_s.symbol]);
            }
        }
        ++next_m;
        mutator_i_s = mutator->take_non_epsilons(next_m,
                                                 input[input_state]);
    }
}


CorrectionQueue Speller::correct(char * line)
{
    // if input initialization fails, return empty correction queue
    if (!init_input(line, mutator->get_encoder(),
                    mutator->get_unknown_symbol())) {
        return CorrectionQueue();
    }
    std::map<std::string, Weight> corrections;
    TreeNode start_node(lexicon->get_fd_table());
    queue.assign(1, start_node);

    while (queue.size() > 0) {
        lexicon_epsilons();
        mutator_epsilons();
        if (queue.front().input_state == input.len()) {
            /* if our transducers are in final states
             * we generate the correction
             */
            if (mutator->final_index(queue.front().mutator_state)&&
                lexicon->final_index(queue.front().lexicon_state)) {
                std::string string = stringify(queue.front().string);
                Weight weight = queue.front().weight +
                    lexicon->final_weight(queue.front().lexicon_state) +
                    mutator->final_weight(queue.front().mutator_state);
                /* if the correction is novel or better than before, insert it
                 */
                if (corrections.count(string) == 0||
                    corrections[string] > weight) {
                    corrections[string] = weight;
                }
            }
        } else {
            consume_input();
        }
        queue.pop_front();
    }
    CorrectionQueue correction_queue;
    std::map<std::string, Weight>::iterator it;
    for (it = corrections.begin(); it != corrections.end(); ++it) {
        correction_queue.push(StringWeightPair(it->first, it->second));
    }
    return correction_queue;
}

bool Speller::check(char * line)
{
    if (!init_input(line, lexicon->get_encoder(), NO_SYMBOL_NUMBER)) {
        return false;
    }
    TreeNode start_node(lexicon->get_fd_table());
    queue.assign(1, start_node);

    while (queue.size() > 0) {
        if (queue.front().input_state == input.len()&&
            lexicon->final_index(queue.front().lexicon_state)) {
            return true;
        }
        lexicon_epsilons();
        lexicon_consume();
        queue.pop_front();
    }
    return false;
}

std::string Speller::stringify(SymbolNumberVector symbol_vector)
{
    std::string s;
    for (SymbolNumberVector::iterator it = symbol_vector.begin();
         it != symbol_vector.end(); ++it) {
        s.append(symbol_table[*it]);
    }
    return s;
}

bool Speller::init_input(char * str,
                         const Encoder & encoder,
                         SymbolNumber other)
{
    return input.initialize(encoder, str, other);
}

void Speller::build_alphabet_translator(void)
{
    const TransducerAlphabet & from = mutator->get_alphabet();
    const TransducerAlphabet & to = lexicon->get_alphabet();
    const SymbolTable & from_keys = from.get_symbol_table();
    StringSymbolMap to_symbols = to.build_string_symbol_map();
    alphabet_translator.push_back(0); // zeroth element is always epsilon
    for (SymbolNumber i = 1; i < from_keys.size(); ++i) {
            if ( (from.is_flag_diacritic(i)) || // if it's a flag
                 (i == from.get_unknown_symbol()) ) {   // or the OTHER symbol
                alphabet_translator.push_back(NO_SYMBOL_NUMBER);
                continue; // no translation
            }
            if (to_symbols.count(from_keys[i]) != 1) {
                std::string name(from_keys[i]);
                if (name != "") {
                    throw AlphabetTranslationException(
                        std::string(from_keys[i]));
                }
            }
            // translator at i points to lexicon's symbol for mutator's string for
            // mutator's symbol number i
            alphabet_translator.push_back(
                to_symbols[from_keys[i]]);
        }
}

} // namespace hfst_ol
