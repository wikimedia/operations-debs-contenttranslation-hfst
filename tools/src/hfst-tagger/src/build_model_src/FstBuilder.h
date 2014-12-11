#ifndef HFST_TAGGER_HEADER_FST_BUILDER_H
#define HFST_TAGGER_HEADER_FST_BUILDER_H

//! @file FstBuilder.h
//!
//! @author Miikka Silfverberg
//!
//! @brief A base-class for other classes which read training data
//! from files and build fsts. Can't be used directly.

//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, version 3 of the Licence.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <vector>
#include <map>
#include <string>

#include "HfstTransducer.h"
#include "WeightedStringVectorCollection.h"

using hfst::implementations::HfstBasicTransducer;
using hfst::HfstTransducer;
using hfst::ImplementationType;
using hfst::implementations::HfstState;

#define START_STATE 0
#define NO_STATE    UINT_MAX

#include "string_handling.h"

class FstBuilder
{
 public:

  // Construct an fst of implementation type @a type with final
  // weights @a default_final_weight and whose name is @a name.
  FstBuilder(ImplementationType type,
	     float default_final_weight,
	     const std::string &name);

  // Return the transducer which was constructed.
  HfstTransducer get_model(void);

 protected:

  typedef std::vector<std::string> StringVector;
  typedef std::map<std::string,HfstState> SymbolTargetStateMap;

  ImplementationType type;
  float default_final_weight;
  std::string name;
  HfstBasicTransducer model_fst;
  SymbolTargetStateMap start_state_targets;
  
  void add_transition(HfstState initial_state,
		      HfstState target_state,
		      const std::string &symbol,
		      float weight);

  void add_transition(HfstState initial_state,
		      HfstState target_state,
		      const std::string &isymbol,
		      const std::string &osymbol,
		      float weight);

  bool has_target(HfstState s,
		  const std::string &symbol);

  HfstState get_target(HfstState s,
		       const std::string &symbol, 
		       bool &new_transition_required);
  StringVector split_at_tabs(const std::string &str);
  virtual void add_sequence(const WeightedStringVector &c,
			    weighted_string_type type) = 0;
  HfstState add_sequence(StringVector::const_iterator it,
			 StringVector::const_iterator end);
};

#endif // HFST_TAGGER_HEADER_FST_BUILDER_H
