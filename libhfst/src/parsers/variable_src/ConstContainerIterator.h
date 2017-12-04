//! @file ConstContainerIterator.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Generic iterator for sets of variables.

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

#ifndef CONST_CONTAINER_ITERATOR_H_
#define CONST_CONTAINER_ITERATOR_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "VariableDefs.h"

template <class T> class VariableContainerBase;
template<class T, class IT> class VariableContainer;

//! @brief Generic iterator for sets of variables.
template <class T> class ConstContainerIterator
{
 protected:
  typedef std::vector<T> TVector;
  typedef std::vector<typename T::const_iterator> TIteratorVector;

  std::vector<typename T::const_iterator> iterator_vector;
  std::vector<typename T::const_iterator> begin_iterator_vector;
  std::vector<typename T::const_iterator> end_iterator_vector;

 static ConstContainerIterator begin(const TVector &v)
  {
    ConstContainerIterator i;
    for (typename TVector::const_iterator it = v.begin();
     it != v.end(); ++it)
      {
    i.iterator_vector.push_back(it->begin());
    i.begin_iterator_vector.push_back(it->begin());
    i.end_iterator_vector.push_back(it->end());
      }
    return i;
  };
  static ConstContainerIterator end(const TVector &v)
  {
    ConstContainerIterator i;
    for (typename TVector::const_iterator it = v.begin();
     it != v.end(); ++it)
      {
    i.iterator_vector.push_back(it->end());
    i.begin_iterator_vector.push_back(it->begin());
    i.end_iterator_vector.push_back(it->end());
      }
    return i;
  };

 public:
  //! @brief Empty instance.
  ConstContainerIterator(void)
  {}

  //! @brief Copy-constructor.
  ConstContainerIterator(const ConstContainerIterator &another):
   iterator_vector(another.iterator_vector),
   begin_iterator_vector(another.begin_iterator_vector),
   end_iterator_vector(another.end_iterator_vector)
   {};

  //! @brief Prevent memory-leaks with polymorphism.
  virtual ~ConstContainerIterator(void) {};

  //! @brief Assign @a another to this.
  ConstContainerIterator &operator=(const ConstContainerIterator &another)
   {
     if (this != &another)
       {
     iterator_vector = another.iterator_vector;
     begin_iterator_vector = another.begin_iterator_vector;
     end_iterator_vector = another.end_iterator_vector;
       }
     return *this;
   };

  //! @brief Test equality with @another.
  bool operator==(const ConstContainerIterator &another) const
   { return iterator_vector == another.iterator_vector; };

  //! @brief Test inequality with @another.
  bool operator!=(const ConstContainerIterator &another) const
  { return ! (*this == another); };

  //! @brief Increment.
  virtual int operator++(void)
   {
     bool found_a_non_final_iterator = false;
     for (size_t i = 0 ; i < iterator_vector.size(); ++i)
       {
     if (iterator_vector.at(i) + 1 == end_iterator_vector.at(i))
       { iterator_vector.at(i) = begin_iterator_vector.at(i); }
     else
       {
         ++iterator_vector.at(i);
         found_a_non_final_iterator = true;
         break;
       }
       }
     if (! found_a_non_final_iterator)
       { iterator_vector = end_iterator_vector; }
     return 1;
   };

  //! Return an iterator which points @a i steps further than @a this.
  ConstContainerIterator operator+(size_t i) const
  {
    ConstContainerIterator it(*this);
    for (size_t n = 0; n < i; ++n) { ++it; }
    return it;
  };

  //! @brief Set values for appropriate variables in @a vvm.
  void set_values(VariableValueMap * vvm) const
  {
    for (typename TIteratorVector::const_iterator it =
       iterator_vector.begin();
     it != iterator_vector.end();
     ++it)
      { it->set_values(vvm); }
  }
  
  //! @brief Dereference. Needed only for complienace with c++ definition of
  //! forward iterators. Genuine functionality is implemented with
  //! @a set_values().
  TVector operator*(void)
    { return TVector(); }

  friend class VariableContainerBase<T>;
  template<class X,class Y> friend class VariableContainer;
};

#endif // CONST_CONTAINER_ITERATOR_H_
