#ifndef HEADER_WEIGHTED_STRING_VECTOR_COLLECTION_H
#define HEADER_WEIGHTED_STRING_VECTOR_COLLECTION_H

//! @file WeightedStringVectorCollection.h
//!
//! @author Miikka Silfverberg
//!

//! Reads statistics from a file and stores the result.
//!
//! The input data has lines of the form
//!
//! "STR1\tSTR2\tSTR3\t...\tSTRN\tWEIGHT"
//!
//! where each STRI is a string and WEIGHT is a positive float. The lines are
//! stored as string vectors with an associated weight.
//!
//! Two kinds of training data can be read:
//! 
//! 1. Lexical training data lines have the form "WORDFORM\tTAG\tWEIGHT" 
//!    e.g. "cat\tNN\t1.0", which is stored as (("c", "a", "t", "NN"),1.0).
//!
//! 2. Sequence training data lines have the form 
//!    "WORDFORM1\tTAG1\tWORDFORM2\tTAG2\t...\tWORDFORMM\tTAGM\tWEIGHT", e.g.
//!    "the\tDT\tcar\tNN\t1.0" which is stored as 
//!    (("the","DT","car","NN"),1.0).
//!
//! Lexical training data lines have to have 3 fields. Sequence training data
//! lines have to have at least three fields and an odd number of fields.  

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

#include "string_handling.h"

// Throw, if file end is reached unexpectedly.
struct EmptyFile
{};

// The type is LEXICAL for lexicon strings and SEQUENCE for sequence
// model strings.
enum weighted_string_type { LEXICAL, SEQUENCE };

class WeightedStringVectorCollection
{
 public:
  typedef std::vector<WeightedStringVector> WeightedStringVectorVector;
  typedef WeightedStringVectorVector::const_iterator const_iterator;
  typedef WeightedStringVectorVector::iterator iterator;

  //! Are we reading lexical training data lines.
  const bool is_lexical_model;

  //! Return the current line number of the current training data file.
  static size_t get_line_number(void);

  //! Set the line number to 0.
  static void init_line_number(void);

  //! Read training data from @a in. The parameter @a lexical model
  //! specifies whether we should read lexical or sequence training data.
  WeightedStringVectorCollection(std::istream &in, weighted_string_type type);

  //! Const iterators to pairs of string vectors and weights.
  const_iterator begin(void) const;
  const_iterator end(void) const;

  //! Iterators to pairs of string vectors and weights.
  iterator begin(void);
  iterator end(void);

  //! Return the name of the training data.
  const std::string &get_name(void) const;

  float get_penalty_weight(void) const;

 private:
  static size_t line_number;

  HfstTokenizer tokenizer;
  WeightedStringVectorVector data;
  std::string name;
  float penalty_weight;

  std::string getline(std::istream &in);
};

#endif // HEADER_WEIGHTED_STRING_VECTOR_COLLECTION_H
