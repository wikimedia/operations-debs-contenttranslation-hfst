/*
   Test file for HfstTransducer constructors, destructor, operator=
   and member functions set_name, get_name and get_type.
*/

#include "HfstTransducer.h"
#include "auxiliary_functions.cc"

using namespace hfst;
using hfst::implementations::HfstBasicTransducer;
using hfst::implementations::HfstBasicTransition;


int main(int argc, char **argv) 
{

  const unsigned int TYPES_SIZE=3;
  const ImplementationType types [] = {SFST_TYPE, 
                       TROPICAL_OPENFST_TYPE, 
                       /*LOG_OPENFST_TYPE,*/ 
                       FOMA_TYPE};

  for (unsigned int i=0; i<TYPES_SIZE; i++)
    {
      if (not HfstTransducer::is_implementation_type_available(types[i]))
	continue;

      /* The empty transducer. */
      verbose_print("The empty transducer", types[i]);
      HfstTransducer empty(types[i]);

      /* The epsilon transducer. */
      verbose_print("The epsilon transducer", types[i]);
      HfstTransducer epsilon("@_EPSILON_SYMBOL_@", types[i]);

      /* One-transition transducer. */
      verbose_print("One-transition transducer", types[i]);
      HfstTransducer foo("foo", types[i]);
      HfstTransducer foobar("foo", "bar", types[i]);

      /* The copy constructor. */
      verbose_print("The copy constructor", types[i]);
      HfstTransducer foobar_copy(foobar);
      assert(foobar.compare(foobar_copy));

      /* Conversion from HfstBasicTransducer. */
      verbose_print("Conversion from HfstBasicTransducer", types[i]);
      HfstBasicTransducer basic;
      basic.add_state(1);
      basic.add_transition(0, HfstBasicTransition(1, "foo", "bar", 0));
      basic.set_final_weight(1, 0);
      HfstTransducer foobar_basic(basic, types[i]);
      assert(foobar.compare(foobar_basic));

      /* By tokenizing. */
      verbose_print("Construction by tokenization", types[i]);
      HfstTokenizer tok;
      tok.add_skip_symbol("baz");
      tok.add_multichar_symbol("foo");
      tok.add_multichar_symbol("bar");
      HfstTransducer foo_tok("bazfoobaz", tok, types[i]);
      HfstTransducer foobar_tok("bazfoo", "barbaz", tok, types[i]);
      assert(foo.compare(foo_tok));
      assert(foobar.compare(foobar_tok));

      /* From AT&T format. */
      verbose_print("Construction from AT&T format", types[i]);
      FILE * file = fopen((std::string(getenv("srcdir")) + 
               std::string("/foobar.att")).c_str(), "rb");
      assert(file != NULL);
      unsigned int linecount = 0;
      HfstTransducer foobar_att(file, types[i], "@0@", linecount);
      (void)linecount;
      fclose(file);
      foobar_att.minimize();

      assert(foobar.compare(foobar_att));

      /* From HfstInputStream. 
     Tests also functions get_type, set_name and get_name. */
      verbose_print("Construction from HfstInputStream", types[i]);
      HfstOutputStream out("testfile.hfst", foobar.get_type());
      foobar.set_name("foobar");
      out << foobar;
      out.close();
      HfstInputStream in("testfile.hfst");
      HfstTransducer foobar_stream(in);
      in.close();
      remove("testfile.hfst");
      assert(foobar.compare(foobar_stream));
      assert(foobar_stream.get_name().compare("foobar") == 0);
      assert(foobar_stream.get_type() == types[i]);

      /* Destructor. */
      verbose_print("Destructor", types[i]);
      HfstTransducer * nu = new HfstTransducer("new", types[i]);
      delete nu;

      /* Operator=. */
      verbose_print("Operator=", types[i]);
      HfstTransducer foobar2("baz", types[i]);
      assert(foobar.get_name().compare("foobar") == 0);
      foobar2 = foobar;
      assert(foobar2.get_name().compare("foobar") == 0);
      assert(foobar.compare(foobar2));
      HfstTransducer empty_ol(HFST_OL_TYPE);
      HfstTransducer empty_olw(HFST_OLW_TYPE);
      /* reserving props in copy constructor (bug: #3405831) */
      HfstTransducer t("a",TROPICAL_OPENFST_TYPE);
      t.convert(HFST_OLW_TYPE);
      t.set_name("foo");
      HfstTransducer s(t);
      assert(s.get_name() == t.get_name());
      try {
        empty_ol = foobar2.convert(HFST_OL_TYPE);
        empty_olw = foobar2.convert(HFST_OLW_TYPE);
	assert(empty_ol.get_name().compare("foobar") == 0);
	assert(empty_olw.get_name().compare("foobar") == 0);
      }
      catch (const FunctionNotImplementedException e)
	{
	  assert(false);
	}

    }

}
