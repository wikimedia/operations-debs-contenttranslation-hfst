// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _MY_TRANSDUCER_LIBRARY_TRANSDUCER_H_
#define _MY_TRANSDUCER_LIBRARY_TRANSDUCER_H_

/** @file MyTransducerLibraryTransducer.h
    \brief Declarations of functions and datatypes that form a bridge between
    the HFST API and your transducer library.

    This file lists the classes and functions that a new library must implement
    before added under the HFST API. Write implementations in file
    MyTransducerLibraryTransducer.cc
*/

#include "HfstExceptionDefs.h"
#include "HfstFlagDiacritics.h"
#include "HfstSymbolDefs.h"
#include "HfstExtractStrings.h"

/* Include all relevant header files of your transducer library here */
#ifndef _MY_TRANSDUCER_LIBRARY_LIB_H_
#define _MY_TRANSDUCER_LIBRARY_LIB_H_
#include "my_transducer_library/MyTransducerLibrary.h"
#endif

#include <cstdio>
#include <string>
#include <sstream>
#include <iosfwd>


namespace hfst {
namespace implementations
{

  /* If your library is written in namespace my_namespace, it must be visible
     as hfst::implementations::my_namespace */
  using namespace my_namespace;

  /** @brief A skeleton class for reading a new type of binary transducers
      from a stream.

     If your transducer read function uses C FILEs, see class SfstInputStream
     or FomaInputStream for an example how to implement the functions
     in class MyTransducerLibraryInputStream. If your transducer read function
     uses C++ streams, see class TropicalWeightInputStream or
     LogWeightInputStream.
   */
  class MyTransducerLibraryInputStream
  {
  private:
    // you probably need
    //std::string filename;

    // if the library uses C FILEs, you probably need this
    //FILE * input_file;

    // if the library uses C++ streams, you probably need this
    //ifstream i_stream;
    //istream &input_stream;

  public:
    /** @brief Create and open a stream to standard in. */
    MyTransducerLibraryInputStream(void);
    /** @brief Create and open a stream to file filename. */
    MyTransducerLibraryInputStream(const std::string &filename);
    /** @brief Close the stream. If it points to standard in, nothing
        is done. */
    void close(void);
    /** @brief Whether the stream is at end. */
    bool is_eof(void);
    /** @brief Whether the stream's badbit has been set. */
    bool is_bad(void);
    /** @brief Whether the stream is good for input operations. */
    bool is_good(void);
    /** @brief Whether the next object in the stream is a MyFst */
    bool is_fst(void);

    /** @brief Extract a char from the stream. */
    char stream_get();
    /** @brief Put back a char to the stream. */
    void stream_unget(char c);
    /** @brief Extract n chars and ignore them. */
    void ignore(unsigned int n);

    /** @brief Optional: if you want to extract implementation specific
        data from the header. */
    bool set_implementation_specific_header_data
      (StringPairVector &data, unsigned int index);

    /** @brief Read a MyFst from the stream. */
    MyFst * read_transducer();
    
  };

  /** @brief A skeleton class for writing a new type of binary transducers
      to a stream.

     If your transducer write function uses C FILEs, see class SfstOutputStream
     or FomaOutputStream for an example how to implement the functions
     in class MyTransducerLibraryOutputStream. If your transducer write
     function uses C++ streams, see class TropicalWeightOutputStream or
     LogWeightOutputStream.
  */
  class MyTransducerLibraryOutputStream
  {
  private:
    // you probably need this
    //std::string filename;

    // if the library uses C FILEs, you probably need this
    //FILE *ofile;

    // if the library uses C++ streams, you probably need this
    //ofstream o_stream;
    //ostream &output_stream;

  public:
    /** @brief Create and open a stream to standard out. */
    MyTransducerLibraryOutputStream(void);
    /** @brief Create and open a stream to file filename. */
    MyTransducerLibraryOutputStream(const std::string &filename);
    /** @brief Close the stream. If it points to standard out, nothing
        is done. */
    void close(void);
    /** @brief Write a char to the stream. */
    void write(const char &c);

