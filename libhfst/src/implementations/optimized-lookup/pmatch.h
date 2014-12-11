#ifndef _HFST_OL_TRANSDUCER_PMATCH_H_
#define _HFST_OL_TRANSDUCER_PMATCH_H_

#include <map>
#include <stack>
#include <sstream>
#include <algorithm>
#include "transducer.h"

namespace hfst_ol {

    class PmatchTransducer;
    class PmatchContainer;
    struct Location;
    class WeightedDoubleTape;

    const unsigned int PMATCH_MAX_RECURSION_DEPTH = 5000;
    
    typedef std::map<SymbolNumber, PmatchTransducer *> RtnMap;
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
                       boundary};

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
        RtnMap rtns;
        std::map<SpecialSymbol, SymbolNumber> special_symbols;
        std::map<SymbolNumber, std::string> end_tag_map;
        std::map<std::string, SymbolNumber> rtn_names;
        SymbolNumberVector guards;
        bool is_end_tag(const SymbolNumber symbol) const;
        bool is_guard(const SymbolNumber symbol) const;
        std::string end_tag(const SymbolNumber symbol);
        std::string start_tag(const SymbolNumber symbol);
        bool extract_tags;

    public:
        PmatchAlphabet(std::istream& is, SymbolNumber symbol_count);
        PmatchAlphabet(void);
        ~PmatchAlphabet(void);
        static bool is_end_tag(const std::string & symbol);
        static bool is_insertion(const std::string & symbol);
        static bool is_guard(const std::string & symbol);
        static bool is_special(const std::string & symbol);
        static std::string name_from_insertion(
            const std::string & symbol);
        bool is_printable(SymbolNumber symbol);
        void add_special_symbol(const std::string & str, SymbolNumber symbol_number);
        void add_rtn(PmatchTransducer * rtn, std::string const & name);
        bool has_rtn(std::string const & name) const;
        bool has_rtn(SymbolNumber symbol) const;
        PmatchTransducer * get_rtn(SymbolNumber symbol);
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
        unsigned int recursion_depth_left;

    public:

        PmatchContainer(std::istream & is, bool verbose = false,
                        bool extract_tags = false);
        PmatchContainer(void);
        ~PmatchContainer(void);

        long line_number;

        void initialize_input(const char * input);
        bool has_unsatisfied_rtns(void) const;
        std::string get_unsatisfied_rtn_name(void) const;
        void process(std::string & input);
        std::string match(std::string & input);
        LocationVectorVector locate(std::string & input);
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
        void be_verbose(void) { verbose = true; }
        bool is_verbose(void) { return verbose; }
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
