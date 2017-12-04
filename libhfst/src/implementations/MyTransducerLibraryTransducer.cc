// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

/*  @file MyTransducerLibraryTransducer.cc
    \brief Implementations of functions and datatypes that form a bridge between
    HFST API and your transducer library. */

#include "MyTransducerLibraryTransducer.h"

#ifndef DEBUG_MAIN
namespace hfst {
namespace implementations
{
  ;

  /* Create and open a stream to standard in. */
  MyTransducerLibraryInputStream::MyTransducerLibraryInputStream(void) {
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Create and open a stream to file filename. */
  MyTransducerLibraryInputStream::MyTransducerLibraryInputStream
  (const std::string &filename) {
    (void)filename;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Close the stream. If it points to standard in, nothing is done. */
  void MyTransducerLibraryInputStream::close(void) {
    HFST_THROW(FunctionNotImplementedException); }
  
  /* */
  bool MyTransducerLibraryInputStream::is_eof(void) {
    HFST_THROW(FunctionNotImplementedException); }
  
  /* */
  bool MyTransducerLibraryInputStream::is_bad(void) {
    HFST_THROW(FunctionNotImplementedException); }
  
  /* */
  bool MyTransducerLibraryInputStream::is_good(void) {
    HFST_THROW(FunctionNotImplementedException); }
  
  /* */
  bool MyTransducerLibraryInputStream::is_fst(void) {
    HFST_THROW(FunctionNotImplementedException); }
    
  /* Extract a char from the stream. */
  char MyTransducerLibraryInputStream::stream_get() {
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Put back a char to the stream. */
  void MyTransducerLibraryInputStream::stream_unget(char c) {
    (void)c;
    HFST_THROW(FunctionNotImplementedException); }

  /* Extract n chars and ignore them. */
  void MyTransducerLibraryInputStream::ignore(unsigned int n) {
    (void)n;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Optional: if you want to extract implementation specific data from the
     header. */
  bool MyTransducerLibraryInputStream::set_implementation_specific_header_data
  (StringPairVector &data, unsigned int index) {
    (void)data;
    (void)index;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Read a transducer from the stream. */
  MyFst * MyTransducerLibraryInputStream::read_transducer() {
    HFST_THROW(FunctionNotImplementedException); }
  


  /* Create and open a stream to standard out. */
  MyTransducerLibraryOutputStream::MyTransducerLibraryOutputStream(void) {
    HFST_THROW(FunctionNotImplementedException); }

  /* Create and open a stream to file filename. */
  MyTransducerLibraryOutputStream::MyTransducerLibraryOutputStream
  (const std::string &filename) {
    (void)filename;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Close the stream. If it points to standard out, nothing is done. */
  void MyTransducerLibraryOutputStream::close(void) {
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Write a char to the stream. */
  void MyTransducerLibraryOutputStream::write(const char &c) {
    (void)c;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Optional: if you want to store implementation specific data to the header.
   */
  void MyTransducerLibraryOutputStream::
    append_implementation_specific_header_data
  (std::vector<char> &header, MyFst *t) {
    (void)header;
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Write a transducer to the stream. */
  void MyTransducerLibraryOutputStream::write_transducer(MyFst * transducer) {
    (void)transducer;
    HFST_THROW(FunctionNotImplementedException); }
  

  
  /* Create a transducer that does not recognise any string. */
  MyFst * MyTransducerLibraryTransducer::create_empty_transducer(void) {
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that recognises the empty string. */
  MyFst * MyTransducerLibraryTransducer::create_epsilon_transducer(void) {
    HFST_THROW(FunctionNotImplementedException); }
    
  /* Create a transducer that recognises the symbol pair symbol:symbol */
  MyFst * MyTransducerLibraryTransducer::define_transducer
  (const std::string &symbol) {
    (void)symbol;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that recognises the symbol pair isymbol:osymbol */
  MyFst * MyTransducerLibraryTransducer::define_transducer
  (const std::string &isymbol, const std::string &osymbol) {
    (void)isymbol;
    (void)osymbol;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that recognises the concatenation of symbol pairs in
     spv */
  MyFst * MyTransducerLibraryTransducer::define_transducer
  (const StringPairVector &spv) {
    (void)spv;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that recognises the union of symbol pairs in sps
     If cyclic is true, any number of consecutive symbol pairs is recognised. */
  MyFst * MyTransducerLibraryTransducer::define_transducer
  (const StringPairSet &sps, bool cyclic) {
    (void)sps;
    (void)cyclic;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that recognises the concatenation of symbol pair unions
     in spsv. */
  MyFst * MyTransducerLibraryTransducer::define_transducer
  (const std::vector<StringPairSet> &spsv) {
    (void)spsv;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a deep copy of transducer t. */
  MyFst * MyTransducerLibraryTransducer::copy(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a deterministic transducer equivalent to transducer t. */
  MyFst * MyTransducerLibraryTransducer::determinize(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a minimal transducer equivalent to transducer t. */
  MyFst * MyTransducerLibraryTransducer::minimize(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create an epsilon-free transducer equivalent to transducer t. */
  MyFst * MyTransducerLibraryTransducer::remove_epsilons(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts any number of consecutive string pairs
     accepted by transducer t. */
  MyFst * MyTransducerLibraryTransducer::repeat_star(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts one or more consecutive string pairs
     accepted by transducer t. */
  MyFst * MyTransducerLibraryTransducer::repeat_plus(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts n consecutive string pairs accepted by
     transducer t. */
  MyFst * MyTransducerLibraryTransducer::repeat_n(MyFst * t,int n) {
    (void)t;
    (void)n;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts from zero to n consecutive string pairs
     accepted by transducer t. */
  MyFst * MyTransducerLibraryTransducer::repeat_le_n(MyFst * t,int n) {
    (void)t;
    (void)n;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts string pairs accepted by transducer t or
     an empty string. */
  MyFst * MyTransducerLibraryTransducer::optionalize(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts string pair string2:string1 iff
     transducer t accepts string pair string1:string2. */
  MyFst * MyTransducerLibraryTransducer::invert(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts string pair 1gnirts:2gnirts iff
     transducer t accepts string pair string1:string2. */
  MyFst * MyTransducerLibraryTransducer::reverse(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts string pair string1:string1 iff
     transducer t accepts string pair string1:string2. */
  MyFst * MyTransducerLibraryTransducer::extract_input_language(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts string pair string2:string2 iff
     transducer t accepts string pair string1:string2. */
  MyFst * MyTransducerLibraryTransducer::extract_output_language(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* A vector of transducers that each accept one string pair accepted by
     transducer t. t cannot be cyclic. */
  std::vector<MyFst*> MyTransducerLibraryTransducer::extract_paths(MyFst *t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* TODO: document */
  void MyTransducerLibraryTransducer::extract_paths
  (MyFst * t, hfst::ExtractStringsCb& callback,
   int cycles, FdTable<unsigned int>* fd, bool filter_fd) {
    (void)t;
    (void)callback;
    (void)cycles;
    (void)fd;
    (void)filter_fd;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts string pair of
     [ A:B* s A:B* t A:B* r A:B* i A:B* n A:B* g A:B* 1:2 A:B* ]
     (where A and B are input and output symbol of symbol_pair) iff transducer
     t accepts string pair string1:string2. */
  MyFst * MyTransducerLibraryTransducer::insert_freely
  (MyFst *t , const StringPair &symbol_pair) {
    (void)t;
    (void)symbol_pair;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer equivalent to transducer t but where all symbols
     old_symbol are substituted with new_symbol. */
  MyFst * MyTransducerLibraryTransducer::substitute
  (MyFst * t, String old_symbol, String new_symbol) {
    (void)t;
    (void)old_symbol;
    (void)new_symbol;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer equivalent to transducer t but where all symbol pairs
     symbol_pair are substituted with a copy of transducer tr. */
  MyFst * MyTransducerLibraryTransducer::substitute
  (MyFst *t, const StringPair &symbol_pair, MyFst *tr) {
    (void)t;
    (void)symbol_pair;
    (void)tr;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Create a transducer that accepts string pair string1:string3 iff t1
     accepts string pair string1:string2 and t2 accepts string pair
     string2:string3, where string2 is any string. */
  MyFst * MyTransducerLibraryTransducer::compose(MyFst * t1, MyFst * t2) {
    (void)t1;
    (void)t2;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts a concatenation of any string pair
     accepted by t1 and any string pair accepted by t2. */
  MyFst * MyTransducerLibraryTransducer::concatenate(MyFst * t1, MyFst * t2) {
    (void)t1;
    (void)t2;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts any string pair accepted by t1 or t2. */
  MyFst * MyTransducerLibraryTransducer::disjunct(MyFst * t1, MyFst * t2) {
    (void)t1;
    (void)t2;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts any string pair accepted by both t1 and
     t2. */
  MyFst * MyTransducerLibraryTransducer::intersect(MyFst * t1, MyFst * t2) {
    (void)t1;
    (void)t2;
    HFST_THROW(FunctionNotImplementedException); }

  /* Create a transducer that accepts any string pair accepted by t1 but not
     t2. */
  MyFst * MyTransducerLibraryTransducer::subtract(MyFst * t1, MyFst * t2) {
    (void)t1;
    (void)t2;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* See file MyTransducerLibraryTransducer.h */
  std::pair<MyFst*, MyFst*> MyTransducerLibraryTransducer::harmonize
  (MyFst *t1, MyFst *t2, bool unknown_symbols_in_use) {
    (void)t1;
    (void)t2;
    (void)unknown_symbols_in_use;
    HFST_THROW(FunctionNotImplementedException); }

  /* Whether transducers t1 an t2 are equivalent. */
  bool MyTransducerLibraryTransducer::are_equivalent(MyFst * t1, MyFst * t2) {
    (void)t1;
    (void)t2;
    HFST_THROW(FunctionNotImplementedException); }

  /* Whether transducer t is cyclic. */
  bool MyTransducerLibraryTransducer::is_cyclic(MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* A table of transducer numbers that represent flag
     diacritics in transducer t. */
  FdTable<unsigned int>* MyTransducerLibraryTransducer::get_flag_diacritics
  (MyFst * t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Remove symbol symbol from the alphabet of transducer t. */
  MyFst * MyTransducerLibraryTransducer::remove_from_alphabet
  (MyFst *t, const std::string &symbol) {
    (void)t;
    (void)symbol;
    HFST_THROW(FunctionNotImplementedException); }

  /* Disjunct t with a path transducer spv. */
  MyFst * MyTransducerLibraryTransducer::disjunct
  (MyFst * t, const StringPairVector &spv) {
    (void)t;
    (void)spv;
    HFST_THROW(FunctionNotImplementedException); }

  /* Get all symbol pairs that occur in transitions of transducer t. */
  StringPairSet MyTransducerLibraryTransducer::get_symbol_pairs(MyFst *t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* The number of states in transducer t. */
  unsigned int MyTransducerLibraryTransducer::number_of_states(MyFst *t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }
  
  /* Add the following number-to-symbol correspondencies to the alphabet of
     transducer t:
     0 : "@_EPSILON_SYMBOL_@", i.e. internal_epsilon
     1 : "@_UNKNOWN_SYMBOL_@", i.e. internal_unknown
     2 : "@_IDENTITY_SYMBOL_@", i.e. internal_identity  */
  void MyTransducerLibraryTransducer::initialize_alphabet(MyFst *t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

  /* Get all symbols that occur in transitions of transducer t. */
  StringSet MyTransducerLibraryTransducer::get_alphabet(MyFst *t) {
    (void)t;
    HFST_THROW(FunctionNotImplementedException); }

}
}

#else
#include <cstdlib>
#include <cassert>
#include <iostream>

int
main(void)
  {
    std::cout << "Unit tests for " __FILE__ ":";
    std::cout << std::endl << "ok" << std::endl;
    return EXIT_SUCCESS;
  }
#endif


