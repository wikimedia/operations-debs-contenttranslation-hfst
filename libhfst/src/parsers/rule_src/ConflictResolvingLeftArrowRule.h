//! @file ConflictResolvingLeftArrowRuleRule.h
//!
//! @brief Holds one <=-type twol rule, whose center is a single symbol pair.
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

#ifndef CONFLICT_RESOLVING_LEFT_ARROW_RULE_H_
#define CONFLICT_RESOLVING_LEFT_ARROW_RULE_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "LeftArrowRule.h"
#include "../string_src/string_manipulation.h"

class LeftArrowRuleContainer;

class ConflictResolvingLeftArrowRule : public LeftArrowRule
{
 protected:
  std::string input_symbol;
 public:
  //! @brief Inititalize.
  ConflictResolvingLeftArrowRule(const std::string &name,
                 const SymbolPair &center,
                 const OtherSymbolTransducerVector &contexts);

  //! @brief Return true if @a another conflicts @a this.
  //!
  //! Return true if the input symbols of the centers of @a another and
  //! @this are equal, the output symbols differ, and the contexts of @a
  //! another and @a this have a non-empty intersection.
  //!
  //! If a conflict exists, store the conflicting string in v.
  bool conflicts_this(const ConflictResolvingLeftArrowRule &another,
              StringVector &v);

  //! Return @a true, if the context of @a another is a sub language of
  //! the context of @a this.
  bool resolvable_conflict(const ConflictResolvingLeftArrowRule &another);

  //! @brief Resolve the conflict between @a this and @a another by subtracting
  //! the context of @a another fromt the @a context of @a this.
  void resolve_conflict(const ConflictResolvingLeftArrowRule &another);

  friend class LeftArrowRuleContainer;
};

#endif // CONFLICT_RESOLVING_LEFT_ARROW_RULE_H_