    /** @brief Optional: if you want to store implementation specific data
        to the binary transducer header. */
    void append_implementation_specific_header_data
      (std::vector<char> &header, MyFst *t);

    /** @brief Write a MyFst to the stream. */
    void write_transducer(MyFst * transducer);
  };
  
  /** @brief A skeleton library class that contains operations for a new
      transducer type that is added under the HFST interface.

      A transducer library that is added under HFST must implement these
      operations. */
  class MyTransducerLibraryTransducer
    {
    public:
      /** @brief Create a transducer that does not recognise any string. */
      static MyFst * create_empty_transducer(void);
      /** @brief Create a transducer that recognises the empty string. */
      static MyFst * create_epsilon_transducer(void);
      /** @brief Create a transducer that recognises the symbol pair
          symbol:symbol */
      static MyFst * define_transducer(const std::string &symbol);
      /** @brief Create a transducer that recognises the symbol pair
          isymbol:osymbol */
      static MyFst * define_transducer
        (const std::string &isymbol, const std::string &osymbol);
      /** @brief Create a transducer that recognises the concatenation of
          symbol pairs in spv */
      static MyFst * define_transducer(const StringPairVector &spv);
      /** @brief Create a transducer that recognises the union of symbol pairs
          in sps. If cyclic is true, any number of consecutive symbol pairs is
          recognised. */
      static MyFst * define_transducer
        (const StringPairSet &sps, bool cyclic=false);
      /** @brief Crate a transducer that recognises the concatenation of
          symbol pair unions in spsv. */
      static MyFst * define_transducer(const std::vector<StringPairSet> &spsv);

      /** @brief Create a deep copy of transducer t. */
      static MyFst * copy(MyFst * t);
      /** @brief Create a deterministic transducer equivalent to transducer t.
       */
      static MyFst * determinize(MyFst * t);
      /** @brief Create a minimal transducer equivalent to transducer t. */
      static MyFst * minimize(MyFst * t);
      /** @brief Create an epsilon-free transducer equivalent to transducer t.
       */
      static MyFst * remove_epsilons(MyFst * t);

      /** @brief Create a transducer that accepts any number of consecutive
          string pairs accepted by transducer t. */
      static MyFst * repeat_star(MyFst * t);
      /** @brief Create a transducer that accepts one or more consecutive
          string pairs accepted by transducer t. */
      static MyFst * repeat_plus(MyFst * t);
      /** @brief Create a transducer that accepts n consecutive string pairs
          accepted by transducer t. */
      static MyFst * repeat_n(MyFst * t, unsigned int n);
      /** @brief Create a transducer that accepts from zero to n consecutive
          string pairs accepted by transducer t. */
      static MyFst * repeat_le_n(MyFst * t, unsigned int n);

      /** @brief Create a transducer that accepts string pairs accepted by
          transducer t or an empty string. */
      static MyFst * optionalize(MyFst * t);
      /** @brief Create a transducer that accepts string pair string2:string1
          iff transducer t accepts string pair string1:string2. */
      static MyFst * invert(MyFst * t);
      /** @brief Create a transducer that accepts string pair 1gnirts:2gnirts
          iff transducer t accepts string pair string1:string2. */
      static MyFst * reverse(MyFst * t);

      /** @brief Create a transducer that accepts string pair string1:string1
          iff transducer t accepts string pair string1:string2. */
      static MyFst * extract_input_language(MyFst * t);
      /** @brief Create a transducer that accepts string pair string2:string2
          iff transducer t accepts string pair string1:string2. */
      static MyFst * extract_output_language(MyFst * t);
      /** @brief A vector of transducers that each accept one string pair
          accepted by transducer t. t cannot be cyclic. */
      static std::vector<MyFst*> extract_paths(MyFst *t);
      /** @brief TODO: document */
      static void extract_paths
        (MyFst * t, hfst::ExtractStringsCb& callback,
         int cycles=-1, FdTable<unsigned int>* fd=NULL, bool filter_fd=false);

