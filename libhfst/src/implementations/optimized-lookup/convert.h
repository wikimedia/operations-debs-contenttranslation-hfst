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

#ifndef _HFST_OL_CONVERT_H_
#define _HFST_OL_CONVERT_H_

#if HAVE_OPENFST
#include "fst/fstlib.h"
#endif // HAVE_OPENFST

#include "transducer.h"
#include "pmatch.h"

namespace hfst_ol {
    
    typedef std::map<hfst_ol::TransitionTableIndex,unsigned int>
    HfstOlToBasicStateMap;

struct TransitionPlaceholder {
    unsigned int target;
    SymbolNumber output;
    float weight;

TransitionPlaceholder(unsigned int t, SymbolNumber o, float w):
    target(t),
    output(o),
    weight(w)
    {}
};

typedef std::map<SymbolNumber, std::vector<TransitionPlaceholder> >
    SymbolTransitionsMap;


struct StatePlaceholder {
    unsigned int state_number;
    unsigned int start_index;
    unsigned int first_transition;
    SymbolTransitionsMap inputs;
    bool final;
    float final_weight;
    StatePlaceholder (unsigned int state, bool finality, unsigned int first,
              Weight final_weight):
    state_number(state),
    start_index(UINT_MAX),
    first_transition(first),
    final(finality),
    final_weight(final_weight)
    {}
    StatePlaceholder ():
    state_number(UINT_MAX),
    start_index(UINT_MAX),
    first_transition(UINT_MAX),
    final(false),
    final_weight(0.0)
    { }
    
    bool is_simple(std::set<SymbolNumber> const & flag_symbols) const
    {
        if (state_number == 0) {
        return false;
        }
        if (flag_symbols.size() == 0) {
        return inputs.size() < 2;
        }
        bool have_zero = false;
        SymbolNumber input_symbols = 0;
        for(SymbolTransitionsMap::const_iterator it = inputs.begin();
        it != inputs.end(); ++it) {
        if ((it->first == 0) or (flag_symbols.count(it->first) != 0)) {
            if (!have_zero) {
            have_zero = true;
            ++input_symbols;
            }
        } else {
            ++input_symbols;
        }
        if (input_symbols > 1) {
            return false;
        }
        }
        return true;
    }
    
    unsigned int number_of_transitions(void) const {
    unsigned int count = 0;
    for(SymbolTransitionsMap::const_iterator it = inputs.begin();
        it != inputs.end(); ++it) {
        count += it->second.size();
    }
    return count;
    }
    
