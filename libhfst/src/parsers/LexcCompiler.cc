//! @file LexcCompiler.cc
//!
//! @brief Implementation of lexc compilation.
//! 
//! @author Tommi A. Pirinen
//!

//       This program is free software: you can redistribute it and/or modify
//       it under the terms of the GNU General Public License as published by
//       the Free Software Foundation, version 3 of the License.
//
//       This program is distributed in the hope that it will be useful,
//       but WITHOUT ANY WARRANTY; without even the implied warranty of
//       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//       GNU General Public License for more details.
//
//       You should have received a copy of the GNU General Public License
//       along with this program.  If not, see <http://www.gnu.org/licenses/>.

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <ctime>

using std::string;
using std::map;
using std::set;
using std::pair;
using std::vector;
using std::set_difference;

#include "LexcCompiler.h"
#include "HfstTransducer.h"
#include "XreCompiler.h"
#include "lexc-utils.h"
#include "lexc-parser.hh"
#include "xre_utils.h"
#include "../../../tools/src/HfstStrings2FstTokenizer.h"

using hfst::HfstTransducer;
using hfst::implementations::HfstTransitionGraph;
using hfst::implementations::HfstBasicTransducer;
using hfst::implementations::HfstState;
using hfst::implementations::HfstBasicTransition;
using hfst::ImplementationType;
using hfst::xre::XreCompiler;


//using same alg as strings to fst
static char *epsilonname=NULL; // FIX: use this
static bool has_spaces=false;
static bool disjunct_strings=false;
static bool pairstrings=false;
static char *multichar_symbol_filename=NULL;
static StringVector multichar_symbols;


// stupid flex and yacc
extern FILE* hlexcin;
extern int hlexcparse();
extern int hlexcnerrs;
extern void hlexclex_destroy();

#ifndef DEBUG_MAIN

