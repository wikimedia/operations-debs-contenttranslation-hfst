#ifndef HEADER_SequenceModelComponent_h
#define HEADER_SequenceModelComponent_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <vector>

#include "HfstTransducer.h"

using hfst::implementations::HfstBasicTransducer;

#include "DataTypes.h"

class SequenceModelComponent
{
 public:
  SequenceModelComponent(void);
  SequenceModelComponent(const HfstBasicTransducer &fst);
  virtual ~SequenceModelComponent(void);

  static const State START_STATE;

  virtual Weight get_final_weight(State state) const;
  virtual TransitionData get_transition(State state, Symbol symbol);

  static Symbol get_symbol(const std::string &string_symbol);
  static std::string get_string_symbol(Symbol symbol);
  
  virtual void clear(void);

 protected:
  static Symbol2NumberMap symbol_to_number_map;
  static Number2SymbolMap number_to_symbol_map;
  
  StateFinalWeightMap state_final_weight_map;
  TransitionMap       transition_map;

  static void add_symbols_from(const HfstBasicTransducer &fst);
  static void add_symbol(const std::string &string_symbol);

  void add_state_final_weights_from(const HfstBasicTransducer &fst);
  void add_transitions_from(const HfstBasicTransducer &fst);

  void add_transition_to_map(Symbol2TransitionDataMap &symbol_to_transition,
			     Symbol symbol,
			     Weight weight,
			     State target);

  State add_state(Weight final_weight);
};

#endif // HEADER_SequenceModelComponent_h
