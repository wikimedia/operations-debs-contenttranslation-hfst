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
    symbols.count(HfstTropicalTransducerTransitionData::get_symbol(symbol))
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
