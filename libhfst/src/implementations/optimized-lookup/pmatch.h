// Copyright (c) 2016 University of Helsinki                          
//                                                                    
// This library is free software; you can redistribute it and/or      
// modify it under the terms of the GNU Lesser General Public         
// License as published by the Free Software Foundation; either       
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more      
// information.
#ifndef _HFST_OL_TRANSDUCER_PMATCH_H_
#define _HFST_OL_TRANSDUCER_PMATCH_H_

#include <map>
#include <stack>
#include <sstream>
#include <algorithm>
#include <ctime>
#include "transducer.h"

namespace hfst_ol {

    class PmatchTransducer;
    class PmatchContainer;
    struct Location;
    class WeightedDoubleTape;

    const unsigned int PMATCH_MAX_RECURSION_DEPTH = 5000;
    
    typedef std::vector<PmatchTransducer *> RtnVector;
    typedef std::map<std::string, SymbolNumber> RtnNameMap;
    typedef std::vector<Location> LocationVector;
    typedef std::vector<LocationVector> LocationVectorVector;
    typedef std::vector<WeightedDoubleTape> WeightedDoubleTapeVector;
            
    
    enum SpecialSymbol{entry,
                       exit,
                       LC_entry,
                       LC_exit,
                       RC_entry,
                       RC_exit,
                       NLC_entry,
                       NLC_exit,
                       NRC_entry,
                       NRC_exit,
                       Pmatch_passthrough,
                       boundary,
                       Pmatch_input_mark,
                       SPECIALSYMBOL_NR_ITEMS};

    struct SymbolPair
    {
        SymbolNumber input;
        SymbolNumber output;
    SymbolPair(void): input(0), output(0) {}
    SymbolPair(SymbolNumber i, SymbolNumber o): input(i), output(o) {}
    };

    class DoubleTape: public std::vector<SymbolPair>
    {
    public:

        void write(unsigned int pos, SymbolNumber in, SymbolNumber out)
        {
            while (pos >= this->size()) {
                this->push_back(SymbolPair());
            }
            this->operator[](pos) = SymbolPair(in, out);
        }

        DoubleTape extract_slice(unsigned int start, unsigned int stop)
        {
            DoubleTape retval;
            while(start < stop) {
                retval.push_back(this->at(start));
                ++start;
            }
            return retval;
        }

    };

    class PositionStack: public std::vector<unsigned int>
    {
        unsigned int tmp;
    public:
        void push(unsigned int val) { push_back(val); }
        void pop(void) { tmp = back(); pop_back(); }
        void unpop(void) { push_back(tmp); }
        unsigned int top(void) { return back(); }
    };

    class WeightedDoubleTape: public DoubleTape
    {
    public:
        Weight weight;
    WeightedDoubleTape(DoubleTape dt, Weight w): DoubleTape(dt), weight(w) {}
    };

    class PmatchAlphabet: public TransducerAlphabet {
    protected:
        RtnVector rtns;
        SymbolNumberVector special_symbols;
        std::map<SymbolNumber, std::string> end_tag_map;
        RtnNameMap rtn_names;
// For each symbol, either NO_SYMBOL for "no corresponding list" or an index into symbol_lists
        SymbolNumberVector symbol2lists;
// For each a symbol, either NO_SYMBOL for "this is not a list" or an index into symbol_list_members
        SymbolNumberVector list2symbols;
        // For each entry referring to entries in the symbol table, indicate
        // "this symbol is an exclusionary list", ie. symbols not in it
        // will match
        SymbolNumberVector exclusionary_lists;
        std::vector<SymbolNumberVector> symbol_lists;
        std::vector<SymbolNumberVector> symbol_list_members;
        std::vector<unsigned long int> counters;
        SymbolNumberVector guards;
        std::vector<bool> printable_vector;
        bool is_end_tag(const SymbolNumber symbol) const;
        bool is_input_mark(const SymbolNumber symbol) const;
        bool is_guard(const SymbolNumber symbol) const;
        bool is_counter(const SymbolNumber symbol) const;
        std::string end_tag(const SymbolNumber symbol);
        std::string start_tag(const SymbolNumber symbol);
        bool extract_tags;

