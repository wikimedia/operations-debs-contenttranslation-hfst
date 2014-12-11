//! @file RightArrowRule.h
//!
//! @brief Holds one =>-type twol rule.
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

#ifndef RIGHT_ARROW_RULE_H
#define RIGHT_ARROW_RULE_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "Rule.h"

class RightArrowRule : public Rule
{
 public:
  RightArrowRule(const std::string &name,
         const OtherSymbolTransducer &center,
         const OtherSymbolTransducerVector &contexts);

  //! @brief Compile @a this. Subclasses implement this method.
  OtherSymbolTransducer compile(void);
};

#endif // LEFT_ARROW_RULE_H
