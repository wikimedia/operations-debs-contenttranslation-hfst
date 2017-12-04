//! @file Alphabet.h
//!
//! @author Miikka Silfverberg
//!
//! @brief The alphabet of a twolc-grammar.

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

#ifndef ALPHABET_H_
#define ALPHABET_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string>

#include "../HfstTwolcDefs.h"
#include "../rule_src/OtherSymbolTransducer.h"

#ifdef HAVE_XFSM
  #define Alphabet TwolCAlphabet
#endif

class Alphabet
{
 protected:
  HandySet<SymbolPair> alphabet_set;
  HandySet<std::string> input_symbols;
  HandySet<std::string> output_symbols;
  HandySet<std::string> diacritics;
  HandyMap<SymbolPair,OtherSymbolTransducer> alphabet;
  HandyMap<std::string,SymbolRange> sets;

  const OtherSymbolTransducer &compute(const SymbolPair &pair);
  bool is_pair(const std::string &input,const std::string &output);
  void define_singleton_set(const std::string &name);
  bool is_set_pair(const SymbolPair &pair) const;
 public:
  void define_set(const std::string &name,const SymbolRange &elements);
  void define_alphabet_pair(const SymbolPair &pair);
  void alphabet_done(void);
  void define_diacritics(const SymbolRange &);
  bool is_empty_pair(const SymbolPair &pair);
  const OtherSymbolTransducer &get_transducer(const SymbolPair &pair);
  SymbolPairVector * get_symbol_pair_vector(const SymbolPair &pair);
};

#endif
