#include "TaggerBuilder.h"

#include <fstream>

#ifndef MAIN_TEST

TaggerBuilder::TaggerBuilder(void):
  in(NULL),
  lexical_model_builder(std::cin),
  sequence_model_builder(std::cin)
{
  delete in;
}

TaggerBuilder::TaggerBuilder(const std::string &file_name):
  in(new std::ifstream(file_name.c_str())),
  lexical_model_builder(*in),
  sequence_model_builder(*in)
{ delete in; }

void TaggerBuilder::store(const std::string &file_name_prefix)
{
  lexical_model_builder.store(file_name_prefix + ".lex");
  sequence_model_builder.store(file_name_prefix + ".seq");
}

void TaggerBuilder::store(void)
{
  lexical_model_builder.store();
  sequence_model_builder.store();
}

#else // MAIN_TEST

int main(void)
{

}

#endif // MAIN_TEST
