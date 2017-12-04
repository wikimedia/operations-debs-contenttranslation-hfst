//! @file MixedConstContainerIterator.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Specialization of @a ConstContainerIterator for "mixed" variable
//! blocks.

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

#ifndef MIXED_CONTAINER_ITERATOR_H_
#define MIXED_CONTAINER_ITERATOR_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <set>
#include "ConstContainerIterator.h"

//! @brief Iterator for a block of variables with matcher <tt>MIXED</tt>
template <class T> class MixedConstContainerIterator :
public ConstContainerIterator<T>
{
 protected:
  bool didnt_end(void)
  {
    for (size_t i = 0; i < ConstContainerIterator<T>::iterator_vector.size();
     ++i)
       {
     if(ConstContainerIterator<T>::iterator_vector.at(i) !=
        ConstContainerIterator<T>::end_iterator_vector.at(i))
       { return true; }
       }
    return false;
  }
  bool equal_indices(void)
  {
    IndexSet index_set;
    for (size_t i = 0; i < ConstContainerIterator<T>::iterator_vector.size();
     ++i)
      {
    size_t index =
      ConstContainerIterator<T>::iterator_vector.at(i) -
      ConstContainerIterator<T>::begin_iterator_vector.at(i);
    if (index_set.has_element(index))
      { return true; }
    index_set.insert(index);
      }
    return false;
  }
 public:
  //! @brief Construct from super class instance.
  MixedConstContainerIterator(const ConstContainerIterator<T> &another)
   {
      ConstContainerIterator<T>::operator=(another);
      while (didnt_end() && equal_indices())
    { operator++(); }
   }
  //! @brief Increment.
  int operator++(void)
   {
     do { ConstContainerIterator<T>::operator++(); }
     while (didnt_end() && equal_indices());
     return 1;
   }
  MixedConstContainerIterator operator+(size_t i) const
  {
    MixedConstContainerIterator it(*this);
    for (size_t n = 0; n < i; ++n) { ++it; }
    return it;
  }
};

#endif // MIXED_CONTAINER_ITERATOR_H_
