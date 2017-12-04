#include "FunctionalTransducer.h"

std::ostream *  FunctionalTransducer::verbose_out = NULL;

FunctionalTransducer::FunctionalTransducer(const HfstBasicTransducer &fst):
  fst(fst)
{
  verbose_print("Constricting FunctionalTransducer.");

  StringSet input_symbols;
  StringSet output_symbols;
  verbose_print("Collecting input and output symbols for tokenization.");
  collect_symbols_from_fst(input_symbols,output_symbols,fst);

  verbose_print("Defining input symbols.");
  define_multichar_symbols(input_symbols,input_tokenizer);

  verbose_print("Defining output_symbols.");
  define_multichar_symbols(output_symbols,output_tokenizer);
}

void FunctionalTransducer::set_verbose_print(std::ostream &out)
{ verbose_out = &out; }

void FunctionalTransducer::verbose_print(const std::string &msg)
{
  if (verbose_out != NULL)
    { std::cout << msg << std::endl; }
}

void FunctionalTransducer::collect_symbols_from_fst
(StringSet &input_symbols,StringSet &output_symbols,
 const HfstBasicTransducer &fst) const
{
  for (HfstBasicTransducer::const_iterator it = fst.begin();
       it != fst.end();
       ++it)
    {
      for (TransitionSet::const_iterator jt = it->second.begin();
       jt != it->second.end();
       ++jt)
    {
      input_symbols.insert(jt->get_input_symbol());
      output_symbols.insert(jt->get_output_symbol());
    }
    }
}

void FunctionalTransducer::define_multichar_symbols
(const StringSet &symbols,HfstTokenizer &tokenizer)
{
  for (StringSet::const_iterator it = symbols.begin();
       it != symbols.end();
       ++it)
    {
      std::string symbol = *it;
      verbose_print(std::string("Symbol: ") + symbol);
      tokenizer.add_multichar_symbol(symbol);
      std::string symbol_start = symbol.substr(0,1);

      // Escaped multichar symbol.
      tokenizer.add_multichar_symbol("\\" + symbol_start);
    }

  // Escaped 0.
  tokenizer.add_multichar_symbol(std::string("\\") + ZERO);

  // Escaped escape symbol.
  tokenizer.add_multichar_symbol("\\\\");
}

std::string FunctionalTransducer::apply_on_input(const std::string &input)
const
{
  verbose_print("Input : " + input + ".");
  StringVector input_vector = tokenize(input,input_tokenizer);
  verbose_print("Tokenized input: " + join(input_vector) + ".");
  return apply(input_vector,true);
}

std::string FunctionalTransducer::apply_on_output(const std::string &output)
const
{
  verbose_print("Output : " +output + ".");
  StringVector output_vector = tokenize(output,output_tokenizer);
  verbose_print("Tokenized output: " + join(output_vector) + ".");
  return apply(output_vector,false);
}

StringVector FunctionalTransducer::tokenize
(const std::string &str,const HfstTokenizer &tokenizer)
{
  // Tokenize.
  StringVector tokenized_str = tokenizer.tokenize_one_level(str);

  // Unescaped escaped symbols and replace "0" with "@_EPSILON_SYMBOL_@".
  for (StringVector::iterator it = tokenized_str.begin();
       it != tokenized_str.end();
       ++it)
    {
      if (not it->empty())
    {
      if (*it == ZERO)
        { *it = EPSILON_SYMBOL; }
      if (*it->begin() == '\\')
        { *it = it->substr(1,std::string::npos); }
    }
    }
  return tokenized_str;
}

std::string FunctionalTransducer::join(const StringVector & v,
                       const std::string &joiner,
                       bool replace_epsilons)
{
  std::string joined;
  for (StringVector::const_iterator it = v.begin();
       it != v.end();
       ++it)
    {
      std::string symbol = *it;
      if (replace_epsilons and symbol == EPSILON_SYMBOL)
    { continue; }
    joined += *it;
      if (it != v.end())
    { joined += joiner; }
    }
  return joined;
}

StringVector
FunctionalTransducer::apply(const StringVector &v,bool input) const
{
  StringVectorVector result;
  StateSet epsilon_path_states;
  follow_epsilon_transitions
    (v.begin(),v.end(),0,input,result,epsilon_path_states);
  follow_transitions(v.begin(),v.end(),0,input,result);
  return join_and_uniquify(result);
}

using hfst::HfstTransducer;
using hfst::TROPICAL_OPENFST_TYPE;

int main(void)
{
  FunctionalTransducer::set_verbose_print(std::cerr);
  HfstTokenizer tokenizer;
  tokenizer.add_multichar_symbol("+N");
  tokenizer.add_multichar_symbol("+Nom");
  tokenizer.add_multichar_symbol("+Pl");
  HfstTransducer cats("cats","cat+N+Nom+Pl",tokenizer,TROPICAL_OPENFST_TYPE);

  FunctionalTransducer func_cats(cats);
  std::string output = func_cats.apply_on_input("cats");
  std::cerr << output << std::endl;
  std::string input = func_cats.apply_on_output("cat+N+Nom+Pl0\\0");
  std::cerr << input << std::endl;
}
