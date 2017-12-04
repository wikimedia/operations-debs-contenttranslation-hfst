//! @file MatchedConstContainerIterator.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Specialization of @a ConstContainerIterator for "matched" variable
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

#ifndef MATCHED_CONTAINER_ITERATOR_H_
#define MATCHED_CONTAINER_ITERATOR_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "ConstContainerIterator.h"

//! @brief Iterator for a block of variables with matcher <tt>MATCHED</tt>.
template <class T> class MatchedConstContainerIterator :
public ConstContainerIterator<T>
{
 public:
  //! @brief Construct from super class instance.
  MatchedConstContainerIterator(const ConstContainerIterator<T> &another)
    {
      ConstContainerIterator<T>::operator=(another);
      
      int set_sizes =
	ConstContainerIterator<T>::begin_iterator_vector.size() == 0 ?
	0
	:
	ConstContainerIterator<T>::end_iterator_vector[0] -
	ConstContainerIterator<T>::begin_iterator_vector[0];

      for (size_t i = 0;
	   i < ConstContainerIterator<T>::begin_iterator_vector.size();
	   ++i)
	{
	  if (ConstContainerIterator<T>::end_iterator_vector[i] -
	      ConstContainerIterator<T>::begin_iterator_vector[i]
	      != set_sizes)
	    { throw UnequalSetSize(); }
	}
    };

  //! @brief Increment.
  int operator++(void)
   {
     for (size_t i = 0;
      i < ConstContainerIterator<T>::iterator_vector.size();
      ++i)
       { ++ConstContainerIterator<T>::iterator_vector.at(i); }
     return 1;
   };
  MatchedConstContainerIterator operator+(size_t i) const
  {
    MatchedConstContainerIterator it(*this);
    for (size_t n = 0; n < i; ++n) { ++it; }
    return it;
  };
};

#endif // MATCHED_CONTAINER_ITERATOR_H_
