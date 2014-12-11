#include "HfstAlphabet.h"
#include "HfstBasic.h"
#include "HfstUtf8.h"
#include "HfstSymbolDefs.h"
#include <cstdlib>

#ifndef DEBUG_MAIN

namespace hfst {
  namespace implementations {
    
    HfstAlphabet::HfstAlphabet() {
      add(hfst::internal_epsilon.c_str(),0);
      add(hfst::internal_unknown.c_str(),1);
      add(hfst::internal_identity.c_str(),2);
    }
    
    HfstAlphabet::HfstAlphabet(const HfstAlphabet &alpha) 
    {
      for (CharMap::const_iterator it = alpha.cm.begin(); it != alpha.cm.end(); it++) {
    cm[it->first] = basic::fst_strdup(it->second);
      }
      for (SymbolMap::const_iterator it = alpha.sm.begin(); it != alpha.sm.end(); it++) {
    sm[basic::fst_strdup(it->first)] = it->second;
      }
      for (NumberPairSet::const_iterator it = alpha.pairs.begin(); it != alpha.pairs.end(); it++) {
    pairs.insert(NumberPair(it->first, it->second));
      }
    }

    HfstAlphabet::~HfstAlphabet() {
      char **s=new char*[cm.size()];
      pairs.clear();
      sm.clear();
      
      size_t i, n=0;
      for( CharMap::iterator it=cm.begin(); it!=cm.end(); it++ )
    s[n++] = it->second;
      cm.clear();
      
      for( i=0; i<n; i++ )
    free(s[i]);
      delete[] s;
    }
    
    HfstAlphabet::const_iterator HfstAlphabet::begin() const { return pairs.begin(); }
    HfstAlphabet::const_iterator HfstAlphabet::end() const { return pairs.end(); };
    size_t HfstAlphabet::size() const { return pairs.size(); };
    
    //bool HfstAlphabet::contains_special_symbols(StringPair sp);

    void HfstAlphabet::print_pairs(FILE *file) {
      for (NumberPairSet::const_iterator it = pairs.begin(); it != pairs.end(); it++)
    fprintf(file, "%s:%s\n", code2symbol(it->first), code2symbol(it->second));
    }

    void HfstAlphabet::print() {
      printf("alphabet..\n");
      for( CharMap::iterator it=cm.begin(); it!=cm.end(); it++ )
    printf("%i\t%s\n",it->first,it->second);
      printf("..alphabet\n");
    }
    
    void HfstAlphabet::insert(NumberPair sp) { 
      /* check special symbols */ pairs.insert(sp); };
    void HfstAlphabet::clear_pairs() { pairs.clear(); };
    HfstAlphabet::CharMap HfstAlphabet::get_char_map() { return cm; };

    void HfstAlphabet::add( const char *symbol, unsigned int c ) {
      char *s = basic::fst_strdup(symbol);
      cm[c] = s;
      sm[s] = c;
    }
    
    int HfstAlphabet::symbol2code( const char * s ) const {
      SymbolMap::const_iterator p = sm.find(s);
      if (p != sm.end()) return p->second;
      return EOF;       
    }
    
    const char *HfstAlphabet::code2symbol( unsigned int c ) const {
      CharMap::const_iterator p=cm.find(c);
      if (p == cm.end())
    return NULL;
      else
    return p->second;
    }
    
    unsigned int HfstAlphabet::add_symbol(const char * symbol) {
      if (sm.find(symbol) != sm.end())
    return sm[symbol];
      
      // assign the symbol to some unused character
      for(unsigned int i=1; i!=0; i++)
    if (cm.find(i) == cm.end()) {
      add(symbol, i);
      return i;
    }
      
      throw "Error: too many symbols in transducer definition";
    }
    
    void HfstAlphabet::add_symbol( const char *symbol, unsigned int c )

    {
      // check whether the symbol was previously defined
      int sc=symbol2code(symbol);
      if (sc != EOF) {
    if ((unsigned int)sc == c)
      return;
    
    if (strlen(symbol) < 60) {
      static char message[100];
      sprintf(message, "Error: reinserting symbol '%s' in alphabet with incompatible character value %u %u", symbol, (unsigned)sc, (unsigned)c);
      throw message;
    }
    else
      throw "reinserting symbol in alphabet with incompatible character value";
      }
      
      // check whether the character is already in use
      const char *s=code2symbol(c);
      if (s == NULL)
    add(symbol, c);
      else {
    if (strcmp(s, symbol) != 0) {
      static char message[100];
      if (strlen(symbol) < 70)
        sprintf(message,"Error: defining symbol %s as character %d (previously defined as %s)", symbol, (unsigned)c, s);
      else
        sprintf(message,"Error: defining a (very long) symbol with previously used character");
      throw message;
    }
      }
    }

