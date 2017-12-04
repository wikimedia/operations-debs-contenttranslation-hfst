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

#ifndef RULE_CONTAINER_H_
#define RULE_CONTAINER_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <vector>

#include "Rule.h"

class RuleContainer
{
 protected:
  typedef Rule::RuleVector RuleVector;
  bool report;
  RuleVector rule_vector;

 public:
  RuleContainer(void);
  virtual void add_rule(Rule * rule);
  virtual ~RuleContainer(void);
  void compile(std::ostream &msg_out,bool be_verbose);
  void store(HfstOutputStream &out,std::ostream &msg_out,bool be_verbose);
  void add_missing_symbols_freely(const SymbolRange &diacritics);
};

#endif // RULE_CONTAINER_H_