namespace hfst { namespace lexc {

LexcCompiler* lexc_ = 0;

LexcCompiler::LexcCompiler() :
    quiet_(false),
    verbose_(false),
    treat_warnings_as_errors_(false),
    format_(TROPICAL_OPENFST_TYPE),
    xre_(TROPICAL_OPENFST_TYPE),
    initialLexiconName_("Root"),
    totalEntries_(0),
    currentEntries_(0),
    parseErrors_(false),
    with_flags_(false),
    minimize_flags_(false),
    rename_flags_(false)
{
    xre_.set_expand_definitions(true);
}

LexcCompiler::LexcCompiler(ImplementationType impl) :
    quiet_(false),
    verbose_(false),
    treat_warnings_as_errors_(false),
    format_(impl),
    xre_(impl),
    initialLexiconName_("Root"),
    totalEntries_(0),
    currentEntries_(0),
    parseErrors_(false),
    with_flags_(false),
    minimize_flags_(false),
    rename_flags_(false)
{
    tokenizer_.add_multichar_symbol("@_EPSILON_SYMBOL_@");
    tokenizer_.add_multichar_symbol("@0@");
    tokenizer_.add_multichar_symbol("@ZERO@");
    tokenizer_.add_multichar_symbol("@@ANOTHER_EPSILON@@");
    string hash("#");
    lexiconNames_.insert(hash);
    tokenizer_.add_multichar_symbol(joinerEncode(hash));
    xre_.set_expand_definitions(true);
}

LexcCompiler::LexcCompiler(ImplementationType impl, bool withFlags) :
    quiet_(false),
    verbose_(false),
    treat_warnings_as_errors_(false),
    format_(impl),
    xre_(impl),
    initialLexiconName_("Root"),
    totalEntries_(0),
    currentEntries_(0),
    parseErrors_(false),
    with_flags_(withFlags),
    minimize_flags_(false),
    rename_flags_(false)
{
    tokenizer_.add_multichar_symbol("@_EPSILON_SYMBOL_@");
    tokenizer_.add_multichar_symbol("@0@");
    tokenizer_.add_multichar_symbol("@ZERO@");
    tokenizer_.add_multichar_symbol("@@ANOTHER_EPSILON@@");
    string hash("#");
    lexiconNames_.insert(hash);
    tokenizer_.add_multichar_symbol(joinerEncode(hash));
    xre_.set_expand_definitions(true);
}


LexcCompiler& LexcCompiler::parse(FILE* infile)
{
    lexc_ = this;
    if (infile == stdin)
      {
        hfst::lexc::set_infile_name("<stdin>");
      }
    else
      {
        hfst::lexc::set_infile_name("<unnamed>");
      }
    hlexclex_destroy();
    hlexcin = infile;
    hlexcparse();
    if (hlexcnerrs > 0)
      {
        parseErrors_ = true;
      }
    return *this;
}

LexcCompiler& LexcCompiler::parse(const char* filename)
{
    lexc_ = this;
    hlexclex_destroy();
    hfst::lexc::set_infile_name(filename);
    hlexcin = fopen(filename, "r");
    if (hlexcin == NULL)
      {
        fprintf(stderr, "could not open %s for reading\n", filename);
        parseErrors_ = true;
        return *this;
      }
    hlexcparse();
    if (hlexcnerrs > 0)
      {
        parseErrors_ = true;
      }
    return *this;
}

LexcCompiler&
LexcCompiler::setVerbosity(bool verbose)
{
    quiet_ = !verbose;
    verbose_ = verbose;
    return *this;
}

LexcCompiler&
LexcCompiler::setTreatWarningsAsErrors(bool value)
{
    treat_warnings_as_errors_ = value;
    return *this;
}

LexcCompiler&
LexcCompiler::setWithFlags(bool value)
{
    with_flags_ = value;
    return *this;
}

LexcCompiler&
LexcCompiler::setMinimizeFlags(bool value)
{
    minimize_flags_ = value;
    return *this;
}

LexcCompiler&
LexcCompiler::setRenameFlags(bool value)
{
    rename_flags_ = value;
    return *this;
}


LexcCompiler&
LexcCompiler::addNoFlag(const string& lexname)
{
    noFlags_.insert(lexname);
    return *this;
}
LexcCompiler&
LexcCompiler::addAlphabet(const string& alpha)
{
    //printf("alpha: %s \n", alpha.c_str());
    tokenizer_.add_multichar_symbol(alpha);
    return *this;
}

// Construct vector nameJoiner data contJoiner and add to trie
LexcCompiler&
LexcCompiler::addStringEntry(const string& data,
        const string& continuation, double weight)
{
    //printf("data: %s \n", data.c_str());
    string str = replace_zero(data);

    currentEntries_++;
    totalEntries_++;
    continuations_.insert(continuation);
    string encodedCont = string(continuation);
    if (with_flags_)
    {
        if (noFlags_.find(continuation) == noFlags_.end())
          {
            encodedCont = flagJoinerEncode(encodedCont, false);
          }
        else
          {
            encodedCont = joinerEncode(encodedCont);
          }
    }
    else
    {
        encodedCont = joinerEncode(encodedCont);
    }
    tokenizer_.add_multichar_symbol(encodedCont);

    // build string pair vector map
    string joinerEnc = currentLexiconName_;
    if (with_flags_)
    {
        if (noFlags_.find(currentLexiconName_) == noFlags_.end())
          {
            flagJoinerEncode(joinerEnc, true);
          }
        else
          {
            joinerEncode(joinerEnc);
          }
    }
    else
    {
        joinerEncode(joinerEnc);
    }
    tokenizer_.add_multichar_symbol(joinerEnc);
    StringPairVector newVector(tokenizer_.tokenize(joinerEnc + str + encodedCont));
    stringsTrie_.disjunct(newVector, weight);

    return *this;
}

LexcCompiler&
LexcCompiler::addStringPairEntry(const string& upper, const string& lower,
        const string& continuation, double weight)
{
    string upper_string = replace_zero(upper);
    string lower_string = replace_zero(lower);

    //printf("upper: %s lower: %s: continuation: %s \n", upper.c_str(), lower.c_str(), continuation.c_str());
           //identityWoJoin.write_in_att_format(stdout, 1);
    currentEntries_++;
    totalEntries_++;
    continuations_.insert(continuation);
    string encodedCont = string(continuation);
    if (with_flags_) {
        if (noFlags_.find(continuation) == noFlags_.end())
          {
            encodedCont = flagJoinerEncode(encodedCont, false);
          }
        else
          {
            encodedCont = joinerEncode(encodedCont);
          }
    }
    else
    {
        encodedCont = joinerEncode(encodedCont);
    }
    tokenizer_.add_multichar_symbol(encodedCont);

    // build string pair vector map

    string joinerEnc = currentLexiconName_;
    if (with_flags_)
    {
        if (noFlags_.find(currentLexiconName_) == noFlags_.end())
          {
            flagJoinerEncode(joinerEnc, true);
          }
        else
          {
            joinerEncode(joinerEnc);
          }
    }
    else
    {
        joinerEncode(joinerEnc);
    }
    tokenizer_.add_multichar_symbol(joinerEnc);

    StringPairVector upperV;
    upperV = tokenizer_.tokenize(upper_string);

    StringPairVector lowerV;
    lowerV = tokenizer_.tokenize(lower_string);

    int upperSize = upperV.size();
    int lowerSize = lowerV.size();

    //cout << "u: "  << upperSize << "\n";
    //cout << "L: "  << lowerSize << "\n";



    StringVector upV;
    StringVector loV;

    StringPairVector newVector;

    if ( upperSize > lowerSize)
    {
        std::string epsilons = "";
        for(int i=1; i <= upperSize-lowerSize ; i++)
        {
            //cout << "another epsilon \n";
            epsilons = epsilons + string("@@ANOTHER_EPSILON@@");

        }
        newVector = tokenizer_.tokenize(joinerEnc + upper_string + encodedCont,
                            joinerEnc + lower_string + epsilons + encodedCont);

    }
    else if (upperSize < lowerSize)
    {
        std::string epsilons = "";
        for(int i=1; i <= lowerSize-upperSize ; i++)
        {
            //cout << "another epsilon \n";
            epsilons = epsilons + string("@@ANOTHER_EPSILON@@");

        }
        newVector = tokenizer_.tokenize(joinerEnc + upper_string + epsilons + encodedCont,
                            joinerEnc + lower_string + encodedCont);
    }
    else
    {
        newVector = tokenizer_.tokenize(joinerEnc + upper_string + encodedCont,
                    joinerEnc + lower_string + encodedCont);
    }
    stringsTrie_.disjunct(newVector, weight);

    return *this;
}

// Construct transducer nameJoiner XRE contJoiner and add to trie
LexcCompiler&
LexcCompiler::addXreEntry(const string& regexp, const string& continuation,
        double weight)
{
    currentEntries_++;
    totalEntries_++;
    continuations_.insert(continuation);
    string encodedCont = string(continuation);
    if (with_flags_)
    {
        if (noFlags_.find(continuation) == noFlags_.end())
          {
            encodedCont = flagJoinerEncode(encodedCont, false);
          }
        else
          {
            encodedCont = joinerEncode(encodedCont);
          }
    }
    else
    {
        encodedCont = joinerEncode(encodedCont);
    }
    tokenizer_.add_multichar_symbol(encodedCont);
    char* xre_encoded = hfst::xre::add_percents(encodedCont.c_str());


   // cout << "XRE COMPILE: " << "\n";



    //HfstTransducer* newPaths = xre_.compile(regexp + " "  + string(xre_encoded));
    HfstTransducer* newPaths = xre_.compile(regexp);

//    if (weight != 0)
//      {
//        newPaths->set_final_weights(weight);
//      }
    newPaths->minimize();


    //printf("newPaths: \n");
    //newPaths->write_in_att_format(stdout, 1);

    //std::map<std::string,hfst::HfstTransducer*> regexps_;

    // encode key
    // keep regexps with different continuations separate
    string regex_key =  currentLexiconName_ + "_" + continuation;

    regExpresionEncode(regex_key);
    tokenizer_.add_multichar_symbol(regex_key);
   // cout << "lexicon " << regex_key << "\n";

    // FIXME: add all implicit chars to multichar symbols
    if (regexps_.find(regex_key) == regexps_.end())
      {
        regexps_.insert(pair<string,HfstTransducer*>(regex_key,
                                                   new HfstTransducer(format_)));
      }
    regexps_[regex_key]->disjunct(*newPaths).minimize();
    if (!quiet_)
      {
        if ((currentEntries_ % 10000) == 0)
          {
            fprintf(stderr, SIZE_T_SPECIFIER "...", currentEntries_);
          }
      }


    // add key to trie

    string joinerEnc = currentLexiconName_;
      if (with_flags_)
      {
          if (noFlags_.find(currentLexiconName_) == noFlags_.end())
            {
              flagJoinerEncode(joinerEnc, true);
            }
          else
            {
              joinerEncode(joinerEnc);
            }
      }
      else
      {
          joinerEncode(joinerEnc);
      }
      tokenizer_.add_multichar_symbol(joinerEnc);
      StringPairVector newVector(tokenizer_.tokenize(joinerEnc + regex_key + encodedCont));
      stringsTrie_.disjunct(newVector, weight);



    return *this;
}

LexcCompiler&
LexcCompiler::addXreDefinition(const string& definition_name, const string& xre)
{
    // FIXME: collect implicit characters
    xre_.define(definition_name, xre);
    if (!quiet_)
      {
        fprintf(stderr,
            "Defined '%s': ? Kb., ? states, ? arcs, ? paths.\n",
            definition_name.c_str());
      }
    return *this;
}

LexcCompiler&
LexcCompiler::setCurrentLexiconName(const string& lexiconName)
{
    static bool firstLexicon = true;
    currentLexiconName_ = lexiconName;
    lexiconNames_.insert(lexiconName);
    if (noFlags_.find(lexiconName) == noFlags_.end())
    {
        string encodedName(lexiconName);
        flagJoinerEncode(encodedName, false);
        tokenizer_.add_multichar_symbol(encodedName);
        flagJoinerEncode(encodedName, true);
        tokenizer_.add_multichar_symbol(encodedName);
    }
    else
    {
        string encodedName(lexiconName);
        joinerEncode(encodedName);
        tokenizer_.add_multichar_symbol(encodedName);
    }


    if ((firstLexicon) && (lexiconName == "Root"))
    {
        setInitialLexiconName(lexiconName);
    }
    else if ((firstLexicon) && (lexiconName != "Root"))
    {
        if (!quiet_) fprintf(stderr, "first lexicon is not named Root\n");
        setInitialLexiconName(lexiconName);
    }
    else if ((!firstLexicon) && (lexiconName == "Root"))
    {
        if (!quiet_) fprintf(stderr, "Root is not first the first lexicon\n");
        setInitialLexiconName(lexiconName);
    }
    if (!firstLexicon && !quiet_)
    {
        fprintf(stderr, SIZE_T_SPECIFIER " ", currentEntries_);
    }
    if (!quiet_) fprintf(stderr, "%s...", lexiconName.c_str());
    firstLexicon = false;

    currentEntries_ = 0;
    return *this;
}

LexcCompiler&
LexcCompiler::setInitialLexiconName(const string& lexiconName)
{
    initialLexiconName_ = lexiconName;
    lexiconNames_.insert(lexiconName);
    // for connectedness calculation:
    continuations_.insert(lexiconName);

//    string joiner_initial_name;
 //   tokenizer_.add_multichar_symbol(joinerEncode(joiner_initial_name));
    return *this;
}

HfstTransducer*
LexcCompiler::compileLexical()
  {

    if (parseErrors_)
      {
        return 0;
      }

    bool warnings_generated = false;
    printConnectedness(warnings_generated);
    if (warnings_generated && treat_warnings_as_errors_)
      {
        if (!quiet_) fprintf(stderr, "*** ERROR: could not parse lexc file: treating warnings as errors [--Werror] ***\n");
        return 0;
      }
/*
    if( with_flags_)
        fprintf(stderr, "With Flags \n \n");
    else
        fprintf(stderr, "no Flags \n \n");
*/

    HfstTransducer lexicons(stringsTrie_, format_);


    lexicons.minimize();


    // DEBUG
    //fprintf(stderr, "lexicons: \n");
    //lexicons.write_in_att_format(stderr, 1);


    // repeat star to overgenerate
    lexicons.repeat_star().minimize();



    //printf("lexicons: \n");
    //lexicons.write_in_att_format(stdout, 1);




    HfstSymbolSubstitutions smallSubstitutions;
    smallSubstitutions.insert(StringPair("@0@", "@_EPSILON_SYMBOL_@"));
    smallSubstitutions.insert(StringPair("@@ANOTHER_EPSILON@@", "@_EPSILON_SYMBOL_@"));
    smallSubstitutions.insert(StringPair("@ZERO@", "0"));

    /*
    lexicons.substitute("@0@", "@_EPSILON_SYMBOL_@");
    lexicons.substitute("@@ANOTHER_EPSILON@@", "@_EPSILON_SYMBOL_@");
    lexicons.substitute("@ZERO@", "0");
    */
    lexicons.substitute(smallSubstitutions);
    lexicons.prune_alphabet();


    //printf("lexicons: \n");
    //lexicons.write_in_att_format(stdout, 1);


    HfstBasicTransducer joinersTrie_;

    HfstSymbolSubstitutions allJoinersToEpsilon;

    if ( !with_flags_ )
    {
        string joinerinitialLexiconName_ = initialLexiconName_;
        //std::cout << "initialLexiconName_ " << initialLexiconName_ << "\n";
        HfstTransducer start(joinerEncode(joinerinitialLexiconName_), tokenizer_, format_);
        string endString = "#";
        joinerEncode(endString);
        HfstTransducer end(endString, tokenizer_, format_);
        lexicons = start.concatenate(lexicons).concatenate(end).minimize();

        //printf("lexicons: \n");
        //lexicons.write_in_att_format(stdout, 1);

        /*
        // if flags

        // for every lex_joiner in noFlags, find only strings where it occurs twice in a row
        // and then replace those joiners with epsilons
        for (set<string>::const_iterator s = noFlags_.begin();
             s != noFlags_.end();
             ++s)
        {
            ...
            string joinerEnc = *s;
            joinerEncode(joinerEnc);
            HfstTransducer joiner(joinerEnc, joinerEnc, format_);
         }
        */

        for (set<string>::const_iterator s = lexiconNames_.begin();
             s != lexiconNames_.end();
             ++s)
        {
            if (verbose_)
            {
                fprintf(stderr, "Morphotaxing... %s ", s->c_str());
            }
            string joinerEnc = *s;
            joinerEncode(joinerEnc);


            // joiners trie version (later compose)
           // tokenizer_.add_multichar_symbol(joinerEnc);
            StringPairVector newVector(tokenizer_.tokenize(joinerEnc + joinerEnc));
            joinersTrie_.disjunct(newVector, 0);

            //printf ("\ninsert...\n");
            allJoinersToEpsilon.insert(StringPair(joinerEnc, "@_EPSILON_SYMBOL_@"));
            //printf ("\ndone.\n");
         }

        string rootJoiner = initialLexiconName_;
        string hashJoiner = "#";
        joinerEncode(rootJoiner);
        joinerEncode(hashJoiner);

        allJoinersToEpsilon.insert(StringPair(rootJoiner, "@_EPSILON_SYMBOL_@"));
        allJoinersToEpsilon.insert(StringPair(hashJoiner, "@_EPSILON_SYMBOL_@"));

    }
    else
    {

        string rootP = initialLexiconName_;
        string rootR = initialLexiconName_;

          HfstTransducer startP(flagJoinerEncode(rootP, false), tokenizer_, format_);
          HfstTransducer startR(flagJoinerEncode(rootR, true), tokenizer_, format_);

          string endStringP = "#";
          string endStringR = "#";
          flagJoinerEncode(endStringP, false);
          flagJoinerEncode(endStringR, true);

          tokenizer_.add_multichar_symbol(endStringP);
          tokenizer_.add_multichar_symbol(endStringR);

          HfstTransducer endP(endStringP, tokenizer_, format_);
          HfstTransducer endR(endStringR, tokenizer_, format_);

          lexicons = startP.
                      concatenate(lexicons).
                      concatenate(endR).
                      minimize();

          //printf("lexicons: \n");
          //lexicons.write_in_att_format(stdout, 1);


          // for every lex_joiner in noFlags, find only strings where it occurs twice in a row
          // and then replace those joiners with epsilons
          /*
          for (set<string>::const_iterator s = noFlags_.begin();
               s != noFlags_.end();
               ++s)
          {
              string joinerEnc = *s;
              joinerEncode(joinerEnc);
              //HfstTransducer joiner(joinerEnc, joinerEnc, format_);
              allJoinersToEpsilon.insert(StringPair(joinerEnc, "@_EPSILON_SYMBOL_@"));

              // joiners trie version (later compose)
                 // tokenizer_.add_multichar_symbol(joinerEnc);
                  StringPairVector newVector(tokenizer_.tokenize(joinerEnc + joinerEnc));
                  joinersTrie_.disjunct(newVector, 0);


           }
           */
          ///

          for (set<string>::const_iterator s = lexiconNames_.begin();
               s != lexiconNames_.end();
               ++s)
          {
            if (verbose_)
            {
            fprintf(stderr, "Morphotaxing... %s ", s->c_str());
            }
            string flagPstring = *s;
            string flagRstring = *s;

            //joinerEncode(joinerEnc);
            //HfstTransducer joiner(joinerEnc, joinerEnc, format_);
            flagJoinerEncode(flagPstring, false);
            flagJoinerEncode(flagRstring, true);

            // joiners trie version (later compose)
           // tokenizer_.add_multichar_symbol(joinerEnc);
            StringPairVector newVector(tokenizer_.tokenize(flagPstring + flagRstring));
            joinersTrie_.disjunct(newVector, 0);
        }
    }


        /// get right side of every pair
        HfstBasicTransducer fsm(lexicons);
        StringSet rightSymbols;
        // Go through all states
        for (HfstBasicTransducer::const_iterator it = fsm.begin();
        it != fsm.end(); it++ )
        {
            // Go through all transitions
            for (HfstBasicTransducer::HfstTransitions::const_iterator tr_it
             = it->begin(); tr_it != it->end(); tr_it++)
            {
                String alph2 = tr_it->get_output_symbol();

                String prefix1("@@ANOTHER_EPSILON@@");
                String prefix2("$_LEXC_JOINER.");
                String prefix3("@_");
                String prefix4("$P.LEXNAME.");
                String prefix5("$R.LEXNAME.");

                if( alph2.substr(0, prefix1.size()) != prefix1 &&
                        alph2.substr(0, prefix2.size()) != prefix2 &&
                        alph2.substr(0, prefix4.size()) != prefix4 &&
                        alph2.substr(0, prefix5.size()) != prefix5 &&
                        alph2.substr(0, prefix3.size()) != prefix3 )
                {
                    rightSymbols.insert(alph2);

                }
            }
        }

        for ( StringSet::const_iterator it = rightSymbols.begin(); it != rightSymbols.end(); ++it)
        {
            String alph = *it;
            tokenizer_.add_multichar_symbol(alph);
            StringPairVector newVector(tokenizer_.tokenize(alph));
            joinersTrie_.disjunct(newVector, 0);
        }

        HfstTransducer joinersAll(joinersTrie_, format_);




        joinersAll.repeat_star();
        joinersAll.minimize();

/*
     printf("lexicons before compose: \n");
     lexicons.write_in_att_format(stdout, 1);

      printf("joinersAll: \n");
      joinersAll.write_in_att_format(stdout, 1);
      printf("\n");
*/

        lexicons.compose(joinersAll).minimize();


        HfstSymbolSubstitutions allSubstitutions;
        if(with_flags_)
        {
            if (verbose_)
            {
                fprintf(stderr, "\nChanging flags...\n");
            }
            HfstSymbolSubstitutions fakeFlagsToRealFlags;
            // Change fake flags to real flags
            lexicons.prune_alphabet();
            //printf("alphabet lexicons: \n");
            StringSet transducerAlphabet = lexicons.get_alphabet();
            for (StringSet::const_iterator s = transducerAlphabet.begin();
                           s != transducerAlphabet.end();
                           ++s)
            {
                //printf("%s \n", s->c_str());
                String alph = *s;

                if ( alph[0] == '$' && *alph.rbegin() == '$' && alph.size() > 2)
                {
                    replace(alph.begin(), alph.end(), '$', '@');
                    //std::cout << alph << '\n';
                    fakeFlagsToRealFlags.insert(StringPair(*s, alph));
                    //lexicons.substitute(*s, alph).minimize();
                }
            }
            allSubstitutions.insert(fakeFlagsToRealFlags.begin(), fakeFlagsToRealFlags.end());

            //lexicons.substitute(fakeFlagsToRealFlags).minimize();
            //lexicons.prune_alphabet();
        }
        else
        {
            allSubstitutions.insert(allJoinersToEpsilon.begin(), allJoinersToEpsilon.end());
            //lexicons.substitute(allJoinersToEpsilon).minimize();
            //lexicons.prune_alphabet();
        }

        lexicons.substitute(allSubstitutions).minimize();
        lexicons.prune_alphabet();



        //replace reg exp key with transducers
        if (verbose_)
        {
            fprintf(stderr, "\nInserting regular expressions...\n");
        }


        // substitute all reg expression into special, unharmonizible symbols
        HfstSymbolSubstitutions fakeRegexprToReal;
        for (std::map<std::string,hfst::HfstTransducer*>::const_iterator it = regexps_.begin();
                               it != regexps_.end();
                               ++it)
        {
            String alph = it->first;
            if ( alph[0] == '$' )
            {
                // TODO: do this only for strings that look like $.....$
                replace(alph.begin(), alph.end(), '$', '@');

                //std::cout << alph << '\n';
                fakeRegexprToReal.insert(StringPair(it->first, alph));

            //    lexicons.substitute(it->first, alph).minimize();
            }
            //lexicons.substitute(StringPair(it->first, it->first), *it->second).minimize();
            //lexicons.substitute(StringPair(alph, alph), *it->second, true).minimize();
        }
        lexicons.substitute(fakeRegexprToReal).minimize();
        lexicons.prune_alphabet();

/*
        printf("lexicons before substitute: \n");
        lexicons.write_in_att_format(stdout, 1);
        printf("--\n");
*/
        //SubstMap regMarkToTr;
        std::map<String, HfstBasicTransducer> regMarkToTr;


        for (std::map<std::string,hfst::HfstTransducer*>::const_iterator it = regexps_.begin();
                                       it != regexps_.end();
                                       ++it)
        {

            String alph = it->first;
            if ( alph[0] == '$' )
            {
                // TODO: do this only for strings that look like $.....$
                replace(alph.begin(), alph.end(), '$', '@');
            }
            HfstBasicTransducer btr(*(it->second));
            regMarkToTr[alph] = btr;
            //lexicons.substitute(StringPair(alph, alph), *it->second, true).minimize();
        }
      

        HfstBasicTransducer lexicons_basic(lexicons);
        lexicons_basic.substitute(regMarkToTr, true);



        lexicons_basic.prune_alphabet();

/*
        printf("lexicons after substitute: \n");
        lexicons_basic.write_in_att_format(stdout, 1);
        printf("--\n");
*/



    HfstTransducer* rv = new HfstTransducer(lexicons_basic, format_);

    // Preserve only first flag of consecutive P and R lexname flag series, 
    // e.g. change P.LEXNAME.1 R.LEXNAME.1 P.LEXNAME.2 R.LEXNAME.2 into P.LEXNAME.1 
        
    if (with_flags_ && minimize_flags_)
          {

            // To substitute "@[P|R].LEXNAME...@" with "$[P|R].LEXNAME...$" and vice versa. 
            std::map<String, String> flag_substitutions;             // @ -> $
            std::map<String, String> reverse_flag_substitutions;     // $ -> @

            // TEST: rename all $P$ and $R$ flags so that they have the same name
            std::map<String, String> dollar_to_foo_substitutions;

            StringSet transducerAlphabet = rv->get_alphabet();
            for (StringSet::const_iterator s = transducerAlphabet.begin();
                 s != transducerAlphabet.end();
                 ++s)
            {
              String alph = *s;
              String alph10 = alph.substr(0,10);
              if ( alph10 == "@P.LEXNAME" || alph10 == "@R.LEXNAME" )  
                {
                  replace(alph.begin(), alph.end(), '@', '$');
                  //fprintf(stderr, "flag found:\t\t%s\t->\t%s\n", s->c_str(), alph.c_str());
                  flag_substitutions[*s] = alph;
                  reverse_flag_substitutions[alph] = *s;
                  // insert mapping: $[P|R].LEXNAME.SOMETHING$  <->  $[P|R]$.FOO.BAR$
                  dollar_to_foo_substitutions[alph] = alph.substr(0, 2).append(".FOO.BAR$");
                  //fprintf(stderr, "dollar_to_foo_substitutions[%s] = %s\n", alph.c_str(), (dollar_to_foo_substitutions[alph]).c_str());
                }
              else
                {
                  //fprintf(stderr, "other found:\t\t%s\n", alph.c_str());
                }
            }

            // Substitute "@[P|R].LEXNAME...@" with "$[P|R].LEXNAME...$"
            rv->substitute(flag_substitutions);

            //fprintf(stderr, "rv:\n");
            //rv->write_in_att_format(stderr, 1);
            //fprintf(stderr, "--\n");

            
            // Construct a rule for consecutive flag removal: 
            // [FLAG1 | FLAG2 ... FLAGN] -> 0 || [FLAG1 | FLAG2 ... FLAGN] _
            // and also an inverted rule
            std::string flag_remover_regexp("[ ");
            bool first_flag = true;
            for (std::map<String, String>::const_iterator it 
                   = flag_substitutions.begin(); it != flag_substitutions.end(); it++)
              {
                //fprintf(stderr, "adding flag to rule:\t%s\n", it->second.c_str());
                if (!first_flag)
                      {
                        flag_remover_regexp.append("| ");
                      }
                flag_remover_regexp.append("\"").append(it->second).append("\" ");
                first_flag = false;
              }
            flag_remover_regexp.append("]");
            std::string context_regexp(flag_remover_regexp);
            flag_remover_regexp.append(" -> 0 || ").append(context_regexp).append(" _ ");
            
            // DEBUG
            //fprintf(stderr, "flag_remover_regexp: %s\n", flag_remover_regexp.c_str());
            
            hfst::xre::XreCompiler xre_comp(format_);
            HfstTransducer * flag_filter = xre_comp.compile(flag_remover_regexp);
            flag_filter->minimize();
            HfstTransducer * inverted_flag_filter = new HfstTransducer(*flag_filter);
            inverted_flag_filter->invert().minimize();
            
            //fprintf(stderr, "flag_filter:\n");
            //flag_filter->write_in_att_format(stderr, 1);
            //fprintf(stderr, "--\n");            

            //fprintf(stderr, "inverted flag_filter:\n");
            //inverted_flag_filter->write_in_att_format(stderr, 1);
            //fprintf(stderr, "--\n");            
            

            // [ [FLAG1 | FLAG2 ... FLAGN] -> 0 || [FLAG1 | FLAG2 ... FLAGN] _ ].inv
            //                        .o.
            //                       RESULT
            //                        .o. 
            // [FLAG1 | FLAG2 ... FLAGN] -> 0 || [FLAG1 | FLAG2 ... FLAGN] _
            HfstTransducer filtered_lexicons(*inverted_flag_filter);
            filtered_lexicons.harmonize_flag_diacritics(*rv);
            filtered_lexicons.compose(*rv, true);
            filtered_lexicons.harmonize_flag_diacritics(*flag_filter);
            filtered_lexicons.compose(*flag_filter, true).minimize();

            //fprintf(stderr, "filtered_lexicons:\n");
            //filtered_lexicons.write_in_att_format(stderr, 1);
            //fprintf(stderr, "--\n");                        

            // TEST: Rename all $P$ and $R$ flags so that they have the same name
            if (rename_flags_)
              {
                filtered_lexicons.substitute(dollar_to_foo_substitutions);
                filtered_lexicons.substitute("$P.FOO.BAR$", "@P.FOO.BAR@");
                filtered_lexicons.substitute("$R.FOO.BAR$", "@R.FOO.BAR@");
              }
            else
              {
                // Convert symbols "$[P|R].LEXNAME...$" back to "@[P|R].LEXNAME...@"            
                filtered_lexicons.substitute(reverse_flag_substitutions);
              }

            rv->assign(filtered_lexicons);
          }

    rv->minimize();
    return rv;
}


const LexcCompiler&
LexcCompiler::printConnectedness(bool & warnings_generated) const
{
  if (/* !quiet_ && */ (lexiconNames_ != continuations_))
    {
        vector<string> lexMinusCont = vector<string>(lexiconNames_.size());
        vector<string> contMinusLex = vector<string>(continuations_.size());
        vector<string>::iterator lexMinusContEnd = set_difference(
                lexiconNames_.begin(), lexiconNames_.end(),
                continuations_.begin(), continuations_.end(),
                lexMinusCont.begin());
        vector<string>::iterator contMinusLexEnd = set_difference(
                continuations_.begin(), continuations_.end(),
                lexiconNames_.begin(), lexiconNames_.end(),
                contMinusLex.begin());
        if (contMinusLexEnd - contMinusLex.begin() > 0)
        {
            for (vector<string>::iterator s = contMinusLex.begin();
                    s != contMinusLexEnd; ++s)
            {
              if (!quiet_)
                {
                  fprintf(stderr,
                          "Warning: Sublexicon is mentioned but not defined."
                          " (%s) \n", s->c_str());
                }
              warnings_generated = true;
            }
        }
        if (lexMinusContEnd - lexMinusCont.begin() > 0)
        {
          warnings_generated = true;
          if (!quiet_)
            {
              fprintf(stderr, "Warning: Sublexicons defined but not used\n");
              for (vector<string>::iterator s = lexMinusCont.begin();
                   s != lexMinusContEnd; ++s)
                {
                  fprintf(stderr, "%s ", s->c_str());
                }
              fprintf(stderr, "\n");
            }
        }
    }
    return *this;
}

} }

