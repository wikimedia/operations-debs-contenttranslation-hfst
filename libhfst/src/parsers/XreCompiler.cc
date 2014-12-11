//! @file XreCompiler.cc
//!
//! @brief Functions for building transducers from Xerox regexps

#include "XreCompiler.h"
#include "xre_utils.h"
#include "HfstTransducer.h"

#ifndef UNIT_TEST

namespace hfst { namespace xre {

    unsigned int cr=0;
    std::set<unsigned int> positions;
    char * position_symbol = NULL;
    std::string error_message;

XreCompiler::XreCompiler() : 
    definitions_(),
    function_definitions_(),
    function_arguments_(),
    format_(hfst::TROPICAL_OPENFST_TYPE)
{}

XreCompiler::XreCompiler(hfst::ImplementationType impl) :
    definitions_(),
    function_definitions_(),
    function_arguments_(),
    format_(impl)
{}

void
XreCompiler::define(const std::string& name, const std::string& xre)
{
  HfstTransducer* compiled = compile(xre);
  if (compiled == NULL)
    {
      fprintf(stderr, "error in XreCompiler::define: xre '%s' could not be parsed, leaving %s undefined\n", 
              xre.c_str(), name.c_str());
      return;
    }
  definitions_[name] = compiled;
}

void
XreCompiler::define(const std::string& name, const HfstTransducer & transducer)
{
  definitions_[name] = new HfstTransducer(transducer);
}

bool
XreCompiler::define_function(const std::string& name, 
                             unsigned int arguments,
                             const std::string& xre)
{ 
  //fprintf(stderr, "XreCompiler: defining function %s(@%i) = [%s]\n", name.c_str(), arguments, xre.c_str()); // DEBUG
  function_arguments_[name] = arguments;
  function_definitions_[name] = xre;
  return true;
}

bool
XreCompiler::is_definition(const std::string & name)
{
  if (definitions_.find(name) != definitions_.end())
    return true;
  return false;
}

bool
XreCompiler::is_function_definition(const std::string & name)
{
  if (function_definitions_.find(name) != function_definitions_.end())
    return true;
  return false;
}

void
XreCompiler::undefine(const std::string& name) 
{
if (definitions_.find(name) != definitions_.end())
  {
    definitions_.erase(name);
  }
}

extern bool expand_definitions;
extern bool harmonize_;
extern bool harmonize_flags_;
extern bool verbose_;
extern FILE * warning_stream;

void XreCompiler::set_expand_definitions(bool expand)
{
  expand_definitions=expand;
}

void XreCompiler::set_harmonization(bool harmonize)
{
  harmonize_=harmonize;
}

void XreCompiler::set_flag_harmonization(bool harmonize_flags)
{
  harmonize_flags_=harmonize_flags;
}

void XreCompiler::set_verbosity(bool verbose, FILE * file)
{
  verbose_=verbose;
  if (verbose)
    {
      warning_stream=file;
    }
}

std::string 
XreCompiler::get_error_message()
{
  return error_message;
}

bool
XreCompiler::contained_only_comments()
{
  return contains_only_comments;
}

HfstTransducer*
XreCompiler::compile(const std::string& xre)
{
  return hfst::xre::compile(xre, definitions_, function_definitions_, function_arguments_, format_);
}

HfstTransducer*
XreCompiler::compile_first(const std::string& xre, unsigned int & chars_read)
{
  return hfst::xre::compile_first(xre, definitions_, function_definitions_, function_arguments_, format_, chars_read);
}

bool XreCompiler::get_positions_of_symbol_in_xre
(const std::string & symbol, const std::string & xre, std::set<unsigned int> & positions_)
{
  position_symbol = strdup(symbol.c_str());
  positions.clear();
  cr=0;
  HfstTransducer * compiled = 
    hfst::xre::compile(xre, definitions_, function_definitions_, function_arguments_, format_);
  free(position_symbol);
  position_symbol = NULL;
  if (compiled == NULL)
    {
      /*fprintf(stderr, "error in XreCompiler::get_positions_of_symbol_in_xre: xre '%s' "
              "could not be parsed, positions of symbol %s not found\n", 
              xre.c_str(), symbol.c_str());*/
      return false;
    }
  positions_ = positions;
  return true;
}

}}

