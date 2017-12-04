//! @file VariableBlock.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Specializations of @a VariableContainer for variable blocks.

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

#ifndef VARIABLE_BLOCK_H_
#define VARIABLE_BLOCK_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "VariableValues.h"
#include "VariableContainer.h"
#include "ConstContainerIterator.h"
#include "MatchedConstContainerIterator.h"
#include "MixedConstContainerIterator.h"

//! @brief Prototype for variable blocks.
template<class IT> class VariableBlock :
public VariableContainer<VariableValues,IT>
{
 public:
  VariableBlock(void):
   VariableContainer<VariableValues,IT>()
  {}
  VariableBlock(const VariableValuesVector &v):
   VariableContainer<VariableValues,IT>()
   {
     for (VariableValuesVector::const_iterator it = v.begin(); it != v.end();
      ++it)
       {
     if (it->empty())
       { throw EmptyContainer(); }
     VariableContainer<VariableValues,IT>::add_object(*it);
       }
   }
};

//! @brief Container for the variables in a variable block with matcher
//! <tt>FREELY</tt>
typedef VariableBlock<ConstContainerIterator<VariableValues> >
  FreelyVariableBlock;

//! @brief Container for the variables in a variable block with matcher
//! <tt>MATCHED</tt>
typedef
VariableBlock<MatchedConstContainerIterator<VariableValues> >
  MatchedVariableBlock;

//! @brief Container for the variables in a variable block with matcher
//! <tt>MIXED</tt>
typedef VariableBlock<MixedConstContainerIterator<VariableValues> >
  MixedVariableBlock;

#endif // VARIABLE_BLOCK_H_