    unsigned int symbol_offset(
        SymbolNumber const symbol,
        std::set<SymbolNumber> const & flag_symbols) const {
        if (symbol == 0) {
            return 0;
        }
        unsigned int offset = 0;
        if (flag_symbols.size() == 0) {
            for(SymbolTransitionsMap::const_iterator it = inputs.begin();
                it!= inputs.end(); ++it) {
                if (symbol == it->first) {
                    return offset;
                }
                offset += it->second.size();
            }
            
        } else {
            if (inputs.count(0) != 0) { // if there are epsilons
                offset = inputs.find(0)->second.size();
            }
            for(std::set<SymbolNumber>::iterator flag_it = flag_symbols.begin();
                flag_it != flag_symbols.end(); ++flag_it) {
                if (inputs.count(*flag_it) != 0) { // if this flag is present
                    if (symbol == *flag_it) {
                        // Flags go to 0 (even if there's no epsilon)
                        return 0;
                    }
                    offset += inputs.find(*flag_it)->second.size();
                }
            }
            for(SymbolTransitionsMap::const_iterator it = inputs.begin();
                it!= inputs.end(); ++it) {
                if (it->first == 0 || flag_symbols.count(it->first) != 0) {
                    continue;
                }
                if (symbol == it->first) {
                    return offset;
                }
                offset += it->second.size();
            }
            std::string message("error in conversion between optimized lookup "
                                "format and HfstTransducer;\ntried to calculate "
                                "symbol_offset for symbol not present in state");
            HFST_THROW_MESSAGE
                (HfstFatalException,
                 message);
        }
        std::string message("error in function StatePlaceholder::symbol_offset");
        HFST_THROW_MESSAGE(HfstFatalException, message);
    }
};

bool compare_states_by_input_size(
    const StatePlaceholder & lhs, const StatePlaceholder & rhs);
bool compare_states_by_state_number(
    const StatePlaceholder & lhs, const StatePlaceholder & rhs);

class IndexPlaceholders: public std::map<unsigned int,
        std::pair<unsigned int, SymbolNumber> >
{
public:
    bool fits(StatePlaceholder const & state,
              std::set<SymbolNumber> const & flag_symbols,
              unsigned int const position) const
    {
    if (count(position) != 0) {
        return false;
    }
    for (SymbolTransitionsMap::const_iterator it = state.inputs.begin();
         it != state.inputs.end(); ++it) {
        SymbolNumber index_offset = it->first;
        if (flag_symbols.count(index_offset) != 0) {
        index_offset = 0;
        }
        if (count(index_offset + position + 1) != 0) {
        return false;
        }
    }
    return true;
    }

    bool unsuitable(unsigned int const index,
                    SymbolNumber const symbols,
                    float const packing_aggression) const
    {
    if (count(index) != 0) {
        return true;
    }
    
    // "Perfect packing" (under this strategy)
/*              for (unsigned int i = 0; i < symbols; ++i) {
        
        if (count(index + i) == 0) {
        return true;
        }
        return false;
        }*/

    unsigned int filled = 0;
    for (unsigned int i = 0; i < symbols; ++i) {
        filled += count(index + i + 1);
        if (filled >= (packing_aggression*symbols)) {
        return true; // too full
        }
    }
    return false;
    }
};


void write_transitions_from_state_placeholders(
    TransducerTable<TransitionW> & transition_table,
    std::vector<hfst_ol::StatePlaceholder>
    & state_placeholders,
    std::set<SymbolNumber> & flag_symbols);

void add_transitions_with(SymbolNumber symbol,
              std::vector<TransitionPlaceholder> & transitions,
              TransducerTable<TransitionW> & transition_table,
              std::vector<hfst_ol::StatePlaceholder>
              & state_placeholders,
              std::set<SymbolNumber> & flag_symbols);

#if HAVE_OPENFST // Covers remainder of file
typedef fst::StdArc::StateId StateId;
typedef fst::StdArc StdArc;
typedef fst::StdVectorFst TransduceR;
typedef fst::ArcIterator<TransduceR> ArcIterator;
typedef std::set<StateId> StateIdSet;
typedef std::set<int64> OfstSymbolSet;

const StateIdNumber NO_ID_NUMBER = UINT_MAX;
const StateId NO_STATE_ID = UINT_MAX;
const SymbolNumber BIG_STATE_LIMIT = 1;


struct transition_label
{
  int64 input_symbol;
  int64 output_symbol;
};

struct compare_transition_labels 
{
  bool operator() ( const transition_label &l1,
            const transition_label &l2) const
  {
    if (l1.input_symbol == l2.input_symbol)
        return l1.output_symbol < l2.output_symbol;
    return l1.input_symbol < l2.input_symbol;
  }
};

typedef std::set<transition_label,compare_transition_labels> LabelSet;

enum place_holder {EMPTY, EMPTY_START, OCCUPIED_START, OCCUPIED };
typedef std::vector<place_holder> PlaceHolderVector;

/*
  A class which can translate between StateId and StateIdNumbers
*/
class ConvertIdNumberMap
{
private:
  typedef std::map<StateIdNumber,StateId> IdNumbersToStateIds;
  typedef std::map<StateId,StateIdNumber> StateIdsToIdNumbers;
  
  IdNumbersToStateIds id_to_node;
  StateIdsToIdNumbers node_to_id;
  
  StateIdNumber node_counter;

  void add_node(StateId n, TransduceR *tr);
  /*
    Assign every node n in t a unique id number i. Assign the start node 
    t->root_node() id number 0. Set node_to_id[n] = i and
    id_to_node[i] = n.
  */
  void set_node_maps(TransduceR * t);

public:
  ConvertIdNumberMap(TransduceR * t):
    node_counter(0)
  { set_node_maps(t); }
  
  StateIdNumber get_number_of_nodes(void) const
  { return node_counter; }
  
  StateIdNumber get_node_id(StateId n) const;
  StateId get_id_node(StateIdNumber i) const;
};

typedef std::map<int64,unsigned int> OfstSymbolCountMap;
typedef std::set<std::string> SymbolSet;

class ConvertTransducerAlphabet
{
 private:
  SymbolTable symbol_table;
  
  TransduceR* transducer;
  fst::SymbolTable * ofst_symbol_table;
  // input and output symbol tables together
  
