// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _FORMAT_SPECIFIERS_H_
#define _FORMAT_SPECIFIERS_H_

#if defined (_MSC_VER) || (__MINGW32__)
  #define SIZE_T_SPECIFIER    "%Iu"
  #define SSIZE_T_SPECIFIER   "%Id"
  #define PTRDIFF_T_SPECIFIER "%Id"
  #define LONG_LONG_SPECIFIER "%I64d"
#else
  #define SIZE_T_SPECIFIER    "%zu"
  #define SSIZE_T_SPECIFIER   "%zd"
  #define PTRDIFF_T_SPECIFIER "%zd"
  #define LONG_LONG_SPECIFIER "%lld"
#endif

#endif
