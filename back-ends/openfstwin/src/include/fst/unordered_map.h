#ifdef _MSC_VER //Added  Paul Dixon
  #include <unordered_map>
  #ifdef NO_CPLUSPLUS_11
    // Basically this means that we are using VC 2008...
    using std::tr1::unordered_map;
  #else
    using std::unordered_map;
  #endif
#else
  // This shouldn't happen, resort to tr1 anyways...
  #include <tr1/unordered_map>
  using std::tr1::unordered_map;
#endif