      /** @brief Create a transducer that accepts string pair of
          [ A:B* s A:B* t A:B* r A:B* i A:B* n A:B* g A:B* 1:2 A:B* ]
         (where A and B are input and output symbol of symbol_pair) iff
         transducer t accepts string pair string1:string2. */
      static MyFst * insert_freely(MyFst *t , const StringPair &symbol_pair);
      /** @brief Create a transducer equivalent to transducer t but where all
          symbols old_symbol are substituted with new_symbol. */
      static MyFst * substitute
        (MyFst * t, String old_symbol, String new_symbol);
      /** @brief Create a transducer equivalent to transducer t but where all
          symbol pairs symbol_pair are substituted with a copy of transducer
          tr. */
      static MyFst * substitute
        (MyFst *t, const StringPair &symbol_pair, MyFst *tr);

      /** @brief Create a transducer that accepts string pair string1:string3
          iff t1 accepts string pair string1:string2 and t2 accepts string pair
          string2:string3, where string2 is any string. */
      static MyFst * compose(MyFst * t1, MyFst * t2);
      /** @brief Create a transducer that accepts a concatenation of any string
          pair accepted by t1 and any string pair accepted by t2. */
      static MyFst * concatenate(MyFst * t1, MyFst * t2);
      /** @brief Create a transducer that accepts any string pair accepted by
          t1 or t2. */
      static MyFst * disjunct(MyFst * t1, MyFst * t2);
      /** @brief Create a transducer that accepts any string pair accepted by
          both t1 and t2. */
      static MyFst * intersect(MyFst * t1, MyFst * t2);
      /** @brief Create a transducer that accepts any string pair accepted by
          t1 but not t2. */
      static MyFst * subtract(MyFst * t1, MyFst * t2);

      /** @brief Return a harmonized copy of transducers t1 and t2.

         First, all string symbols that are found in t2's alphabet but not in
         t1's alphabet are added to the alphabet of t1 to the next free
         positions (numbers). Then a copy of t2 is created where the
         string-to-number mappings are the same as in t1.

         Next all unknown and identity symbols of t1 and t2 are expanded
         according to the alphabets of the transducers, i.e. an unknown or
         identity symbol in t2 is expanded to a set of all symbols known to t1
         but unknown to t2 and vice versa.
         
         Unknown and identity symbols are explained in more detail in (Ref.).

         A false value of unknown_symbols_in_use may be used for optimization
         as no unknown or identity expanding is needed in that case. */
      static std::pair<MyFst*, MyFst*> harmonize
        (MyFst *t1, MyFst *t2, bool unknown_symbols_in_use=true);

      /** @brief Whether transducers t1 an t2 are equivalent. */
      static bool are_equivalent(MyFst * t1, MyFst * t2);
      /** @brief Whether transducer t is cyclic. */
      static bool is_cyclic(MyFst * t);
      
      /** @brief A table of numbers that represent flag
          diacritics in transducer t. */
      static FdTable<unsigned int>* get_flag_diacritics(MyFst * t);

      /** @brief Remove symbol symbol from the alphabet of transducer t. */
      static MyFst * remove_from_alphabet(MyFst *t, const std::string &symbol);

      /** @brief Disjunct t with a path transducer spv. */
      static MyFst * disjunct(MyFst * t, const StringPairVector &spv);

      /** @brief Get all symbol pairs that occur in transitions of transducer
          t. */
      static StringPairSet get_symbol_pairs(MyFst *t);

      /** @brief The number of states in transducer t. */
      static unsigned int number_of_states(MyFst *t);

      // you probably need also these functions
    protected:
      /** @brief Add the following number-to-symbol correspondencies to the
          alphabet of transducer t:
         0 : "@_EPSILON_SYMBOL_@"
         1 : "@_UNKNOWN_SYMBOL_@"
         2 : "@_IDENTITY_SYMBOL_@"  */
      static void initialize_alphabet(MyFst *t);
      /** @brief Get all symbols that occur in transitions of transducer t. */
      static StringSet get_alphabet(MyFst *t);

    };


} }


#endif // #ifndef _MY_TRANSDUCER_LIBRARY_TRANSDUCER_H_
