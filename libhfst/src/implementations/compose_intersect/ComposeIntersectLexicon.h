// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.
#ifndef COMPOSE_INTERSECT_LEXICON_H
#define COMPOSE_INTERSECT_LEXICON_H

#include <queue>
#include <set>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "ComposeIntersectFst.h"
#include "ComposeIntersectRulePair.h"

namespace hfst
{
  namespace implementations
  {
    class ComposeIntersectLexicon : public ComposeIntersectFst
    {
    public:
      typedef ComposeIntersectFst::SymbolTransitionMap SymbolTransitionMap;
      ComposeIntersectLexicon(const HfstBasicTransducer &);
      ComposeIntersectLexicon(void);
      HfstBasicTransducer compose_with_rules(ComposeIntersectRule *);
    protected:
      typedef std::pair<HfstState,HfstState> StatePair;
      typedef std::map<StatePair,HfstState> StatePairMap;
      typedef std::set<HfstState> StateSet;

      typedef std::vector<StatePair> PairVector;
      typedef std::queue<HfstState> StateQueue;


      StatePairMap state_pair_map;
      PairVector   pair_vector;
      StateQueue   agenda;
      HfstBasicTransducer result;
      StateSet lexicon_non_epsilon_states;

      bool is_flag_diacritic(size_t);
      HfstState get_state(const StatePair &, bool allow_lexicon_epsilons=true);
      StatePair get_pair(HfstState);
      void clear_all_info(void);
      HfstState map_state_and_add_to_agenda(const StatePair &,
                                            bool allow_lexicon_epsilons);
      HfstBasicTransducer &compute_composition_result
    (ComposeIntersectRule *);
      void compute_state(HfstState state,ComposeIntersectRule *,
                         bool allow_lexicon_epsilons);
      bool can_have_lexicon_epsilons(HfstState s);
      void set_final_state_weights(ComposeIntersectRule *);
      void lexicon_skip_symbol_compose
    (const TransitionSet &,HfstState,HfstState);
      void rule_skip_symbol_compose(const TransitionSet &,HfstState,HfstState);
      void compose(const TransitionSet &,const TransitionSet &,HfstState);
      void add_transition
    (HfstState, size_t,size_t,float,HfstState);
      void identity_compose
    (const TransitionSet &,const HfstBasicTransition &,HfstState);
    };
  }
}

#endif
