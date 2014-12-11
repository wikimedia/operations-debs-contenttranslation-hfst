//! @file VariableValues.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Container for the values of one rule variable.

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

#ifndef VARIABLE_VALUES_H_
#define VARIABLE_VALUES_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "VariableDefs.h"
#include "VariableValueIterator.h"

//! @brief Container for the values of one rule variable.
class VariableValues : public std::vector<std::string>
{
 protected:
  std::string variable;
 public:
  typedef ConstVariableValueIterator const_iterator;

  //! @brief Set the variable to @a variable.
  void set_variable(const std::string &variable);

  //! @brief Const iterator to beginning.
  const_iterator begin(void) const;

  //! @brief Const iterator to end.
  const_iterator end(void) const;
};

//! @brief Container for @a VariableValues objects..
typedef std::vector<VariableValues> VariableValuesVector;

#endif // VARIABLE_VALUES_H_
