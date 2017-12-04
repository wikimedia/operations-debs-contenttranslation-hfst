//! @file Rule.h
//!
//! @brief Holds one two-level rule.
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

#ifndef RULE_H_
#define RULE_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string>
#include "HfstTransducer.h"
#include "OtherSymbolTransducer.h"
#include "grammar_defs.h"
#include "../string_src/string_manipulation.h"

using hfst::HfstOutputStream;

class Rule
{
 protected:
  bool is_empty;
  std::string name;
  OtherSymbolTransducer center;
  OtherSymbolTransducer context;
  OtherSymbolTransducer rule_transducer;

  void add_name(void);

 public:
  typedef std::vector<Rule*> RuleVector;

  //! @brief Construct a rule with @a name, @a center and @a contexts.
  Rule(const std::string &name,
       const OtherSymbolTransducer &center,
       const OtherSymbolTransducerVector &contexts);

  //! @brief Construct a rule which is equivalent to the intersection of the
  //! rules in @a v.
  Rule(const std::string &name,
       const RuleVector &v);

  //! @brief If conflict resolution incoreporates this rule in another rule
  //! @a empty return true and false otherwise.
  bool empty(void) const;
    
  //! @brief Prevents memory-leaks.
  virtual ~Rule(void);

  //! @brief Compile @a this.
  virtual OtherSymbolTransducer compile(void);

  //! @brief Store this transducer in @a out.
  void store(HfstOutputStream &out);

  //! @brief Get the name of this rule.
  std::string get_name(void);

  //! @brief Return <tt>?* DIAMOND ?* DIAMOND ?*</tt>.
  static OtherSymbolTransducer get_universal_language_with_diamonds(void);

  static OtherSymbolTransducer get_center(const std::string &input,
                      const std::string &output);

  static OtherSymbolTransducer get_center(const SymbolPairVector &v);

  static OtherSymbolTransducer get_center
    (const OtherSymbolTransducer &restricted_center);

  //! Replace "__HFST_TWOLC_SPACE" with " " and replace
  //! "__HFST_TWOLC_RULE_NAME=" with "".
  static std::string get_print_name(const std::string &s);

  //! Freely add symbols in @a diacritics, which do not occur in the alphabet
  //! of this rule.
  void add_missing_symbols_freely(const SymbolRange &diacritics);
  
};

#endif // RULE_H_
