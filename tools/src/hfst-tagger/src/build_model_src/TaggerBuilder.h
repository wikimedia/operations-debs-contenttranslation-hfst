#ifndef HEADER_TaggerBuilder_h
#define HEADER_TaggerBuilder_h

//! @file TaggerBuilder.h
//!
//! @author Miikka Silfverberg
//!
//! @brief A class which can read a file of training data and use it
//! to train a tagger. It can also store the tagger in two files.

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

#include <fstream>
#include <string>

#include "LexicalModelBuilder.h"
#include "SequenceModelBuilder.h"

class TaggerBuilder
{
 public:
  // Construct a TaggerBuilder. Read training data from STDIN.
  TaggerBuilder(void);

  // Construct a TaggerBuilder. Read training data from @a filename.
  TaggerBuilder(const std::string &filename);

  // Store the lexical model of this tagger in file_name_prefix + ".lex" and
  // store the sequence model in file_name_prefix + ".seq". 
  void store(const std::string &file_name_prefix);

  // Store the lexical model and sequence model of this tagger in STDOUT.
  void store(void);

 private:
  std::ifstream * in;
  LexicalModelBuilder lexical_model_builder;
  SequenceModelBuilder sequence_model_builder;
};

#endif // HEADER_TaggerBuilder_h
