// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

//! @file lexc-utils.h
//!
//! @brief Various string handling methods for HFST lexc.
//!
//! @author Tommi A. Pirinen

#ifndef GUARD_lexc_utils_h
#define GUARD_lexc_utils_h
#if HAVE_CONFIG_H
#  include <config.h>
#endif
#include <string>

#ifdef _MSC_VER
#  include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif


namespace hfst { namespace xfst {

#ifndef HAVE_GETLINE
#   define MAX_LINE_SIZE 12345678
    ssize_t getline(char** line, size_t* n, FILE* f);
#endif

//! @brief Strips initial and final white space and strdups
char* strstrip(const char* s);

 int nametoken_to_number(const char * token);

//! @brief extracts the variable substring part from token.
//! Omits constant string prefix, suffix and optionally strips spaces.
char* strdup_nonconst_part(const char* token,
                           const char* prefix,
                           const char* suffix,
                           bool strip);

} }
// vim: set ft=cpp.doxygen:
#endif // GUARD_lexc_utils_h
