#ifndef _SFST_ALPHABET_H_
#define _SFST_ALPHABET_H_

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef INCLUDE_TR1_UNORDERED_MAP_AND_SET
#include <tr1/unordered_map>
#else
#include <unordered_map>
#endif

#ifdef USE_TR1_UNORDERED_MAP_AND_SET
using std::tr1::unordered_map;
#else
using std::unordered_map;
#endif

#include <set>
#include <vector>
#include <string.h>
#include <stdio.h>

/* @file SfstAlphabet.h
   \brief Declaration of class SfstAlphabet. */

namespace hfst {
  namespace implementations {

    /* copied from SFST's alphabet.h|C */
    class SfstAlphabet {
      
    public:
      typedef std::pair<unsigned int,unsigned int> NumberPair;
      // used to map the codes back to the symbols
      typedef unordered_map<unsigned int, char*> CharMap;

    private:
      // string comparison operators needed ???
      struct eqstr {
    bool operator()(const char* s1, const char* s2) const {
      return strcmp(s1, s2) == 0;
    }
      };
      
      // used to map the symbols to their codes
      typedef unordered_map<const char*, unsigned int> SymbolMap;

      // set of symbol pairs
      typedef std::set<NumberPair> NumberPairSet;
      
      SymbolMap sm; // maps symbols to codes
      CharMap  cm; // maps codes to symbols
      
      
      // The set of string pairs
      NumberPairSet pairs;
      
    public:
      SfstAlphabet();
      SfstAlphabet(const SfstAlphabet &alpha);
      ~SfstAlphabet();

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
