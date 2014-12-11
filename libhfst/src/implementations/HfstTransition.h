#ifndef _HFST_TRANSITION_H_
#define _HFST_TRANSITION_H_

/** @file HfstTransition.h 
    @brief Class HfstTransition */

#include "../HfstDataTypes.h"

namespace hfst {

  namespace implementations {

   /** @brief A transition that consists of a target state and 
        transition data represented by class C. 

	The easiest way to use this template is to choose the 
	the implementation #HfstBasicTransition which is compatible with
	#HfstBasicTransducer.
	
	@see HfstBasicTransition
   */
    template <class C> class HfstTransition 
      {
      protected:
        HfstState target_state; // the state where the transition leads
        C transition_data;      // the actual transition data
	
	/* Get the number that represents the symbol in the transition data. */
	static unsigned int get_symbol_number
	  (const typename C::SymbolType &symbol) {
	  return C::get_symbol_number(symbol);
	}
	
      public:
	
        /** @brief Create a transition leading to state zero with input and
            output symbols and weight as given by default constructors
            of C::SymbolType and C::WeightType. */
      HfstTransition(): target_state(0)
          {}
	
        /** @brief Create a transition leading to state \a s with input symbol
            \a isymbol, output_symbol \a osymbol and weight \a weight. */
      HfstTransition(HfstState s, 
		     typename C::SymbolType isymbol, 
		     typename C::SymbolType osymbol, 
		     typename C::WeightType weight):
        target_state(s), transition_data(isymbol, osymbol, weight)
          {}
	
      HfstTransition(HfstState s, 
		     unsigned int inumber, 
		     unsigned int onumber, 
		     typename C::WeightType weight,
		     bool foo):
        target_state(s), transition_data(inumber, onumber, weight)
          { (void)foo; }
	
        /** @brief Create a deep copy of transition \a another. */
      HfstTransition(const HfstTransition<C> &another): 
        target_state(another.target_state), 
          transition_data(another.transition_data) 
	    {}
	
        /** @brief Whether this transition is less than transition \a
            another. Needed for storing transitions in a set. */
        bool operator<(const HfstTransition<C> &another) const {
          if (target_state == another.target_state)
            return (transition_data < another.transition_data);
          return (target_state < another.target_state);
	}
	
        /** @brief Assign this transition the same value as transition 
            \a another. */
        void operator=(const HfstTransition<C> &another) {
          target_state = another.target_state;
          transition_data = another.transition_data;
        }
	
        /** @brief Get the target state of the transition. */
        HfstState get_target_state() const {
          return target_state;
        }
	
        /** @brief Get the transition data of the transition. */
        const C & get_transition_data() const {
          return transition_data;
        }
	
        /** @brief Get the input symbol of the transition. */
        typename C::SymbolType get_input_symbol() const {
          return transition_data.get_input_symbol();
        }
    
        /** @brief Get the output symbol of the transition. */
        typename C::SymbolType get_output_symbol() const {
          return transition_data.get_output_symbol();
        }

	/* Get the internal input number of the transition. */
	unsigned int get_input_number() const {
	  return transition_data.get_input_number();
	}

	/* Get the internal output number of the transition. */
	unsigned int get_output_number() const {
	  return transition_data.get_output_number();
	}

        /** @brief Get the weight of the transition. */
        typename C::WeightType get_weight() const {
          return transition_data.get_weight();
        }

        friend class ComposeIntersectFst;
        friend class ComposeIntersectLexicon;
        friend class ComposeIntersectRule;
        friend class ComposeIntersectRulePair;
      };

    /** @brief An HfstTransition with transition data of type
        HfstTropicalTransducerTransitionData. 

        This implementation is compatible with #HfstBasicTransducer.

        @see HfstTropicalTransducerTransitionData HfstBasicTransducer */
    typedef HfstTransition<HfstTropicalTransducerTransitionData> 
      HfstBasicTransition;

    /** @brief An HfstTransition with transition data of type
        HfstFastTransitionData. 

        This implementation is compatible with #HfstFastTransducer.

        @see HfstFastTransitionData HfstFastTransducer */
    typedef HfstTransition<HfstFastTransitionData> HfstFastTransition;

  }

}

#endif // _HFST_TRANSITION_H_
