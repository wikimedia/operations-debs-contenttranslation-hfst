#ifndef HEADER_DelayedSequenceModelComponent_h
#define HEADER_DelayedSequenceModelComponent_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "SequenceModelComponent.h"

class DelayedSequenceModelComponent : public SequenceModelComponent
{
 public:
  DelayedSequenceModelComponent(SequenceModelComponent &model,
				size_t delay);
  
  Weight get_final_weight(State state) const;
  TransitionData get_transition(State state, Symbol symbol);

 protected:
  SequenceModelComponent &model;
  size_t delay;

};

#endif // HEADER_DelayedSequenceModelComponent_h
