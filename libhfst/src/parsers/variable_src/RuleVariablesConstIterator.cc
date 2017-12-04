//! @file RuleVariablesConstIterator.cc
//!
//! @author Miikka Silfverberg

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

#include "RuleVariablesConstIterator.h"

RuleVariablesConstIterator RuleVariablesConstIterator::begin
(const RuleVariables &rv)
{
  RuleVariablesConstIterator it;
  it.f_it = rv.freely_blocks.begin();
  it.ma_it = rv.matched_blocks.begin();
  it.mi_it = rv.mixed_blocks.begin();

  it.set_begin_and_end(rv);
  return it;
}

RuleVariablesConstIterator RuleVariablesConstIterator::end
(const RuleVariables &rv)
{
  RuleVariablesConstIterator it;
  it.f_it = rv.freely_blocks.end();
  it.ma_it = rv.matched_blocks.end();
  it.mi_it = rv.mixed_blocks.end();

  it.set_begin_and_end(rv);
  return it;
}

void RuleVariablesConstIterator::set_begin_and_end(const RuleVariables &rv)
{
  f_begin = rv.freely_blocks.begin();
  ma_begin = rv.matched_blocks.begin();
  mi_begin = rv.mixed_blocks.begin();
  f_end = rv.freely_blocks.end();
  ma_end = rv.matched_blocks.end();
  mi_end = rv.mixed_blocks.end();
}

RuleVariablesConstIterator &RuleVariablesConstIterator::operator=
(const RuleVariablesConstIterator &another)
{
  f_it = another.f_it;
  ma_it = another.ma_it;
  mi_it = another.mi_it;
  f_begin = another.f_begin;
  ma_begin = another.ma_begin;
  mi_begin = another.mi_begin;
  f_end = another.f_end;
  ma_end = another.ma_end;
  mi_end = another.mi_end;
  return *this;
}

bool RuleVariablesConstIterator::operator==
(const RuleVariablesConstIterator &another)
{ return f_it == another.f_it && ma_it == another.ma_it &&
    mi_it == another.mi_it; }

bool RuleVariablesConstIterator::operator!=
(const RuleVariablesConstIterator &another)
{ return ! (*this == another); }

void RuleVariablesConstIterator::operator++(void)
{
  if (f_it + 1 == f_end)
    {
      if (ma_it + 1 == ma_end)
    {
      if (mi_it + 1 == mi_end)
        {
          f_it = f_end;
          ma_it = ma_end;
          mi_it = mi_end;
          return;
        }
      else
        { ++mi_it; }
      ma_it = ma_begin;
    }
      else
    { ++ma_it; }
      f_it = f_begin;
    }
  else
    { ++f_it; }
}

RuleVariablesConstIterator RuleVariablesConstIterator::operator+(size_t i)
{
  RuleVariablesConstIterator it = *this;
  for (size_t n = 0; n < i; ++n) { ++it; }
  return it;
}

void RuleVariablesConstIterator::set_values(VariableValueMap &vvm)
{
  f_it.set_values(&vvm);
  ma_it.set_values(&vvm);
  mi_it.set_values(&vvm);
}
