#ifndef HEADER_SequenceModelComponentPair_h
#define HEADER_SequenceModelComponentPair_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <utility>
#include <map>

#include "SequenceModelComponent.h"

class SequenceModelComponentPair : public SequenceModelComponent
{
 public:
  SequenceModelComponentPair(SequenceModelComponent &component1,
			     SequenceModelComponent &component2);

  Weight get_final_weight(State state) const;
  TransitionData get_transition(State state, Symbol symbol); 

  virtual void clear(void);

 protected:

  typedef std::pair<State,State> StatePair;
  
  class StatePair2StateMap
  {
  public:
    size_t count(const StatePair &p);
    State &operator[](const StatePair &p);
    size_t size(void);
    void clear(void);
  private:
    typedef std::vector<State> StateVector;
    typedef std::vector<StateVector> StateVectorVector;

    StateVectorVector state_pair_to_state_map_;
  };
  
  //typedef std::map<StatePair,State> StatePair2StateMap;

  typedef std::vector<StatePair> State2StatePairMap;

  SequenceModelComponent &component1;
  SequenceModelComponent &component2;
  StatePair2StateMap           state_pair_to_state_map;
  State2StatePairMap           state_to_state_pair_map;

  State get_state(const StatePair &state_pair);
};

#endif // HEADER_SequenceModelComponentPair_h