    public:
        PmatchAlphabet(std::istream& is, SymbolNumber symbol_count);
        PmatchAlphabet(TransducerAlphabet const & a);
        PmatchAlphabet(void);
        ~PmatchAlphabet(void);
        virtual void add_symbol(const std::string & symbol);
        static bool is_end_tag(const std::string & symbol);
        static bool is_insertion(const std::string & symbol);
        static bool is_guard(const std::string & symbol);
        static bool is_list(const std::string & symbol);
        static bool is_counter(const std::string & symbol);
        static bool is_special(const std::string & symbol);
        static bool is_printable(const std::string & symbol);
        static std::string name_from_insertion(
            const std::string & symbol);
        bool is_printable(SymbolNumber symbol);
        void add_special_symbol(const std::string & str, SymbolNumber symbol_number);
        void process_symbol_list(std::string str, SymbolNumber sym);
        void process_counter(std::string str, SymbolNumber sym);
        void count(SymbolNumber sym);
        void add_rtn(PmatchTransducer * rtn, std::string const & name);
        bool has_rtn(std::string const & name) const;
        bool has_rtn(SymbolNumber symbol) const;
        PmatchTransducer * get_rtn(SymbolNumber symbol);
        std::string get_counter_name(SymbolNumber symbol);
        SymbolNumber get_special(SpecialSymbol special) const;
        SymbolNumberVector get_specials(void) const;
        std::string stringify(const DoubleTape & str);
        Location locatefy(unsigned int input_offset,
                          const WeightedDoubleTape & str);

        friend class PmatchTransducer;
        friend class PmatchContainer;
    };

    class PmatchContainer
    {
    protected:
        PmatchAlphabet alphabet;
        Encoder * encoder;
        SymbolNumber orig_symbol_count;
        SymbolNumber symbol_count;
        PmatchTransducer * toplevel;
        size_t io_size;
        SymbolNumberVector input;
        PositionStack entry_stack;
        DoubleTape tape;
        DoubleTape output;
        LocationVectorVector locations;
        std::vector<char> possible_first_symbols;
        bool verbose;
        bool locate_mode;
        bool profile_mode;
        bool single_codepoint_tokenization;
        unsigned int recursion_depth_left;
        // An optional time limit for operations
        double max_time;
        // When we started work
        clock_t start_clock;
        // A counter to avoid checking the clock too often
        unsigned long call_counter;
        // A flag to set for when time has been overstepped
        bool limit_reached;

    public:

        PmatchContainer(std::istream & is);
        PmatchContainer(Transducer * toplevel);
        PmatchContainer(void);
        ~PmatchContainer(void);

        unsigned long line_number;

        void initialize_input(const char * input);
        bool has_unsatisfied_rtns(void) const;
        std::string get_unsatisfied_rtn_name(void) const;
        void add_rtn(Transducer * rtn, const std::string & name);
        void process(const std::string & input);
        std::string match(const std::string & input,
                          double time_cutoff = 0.0);
        LocationVectorVector locate(std::string & input,
                                    double time_cutoff = 0.0);
        std::string get_profiling_info(void);
        bool has_queued_input(unsigned int input_pos);
        bool not_possible_first_symbol(SymbolNumber sym)
        {
            if (possible_first_symbols.size() == 0) {
                return false;
            }
            return sym >= possible_first_symbols.size() ||
                possible_first_symbols[sym] == 0;
        }
        void copy_to_output(const DoubleTape & best_result);
        void copy_to_output(SymbolNumber input, SymbolNumber output);
        std::string stringify_output(void);
//        LocationVector locatefy_output(void);
        static std::string parse_name_from_hfst3_header(std::istream & f);
        void set_verbose(bool b) { verbose = b; }
        void set_extract_tags_mode(bool b)
            { alphabet.extract_tags = b; }
        void set_single_codepoint_tokenization(bool b)
            { single_codepoint_tokenization = b; }
        void set_profile(bool b) { profile_mode = b; }
        bool try_recurse(void)
        {
            if (recursion_depth_left > 0) {
                --recursion_depth_left;
                return true;
            } else {
                return false;
            }
        }
        void unrecurse(void) { ++recursion_depth_left; }
        void reset_recursion(void) { recursion_depth_left = PMATCH_MAX_RECURSION_DEPTH; }

        friend class PmatchTransducer;
    };

    struct Location
    {
        unsigned int start;
        unsigned int length;
        std::string input;
        std::string output;
        std::string tag;
        Weight weight;
        std::vector<size_t> input_parts;
        std::vector<size_t> output_parts;

        bool operator<(Location rhs) const
            { return this->weight < rhs.weight; }
    };

    struct ContextMatchedTrap
    {
        bool polarity;
    ContextMatchedTrap(bool p): polarity(p) {}
    };

    class PmatchTransducer
    {
    protected:
        enum ContextChecking{none, LC, NLC, RC, NRC};

// Transducers have static data, ie. tables for describing the states and
// transitions, and dynamic data, which is altered during lookup.
// In pmatch several instances of the same transducer may be operating
// in a stack, so this dynamic data is put in a class of its own.
        struct LocalVariables
        {
            hfst::FdState<SymbolNumber> flag_state;
            char tape_step;
            unsigned int context_placeholder;
            ContextChecking context;
            bool default_symbol_trap;
            bool negative_context_success;
            bool pending_passthrough;
            Weight running_weight;
        };

        struct RtnVariables
        {
            unsigned int candidate_input_pos;
            unsigned int candidate_tape_pos;
            unsigned int input_tape_entry;
            unsigned int tape_entry;
            DoubleTape best_result;
            Weight best_weight;
            bool candidate_found;
        };

