#ifdef _MSC_VER //Added  Paul Dixon
  #include <unordered_set>
  #ifdef NO_CPLUSPLUS_11
    // Basically this means that we are using VC 2008...
    using std::tr1::unordered_set;
  #else
    using std::unordered_set;
  #endif
#else
  // This shouldn't happen, resort to tr1 anyways...
  #include <tr1/unordered_set>
  using std::tr1::unordered_set;
#endif
