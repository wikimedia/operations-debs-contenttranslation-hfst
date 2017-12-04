//! @file HfstTwolcDefs.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Definitions for hfst-twolc.

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

#ifndef HFST_TWOLC_DEFS_H_
#define HFST_TWOLC_DEFS_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <map>
#include <set>
#include <deque>
#include <iosfwd>

//! @brief Convenient subclass of std::map.
template <class K,class V> class HandyMap : public std::map<K,V>
{
 public:
  //! @brief Return true if @a k is associated with a value. Otherwise, return
  //! false.
  bool has_key(const K &k) const
  { return std::map<K,V>::find(k) != std::map<K,V>::end(); }

  //! @brief Return the value associated with @a k.
  //!
  //! @pre The key @a k is associated with a value.
  V get_value(const K &k) const
  { return std::map<K,V>::find(k)->second; }
};

//! @brief Convenient subclass of std::set.
template <class V> class HandySet : public std::set<V>
{
 public:
  //! @brief Return true if @a v belongs to this set.
  bool has_element(const V &v) const
  { return std::set<V>::find(v) != std::set<V>::end(); }
};

//! @brief Convenient subclass of std::queue
template <class C> class HandyDeque : public std::deque<C>
{
 public:
  C get_front_and_pop(void)
  {
    C temp = std::deque<C>::front();
    std::deque<C>::pop_front();
    return temp;
  }
};

template <class C> std::ostream &operator<<
(std::ostream &out, const HandyDeque<C> &d)
{
  for (typename HandyDeque<C>::const_iterator it = d.begin();
       it != d.end();
       ++it)
    { out << *it << " "; }
  return out;
}

#endif // HFST_TWOLC_DEFS_H_
