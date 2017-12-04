#include "HfstTransducer.h"

int main(int argc, char **argv)
{
  using namespace hfst;
  using namespace hfst::lexc;

  const unsigned int TYPES_SIZE=3;//4;
  const ImplementationType types [] = {SFST_TYPE,
                       TROPICAL_OPENFST_TYPE,
                       /*LOG_OPENFST_TYPE,*/
                       FOMA_TYPE};

   const char* srcdirc = getenv("srcdir");
   if (srcdirc == 0)
     {
       srcdirc = "./";
     }
   std::string srcdir(srcdirc);
  /* For all transducer implementation types, perform the following tests: */
  for (unsigned int i=0; i<TYPES_SIZE; i++)
    {

      if (not HfstTransducer::is_implementation_type_available(types[i]))
        {
          continue;
        }

      // Test the lexc parser:
      fprintf(stderr, "Testing type %d... ", i);
      // (1) A file in valid lexc format
      fprintf(stderr, "valid file, parse... ", i);
      LexcCompiler compiler(types[i]);
      compiler.parse((srcdir + std::string("/test_lexc.lexc")).c_str());
      HfstTransducer * parsed = compiler.compileLexical();
      assert(parsed != 0);
      HfstTokenizer tok;
      HfstTransducer cat("cat", tok, types[i]);
      HfstTransducer dog("dog", tok, types[i]);
      HfstTransducer mouse("mouse", tok, types[i]);

      HfstTransducer animals(types[i]);
      animals.disjunct(cat);
      animals.disjunct(dog);
      animals.disjunct(mouse);

      assert(animals.compare(*parsed));
      delete parsed;
  
      

      try
        {
          fprintf(stderr, "valid file, read_lexc... ", i);
          HfstTransducer * rlexc
             = HfstTransducer::read_lexc(srcdir + "/test_lexc.lexc", types[i]);
          assert(rlexc != 0);
          assert(animals.compare(*rlexc));
          delete rlexc;
        }
      catch (FunctionNotImplementedException e)
        {
          assert(false);
        }

      // (2) A file that does not follow lexc format
      LexcCompiler compiler2(types[i]);
      fprintf(stderr, "invalid file, parse... ", i);
      compiler2.parse((srcdir + std::string("/test_lexc_fail.lexc")).c_str());
      parsed = compiler2.compileLexical();
      assert(parsed == 0);

      // (3) A file that does not exist
      LexcCompiler compiler3(types[i]);
      fprintf(stderr, "missing file, parse... ", i);
      compiler3.parse((srcdir + std::string("/nonexistent.lexc")).c_str());
      parsed = compiler3.compileLexical();
      assert(parsed == 0);
      // (2) A file that does not follow lexc format
      /*try {
    HfstTransducer * rlexc
      = HfstTransducer::read_lexc
      (std::string(getenv("srcdir")) + "/test_lexc_fail.lexc", types[i]);
    assert(false);
      }
      catch (FunctionNotImplementedException e) {
    assert(false);
      }
      catch (NotValidLexcFormatException e) {
    ;
    }*/

      // (3) A file that does not exist
      /*try {
    HfstTransducer * rlexc
      = HfstTransducer::read_lexc
      (std::string(getenv("srcdir")) +
       "/a_test_file_that_does_not_exist.o2f393480f31fsfgqe", types[i]);
    assert(false);
      }
      catch (FunctionNotImplementedException e) {
    assert(false);
      }
      catch (StreamNotReadableException e) {
    ;
    }*/

    }

}
