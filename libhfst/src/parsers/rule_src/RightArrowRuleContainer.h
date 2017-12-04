//! @file RuleContainer.h
//!
//! @brief Holds pointers to =>-rules, compiles the rules and stores them.
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

#ifndef RIGHT_ARROW_RULE_CONTAINER_H_
#define RIGHT_ARROW_RULE_CONTAINER_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <map>

#include "RuleContainer.h"
#include "ConflictResolvingRightArrowRule.h"

class RightArrowRuleContainer : public RuleContainer
{
 protected:
  static bool report_right_arrow_conflicts;
  static bool resolve_right_arrow_conflicts;
  typedef HandyMap<SymbolPair,ConflictResolvingRightArrowRule*>
    CenterToRuleMap;
  CenterToRuleMap center_to_rule_map;
 public:
  static void set_report_right_arrow_conflicts(bool option);
  static void set_resolve_right_arrow_conflicts(bool option);
  void add_rule_and_display_and_resolve_conflicts
    (ConflictResolvingRightArrowRule * rule,std::ostream &out);
};

#endif // RIGHT_ARROW_RULE_CONTAINER_H_
