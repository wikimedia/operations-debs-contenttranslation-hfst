#include "DelayedSequenceModelComponent.h"

#ifndef MAIN_TEST

DelayedSequenceModelComponent::DelayedSequenceModelComponent
(SequenceModelComponent &model,
 size_t delay):
  model(model),
  delay(delay)
{}

Weight DelayedSequenceModelComponent::get_final_weight(State state) const
{
  if (state < static_cast<int>(delay))
    { return 0.0; }
 
  return model.get_final_weight(state - delay);
}

TransitionData DelayedSequenceModelComponent::get_transition
(State state, Symbol symbol)
{
  TransitionData transition_data;

  if (state < static_cast<int>(delay))
    { 
      transition_data.weight = 0.0;
      transition_data.target = state + 1;
    }
  else
    {
      TransitionData internal_transition_data = 
	model.get_transition(state - delay, symbol); 

      transition_data.weight = internal_transition_data.weight;
      transition_data.target = internal_transition_data.target + delay;
    }
  return transition_data;
}

#else // MAIN_TEST

#include <cassert>
#include <iostream>

using hfst::implementations::HfstBasicTransition;

int main(void)
{
  // fst initially has one state.
  HfstBasicTransducer fst;

  // Add a state, so that a transition can be added.
  fst.add_state();

  // Add a transition from state 0 to state 1.
  fst.add_transition(0,HfstBasicTransition(1,"a","a",0.0));

  // Set state 1 final.
  fst.set_final_weight(1,2.0);

  SequenceModelComponent sequence_model_component(fst);

  // Test first with delay 0.
  DelayedSequenceModelComponent delayed_sequence_model_component_0
    (sequence_model_component,0);

  float infinity = std::numeric_limits<float>::infinity();

  assert(delayed_sequence_model_component_0.get_final_weight(0) == infinity);
  assert(delayed_sequence_model_component_0.get_final_weight(1) == 2.0);
  assert(delayed_sequence_model_component_0.
	 get_transition(0,SequenceModelComponent::get_symbol("a")).
	 target == 1);
  assert(delayed_sequence_model_component_0.
	 get_transition(0,SequenceModelComponent::get_symbol("a")).
	 weight == static_cast<float>(0.0));

  // The then with delay 2.
  DelayedSequenceModelComponent delayed_sequence_model_component_2
    (sequence_model_component,2);

  assert(delayed_sequence_model_component_2.get_final_weight(0) == 0.0);
  assert(delayed_sequence_model_component_2.get_final_weight(1) == 0.0);
  assert(delayed_sequence_model_component_2.get_final_weight(2) == infinity);
  assert(delayed_sequence_model_component_2.get_final_weight(3) == 2.0);
  assert(delayed_sequence_model_component_2.
	 get_transition(2,SequenceModelComponent::get_symbol("a")).
	 target == 3);
  assert(delayed_sequence_model_component_2.
	 get_transition(2,SequenceModelComponent::get_symbol("a")).
	 weight == static_cast<float>(0.0));

  SequenceModelComponent * smc = 
    &delayed_sequence_model_component_0;
  assert(smc->get_final_weight(0) == infinity);
  
  smc = 
    &delayed_sequence_model_component_2;
  assert(smc->get_final_weight(0) == 0.0);
}
#endif // MAIN_TEST
