#include "SequenceModelBuilder.h"

#ifndef MAIN_TEST

using hfst::HfstOutputStream;
using hfst::TROPICAL_OPENFST_TYPE;

SequenceModelBuilder::SequenceModelBuilder(std::istream &in)
{
  ModelBuilder::verbose_printf("Compiling sequence models.\n");

  while (1)
    {
      try
	{
	  ModelBuilder model_builder(WeightedStringVectorCollection(in,
								    SEQUENCE));
	  
	  model_vector.push_back(model_builder.get_model());
	}
      catch (const EmptyFile &e)
	{
	  static_cast<void>(e);
	  break;
	}
    }
}

void SequenceModelBuilder::store(const std::string &file_name)
{
  ModelBuilder::verbose_printf(std::string("Storing sequence models in ") +
			       file_name + ".\n");

  HfstOutputStream out(file_name,TROPICAL_OPENFST_TYPE);
  
  for (TransducerVector::iterator it = model_vector.begin();
       it != model_vector.end();
       ++it)
    { out << *it; }
}

void SequenceModelBuilder::store(void)
{
  ModelBuilder::verbose_printf("Storing sequence models in <stdout>.\n");

  HfstOutputStream out(TROPICAL_OPENFST_TYPE);
  
  for (TransducerVector::iterator it = model_vector.begin();
       it != model_vector.end();
       ++it)
    { out << *it; }
}

#else // MAIN_TEST

int main(void)
{

}

#endif // MAIN_TEST
