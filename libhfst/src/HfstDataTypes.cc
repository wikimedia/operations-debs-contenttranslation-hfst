// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#include "HfstDataTypes.h"
#include <limits.h>
#include <float.h>
#include <stdexcept>
#include <cstdio>

namespace hfst
{

  const char * implementation_type_to_string(ImplementationType type)
  {
    switch (type)
      {
      case SFST_TYPE:
        return "SFST_TYPE";
        break;
      case TROPICAL_OPENFST_TYPE:
        return "TROPICAL_OPENFST_TYPE";
        break;
      case LOG_OPENFST_TYPE:
        return "LOG_OPENFST_TYPE";
        break;
      case FOMA_TYPE:
        return "FOMA_TYPE";
        break;
      case XFSM_TYPE:
        return "XFSM_TYPE";
        break;
      case HFST_OL_TYPE:
        return "HFST_OL_TYPE";
        break;
      case HFST_OLW_TYPE:
        return "HFST_OLW_TYPE";
        break;
      case HFST2_TYPE:
        return "HFST2_TYPE";
        break;
      case UNSPECIFIED_TYPE:
        return "UNSPECIFIED_TYPE";
        break;
      case ERROR_TYPE:
        return "ERROR_TYPE";
        break;
      default:
        return "(implementation type not recognized)";
        break;
      }
  }

  const char * implementation_type_to_format(ImplementationType type)
  {
    switch (type)
      {
      case SFST_TYPE:
        return "sfst";
        break;
      case TROPICAL_OPENFST_TYPE:
        return "openfst-tropical";
        break;
      case LOG_OPENFST_TYPE:
        return "openfst-log";
        break;
      case FOMA_TYPE:
        return "foma";
        break;
      case XFSM_TYPE:
        return "xfsm";
        break;
      case HFST_OL_TYPE:
        return "hfst-optimized-lookup-unweighted";
        break;
      case HFST_OLW_TYPE:
        return "hfst-optimized-lookup-weighted";
        break;
      case HFST2_TYPE:
        return "hfst2";
        break;
      case UNSPECIFIED_TYPE:
        return "unspecified-type";
        break;
      case ERROR_TYPE:
        return "error-type";
        break;
      default:
        return "(implementation-type-not-recognized)";
        break;
      }
  }

  int size_t_to_int(size_t value)
  {
    if (value > INT_MAX)
      {
        throw std::overflow_error("data is larger than INT_MAX");
      }
    return static_cast<int>(value);
  }

  unsigned int size_t_to_uint(size_t value)
  {
    if (value > UINT_MAX)
      {
        throw std::overflow_error("data is larger than UINT_MAX");
      }
    return static_cast<unsigned int>(value);
  }

  unsigned short size_t_to_ushort(size_t value)
  {
    if (value > USHRT_MAX)
      {
        throw std::overflow_error("data is larger than USHRT_MAX");
      }
    return static_cast<unsigned short>(value);
  }

  float double_to_float(double value)
  {
    if (value > FLT_MAX)
      {
        throw std::overflow_error("data is larger than FLT_MAX");
      }
    return static_cast<float>(value);
  }

  FILE * hfst_fopen(const char * filename, const char * mode)
  {
#ifdef _MSC_VER
    FILE * f = NULL;
    errno_t err = fopen_s(&f, filename, mode);
    if (err != 0)
      return NULL;
    else
      return f;
#else
    return fopen(filename, mode);
#endif
  }

}

