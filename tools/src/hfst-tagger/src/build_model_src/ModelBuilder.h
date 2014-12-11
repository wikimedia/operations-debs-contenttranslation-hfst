#ifndef HEADER_MODEL_BUILDER_H
#define HEADER_MODEL_BUILDER_H

//! @file ModelBuilder.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Use training data parsed and stored in A
//! WeightedStringVectorCollection to train a lexical model or sequence
//! model.

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

#include <limits>
#include <string>

#include "FstBuilder.h"

#include "WeightedStringVectorCollection.h"

typedef std::vector<HfstState> StateVector;

class ModelBuilder : public FstBuilder
{
 public:
  
  //! If you want a lot of messages to be printed in STDERR during
  //! training, set @a verbose to true.
  static bool verbose;

  //! Print @a message to STDERR iff, @a ModelBuilder::verbose = true.
  static void verbose_printf(const std::string &message);

  ModelBuilder(const WeightedStringVectorCollection &model_weights);

 protected:

  void add_sequence(const WeightedStringVector &v,
		    weighted_string_type string_type);

  size_t depth;

  void complete_model(float penalty_weight);

  void complete_model(HfstState s,
		      StateVector::const_iterator default_state_vector_it,
		      float penalty_weight);
};

#endif // HEADER_MODEL_BUILDER_H
