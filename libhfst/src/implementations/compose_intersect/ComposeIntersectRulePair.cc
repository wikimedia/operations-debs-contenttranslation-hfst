// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.
#include "ComposeIntersectRulePair.h"

#ifndef MAIN_TEST

namespace hfst
{
  namespace implementations
  {
    const HfstState ComposeIntersectRulePair::START = 0;
    
    ComposeIntersectRulePair::ComposeIntersectRulePair
    (ComposeIntersectRule * fst1,ComposeIntersectRule * fst2):
      fst1(fst1),
      fst2(fst2)
    {
      ComposeIntersectRule::symbol_set = fst1->get_symbols();

      pair_state_map[StatePair(ComposeIntersectRule::START,
                   ComposeIntersectRule::START)] = START;

      state_pair_vector.push_back(StatePair(ComposeIntersectRule::START,
                        ComposeIntersectRule::START));

      state_transition_vector.push_back(SymbolTransitionMap());
    }

    ComposeIntersectRulePair::~ComposeIntersectRulePair(void)
    {
      delete fst1;
      delete fst2;
    }

    const ComposeIntersectRulePair::TransitionSet &
    ComposeIntersectRulePair::get_transitions
    (HfstState s,size_t symbol)
    {
      if (! has_state(s))
    { HFST_THROW(StateNotDefined); }
      if (! transitions_computed(s,symbol))
    { compute_transition_set(s,symbol); }
      return state_transition_vector[s][symbol];
    }
    
    bool ComposeIntersectRulePair::has_state(HfstState s) const
    { return s < state_pair_vector.size(); }
    
    bool ComposeIntersectRulePair::has_pair
    (const ComposeIntersectRulePair::StatePair &p) const
    { return pair_state_map.find(p) != pair_state_map.end(); }
    
    bool ComposeIntersectRulePair::transitions_computed
    (HfstState state,size_t symbol)
    { return state_transition_vector.at(state).find(symbol)
    != state_transition_vector.at(state).end(); }
    
    HfstState ComposeIntersectRulePair::get_state(const StatePair &p)
    {
      if (! has_pair(p))
    {
      pair_state_map[p] = hfst::size_t_to_uint(state_pair_vector.size());
      state_pair_vector.push_back(p);
      state_transition_vector.push_back(SymbolTransitionMap());
      return hfst::size_t_to_uint(state_pair_vector.size() - 1);
    }
      return pair_state_map[p];
    }

    void ComposeIntersectRulePair::add_transition
    (TransitionSet &transitions,HfstState target,size_t input_symbol,
     size_t output_symbol,float weight)
    {
      transitions.insert
    (Transition(target,input_symbol,output_symbol,weight));
    }

    float ComposeIntersectRulePair::get_final_weight(HfstState s) const
    {
      if (! has_state(s))
    { HFST_THROW(StateNotDefined); }
      const StatePair &state_pair = state_pair_vector[s];
      return fst1->get_final_weight(state_pair.first) +
    fst2->get_final_weight(state_pair.second);
    }

    void ComposeIntersectRulePair::compute_transition_set
    (HfstState state, size_t symbol)
    {
      StatePair state_pair = state_pair_vector[state];
      const ComposeIntersectRule::TransitionSet &fst1_transitions =
    fst1->get_transitions(state_pair.first,symbol);
      ComposeIntersectRule::TransitionSet::const_iterator it =
    fst1_transitions.begin();
      const ComposeIntersectRule::TransitionSet &fst2_transitions =
    fst2->get_transitions(state_pair.second,symbol);
      ComposeIntersectRule::TransitionSet::const_iterator jt =
    fst2_transitions.begin();
 
      (void)state_transition_vector[state][symbol];
      TransitionSet transitions;
      while (it != fst1_transitions.end() && jt != fst2_transitions.end())
    {
      if (it->olabel == jt->olabel)
        {
          size_t output = it->olabel;
          HfstState target = get_state(StatePair(it->target,jt->target));
          float weight = it->weight + jt->weight;
          add_transition(transitions,target,symbol,output,weight);
          ++it; ++jt;
        }
      else if (it->olabel < jt->olabel)
        { ++it; }
      else
        { ++jt; }
    }
      state_transition_vector[state][symbol] = transitions;
    }
  }
}

#else // MAIN_TEST was defined

#include "HfstTokenizer.h"
#include "HfstTransducer.h"

using namespace hfst;
using hfst::implementations::ComposeIntersectRule;
using hfst::implementations::ComposeIntersectRulePair;

std::ostream &ComposeIntersectRulePair::print(std::ostream &out)
{
  HfstState s = ComposeIntersectRulePair::START;
  while (1)
    {
      for (ComposeIntersectRule::SymbolSet::const_iterator it =
         ComposeIntersectRule::symbol_set.begin();
       it != ComposeIntersectRule::symbol_set.end();
       ++it)
    {
      const TransitionSet &transitions = get_transitions(s,*it);
      for (TransitionSet::const_iterator jt = transitions.begin();
           jt != transitions.end();
           ++jt)
        {
          out << s << "\t"
          << jt->target << "\t"
          << HfstTropicalTransducerTransitionData::get_symbol(jt->ilabel) << "\t"
          << HfstTropicalTransducerTransitionData::get_symbol(jt->olabel) << "\t"
          << jt->weight << std::endl;
        }
    }
      out << s << "\t" << get_final_weight(s) << std::endl;
      ++s;
      if (! has_state(s))
    { break; }
    }
  return out;
}

std::ostream &operator<<
(std::ostream &out,ComposeIntersectRulePair &p)
{ return p.print(out); }

#include <cassert>
#include <sstream>

int main(int argc, char * argv[])
{
    std::cout << "Unit tests for " __FILE__ ":" << std::endl;

  HfstTokenizer tokenizer;
  HfstTransducer a("a",tokenizer,TROPICAL_OPENFST_TYPE);
  a.set_final_weights(1);
  HfstTransducer aa("aa",tokenizer,TROPICAL_OPENFST_TYPE);
  aa.set_final_weights(0.5);
  HfstTransducer aaa("aaa",tokenizer,TROPICAL_OPENFST_TYPE);
  aaa.set_final_weights(0.25);
  a.repeat_star().minimize();
  aa.repeat_star().minimize();
  aaa.repeat_star().minimize();

  ComposeIntersectRulePair compose_intersect_rule_pair
    (new ComposeIntersectRule(aaa),new ComposeIntersectRulePair
     (new ComposeIntersectRule(a),new ComposeIntersectRule(aa)));
/*  try
    {
      compose_intersect_rule_pair.get_transitions(100,"a");
      assert(0);
    }
  catch (const StateNotDefined &e)
  { std::cerr << e() << std::endl; } */ // FIXME get_transitions wants size_t as second argument

  
  std::string str;
  std::stringstream sstr(str);
  sstr << "Print:" << std::endl;
  sstr << compose_intersect_rule_pair << std::endl;

  std::cout << "ok" << std::endl;

  return 0;
}
#endif // MAIN_TEST
