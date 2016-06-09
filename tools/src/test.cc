/*
 * test.cc: A test file for hfst3
 */

#include "HfstTransducer.h"
#include <cstdio>
#include <assert.h>

using namespace hfst;

void print(HfstInternalTransducer &t)
{
  HfstStateIterator it(t);
  while (not it.done()) {
    HfstState s = it.value();
    HfstTransitionIterator IT(t,s);
    while (not IT.done()) {
      //fprintf(stderr, "loop starts\n");
      HfstTransition tr = IT.value();
      //fprintf(stderr, "transition\n");
      cout << s << "\t" << tr.get_target_state() << "\t"
       << tr.get_input_symbol() << "\t" << tr.get_output_symbol()
       << "\t" << tr.get_weight();
      cout << "\n";
      IT.next();
    }
    if ( t.is_final(s) )
      cout << s << "\t" << t.get_final_weight(s) << "\n";
    it.next();
  }
  return;
}


int main(int argc, char **argv) {

  ImplementationType types[] = {SFST_TYPE, TROPICAL_OPENFST_TYPE, LOG_OPENFST_TYPE, FOMA_TYPE};
  for (int i=0; i<4; i++) {
    {
      // Test the empty transducer constructors for all implementation types.
      HfstTransducer tr(types[i]);
      assert (tr.get_type() == types[i]);
      for (int j=0; j<4; j++) {
    // Test the conversions.
    HfstTransducer trconv = tr.convert(types[j]);
    assert (tr.get_type() == types[j]);
    assert (HfstTransducer::test_equivalence(tr, trconv));
    HfstTransducer tranother(types[j]);
    assert (HfstTransducer::test_equivalence(tr, tranother));
      }
      HfstInternalTransducer mut(tr);
      HfstTransducer foo(mut);
      assert (HfstTransducer::test_equivalence(tr, foo));
    }
    printf("Empty constructors tested on transducers of type %i.\n", types[i]);
    {
      // Test the one-transition transducer constructors for all implementation types.
      HfstTransducer tr("foo", types[i]);
      assert (tr.get_type() == types[i]);
      for (int j=0; j<4; j++) {
    // Test the conversions.
    HfstTransducer trconv = tr.convert(types[j]);
    assert (tr.get_type() == types[j]);
    assert (HfstTransducer::test_equivalence(tr, trconv));
    HfstTransducer tranother("foo", types[j]);
    assert (HfstTransducer::test_equivalence(tr, tranother));
      }
      HfstInternalTransducer mut(tr);
      HfstTransducer foo(mut);
      assert (HfstTransducer::test_equivalence(tr, foo));
    }
    printf("One-transition constructors tested on transducers of type %i.\n", types[i]);
    {
      // Test the two-transition transducer constructors for all implementation types.
      HfstTransducer tr("foo", "bar", types[i]);
      assert (tr.get_type() == types[i]);
      for (int j=0; j<4; j++) {
    // Test the conversions.
    HfstTransducer trconv = tr.convert(types[j]);
    assert (tr.get_type() == types[j]);
    assert (HfstTransducer::test_equivalence(tr, trconv));
    HfstTransducer tranother("foo", "bar", types[j]);
    assert (HfstTransducer::test_equivalence(tr, tranother));
    // test the att format
    tr.write_in_att_format("testfile");
    HfstTransducer foo = HfstTransducer::read_in_att_format("testfile");
    assert (HfstTransducer::test_equivalence(tr, foo));
      }
      HfstInternalTransducer mut(tr);
      HfstTransducer foo(mut);
      assert (HfstTransducer::test_equivalence(tr, foo));
    }
    printf("Two-transition constructors tested on transducers of type %i.\n", types[i]);
    {
      // Test the one-string transducer constructors for all implementation types.
      HfstTokenizer tok;
      tok.add_multichar_symbol("foo");
      tok.add_multichar_symbol("bar");
      HfstTransducer tr("foobar", tok, types[i]);
      assert (tr.get_type() == types[i]);
      for (int j=0; j<4; j++) {
    // Test the conversions.
    HfstTransducer trconv = tr.convert(types[j]);
    assert (tr.get_type() == types[j]);
    assert (HfstTransducer::test_equivalence(tr, trconv));
    HfstTransducer tranother("foobar", tok, types[j]);
    assert (HfstTransducer::test_equivalence(tr, tranother));
      }
      HfstInternalTransducer mut(tr);
      HfstTransducer foo(mut);
      assert (HfstTransducer::test_equivalence(tr, foo));
    }
    printf("One-string constructors tested on transducers of type %i.\n", types[i]);
    {
      // Test the two-string transducer constructors for all implementation types.
      HfstTokenizer tok;
      tok.add_multichar_symbol("foo");
      tok.add_multichar_symbol("bar");
      HfstTransducer tr("fofoo", "barbarba", tok, types[i]);
      assert (tr.get_type() == types[i]);
      for (int j=0; j<4; j++) {
    // Test the conversions.
    HfstTransducer trconv = tr.convert(types[j]);
    assert (tr.get_type() == types[j]);
    assert (HfstTransducer::test_equivalence(tr, trconv));
    HfstTransducer tranother("fofoo", "barbarba", tok, types[j]);
    assert (HfstTransducer::test_equivalence(tr, tranother));
      }
      HfstInternalTransducer mut(tr);
      HfstTransducer foo(mut);
      assert (HfstTransducer::test_equivalence(tr, foo));
    }
    printf("Two-string constructors tested on transducers of type %i.\n", types[i]);
  }

  {
      HfstTransducer foo = HfstTransducer::read_in_att_format("test_transducer.att");
      HfstTransducer test0 = HfstTransducer(foo);
      HfstTransducer test1 = HfstTransducer(foo);
      HfstTransducer test2 = HfstTransducer(foo);
      HfstTransducer test3 = HfstTransducer(foo);
      test0.convert(types[0]);
      test1.convert(types[1]);
      test2.convert(types[2]);
      test3.convert(types[3]);

      assert ( test0.get_type() !=
           test1.get_type() !=
           test2.get_type() !=
           test3.get_type() );
      

      // ----- repeat_star -----
      {
    HfstTransducer test0_plus = HfstTransducer(test0).repeat_plus(); 
    HfstTransducer test1_plus = HfstTransducer(test1).repeat_plus();
    HfstTransducer test2_plus = HfstTransducer(test2).repeat_plus();
    HfstTransducer test3_plus = HfstTransducer(test3).repeat_plus();
    
    assert ( test0_plus.get_type() !=
         test1_plus.get_type() !=
         test2_plus.get_type() !=
         test3_plus.get_type() );

    assert (HfstTransducer::test_equivalence( test0_plus, test1_plus ) );
    assert (HfstTransducer::test_equivalence( test0_plus, test2_plus ) );
    assert (HfstTransducer::test_equivalence( test0_plus, test3_plus ) );
      }
      printf("repeat_star tested\n");


      // ----- repeat_plus -----
      {
    HfstTransducer test0_plus = HfstTransducer(test0).repeat_plus();      
    HfstTransducer test1_plus = HfstTransducer(test1).repeat_plus();
    HfstTransducer test2_plus = HfstTransducer(test2).repeat_plus();
    HfstTransducer test3_plus = HfstTransducer(test3).repeat_plus();
    
    assert ( test0_plus.get_type() !=
         test1_plus.get_type() !=
         test2_plus.get_type() !=
         test3_plus.get_type() );

    assert (HfstTransducer::test_equivalence( test0_plus, test1_plus ) );
    assert (HfstTransducer::test_equivalence( test0_plus, test2_plus ) );
    assert (HfstTransducer::test_equivalence( test0_plus, test3_plus ) );
      }
      printf("repeat_plus tested\n");


      // ----- repeat_n -----
      {
    const int MAX_REPEAT_N = 5; 
    for (int n=0; n <= MAX_REPEAT_N; n++) {

      HfstTransducer test0_n = HfstTransducer(test0).repeat_n(n); 
      HfstTransducer test1_n = HfstTransducer(test1).repeat_n(n);
      HfstTransducer test2_n = HfstTransducer(test2).repeat_n(n);
      HfstTransducer test3_n = HfstTransducer(test3).repeat_n(n);
    
    assert ( test0_n.get_type() !=
         test1_n.get_type() !=
         test2_n.get_type() !=
         test3_n.get_type() );

      assert (HfstTransducer::test_equivalence( test0_n, test1_n ) );
      assert (HfstTransducer::test_equivalence( test0_n, test2_n ) );
      assert (HfstTransducer::test_equivalence( test0_n, test3_n ) );
    }
      }
      printf("repeat_n tested\n");


      // ----- repeat_n_minus -----
      {
    const int MAX_REPEAT_N = 5; 
    for (int n=0; n <= MAX_REPEAT_N; n++) {
      HfstTransducer test0_n = HfstTransducer(test0).repeat_n_minus(n); 
      HfstTransducer test1_n = HfstTransducer(test1).repeat_n_minus(n);
      HfstTransducer test2_n = HfstTransducer(test2).repeat_n_minus(n);
      HfstTransducer test3_n = HfstTransducer(test3).repeat_n_minus(n);
    
      assert ( test0_n.get_type() !=
           test1_n.get_type() !=
           test2_n.get_type() !=
           test3_n.get_type() );

      assert (HfstTransducer::test_equivalence( test0_n, test1_n ) );
      assert (HfstTransducer::test_equivalence( test0_n, test2_n ) );
      assert (HfstTransducer::test_equivalence( test0_n, test3_n ) );
    }
      }
      printf("repeat_n_minus tested\n");


      // ----- repeat_n_plus -----
      {
    const int MAX_REPEAT_N = 1; 
    for (int n=0; n <= MAX_REPEAT_N; n++) {
      HfstTransducer test0_n = HfstTransducer(test0).repeat_n_plus(n); 
      HfstTransducer test1_n = HfstTransducer(test1).repeat_n_plus(n);
      HfstTransducer test2_n = HfstTransducer(test2).repeat_n_plus(n);
      HfstTransducer test3_n = HfstTransducer(test3).repeat_n_plus(n);
    
      assert ( test0_n.get_type() !=
           test1_n.get_type() !=
           test2_n.get_type() !=
           test3_n.get_type() );

      assert (HfstTransducer::test_equivalence( test0_n, test1_n ) );
      assert (HfstTransducer::test_equivalence( test0_n, test2_n ) );
      assert (HfstTransducer::test_equivalence( test0_n, test3_n ) );     
    }
      }
      printf("repeat_n_plus tested\n");


      // ----- repeat_n_to_k -----
      {
    const int REPEAT_N_MAX = 2; 
    const int REPEAT_K_MAX = 3;
    for (int n=0; n <= REPEAT_N_MAX; n++) {
      for (int k=n; k <= REPEAT_K_MAX; k++) {
        HfstTransducer test0_n = HfstTransducer(test0).repeat_n_to_k(n,k); 
        HfstTransducer test1_n = HfstTransducer(test1).repeat_n_to_k(n,k);
        HfstTransducer test2_n = HfstTransducer(test2).repeat_n_to_k(n,k);
        HfstTransducer test3_n = HfstTransducer(test3).repeat_n_to_k(n,k);
        
        assert ( test0_n.get_type() !=
             test1_n.get_type() !=
             test2_n.get_type() !=
             test3_n.get_type() );

        assert (HfstTransducer::test_equivalence( test0_n, test1_n ) );
        assert (HfstTransducer::test_equivalence( test0_n, test2_n ) );
        assert (HfstTransducer::test_equivalence( test0_n, test3_n ) );
      }
    }
      }
      printf("repeat_n_to_k tested\n");

      
      // ----- optionalize -----
      {
    HfstTransducer test0_opt = HfstTransducer(test0).optionalize();      
    HfstTransducer test1_opt = HfstTransducer(test1).optionalize();
    HfstTransducer test2_opt = HfstTransducer(test2).optionalize();
    HfstTransducer test3_opt = HfstTransducer(test3).optionalize();
    
    assert ( test0_opt.get_type() !=
         test1_opt.get_type() !=
         test2_opt.get_type() !=
         test3_opt.get_type() );

    assert (HfstTransducer::test_equivalence( test0_opt, test1_opt ) );
    assert (HfstTransducer::test_equivalence( test0_opt, test2_opt ) );
    assert (HfstTransducer::test_equivalence( test0_opt, test3_opt ) );
      }
      printf("optionalize tested\n");


  }
  return 0;
}


