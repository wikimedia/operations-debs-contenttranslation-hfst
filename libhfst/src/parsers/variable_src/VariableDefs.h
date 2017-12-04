//! @file VariableDefs.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Definitions for files implementing rule variable functionality.

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

#ifndef VARIABLE_DEFS_H_
#define VARIABLE_DEFS_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <vector>
#include <string>
#include <iostream>

#include "HfstTwolcDefs.h"

//! @brief Translates variables to values.
typedef HandyMap<std::string,std::string> VariableValueMap;

//! @brief Stores indices. Used with variable blocks with matcher mixed.
typedef HandySet<size_t> IndexSet;

//! @brief Thrown when trying to access an object in an empty container.
class EmptyContainer {};

//! Thrown when matched keyword is used with sets of unequal sizes.
class UnequalSetSize {};

//! The different variable block matchers.
enum Matcher { FREELY,MATCHED,MIXED };

#endif // VARIABLE_DEFS_H_
