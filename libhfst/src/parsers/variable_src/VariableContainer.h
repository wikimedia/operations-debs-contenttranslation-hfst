//! @file VariableContainer.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Generic container-type for subsets of rule variables.

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

#ifndef VARIABLE_CONTAINER_H_
#define VARIABLE_CONTAINER_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "ConstContainerIterator.h"
#include "VariableContainerBase.h"

//! @brief Generic container-type for subsets of rule variables.
template<class T, class IT> class VariableContainer :
public VariableContainerBase<T>
{
 public:
  //! @brief Const iterator.
  typedef IT const_iterator;

  //! @brief Const iterator to beginning.
  const_iterator begin(void) const
  { return const_iterator::begin(VariableContainerBase<T>::T_vector); }

  //! @brief Const iterator to end.
  const_iterator end(void) const
  { return const_iterator::end(VariableContainerBase<T>::T_vector); }
};

#endif // VARIABLE_CONTAINER_H_
