//! @file LeftRestrictionArrowRule.h
//!
//! @brief Holds one /<=-type twol rule.
//!
//! @author Miikka Silfverberg

//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, version 3 of the License.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef LEFT_RESTRICTION_ARROW_RULE_H
#define LEFT_RESTRICTION_ARROW_RULE_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "Rule.h"

class LeftRestrictionArrowRule : public Rule
{
 public:
  LeftRestrictionArrowRule(const std::string &name,
               const OtherSymbolTransducer &center,
               const OtherSymbolTransducerVector &contexts);

  //! @brief Inititalize.
  LeftRestrictionArrowRule(const std::string &name,
               const SymbolPair &center,
               const OtherSymbolTransducerVector &contexts);

  //! @brief Compile @a this. Subclasses implement this method.
  OtherSymbolTransducer compile(void);
};

#endif // LEFT_RESTRICTION_ARROW_RULE_H
