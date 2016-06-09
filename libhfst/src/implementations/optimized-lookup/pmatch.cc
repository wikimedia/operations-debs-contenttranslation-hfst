// Copyright (c) 2016 University of Helsinki                          
//                                                                    
// This library is free software; you can redistribute it and/or      
// modify it under the terms of the GNU Lesser General Public         
// License as published by the Free Software Foundation; either       
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more      
// information.
#include "pmatch.h"
#include "hfst.h"

namespace hfst_ol {

PmatchAlphabet::PmatchAlphabet(std::istream & inputstream,
                               SymbolNumber symbol_count):
    TransducerAlphabet(inputstream, symbol_count, false),
    special_symbols(SPECIALSYMBOL_NR_ITEMS, NO_SYMBOL_NUMBER) // SpecialSymbols enum
{
    symbol2lists = SymbolNumberVector(orig_symbol_count, NO_SYMBOL_NUMBER);
    list2symbols = SymbolNumberVector(orig_symbol_count, NO_SYMBOL_NUMBER);
    rtns = RtnVector(orig_symbol_count, NULL);
    // We initialize the vector of which symbols have a printable representation
    // with false, then flip those that actually do to true
    printable_vector = std::vector<bool>(orig_symbol_count, false);
    for (SymbolNumber i = 1; i < symbol_table.size(); ++i) {
        add_special_symbol(symbol_table[i], i);
        if (is_flag_diacritic(i)) {
            printable_vector[i] = false;
        }
    }
}

PmatchAlphabet::PmatchAlphabet(TransducerAlphabet const & a):
    TransducerAlphabet(a),
    special_symbols(SPECIALSYMBOL_NR_ITEMS, NO_SYMBOL_NUMBER) {
    symbol2lists = SymbolNumberVector(orig_symbol_count, NO_SYMBOL_NUMBER);
    list2symbols = SymbolNumberVector(orig_symbol_count, NO_SYMBOL_NUMBER);
    rtns = RtnVector(orig_symbol_count, NULL);
    // We initialize the vector of which symbols have a printable representation
    // with false, then flip those that actually do to true
    printable_vector = std::vector<bool>(orig_symbol_count, false);
    for (SymbolNumber i = 1; i < symbol_table.size(); ++i) {
        add_special_symbol(symbol_table[i], i);
        if (is_flag_diacritic(i)) {
            printable_vector[i] = false;
        }
    }
}

PmatchAlphabet::PmatchAlphabet(void):
    TransducerAlphabet()
{}

void PmatchAlphabet::add_symbol(const std::string & symbol)
{
    symbol2lists.push_back(NO_SYMBOL_NUMBER);
    list2symbols.push_back(NO_SYMBOL_NUMBER);
    rtns.push_back(NULL);
    printable_vector.push_back(true);
    if (exclusionary_lists.size() != 0) {
        // if there are exclusionary lists, they should all accept the new symbol
        symbol2lists[symbol_table.size()] = symbol_lists.size();
        symbol_lists.push_back(SymbolNumberVector(exclusionary_lists.begin(),
                                                  exclusionary_lists.end()));
#ifndef _MSC_VER
        for(const auto & exc: exclusionary_lists) {
          symbol_list_members[list2symbols[exc]].push_back(symbol_table.size());
        }
#else
        for (SymbolNumberVector::const_iterator exc = exclusionary_lists.begin(); exc != exclusionary_lists.end(); exc++) {
          symbol_list_members[list2symbols[*exc]].push_back(symbol_table.size());
        }
#endif
    }
    TransducerAlphabet::add_symbol(symbol);
}

bool PmatchAlphabet::is_printable(SymbolNumber symbol)
{
    return symbol < printable_vector.size() && printable_vector[symbol];
}

void PmatchAlphabet::add_special_symbol(const std::string & str,
                                         SymbolNumber symbol_number)
{
    if (str == "@PMATCH_ENTRY@") {
        special_symbols[entry] = symbol_number;
    } else if (str == "@PMATCH_EXIT@") {
        special_symbols[exit] = symbol_number;
    } else if (str == "@PMATCH_LC_ENTRY@") {
        special_symbols[LC_entry] = symbol_number;
    } else if (str == "@PMATCH_RC_ENTRY@") {
        special_symbols[RC_entry] = symbol_number;
    } else if (str == "@PMATCH_LC_EXIT@") {
        special_symbols[LC_exit] = symbol_number;
    } else if (str == "@PMATCH_RC_EXIT@") {
        special_symbols[RC_exit] = symbol_number;
    } else if (str == "@PMATCH_NLC_ENTRY@") {
        special_symbols[NLC_entry] = symbol_number;
    } else if (str == "@PMATCH_NRC_ENTRY@") {
        special_symbols[NRC_entry] = symbol_number;
    } else if (str == "@PMATCH_NLC_EXIT@") {
        special_symbols[NLC_exit] = symbol_number;
    } else if (str == "@PMATCH_NRC_EXIT@") {
        special_symbols[NRC_exit] = symbol_number;
    } else if (str == "@PMATCH_PASSTHROUGH@") {
        special_symbols[Pmatch_passthrough] = symbol_number;
    } else if (str == "@PMATCH_INPUT_MARK@") {
        special_symbols[Pmatch_input_mark] = symbol_number;
    } else if (str == "@BOUNDARY@") {
        special_symbols[boundary] = symbol_number;
    } else if (is_end_tag(str)) {
        // Fetch the part between @PMATCH_ENDTAG_ and @
        end_tag_map[symbol_number] = str.substr(
            sizeof("@PMATCH_ENDTAG_") - 1,
            str.size() - (sizeof("@PMATCH_ENDTAG_@") - 1));
    } else if (is_insertion(str)) {
        rtn_names[name_from_insertion(str)] = symbol_number;
    } else if (is_guard(str)) {
        guards.push_back(symbol_number);
    } else if (is_list(str)) {
        process_symbol_list(str, symbol_number);
    } else if (is_counter(str)) {
        process_counter(str, symbol_number);
    } else {
        // it's a regular symbol
        printable_vector[symbol_number] = true;
    }
}

void PmatchAlphabet::process_symbol_list(std::string str, SymbolNumber sym)
{
    SymbolNumberVector list_symbols;
    StringSymbolMap ss = build_string_symbol_map();
    // regular list or exlusionary list?
    bool polarity = str[1] == 'L';
    size_t begin = strlen("@L.");
    size_t stop;
    std::vector<std::string> collected_symbols;
    while ((stop = str.find('_', begin)) != std::string::npos) {
// For each underscore after the prelude, grab the substring
        std::string symbol = str.substr(begin, stop - begin);
        if (symbol.size() == 0) {
// If the symbol _is_ an underscore it looks like we got an empty string
            symbol = "_";
            begin = stop + 2;
        } else {
            begin = stop + 1;
        }
        collected_symbols.push_back(symbol);
    }
    // Process the symbols we found
    for (std::vector<std::string>::const_iterator it = collected_symbols.begin();
         it != collected_symbols.end(); ++it) {
        SymbolNumber str_sym;
        if (ss.count(*it) == 0) {
// This symbol isn't mentioned elsewhere in the alphabet
            add_symbol(*it);
            str_sym = orig_symbol_count;
            ++orig_symbol_count;
        } else {
            str_sym = ss[*it];
        }
        list_symbols.push_back(str_sym);
        if (polarity == true) {
            if (symbol2lists[str_sym] == NO_SYMBOL_NUMBER) {
                symbol2lists[str_sym] = symbol_lists.size();
                symbol_lists.push_back(SymbolNumberVector(1, sym));
            } else {
                symbol_lists[symbol2lists[str_sym]].push_back(sym);
            }
        }
    }
    list2symbols[sym] = symbol_list_members.size();
    if (polarity == false) {
        SymbolNumberVector excl_symbols;
        exclusionary_lists.push_back(sym);
        for (SymbolNumber candidate_for_list = 1; candidate_for_list < symbol_table.size(); ++candidate_for_list) {
            if (is_printable(symbol_table[candidate_for_list]) &&
                find(list_symbols.begin(), list_symbols.end(), candidate_for_list) == list_symbols.end()) {
                excl_symbols.push_back(candidate_for_list);
                if (symbol2lists[candidate_for_list] == NO_SYMBOL_NUMBER) {
                    symbol2lists[candidate_for_list] = symbol_lists.size();
                    symbol_lists.push_back(SymbolNumberVector(1, sym));
                } else {
                    symbol_lists[symbol2lists[sym]].push_back(sym);
                }
            }
        }
        symbol_list_members.push_back(excl_symbols);
    } else {
        symbol_list_members.push_back(list_symbols);
    }
}

SymbolNumberVector PmatchAlphabet::get_specials(void) const
{
    SymbolNumberVector v;
    for (SymbolNumberVector::const_iterator it =
             special_symbols.begin(); it != special_symbols.end(); ++it) {
        if (*it != NO_SYMBOL_NUMBER) {
            v.push_back(*it);
        }
    }
    return v;
}

void PmatchAlphabet::process_counter(std::string str, SymbolNumber sym)
{
    // Fill up non-counter spots in the counter vector with blanks
    while (counters.size() < sym) {
        counters.push_back(NO_COUNTER);
    }
    counters.push_back(0);
}

void PmatchAlphabet::count(SymbolNumber sym)
{
    if (is_counter(sym)) {
        counters[sym]++;
    }
}

PmatchContainer::PmatchContainer(std::istream & inputstream):
    verbose(false),
    locate_mode(false),
    profile_mode(false),
    single_codepoint_tokenization(false),
    recursion_depth_left(PMATCH_MAX_RECURSION_DEPTH),
    entry_stack()
{
    std::string transducer_name;
    transducer_name = parse_name_from_hfst3_header(inputstream);
    // the first transducer should be called eg. "TOP", this could be tested
    // for once more established

    TransducerHeader header(inputstream);
    alphabet = PmatchAlphabet(inputstream, header.symbol_count());
    orig_symbol_count = symbol_count = alphabet.get_orig_symbol_count();
    alphabet.extract_tags = locate_mode;
    line_number = 0;
    encoder = new Encoder(alphabet.get_symbol_table(), orig_symbol_count);
    toplevel = new hfst_ol::PmatchTransducer(
        inputstream,
        header.index_table_size(),
        header.target_table_size(),
        alphabet,
        this);
    while (inputstream.good()) {
        try {
            transducer_name = parse_name_from_hfst3_header(inputstream);
        } catch (TransducerHeaderException & e) {
            break;
        }
        header = TransducerHeader(inputstream);
        TransducerAlphabet dummy = TransducerAlphabet(
            inputstream, header.symbol_count());
        hfst_ol::PmatchTransducer * rtn =
            new hfst_ol::PmatchTransducer(inputstream,
                                          header.index_table_size(),
                                          header.target_table_size(),
                                          alphabet,
                                          this);
        if (!alphabet.has_rtn(transducer_name)) {
            alphabet.add_rtn(rtn, transducer_name);
        } else {
            delete rtn;
        }
    }
    
    toplevel->collect_possible_first_symbols();

    // Finally fetch the first symbols from any
    // first-position rtn arcs in TOP. If they are potential epsilon loops,
    // clear out the set.
    SymbolNumber max_input_sym = 0;
    std::set<SymbolNumber> & possible_firsts = toplevel->possible_first_symbols;
    for (std::set<SymbolNumber>::iterator it = possible_firsts.begin();
         it != possible_firsts.end(); ++it) {
        if (*it > max_input_sym) { max_input_sym = *it; }
        if (alphabet.has_rtn(*it)) {
            if (alphabet.get_rtn(*it) == toplevel) {
                possible_firsts.clear();
                break;
            }
            alphabet.get_rtn(*it)->collect_possible_first_symbols();
            std::set<SymbolNumber> rtn_firsts =
                alphabet.get_rtn(*it)->possible_first_symbols;
            for (RtnNameMap::const_iterator it = alphabet.rtn_names.begin();
                 it != alphabet.rtn_names.end(); ++it) {
                if (rtn_firsts.count(it->second) == 1) {
                    // For now we are very conservative:
                    // if we can go through two levels of rtns
                    // without any input, we just assume the full
                    // input set is possible
                    possible_firsts.clear();
                }
            }
            if (rtn_firsts.empty() || possible_firsts.empty()) {
                possible_firsts.clear();
                break;
            } else {
                for (std::set<SymbolNumber>::
                         const_iterator rtn_it = rtn_firsts.begin();
                     rtn_it != rtn_firsts.end(); ++rtn_it) {
                    if (*rtn_it > max_input_sym) { max_input_sym = *rtn_it ;}
                    possible_firsts.insert(*rtn_it);
                }
            }
        }
    }
    for (RtnNameMap::const_iterator it = alphabet.rtn_names.begin();
         it != alphabet.rtn_names.end(); ++it) {
        possible_firsts.erase(it->second);
    }
    if (!possible_firsts.empty() &&
        alphabet.get_special(boundary) != NO_SYMBOL_NUMBER) {
        possible_firsts.insert(alphabet.get_special(boundary));
    }
    if (!possible_firsts.empty()) {
        for (int i = 0; i <= max_input_sym; ++i) {
            if (possible_firsts.count(i) == 1) {
                possible_first_symbols.push_back(1);
            } else {
                possible_first_symbols.push_back(0);
            }
        }
    }
    
}

PmatchContainer::PmatchContainer(Transducer * t):
    verbose(false),
    locate_mode(false),
    profile_mode(false),
    single_codepoint_tokenization(false),
    recursion_depth_left(PMATCH_MAX_RECURSION_DEPTH),
    entry_stack()
{
    TransducerHeader header = t->get_header();
    alphabet = PmatchAlphabet(t->get_alphabet());
    orig_symbol_count = symbol_count = alphabet.get_orig_symbol_count();
    alphabet.extract_tags = locate_mode;
    line_number = 0;
    encoder = new Encoder(alphabet.get_symbol_table(), orig_symbol_count);
    TransducerTable<TransitionW> transitions = t->copy_transitionw_table();
    TransducerTable<TransitionWIndex> indices = t->copy_windex_table();
    toplevel = new hfst_ol::PmatchTransducer(
        transitions.get_vector(),
        indices.get_vector(),
        alphabet,
        this);
    toplevel->collect_possible_first_symbols();

    // Finally fetch the first symbols from any
    // first-position rtn arcs in TOP. If they are potential epsilon loops,
    // clear out the set.
    SymbolNumber max_input_sym = 0;
    std::set<SymbolNumber> & possible_firsts = toplevel->possible_first_symbols;
    for (std::set<SymbolNumber>::iterator it = possible_firsts.begin();
         it != possible_firsts.end(); ++it) {
        if (*it > max_input_sym) { max_input_sym = *it; }
        if (alphabet.has_rtn(*it)) {
            if (alphabet.get_rtn(*it) == toplevel) {
                possible_firsts.clear();
                break;
            }
            alphabet.get_rtn(*it)->collect_possible_first_symbols();
            std::set<SymbolNumber> rtn_firsts =
                alphabet.get_rtn(*it)->possible_first_symbols;
            for (RtnNameMap::const_iterator it = alphabet.rtn_names.begin();
                 it != alphabet.rtn_names.end(); ++it) {
                if (rtn_firsts.count(it->second) == 1) {
                    // For now we are very conservative:
                    // if we can go through two levels of rtns
                    // without any input, we just assume the full
                    // input set is possible
                    possible_firsts.clear();
                }
            }
            if (rtn_firsts.empty() || possible_firsts.empty()) {
                possible_firsts.clear();
                break;
            } else {
                for (std::set<SymbolNumber>::
                         const_iterator rtn_it = rtn_firsts.begin();
                     rtn_it != rtn_firsts.end(); ++rtn_it) {
                    if (*rtn_it > max_input_sym) { max_input_sym = *rtn_it ;}
                    possible_firsts.insert(*rtn_it);
                }
            }
        }
    }
    for (RtnNameMap::const_iterator it = alphabet.rtn_names.begin();
         it != alphabet.rtn_names.end(); ++it) {
        possible_firsts.erase(it->second);
    }
    if (!possible_firsts.empty() &&
        alphabet.get_special(boundary) != NO_SYMBOL_NUMBER) {
        possible_firsts.insert(alphabet.get_special(boundary));
    }
    if (!possible_firsts.empty()) {
        for (int i = 0; i <= max_input_sym; ++i) {
            if (possible_firsts.count(i) == 1) {
                possible_first_symbols.push_back(1);
            } else {
                possible_first_symbols.push_back(0);
            }
        }
    }
}

void PmatchContainer::add_rtn(Transducer * rtn, const std::string & name)
{
    TransducerTable<TransitionW> transitions = rtn->copy_transitionw_table();
    TransducerTable<TransitionWIndex> indices = rtn->copy_windex_table();
    PmatchTransducer * pmatch_rtn = new hfst_ol::PmatchTransducer(
        transitions.get_vector(),
        indices.get_vector(),
        alphabet,
        this);
    if (!alphabet.has_rtn(name)) {
        alphabet.add_rtn(pmatch_rtn, name);
    } else {
        delete rtn;
    }
}

PmatchContainer::PmatchContainer(void)
{
    // Not used, but apparently needed by swig to construct these
}

bool PmatchAlphabet::is_end_tag(const std::string & symbol)
{
    return symbol.find("@PMATCH_ENDTAG_") == 0 &&
        symbol.rfind("@") == symbol.size() - 1;
}

bool PmatchAlphabet::is_end_tag(const SymbolNumber symbol) const
{
    return end_tag_map.count(symbol) == 1;
}

bool PmatchAlphabet::is_insertion(const std::string & symbol)
{
    return symbol.find("@I.") == 0 && symbol.rfind("@") == symbol.size() - 1;
}

bool PmatchAlphabet::is_guard(const std::string & symbol)
{
    return symbol.find("@PMATCH_GUARD_") == 0 && symbol.rfind("@") == symbol.size() - 1;
}

bool PmatchAlphabet::is_counter(const std::string & symbol)
{
    return symbol.find("@PMATCH_COUNTER_") == 0 && symbol.rfind("@") == symbol.size() - 1;
}

bool PmatchAlphabet::is_list(const std::string & symbol)
{
    return (symbol.find("@L.") == 0 || symbol.find("@X.") == 0) && symbol.rfind("@") == symbol.size() - 1;
}

bool PmatchAlphabet::is_special(const std::string & symbol)
{
    if (symbol.size() == 0) {
        return false;
    }
    if (is_insertion(symbol) || symbol == "@BOUNDARY@") {
//        || symbol == "@_UNKNOWN_SYMBOL_@" || symbol == "@_IDENTITY_SYMBOL_@"
        return true;
    } else {
        return symbol.find("@PMATCH") == 0 && symbol.at(symbol.size() - 1) == '@';
    }
}

bool PmatchAlphabet::is_printable(const std::string & symbol)
{
    if (symbol.size() < 3) {
        return true;
    }
    return symbol.find("@") != 0 || symbol.at(symbol.size() - 1) != '@';
}

bool PmatchAlphabet::is_guard(const SymbolNumber symbol) const
{
    for(SymbolNumberVector::const_iterator it = guards.begin();
        it != guards.end(); ++it) {
        if(symbol == *it) {
            return true;
        }
    }
    return false;
}

bool PmatchAlphabet::is_counter(const SymbolNumber symbol) const
{
    return (symbol < counters.size() && counters[symbol] != NO_COUNTER);
}

bool PmatchAlphabet::is_input_mark(const SymbolNumber symbol) const
{
    return get_special(Pmatch_input_mark) == symbol;
}

std::string PmatchAlphabet::name_from_insertion(const std::string & symbol)
{
    return symbol.substr(sizeof("@I.") - 1, symbol.size() - (sizeof("@I.@") - 1));
}

std::string PmatchAlphabet::end_tag(const SymbolNumber symbol)
{
    if (end_tag_map.count(symbol) == 0) {
        return "";
    } else {
        return "</" + end_tag_map[symbol] + ">";
    }
}

std::string PmatchAlphabet::start_tag(const SymbolNumber symbol)
{
    if (end_tag_map.count(symbol) == 0) {
        return "";
    } else {
        return "<" + end_tag_map[symbol] + ">";
    }
    
}

PmatchContainer::~PmatchContainer(void)
{
    delete encoder;
    delete toplevel;
}

PmatchAlphabet::~PmatchAlphabet(void)
{
    for (RtnVector::iterator it = rtns.begin();
         it != rtns.end(); ++it) {
        delete *it;
        *it = NULL;
    }

}

std::string PmatchContainer::parse_name_from_hfst3_header(std::istream & f)
{
    const char* header1 = "HFST";
    unsigned int header_loc = 0; // how much of the header has been found
    int c;
    for(header_loc = 0; header_loc < strlen(header1) + 1; header_loc++)
    {
        c = f.get();
        if(c != header1[header_loc]) {
            break;
        }
    }
    if(header_loc == strlen(header1) + 1)
    {
        unsigned short remaining_header_len;
        f.read((char*) &remaining_header_len, sizeof(remaining_header_len));
        if (f.get() != '\0') {
            HFST_THROW(TransducerHeaderException);
        }
        char * headervalue = new char[remaining_header_len];
        f.read(headervalue, remaining_header_len);
        if (headervalue[remaining_header_len - 1] != '\0') {
            HFST_THROW(TransducerHeaderException);
        }
        char * type = new char [remaining_header_len];
        bool type_defined = false;
        char * name = new char [remaining_header_len];
        bool name_defined = false;
        int i = 0;
        while (i < remaining_header_len) {
            if (!type_defined && strstr(headervalue + i, "type")) {
                strcpy(type, headervalue + i + strlen("type") + 1);
                type_defined = true;
            } else if (!name_defined && strstr(headervalue + i, "name")) {
                strcpy(name, headervalue + i + strlen("name") + 1);
                name_defined = true;
            }
            while (i < remaining_header_len &&
                   headervalue[i] != '\0') {
                ++i;
            }
            ++i;
        }
        delete[] headervalue;
        if (strcmp(type, "HFST_OL") == 0) {
            std::cerr << "\nThis version of pmatch uses weighted rulesets only, please recompile your rules\n\n";
            HFST_THROW_MESSAGE(TransducerHeaderException,
                               "This version of pmatch uses weighted rulesets only, please recompile your rules\n");
        }
        if (strcmp(type, "HFST_OLW") != 0) {
            HFST_THROW(TransducerHeaderException);
        }
        std::string retval = std::string(name);
        delete [] type;
        delete [] name;
        return retval;
    } else // nope. put back what we've taken
    {
        f.unget(); // first the non-matching character
        for(int i = header_loc - 1; i>=0; i--) {
            // then the characters that did match (if any)
            f.unget();
        }
        HFST_THROW(TransducerHeaderException);
    }
}

void PmatchAlphabet::add_rtn(PmatchTransducer * rtn, std::string const & name)
{
    SymbolNumber symbol = rtn_names[name];
    rtns[symbol] = rtn;
}

bool PmatchAlphabet::has_rtn(std::string const & name) const
{
    return rtn_names.at(name) < rtns.size() && rtns[rtn_names.at(name)] != NULL;
}

bool PmatchAlphabet::has_rtn(SymbolNumber symbol) const
{
    return symbol < rtns.size() && rtns[symbol] != NULL;
}

PmatchTransducer * PmatchAlphabet::get_rtn(SymbolNumber symbol)
{
    return rtns[symbol];
}

std::string PmatchAlphabet::get_counter_name(SymbolNumber symbol)
{
    if (symbol_table.size() <= symbol) {
        return "INVALID_COUNTER";
    }
    std::string name = symbol_table[symbol];
    if (!is_counter(name)) {
        return "INVALID_COUNTER";
    }
    return name.substr(strlen("@PMATCH_COUNTER_"),
                       name.size() - strlen("@PMATCH_COUNTER_") - 1);
}

SymbolNumber PmatchAlphabet::get_special(SpecialSymbol special) const
{
    return special_symbols.at(special);
}

void PmatchContainer::process(const std::string & input_str)
{
    initialize_input(input_str.c_str());
    unsigned int input_pos = 0;
    unsigned int printable_input_pos = 0;

    ++line_number;
    output.clear();
    locations.clear();
    DoubleTape nonmatching_locations;
    while (has_queued_input(input_pos)) {
        SymbolNumber current_input = input[input_pos];
        if (not_possible_first_symbol(current_input)) {
            copy_to_output(current_input, current_input);
            ++input_pos;
            if (locate_mode && alphabet.is_printable(current_input)) {
                ++printable_input_pos;
                nonmatching_locations.push_back(
                    SymbolPair(current_input, current_input));
            }
            continue;
        }
        tape.clear();
        unsigned int tape_pos = 0;
        unsigned int old_input_pos = input_pos;
        toplevel->match(input_pos, tape_pos);
        if (tape_pos > 0) {
            // Tape moved
            if (locate_mode) {
                if (!nonmatching_locations.empty()) {
                    LocationVector ls;
                    Location nonmatching = alphabet.locatefy(printable_input_pos - nonmatching_locations.size(),
                                                             WeightedDoubleTape(nonmatching_locations, 0.0));
                    nonmatching.output = "@_NONMATCHING_@";
                    ls.push_back(nonmatching);
                    locations.push_back(ls);
                    nonmatching_locations.clear();
                }
                LocationVector ls;
                for (WeightedDoubleTapeVector::iterator it = (toplevel->locations)->begin();
                     it != (toplevel->locations)->end(); ++it) {
                    ls.push_back(alphabet.locatefy(printable_input_pos,
                                                          *it));
                }
                sort(ls.begin(), ls.end());
                locations.push_back(ls);
                printable_input_pos += (input_pos - old_input_pos);
            } else {
                copy_to_output(toplevel->get_best_result());
            }
        }
        if (tape_pos == 0 || input_pos == old_input_pos) {
            // If nothing happened, we move one position up
            copy_to_output(current_input, current_input);
            ++input_pos;
            if (locate_mode && alphabet.is_printable(current_input)) {
                ++printable_input_pos;
                nonmatching_locations.push_back(SymbolPair(current_input, current_input));
            }
        }
    }
    if (locate_mode && !nonmatching_locations.empty()) {
        LocationVector ls;
        Location nonmatching = alphabet.locatefy(printable_input_pos - nonmatching_locations.size(),
                                                 WeightedDoubleTape(nonmatching_locations, 0.0));
        nonmatching.output = "@_NONMATCHING_@";
        ls.push_back(nonmatching);
        locations.push_back(ls);
    }
}

std::string PmatchContainer::match(const std::string & input,
                                   double time_cutoff)
{
    max_time = time_cutoff;
    if (max_time > 0.0) {
        start_clock = clock();
        call_counter = 0;
        limit_reached = false;
    }
    locate_mode = false;
    process(input);
    return stringify_output();
}

LocationVectorVector PmatchContainer::locate(std::string & input,
                                             double time_cutoff)
{
    max_time = time_cutoff;
    if (max_time > 0.0) {
        start_clock = clock();
        call_counter = 0;
        limit_reached = false;
    }
    locate_mode = true;
    process(input);
    return locations;
}

// A utility comparing function for get_profiling_info
bool counter_comp(std::pair<std::string, unsigned long> l,
                  std::pair<std::string, unsigned long> r)
{
    // Descending order
    return l.second > r.second;
}

std::string PmatchContainer::get_profiling_info(void)
{
    std::stringstream retval;
    size_t max_name_len = 0;
    retval << "Profiling information:\n";
    retval << "  Traversals of Counter() positions:\n";
    std::vector<std::pair<std::string, unsigned long> > counter_name_val_pairs;
    for(SymbolNumber i = 0; i < alphabet.counters.size(); ++i) {
        if (alphabet.counters[i] != NO_COUNTER) {
            std::string counter_name = alphabet.get_counter_name(i);
            if (counter_name.size() > max_name_len) {
                max_name_len = counter_name.size();
            }
            counter_name_val_pairs.push_back(
                std::pair<std::string, unsigned long>(counter_name,
                                                      alphabet.counters[i]));
        }
    }
    std::sort(counter_name_val_pairs.begin(), counter_name_val_pairs.end(),
              counter_comp);
    for(std::vector<std::pair<std::string, unsigned long> >::const_iterator it =
            counter_name_val_pairs.begin(); it != counter_name_val_pairs.end(); ++it) {
        retval << "    " << it->first;
        size_t spacing_counter = max_name_len + 8 - it->first.size();
        while (spacing_counter) {
            retval << " ";
            --spacing_counter;
        }
        retval << it->second << "\n";
    }
    return retval.str();
}

void PmatchContainer::copy_to_output(const DoubleTape & best_result)
{
    for (DoubleTape::const_iterator it = best_result.begin();
         it != best_result.end(); ++it) {
        output.push_back(*it);
    }
}

void PmatchContainer::copy_to_output(SymbolNumber input_sym, SymbolNumber output_sym)
{
    output.push_back(SymbolPair(input_sym, output_sym));
}

std::string PmatchContainer::stringify_output(void)
{
    return alphabet.stringify(output);
}

//LocationVector PmatchContainer::locatefy_output(void)
//{
//    return alphabet.locatefy(output);
//}

std::string PmatchAlphabet::stringify(const DoubleTape & str)
{
    std::string retval;
    std::stack<unsigned int> start_tag_pos;
    for (DoubleTape::const_iterator it = str.begin();
         it != str.end(); ++it) {
        SymbolNumber output = it->output;
        if (output == special_symbols[entry]) {
            start_tag_pos.push(retval.size());
        } else if (output == special_symbols[exit]) {
            if (start_tag_pos.size() != 0) {
                start_tag_pos.pop();
            }
        } else if (is_end_tag(output)) {
            unsigned int pos;
            if (start_tag_pos.size() == 0) {
                std::cerr << "Warning: end tag without start tag\n";
                pos = 0;
            } else {
                pos = start_tag_pos.top();
            }
            retval.insert(pos, start_tag(output));
            retval.append(end_tag(output));
        } else {
            if ((!extract_tags || start_tag_pos.size() != 0)
                && is_printable(output)) {
                retval.append(string_from_symbol(output));
            }
        }
    }
    return retval;
}

Location PmatchAlphabet::locatefy(unsigned int input_offset,
                                  const WeightedDoubleTape & str)
{
    Location retval;
    retval.start = input_offset;
    retval.weight = str.weight;
    size_t input_mark = 0;
    size_t output_mark = 0;

    // We rebuild the original input without special
    // symbols but with IDENTITIES etc. replaced
    for (DoubleTape::const_iterator it = str.begin();
         it != str.end(); ++it) {
        SymbolNumber input = it->input;
        SymbolNumber output = it->output;
        if (is_end_tag(output)) {
            retval.tag = start_tag(output);
            continue;
        }
        if (is_printable(output)) {
            retval.output.append(string_from_symbol(output));
        }
        if (is_printable(input)) {
            retval.input.append(string_from_symbol(input));
            ++input_offset;
        }
        if (is_input_mark(output)) {
            retval.output_parts.push_back(output_mark);
            retval.input_parts.push_back(input_mark);
            output_mark = retval.output.size();
            input_mark = retval.input.size();
        }
    }
    if (output_mark > 0) {
        retval.output_parts.push_back(output_mark);
    }
    if (input_mark > 0) {
        retval.input_parts.push_back(input_mark);
    }
    retval.length = input_offset - retval.start;
    return retval;
}

bool PmatchContainer::has_unsatisfied_rtns(void) const
{
    return false;
}

std::string PmatchContainer::get_unsatisfied_rtn_name(void) const
{
    return "";
}

bool PmatchContainer::has_queued_input(unsigned int input_pos)
{
    return input_pos < input.size();
}

PmatchTransducer::PmatchTransducer(std::istream & is,
                                   TransitionTableIndex index_table_size,
                                   TransitionTableIndex transition_table_size,
                                   PmatchAlphabet & alpha,
                                   PmatchContainer * cont):
    alphabet(alpha),
    container(cont),
    locations(NULL)
{
    orig_symbol_count = alphabet.get_symbol_table().size();
    // initialize the stack for local variables
    LocalVariables locals_front;
    locals_front.flag_state = alphabet.get_fd_table();
    locals_front.tape_step = 1;
    locals_front.context = none;
    locals_front.context_placeholder = 0;
    locals_front.default_symbol_trap = false;
    locals_front.negative_context_success = false;
    locals_front.pending_passthrough = false;
    locals_front.running_weight = 0.0;
    local_stack.push(locals_front);
    RtnVariables rtn_front;
    rtn_front.tape_entry = 0;
    rtn_front.input_tape_entry = 0;
    rtn_front.candidate_input_pos = 0;
    rtn_front.candidate_tape_pos = 0;
    rtn_stack.push(rtn_front);


    // Allocate and read tables
    char * indextab = (char*) malloc(TransitionWIndex::size * index_table_size);
    char * transitiontab = (char*) malloc(TransitionW::size * transition_table_size);
    is.read(indextab, TransitionWIndex::size * index_table_size);
    is.read(transitiontab, TransitionW::size * transition_table_size);
    char * orig_p = indextab;
    index_table.reserve(index_table_size);
    while(index_table_size) {
        // index_table.push_back(
        //     SimpleIndex(*(SymbolNumber *) indextab,
        //                 *(TransitionTableIndex *) (indextab + sizeof(SymbolNumber))));
        // --index_table_size;
        index_table.push_back(TransitionWIndex(indextab));
        --index_table_size;
        indextab += TransitionWIndex::size;
    }
    free(orig_p);
    orig_p = transitiontab;
    transition_table.reserve(transition_table_size);
    while(transition_table_size) {
        transition_table.push_back(TransitionW(transitiontab));
            // SimpleTransition(*(SymbolNumber *) transitiontab,
            //                  *(SymbolNumber *) (transitiontab + sizeof(SymbolNumber)),
            //                  *(TransitionTableIndex *) (transitiontab + 2*sizeof(SymbolNumber))));
        --transition_table_size;
        transitiontab += TransitionW::size;
    }
    free(orig_p);
}

PmatchTransducer::PmatchTransducer(std::vector<TransitionW> transition_vector,
                                   std::vector<TransitionWIndex> index_vector,
                                   PmatchAlphabet & alpha,
                                   PmatchContainer * cont):
    alphabet(alpha),
    container(cont),
    locations(NULL),
    transition_table(transition_vector),
    index_table(index_vector)
{
    orig_symbol_count = alphabet.get_symbol_table().size();
    // initialize the stack for local variables
    LocalVariables locals_front;
    locals_front.flag_state = alphabet.get_fd_table();
    locals_front.tape_step = 1;
    locals_front.context = none;
    locals_front.context_placeholder = 0;
    locals_front.default_symbol_trap = false;
    locals_front.negative_context_success = false;
    locals_front.pending_passthrough = false;
    locals_front.running_weight = 0.0;
    local_stack.push(locals_front);
    RtnVariables rtn_front;
    rtn_front.tape_entry = 0;
    rtn_front.input_tape_entry = 0;
    rtn_front.candidate_input_pos = 0;
    rtn_front.candidate_tape_pos = 0;
    rtn_stack.push(rtn_front);
}

// Precompute which symbols may be at the start of a match.
// For now we ignore default arcs, as does the rest of pmatch.
void PmatchTransducer::collect_possible_first_symbols(void)
{
    SymbolNumberVector input_symbols;
    SymbolNumberVector special_symbol_v = alphabet.get_specials();
    std::set<SymbolNumber> special_symbols(special_symbol_v.begin(),
                                           special_symbol_v.end());
    SymbolTable table = alphabet.get_symbol_table();
    SymbolNumber symbol_count = table.size();
    for (SymbolNumber i = 1; i < symbol_count; ++i) {
        if (!alphabet.is_like_epsilon(i) &&
            !alphabet.is_end_tag(i) &&
            special_symbols.count(i) == 0 &&
            i != alphabet.get_unknown_symbol() &&
            i != alphabet.get_identity_symbol() &&
            i != alphabet.get_default_symbol())
        {
            input_symbols.push_back(i);
        }
    }
    // always include unknown and identity (once) but not default
    if (alphabet.get_unknown_symbol() != NO_SYMBOL_NUMBER) {
        input_symbols.push_back(alphabet.get_unknown_symbol());
    }
    if (alphabet.get_identity_symbol() != NO_SYMBOL_NUMBER) {
        input_symbols.push_back(alphabet.get_identity_symbol());
    }
    std::set<TransitionTableIndex> seen_indices;
    try {
        collect_first(0, input_symbols, seen_indices);
    } catch (bool e) {
        // If the end state can be reached without any input
        // or we have initial wildcards
        if (e == true) {
            possible_first_symbols.clear();
        }
    }

}

void PmatchTransducer::collect_first_epsilon(TransitionTableIndex i,
                                             SymbolNumberVector const& input_symbols,
                                             std::set<TransitionTableIndex> & seen_indices)
{
    while(true) {
        SymbolNumber output = transition_table[i].get_output_symbol();
        if (transition_table[i].get_input_symbol() == 0) {
            if (!checking_context()) {
                if (!try_entering_context(output)) {
                    collect_first(transition_table[i].get_target(), input_symbols, seen_indices);
                    ++i;
                } else {
                    // We're going to fake through a context
                    collect_first(transition_table[i].get_target(), input_symbols, seen_indices);
                    local_stack.pop();
                    ++i;
                }
            } else {
                // We *are* checking context and may be done
                if (try_exiting_context(output)) {
                    collect_first(transition_table[i].get_target(), input_symbols, seen_indices);
                    local_stack.pop();
                    ++i;
                } else {
                    // Don't touch output when checking context
                    collect_first(transition_table[i].get_target(), input_symbols, seen_indices);
                    ++i;
                }
            }
        } else if (alphabet.is_flag_diacritic(
                       transition_table[i].get_input_symbol())) {
            collect_first(transition_table[i].get_target(), input_symbols, seen_indices);
            ++i;
        } else if (alphabet.has_rtn(transition_table[i].get_input_symbol())) {
            possible_first_symbols.insert(transition_table[i].get_input_symbol());
            // collect the inputs from this later
            ++i;
        } else { // it's not epsilon and it's not a flag or Ins, so nothing to do
            return;
        }
    }

}

void PmatchTransducer::collect_first_epsilon_index(TransitionTableIndex i,
                                                   SymbolNumberVector const& input_symbols,
                                                   std::set<TransitionTableIndex> & seen_indices)
{
    if (index_table[i].get_input_symbol() == 0) {
        collect_first_epsilon(
            index_table[i].get_target() - TRANSITION_TARGET_TABLE_START,
            input_symbols, seen_indices);                                
    }
}

void PmatchTransducer::collect_first_transition(TransitionTableIndex i,
                                                SymbolNumberVector const& input_symbols,
                                                std::set<TransitionTableIndex> & seen_indices)
{
    for (SymbolNumberVector::const_iterator it = input_symbols.begin();
         it != input_symbols.end(); ++it) {
        if (transition_table[i].get_input_symbol() == *it) {
            if (!checking_context()) {
                // if this is unknown or identity, game over
                if (*it == alphabet.get_identity_symbol() ||
                    *it == alphabet.get_unknown_symbol()) {
                    container->reset_recursion();
                    throw true;
                }
                if (alphabet.list2symbols[*it] != NO_SYMBOL_NUMBER) {
                    // If this is a list, collect everything in the list
                    // if it's an exclusionary list, give up
                    if (std::find(alphabet.exclusionary_lists.begin(),
                                  alphabet.exclusionary_lists.end(),
                                  *it)
                        != alphabet.exclusionary_lists.end()) {
                        container->reset_recursion();
                        throw true;
                    }
                    for (SymbolNumberVector::const_iterator sym_it =
                            alphabet.symbol_list_members[alphabet.list2symbols[*it]].begin();
                        sym_it != alphabet.symbol_list_members[alphabet.list2symbols[*it]].end(); ++sym_it) {
                        possible_first_symbols.insert(*sym_it);
                    }
                } else {
                    possible_first_symbols.insert(*it);
                }
            } else {
                // faking through a context check
                collect_first(transition_table[i].get_target(),
                              input_symbols, seen_indices);
            }
        }
    }
}

void PmatchTransducer::collect_first_index(TransitionTableIndex i,
                                           SymbolNumberVector const& input_symbols,
                                           std::set<TransitionTableIndex> & seen_indices)
{
    for (SymbolNumberVector::const_iterator it = input_symbols.begin();
         it != input_symbols.end(); ++it) {
        if (index_table[i+*it].get_input_symbol() == *it) {
            collect_first_transition(index_table[i+*it].get_target() -
                                     TRANSITION_TARGET_TABLE_START,
                                     input_symbols, seen_indices);
        }
    }
}

void PmatchTransducer::collect_first(TransitionTableIndex i,
                                     SymbolNumberVector const& input_symbols,
                                     std::set<TransitionTableIndex> & seen_indices)
{
    if (!container->try_recurse()) {
        container->reset_recursion();
        throw true;
    }
    if (seen_indices.count(i) == 1) {
        container->unrecurse();
        return;
    } else {
        seen_indices.insert(i);
    }
    if (indexes_transition_table(i))
    {
        i -= TRANSITION_TARGET_TABLE_START;
        
        // If we can get to finality without any input,
        // throw a bool indicating that the full input set is needed
        if (transition_table[i].final()) {
            container->reset_recursion();
            throw true;
        }

        collect_first_epsilon(i+1, input_symbols, seen_indices);
        collect_first_transition(i+1, input_symbols, seen_indices);
        
    } else {
        if (index_table[i].final()) {
            container->reset_recursion();
            throw true;
        }
        collect_first_epsilon_index(i+1, input_symbols, seen_indices);
        collect_first_index(i+1, input_symbols, seen_indices);
    }
}



void PmatchContainer::initialize_input(const char * input_s)
{
    input.clear();
    char * input_str = const_cast<char *>(input_s);
    char ** input_str_ptr = &input_str;
    SymbolNumber k = NO_SYMBOL_NUMBER;
    SymbolNumber boundary_sym = alphabet.get_special(boundary);
    char * single_codepoint_scratch;
    char * single_codepoint_scratch_orig;
    if (single_codepoint_tokenization) {
        single_codepoint_scratch = new char[5];
        single_codepoint_scratch_orig = single_codepoint_scratch;
    }
    if (boundary_sym != NO_SYMBOL_NUMBER) {
        input.push_back(boundary_sym);
    }
    while (**input_str_ptr != 0) {
        char * original_input_loc = *input_str_ptr;
        if (single_codepoint_tokenization) {
            int bytes_to_tokenize = nByte_utf8(**input_str_ptr);
            if (bytes_to_tokenize > 0) {
                single_codepoint_scratch = single_codepoint_scratch_orig;
                memcpy(single_codepoint_scratch, *input_str_ptr, bytes_to_tokenize);
                single_codepoint_scratch[bytes_to_tokenize] = '\0';
                k = encoder->find_key(&single_codepoint_scratch);
                if (k != NO_SYMBOL_NUMBER) {
                    (*input_str_ptr) += bytes_to_tokenize;
                }
            }
        } else {
            k = encoder->find_key(input_str_ptr);
        }
        if (k == NO_SYMBOL_NUMBER) {
            // Regular tokenization failed
            // the encoder moves as far as it can during tokenization,
            // we want to go back to be in position to add one utf-8 char
            *input_str_ptr = original_input_loc;
            int bytes_to_tokenize = nByte_utf8(**input_str_ptr);
            if (bytes_to_tokenize == 0) {
                // if utf-8 tokenization fails too, just grab a byte
                bytes_to_tokenize = 1;
            }
            char new_symbol[5];
            memcpy(new_symbol, *input_str_ptr, bytes_to_tokenize);
            new_symbol[bytes_to_tokenize] = '\0';
            (*input_str_ptr) += bytes_to_tokenize;
            alphabet.add_symbol(new_symbol);
            encoder->read_input_symbol(new_symbol, symbol_count);
            k = symbol_count;
            ++symbol_count;
        }
        input.push_back(k);
    }
    if (boundary_sym != NO_SYMBOL_NUMBER) {
        input.push_back(boundary_sym);
    }
    if (single_codepoint_tokenization) {
        delete single_codepoint_scratch_orig;
    }
    return;
}

void PmatchTransducer::match(unsigned int & input_tape_pos,
                             unsigned int & tape_pos)
{
    rtn_stack.top().best_result.clear();
    rtn_stack.top().candidate_input_pos = input_tape_pos;
    rtn_stack.top().input_tape_entry = input_tape_pos;
    rtn_stack.top().tape_entry = tape_pos;
    rtn_stack.top().candidate_tape_pos = tape_pos;
    rtn_stack.top().best_weight = 0.0;
    rtn_stack.top().candidate_found = false;
    local_stack.top().context = none;
    local_stack.top().tape_step = 1;
    local_stack.top().context_placeholder = 0;
    local_stack.top().default_symbol_trap = false;
    local_stack.top().running_weight = 0.0;
    if (locations != NULL) {
        delete locations;
        locations = NULL;
    }
    if (container->locate_mode) {
        locations = new WeightedDoubleTapeVector();
    }
    get_analyses(input_tape_pos, tape_pos, 0);
    tape_pos = rtn_stack.top().candidate_tape_pos;
    input_tape_pos = rtn_stack.top().candidate_input_pos;
}

void PmatchTransducer::rtn_call(unsigned int & input_tape_pos,
                                unsigned int & tape_pos)
{
    rtn_stack.push(rtn_stack.top());
    rtn_stack.top().candidate_input_pos = input_tape_pos;
    rtn_stack.top().input_tape_entry = input_tape_pos;
    rtn_stack.top().tape_entry = tape_pos;
    rtn_stack.top().candidate_tape_pos = tape_pos;
    rtn_stack.top().best_weight = 0.0;
    rtn_stack.top().candidate_found = false;
    local_stack.push(local_stack.top());
    local_stack.top().flag_state = alphabet.get_fd_table();
    local_stack.top().tape_step = 1;
    local_stack.top().context = none;
    local_stack.top().context_placeholder = 0;
    local_stack.top().default_symbol_trap = false;
    local_stack.top().running_weight = 0.0;
    get_analyses(input_tape_pos, tape_pos, 0);
    tape_pos = rtn_stack.top().candidate_tape_pos;
    input_tape_pos = rtn_stack.top().candidate_input_pos;
}

void PmatchTransducer::rtn_exit(void)
{
    rtn_stack.pop();
    local_stack.pop();
}

void PmatchTransducer::note_analysis(unsigned int input_pos,
                                     unsigned int tape_pos)
{
    if (input_pos + 1 == 0) {
        // Sanity check for tape beyond its limits, this can happen
        // with left contexts and should be dealt with a bit more nicely
        return;
    }
    rtn_stack.top().candidate_found = true;
    if (locations != NULL) {
        grab_location(input_pos, tape_pos);
        return;
    }
    
    if ((input_pos > rtn_stack.top().candidate_input_pos) ||
        (input_pos == rtn_stack.top().candidate_input_pos &&
         rtn_stack.top().best_weight > local_stack.top().running_weight)) {
        rtn_stack.top().best_result = container->tape.extract_slice(
            rtn_stack.top().tape_entry, tape_pos);
        rtn_stack.top().candidate_tape_pos = tape_pos;
        rtn_stack.top().candidate_input_pos = input_pos;
        rtn_stack.top().best_weight = local_stack.top().running_weight;
    } else if (container->verbose &&
               input_pos == rtn_stack.top().candidate_input_pos &&
               rtn_stack.top().best_weight == local_stack.top().running_weight) {
        DoubleTape discarded(container->tape.extract_slice(
                                 rtn_stack.top().tape_entry, tape_pos));
        std::cerr << "\n\tline " << container->line_number << ": conflicting equally weighted matches found, keeping:\n\t"
                  << alphabet.stringify(rtn_stack.top().best_result) << std::endl
                  << "\tdiscarding:\n\t"
                  << alphabet.stringify(discarded) << std::endl << std::endl; 
    }
}

void PmatchTransducer::grab_location(unsigned int input_pos, unsigned int tape_pos)
{
    if (locations->size() != 0) {
        if (input_pos < rtn_stack.top().candidate_input_pos) {
            // We already have better matches
            return;
        } else if (input_pos > rtn_stack.top().candidate_input_pos) {
            // The old locations are worse
            locations->clear();
        }
    }
    rtn_stack.top().candidate_tape_pos = tape_pos;
    rtn_stack.top().candidate_input_pos = input_pos;
    WeightedDoubleTape rv(container->tape.extract_slice(
                              rtn_stack.top().tape_entry, tape_pos),
                          local_stack.top().running_weight);
    locations->push_back(rv);
}

void PmatchTransducer::take_epsilons(unsigned int input_pos,
                                     unsigned int tape_pos,
                                     TransitionTableIndex i)
{
    i = make_transition_table_index(i, 0);
    
    while (is_good(i)) {
        SymbolNumber input = transition_table[i].get_input_symbol();
        SymbolNumber output = transition_table[i].get_output_symbol();
        TransitionTableIndex target = transition_table[i].get_target();
        Weight weight = transition_table[i].get_weight();
        // We handle paths where we're checking contexts here
        if (input == 0) {
            if (container->profile_mode) {
                alphabet.count(output);
            }
            if (!checking_context()) {
                if (!try_entering_context(output)) {
                    // no context to enter, regular input epsilon
                    container->tape.write(tape_pos, 0, output);
                    Weight old_weight = local_stack.top().running_weight;
                    local_stack.top().running_weight += weight;

                    // if it's an entry or exit arc, adjust entry stack
                    if (output == alphabet.get_special(entry)) {
                        container->entry_stack.push(input_pos);
                    } else if (output == alphabet.get_special(exit)) {
                        container->entry_stack.pop();
                    }
                    
                    get_analyses(input_pos, tape_pos + 1, target);

                    if (output == alphabet.get_special(entry)) {
                        container->entry_stack.pop();
                    } else if (output == alphabet.get_special(exit)) {
                        container->entry_stack.unpop();
                    }
                    
                    local_stack.top().running_weight = old_weight;
                } else {
                    check_context(input_pos, tape_pos, i);
                }
            } else {
                // We *are* checking context and may be done
                if (try_exiting_context(output)) {
                    // We've successfully completed a context check
                    get_analyses(local_stack.top().context_placeholder, tape_pos, target);
                    local_stack.pop();
                } else {
                    if (local_stack.top().negative_context_success == true) {
                        // We've succeeded in a negative context, just back out
                        return;
                    } else {
                        // Don't alter tapes when checking context
                        get_analyses(input_pos, tape_pos, target);
                    }
                }
            }
        } else if (alphabet.is_flag_diacritic(input)) {
            take_flag(input, input_pos, tape_pos, i);
        } else if (alphabet.has_rtn(input)) {
            take_rtn(input, input_pos, tape_pos, i);
        } else { // it's not epsilon and it's not a flag or Ins, so nothing to do
            return;
        }
        ++i;
    }
}

void PmatchTransducer::check_context(unsigned int input_pos,
                                     unsigned int tape_pos,
                                     TransitionTableIndex i)
{
    local_stack.top().context_placeholder = input_pos;
    if (local_stack.top().context == LC ||
        local_stack.top().context == NLC) {
        // Jump to the left-hand side of the input
        input_pos = container->entry_stack.top() - 1;
    }
    get_analyses(input_pos, tape_pos, transition_table[i].get_target());
    // In case we have a negative context, we check to see if the context matched.
    // If it did, we schedule a passthrough arc after we've processed epsilons.
    bool schedule_passthrough = false;
//            std::cerr << "!local_stack.top().negative_context_success is " <<
//            !local_stack.top().negative_context_success << std::endl;

    if((local_stack.top().context == NLC || local_stack.top().context == NRC)
       && !local_stack.top().negative_context_success) {
        schedule_passthrough = true;
//        std::cerr << "scheduled passthrough\n";
    }
    local_stack.pop();
    if (schedule_passthrough) {
        local_stack.top().pending_passthrough = true;
    }
}

void PmatchTransducer::take_rtn(SymbolNumber input,
                                unsigned int input_pos,
                                unsigned int tape_pos,
                                TransitionTableIndex i)
{
    unsigned int original_tape_pos = tape_pos;
    Weight original_weight = local_stack.top().running_weight;
    local_stack.top().running_weight += transition_table[i].get_weight();
    // Pass control
    PmatchTransducer * rtn_target =
        alphabet.get_rtn(input);
    rtn_target->rtn_call(input_pos, tape_pos);
    if (tape_pos != original_tape_pos) {
        // Tape moved, fetch result
        tape_pos = original_tape_pos;
        for(DoubleTape::const_iterator it =
                rtn_target->get_best_result().begin();
            it != rtn_target->get_best_result().end();
            ++it) {
            container->tape.write(tape_pos++, it->input, it->output);
        }
        local_stack.top().running_weight += rtn_target->get_best_weight();
        rtn_target->rtn_exit();
        // We're back in this transducer and continue where we left off
        get_analyses(input_pos, tape_pos, transition_table[i].get_target());
    } else {
        rtn_target->rtn_exit();
    }
    local_stack.top().running_weight = original_weight;
}

void PmatchTransducer::take_flag(SymbolNumber input,
                                 unsigned int input_pos,
                                 unsigned int tape_pos,
                                 TransitionTableIndex i)
{
    std::vector<short> old_values(local_stack.top().flag_state.get_values());
    if (local_stack.top().flag_state.apply_operation(
            *(alphabet.get_operation(input)))) {
        // flag diacritic allowed
        // generally we shouldn't care to write flags
//                container->tape.write(tape_pos, input, output);
        Weight old_weight = local_stack.top().running_weight;
        local_stack.top().running_weight += transition_table[i].get_weight();
        get_analyses(input_pos, tape_pos, transition_table[i].get_target());
        local_stack.top().running_weight = old_weight;
    }
    local_stack.top().flag_state.assign_values(old_values);
}

void PmatchTransducer::take_transitions(SymbolNumber input,
                                        unsigned int input_pos,
                                        unsigned int tape_pos,
                                        TransitionTableIndex i)
{
    i = make_transition_table_index(i, input);
    
    while (is_good(i)) {
        SymbolNumber this_input = transition_table[i].get_input_symbol();
        SymbolNumber this_output = transition_table[i].get_output_symbol();
        TransitionTableIndex target = transition_table[i].get_target();
        if (this_input == NO_SYMBOL_NUMBER) {
            return;
        } else if (this_input == input) {
            if (!checking_context()) {
                if (this_output == alphabet.get_identity_symbol() ||
                    (this_output == alphabet.get_unknown_symbol()) ||
                    (alphabet.list2symbols[this_output] != NO_SYMBOL_NUMBER)) {
                // we got here via a meta-arc, so look back in the
                // input tape to find the symbol we want to write
                    this_output = container->input[input_pos];
                }
                if (this_input == alphabet.get_identity_symbol() ||
                    (this_input == alphabet.get_unknown_symbol()) ||
                    (alphabet.list2symbols[this_input] != NO_SYMBOL_NUMBER)) {
                    this_input = container->input[input_pos];
                }
                Weight tmp = local_stack.top().running_weight;
                local_stack.top().running_weight +=
                    transition_table[i].get_weight();
                if (this_input == alphabet.get_special(Pmatch_passthrough)) {
                    get_analyses(input_pos, tape_pos, target); // FIXME
                } else {
                    container->tape.write(tape_pos, this_input, this_output);
                    get_analyses(input_pos + 1, tape_pos + 1, target);
                }
                local_stack.top().running_weight = tmp;
            } else {
                // Checking context so don't touch output
                get_analyses(input_pos + local_stack.top().tape_step, tape_pos, target);
            }
            local_stack.top().default_symbol_trap = false;
        } else {
            return;
        }
        ++i;
    }
}

void PmatchTransducer::get_analyses(unsigned int input_pos,
                                    unsigned int tape_pos,
                                    TransitionTableIndex i)
{
    if (container->max_time > 0.0) {
        ++container->call_counter;
        // Have we spent too much time?
        if (container->limit_reached ||
            (container->call_counter % 1000000 == 0 &&
             (rtn_stack.top().candidate_found &&
              // if we have at least something, stop doing more work
              (((double)(clock() - container->start_clock)) / CLOCKS_PER_SEC) > container->max_time))) {
            container->limit_reached = true;
            return;
        }
    }
    if (!container->try_recurse()) {
        if (container->verbose) {
            std::cerr << "pmatch: out of stack space, truncating result\n";
        }
        return;
    }
    local_stack.top().default_symbol_trap = true;
    take_epsilons(input_pos, tape_pos, i + 1);
//    std::cerr << "get_analyses local stack size is " << local_stack.size() << std::endl;
    if (local_stack.top().pending_passthrough) {
        // A negative context failed
        take_transitions(alphabet.get_special(Pmatch_passthrough),
                         input_pos, tape_pos, i+1);
        local_stack.top().pending_passthrough = false;
    }
    // Check for finality even if the input string hasn't ended
    if (is_final(i)) {
        Weight tmp = local_stack.top().running_weight;
        local_stack.top().running_weight += get_weight(i);
        note_analysis(input_pos, tape_pos);
        local_stack.top().running_weight = tmp;
    }

    SymbolNumber input;
    if (!container->has_queued_input(input_pos)) {
        container->unrecurse();
        return;
    } else {
        input = container->input[input_pos];
    }
    
    if (alphabet.symbol2lists[input] != NO_SYMBOL_NUMBER) {
// At least one symbol list could allow this symbol
        for(SymbolNumberVector::const_iterator it =
                alphabet.symbol_lists[alphabet.symbol2lists[input]].begin();
            it != alphabet.symbol_lists[alphabet.symbol2lists[input]].end(); ++it) {
            take_transitions(*it, input_pos, tape_pos, i+1);
        }
    }
    // The "normal" case where we have a regular input symbol
    if (input < orig_symbol_count) {
        take_transitions(input, input_pos, tape_pos, i+1);
    } else {
        if (alphabet.get_identity_symbol() != NO_SYMBOL_NUMBER) {
            take_transitions(alphabet.get_identity_symbol(), input_pos, tape_pos, i+1);
        }
        if (alphabet.get_unknown_symbol() != NO_SYMBOL_NUMBER) {
            take_transitions(alphabet.get_unknown_symbol(), input_pos, tape_pos, i+1);
        }
    }
    
    container->unrecurse();
}

bool PmatchTransducer::checking_context(void) const
{
    return local_stack.top().context != none;
}

bool PmatchTransducer::try_entering_context(SymbolNumber symbol)
{
    if (symbol == alphabet.get_special(LC_entry)) {
        local_stack.push(local_stack.top());
        local_stack.top().context = LC;
        local_stack.top().tape_step = -1;
        return true;
    } else if (symbol == alphabet.get_special(RC_entry)) {
        local_stack.push(local_stack.top());
        local_stack.top().context = RC;
        local_stack.top().tape_step = 1;
        return true;
    } else if (symbol == alphabet.get_special(NLC_entry)) {
        local_stack.push(local_stack.top());
        local_stack.top().context = NLC;
        local_stack.top().tape_step = -1;
        return true;
    } else if (symbol == alphabet.get_special(NRC_entry)) {
        local_stack.push(local_stack.top());
        local_stack.top().context = NRC;
        local_stack.top().tape_step = 1;
        return true;
    } else {
        return false;
    }
}

bool PmatchTransducer::try_exiting_context(SymbolNumber symbol)
{
    switch (local_stack.top().context) {
    case LC:
        if (symbol == alphabet.get_special(LC_exit)) {
            exit_context();
            return true;
        } else {
            return false;
        }
    case RC:
        if (symbol == alphabet.get_special(RC_exit)) {
            exit_context();
            return true;
        } else {
            return false;
        }
    case NRC:
        if (symbol == alphabet.get_special(NRC_exit)) {
            local_stack.top().negative_context_success = true;
            return false;
        }
    case NLC:
        if (symbol == alphabet.get_special(NLC_exit)) {
            local_stack.top().negative_context_success = true;
            return false;
        }
    default:
        return false;
    }
}

void PmatchTransducer::exit_context(void)
{
    local_stack.push(local_stack.top());
    local_stack.top().context = none;
    local_stack.top().negative_context_success = false;
    local_stack.top().tape_step = 1;
}

}
