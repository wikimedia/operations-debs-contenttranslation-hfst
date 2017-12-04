#ifndef HEADER_AcyclicAutomaton_h
#define HEADER_AcyclicAutomaton_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "DataTypes.h"

#include <vector>
#include <limits>

#define WORD_STATE_RESERVED_LENGTH 500
#define SENTENCE_RESERVED_LENGTH 500

class AcyclicState
{
 public:
  AcyclicState(size_t id);
  void add_transition(size_t source_id,Symbol symbol,Weight weight);
  Symbol get_symbol(void) const;
  Weight get_weight(void) const;
  void set_weight(Weight w);
  size_t get_source(void) const;
  bool is_initialized(void);
  void clear(void);
 private:
  size_t id;
  size_t source_id;
  Symbol symbol;
  Weight weight;
};

class AcyclicAutomaton
{
 public:
  AcyclicAutomaton(void);

  void add_transition(State source,Symbol symbol,Weight weight,State target);
  State add_state(void);
  void finalize_position(void);
  void set_final_weight(State s, Weight weight);
  void clear(void);
  WeightedSymbolVector get_best_path(void);

 private:
  typedef std::vector<AcyclicState> AcyclicStateVector;
  typedef std::vector<AcyclicStateVector> Data;
  typedef std::vector<size_t> State2IdMap;

  AcyclicStateVector default_position;
  Data data;
  State2IdMap state_to_id_map;
  size_t current_position;
  size_t current_id;

  void initialize(void);
  SymbolVector get_path(size_t id) const;
};

#endif // HEADER_AcyclicAutomaton_h
