#ifndef HEADER_SEQUENCE_MODEL_BUILDER_H
#define HEADER_SEQUENCE_MODEL_BUILDER_H

//! @file SequenceModelBuilder.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Read training data from STDIN. Use it to train a tag
//! sequence model for a POS tagger.

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

#include <iostream>
#include <vector>

#include "HfstTransducer.h"

using hfst::HfstTransducer;

#include "ModelBuilder.h"

class SequenceModelBuilder
{
 public:
  //! Read training data from @a in
  SequenceModelBuilder(std::istream &in);

  //! Store the model in @a file_name.
  void store(const std::string &file_name);

  //! Store the model in STDOUT.
  void store(void);
 private:

  typedef std::vector<HfstTransducer> TransducerVector;
  TransducerVector model_vector;
};

#endif // HEADER_SEQUENCE_MODEL_BUILDER_H
