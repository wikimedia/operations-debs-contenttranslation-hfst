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

#ifndef _HFST_PROC_H_
#define _HFST_PROC_H_

#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <string>
#include <iostream>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "implementations/optimized-lookup/transducer.h"

#define OL_FULL_DEBUG 1

using namespace hfst_ol;

class LookupPath;

/**
 * A list of pointers to lookup paths. They are pointers for the sake of
 * polymorphism
 */
typedef std::vector<LookupPath*> LookupPathVector;

class TokenIOStream;
class Token;
typedef std::vector<Token> TokenVector;
class OutputFormatter;

extern bool verboseFlag;
extern bool silentFlag;

extern bool displayWeightsFlag;
extern int maxAnalyses;
extern int maxWeightClasses;
extern bool preserveDiacriticRepresentationsFlag;
extern bool processCompounds;
extern bool displayRawAnalysisInCG;

// the following flags are only meaningful with certain debugging #defines
extern bool printDebuggingInformationFlag;

enum GenerationMode
{
  gm_clean,      // clear all
  gm_unknown,    // display unknown words, clear transfer and generation tags
  gm_all         // display all
};

/**
 * Different methods of dealing with capitalization during generation
 * IgnoreCase     - allow uppercase symbols to be treated as lowercase during
 *                  lookup. Retain the surface form's case for the output
 * CaseSensitive  - only allow the given case of the surface form symbol to be
 *                  fed into the transducer for lookup
 * DictionaryCase - allow uppercase symbols to be treated as lowecase during
 *                  lookup. Output the result with the capitalization found in
 *                  the transducer
 */
enum CapitalizationMode
  {
    IgnoreCase,
    CaseSensitive,
    DictionaryCase,
    CaseSensitiveDictionaryCase
  };

/**
 * Describes the case properties of a surface form (detection examines only
 * the first and last symbols)
 * LowerCase      - The first and last symbols are lowercase
 * FirstUpperCase - The first symbol is uppercase and the last is lowercase
 * UpperCase      - The first and last symbols are uppercase
 */
enum CapitalizationState {Unknown, LowerCase, FirstUpperCase, UpperCase};

void stream_error(const char* e);
void stream_error(std::string e);


#endif