#ifdef FOO

  // create transducer t1
  HfstInternalTransducer t1;
  HfstState second_state1 = t1.add_state();
  HfstState third_state1 = t1.add_state();
  t1.set_final_weight(second_state1, 0.5);
  t1.add_transition(0, "foo", "bar", 0.3, second_state1);
  t1.add_transition(second_state1, "@_UNKNOWN_SYMBOL_@", "@_UNKNOWN_SYMBOL_@", 0.2, third_state1);
  t1.add_transition(third_state1, "@_IDENTITY_SYMBOL_@", "@_IDENTITY_SYMBOL_@", 0.1, second_state1);

  // create transducer t2
  HfstInternalTransducer t2;
  HfstState second_state2 = t2.add_state();
  t2.set_final_weight(second_state2, 0.3);
  t2.add_transition(0, "@_UNKNOWN_SYMBOL_@", "baz", 1.6, second_state2);


  HfstTokenizer TOK;
  TOK.add_multichar_symbol("foo");
  TOK.add_multichar_symbol("bar");
  HfstTransducer TOK_TR("fooofoooa", "barrbabarr", TOK, TROPICAL_OPENFST_TYPE);
  TOK_TR.print();

  HfstTokenizer TOK2;
  TOK2.add_multichar_symbol("fii");
  TOK2.add_multichar_symbol("baar");
  HfstTransducer TOK_TR2("foofii", "barbaarq", TOK2, TROPICAL_OPENFST_TYPE);
  TOK_TR2.print();

  HfstTransducer TOK_CAT = TOK_TR.concatenate(TOK_TR2);
  TOK_CAT.print();


  ImplementationType types[] = {TROPICAL_OPENFST_TYPE, LOG_OPENFST_TYPE, SFST_TYPE, FOMA_TYPE};
  for (int i=0; i<4; i++) 
    {      
      fprintf(stderr, "testing transducers of type %i\n", types[i]);

      // open two output streams to file
      HfstOutputStream out1("test1.hfst", types[i]);
      out1.open();
      HfstOutputStream out2("test2.hfst", types[i]);
      out2.open();

      // convert both transducers and write them to the streams
      HfstTransducer T1(t1);
      T1 = T1.convert(types[i]);
      HfstTransducer T2(t2);
      T2 = T2.convert(types[i]);
      out1 << T1;
      out1 << T2;
      out2 << T2;
      out2 << T1;
      out1.close();
      out2.close();

      // open two input streams to the files
      HfstInputStream in1("test1.hfst");
      in1.open();
      HfstInputStream in2("test2.hfst");
      in2.open();

      while (not in1.is_eof() && not in2.is_eof()) {
    fprintf(stderr, " while loop\n");
    HfstTransducer tr1(in1);
    HfstTransducer tr2(in2);

    { HfstTransducer t = tr1.compose(tr2);
      fprintf(stderr, "  composed\n"); }
    { HfstTransducer t = tr1.intersect(tr2);
      fprintf(stderr, "  intersected\n"); }
    { HfstTransducer t = tr1.disjunct(tr2);
      fprintf(stderr, "  disjuncted\n"); }
    { HfstTransducer t = tr1.concatenate(tr2);
      fprintf(stderr, "  concatenated\n"); }
    { HfstTransducer t = tr1.subtract(tr2);
      fprintf(stderr, "  subtracted\n"); }

    { HfstTransducer t = tr1.remove_epsilons();
      fprintf(stderr, "  removed epsilons\n"); }
    { HfstTransducer t = tr1.determinize();
      fprintf(stderr, "  determinized\n"); }
    { HfstTransducer t = tr1.minimize();
      fprintf(stderr, "  minimized\n"); }

    { HfstTransducer t = tr1.repeat_star();
      fprintf(stderr, "  repeated star\n"); }
    { HfstTransducer t = tr1.repeat_plus();
      fprintf(stderr, "  repeated plus\n"); }
    { HfstTransducer t = tr1.repeat_n(3);
      fprintf(stderr, "  repeated n\n"); }
    { HfstTransducer t = tr1.repeat_n_minus(3);
      fprintf(stderr, "  repeated n minus\n"); }
    { HfstTransducer t = tr1.repeat_n_plus(3);
      fprintf(stderr, "  repeated n plus\n"); }
    { HfstTransducer t = tr1.repeat_n_to_k(1, 4);
      fprintf(stderr, "  repeated n to k\n"); }
    { HfstTransducer t = tr1.optionalize();
      fprintf(stderr, "  optionalized\n"); }

    { HfstTransducer t = tr1.invert();
      fprintf(stderr, "  inverted\n"); }
    { HfstTransducer t = tr1.input_project();
      fprintf(stderr, "  input projected\n"); }
    { HfstTransducer t = tr1.output_project();
      fprintf(stderr, "  output projected\n"); }
    { HfstTransducer t = tr1.reverse();
      fprintf(stderr, "  reversed\n"); }
    { HfstTransducer t = tr1.substitute(std::string(),
                        std::string();
      fprintf(stderr, "  substituted string\n"); }
    { HfstTransducer t = tr1.substitute(const StringSymbolPair &old_symbol_pair,
                        const StringSymbolPair &new_symbol_pair);
      fprintf(stderr, "  substituted string pair\n"); }

      }

      remove("test1.hfst");
      remove("test2.hfst");

    }

  return 0;
}

