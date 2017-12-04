#ifdef INCLUDE_TR1_UNORDERED_MAP_AND_SET
#include <tr1/unordered_set>
#else
#include <unordered_set>
#endif

#ifdef USE_TR1_UNORDERED_MAP_AND_SET
using std::tr1::unordered_set;
using std::tr1::unordered_multiset;
#else
using std::unordered_set;
using std::unordered_multiset;
#endif