#else
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace hfst;
using hfst::lexc::LexcCompiler;

int
main(int argc, char** argv)
  {
    std::cout << "Unit tests for " __FILE__ ":";
    std::cout << std::endl << "constructors: ";
    std::cout << " (default)...";
    LexcCompiler lexcDefault();
#if HAVE_SFST
    std::cout << " (SFST)...";
    LexcCompiler lexcSfst(SFST_TYPE);
#endif
#if HAVE_OPENFST
    std::cout << " (OpenFST)...";
    LexcCompiler lexcOfst(TROPICAL_OPENFST_TYPE);
#endif
#if HAVE_FOMA
    std::cout << " (foma)...";
    LexcCompiler lexcFoma(FOMA_TYPE);
#endif
    std::cout << std::endl << "set verbose:";
#if HAVE_SFST
    lexcSfst.setVerbosity(true);
    lexcSfst.setVerbosity(false);
#endif
#if HAVE_OFST
    lexcOfst.setVerbosity(true);
    lexcOfst.setVerbosity(false);
#endif
#if HAVE_FOMA
    lexcFoma.setVerbosity(true);
    lexcFoma.setVerbosity(false);
#endif
    FILE* existence_check = fopen("LexcCompiler_test.lexc", "r");
    if (existence_check == NULL)
      {
        existence_check = fopen("LexcCompiler_test.lexc", "w");
        assert(existence_check != NULL);
        fprintf(existence_check, "Definitions\n"        \
                "\tdef1 = a\tb c;\n" \
                "\tdef2 = \"asdf\";\n" \
                "\tdef3 = \"sdfg\";\n" \
                "\tdef4 = \"xxx\"; def5 = \"zzz\";\n" \
                "\tdef6 = \"%%;\";\n" \
                "LEXICON Root\ncat # ;\ndog Plural ;\n");
        fclose(existence_check);
      }
    existence_check = fopen("LexcCompiler_test2.lexc", "r");
    if (existence_check == NULL)
      {
        existence_check = fopen("LexcCompiler_test2.lexc", "w");
        assert(existence_check != NULL);
        fprintf(existence_check, "LEXICON Plural\ns # ;\n");
        fclose(existence_check);
      }
    std::cout << std::endl << "parsing: ";
#if HAVE_SFST
    std::cout << "sfst parse(FILE)...";
    FILE* sfstFile = fopen("LexcCompiler_test.lexc", "r");
    lexcSfst.parse(sfstFile);
    fclose(sfstFile);
    std::cout << "parse(filename)...";
    lexcSfst.parse("LexcCompiler_test2.lexc");
#endif
#if HAVE_OPENFST
    std::cout << "ofst parse(FILE)...";
    FILE* ofstFile = fopen("LexcCompiler_test.lexc", "r");
    lexcOfst.parse(ofstFile);
    fclose(ofstFile);
    std::cout << "parse(filename)...";
    lexcOfst.parse("LexcCompiler_test2.lexc");
#endif
#if HAVE_FOMA
    std::cout << "foma parse(FILE)...";
    FILE* fomaFile = fopen("LexcCompiler_test.lexc", "r");
    lexcFoma.parse(fomaFile);
    fclose(fomaFile);
    std::cout << "parse(filename)...";
    lexcFoma.parse("LexcCompiler_test2.lexc");
#endif
      
    std::cout << std::endl << "add multichars:";
#if HAVE_SFST
    lexcSfst.addAlphabet("foo");
    lexcSfst.addAlphabet("bar");
#endif
#if HAVE_OFST
    lexcOfst.addAlphabet("foo");
    lexcOfst.addAlphabet("bar");
#endif
#if HAVE_FOMA
    lexcFoma.addAlphabet("foo");
    lexcFoma.addAlphabet("bar");
#endif
    std::cout << std::endl << "set lexicon name:";
#if HAVE_SFST
    lexcSfst.setCurrentLexiconName("Root");
#endif
#if HAVE_OFST
    lexcOfst.setCurrentLexiconName("Root");
#endif
#if HAVE_FOMA
    lexcFoma.setCurrentLexiconName("Root");
#endif
    std::cout << std::endl << "add entries:";
#if HAVE_SFST
    std::cout << " sfst string(dog, #)...";
    lexcSfst.addStringEntry("dog", "#", 0);
    std::cout << " sfst string(banana, apple, #)...";
    lexcSfst.addStringPairEntry("banana", "apple", "#", 0);
    std::cout << " sfst xre(f i:o 0:u g h t, #)...";
    lexcSfst.addXreEntry("f i:o 0:u g h t", "#", 0);
#endif
#if HAVE_OFST
    std::cout << " ofst string(dog, #)...";
    lexcOfst.addStringEntry("dog", "#", 0);
    std::cout << " ofst string(banana, apple, #)...";
    lexcOfst.addStringPairEntry("banana", "apple", "#", 0);
    std::cout << " ofst xre(f i:o 0:u g h t, #)...";
    lexcOfst.addXreEntry("f i:o 0:u g h t", "#", 0);
#endif
#if HAVE_FOMA
    std::cout << " foma string(dog, #)...";
    lexcFoma.addStringEntry("dog", "#", 0);
    std::cout << " foma string(banana, apple, #)...";
    lexcFoma.addStringPairEntry("banana", "apple", "#", 0);
    std::cout << " foma xre(f i:o 0:u g h t, #)...";
    lexcFoma.addXreEntry("f i:o 0:u g h t", "#", 0);
#endif
    std::cout << std::endl << "add definitions:";
#if HAVE_SFST
    std::cout << " sfst define(vowels, a | e | i | o | u | y)...";
    lexcSfst.addXreDefinition("Vowels", "a | e | i | o | u | y");
#endif
#if HAVE_OFST
    std::cout << " ofst define(vowels, a | e | i | o | u | y)...";
    lexcOfst.addXreDefinition("Vowels", "a | e | i | o | u | y");
#endif
#if HAVE_FOMA
    std::cout << " foma define(vowels, a | e | i | o | u | y)...";
    lexcFoma.addXreDefinition("Vowels", "a | e | i | o | u | y");
#endif
    std::cout << std::endl << "set initial lexicon name:";
#if HAVE_SFST
    std::cout << " sfst initial(Root)...";
    lexcSfst.setInitialLexiconName("Root");
#endif
#if HAVE_OFST
    std::cout << " ofst initial(Root)...";
    lexcOfst.setInitialLexiconName("Root");
#endif
#if HAVE_FOMA
    std::cout << " foma initial(Root)...";
    lexcFoma.setInitialLexiconName("Root");
#endif
    std::cout << std::endl << "compile:";
#if HAVE_SFST
    std::cout << " sfst compile...";
    assert(lexcSfst.compileLexical() != NULL);
#endif
#if HAVE_OFST
    std::cout << " ofst compile...";
    assert(lexcOfst.compileLexical() != NULL);
#endif
#if HAVE_FOMA
    std::cout << " foma compile...";
    assert(lexcFoma.compileLexical() != NULL);
#endif
    return EXIT_SUCCESS;
  }
#endif
// vim: set ft=cpp.doxygen:
