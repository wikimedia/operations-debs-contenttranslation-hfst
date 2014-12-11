#ifndef HEADER_SentenceTagger_h
#define HEADER_SentenceTagger_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "SequenceTagger.h"
#include "NewLexicalModel.h"

#define BUFFER "||"

class SentenceTagger
{
 public:
  SentenceTagger(const std::string &lexical_model_filename,
		 const std::string &sequence_model_filename,
		 std::istream * paradigm_guess_stream = 0);
  ~SentenceTagger(void);
  WeightedStringPairVector operator[] (const StringVector &sentence);
  bool is_oov(const std::string &word);
  bool is_lexicon_oov(const std::string &word);
 protected:
  typedef std::vector<SequenceModelComponent*> ModelPointerVector;

  NewLexicalModel lexical_model;
  ModelPointerVector models;
  SequenceModelComponent * top_level_model;
  SequenceTagger * sequence_tagger;
  WeightedStringVector buffer_analyses;
  
  void init_sequence_model(const std::string &sequence_model_filename);
  SequenceModelComponent * read_model(SequenceModelComponent * p,
				      HfstInputStream &in);
  static size_t get_model_order(const HfstTransducer &model_fst);
};

#endif // HEADER_SentenceTagger_h
