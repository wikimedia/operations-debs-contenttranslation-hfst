// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

//! @file PmatchCompiler.cc
//!
//! @brief Functions for building transducers from Xerox regexps

#include "PmatchCompiler.h"
#include "pmatch_utils.h"
#include "HfstTransducer.h"

#ifndef UNIT_TEST

namespace hfst { namespace pmatch {
PmatchCompiler::PmatchCompiler() :
    flatten(false),
    verbose(false),
    definitions_(),
    format_(hfst::TROPICAL_OPENFST_TYPE)
{}

PmatchCompiler::PmatchCompiler(hfst::ImplementationType impl) :
    flatten(false),
    verbose(false),
    definitions_(),
    format_(impl)
{}

void
PmatchCompiler::define(const std::string& name, const std::string& pmatch)
{
  compile(pmatch);
  if (definitions.count(name) != 0) {
      definitions_[name] = definitions[name]->evaluate();
  }
}

std::map<std::string, HfstTransducer*>
PmatchCompiler::compile(const std::string& pmatch)
{
    return hfst::pmatch::compile(pmatch, definitions_, format_,
                                 verbose, flatten, include_cosine_distances,
                                 includedir);
}

void PmatchCompiler::set_include_path(std::string path)
{
    includedir = path;
}

}}

#else // UNIT_TEST
#include <cstdlib>
#include <cassert>

using namespace hfst;
using namespace hfst::pmatch;

extern int pmatchdebug;