  std::map<int64, SymbolNumber> input_symbols_map;
  std::map<int64, SymbolNumber> output_symbols_map;
  
  void inspect_node(StateId n, StateIdSet& visited_nodes,
    OfstSymbolCountMap& symbol_count_map, SymbolSet& all_symbol_set);
  void get_symbol_info(
      OfstSymbolCountMap &symbol_count_map, SymbolSet& all_symbol_set);
  void populate_symbol_table(
      OfstSymbolCountMap &input_symbol_counts, SymbolSet& all_symbol_set);
  void set_maps();
 public:
  ConvertTransducerAlphabet(TransduceR* t);
  
  void display() const;
  
  const SymbolTable& get_symbol_table() const {return symbol_table;}
  SymbolNumber lookup_ofst_input_symbol(int64 s) const;
  SymbolNumber lookup_ofst_output_symbol(int64 s) const;
  bool is_flag_diacritic(SymbolNumber symbol) const;
  
  TransducerAlphabet to_alphabet() const;
};

class ConvertTransition
{
private:
  SymbolNumber input_symbol;
  SymbolNumber output_symbol;
  // initially we only know the StateIdNumber of the target, but once the
  // tables have been laid out we can just store the state's table index
  union
  {
    StateIdNumber target_state_id;
    TransitionTableIndex target_state_index;
  };
  Weight weight;
  
  TransitionTableIndex table_index; // location in the transition table
public:
  /* 
     Set the symbol numbers and set the indices of the states according
     to ConvertIdNumberMap nodes_to_id_numbers.
  */
  ConvertTransition(const StdArc &a);
  
  void display() const;
  
  SymbolNumber get_input_symbol(void) const
  { return input_symbol; }
  
  void set_target_state_index();
  
  void set_table_index(TransitionTableIndex i)
  { table_index = i; }
  
  TransitionTableIndex get_table_index(void) const
  { return table_index; }
  
  template<class T> T to_transition() const;
  
  bool numerical_cmp( const ConvertTransition &another_transition) const;
  bool operator<(const ConvertTransition &another_index) const;
};

class ConvertTransitionIndex
{
private:
  SymbolNumber input_symbol;
  // initially we only have the corresponding transition object, but once the
  // tables have been laid out we can just store the transition's table index
  union
  {
    ConvertTransition* first_transition;
    TransitionTableIndex first_transition_index;
  };
public:
  ConvertTransitionIndex(SymbolNumber input, ConvertTransition* transition):
    input_symbol(input), first_transition(transition) {}
  
  void display() const;
  
  SymbolNumber get_input_symbol(void) const
  { return input_symbol; }
  
  ConvertTransition* get_first_transition() const
  { return first_transition; }
  
  void set_first_transition_index(TransitionTableIndex i)
  { first_transition_index = i; }
  
  template<class T> T to_transition_index() const;
  
  bool operator<(const ConvertTransitionIndex &another_index) const;
};

struct ConvertTransitionCompare
{
  bool operator() (const ConvertTransition * t1,
           const ConvertTransition * t2) const 
  { 
    return t1->operator<(*t2); 
  }
};

struct ConvertTransitionIndexCompare
{
  bool operator() (const ConvertTransitionIndex * i1,
           const ConvertTransitionIndex * i2) const 
  {
    return i1->operator<(*i2); 
  }
};

typedef std::set<ConvertTransition*,ConvertTransitionCompare>
    ConvertTransitionSet;
typedef std::set<ConvertTransitionIndex*,ConvertTransitionIndexCompare>
    ConvertTransitionIndexSet;

class ConvertFstState
{
private:
  ConvertTransitionSet transitions;
  ConvertTransitionIndexSet transition_indices;
  
  // the location in the transition table of the state's first transition. For
  // states without transitions, this is where the first transition *would* be
  TransitionTableIndex first_transition_index;
  // the location in the table tables where the state's transition indices
  // begin the state's location in the index tables. This can be either in the
  // transition index table, or, if the state only has transitions with
  // one input symbol, in the transition table, immediately preceding
  // the first transition
  TransitionTableIndex table_index;
  
  bool final;
  Weight weight;
  
  StateIdNumber id;
  
  void set_transitions(StateId n, TransduceR * tr);
  void set_transition_indices(void);
  
  friend class fst_state_compare;
public:
  ConvertFstState(StateId n, TransduceR * tr);
  ~ConvertFstState();
  
  void display() const;
  
  TransitionTableIndex set_transition_table_indices(
      TransitionTableIndex place);
  
