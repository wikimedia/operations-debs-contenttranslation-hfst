// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

//! @file string-utils.cc
//!
//! @brief Implementation of some string manipulation utilities.

#include "string-utils.h"

using std::string;

namespace hfst {

string&
replace_all(string& haystack, const string& needle, const string& replacement)
  {
    size_t last_needle = haystack.find(needle);
    size_t needle_len = needle.length();
    size_t replacement_len = replacement.length();
    while (last_needle != string::npos)
      {
        haystack.replace(last_needle, needle_len, replacement);
        last_needle = haystack.find(needle, last_needle + replacement_len);
      }
    return haystack;
  }

}
