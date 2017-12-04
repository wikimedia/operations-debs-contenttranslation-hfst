//! @file VariableValueIterator.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Iterator for container of type @a VariableValue.

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

#ifndef VARIABLE_VALUE_ITERATOR_H_
#define VARIABLE_VALUE_ITERATOR_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

class VariableValues;

//! @brief Iterator for container of type @a VariableValues.
template <class IT> class VariableValueIterator
{
 protected:
  std::string variable;
  IT it;
  static VariableValueIterator begin(const std::string &variable,
                     const std::vector<std::string> &v)
  { return VariableValueIterator<IT>(variable,v.begin()); }

  static VariableValueIterator end(const std::string &variable,
                    const std::vector<std::string> &v)
  { return VariableValueIterator<IT>(variable,v.end()); }
  
  VariableValueIterator(const std::string &variable,const IT &it):
  variable(variable), it(it)
  {};

 public:
  //! @brief Initialize empty instance.
  VariableValueIterator(void) {}

  //! @brief Copy construct from @a another.
  VariableValueIterator(const VariableValueIterator<IT> &another):
  variable(another.variable), it(another.it)
  {}
  
  //! @brief Assign @a another.
  VariableValueIterator &operator=(const VariableValueIterator<IT> &another)
  {
    if (! (this == &another))
      {
    variable = another.variable;
    it = another.it;
      }
    return *this;
  }

  //! @brief Test equality with another.
  bool operator==(const VariableValueIterator<IT> &another) const
  { return variable == another.variable && it == another.it; }

  //! @brief Test unequality with another.
  bool operator!=(const VariableValueIterator<IT> &another) const
  { return ! (*this == another); }

  //! Increment.
  void operator++(void)
  { ++it; }

  //! Return an iterator which points @a i steps further than @a this.
  VariableValueIterator<IT> operator+(size_t i) const
  {
    VariableValueIterator<IT> vvit(*this);
    for (size_t n = 0; n < i; ++n) { ++vvit; }
    return vvit;
  }

  //! @brief Return the number of incrementations needed to make @a this point
  //! to the same position as @a another.
  int operator-(const VariableValueIterator<IT> &another)
  { return it - another.it; }

  //! @brief Set the value of the variable of the underlying container to the
  //! its value.
  void set_values(VariableValueMap * vvm) const
  { vvm->operator[](variable) = *it; }
  friend class VariableValues;
};

//! @brief Const version of  @a VariableValueIterator.
typedef VariableValueIterator<std::vector<std::string>::const_iterator>
ConstVariableValueIterator;

#endif // VARIABLE_VALUE_ITERATOR_H_
