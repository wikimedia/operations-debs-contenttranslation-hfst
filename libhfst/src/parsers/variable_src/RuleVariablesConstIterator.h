//! @file RuleVariablesConstIterator.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Const iterator for @a RuleVariables objects.

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

#ifndef RULE_VARIABLES_CONST_ITERATOR_H_
#define RULE_VARIABLES_CONST_ITERATOR_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "RuleVariables.h"

class RuleVariablesConstIterator
{
 protected:
  FreelyVariableBlockConstIterator f_it;
  MatchedVariableBlockConstIterator ma_it;
  MixedVariableBlockConstIterator mi_it;

  FreelyVariableBlockConstIterator f_begin;
  MatchedVariableBlockConstIterator ma_begin;
  MixedVariableBlockConstIterator mi_begin;

  FreelyVariableBlockConstIterator f_end;
  MatchedVariableBlockConstIterator ma_end;
  MixedVariableBlockConstIterator mi_end;

  static RuleVariablesConstIterator begin(const RuleVariables &rv);
  static RuleVariablesConstIterator end(const RuleVariables &rv);
  void set_begin_and_end(const RuleVariables &rv);
 public:

  //! @brief Assignment.
  RuleVariablesConstIterator &operator=
    (const RuleVariablesConstIterator &another);

  //! @brief Test equality with @a another.
  bool operator==(const RuleVariablesConstIterator &another);

  //! @brief Test unequality with another.
  bool operator!=(const RuleVariablesConstIterator &another);

  //! Increment.
  void operator++(void);

  //! @brief Return an iterator which is equivalent to @a this incremented
  //! @a i times.
  RuleVariablesConstIterator operator+(size_t i);

  //! @brief Set the current variables values to @a vvm.
  void set_values(VariableValueMap &vvm);

  friend class RuleVariables;
};

#endif // RULE_VARIABLES_CONST_ITERATOR_H_
