#ifdef INCLUDE_TR1_UNORDERED_MAP_AND_SET
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif

#ifdef USE_TR1_UNORDERED_MAP_AND_SET
using std::tr1::unordered_map;
using std::tr1::unordered_multimap;
#else
using std::unordered_map;
using std::unordered_multimap;
#endif
