#include "SequenceModelComponentPair.h"

#ifndef MAIN_TEST

size_t 
SequenceModelComponentPair::StatePair2StateMap::count(const StatePair &p)
{
  if (static_cast<int>(state_pair_to_state_map_.size()) <= p.first)
    { return 0; }
  if (static_cast<int>(state_pair_to_state_map_[p.first].size()) <= p.second)
    { return 0; }

  return state_pair_to_state_map_[p.first][p.second] == -1 ? 0 : 1; 
}

State &
SequenceModelComponentPair::StatePair2StateMap::operator[](const StatePair &p)
{
  while (static_cast<int>(state_pair_to_state_map_.size()) <= p.first)
    { 
      state_pair_to_state_map_.insert(state_pair_to_state_map_.end(),
                                      state_pair_to_state_map_.size() + 1,
                                      StateVector()); 
    }

  StateVector &state_vector = state_pair_to_state_map_[p.first];

  while (static_cast<int>(state_vector.size()) <= p.second)
    { state_vector.insert(state_vector.end(),state_vector.size() + 1,-1); }

  return state_vector[p.second];
}

size_t SequenceModelComponentPair::StatePair2StateMap::size(void)
{ return state_pair_to_state_map_.size(); }

void SequenceModelComponentPair::StatePair2StateMap::clear(void)
{
  state_pair_to_state_map_.clear();
}

void SequenceModelComponentPair::clear(void)
{
  component1.clear();
  component2.clear();

  state_pair_to_state_map.clear();
  state_to_state_pair_map.clear();

  (void)get_state(StatePair(0,0)); 
}

SequenceModelComponentPair::SequenceModelComponentPair
(SequenceModelComponent &component1,
 SequenceModelComponent &component2):
  component1(component1),
  component2(component2)
{ (void)get_state(StatePair(0,0)); }

Weight SequenceModelComponentPair::get_final_weight(State state) const
{
#ifndef OPTIMIZE_DANGEROUSLY
  if (state >= static_cast<int>(state_to_state_pair_map.size()))
    { throw InvalidState(); }
#endif // OPTIMIZE_DANGEROUSLY

  StatePair state_pair = state_to_state_pair_map[state];
  
  
  return 
    component1.get_final_weight(state_pair.first) + 
    component2.get_final_weight(state_pair.second); 
}

TransitionData SequenceModelComponentPair::get_transition
(State state, Symbol symbol)
{
#ifndef OPTIMIZE_DANGEROUSLY
  if (state >= static_cast<int>(state_to_state_pair_map.size()))
    { throw InvalidState(); }
#endif // OPTIMIZE_DANGEROUSLY

  StatePair state_pair = state_to_state_pair_map[state];
  
  TransitionData transition_data1 = 
    component1.get_transition(state_pair.first,symbol);

  TransitionData transition_data2 = 
    component2.get_transition(state_pair.second,symbol);

  StatePair target_pair(transition_data1.target, transition_data2.target);

  State target = get_state(target_pair);
  
  TransitionData transition_data;
  transition_data.target = target;
  transition_data.weight = transition_data1.weight + transition_data2.weight;

  return transition_data;
}

State SequenceModelComponentPair::get_state(const StatePair &state_pair)
{
  if (state_pair_to_state_map.count(state_pair) == 0)
    { 
      state_pair_to_state_map[state_pair] = state_to_state_pair_map.size();
      state_to_state_pair_map.push_back(state_pair);

      return state_to_state_pair_map.size() - 1;
    }

  return state_pair_to_state_map[state_pair];
}

#else // MAIN_TEST
#include <cassert>
#include <iostream>

#include "DelayedSequenceModelComponent.h"

using hfst::HfstTransducer;
using hfst::TROPICAL_OPENFST_TYPE;

int main(void)
{
  bool enc = hfst::get_encode_weights();
  hfst::set_encode_weights(false); // TEST

  HfstTransducer a("a",TROPICAL_OPENFST_TYPE);
  HfstTransducer def(DEFAULT_SYMBOL,TROPICAL_OPENFST_TYPE);
  HfstTransducer b("b",TROPICAL_OPENFST_TYPE);

  def.set_final_weights(10.0);
  a.set_final_weights(1.0);
  b.set_final_weights(2.0);

  a.disjunct(def).minimize();
  b.disjunct(def).minimize();

  SequenceModelComponent m1(a);
  SequenceModelComponent m2(b);
  DelayedSequenceModelComponent dm2(m2,0);

  SequenceModelComponentPair mp(m1,dm2);

  float infinity = std::numeric_limits<float>::infinity();

  assert(mp.get_final_weight(0) == infinity);

  assert(mp.get_transition
         (0,
          SequenceModelComponent::get_symbol("a")).target == 1);

  assert(mp.get_transition
         (0,
          SequenceModelComponent::get_symbol("a")).weight +
         mp.get_final_weight(1) == static_cast<float>(11.0));

  assert(mp.get_transition
         (0,
          SequenceModelComponent::get_symbol("b")).weight +
         mp.get_final_weight(1) == static_cast<float>(12.0));
  
  assert(mp.get_transition
         (0,
          SequenceModelComponent::get_symbol("c")).weight +
         mp.get_final_weight(1) == static_cast<float>(20.0));

  HfstTransducer c("c",TROPICAL_OPENFST_TYPE);
  c.set_final_weights(3.0).minimize();
  SequenceModelComponent m3(c);
  SequenceModelComponentPair mpp(m3,mp);

  assert(mpp.get_transition
         (0,
          SequenceModelComponent::get_symbol("c")).weight +
         mpp.get_final_weight(1) == static_cast<float>(23.0));

  hfst::set_encode_weights(enc); // TEST
}
#endif // MAIN_TEST
