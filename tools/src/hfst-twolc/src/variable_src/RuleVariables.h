//! @file RuleVariables.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Container for the variable blocks of a rule.

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

#ifndef RULE_VARIABLES_H_
#define RULE_VARIABLES_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "VariableBlockContainer.h"

class RuleVariablesConstIterator;

//! @brief Container for the variable blocks of a rule.
class RuleVariables
{
 protected:
  FreelyVariableBlockContainer freely_blocks;
  MatchedVariableBlockContainer matched_blocks;
  MixedVariableBlockContainer mixed_blocks;
  VariableValuesVector current_variable_block;

 public:
  typedef RuleVariablesConstIterator const_iterator;

  //! @brief Set the current variable.
  //!
  //! All calls to @a add_value() before the next call to @a set_variable()
  //! will add values for the variable @var.
  void set_variable(const std::string &var);

  //! @brief Add a new value for the current variable.
  //!
  //! @pre @a set_variable() has been called. Otherwise an @a EmptyContainer
  //! is thrown.
  void add_value(const std::string &value);

  //! @brief Add the values in @a values for the current variable.
  //!
  //! @pre @a set_variable() has been called. Otherwise an @a EmptyContainer
  //! is thrown.
  void add_values(const std::vector<std::string> &values);

  //! @brief Set the matcher for the current block and start a new block.
  void set_matcher(Matcher matcher);
  
  //! @brief Const iterator to the beginning.
  const_iterator begin(void) const;

  //! @brief Const iterator to the end.
  const_iterator end(void) const;

  //! Disacrd all defined blocks.
  void clear(void);

  //! @brief Return true, if no variables have been defines. Return false otherwise.
  bool empty(void) const;

  friend class RuleVariablesConstIterator;
};

#include "RuleVariablesConstIterator.h"

#endif // RULE_VARIABLES_H_
