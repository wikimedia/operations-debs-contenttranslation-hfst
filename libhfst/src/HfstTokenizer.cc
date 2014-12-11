//       This program is free software: you can redistribute it and/or modify
//       it under the terms of the GNU General Public License as published by
//       the Free Software Foundation, version 3 of the License.
//
//       This program is distributed in the hope that it will be useful,
//       but WITHOUT ANY WARRANTY; without even the implied warranty of
//       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//       GNU General Public License for more details.
//
//       You should have received a copy of the GNU General Public License
//       along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "HfstTokenizer.h"
#include <string>

#ifndef MAIN_TEST

using std::string;
namespace hfst 
{
  bool MultiCharSymbolTrie::is_end_of_string(const char * p) const
  { return *(p+1) == 0; }

  void MultiCharSymbolTrie::set_symbol_end(const char * p)
  { is_leaf[(unsigned char)(*p)] = true; }

  bool MultiCharSymbolTrie::is_symbol_end(const char * p) const
  { return is_leaf[(unsigned char)(*p)]; }
  
  void MultiCharSymbolTrie::init_symbol_rests(const char * p)
  { 
    if (symbol_rests[(unsigned char)(*p)] == NULL)
      { symbol_rests[(unsigned char)(*p)] = new MultiCharSymbolTrie(); }
  }
  
  void MultiCharSymbolTrie::add_symbol_rest(const char * p)
  { symbol_rests[(unsigned char)(*p)]->add(p+1); }

  MultiCharSymbolTrie * MultiCharSymbolTrie::get_symbol_rest_trie
  (const char * p) const
  { return symbol_rests[(unsigned char)(*p)]; }
  
  MultiCharSymbolTrie::MultiCharSymbolTrie(void):
    symbol_rests(UCHAR_MAX, (MultiCharSymbolTrie*) NULL),
    is_leaf(UCHAR_MAX, false)
  {}

  MultiCharSymbolTrie::~MultiCharSymbolTrie(void)
  {
    for (MultiCharSymbolTrieVector::iterator it = symbol_rests.begin();
         it != symbol_rests.end();
         ++it)
      { delete *it; }
  }

  void MultiCharSymbolTrie::add(const char * p)
  {
    if (is_end_of_string(p))
      { set_symbol_end(p); }
    else
      { init_symbol_rests(p);
        add_symbol_rest(p); }
  }
  
  const char * MultiCharSymbolTrie::find(const char * p) const
  {
    MultiCharSymbolTrie * symbol_rest_trie = get_symbol_rest_trie(p);
    if (symbol_rest_trie == NULL)
      { 
        if (is_symbol_end(p))
          { return p+1; }
        return NULL; 
      }
    const char * symbol_end = symbol_rest_trie->find(p+1);
    if (symbol_end == NULL)
      { 
        if (is_symbol_end(p))
          { return p+1; }
      }
    return symbol_end;
  }
  
  HfstTokenizer::HfstTokenizer() {}


int HfstTokenizer::get_next_symbol_size(const char * symbol)
const
{
  if (not *symbol)
    { return 0; }

  const char * multi_char_symbol_end = multi_char_symbols.find(symbol);  

  /* The string begins with a multi character symbol */
  if (multi_char_symbol_end != NULL)
    { return multi_char_symbol_end - symbol; }
  if ((128 & *symbol) == 0)
    { return 1; }
  else if ((32 & *symbol) == 0)
    { return 2; }
  else if ((16 & *symbol) == 0)
    { return 3; }
  else
    {
      return 4;
    }
}

