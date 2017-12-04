/*
 * A test file for functions in namespace hfst::rules.
 */

#include "HfstTransducer.h"
#include "auxiliary_functions.cc"

#include <cstdio>
#include <assert.h>
#include <fstream>

using namespace hfst;
;


void compare_and_delete(HfstTransducer * rule_transducers1[],
            HfstTransducer * rule_transducers2[],
            HfstTransducer * rule_transducers3[])
{

  if (not HfstTransducer::is_implementation_type_available
      (TROPICAL_OPENFST_TYPE))
    return;

  if (HfstTransducer::is_implementation_type_available(SFST_TYPE)) {
    rule_transducers1[0]->convert(TROPICAL_OPENFST_TYPE);
    rule_transducers2[0]->convert(TROPICAL_OPENFST_TYPE);
    rule_transducers3[0]->convert(TROPICAL_OPENFST_TYPE);
  }
  
  if (HfstTransducer::is_implementation_type_available(FOMA_TYPE)) {
    rule_transducers1[2]->convert(TROPICAL_OPENFST_TYPE);
    rule_transducers2[2]->convert(TROPICAL_OPENFST_TYPE);
    rule_transducers3[2]->convert(TROPICAL_OPENFST_TYPE);
  }
  
  if (HfstTransducer::is_implementation_type_available
      (SFST_TYPE)) {
    assert(rule_transducers1[0]->compare(*rule_transducers1[1]) );
    assert(rule_transducers2[0]->compare(*rule_transducers2[1]) );
    assert(rule_transducers3[0]->compare(*rule_transducers3[1]) );
  }

  if (HfstTransducer::is_implementation_type_available
      (FOMA_TYPE)) {
    assert(rule_transducers1[2]->compare(*rule_transducers1[1]) );
    assert(rule_transducers2[2]->compare(*rule_transducers2[1]) );
    assert(rule_transducers3[2]->compare(*rule_transducers3[1]) );
  }
  
  for (int i=0; i<3; i++) {
    if (rule_transducers1[i] != NULL)
      delete rule_transducers1[i];
    if (rule_transducers2[i] != NULL)
      delete rule_transducers2[i];
    if (rule_transducers3[i] != NULL)
      delete rule_transducers3[i];
  }
  
}

