//! @file RuleContainer.h
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

#include "RightArrowRuleContainer.h"

bool RightArrowRuleContainer::report_right_arrow_conflicts = true;
bool RightArrowRuleContainer::resolve_right_arrow_conflicts = true;

void RightArrowRuleContainer::set_report_right_arrow_conflicts(bool option)
{ report_right_arrow_conflicts = option; }

void RightArrowRuleContainer::set_resolve_right_arrow_conflicts(bool option)
{ resolve_right_arrow_conflicts = option; }

void RightArrowRuleContainer::add_rule_and_display_and_resolve_conflicts
(ConflictResolvingRightArrowRule * rule,std::ostream &out)
{
  if (center_to_rule_map.has_key(rule->center_pair))
    {
      if (report_right_arrow_conflicts)
    {
      out << "There is a =>-rule conflict between "
          << Rule::get_print_name
        (center_to_rule_map[rule->center_pair]->name)
          << " and " << Rule::get_print_name(rule->name) << "."
          << std::endl
          << "Resolving the conflict by joining contexts."
          << std::endl << std::endl;
    }

      if (resolve_right_arrow_conflicts)
        {
          center_to_rule_map[rule->center_pair]->resolve_conflict(*rule);
          rule->is_empty = true;
        }
      else
        { rule_vector.push_back(rule); }
    }
  else
    {
      center_to_rule_map[rule->center_pair] = rule;
      rule_vector.push_back(rule);
    }
}

#ifdef TEST_RIGHT_ARROW_RULE_CONTAINER
#include <cassert>
int main(void)
{

}
#endif
