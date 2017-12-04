//! @file SimpleCenterLeftArrowRuleRule.cc
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

#include "ConflictResolvingLeftArrowRule.h"

ConflictResolvingLeftArrowRule::ConflictResolvingLeftArrowRule
(const std::string &name,
 const SymbolPair &center,
 const OtherSymbolTransducerVector &contexts):
  LeftArrowRule(name,
        Rule::get_center(center.first,center.second),
        contexts),
  input_symbol(center.first)
{}

OtherSymbolTransducer get_wb_fst(void)
{
  OtherSymbolTransducer wb("__HFST_TWOLC_.#.",
                           "__HFST_TWOLC_.#.");

  OtherSymbolTransducer no_wb(TWOLC_UNKNOWN,
                              TWOLC_UNKNOWN);
  
  OtherSymbolTransducer diamond(TWOLC_DIAMOND,
                                TWOLC_DIAMOND);

  no_wb.apply(&HfstTransducer::subtract, wb);
  no_wb.apply(&HfstTransducer::disjunct, diamond);
  no_wb.apply(&HfstTransducer::repeat_star);

  OtherSymbolTransducer result(wb);
  result.apply(&HfstTransducer::concatenate, no_wb);
  result.apply(&HfstTransducer::concatenate, wb);

  return result;
}

OtherSymbolTransducer wbize(const OtherSymbolTransducer &t)
{
  OtherSymbolTransducer t_copy(t);
  OtherSymbolTransducer wb_fst = get_wb_fst();
  t_copy.apply(&HfstTransducer::intersect,wb_fst);
  return t_copy;
}

bool ConflictResolvingLeftArrowRule::conflicts_this
(const ConflictResolvingLeftArrowRule &another,StringVector &v)
{
  return ! context.is_empty_intersection(wbize(another.context),v);
}

bool ConflictResolvingLeftArrowRule::resolvable_conflict
(const ConflictResolvingLeftArrowRule &another)
{ return context.is_subset(wbize(another.context)); }

void ConflictResolvingLeftArrowRule::resolve_conflict
(const ConflictResolvingLeftArrowRule &another)
{ context.apply(&HfstTransducer::subtract,another.context); }

#ifdef TEST_CONFLICT_RESOLVING_LEFT_ARROW_RULE
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

  // ?* a:?* <D> ?* <D> ?*
  context1.
    apply(&HfstTransducer::concatenate,a_sth).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown);

  OtherSymbolTransducerVector v1(1,context1);
  ConflictResolvingLeftArrowRule rule1("__TWOLC_RULE_NAME=\"test rule I\"",
                       SymbolPair("a","b"),v1);

  OtherSymbolTransducer a_b("a","b");
  OtherSymbolTransducer context2(unknown);
  context2.
    apply(&HfstTransducer::concatenate,a_b).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown);
  OtherSymbolTransducerVector v2(1,context2);
  ConflictResolvingLeftArrowRule rule2("__TWOLC_RULE_NAME=\"test rule II\"",
                       SymbolPair("a","b"),v2);
  
  StringVector v;
  //assert(rule1.conflicts_this(rule2,v));
  //assert(rule1.resolvable_conflict(rule2));
  //rule1.resolve_conflict(rule2);
  //std::cout << rule1.compile().get_transducer() << std::endl;
  //std::cout << rule2.compile().get_transducer() << std::endl;
}
#endif