        std::stack<LocalVariables> local_stack;
        std::stack<RtnVariables> rtn_stack;
    
        std::vector<TransitionW> transition_table;
        std::vector<TransitionWIndex> index_table;

        PmatchAlphabet & alphabet;
        SymbolNumber orig_symbol_count;
        PmatchContainer * container;
        WeightedDoubleTapeVector * locations;

        bool is_final(TransitionTableIndex i)
        {
            if (indexes_transition_table(i)) {
                return transition_table[i - TRANSITION_TARGET_TABLE_START].final();
            } else {
                return index_table[i].final();
            }
        }

        bool get_weight(TransitionTableIndex i)
        {
            if (indexes_transition_table(i)) {
                return transition_table[i - TRANSITION_TARGET_TABLE_START].get_weight();
            } else {
                return index_table[i].final_weight();
            }
        }

        TransitionTableIndex make_transition_table_index(
            TransitionTableIndex i, SymbolNumber input) {
            if (indexes_transition_table(i)) {
                return i - TRANSITION_TARGET_TABLE_START;
            } else {
                if (index_table[i + input].get_input_symbol() == input) {
                    return index_table[i + input].get_target() - TRANSITION_TARGET_TABLE_START;
                } else {
                    return TRANSITION_TARGET_TABLE_START;
                }
            }
        }

        // The mutually recursive lookup-handling functions

        void take_epsilons(unsigned int input_pos,
                           unsigned int tape_pos,
                           TransitionTableIndex i);

        void check_context(unsigned int input_pos,
                           unsigned int tape_pos,
                           TransitionTableIndex i);
  
        void take_rtn(SymbolNumber input,
                      unsigned int input_pos,
                      unsigned int tape_pos,
                      TransitionTableIndex i);
  
        void take_flag(SymbolNumber input,
                       unsigned int input_pos,
                       unsigned int tape_pos,
                       TransitionTableIndex i);
  
        void take_transitions(SymbolNumber input,
                              unsigned int input_pos,
                              unsigned int tape_pos,
                              TransitionTableIndex i);

        void get_analyses(unsigned int input_pos,
                          unsigned int tape_pos,
                          TransitionTableIndex index);

        bool checking_context(void) const;
        bool try_entering_context(SymbolNumber symbol);
        bool try_exiting_context(SymbolNumber symbol);
        void exit_context(void);

        void collect_first_epsilon(TransitionTableIndex i,
                                   SymbolNumberVector const& input_symbols,
                                   std::set<TransitionTableIndex> & seen_indices);
        void collect_first_epsilon_index(TransitionTableIndex i,
                                         SymbolNumberVector const& input_symbols,
                                         std::set<TransitionTableIndex> & seen_indices);
        void collect_first_transition(TransitionTableIndex i,
                                      SymbolNumberVector const& input_symbols,
                                      std::set<TransitionTableIndex> & seen_indices);
        void collect_first_index(TransitionTableIndex i,
                                 SymbolNumberVector const& input_symbols,
                                 std::set<TransitionTableIndex> & seen_indices);
        void collect_first(TransitionTableIndex i,
                           SymbolNumberVector const& input_symbols,
                           std::set<TransitionTableIndex> & seen_indices);


    public:
        PmatchTransducer(std::istream& is,
                         TransitionTableIndex index_table_size,
                         TransitionTableIndex transition_table_size,
                         PmatchAlphabet & alphabet,
                         PmatchContainer * container);

        PmatchTransducer(std::vector<TransitionW> transition_vector,
                         std::vector<TransitionWIndex> index_vector,
                         PmatchAlphabet & alphabet,
                         PmatchContainer * container);

        std::set<SymbolNumber> possible_first_symbols;

        bool final_index(TransitionTableIndex i) const
        {
            if (indexes_transition_table(i)) {
                return transition_table[i].final();
            } else {
                return index_table[i].final();
            }
        }

        static bool indexes_transition_table(TransitionTableIndex i)
        { return  i >= TRANSITION_TARGET_TABLE_START; }

        static bool is_good(TransitionTableIndex i)
        { return  i < TRANSITION_TARGET_TABLE_START; }

        const DoubleTape & get_best_result(void) const
        { return rtn_stack.top().best_result; }
        unsigned int get_candidate_input_pos(void) const
        { return rtn_stack.top().candidate_input_pos; }
        Weight get_best_weight(void) const
        { return rtn_stack.top().best_weight; }
    
        void match(unsigned int & input_pos, unsigned int & tape_pos);
        void rtn_call(unsigned int & input_pos, unsigned int & tape_pos);
        void rtn_exit(void);
        void note_analysis(unsigned int input_pos, unsigned int tape_pos);
        void grab_location(unsigned int input_pos, unsigned int tape_pos);
        void collect_possible_first_symbols(void);

        friend class PmatchContainer;
    };

}

#endif //_HFST_OL_TRANSDUCER_PMATCH_H_
