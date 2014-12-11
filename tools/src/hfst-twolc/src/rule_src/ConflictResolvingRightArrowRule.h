//! @file ConflictResolvingRightArrowRuleRule.h
//!
//! @brief Holds one =>-type twol rule, whose center is a single symbol pair.
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

#ifndef CONFLICT_RESOLVING_RIGHT_ARROW_RULE_H_
#define CONFLICT_RESOLVING_RIGHT_ARROW_RULE_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "RightArrowRule.h"

class RightArrowRuleContainer;

class ConflictResolvingRightArrowRule : public RightArrowRule
{
 protected:
  SymbolPair center_pair;
 public:
  ConflictResolvingRightArrowRule(const std::string &name,
                  const SymbolPair &center,
                  const OtherSymbolTransducerVector &contexts);
  bool conflicts_this(ConflictResolvingRightArrowRule &another);
  void resolve_conflict(ConflictResolvingRightArrowRule &another);

  friend class RightArrowRuleContainer;
};

#endif // CONFLICT_RESOLVING_RIGHT_ARROW_RULE_H_
