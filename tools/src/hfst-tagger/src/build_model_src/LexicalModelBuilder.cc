#include "LexicalModelBuilder.h"

#ifndef MAIN_TEST

using hfst::HfstOutputStream;
using hfst::HFST_OLW_TYPE;
using hfst::TROPICAL_OPENFST_TYPE;

// The models are P(word | tag), P(lower_case_suffix_tag |
// lower_case_suffix), P(lower_case_suffix), P(lower_case_suffix_tag),
// P(upper_case_suffix_tag | upper_case_suffix), P(upper_case_suffix)
// and P(upper_case_suffix_tag)
#define NUMBER_OF_LEXICAL_MODELS 7

LexicalModelBuilder::LexicalModelBuilder(std::istream &in)
{
  ModelBuilder::verbose_printf("Compiling lexical model.\n");
  for (size_t i = 0; i < NUMBER_OF_LEXICAL_MODELS; ++i)
    {
      ModelBuilder model_builder(WeightedStringVectorCollection(in,LEXICAL));
      model_vector.push_back(model_builder.get_model());
    }
}

void LexicalModelBuilder::store(HfstOutputStream &out, const std::string &file_name)
{
  HfstTransducer lexical_model(TROPICAL_OPENFST_TYPE);

  ModelBuilder::verbose_printf("Disjuncting the lexical sub models.\n");

  for (TransducerVector::iterator it = model_vector.begin();
       it != model_vector.end();
       ++it)
    { lexical_model.disjunct(*it); }
  
  ModelBuilder::verbose_printf("Minimizing the lexical model.\n");

  lexical_model.minimize();

  ModelBuilder::verbose_printf("Transforming the lexical model to "
			       "optimized format.\n");

  lexical_model.convert(HFST_OLW_TYPE); 
 
  ModelBuilder::verbose_printf(std::string("Storing the lexical model in") +
			       file_name + ".\n");
 
  out << lexical_model;
}

void LexicalModelBuilder::store(const std::string &file_name)
{
  HfstOutputStream out(file_name,HFST_OLW_TYPE);

  store(out,file_name);
}

void LexicalModelBuilder::store(void)
{
  HfstOutputStream out(HFST_OLW_TYPE);
  
  store(out,"<stdout>");
}

#else // MAIN_TEST

int main(void)
{

}

#endif // MAIN_TEST
