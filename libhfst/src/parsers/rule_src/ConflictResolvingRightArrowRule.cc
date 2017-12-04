//! @file ConflictResolvingRightArrowRuleRule.cc
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

#include "ConflictResolvingRightArrowRule.h"

ConflictResolvingRightArrowRule::ConflictResolvingRightArrowRule
(const std::string &name,
 const SymbolPair &center,
 const OtherSymbolTransducerVector &contexts):
  RightArrowRule(name,
         get_center(center.first,center.second),
         contexts),
  center_pair(center)
{}

bool ConflictResolvingRightArrowRule::conflicts_this
(ConflictResolvingRightArrowRule &another)
{ return
    center_pair.first == another.center_pair.first &&
    center_pair.second == another.center_pair.second; }

void ConflictResolvingRightArrowRule::resolve_conflict
(ConflictResolvingRightArrowRule &another)
{
  context.
    apply(&HfstTransducer::disjunct,another.context).
    apply(&HfstTransducer::minimize);
  name += " and " + another.name;
}

#ifdef TEST_CONFLICT_RESOLVING_RIGHT_ARROW_RULE
#include <cassert>
int main(void)
{
  HandySet<SymbolPair> symbol_pairs;
  symbol_pairs.insert(SymbolPair("a","b"));
  symbol_pairs.insert(SymbolPair("a","c"));
  symbol_pairs.insert(SymbolPair("d","e"));
  OtherSymbolTransducer::set_symbol_pairs(symbol_pairs);
  OtherSymbolTransducer::set_transducer_type(hfst::TROPICAL_OPENFST_TYPE);
  OtherSymbolTransducer unknown(TWOLC_UNKNOWN);
  unknown.apply(&HfstTransducer::repeat_star);
  OtherSymbolTransducer diamond(TWOLC_DIAMOND);
  OtherSymbolTransducer a_sth("a",TWOLC_UNKNOWN);
  OtherSymbolTransducer context1(unknown);
  context1.
    apply(&HfstTransducer::concatenate,a_sth).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown);
  OtherSymbolTransducerVector v1(1,context1);
  ConflictResolvingRightArrowRule rule1("__TWOLC_RULE_NAME=\"test rule\"",
                       SymbolPair("a","b"),v1);

  OtherSymbolTransducer context2(unknown);
  OtherSymbolTransducer a_c("a","c");
  context2.
    apply(&HfstTransducer::concatenate,a_c).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown);
  OtherSymbolTransducerVector v2(1,context2);
  ConflictResolvingRightArrowRule rule2("__TWOLC_RULE_NAME=\"test rule\"",
                       SymbolPair("a","b"),v2);

  assert(rule1.conflicts_this(rule2));
  rule1.resolve_conflict(rule2);
  //std::cout << rule1.compile().get_transducer() << std::endl;
}
#endif // TEST_CONFLICT_RESOLVING_RIGHT_ARROW_RULE
