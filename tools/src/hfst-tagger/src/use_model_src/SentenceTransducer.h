#ifndef HEADER_SentenceTransducer_h
#define HEADER_SentenceTransducer_h

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "SequenceModelComponent.h"

typedef std::pair<Weight,std::string> WeightedString;
typedef std::vector<WeightedString> WeightedStringVector;

void sort(WeightedStringVector &v);

class SentenceTransducer : public SequenceModelComponent
{
 public:
  SentenceTransducer(void);
  void add_word(const std::string &word,const WeightedStringVector &tags);
  void finalize(void);
  
  const Symbol2TransitionDataMap &operator[](State state) const;
  State get_max_state(void) const;

 private:
  State current_max_state;
  
};

#endif // HEADER_SentenceTransducer_h
