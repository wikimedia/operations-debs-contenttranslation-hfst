// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

// --- licensing stuff here?

#ifndef HARMONIZE_UNKNOWN_AND_IDENTITY_SYMBOLS
#define HARMONIZE_UNKNOWN_AND_IDENTITY_SYMBOLS

// ---
/* A more generalized class that takes an template <class C, class W>
   HfstTransitionGraph as its constructor arguments. The functions could
   take a HfstTransitionGraph::HfstTransitionGraphAlphabet as their
   arguments and use functions C::get_unknown() etc.
 */

#include <set>
#include <string>
#include <iosfwd>
#include <algorithm>

#include "HfstDataTypes.h"
#include "HfstSymbolDefs.h"

namespace hfst
{
using implementations::HfstBasicTransducer;
using implementations::HfstBasicTransition;

#ifdef TEST_HARMONIZE_UNKNOWN_AND_IDENTITY_SYMBOLS
#define debug_harmonize 1
#else
#define debug_harmonize 0
#endif // TEST_HARMONIZE_UNKNOWN_AND_IDENTITY_SYMBOLS

#include "hfstdll.h"

// --- a short documentation
class HarmonizeUnknownAndIdentitySymbols
{
  // --- HfstSymbolDefs.h has members const std::string internal_identity
  //     and internal_unknown
 public:
  // --- const std::string instead
  static const char * identity; // --- a short documentation
  static const char * unknown;  // --- "" ---
  
  // Constructor whose side effect it is to harmonize the identity and unknown
  // symbols of its arguments.
  HFSTDLL HarmonizeUnknownAndIdentitySymbols
    (HfstBasicTransducer &,HfstBasicTransducer &);
 protected:

  HfstBasicTransducer &t1;
  HfstBasicTransducer &t2;
  StringSet t1_symbol_set;  // --- symbols known to t1?
  StringSet t2_symbol_set;  // --- symbols known to t2?
  
  // Collect the symbols from the transitions of the argument transducer
  // and store them in the argument set. This is needed since the alphabet
  // of HfstBasicTransducers can sometimes unexplainedly be empty...
  // --- the alphabet can contain also symbols that are not found in
  //     transitions...
  HFSTDLL void populate_symbol_set(const HfstBasicTransducer &,StringSet &);

  // Add all symbols in the StringSet to the alphabet of the transducer.
  HFSTDLL void add_symbols_to_alphabet(HfstBasicTransducer &, const StringSet &);

  // For every x in the set, add x:x transitions for every identity:identity
  // transition in the argument transducer (the source and target states as
  // well as the weights are the same as in the original identity transition.
  HFSTDLL void harmonize_identity_symbols
    (HfstBasicTransducer &,const StringSet &);

  // For every x in the set
  // 1. add, x:c transitions for every unknown:c transition in the argument
  //    transducer.
  // 2. add, c:x transitions for every c:unknown transition in the argument
  //    transducer.
  //
  // For every x and y in the set with x != y, add x:y transitions for every
  // unknown:unknown transition in the argument transducer.
  //
  // (the source and target states as well as the weights are the same as in
  // the original identity transition)
  HFSTDLL void harmonize_unknown_symbols
    (HfstBasicTransducer &,const StringSet &);
};

HFSTDLL void debug_harmonize_print(const StringSet &);
HFSTDLL void debug_harmonize_print(const std::string &);
// use name 'max_' to avoid collision with windows macro 'max'
HFSTDLL size_t max_(size_t t1,size_t t2); // --- a short documentation

}


#endif // HARMONIZE_UNKNOWN_AND_IDENTITY_SYMBOLS --- good