#else // UNIT_TEST
#include <cstdlib>
#include <cassert>

using namespace hfst;
using namespace hfst::xre;

extern int xredebug;

int
main(int, char**)
  {
    std::cout << "Unit tests for " __FILE__ ":";
    std::cout << std::endl << "constructors: ";
    std::cout << " (default)...";
    XreCompiler defaultXre();
#if HAVE_SFST
    std::cout << " (SFST)...";
    XreCompiler sfstXre = XreCompiler(SFST_TYPE);
#endif
#if HAVE_OPENFST
    std::cout << " (OpenFst)...";
    XreCompiler ofstXre = XreCompiler(TROPICAL_OPENFST_TYPE);
#endif
#if HAVE_FOMA
    std::cout << " (Foma)...";
    XreCompiler fomaXre = XreCompiler(FOMA_TYPE);
#endif
    HfstBasicTransducer basicCat;
    basicCat.add_state(1);
    basicCat.add_state(2);
    basicCat.add_state(3);
    basicCat.add_transition(0, HfstBasicTransition(1, "c", "c", 0));
    basicCat.add_transition(1, HfstBasicTransition(2, "a", "a", 0));
    basicCat.add_transition(2, HfstBasicTransition(3, "t", "t", 0));
    basicCat.set_final_weight(3, 0);
    HfstBasicTransducer basicFight;
    basicFight.add_state(1);
    basicFight.add_state(2);
    basicFight.add_state(3);
    basicFight.add_state(4);
    basicFight.add_state(5);
    basicFight.add_state(6);
    basicFight.add_transition(0, HfstBasicTransition(1, "f", "f", 0));
    basicFight.add_transition(1, HfstBasicTransition(2, "i", "o", 0));
    basicFight.add_transition(2, HfstBasicTransition(3, hfst::internal_epsilon,
                                                     "u", 0));
    basicFight.add_transition(3, HfstBasicTransition(4, "g", "g", 0));
    basicFight.add_transition(4, HfstBasicTransition(5, "h", "h", 0));
    basicFight.add_transition(5, HfstBasicTransition(6, "t", "t", 0));
    basicFight.set_final_weight(6, 0);
    HfstBasicTransducer basicCatOrDog;
    basicCatOrDog.add_state(1);
    basicCatOrDog.add_state(2);
    basicCatOrDog.add_state(3);
    basicCatOrDog.add_transition(0, HfstBasicTransition(1, "c", "c", 0));
    basicCatOrDog.add_transition(1, HfstBasicTransition(2, "a", "a", 0));
    basicCatOrDog.add_transition(2, HfstBasicTransition(3, "t", "t", 0));
    basicCatOrDog.add_transition(0, HfstBasicTransition(3, "dog", "dog", 0));
    basicCatOrDog.set_final_weight(3, 0);
    // <http://sourceforge.net/tracker/
    // ?func=detail&atid=1061990&aid=3468932&group_id=224521>
    HfstBasicTransducer basicAaOrBc;
    basicAaOrBc.add_state(1);
    basicAaOrBc.add_state(2);
    basicAaOrBc.add_state(3);
    basicAaOrBc.add_transition(0, HfstBasicTransition(1, "a", "a", 0));
    basicAaOrBc.add_transition(1, HfstBasicTransition(2, "a", "a", 0));
    basicAaOrBc.add_transition(0, HfstBasicTransition(3, "b", "b", 0));
    basicAaOrBc.add_transition(3, HfstBasicTransition(2, "c", "c", 0));
    basicAaOrBc.set_final_weight(2, 0);
    std::cout << std::endl << "compilation: ";
#if HAVE_SFST
    std::cout << "sfst compile(c a t)...";
    HfstTransducer* sfstCat = sfstXre.compile("c a t");
    assert(sfstCat != 0);
    assert(sfstCat->compare(HfstTransducer(basicCat, SFST_TYPE)));
    delete sfstCat;
    std::cout << "(f i:o 0:u g h t)...";
    HfstTransducer* sfstFight = sfstXre.compile("f i:o 0:u g h t");
    assert(sfstFight != 0);
    assert(sfstFight->compare(HfstTransducer(basicFight, SFST_TYPE)));
    delete sfstFight;
    std::cout << "(c a t | dog)...";
    HfstTransducer* sfstCatOrDog = sfstXre.compile("c a t | dog");
    assert(sfstCatOrDog != 0);
    assert(sfstCatOrDog->compare(HfstTransducer(basicCatOrDog, SFST_TYPE)));
    delete sfstCatOrDog;
    std::cout << "(a a | b c)...";
    HfstTransducer* sfstAaOrBc = sfstXre.compile("a a | b c");
    assert(sfstAaOrBc != 0);
    assert(sfstAaOrBc->compare(HfstTransducer(basicAaOrBc, SFST_TYPE)));
    delete sfstAaOrBc;
#endif
#if HAVE_OPENFST
    std::cout << "ofst compile(c a t)...";
    HfstTransducer* ofstCat = ofstXre.compile("c a t");
    assert(ofstCat != 0);
    assert(ofstCat->compare(HfstTransducer(basicCat, TROPICAL_OPENFST_TYPE)));
    delete ofstCat;
    std::cout << "(f i:o 0:u g h t)...";
    HfstTransducer* ofstFight = ofstXre.compile("f i:o 0:u g h t");
    assert(ofstFight != 0);
    assert(ofstFight->compare(HfstTransducer(basicFight,
                                             TROPICAL_OPENFST_TYPE)));
    delete ofstFight;
    std::cout << "(c a t | dog)...";
    HfstTransducer* ofstCatOrDog = ofstXre.compile("c a t | dog");
    assert(ofstCatOrDog != 0);
    assert(ofstCatOrDog->compare(HfstTransducer(basicCatOrDog,
                                                TROPICAL_OPENFST_TYPE)));
    delete ofstCatOrDog;
    std::cout << "(a a | b c)...";
    HfstTransducer* ofstAaOrBc = ofstXre.compile("a a | b c");
    assert(ofstAaOrBc != 0);
    assert(ofstAaOrBc->compare(HfstTransducer(basicAaOrBc, 
                                              TROPICAL_OPENFST_TYPE)));
    delete ofstAaOrBc;
#endif
#if HAVE_FOMA
    std::cout << "foma compile(c a t)...";
    HfstTransducer* fomaCat = fomaXre.compile("c a t");
    assert(fomaCat != 0);
    assert(fomaCat->compare(HfstTransducer(basicCat, FOMA_TYPE)));
    delete fomaCat;
    std::cout << "(f i:o 0:u g h t)...";
    HfstTransducer* fomaFight = fomaXre.compile("f i:o 0:u g h t");
    assert(fomaFight != 0);
    assert(fomaFight->compare(HfstTransducer(basicFight, FOMA_TYPE)));
    delete fomaFight;
    std::cout << "(c a t | dog)...";
    HfstTransducer* fomaCatOrDog = fomaXre.compile("c a t | dog");
    assert(fomaCatOrDog != 0);
    assert(fomaCatOrDog->compare(HfstTransducer(basicCatOrDog, FOMA_TYPE)));
    delete fomaCatOrDog;
    std::cout << "(a a | b c)...";
    HfstTransducer* fomaAaOrBc = fomaXre.compile("a a | b c");
    assert(fomaAaOrBc != 0);
    assert(fomaAaOrBc->compare(HfstTransducer(basicAaOrBc, FOMA_TYPE)));
    delete fomaAaOrBc;
#endif
    std::cout << std::endl << "define:";
#if HAVE_SFST
    std::cout << "sfst define(vowels, a | e | i | o | u | y)...";
    sfstXre.define("vowels", "a | e | i | o | u | y");
#endif
#if HAVE_OPENFST
    std::cout << "openfst define(vowels, a | e | i | o | u | y)...";
    ofstXre.define("vowels", "a | e | i | o | u | y");
#endif
#if HAVE_FOMA
    std::cout << "foma define(vowels, a | e | i | o | u | y)...";
    fomaXre.define("vowels", "a | e | i | o | u | y");
#endif
    std::cout << "ok." << std::endl;
    return EXIT_SUCCESS;
  }
#endif
