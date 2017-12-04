//! @file RuleContainer.h
//!
//! @brief Holds pointers to rules, compiles the rules and stores them.
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

#include "RuleContainer.h"

RuleContainer::RuleContainer(void):
  report(true)
{}

RuleContainer::~RuleContainer(void)
{
  for (RuleVector::iterator it = rule_vector.begin();
       it != rule_vector.end();
       ++it)
    { delete *it; }
}

void RuleContainer::add_rule(Rule * rule)
{ rule_vector.push_back(rule); }

void RuleContainer::compile(std::ostream &msg_out,bool be_verbose)
{
  for (RuleVector::iterator it = rule_vector.begin();
       it != rule_vector.end();
       ++it)
    {
      if (be_verbose)
    { msg_out << "Compiling " << Rule::get_print_name((*it)->get_name())
          << std::endl; }
      (*it)->compile();
    }
}

void RuleContainer::store
(HfstOutputStream &out,std::ostream &msg_out,bool be_verbose)
{
  for (RuleVector::iterator it = rule_vector.begin();
       it != rule_vector.end();
       ++it)
    {
      if (be_verbose)
    { msg_out << "Storing " << Rule::get_print_name((*it)->get_name())
          << std::endl; }
      (*it)->store(out);
    }
}

void RuleContainer::add_missing_symbols_freely(const SymbolRange &diacritics)
{
  for (RuleVector::iterator it = rule_vector.begin();
       it != rule_vector.end();
       ++it)
    { (*it)->add_missing_symbols_freely(diacritics); }
}

#ifdef TEST_RULE_CONTAINER
#include <cassert>
int main(void)
{
  
}
#endif // TEST_RULE_CONTAINER