int
main(int, char**)
  {
    std::cout << "Unit tests for " __FILE__ ":";
//     std::cout << std::endl << "constructors: ";
//     std::cout << " (default)...";
//     PmatchCompiler defaultPmatch();
// #if HAVE_SFST
//     std::cout << " (SFST)...";
//     PmatchCompiler sfstPmatch = PmatchCompiler(SFST_TYPE);
// #endif
// #if HAVE_OPENFST
//     std::cout << " (OpenFst)...";
//     PmatchCompiler ofstPmatch = PmatchCompiler(TROPICAL_OPENFST_TYPE);
// #endif
// #if HAVE_FOMA
//     std::cout << " (Foma)...";
//     PmatchCompiler fomaPmatch = PmatchCompiler(FOMA_TYPE);
// #endif
//     HfstBasicTransducer basicCat;
//     basicCat.add_state(1);
//     basicCat.add_state(2);
//     basicCat.add_state(3);
//     basicCat.add_transition(0, HfstBasicTransition(1, "c", "c", 0));
//     basicCat.add_transition(1, HfstBasicTransition(2, "a", "a", 0));
//     basicCat.add_transition(2, HfstBasicTransition(3, "t", "t", 0));
//     basicCat.set_final_weight(3, 0);
//     HfstBasicTransducer basicFight;
//     basicFight.add_state(1);
//     basicFight.add_state(2);
//     basicFight.add_state(3);
//     basicFight.add_state(4);
//     basicFight.add_state(5);
//     basicFight.add_state(6);
//     basicFight.add_transition(0, HfstBasicTransition(1, "f", "f", 0));
//     basicFight.add_transition(1, HfstBasicTransition(2, "i", "o", 0));
//     basicFight.add_transition(2, HfstBasicTransition(3, hfst::internal_epsilon,
//                                                      "u", 0));
//     basicFight.add_transition(3, HfstBasicTransition(4, "g", "g", 0));
//     basicFight.add_transition(4, HfstBasicTransition(5, "h", "h", 0));
//     basicFight.add_transition(5, HfstBasicTransition(6, "t", "t", 0));
//     basicFight.set_final_weight(6, 0);
//     HfstBasicTransducer basicCatOrDog;
//     basicCatOrDog.add_state(1);
//     basicCatOrDog.add_state(2);
//     basicCatOrDog.add_state(3);
//     basicCatOrDog.add_transition(0, HfstBasicTransition(1, "c", "c", 0));
//     basicCatOrDog.add_transition(1, HfstBasicTransition(2, "a", "a", 0));
//     basicCatOrDog.add_transition(2, HfstBasicTransition(3, "t", "t", 0));
//     basicCatOrDog.add_transition(0, HfstBasicTransition(3, "dog", "dog", 0));
//     basicCatOrDog.set_final_weight(3, 0);
//     // <http://sourceforge.net/tracker/
//     // ?func=detail&atid=1061990&aid=3468932&group_id=224521>
//     HfstBasicTransducer basicAaOrBc;
//     basicAaOrBc.add_state(1);
//     basicAaOrBc.add_state(2);
//     basicAaOrBc.add_state(3);
//     basicAaOrBc.add_transition(0, HfstBasicTransition(1, "a", "a", 0));
//     basicAaOrBc.add_transition(1, HfstBasicTransition(2, "a", "a", 0));
//     basicAaOrBc.add_transition(0, HfstBasicTransition(3, "b", "b", 0));
//     basicAaOrBc.add_transition(3, HfstBasicTransition(2, "c", "c", 0));
//     basicAaOrBc.set_final_weight(2, 0);
//     std::cout << std::endl << "compilation: ";
// #if HAVE_SFST
//     std::cout << "sfst compile(c a t)...";
//     HfstTransducer* sfstCat = sfstPmatch.compile("c a t");
//     assert(sfstCat != 0);
//     assert(sfstCat->compare(HfstTransducer(basicCat, SFST_TYPE)));
//     delete sfstCat;
//     std::cout << "(f i:o 0:u g h t)...";
//     HfstTransducer* sfstFight = sfstPmatch.compile("f i:o 0:u g h t");
//     assert(sfstFight != 0);
//     assert(sfstFight->compare(HfstTransducer(basicFight, SFST_TYPE)));
//     delete sfstFight;
//     std::cout << "(c a t | dog)...";
//     HfstTransducer* sfstCatOrDog = sfstPmatch.compile("c a t | dog");
//     assert(sfstCatOrDog != 0);
//     assert(sfstCatOrDog->compare(HfstTransducer(basicCatOrDog, SFST_TYPE)));
//     delete sfstCatOrDog;
//     std::cout << "(a a | b c)...";
//     HfstTransducer* sfstAaOrBc = sfstPmatch.compile("a a | b c");
//     assert(sfstAaOrBc != 0);
//     assert(sfstAaOrBc->compare(HfstTransducer(basicAaOrBc, SFST_TYPE)));
//     delete sfstAaOrBc;
// #endif
// #if HAVE_OPENFST
//     std::cout << "ofst compile(c a t)...";
//     HfstTransducer* ofstCat = ofstPmatch.compile("c a t");
//     assert(ofstCat != 0);
//     assert(ofstCat->compare(HfstTransducer(basicCat, TROPICAL_OPENFST_TYPE)));
//     delete ofstCat;
//     std::cout << "(f i:o 0:u g h t)...";
//     HfstTransducer* ofstFight = ofstPmatch.compile("f i:o 0:u g h t");
//     assert(ofstFight != 0);
//     assert(ofstFight->compare(HfstTransducer(basicFight,
//                                              TROPICAL_OPENFST_TYPE)));
//     delete ofstFight;
//     std::cout << "(c a t | dog)...";
//     HfstTransducer* ofstCatOrDog = ofstPmatch.compile("c a t | dog");
//     assert(ofstCatOrDog != 0);
//     assert(ofstCatOrDog->compare(HfstTransducer(basicCatOrDog,
//                                                 TROPICAL_OPENFST_TYPE)));
//     delete ofstCatOrDog;
//     std::cout << "(a a | b c)...";
//     HfstTransducer* ofstAaOrBc = ofstPmatch.compile("a a | b c");
//     assert(ofstAaOrBc != 0);
//     assert(ofstAaOrBc->compare(HfstTransducer(basicAaOrBc,
//                                               TROPICAL_OPENFST_TYPE)));
//     delete ofstAaOrBc;
// #endif
// #if HAVE_FOMA
//     std::cout << "foma compile(c a t)...";
//     HfstTransducer* fomaCat = fomaPmatch.compile("c a t");
//     assert(fomaCat != 0);
//     assert(fomaCat->compare(HfstTransducer(basicCat, FOMA_TYPE)));
//     delete fomaCat;
//     std::cout << "(f i:o 0:u g h t)...";
//     HfstTransducer* fomaFight = fomaPmatch.compile("f i:o 0:u g h t");
//     assert(fomaFight != 0);
//     assert(fomaFight->compare(HfstTransducer(basicFight, FOMA_TYPE)));
//     delete fomaFight;
//     std::cout << "(c a t | dog)...";
//     HfstTransducer* fomaCatOrDog = fomaPmatch.compile("c a t | dog");
//     assert(fomaCatOrDog != 0);
//     assert(fomaCatOrDog->compare(HfstTransducer(basicCatOrDog, FOMA_TYPE)));
//     delete fomaCatOrDog;
//     std::cout << "(a a | b c)...";
//     HfstTransducer* fomaAaOrBc = fomaPmatch.compile("a a | b c");
//     assert(fomaAaOrBc != 0);
//     assert(fomaAaOrBc->compare(HfstTransducer(basicAaOrBc, FOMA_TYPE)));
//     delete fomaAaOrBc;
// #endif
//     std::cout << std::endl << "define:";
// #if HAVE_SFST
//     std::cout << "sfst define(vowels, a | e | i | o | u | y)...";
//     sfstPmatch.define("vowels", "a | e | i | o | u | y");
// #endif
// #if HAVE_OPENFST
//     std::cout << "openfst define(vowels, a | e | i | o | u | y)...";
//     ofstPmatch.define("vowels", "a | e | i | o | u | y");
// #endif
// #if HAVE_FOMA
//     std::cout << "foma define(vowels, a | e | i | o | u | y)...";
//     fomaPmatch.define("vowels", "a | e | i | o | u | y");
// #endif
    std::cout << "ok." << std::endl;
    return EXIT_SUCCESS;
  }
#endif
