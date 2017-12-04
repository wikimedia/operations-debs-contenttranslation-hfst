//! @file TwolCGrammar.h
//!
//! @brief Hold the rules in a twolc-grammar, resolve their conflicts and store
//! them.
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

#ifndef TWOL_C_GRAMMAR_H_
#define TWOL_C_GRAMMAR_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "HfstTwolcDefs.h"
#include "LeftRestrictionArrowRule.h"
#include "RuleContainer.h"
#include "LeftArrowRuleContainer.h"
#include "RightArrowRuleContainer.h"

namespace op
{
  enum OPERATOR
  {
    RIGHT,
    LEFT,
    NOT_LEFT,
    LEFT_RIGHT,
    RE_RIGHT,
    RE_LEFT,
    RE_NOT_LEFT,
    RE_LEFT_RIGHT
  };
}

class TwolCGrammar
{
 protected:
  typedef HandySet<Rule*> RuleSet;
  typedef HandyMap<std::string,RuleSet> StringRuleSetMap;
  bool be_quiet;
  bool be_verbose;
  StringRuleSetMap name_to_rule_subcases;

  LeftArrowRuleContainer left_arrow_rule_container;
  RightArrowRuleContainer right_arrow_rule_container;
  RuleContainer other_rule_container;

  RuleContainer compiled_rule_container;

  std::string get_original_name(const std::string &name);

  SymbolRange diacritics;

 public:
  TwolCGrammar(bool be_quiet,
               bool be_verbose,
               bool resolve_left_conflicts,
               bool resolve_right_conflicts);
  void define_diacritics(const SymbolRange &diacritics);
  void add_rule(const std::string &name,
        const SymbolPair &center,
        op::OPERATOR oper,
        const OtherSymbolTransducerVector contexts);
  void add_rule(const std::string &name,
        const OtherSymbolTransducer &center,
        op::OPERATOR oper,
        const OtherSymbolTransducerVector contexts);
  void add_rule(const std::string &name,
        const SymbolPairVector &center,
        op::OPERATOR oper,
        const OtherSymbolTransducerVector contexts);
  void compile_and_store(HfstOutputStream &out);
};

#endif // TWOL_C_GRAMMAR_H_
