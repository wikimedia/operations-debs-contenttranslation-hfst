//! @file RuleSymbolVector.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Stores a rule and replaces its variables with values.

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

#ifndef RULE_SYMBOL_VECTOR_H_
#define RULE_SYMBOL_VECTOR_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <vector>
#include <string>
#include <utility>
#include "VariableDefs.h"

typedef std::pair<std::string, std::string> RuleCenter;

class RuleSymbolVector : public std::vector<std::string>
{
 protected:
  const VariableValueMap &vvm;
 public:
  //! @brief Create empty instance whose variable values are read from
  //! @a vvm.
  RuleSymbolVector(const VariableValueMap &vvm);

  //! @brief Replace variables with their values given by
  //! @a vvm and return a string representation of the result.
  std::string replace_variables(void);

  //! @brief Replace variables with their values given by
  //! @a vvm and return a string representation of the result.
  std::string replace_variables(const RuleCenter &center);

  //! @brief Regular @a push_back of std::vector<std::string>.
  RuleSymbolVector &push_back(const std::string &s);

  //! @brief Add the contents @a v to the end of @a this.
  RuleSymbolVector &push_back(const std::vector<std::string> &v);
};

#endif // RULE_SYMBOL_VECTOR_H_
