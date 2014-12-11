#ifndef _HFST_ALPHABET_H_
#define _HFST_ALPHABET_H_

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#if HAVE_BACKWARD_HASH_MAP
#  include <backward/hash_map>
#elif HAVE_EXT_HASH_MAP
#  include <ext/hash_map>
#elif HAVE_HASH_MAP
#  include <hash_map>
#else
#  warning "unknown hash_map"
#  include <hash_map>
#endif

#include <set>
#include <vector>
#include <string.h>
#include <stdio.h>

/* @file HfstAlphabet.h
   \brief Declaration of class HfstAlphabet. */

namespace hfst {
  namespace implementations {

    /* copied from SFST's alphabet.h|C */
    class HfstAlphabet {
      
    public:
      typedef std::pair<unsigned int,unsigned int> NumberPair;
      // hash table used to map the codes back to the symbols
#ifdef __GNUC__
      typedef __gnu_cxx::hash_map<unsigned int, char*> CharMap;
#else
      typedef std::hash_map<unsigned int, char*> CharMap;
#endif

    private:
      // string comparison operators needed to stored strings in a hash table
      struct eqstr {
    bool operator()(const char* s1, const char* s2) const {
      return strcmp(s1, s2) == 0;
    }
      };
      
      // hash table used to map the symbols to their codes
#ifdef __GNUC__
      typedef __gnu_cxx::hash_map<const char*, unsigned int, __gnu_cxx::hash<const char*>,eqstr> SymbolMap;
#else
      typedef std::hash_map<const char*, unsigned int, std::hash<const char*>,eqstr> SymbolMap;
#endif
      // set of symbol pairs
      typedef std::set<NumberPair> NumberPairSet;
      
      SymbolMap sm; // maps symbols to codes
      CharMap  cm; // maps codes to symbols
      
      
      // The set of string pairs
      NumberPairSet pairs;
      
    public:
      HfstAlphabet();
      HfstAlphabet(const HfstAlphabet &alpha);
      ~HfstAlphabet();

      typedef NumberPairSet::const_iterator const_iterator;
      const_iterator begin() const;
      const_iterator end() const;
      size_t size() const;
      
      //bool contains_special_symbols(StringPair sp);

      void print();
      void print_pairs(FILE *file);

      void insert(NumberPair sp);
      void clear_pairs();
      CharMap get_char_map();

      void add( const char *symbol, unsigned int c );
      void add_symbol( const char *symbol, unsigned int c );
      int symbol2code( const char * s ) const;
      const char *code2symbol( unsigned int c ) const;
      unsigned int add_symbol(const char * symbol);
      void complement( std::vector<unsigned int> &sym );

      std::pair<unsigned int, unsigned int> next_label(char *&, bool extended=true);
      int next_code( char* &string, bool extended=true, bool insert=true );
      int next_mcsym( char* &string, bool insert=true );
    };

  }
}

#endif
