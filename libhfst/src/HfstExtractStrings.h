// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _EXTRACT_STRINGS_H_
#define _EXTRACT_STRINGS_H_
#include "HfstSymbolDefs.h"
#include <string>
#include <vector>
#include <iosfwd>
#include <sstream>
#include <set>

/* @file HfstExtractStrings.h
    \brief Classes WeightedPath and WeightsPaths */

namespace hfst {

  typedef std::vector<std::pair<std::string,std::string> > StringPairVector;
  typedef std::pair<float, StringPairVector> HfstTwoLevelPath;
  typedef std::set<HfstTwoLevelPath> HfstTwoLevelPaths;

  using std::stringstream;
  using std::ios;

  /* \brief (Being replaced by HfstOneLevelPath and HfstTwoLevelPath)
      A weighted string pair that represents a path in a transducer.

      @see WeightedPaths
      @see HfstOneLevelPath
      @see HfstTransducer::extract_paths
  */
#ifdef FOO
  template<class W> class WeightedPath
    {
    public:
      /* \brief The input string of the path. */
      std::string istring;
      /* \brief The output string of the path. */
      std::string ostring;
      /* \brief The weight of the path. */
      W weight;
      /* \brief An optional StringPairVector representation of the path.

          This can be used when we are interested in the exact alignment of
          symbols in a given path. If you are going to use this variable,
          set the value of \a is_spv_in_use 'true'. */
      StringPairVector spv;
      /* \brief  Whether the StringPairVector representation is in use.

          This variable tells whether we are using the string pair vector
          representation. By default, it is 'false'. */
      bool is_spv_in_use;

      WeightedPath(const std::string &is,const std::string &os,W w)
        { weight = w; istring = is; ostring = os; is_spv_in_use=false; }

      bool operator< (const WeightedPath &another) const
        { if (weight == another.weight)
            { if (istring == another.istring)
                { if (ostring == another.ostring)
                  { /* Handle here spv. */
                    if (not is_spv_in_use)
                      return false; /* paths are equivalent */
                    unsigned int common_length
                      = (spv.size()<another.spv.size())?
                      spv.size() : another.spv.size();
                    /* Go through string pairs. */
                    for (unsigned int i=0; i<common_length; i++) {
                      if (spv[i].first == another.spv[i].first)
                        { if (spv[i].second == another.spv[i].second)
                            { continue; }
                          return (spv[i].second < another.spv[i].second); }
                      return (spv[i].first < another.spv[i].first);
                    }
                    /* Shorter path is smaller. */
                    return (spv.size() < another.spv.size());
                  }
                  return ostring < another.ostring; }
              return istring < another.istring; }
          return weight < another.weight; }
      
      std::string to_string(void) const
        { stringstream s_stream(ios::out);
          s_stream << istring << ":" << ostring << "\t" << weight;
          s_stream.flush();
          return s_stream.str();
        }
      
      WeightedPath<W> &reverse(void)
      { for(size_t i = 0; i < (istring.size() / 2); ++i)
          { char c = istring[i];
            istring[i] = istring[istring.size() - i - 1];
            istring[istring.size() - i - 1] = c; }

        for(size_t i = 0; i < (ostring.size() / 2); ++i)
          { char c = ostring[i];
            ostring[i] = ostring[ostring.size() - i - 1];
            ostring[ostring.size() - i - 1] = c; }
        return *this; }

      WeightedPath &add(const WeightedPath &another,bool in_front=true)
        { if (in_front)
            {
              istring = another.istring + istring;
              ostring = another.ostring + ostring;
              weight = weight + another.weight;
              return *this;
            }
          else
            {
              istring = istring + another.istring;
              ostring = ostring + another.ostring;
              weight = weight + another.weight;
              return *this;
            }
        }
      void operator=(const WeightedPath &another)
        { if (this == &another) { return; }
          this->istring = another.istring;
          this->ostring = another.ostring;
          this->weight = another.weight; }
    };


  /* \brief A class for storing weighted string pairs that represent
      paths in a transducer.

      Iterators to Vectors and Sets return paths in descending weight order
      (the string with the biggest weight is returned first). (check this)

      For an example, see HfstTransducer::extract_paths.

      @see HfstTransducer::extract_paths */
  template<class W> class WeightedPaths
    { public:

      /* \brief A vector of weighted string pairs. */
      typedef std::vector< WeightedPath<W> > Vector;
      /* \brief A set of weighted string pairs. */
      typedef std::set< WeightedPath<W> > Set;

      static void add(Vector &v,WeightedPath<W> &s)
      {
        for (typename Vector::iterator it = v.begin(); it != v.end(); ++it)
          { it->add(s,false); }
      }

      static void add(WeightedPath<W> &s,Vector &v)
      {
        for (typename Vector::iterator it = v.begin(); it != v.end(); ++it)
          { it->add(s); }
      }

      static void cat(Vector &v, const Vector &another_v)
      {
        v.insert(v.end(),another_v.begin(),another_v.end());
      }
      
      static void reverse_strings(Vector &v)
      {
        for (typename Vector::iterator it = v.begin(); it != v.end(); ++it)
          { it->reverse(); }
      }
    };
#endif
    
    class ExtractStringsCb
    {
     public:
      class RetVal
      {
       public:
        bool continueSearch;
        bool continuePath;
        RetVal(bool s, bool p): continueSearch(s), continuePath(p) {}
        void operator=(const RetVal& o)
        {
          continueSearch = o.continueSearch;
          continuePath = o.continuePath;
        }
      };
      
      /**
       * This function is called by extract_paths after every transition with
       * the path \a path up to that point, and whether or not the path
       * ends at a \a final state. The return value determines the future course
       * of the extraction search.
       *
       * @returns A data structure indicating whether the search
       *          should continue, be broken off immediately,
       *          or whether the specific path should no longer be followed.
       */
      //virtual RetVal operator()(WeightedPath<float>& path, bool final) = 0;
      virtual RetVal operator()(HfstTwoLevelPath& path, bool final) = 0;
    };
  }
#endif