#endif






#ifdef foo

    HfstTransducer &remove_epsilons(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &determinize(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &minimize(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &n_best(int n,ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &repeat_star(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &repeat_plus(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &repeat_n(unsigned int n,
                       ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &repeat_n_minus(unsigned int n,
                       ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &repeat_n_plus(unsigned int n,
                       ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer& repeat_n_to_k(unsigned int n, unsigned int k,
                       ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &optionalize(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &invert(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &input_project(ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &output_project(ImplementationType type=UNSPECIFIED_TYPE);
    void extract_paths(WeightedStrings<float>::Set &results);
    HfstTransducer &substitute(Key old_key, Key new_key);
    HfstTransducer &substitute(const std::string &old_symbol,
                   const std::string &new_symbol);
    HfstTransducer &substitute(const KeyPair &old_key_pair, 
                   const KeyPair &new_key_pair);
    HfstTransducer &substitute(const StringSymbolPair &old_symbol_pair,
                   const StringSymbolPair &new_symbol_pair);
    HfstTransducer &compose(HfstTransducer &another,
                ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &concatenate(HfstTransducer &another,
                ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &disjunct(HfstTransducer &another,
                 ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &intersect(HfstTransducer &another,
                  ImplementationType type=UNSPECIFIED_TYPE);
    HfstTransducer &subtract(HfstTransducer &another,
                 ImplementationType type=UNSPECIFIED_TYPE);



  fprintf(stderr, "disjunction:\n");

  HfstTransducer DISJ = T1.disjunct(T1, SFST_TYPE);

  fprintf(stderr, "disjunction done\n");

  HfstInternalTransducer Disj = HfstInternalTransducer(DISJ);
  fprintf(stderr, "converted to internal\n");
  print(Disj);


  //HfstTransducer T(t);
  ImplementationType type = T.get_type();
  //fprintf(stderr, "%i\n", type);

  //fprintf(stderr, "main: (1)\n");
  T = T.convert(FOMA_TYPE);
  //fprintf(stderr, "main: (1.5)\n");

  HfstTransducer Tcopy = HfstTransducer(T);
  //fprintf(stderr, "main: (1.51)\n");
  HfstTransducer disj = T.disjunct(Tcopy, FOMA_TYPE);

  //fprintf(stderr, "main: (2)\n");
  T = T.convert(SFST_TYPE);
  //fprintf(stderr, "main: (3)\n");
  T = T.convert(TROPICAL_OPENFST_TYPE);
  //fprintf(stderr, "main: (4)\n");
  T = T.convert(FOMA_TYPE);
  //fprintf(stderr, "main: (5)\n");
  type = T.get_type();
  //fprintf(stderr, "%i\n", type);
  //HfstOutputStream os(FOMA_TYPE);
  //os << T;
  //fprintf(stderr, "\n\n");
  //cout << T;
  //fprintf(stderr, "\n");
  //fprintf(stderr, "main: (6)\n");
  // FIX: calling ~HfstTransducer causes a glibc with foma
  return 0;
#endif

