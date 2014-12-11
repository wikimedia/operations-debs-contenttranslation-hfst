#ifndef COMPOSE_INTERSECT_LEXICON_H
#define COMPOSE_INTERSECT_LEXICON_H

#include <queue>

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
      typedef std::vector<StatePair> PairVector;
      typedef std::queue<HfstState> StateQueue;

      StatePairMap state_pair_map;
      PairVector   pair_vector;
      StateQueue   agenda;
      HfstBasicTransducer result;

      bool is_flag_diacritic(size_t);
      HfstState get_state(const StatePair &);
      StatePair get_pair(HfstState);
      void clear_all_info(void);
      HfstState map_state_and_add_to_agenda(const StatePair &);
      HfstBasicTransducer &compute_composition_result
    (ComposeIntersectRule *);
      void compute_state(HfstState state,ComposeIntersectRule *);
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
