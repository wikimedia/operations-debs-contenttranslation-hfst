// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _HFST_EPSILON_HANDLER_H_
#define _HFST_EPSILON_HANDLER_H_

#include "HfstDataTypes.h"

namespace hfst {

  /* A class for handling input epsilon cycles in function lookup_fd. */
  class HfstEpsilonHandler
  {
  protected:
    typedef std::vector<hfst::implementations::HfstState> HfstStateVector;
    // the path of consecutive input epsilon transitions
    HfstStateVector epsilon_path;
    size_t max_cycles; // maximum number of consecutive epsilon cycles allowed
    size_t cycles;     // number of cycles detected so far
  public:
    HfstEpsilonHandler(size_t cutoff);
    void push_back(hfst::implementations::HfstState s);
    void pop_back();
    bool can_continue(hfst::implementations::HfstState s);
  };

}

#endif // _HFST_EPSILON_HANDLER_H_