int main(int argc, char **argv) {
  
  ImplementationType types [] = {SFST_TYPE, TROPICAL_OPENFST_TYPE, FOMA_TYPE};
  HfstTransducer * rule_transducers1 [3] = {NULL, NULL, NULL};
  HfstTransducer * rule_transducers2 [3] = {NULL, NULL, NULL};
  HfstTransducer * rule_transducers3 [3] = {NULL, NULL, NULL};
  
  
  /* HfstTransducer two_level_if(
     HfstTransducerPair &context,
     StringPairSet &mappings,
     StringPairSet &alphabet,
     ImplementationType type); */
  
  verbose_print("HfstTransducer two_level_if("
		"HfstTransducerPair &context,"
		"StringPairSet &mappings,"
		"StringPairSet &alphabet,"
		"ImplementationType type");

  {
    for (int i=0; i<3; i++) {
      
      if (not HfstTransducer::is_implementation_type_available(types[i]))
	continue;
      
      HfstTransducer leftc("c", types[i]);
      HfstTransducer rightc("c", types[i]);
      HfstTransducerPair context(leftc, rightc);
      StringPair mapping("a", "b");
      StringPairSet mappings;
      mappings.insert(mapping);
      StringPairSet alphabet;
      alphabet.insert(StringPair("a", "a"));
      alphabet.insert(StringPair("a", "b"));
      alphabet.insert(StringPair("b", "b"));
      alphabet.insert(StringPair("c", "c"));
      

      HfstTransducer rule_transducer1
	= rules::two_level_if(context, mappings, alphabet);
      HfstTransducer rule_transducer2
	= rules::two_level_only_if(context, mappings, alphabet);
      HfstTransducer rule_transducer3
	= rules::two_level_if_and_only_if(context, mappings, alphabet);
      rule_transducers1[i] = new HfstTransducer(rule_transducer1);
      rule_transducers2[i] = new HfstTransducer(rule_transducer2);
      rule_transducers3[i] = new HfstTransducer(rule_transducer3);
    }
  }
  
  compare_and_delete(rule_transducers1,
		     rule_transducers2,
		     rule_transducers3);
  
  // replace_down_karttunen
  {
    for (int i=0; i<3; i++) {
      
      if (not HfstTransducer::is_implementation_type_available(types[i]))
	continue;
      
      HfstTokenizer TOK;
      TOK.add_multichar_symbol("@_EPSILON_SYMBOL_@");
      HfstTransducer mapping("ab", "x", TOK, types[i]);
      HfstTransducer left_context("ab", "ab", TOK, types[i]);
      HfstTransducer right_context("a", types[i]);
      HfstTransducerPair context(left_context, right_context);
      StringPairSet alphabet;
      alphabet.insert(StringPair("a", "a"));
      alphabet.insert(StringPair("b", "b"));
      alphabet.insert(StringPair("x", "x"));
      bool optional = false;
      
      HfstTransducer replace_down_transducer
	= rules::replace_down_karttunen(context, mapping, optional, alphabet);
      
      HfstTransducer test_abababa("abababa", TOK, types[i]);
      test_abababa.compose(replace_down_transducer);
      HfstTransducer abxaba("abababa",
			    "abx@_EPSILON_SYMBOL_@aba", TOK, types[i]);
      HfstTransducer ababxa("abababa",
			    "ababx@_EPSILON_SYMBOL_@a", TOK, types[i]);
      HfstTransducer expected_result(types[i]);
      expected_result.disjunct(abxaba);
      expected_result.disjunct(ababxa);
      assert(expected_result.compare(test_abababa));
    }
  }
  
#ifdef FOO
  /* HfstTransducer &replace_in_context(
     HfstTransducerPair &context,
     ReplaceType repl_type,
     HfstTransducer &t,
     bool optional,
     StringPairSet &alphabet) */
  
  verbose_print("HfstTransducer &replace_in_context("
		"HfstTransducerPair &context,"
		"ReplaceType repl_type,"
		"HfstTransducer &t,"
		"bool optional,"
		"StringPairSet &alphabet");
  
  for (int i=0; i<3; i++) {
    
    if (not HfstTransducer::is_implementation_type_available(types[i]))
      continue;
    
    HfstTransducer left("c",types[i]);
    HfstTransducer right("c",types[i]);
    HfstTransducerPair context(left,right);
    HfstTransducer mapping("a","b",types[i]);
    HfstTransducer mapping2("b","c",types[i]);
    mapping.disjunct(mapping2);
    StringPairSet alphabet;
    alphabet.insert(StringPair("a","a"));
    alphabet.insert(StringPair("b","b"));
    alphabet.insert(StringPair("c","c"));
    HfstTransducer rule = rules::replace_up(context, mapping, false, alphabet);
  }
#endif
 

  // replace_up for SFST in a special case that seems to fail sometimes

  if (HfstTransducer::is_implementation_type_available(SFST_TYPE))
    {
      ImplementationType type = SFST_TYPE;
      
      HfstBasicTransducer mapping;
      
      mapping.add_transition
	(0, HfstBasicTransition(1, "@_EPSILON_SYMBOL_@", "X", 0));
      mapping.set_final_weight(1, 0);
      
      mapping.add_transition
	(0, HfstBasicTransition(2, "@_UNKNOWN_SYMBOL_@", "X", 0));
      mapping.add_transition
	(0, HfstBasicTransition(2, "X", "X", 0));
      mapping.add_transition
	(2, HfstBasicTransition(2, "X", "@_EPSILON_SYMBOL_@", 0));
      mapping.add_transition
	(2, HfstBasicTransition
	 (2, "@_UNKNOWN_SYMBOL_@", "@_EPSILON_SYMBOL_@", 0));
      mapping.set_final_weight(2, 0);
      
      HfstTransducer mapping_(mapping, type);
      
      StringPairSet alphabet;
      alphabet.insert(StringPair("a", "a"));
      alphabet.insert(StringPair("b", "b"));
      alphabet.insert(StringPair("X", "X"));
      alphabet.insert(StringPair("K", "K"));
      
      bool optional = false;
      
      HfstTransducerPair context(HfstTransducer("K", "K", type),
				 HfstTransducer("K", "K", type));
      
      HfstTransducer rule
	= rules::replace_up(context, mapping_, optional, alphabet);
      
      HfstTokenizer TOK;
      
      HfstTransducer abKabKab("abKabKab", TOK, type);
      
      abKabKab.compose(rule).minimize();
      
      HfstTransducer abKabKab_("abKabKab", TOK, type);
      
      assert(not abKabKab.compare(abKabKab_));
      
    }
  
}