  bool HfstTokenizer::is_skip_symbol(hfst::String &s) const
{ return (s == "") or (skip_symbol_set.find(s) != skip_symbol_set.end()); }

void
HfstTokenizer::add_multichar_symbol(const string& symbol)
{  multi_char_symbols.add(symbol.c_str()); }

void
HfstTokenizer::add_skip_symbol(const std::string &symbol)
{ if (symbol == "")
    { return; }
  multi_char_symbols.add(symbol.c_str()); 
  skip_symbol_set.insert(symbol.c_str()); }

StringPairVector HfstTokenizer::tokenize
(const string& input_string) const
{
  check_utf8_correctness(input_string);
  StringPairVector spv;
  const char* s = input_string.c_str();
  while (*s)
    {
      int symbol_size = get_next_symbol_size(s);
      std::string symbol(s,0,symbol_size);
      s += symbol_size;
      if (is_skip_symbol(symbol))
        { continue; }
      spv.push_back(StringPair(symbol,symbol));
    }
  return spv;
}

StringVector HfstTokenizer::tokenize_one_level
(const string& input_string) const
{
  check_utf8_correctness(input_string);

  StringVector sv;
  const char* s = input_string.c_str();
  while (*s)
    {
      int symbol_size = get_next_symbol_size(s);
      std::string symbol(s,0,symbol_size);
      s += symbol_size;
      if (is_skip_symbol(symbol))
        { continue; }
      sv.push_back(symbol);
    }
  return sv;
}

StringPairVector HfstTokenizer::tokenize_space_separated(const std::string & str)
{
  check_utf8_correctness(str);

  StringPairVector retval;
  size_t pos = 0;
  // position where a symbol begins, not yet defined
  size_t symbol_pos = std::string::npos;

  while (pos < str.size())
    {
      // end of symbol reached
      if (str[pos] == ' ' && symbol_pos != std::string::npos)
        {
          std::string symbol(str, symbol_pos, pos - symbol_pos);
          retval.push_back(StringPair(symbol, symbol));
          symbol_pos = std::string::npos; // next symbol not yet found
        }
      // next symbol found
      else if (str[pos] != ' ' && symbol_pos == std::string::npos)
        {
          symbol_pos = pos;
        }
      else 
        {}
      ++pos;
    }
  
  // last symbol
  if (symbol_pos != std::string::npos)
    {
      std::string symbol(str, symbol_pos, std::string::npos);
      retval.push_back(StringPair(symbol, symbol));
    }

  return retval;
}

StringPairVector HfstTokenizer::tokenize
(const string& input_string,const string& output_string) const
{
  check_utf8_correctness(input_string);
  check_utf8_correctness(output_string);

  StringPairVector spv;
  
  StringPairVector input_spv = tokenize(input_string.c_str());
  StringPairVector output_spv = tokenize(output_string.c_str());

  if (input_spv.size() < output_spv.size())
    {
      StringPairVector::iterator jt = output_spv.begin();
      for (StringPairVector::iterator it = input_spv.begin();
           it != input_spv.end();
           ++it)
        { spv.push_back(StringPair(it->first,
                                    jt->first));
          ++jt; }
      for ( ; jt != output_spv.end(); ++jt)
        { spv.push_back(StringPair(internal_epsilon,jt->first)); }
    }
  else
    {
      StringPairVector::iterator it = input_spv.begin();
      for (StringPairVector::iterator jt = output_spv.begin();
           jt != output_spv.end();
           ++jt)
        { spv.push_back(StringPair(it->first,
                                   jt->first));
          ++it; }
      for ( ; it != input_spv.end(); ++it)
        { spv.push_back(StringPair(it->first,internal_epsilon)); }
    }
  return spv;
}
  
  void 
  HfstTokenizer::check_utf8_correctness(const std::string &input_string)
{
  // Check that input_string is made up from utf-8 sequences.
  for (std::string::const_iterator it = input_string.begin(); 
       it != input_string.end();
       ++it)
    {
      // The initial byte of the sequence.
      unsigned char initial_char = *it;
      size_t additional_chars = 0;
  
      // The bytes 192, 193, 245, 246 and 247 are invalid in utf8.
      if (initial_char == 192 or initial_char == 193 or
      initial_char == 245 or initial_char == 246 or initial_char == 247)
    { HFST_THROW_MESSAGE(IncorrectUtf8CodingException, 
                         "leading octet in [192, 193, 245, 246, 247]"); }
      // Case 0xxxxxxx, i.e. ASCII byte.
      else if ((128 & initial_char) == 0)
    { additional_chars = 0; }
      // Case 10xxxxxx cannot be an initial byte. 
      else if ((64 & initial_char) == 0)
    { HFST_THROW_MESSAGE(IncorrectUtf8CodingException, 
                         "leading octet & 10000000b"); }
      // Case 110xxxxx, i.e. read one more byte.
      else if ((32 & initial_char) == 0)
    { additional_chars = 1; }
      // Case 1110xxxx, i.e. read two more bytes.
      else if ((16 & initial_char) == 0)
    { additional_chars = 2; }
      // Case 11110xxx, i.e. read three more bytes.
      else if ((8 & initial_char) == 0) 
    { additional_chars = 3; }
      // Case 11111xxx is not allowed in utf8.
      else
    { HFST_THROW_MESSAGE(IncorrectUtf8CodingException, 
                         "leading octet & 11111000b"); }

      // Read the continuation bytes.
      for (size_t i = 0; i < additional_chars; ++i)
    {
      ++it;
      // String ends too early.
      if (it == input_string.end())
        { HFST_THROW_MESSAGE(IncorrectUtf8CodingException,
                             "eos in multioctet sequence"); }
      unsigned char byte = *it;
      // All continuation bytes look like 10xxxxxx.
      if (not (128 & byte and 64 ^ byte))
        { HFST_THROW_MESSAGE(IncorrectUtf8CodingException,
                             "not continuation octet & 100000000b"); }
    }
    }
}
  
}

#else // MAIN_TEST was defined

#include <iostream>

int main(int argc, char * argv[])
{
    std::cout << "Unit tests for " __FILE__ ":" << std::endl;
    
    std::cout << "ok" << std::endl;
    return 0;
}

#endif // MAIN_TEST
