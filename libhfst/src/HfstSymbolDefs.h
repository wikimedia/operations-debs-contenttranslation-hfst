// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _SYMBOL_DEFS_H_
#define _SYMBOL_DEFS_H_
#include <vector>
#include <string>
#include <map>
#include <set>

#include "hfstdll.h"

/** @file HfstSymbolDefs.h
    \brief Typedefs and functions for symbols, symbol pairs and
    sets of symbols. */

/* Macros that can be used instead of hfsT::internal_epsilon etc
   if there are problems with variable initialization. */
#define INTERNAL_EPSILON "@_EPSILON_SYMBOL_@"
#define INTERNAL_UNKNOWN "@_UNKNOWN_SYMBOL_@"
#define INTERNAL_IDENTITY "@_IDENTITY_SYMBOL_@"
#define INTERNAL_DEFAULT "@_DEFAULT_SYMBOL_@"


namespace hfst
{

  /** \brief A UTF-8 symbol in a transition.

    Strings <i>"@_EPSILON_SYMBOL_@"</i>, <i>"@_UNKNOWN_SYMBOL_@"</i>
    and <i>"@_IDENTITY_SYMBOL_@"</i> are reserved.

    - <i>"@_EPSILON_SYMBOL_@"</i> denotes the epsilon (in AT&T formalism
      <tt>[0]</tt>).
    - <i>"@_UNKNOWN_SYMBOL_@"</i> denotes an unknown symbol,
      i.e. any symbol that
      does not occur or has not occurred in the transducer
      (in AT&T formalism <tt>[?], [?:x], [x:?]</tt>).
    - <i>"@_IDENTITY_SYMBOL_@"</i> denotes any unknown symbol that is the same
      on the input and output side of a transition (in AT&T formalism
      <tt>[?:?]</tt>).

      For an example of special symbols, see HFST transducer
      <a href="classhfst_1_1HfstTransducer.html#symbols">
      documentation</a>.

    Strings of form <CODE> @[PNDRCU][.][A-Z]+([.][A-Z]+)?@ </CODE>
    are reserved for flag diacritics. For an example of flag diacritics, see
    #hfst::HfstTransducer::extract_paths_fd(hfst::HfstTwoLevelPaths&, int, int, bool) const.
    For more information on flag diacritics, see Finite State Morphology
    (Beesley & Karttunen, 2003).
   */
  typedef std::string String;

  /* A set of strings. */
  typedef std::set<String> StringSet;

  typedef std::vector<String> StringVector;

  /** \brief A symbol pair in a transition.

      @see HfstTransducer::substitute(const StringPair&, const StringPair&)
      and other substitute functions */
  typedef std::pair<String, String> StringPair;

  /** \brief A vector of transitions that represents a path in a transducer.

      @see HfstTokenizer */
  typedef std::vector<StringPair> StringPairVector;

  /** \brief A set of symbol pairs used in substituting symbol pairs
      and in rule functions.

     @see HfstTransducer::substitute(const StringPair&, const StringPairSet &)
     #hfst::rules */
  typedef std::set<StringPair> StringPairSet;

  /** \brief A map of substitutions used when performing multiple
      symbol-to-symbol substitutions.

      @see HfstTransducer::substitute(const HfstSymbolSubstitutions&) */
  typedef std::map<String, String> HfstSymbolSubstitutions;

  /** \brief A map of substitutions used when performing multiple
      symbol pair-to-symbol pair substitutions.

      @see HfstTransducer::substitute(const HfstSymbolPairSubstitutions&) */
  typedef std::map<StringPair, StringPair> HfstSymbolPairSubstitutions;

  typedef std::pair<float, StringPairVector> HfstTwoLevelPath;
  typedef std::set<HfstTwoLevelPath> HfstTwoLevelPaths;
  
/* The internal representations */
  const std::string internal_epsilon("@_EPSILON_SYMBOL_@");
  const std::string internal_unknown("@_UNKNOWN_SYMBOL_@");
  const std::string internal_identity("@_IDENTITY_SYMBOL_@");
  const std::string internal_default("@_DEFAULT_SYMBOL_@");
  
  /* Check whether a string is equal to reserved internal representation. */
  HFSTDLL bool is_epsilon(std::string const & str);
  HFSTDLL bool is_unknown(std::string const & str);
  HFSTDLL bool is_identity(std::string const & str);
  HFSTDLL bool is_default(std::string const & str);
  HFSTDLL bool is_epsilon(const char * str);
  HFSTDLL bool is_unknown(const char * str);
  HFSTDLL bool is_identity(const char * str);
  HFSTDLL bool is_default(const char * str);

  /* For internal use */
  typedef std::pair<unsigned int, unsigned int> NumberPair;
  typedef std::vector<NumberPair> NumberPairVector;
  typedef std::set<NumberPair> NumberPairSet;
  typedef std::map<String,unsigned int> StringNumberMap;
  typedef std::map<unsigned int,unsigned int> NumberNumberMap;

  namespace symbols {
    HFSTDLL void collect_unknown_sets(StringSet &s1, StringSet &unknown1,
                  StringSet &s2, StringSet &unknown2);
    HFSTDLL int longest_path_length(const hfst::HfstTwoLevelPaths & paths, bool equally_long=false);
    HFSTDLL hfst::HfstTwoLevelPaths get_longest_paths(const hfst::HfstTwoLevelPaths & paths);
    HFSTDLL StringVector to_string_vector(const hfst::HfstTwoLevelPath & path);
    HFSTDLL std::string to_string(const StringVector & sv, bool spaces=false);
    HFSTDLL std::string to_string(const StringPairVector & sv, bool spaces=false);
    HFSTDLL StringVector to_string_vector(const StringPairVector & spv, bool input_side);
    HFSTDLL hfst::HfstTwoLevelPaths remove_flags(const hfst::HfstTwoLevelPaths & paths);
    HFSTDLL hfst::HfstTwoLevelPath remove_flags(const hfst::HfstTwoLevelPath & path);
    HFSTDLL StringPairSet to_string_pair_set(const StringSet & ss);
    HFSTDLL StringPairVector remove_flags(const StringPairVector &v);
    HFSTDLL StringVector remove_flags(const StringVector &v);
  }
}
#endif