  TransitionTableIndex get_first_transition_index() const
  { return first_transition_index; }
  
  void set_table_index(TransitionTableIndex i)
  { table_index = i; }
  TransitionTableIndex get_table_index(void) const
  { return table_index; }
    
  SymbolNumberSet * get_input_symbols(void) const;
  
  SymbolNumber number_of_input_symbols(void) const
  { return transition_indices.size(); }
  SymbolNumber number_of_transitions(void) const
  { return transitions.size(); }
  bool is_final(void) const {return final;}
  bool is_big_state(void) const
  {
      return (transition_indices.size() > BIG_STATE_LIMIT);
  }
  bool is_start_state(void) const {return id == 0;}
  StateIdNumber get_id(void) const {return id;}
  
  // update transitions with the state's location in the tables
  void set_transition_target_indices();
  
  // add this state's transition indices into the given transition index table
  template<class T>
  void insert_transition_indices(TransducerTable<T>& index_table) const;
  
  template<class T>
  TransitionTableIndex append_transitions(TransducerTable<T>& transition_table, 
                                          TransitionTableIndex place) const;
};

 typedef std::vector<ConvertFstState*> ConvertFstStateVector;

class ConvertTransitionTableIndices 
{
private:
  PlaceHolderVector indices;
  PlaceHolderVector::size_type lower_bound;
  unsigned int lower_bound_test_count;
  SymbolNumber number_of_input_symbols;
  
  bool state_fits(SymbolNumberSet * input_symbols,
          bool final_state,
          PlaceHolderVector::size_type index);

  void insert_state(SymbolNumberSet * input_symbols,
            bool final_state,
            PlaceHolderVector::size_type index);
  void get_more_space(void);
public:
  ConvertTransitionTableIndices(SymbolNumber input_symbol_count):
    lower_bound(0), lower_bound_test_count(0),
    number_of_input_symbols(input_symbol_count)
  {
    get_more_space();
  };
  
  PlaceHolderVector::size_type add_state(ConvertFstState * state);
  PlaceHolderVector::size_type size(void) const
  { return indices.size(); }

  PlaceHolderVector::size_type last_full_index(void) const;
};

class ConvertTransducerHeader
{
 private:
  static void full_traversal(TransducerHeader& h, TransduceR* tr, StateId n,
         StateIdSet& visited_nodes, StateIdSet& nodes_in_path,
                 OfstSymbolSet& all_input_symbols);
  static void find_input_epsilon_cycles(StateId n, StateId t,
                    StateIdSet &epsilon_targets,
                    bool unweighted_only, TransduceR * tr,
                    TransducerHeader& h);
 public:
  static void compute_header(TransducerHeader& header,
      TransduceR * t, SymbolNumber symbol_count,
        TransitionTableIndex number_of_index_table_entries,
        TransitionTableIndex number_of_target_table_entries,
        bool weighted);
};

class ConvertTransducer
{
private:
  TransduceR * fst;
  ConvertIdNumberMap * id_number_map;
  ConvertTransitionTableIndices * fst_indices;
  PlaceHolderVector::size_type index_table_size;
  
  TransducerHeader header;
  ConvertTransducerAlphabet alphabet;
  ConvertFstStateVector states;
  
  void read_nodes(void);
  void set_transition_table_indices(void);
  void set_index_table_indices(void);
  
  void add_input_symbols(StateId n,
             SymbolNumberSet &input_symbols,
             StateIdSet &visited_nodes);
  SymbolNumber number_of_input_symbols(void);
  
  TransitionTableIndex count_transitions(void) const;
  
  void display_states() const;
  void display_tables() const;
  
  template<class T> TransducerTable<T> make_index_table(
      TransitionTableIndex index_table_size) const;
  template<class T> TransducerTable<T> make_transition_table() const;
public:
  ConvertTransducer(TransduceR * tr, bool weighted);
  ~ConvertTransducer();
  
  ConvertIdNumberMap& get_id_number_map() {return *id_number_map;}
  ConvertTransducerAlphabet& get_alphabet() {return alphabet;}
  ConvertFstState& get_state(StateIdNumber s) {return *states[s];}
  bool is_weighted() const {return header.probe_flag(Weighted);}
  
  Transducer* to_transducer() const;
  
  // exposed to this module during the constructor
  static ConvertTransducer* constructing_transducer; 
};

#endif // HAVE_OPENFST

}

#endif // include guard
