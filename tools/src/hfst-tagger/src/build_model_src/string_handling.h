#ifndef HEADER_STRING_HANDLING_H
#define HEADER_STRING_HANDLING_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string>

#include "HfstTransducer.h"

using hfst::HfstTokenizer;
using hfst::StringVector;

// STR1 changes its argument into a string, i.e. surrounds it with
// quotation marks. Since arguments of # aren't evaluated, two macro
// levels are needed, to convert the result of a macro such as __LINE__
// into a string.
#define STR1(a) # a
#define STR(a) STR1(a)

// Thrown when a line has an unexpected field count (i.e. number of
// tab-separated segments).
struct InvalidLine
{
  InvalidLine(const std::string &representation);
  InvalidLine(const InvalidLine &,const std::string &representation);

  std::string representation;
};

// Thrown when encountering something that cannot be interpreted as a
// positive float.
struct InvalidFloat
{
  InvalidFloat(const std::string &representation);
  InvalidFloat(const InvalidFloat &,const std::string &representation);

  std::string representation;
};

// Hold a vector of strings (a future path in a transducer) and it's
// associated weight, which is a positive float.
struct WeightedStringVector
{
  WeightedStringVector(const StringVector &v, float f);

  StringVector string_vector;
  float weight;
};

// Tokenize lines of the form "foo\tNN\t1.0" to a weighted string vector,
// whose string vector is {f,o,o,NN} and whose weight is 1.0.
WeightedStringVector tokenize_lexicon_line(const std::string &line,
					   HfstTokenizer &tokenizer);

// Tokenize lines of the form "(foo\tbar\t)+1.0" to a weighted string vector,
// whose string vector is {(foo,bar,)+} and whose weight is 1.0.
WeightedStringVector tokenize_grammar_line(const std::string &line,
					   HfstTokenizer &tokenizer);

// In a statistics file of word-n-gram frequencies, there are start
// and stop tags for statistics, read the start tag of form "START
// FOO". FOO can't contain tabs.
std::string read_model_start_tag(const std::string &line);

// In a statistics file of word-n-gram frequencies, there are start
// and stop tags for statistics, read the stop tag of form "START
// FOO". FOO can't contain tabs.
std::string read_model_stop_tag(const std::string &line);

// Read the penalty weight X as a float from string "PENALTY_WEIGHT=X".
float read_model_penalty_weight(const std::string &line);

#endif // HEADER_STRING_HANDLING_H