    void HfstAlphabet::complement( std::vector<unsigned int> &sym ) {
      std::vector<unsigned int> result;
      for( CharMap::const_iterator it=cm.begin(); it!=cm.end(); it++ ) {
    unsigned int c = it->first;
    if (c != 0 && c != 1 && c != 2) { // no special symbols
      size_t i;
      for( i=0; i<sym.size(); i++ )
        if (sym[i] == c)
          break;
      if (i == sym.size())
        result.push_back(c);
    }
      }
      sym.swap(result);
    }

    /*******************************************************************/
    /*                                                                 */
    /*  Alphabet::next_mcsym                                           */
    /*                                                                 */
    /*  recognizes multi-character symbols which are enclosed with     */
    /*  angle brackets <...>. If the argument flag insert is true,     */
    /*  the multi-character symbol must be already in the lexicon in   */
    /*  order to be recognized.                                        */
    /*                                                                 */
    /*******************************************************************/
    
    int HfstAlphabet::next_mcsym( char* &string, bool insert )
      
    {
      char *start=string;
      
      if (*start == '<')
    // symbol might start here
    for( char *end=start+1; *end; end++ )
      if (*end == '>') {
        // matching pair of angle brackets found
        // mark the end of the substring with \0
        char lastc = *(++end);
        *end = 0;
        
        int c;

        // handle epsilon symbol "<>" here
        if (strcmp(start,"<>") == 0) {
          c = 0;
        }
        else {
          if (insert)
        c = add_symbol( start );
          else
        c = symbol2code(start);
        }
        // restore the original string
        *end = lastc;
        
        if (c != EOF) {
          // symbol found
          // return its code
          string = end;
          return (unsigned int)c;
        }
        else
          // not a complex character
          break;
      }
      return EOF;
    }

    int HfstAlphabet::next_code( char* &string, bool extended, bool insert )
      
    {
      if (*string == 0)
    return EOF; // finished
      
      int c = next_mcsym(string, insert);
      if (c != EOF)
    return c;
      
      if (extended && *string == '\\')
    string++; // remove quotation
      
      //if (utf8) {
      {
    unsigned int c = hfst_utf8::utf8toint( &string );
    return (int)add_symbol(hfst_utf8::int2utf8(c));
      }
      //}
      /*else {
    char buffer[2];
    buffer[0] = *string;
    buffer[1] = 0;
    string++;
    return (int)add_symbol(buffer);
    }*/
    }

    std::pair<unsigned int, unsigned int> HfstAlphabet::next_label(char * &string, bool extended) 
    {
      // read first character
      int c = next_code( string, extended );
      if (c == EOF) {
    return std::pair<unsigned int, unsigned int>(0,0); // end of string reached
      }
      
      unsigned int lc=(unsigned int)c;
      if (!extended || *string != ':') { // single character?
    if (lc == 0)
      return next_label(string, extended); // ignore epsilon
    return std::pair<unsigned int, unsigned int>(lc,lc);
      }
      
      // read second character
      string++; // jump over ':'
      c = next_code( string );
      if (c == EOF) {
    static char buffer[1000];
    sprintf(buffer,"Error: incomplete symbol in input file: %s", string);
    throw buffer;
      }
      
      std::pair<unsigned int, unsigned int> retval(lc, (unsigned int)c);
      if (retval.first == 0 && retval.second == 0)
    return next_label(string, extended); // ignore epsilon transitions
      return retval; 
    }
    
  }
}
#else
#include <iostream>
int
main(int argc, char** argv)
{
  std::cout << "Unit tests for " __FILE__ ":";
  std::cout << std::endl << "constructors: ";
  std::cout << " default()...";
  HfstAlphabet defaultAlpha;
  std::cout << " (copy)...";
  HfstAlphabet copyAlpha(defaultAlpha);
  std::cout << std::endl << "destructor: ";
    delete new HfstAlphabet();
    delete new HfstAlphabet(defaultAlpha);
    std::cout << std::endl << "rest skipped...";
    std::cout << "ok" << std::endl;
    return EXIT_SUCCESS;
}
#endif
