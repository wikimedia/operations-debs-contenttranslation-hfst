// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _HFSTDLL_H_
#define _HFSTDLL_H_
#ifdef _MSC_VER
#ifdef HFSTEXPORT
#define HFSTDLL  __declspec(dllexport)
#else
#define HFSTDLL __declspec(dllimport)
#endif // HFSTEXPORT
#else
#define HFSTDLL
#endif // _MSC_VER
#endif // _HFSTDLL_H_
