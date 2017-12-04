//! @file grammar_defs.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Simple data structures for basic twolc grammar concepts.

//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, version 3 of the Licence.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef GRAMMAR_DEFS_H__
#define GRAMMAR_DEFS_H__

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <utility>
#include <vector>
#include <string>
#include <map>

//! @brief A single symbol e.g. an operator.
typedef std::string Symbol;

//! @brief Pair of symbols. e.g. <tt>x:y</tt>.
typedef std::pair<std::string,std::string> SymbolPair;

//! @brief A range of symbols e.g. in a set definition.
typedef std::vector<std::string> SymbolRange;

//! @brief A range of symbol pairs e.g. in the alphabet.
typedef std::vector<SymbolPair>  SymbolPairRange;

//! @brief A range of symbol pairs e.g. in the alphabet.
typedef std::vector<SymbolPair>  SymbolPairVector;

//! @brief A symbols set consisting of a name and a @a SymbolRange.
typedef std::pair<std::string,SymbolRange> SymbolSet;

//! @brief Maps a set name to the corresponding @a SymbolSet.
typedef std::map<std::string,SymbolSet>  SymbolSetMap;
#endif
