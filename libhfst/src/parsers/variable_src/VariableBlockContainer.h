//! @file VariableBlockContainer.h
//!
//! @author Miikka Silfverberg
//!
//! @brief Containers for @a VariableBlock objects.

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

#ifndef VARIABLE_BLOCK_CONTAINER_H_
#define VARIABLE_BLOCK_CONTAINER_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "VariableBlock.h"

//! Iterator for @a FreelyVariableBlock objects.
typedef ConstContainerIterator<FreelyVariableBlock>
FreelyVariableBlockConstIterator;

//! Iterator for @a MatchedVariableBlock objects.
typedef ConstContainerIterator<MatchedVariableBlock>
MatchedVariableBlockConstIterator;

//! Iterator for @a MixedVariableBlock objects.
typedef ConstContainerIterator<MixedVariableBlock>
MixedVariableBlockConstIterator;

//! Container for @a FreelyVariableBlock objects.
typedef
VariableContainer<FreelyVariableBlock,FreelyVariableBlockConstIterator>
FreelyVariableBlockContainer;

//! Container for @a MatchedVariableBlock objects.
typedef
VariableContainer<MatchedVariableBlock,MatchedVariableBlockConstIterator>
MatchedVariableBlockContainer;

//! Container for @a MixedVariableBlock objects.
typedef
VariableContainer<MixedVariableBlock,MixedVariableBlockConstIterator>
MixedVariableBlockContainer;

#endif // VARIABLE_BLOCK_CONTAINER_H_
