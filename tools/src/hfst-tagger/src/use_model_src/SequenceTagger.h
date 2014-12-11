#ifndef HEADER_SequenceTagger_h
#define HEADER_SequenceTagger_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <queue>

#include "SequenceModelComponent.h"
#include "SentenceTransducer.h"
#include "DataTypes.h"
#include "AcyclicAutomaton.h"

class SequenceTagger
{
 public:
  SequenceTagger(SequenceModelComponent &sequence_model_component);
  ~SequenceTagger(void);
  WeightedStringPairVector operator[]
    (const SentenceTransducer &sentence_transducer);
 private:

  typedef std::pair<State,State> StatePair;
  typedef std::queue<StatePair> Agenda;
  typedef std::map<StatePair,State> StatePair2StateMap;
  typedef std::vector<StatePair> State2StatePairMap;

  SequenceModelComponent &sequence_model_component;

  StatePair2StateMap state_pair_to_state_map;
  State2StatePairMap state_to_state_pair_map;
  AcyclicAutomaton result;

  Agenda agenda;

  size_t states;
  size_t sentences;

  void process_configuration(const SentenceTransducer &sentence_transducer,
			     const StatePair &configuration,
			     State result_state,
			     AcyclicAutomaton &result);

  WeightedStringPairVector 
    get_weighted_analysis(AcyclicAutomaton &result) const;

  State get_state(const StatePair &configuration,
		  const SentenceTransducer &sentence_transducer,
		  AcyclicAutomaton &result);
};

#endif // HEADER_SequenceTagger_h
