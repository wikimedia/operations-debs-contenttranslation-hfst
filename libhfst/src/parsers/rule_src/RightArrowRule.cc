//! @file RightArrowRule.cc
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

#include "RightArrowRule.h"

RightArrowRule::RightArrowRule
(const std::string &name,
 const OtherSymbolTransducer &center,
 const OtherSymbolTransducerVector &contexts):
  Rule(name,center,contexts)
{}

OtherSymbolTransducer RightArrowRule::compile(void)
{
  center.
    apply(&HfstTransducer::subtract,context).
    apply(&HfstTransducer::substitute,TWOLC_DIAMOND,HFST_EPSILON,true,true);
  rule_transducer = OtherSymbolTransducer(TWOLC_UNKNOWN);
  rule_transducer.
    apply(&HfstTransducer::repeat_star).
    apply(&HfstTransducer::subtract,center);
  return rule_transducer;
}

#ifdef TEST_RIGHT_ARROW_RULE
#include <cassert>

int main(void)
{
  bool have_openfst = false;
#if HAVE_OPENFST
  have_openfst = true;
#endif // HAVE_OPENFST

  bool have_sfst = false;
#if HAVE_SFST
  have_sfst = true;
#endif // HAVE_SFST

  bool have_foma = false;
#if HAVE_FOMA
  have_foma = true;
#endif // HAVE_FOMA

ImplementationType transducer_type
= have_openfst ? hfst::TROPICAL_OPENFST_TYPE :
  have_sfst ? hfst::SFST_TYPE :
  have_foma ? hfst::FOMA_TYPE :
  hfst::ERROR_TYPE;

 OtherSymbolTransducer::set_transducer_type(transducer_type);

  HandySet<SymbolPair> symbols;
  symbols.insert(SymbolPair("a","b"));
  symbols.insert(SymbolPair("a","d"));
  symbols.insert(SymbolPair("b","c"));
  OtherSymbolTransducer::set_symbol_pairs(symbols);
  OtherSymbolTransducer unknown("__HFST_TWOLC_?","__HFST_TWOLC_?");
  unknown.apply(&HfstTransducer::repeat_star);
  OtherSymbolTransducer diamond("__HFST_TWOLC_DIAMOND");
  OtherSymbolTransducer a_b_pair("a","b");
  OtherSymbolTransducer center(unknown);
  center.
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,a_b_pair).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown);
  OtherSymbolTransducer b_c_pair("b","c");
  OtherSymbolTransducer context = unknown;
  context.
    apply(&HfstTransducer::concatenate,b_c_pair).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown).
    apply(&HfstTransducer::concatenate,diamond).
    apply(&HfstTransducer::concatenate,unknown);
  OtherSymbolTransducerVector contexts(1,context);
  RightArrowRule rule("__HFST_TWOLC_RULE_NAME=\"Test rule\"",
             center,contexts);
  OtherSymbolTransducer compiled_rule = rule.compile();
  //std::cout << compiled_rule.get_transducer() << std::endl;
}
#endif // TEST_RIGHT_ARROW_RULE
