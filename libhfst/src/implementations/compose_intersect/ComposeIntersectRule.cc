// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.
#include "ComposeIntersectRule.h"

#ifndef MAIN_TEST

namespace hfst
{
  namespace implementations
  {
   ComposeIntersectRule::ComposeIntersectRule(const HfstBasicTransducer &t):
      ComposeIntersectFst(t,true)
    { symbols = t.get_alphabet(); }
    ComposeIntersectRule::ComposeIntersectRule(void):
      ComposeIntersectFst()
    {}
    bool ComposeIntersectRule::known_symbol(size_t symbol)
    { return
        symbols.count(HfstTropicalTransducerTransitionData::get_symbol(hfst::size_t_to_uint(symbol)))
    > 0; }
  }
}

#else // MAIN_TEST was defined

#include <iostream>

int main(int argc, char * argv[])
{
    std::cout << "Unit tests for " __FILE__ ":" << std::endl;
    
    std::cout << "ok" << std::endl;
    return 0;
}

#endif // MAIN_TEST
