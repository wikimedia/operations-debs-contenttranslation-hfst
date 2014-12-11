#include "ComposeIntersectUtilities.h"

#include <set>

struct CmpInt
{ bool operator() (int i, int j) const { return i < j; } };

typedef 
hfst::implementations::compose_intersect_utilities::SpaceSavingSet<int,CmpInt> 
IntSpaceSavingSet;

template<> CmpInt IntSpaceSavingSet::comparator = CmpInt();

#ifndef MAIN_TEST


#else // MAIN_TEST was defined

#include <iostream>
#include <cassert>

int main(int argc, char * argv[])
{
    std::cout << "Unit tests for " __FILE__ ":" << std::endl;
    
  IntSpaceSavingSet sset;
  assert(sset.size() == 0);
  assert(not sset.has_element(0));
  
  sset.insert(0);
  assert(sset.size() == 1);
  assert(sset.has_element(0));

  sset.insert(1);
  assert(sset.size() == 2);
  assert(sset.has_element(0));
  assert(sset.has_element(1));

  sset.insert(1);
  sset.insert(1);
  sset.insert(0);
  sset.insert(2);
  sset.insert(4);
  sset.insert(3);
  assert(sset.has_element(0));
  assert(sset.has_element(1));
  assert(sset.has_element(2));
  assert(sset.has_element(3));
  assert(sset.has_element(4));

  sset.clear();
  assert(sset.size() == 0);
  assert(not sset.has_element(0));
  sset.insert(0);
  sset.insert(1);
  assert(sset.has_element(1));
  assert(sset.has_element(0));

  IntSpaceSavingSet::const_iterator jt = sset.begin();
  assert(jt != sset.end());
  assert(*jt == 0);
  ++jt;
  assert(jt != sset.end());
  assert(*jt == 1);
  ++jt;
  assert(jt == sset.end());

  sset.clear();
  assert(sset.size() == 0);
  assert(not sset.has_element(0));
  sset.insert(1);
  sset.insert(0);
  assert(sset.has_element(0));
  assert(sset.has_element(1));
 
  jt = sset.begin();
  assert(jt != sset.end());
  assert(*jt == 0);
  ++jt;
  assert(jt != sset.end());
  assert(*jt == 1);
  ++jt;
  assert(jt == sset.end());

  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);

  for (size_t i = 0; i != 100000; ++i)
    { IntSpaceSavingSet * p = new IntSpaceSavingSet(); p->insert(0); p->insert(1);}

  sset.clear();
  sset.insert(2);
  assert(not sset.has_element(1));

  std::cout << "ok" << std::endl;
  return 0;
}
#endif // MAIN_TEST
