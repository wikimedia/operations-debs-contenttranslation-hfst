// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.
#ifndef COMPOSE_INTERSECT_RULE_PAIR_H
#define COMPOSE_INTERSECT_RULE_PAIR_H

#include <map>
#include <string>
#include <vector>
#include <string>

#include "ComposeIntersectRule.h"

namespace hfst
{
  namespace implementations
  {

    class ComposeIntersectRulePair : public ComposeIntersectRule
    {
    public:
      typedef ComposeIntersectRule::TransitionSet TransitionSet;
      
      static const HfstState START; // = 0;
      
      ComposeIntersectRulePair(ComposeIntersectRule *,ComposeIntersectRule *);
      
      ~ComposeIntersectRulePair(void);

      virtual const TransitionSet &get_transitions(HfstState,size_t);

      float get_final_weight(HfstState) const;

#ifdef MAIN_TEST
      std::ostream &print(std::ostream &);
#endif
      
    protected:
      typedef std::pair<HfstState,HfstState> StatePair;
      typedef std::vector<StatePair> StatePairVector;
      typedef std::map<StatePair,HfstState> PairStateMap;
      typedef std::map<size_t,TransitionSet> SymbolTransitionMap;
      typedef std::vector<SymbolTransitionMap> StateTransitionVector;

      StatePairVector state_pair_vector;
      PairStateMap pair_state_map;
      
      StateTransitionVector state_transition_vector;

      ComposeIntersectRule * fst1;
      ComposeIntersectRule * fst2;

      bool has_state(HfstState s) const;
      bool has_pair(const StatePair&) const;
      bool transitions_computed(HfstState,size_t);
      void compute_transition_set(HfstState,size_t);
      HfstState get_state(const StatePair &);
      void add_transition
    (TransitionSet &,HfstState target,size_t,size_t,float);
    };
  }
}

#endif
