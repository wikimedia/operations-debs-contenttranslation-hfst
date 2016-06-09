#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <hfst2/hfst.h>

namespace HFST
{
static const int UNWEIGHTED = 0;
static const int WEIGHTED = 1;

typedef vector<TransducerHandle> FstVector;
typedef vector<Key> KeyVector;
typedef vector<KeyPair*> KeyPairVector;
typedef vector<char*> SymbolNamePairVector;
typedef vector<char*> RuleNameVector;

static KeyTable * rule_keys;
static TransducerHandle tokenizer = NULL;

/* Display a symbol pair vector. Every key have to correspond to some symbol in
   rule_keys. */
void display_pair_vector(KeyPairVector * v) {
  if ( v == NULL )
    {
      fprintf(stderr,"(null)\n");
      return;
    }
  fprintf(stderr,"{");
  for(KeyPairVector::iterator it = v->begin();
      it != v->end();
      ++it )
    {
      KeyPair * kp = *it;
      Symbol 
    input(get_key_symbol(kp->lower_char(),rule_keys)),
    output(get_key_symbol(kp->upper_char(),rule_keys));
      const char *
    input_name(get_symbol_name(input));
      const char *
    output_name(get_symbol_name(output));

      if (v->end() == (it+1))
    {
      fprintf(stderr,"%s:%s", input_name, output_name);
    }
      else
    {
      fprintf(stderr,"%s:%s, ", input_name, output_name);
    }
    }
  fprintf(stderr,"}\n");
}

/* Create the tokenizer, which will be used to convert input strings
   into KeyVectors. 

   The tokenizer transducer can't handle epsilon, so it has to be replaced by
   an internal epsilon not likely to be encountered (PAIR::TEST::EPSILON). */ 
void make_tokenizer(void) 
{
  /*  epsilon_representation = rule_keys->get_unused_key();

  non_epsilon_rule_keys = 
    recode_key_table(rule_keys,internal_epsilon);
  */
  tokenizer = longest_match_tokenizer2(rule_keys);
  if (debug)
    {
      print_transducer(tokenizer,rule_keys);
    }
}

/* Return the symbol number corresponding to the symbol name symbol_name.
   If symbol_name has no symbol number, return -1. */
int get_symbol_number(char * symbol_name) {
  if (not is_symbol(symbol_name)) 
    {
      if (debug)
    {
      fprintf(stderr,"Symbol %s has no corresponding symbol number\n",
          symbol_name);
    }
      return -1;
    }
  return get_symbol(symbol_name);
}

/* Return the symbol number key corresponding to the symbol number 
   symbol_number. If symbol_number has no key, return -1. */
int get_symbol_number_key(Symbol symbol_number, char * symbol_name) {
  if (not is_symbol(symbol_number,rule_keys)) 
    {
      if (debug)
    {
      fprintf(stderr,"Symbol %s has no key\n",symbol_name);
    }
      return -1;
    }
  return get_key(symbol_number,rule_keys);
}

/* Split symbol_pair_string at colon-character and attempt to code the pieces
   into a KeyPair accoring to the coding given by KeyTable rule_keys. If 
   rule_keys, doesn't know one of the symbols, return NULL. 

   symbol_pair_string should be set to a non-empty string. */
KeyPair * split_symbol_pair(char * symbol_pair_string) {
  if (debug)
    {
      // Assert preconditions.
      assert(symbol_pair_string != NULL);
      assert(strcmp(symbol_pair_string,"") != 0);
    }
  // Divide symbol_pair_string at colon-characters.
  char * input = strtok(symbol_pair_string,":");
  char * output = strtok(NULL,":");
  
  // Get the symbol number corresponding to the symbol name input.
  Symbol input_symbol;
  int input_symbol_indicator = get_symbol_number(input);
  if (-1 == input_symbol_indicator)
    {
      return NULL;
    }
  input_symbol = static_cast<Symbol>(input_symbol_indicator);

  // Get the symbol key corresponding to the symbol number input_symbol.
  Key input_key,output_key;
  int input_key_indicator = get_symbol_number_key(input_symbol,input);
  if (-1 == input_key_indicator)
    {
      return NULL;
    }
  input_key = static_cast<Key>(input_key_indicator);
  
  // In case this is an identity-pair, set output_key equal to input_key.
  if (output == NULL)
    {
      output_key = input_key;
    }
  else
    {
      // Get the symbol number corresponding to the symbol name output.
      Symbol output_symbol;
      int output_symbol_indicator = get_symbol_number(output);
      if (-1 == output_symbol_indicator)
    {
      return NULL;
    }
      output_symbol = static_cast<Symbol>(output_symbol_indicator);

      // Get the symbol key corresponding to the symbol number output_symbol.
      int output_key_indicator = get_symbol_number_key(output_symbol,output);
      if (-1 == output_key_indicator)
    {
      return NULL;
    }
      output_key = static_cast<Key>(output_key_indicator);
    }
  // Return the pair input_key:output_key.
  return define_keypair(input_key,output_key);
}

bool test_correspondence(KeyPairVector * input_vector,
             FstVector * rules,
             RuleNameVector * rule_names,
             bool negative,
             FILE * output_file=stdout)
{
  if ( debug )
    {
      assert(input_vector != NULL);
      assert(rules != NULL);
      assert((rule_names == NULL) or (rules->size() == rule_names->size()));
    }
  bool passed_test;
  // Rather complicatd way to transform a KeyPairVector into a transducer...
  TransducerHandle input_fst = 
    disjunct_as_trie(HFST::create_empty_transducer(),
               input_vector);

  // Delete input_vector
  for (KeyPairVector::iterator it = input_vector->begin();
       it != input_vector->end();
       ++it)
    {
      delete *it;
    }
  delete input_vector;
  if (not negative)
    {
      passed_test = true;
      for (size_t i = 0; i < rules->size(); ++i)
    {
      // Is the correspondence accepted by the rule?
      bool test_result =
        not are_disjoint(input_fst,rules->at(i));
      if (not test_result) {
        if (debug or verbose)
          {
        if (rule_names == NULL)
          {
            fprintf(output_file,"Rule " SIZE_T_SPECIFIER " rejects\n",i);
          }
        else
          {
            fprintf(output_file,"Rule %s rejects\n",rule_names->at(i));
          }
          }
      }
      passed_test = passed_test and test_result;
    }
    }
  else
    {
      passed_test = false;
      for (size_t i = 0; i < rules->size(); ++i)
    {
      bool test_result =
        are_disjoint(input_fst,rules->at(i));
      if (test_result)
        {
          passed_test = true;
          break;
        }
    }
    }

  delete input_fst;
  return passed_test;
}

/* Delete key pairs in v and then delete v. */
void delete_key_pair_vector(KeyPairVector * v)
{
  for(KeyPairVector::iterator it = v->begin();
      it != v->end();
      ++it ) 
    {
      delete *it;
    }
  delete v;
}

/* Divide the string input_string at spaces. Skip multiple spaces. The segments
   which are formed are symbol-pairs. These are divided at colon-characters.
   The string of symbol-pairs, which is formed,  is coded into a KeyPairVector 
   according to the coding given by KeyTable * rule_keys. */
KeyPairVector * split_at_spaces(char * input_string)
{
  // Result vector contans the input symbol-pair string tokenized.
  KeyPairVector * tokenized_input = new KeyPairVector;
  
  // If something goes wrong, the original string may be printed 
  // as part of a debug-message.
  char * original_input_string = strdup(input_string);

  // A container for the string representations of the symbol-pairs, which
  // are obtained by splittng input_string at spaces. This is needed, since 
  // strtok can't be used in two tokenization tasks intertwined. Hence we need
  // to first split input_string into pairs and then split the pairs into 
  // symbols.
  SymbolNamePairVector symbol_name_pairs; 

  char * symbol_pair_string = strtok(input_string," ");    
  do {
    // Divide the symbol-pair string into symbol-pairs at spaces.
    // and store the pairs in symbol_name_pairs.
    if (symbol_pair_string != NULL)
      {
    symbol_name_pairs.push_back(symbol_pair_string);
      }
  } while ((symbol_pair_string = strtok(NULL," ")) != NULL);
  
  for(SymbolNamePairVector::iterator it = symbol_name_pairs.begin();
      it != symbol_name_pairs.end();
      ++it)
    {
      symbol_pair_string = *it;
      KeyPair * symbol_pair = 
    split_symbol_pair(symbol_pair_string);
      if (symbol_pair == NULL)
    {
      fprintf(stderr,
         "WARNING!\n"
         "The string \"%s\" can't be tokenized. It's likely, that it\n"
         "contains symbols not declared in the alphabet of the\n"
         "rule-transducers.\n",original_input_string);
      free(original_input_string);
      delete_key_pair_vector(tokenized_input);
      return NULL;
    }
      tokenized_input->push_back(symbol_pair);
    }
  free(original_input_string);
  return tokenized_input;
}

KeyPairVector * duplicate_keys(KeyVector * v) {
  KeyPairVector * pv = new KeyPairVector;
  for(KeyVector::iterator it = v->begin();
      it != v->end();
      ++it ) 
    {
      pv->push_back(new KeyPair(*it));
    }
  delete v;
  return pv;
}

KeyPairVector * construct_pair_vector(vector<KeyVector*> &input_fragments) 
{
  if (input_fragments.size() == 0)
    { return new KeyPairVector; }
  if (input_fragments.size() == 1)
    { return duplicate_keys(input_fragments.at(0)); }

  KeyPairVector * pairs = new KeyPairVector;
  Key previous_key(0);

  for(vector<KeyVector*>::iterator it = input_fragments.begin();
      it != input_fragments.end();
      ++it)
    {
      if (pairs == NULL)
    {
      delete *it;
      continue;
    }
      if ((*it)->empty())
    {
      delete pairs;
      pairs = NULL;
      delete *it;
      continue;
    }
      if (it == input_fragments.begin())
    {
      for(KeyVector::iterator jt = (*it)->begin();
          jt != (*it)->end() - 1;
          ++jt) 
        {
          pairs->push_back(new KeyPair(*jt));
        }
      Key last_key = *((*it)->end() - 1);
      previous_key = last_key;
    }
      else if (it+1 == input_fragments.end())
    {
      Key first_key = *((*it)->begin());
      pairs->push_back(new KeyPair(previous_key,first_key));
      for(KeyVector::iterator jt = (*it)->begin()+1;
          jt != (*it)->end();
          ++jt)
        {
          pairs->push_back(new KeyPair(*jt));
        }
    }
      else if ((*it)->size() < 2)
    {
      delete *it;
      delete pairs;
      pairs = NULL;
      continue;
    }
      else 
    {
      Key first_key = *((*it)->begin());
      pairs->push_back(new KeyPair(previous_key,first_key));
      for(KeyVector::iterator jt = (*it)->begin()+1;
          jt != (*it)->end() - 1;
          ++jt)
        {
          pairs->push_back(new KeyPair(*jt));
        }
      Key last_key = *((*it)->end() - 1);
      previous_key = last_key;
    }
    }
  return pairs;
}

/* Split input_string into fragments at colon-characters. Do a longest prefix 
   tokenization of the fragments obtained according to the coding given by 
   KeyTable * rule_keys. If one of the fragments can't be tokenized return 
   NULL. Build a KeyPairVector of the fragments by pairing up the last token 
   and the first token of two adjacent fragments. The first token of the first 
   fragment, the last token of the last fragment and all tokens n the middle of
   a fragment represent identity-pairs. */
KeyPairVector * tokenize(char * input_string) 
{

  vector<KeyVector*> input_fragments;
  char * original_input_string = strdup(input_string);
  char* last_start = input_string;
  char* colon = NULL;
  // using do-while{} because last uncolonized section must also be parsed.
  do {
  	colon = strchr(last_start, ':');
    if ((colon != NULL) && (colon == last_start))
    {
        // either absolute start is : or there is :: somewhere
        colon = strchr(last_start + 1, ':');
    }
    while ((colon != NULL) && (colon != input_string) &&
        (*(colon - 1) == '\\'))
    {
        colon = strchr(colon + 1 , ':');
    }
    char* input_fragment = NULL;
    if (colon != NULL)
    {
        input_fragment = static_cast<char*>(malloc(sizeof(char) *
                    (colon - last_start + 1)));
        input_fragment = static_cast<char*>(memcpy(input_fragment, last_start, colon - last_start));
        input_fragment[colon - last_start] = '\0';
    }
    else
    {
        input_fragment = strdup(last_start);
    }
    last_start = colon + 1;
#if 0
    fprintf(stderr, "*** DBG: input_fragment %s\n", input_fragment);
#endif
    KeyVector * tokenized_string_fragment =
      longest_match_tokenize(tokenizer,
                   input_fragment,
                   rule_keys);
    //replace_epsilons(tokenized_string_fragment);
    if (tokenized_string_fragment == NULL) {
      for(vector<KeyVector*>::iterator it = input_fragments.begin();
      it != input_fragments.end();
      ++it ) {
    delete *it;
      }
      fprintf(stderr,
          "WARNING!\n"
          "The string \"%s\" can't be tokenized. It's likely, that it\n"
          "contains symbols not declared in the alphabet of the\n"
          "rule-transducers.\n",original_input_string);
      free(original_input_string);
      return NULL;
    }
    input_fragments.push_back(tokenized_string_fragment);
  } while (colon != NULL);

  KeyPairVector * tokenized_input =
    construct_pair_vector(input_fragments);

  if (tokenized_input == NULL)
    {
      fprintf(stderr,
          "WARNING!\n"
          "The string \"%s\" can't be tokenized. It is syntactically\n"
          "incorrect in some way. Use option --help to find out more\n",
          original_input_string);
    }
  free(original_input_string);
  return tokenized_input;
}

void display_rule_keys(void)
{
  if ( rule_keys == NULL ) 
    {
      fprintf(stderr,"No key table stored with the rules.\n");
    }
  fprintf(stderr,"Key table\n");
  write_symbol_table(rule_keys,cout,false);
  fprintf(stderr,"\n");
}

/* Unless the key table rule_keys has been set, attempt to read a key table
   from the file named char * symbol_file_name. Do nothing, if rule_keys is
   already set. exit, if rule_keys is not set and alphabet cannot be read. */
void get_alphabet(char * symbol_file_name) 
{
  if ( rule_keys != NULL )
    {
      return;
    }
  if ( symbol_file_name == NULL )
    {
      fprintf(stderr,"Error: No alphabet supplied either with the rule\n"
          "transducers or in a separate file.\n");
      exit(1);
    }
  ifstream sym_in(symbol_file_name);
  rule_keys = read_symbol_table(sym_in);
  if ( rule_keys == NULL )
    {
      fprintf(stderr,"Error: The file %s doesn't contain a symbol table.\n",
          symbol_file_name);
      exit(1);
    }
}

/* Read the rule transducers either given in STDIN or the file whose name is
   fst_file_name. Return the rules in a FstVector. */
FstVector * read_rule_transducers(void)
{
  // Return the rule transducers in the container.
  FstVector * rules = new FstVector;
  
  // In case read fails, preserve the format given by read_format
  // in order to give diagnostics.
  int format = UNWEIGHTED;

  if ( fst_file_name == NULL ) 
    {
      // Count the rules, in order to display information.
      size_t counter = 0;
      if (not silent)
    fprintf(stderr,
        "Reading rule transducers from STDIN.\n"
        "(If this seems to take forever, please check\n"
        "that you're actually giving something as input)\n\n");
      while ((format = read_format()) == UNWEIGHTED)
    {
      if ( rule_keys == NULL and has_symbol_table(cin)) 
        {
          rule_keys = create_key_table();
          rules->push_back(read_transducer(cin,rule_keys));
        }
      else
        {
          rules->push_back(read_transducer());
        }
      if ( debug or verbose )
        fprintf(stderr,"Read rule: " SIZE_T_SPECIFIER "   \r",++counter);
    }
    }
  else
    {
      size_t counter = 0;
      ifstream fst_in(fst_file_name);
      while ((format = read_format(fst_in)) == UNWEIGHTED)
    {
      if ( rule_keys == NULL and has_symbol_table(fst_in)) 
        {
          rule_keys = create_key_table();
          rules->push_back(read_transducer(fst_in,rule_keys));
        }
      else
        {
          rules->push_back(read_transducer(fst_in));
        }
      if ( debug or verbose )
        fprintf(stderr,"Read rule: " SIZE_T_SPECIFIER "   \r",++counter);
    }
    }
  if ( debug or verbose )
    fprintf(stderr,"\n\n");
  if (rules->empty())
    {
      delete rules;
      fprintf(stderr,
          "No input transducers could be read.\n");
      if (format != EOF)
    {
      if (format == WEIGHTED)
        {
          fprintf(stderr,
              "Error: You gave weighted input transducers.\n");
        }
      else 
        {
          fprintf(stderr,
              "Error: Unknown input transducer format.\n");
        }
    }
      else
    {
      fprintf(stderr,
          "Error: The input transducer file is empty\n");

    }
      exit(1);
    }
  return rules;
}
} // namespace
