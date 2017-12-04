// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#include "HfstEpsilonHandler.h"

namespace hfst {

  /* Create an epsilon handler which allows a maximum of \a cutoff
     consecutive input epsilon cycles. The cycles do not need to be
     the same. */
  HfstEpsilonHandler::HfstEpsilonHandler(size_t cutoff):
    epsilon_path(), max_cycles(cutoff), cycles(0) {};
  
  /* Called before calling lookup_fd recursively.
     Appends state \a s to the epsilon path if not found at the end already. */
  void HfstEpsilonHandler::push_back(hfst::implementations::HfstState s)
  {
    if (! epsilon_path.empty()) {
      if  (epsilon_path.back() != s ) {
        epsilon_path.push_back(s);
      }
    }
    else {
      epsilon_path.push_back(s);
    }
  };
  
  /* Removes a state from the end of the epsilon path,
     unless the path it is empty. */
  void HfstEpsilonHandler::pop_back()
  {
    if (! epsilon_path.empty())
      epsilon_path.pop_back();
  };
  
  /* This function is called at the beginning of lookup_fd.
     It tells whether we can proceed in the current state (i.e. state \a s)
     and updates the cycle counter and epsilon path of the HfstEpsilonHandler. */
  bool HfstEpsilonHandler::can_continue(hfst::implementations::HfstState s)
  {
    for(HfstStateVector::iterator it = epsilon_path.begin();
        it != epsilon_path.end(); it++)
      {
        if (*it == s) // a cycle detected
          {
            it++;
            // erase the cycle from the epsilon path
            // and check whether the number of cycles is exceeded
            epsilon_path.erase(it, epsilon_path.end());
            cycles++;
            if (cycles > max_cycles) {
              return false;
            }
            return true;
          }
      }
    return true;  // no cycle detected
  };

}
