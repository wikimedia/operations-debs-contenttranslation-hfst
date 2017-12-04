#ifndef HEADER_GUESSIFY_FST_H
#define HEADER_GUESSIFY_FST_H

//! @file guessify_fst.cc
//!
//! @brief Functions for making an affix guesser from a morphological analyzer.
//!
//! @author Miikka Silfverberg (HFST Team)


//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, version 3 of the License.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "HfstTransducer.h"

using hfst::HfstTransducer;
using hfst::HfstOutputStream;
using hfst::StringSet;

// Default penalty for skipping symbols in input strings.
#define DEFAULT_PENALTY 1.0

// Prefix which all inflection category symbols in the morphological
// analyzer are expected to have.
#define CATEGORY_SYMBOL_PREFIX "[GUESS_CATEGORY="

// Replace every flag diacritic symbol with an epsilon.
void remove_flag_diacritics(HfstTransducer &morphological_analyzer,
			    const StringSet &alphabet);

// Return the set of all symbols in alphabet, which start "[GUESS_CATEGORY=".
StringSet get_cathegory_symbols(const StringSet &alphabet);

// Return an automaton that only accepts paths which contain at least
// one cathegory symbol ("[GUESS_CATEGORY=...").
HfstTransducer get_invalid_form_filterer(const StringSet &alphabet);

// Return a transducer, which rewrites all symbols after the
// first symbol after the cathegory symbol into "<removed_symbol>".
HfstTransducer get_prefix_remover(const StringSet &alphabet);

// Return true if @a symbol has a prefix "[CATEGORY_SYMBOL=".
bool is_cathegory_symbol(const std::string &symbol);

// Rewrite all pairs "<removed_symbol>":"@_EPSILON_SYMBOL_@" to
// "@_EPSILON_SYMBOL_@" and other pairs "<removed_symbol>":"x" to "x".
void rewrite_removed_symbols(HfstTransducer &morphological_analyzer,
			     const StringSet &alphabet);

// Return a guesser, which has been compiled from
// morpholocial_analyzer. The parameter @a penalty gives the penalty
// for skipping letters.
//
// Precondition: the input tape of morphological_analyzer represents
// word forms and the output tape represents analyses.
//
// Postcondition: The input tape of morphological analyzer represents
// reversed word forms and the output tape represents reversed
// analyses.
HfstTransducer guessify_analyzer(HfstTransducer morphological_analyzer,
				 float penalty);

// Store @a guesser in @a filename. If @filename is <stdout>, store @a
// guesser in STDOUT. if @a compile_generator is true, also compile a
// generator from @a guesser and store it in the same file as @a guesser
// after @a guesser.
void store_guesser(HfstTransducer &guesser,
		   HfstOutputStream &out,
		   bool compile_generator);

#endif // HEADER_GUESSIFY_FST_H
