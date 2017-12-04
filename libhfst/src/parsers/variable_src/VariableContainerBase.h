//! @file VariableContainerBase.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Base class for @a VariableContainer.

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

#ifndef VARIABLE_CONTAINER_BASE_H_
#define VARIABLE_CONTAINER_BASE_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "ConstContainerIterator.h"
//! @brief Base-class for @a VariableContainer.
template <class T> class VariableContainerBase
{
 protected:
  std::vector<T> T_vector;
 public:
  //! @brief Initialize empty instance.
  VariableContainerBase(void) {};

  //! @brief Prevent memory-leaks in polymorphism.
  virtual ~VariableContainerBase(void) {};

  //! @brief Add the object @a t.
  void add_object(const T &t)
  { T_vector.push_back(t); }

  //! @brief Discard all objects.
  void clear(void)
  { T_vector.clear(); }
};

#endif // VARIABLE_CONTAINER_BASE_H_
