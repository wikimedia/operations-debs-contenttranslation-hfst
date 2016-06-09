// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

//! @file string-utils.h
//!
//! @brief String manipulation utilities.

#ifndef GUARD_string_utils_h
#define GUARD_string_utils_h

#include <string>

using std::string;

namespace hfst {

//! @brief Replace all strings needles in haystack with replacement, moving
//! the cursor past the replacement each time, ie if needle is in replacement,
//! it won't be replaced. */

string& replace_all(string& haystack, const string& needle, const string& replacement);

}

#endif // GUARD_string_utils_h
