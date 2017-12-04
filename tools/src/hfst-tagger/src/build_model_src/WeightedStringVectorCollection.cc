#include "WeightedStringVectorCollection.h"

#ifndef MAIN_TEST

#include <string>
#include <cstdio>

size_t WeightedStringVectorCollection::line_number = 0;

size_t WeightedStringVectorCollection::get_line_number(void)
{ return line_number; }

void WeightedStringVectorCollection::init_line_number(void)
{ line_number = 0; }

WeightedStringVectorCollection::WeightedStringVectorCollection
(std::istream &in, weighted_string_type type):
  is_lexical_model(type == LEXICAL)
{
  this->name = read_model_start_tag(getline(in));
  
  if (not is_lexical_model)
    {
      this->penalty_weight = read_model_penalty_weight(getline(in));
    }



  if (in.peek() == EOF)
    { throw EmptyFile(); }

  std::string line;

  while (1)
    {
      line = getline(in);

      try
	{
	  WeightedStringVector entry =
	    (this->is_lexical_model ?
	     tokenize_lexicon_line(line,tokenizer) :
	     tokenize_grammar_line(line,tokenizer));

	  data.push_back(entry);
	}
      catch (InvalidLine &e)
	{
	  std::string stop_name = read_model_stop_tag(line);
	  
	  if (name != stop_name)
	    { throw InvalidLine(e,STR(__LINE__)); }

	  break;
	}
    }
}
  
std::string WeightedStringVectorCollection::getline(std::istream &in)
{
  std::string line;

  if (in.peek() == EOF)
    {
      throw EmptyFile();
    }

  std::getline(in,line);
  
  ++WeightedStringVectorCollection::line_number;
  return line;
}

WeightedStringVectorCollection::const_iterator
WeightedStringVectorCollection::begin(void) const
{ return this->data.begin(); }

WeightedStringVectorCollection::const_iterator
WeightedStringVectorCollection::end(void) const
{ return this->data.end(); }

WeightedStringVectorCollection::iterator
WeightedStringVectorCollection::begin(void)
{ return this->data.begin(); }

WeightedStringVectorCollection::iterator
WeightedStringVectorCollection::end(void)
{ return this->data.end(); }

const std::string &WeightedStringVectorCollection::get_name(void) const
{ return this->name; }

float WeightedStringVectorCollection::get_penalty_weight(void) const
{ return this->penalty_weight; }

#else // MAIN_TEST

#include <string>
#include <sstream>
#include <cassert>

int main(void)
{
  std::string line1 = "START LEX MODEL\n";
  std::string line2 = "a\tDT\t1.0\n";
  std::string line3 = "oof\tNN\t2.0\n";
  std::string line4 = "STOP LEX MODEL\n";

  std::string line5 = "START SEQ MODEL\n";
  std::string line6 = "PENALTY_WEIGHT=1.0\n";
  std::string line7 = "DT\tNN\t1.5\n";
  std::string line8 = "STOP SEQ MODEL";

  std::string file = line1 + line2 + line3 + line4 + line5 + line6 + line7 +
    line8;

  std::istringstream in(file);

  WeightedStringVectorCollection c1(in,LEXICAL);

  WeightedStringVectorCollection::const_iterator it = c1.begin();
  
  assert(it != c1.end());
  assert(it->string_vector.size() == 2);
  assert(it->string_vector[0] == "a");
  assert(it->string_vector[1] == "DT");

  ++it;
  assert(it != c1.end());
  assert(it->string_vector.size() == 4);
  assert(it->string_vector[0] == "o");
  assert(it->string_vector[1] == "o");
  assert(it->string_vector[2] == "f");
  assert(it->string_vector[3] == "NN");

  ++it;

  assert(it == c1.end());

  WeightedStringVectorCollection c2(in,SEQUENCE);

  it = c2.begin();

  assert(it != c2.end());
  assert(it->string_vector.size() == 2);
  assert(it->string_vector[0] == "DT");
  assert(it->string_vector[1] == "NN");
  
  ++it;

  assert(it == c2.end());

  try
    {
      static_cast<void>(WeightedStringVectorCollection(in,SEQUENCE));
      assert(false);
    }
  catch (...)
    {}
}

#endif // MAIN_TEST
