#ifndef HEADER_STRINGS_2_FST_TOKENIZER_H
#define HEADER_STRINGS_2_FST_TOKENIZER_H

// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#include <vector>
#include <string>
#include <utility>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "HfstDataTypes.h"
#include "HfstTokenizer.h"

typedef std::vector<std::string> StringVector;
typedef std::pair<std::string,std::string> StringPair;
typedef std::vector<StringPair> StringPairVector;

#define COL  ":"
#define BACKSLASH  "\\"
#define SPACE " "
#define BACKSLASH_ESC "@_BACKSLASH_@"
#define EPSILON_SYMBOL "@_EPSILON_SYMBOL_@"
#define EMPTY ""

#define COL_CHAR ':'
#define BACKSLASH_CHAR '\\'

#define COL_ESCAPE "@_COLON_@"
#define TAB_ESCAPE "@_TAB_@"
#define SPACE_ESCAPE "@_SPACE_@"

namespace hfst {

class EmptyMulticharSymbol
{};

class UnescapedColsFound
{};

class HfstStrings2FstTokenizer
{
 public:
  HfstStrings2FstTokenizer
    (StringVector &multichar_symbols,const std::string &eps);

  //! Return a StringPairVector representation of the pair string str.
  //! The parameter spaces tells whether spaces have been used to separate
  //! symbol pairs.
  StringPairVector tokenize_pair_string(const std::string &str,bool spaces);

  //! Return a StringPairVector representation of the string pair str.
  //! The parameter spaces tells whether spaces have been used to separate
  //! symbols.
  StringPairVector tokenize_string_pair(const std::string &str,bool spaces);

 protected:

  hfst::HfstTokenizer tokenizer;
  std::string eps;

  // Add the multichar symbol XYZ to the tokenizer.
  void add_multichar_symbol(const std::string &multichar_symbol);

  // For multichar symbol XYZ, add the multichar symbol \X to tokenizer.
  void add_multichar_symbol_head(const std::string &multichar_symbol);
  
  // Transform v into a StringPairVector by treating symbols separated by a
  // ":" symbol as the input and output symbols of a pair and treating other
  // symbols as identity pairs. Treat initial and final colons as eps
  StringPairVector make_pair_vector(const StringVector &v);

  // Make a pair string out of input and output by pairing symbols at the
  // same indices. Pad with zeroes at the end when ncecessary.
  StringPairVector make_pair_vector(const StringVector &input,
                    const StringVector &output);

  // Return true it *it is followed by ':' and another symbol.
  bool is_pair_input_symbol(StringVector::const_iterator it,
                StringVector::const_iterator end);
  
  // Remove backslashes, except quoted backslashes '\\'.
  std::string unescape(std::string symbol);

  // Return the position of the first unquoted ':'. Return -1 if not found.
  int get_col_pos(const std::string &str);

  //! Split str at spaces, except quoted spaces "\ ".
  StringVector split_at_spaces(const std::string &str);

  //! Throw UnescapedColsFound, if symbols contains unescaped ':'-symbols.
  void check_cols(const std::string &symbol);
};

} // namespace hfst

#endif // HEADER_STRINGS_2_FST_TOKENIZER_H
