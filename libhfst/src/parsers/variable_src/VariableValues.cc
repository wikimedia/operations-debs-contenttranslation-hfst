//! @file VariableValues.cc
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

#include "VariableValues.h"

void VariableValues::set_variable(const std::string &variable)
{ this->variable = variable; }

VariableValues::const_iterator VariableValues::begin(void) const
{ return const_iterator(variable,std::vector<std::string>::begin()); }

VariableValues::const_iterator VariableValues::end(void) const
{ return const_iterator(variable,std::vector<std::string>::end()); }
