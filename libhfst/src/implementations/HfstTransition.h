// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _HFST_TRANSITION_H_
#define _HFST_TRANSITION_H_

/** @file HfstTransition.h
    @brief Class HfstTransition */

#include "../HfstDataTypes.h"

#include "../hfstdll.h"

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
      HFSTDLL HfstTransition(): target_state(0)
          {}
        
        /** @brief Create a transition leading to state \a s with input symbol
            \a isymbol, output_symbol \a osymbol and weight \a weight. */
      HFSTDLL HfstTransition(HfstState s,
                     typename C::SymbolType isymbol,
                     typename C::SymbolType osymbol,
                     typename C::WeightType weight):
        target_state(s), transition_data(isymbol, osymbol, weight)
          {}
        
      HFSTDLL HfstTransition(HfstState s,
                     unsigned int inumber,
                     unsigned int onumber,
                     typename C::WeightType weight,
                     bool foo):
        target_state(s), transition_data(inumber, onumber, weight)
          { (void)foo; }
        
        /** @brief Create a deep copy of transition \a another. */
      HFSTDLL HfstTransition(const HfstTransition<C> &another):
        target_state(another.target_state),
          transition_data(another.transition_data)
            {}

        HFSTDLL ~HfstTransition() {}
        
        /** @brief Whether this transition is less than transition \a
            another. Needed for storing transitions in a set. */
        HFSTDLL bool operator<(const HfstTransition<C> &another) const {
          if (target_state == another.target_state)
            return (transition_data < another.transition_data);
          return (target_state < another.target_state);
        }
        
        /** @brief Assign this transition the same value as transition
            \a another. */
        HFSTDLL void operator=(const HfstTransition<C> &another) {
          target_state = another.target_state;
          transition_data = another.transition_data;
        }
        
        /** @brief Get the target state of the transition. */
        HFSTDLL HfstState get_target_state() const {
          return target_state;
        }
        
        /** @brief Get the transition data of the transition. */
        HFSTDLL const C & get_transition_data() const {
          return transition_data;
        }
        
        /** @brief Get the input symbol of the transition. */
        HFSTDLL typename C::SymbolType get_input_symbol() const {
          return transition_data.get_input_symbol();
        }
    
        /** @brief Get the output symbol of the transition. */
        HFSTDLL typename C::SymbolType get_output_symbol() const {
          return transition_data.get_output_symbol();
        }

        /* Get the internal input number of the transition. */
        HFSTDLL unsigned int get_input_number() const {
          return transition_data.get_input_number();
        }

        /* Get the internal output number of the transition. */
        HFSTDLL unsigned int get_output_number() const {
          return transition_data.get_output_number();
        }

        /** @brief Get the weight of the transition. */
        HFSTDLL typename C::WeightType get_weight() const {
          return transition_data.get_weight();
        }

       /** @brief Set the weight of the transition. */
        HFSTDLL void set_weight(float w) {
          transition_data.set_weight(w);
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

    // TODO: remove?
    typedef HfstTransition<HfstFastTransitionData> HfstFastTransition;

  }

}

#endif // _HFST_TRANSITION_H_
