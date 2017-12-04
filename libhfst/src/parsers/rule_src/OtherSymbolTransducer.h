//! @file OtherSymbolTransducer.h
//!
//! @brief Transducers with other-symbols.
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

#ifndef OTHER_SYMBOL_TRANSDUCER_H_
#define OTHER_SYMBOL_TRANSDUCER_H_

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "../../../../libhfst/src/HfstTransducer.h"
#include "HfstTwolcDefs.h"
#include "grammar_defs.h"
#include "../string_src/string_manipulation.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>

using hfst::HfstTransducer;
using hfst::ImplementationType;
using hfst::implementations::HfstState;
using hfst::implementations::HfstBasicTransducer;
using hfst::implementations::HfstBasicTransition;
using hfst::implementations::HfstState;
typedef std::set<HfstBasicTransition> HfstBasicTransitionSet;
typedef std::pair<HfstState,HfstState> StatePair;

class EmptySymbolPairSet
{};

class UndefinedSymbolPairsFound
{};

static const std::string TWOLC_IDENTITY = "@_TWOLC_IDENTITY_SYMBOL_@";
static const std::string HFST_IDENTITY = "@_IDENTITY_SYMBOL_@";
static const std::string HFST_UNKNOWN = "@_UNKNOWN_SYMBOL_@";
static const std::string HFST_EPSILON = "@_EPSILON_SYMBOL_@";
static const std::string TWOLC_UNKNOWN = "__HFST_TWOLC_?";
static const std::string TWOLC_DIAMOND = "__HFST_TWOLC_DIAMOND";
static const std::string TWOLC_EPSILON = "__HFST_TWOLC_0";
static const std::string TWOLC_FREELY_INSERT = "__HFST_TWOLC_FREELY_INSERT";

//! @brief Pointer to a member function of @a HfstTransducer taking zero
//! arguments.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerZeroArgMember) (void);

//! @brief Pointer to a member function of @a HfstTransducer taking one
//! argument.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerOneArgMember)
  (const HfstTransducer &);

//! @brief Pointer to a member function of @a HfstTransducer taking one
//! argument.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerBoolArgMember)
  (const HfstTransducer &, bool);

//! @brief Pointer to a member function of @a HfstTransducer taking one
//! argument and returning a boolean.
typedef bool (HfstTransducer::*HfstTransducerOneArgMemberBool)
  (const HfstTransducer &) const;

//! @brief Pointer to a member function of @a HfstTransducer taking one
//! unsigned int argument.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerOneNumArgMember)
  (unsigned int);

//! @brief Pointer to a member function of @a HfstTransducer taking two
//! unsigned int arguments.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerTwoNumArgMember)
  (unsigned int,unsigned int);

//! @brief Pointer to a member function of @a HfstTransducer taking one
//! const SymbolPair& argument.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerOneSymbolPairArgMember)
  (const SymbolPair &);

typedef HfstTransducer &(HfstTransducer::*HfstTransducerOneSymbolPairBoolArgMember)
  (const SymbolPair &, bool);

//! @brief Pointer to member function of @A HfstTransducer taking two
//! strings and two booleans as arguments.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerSubstMember)
  (const std::string&,const std::string &,bool,bool);

//! @brief Pointer to member function of @A HfstTransducer taking two
//! @a SymbolPairs as arguments.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerSubstPairMember)
  (const SymbolPair &,const SymbolPair &);

//! @brief Pointer to member function of @A HfstTransducer taking a
//! @a SymbolPair and an @a HfstTransducer as arguments.
typedef HfstTransducer &(HfstTransducer::*HfstTransducerSubstPairFstMember)
  (const SymbolPair &,HfstTransducer &,bool);

//! @brief For calling a pointer to a member function passed as argument.
#define CALL_MEMBER_FN(object,ptr_to_member) ((object).*(ptr_to_member))

class Rule;

class OtherSymbolTransducer
{
 protected:
  static HandySet<std::string> input_symbols;
  static HandySet<std::string> output_symbols;
  static HandySet<std::string> diacritics;
  static HandySet<SymbolPair>  symbol_pairs;
  static ImplementationType transducer_type;
  bool is_broken;
  HfstTransducer transducer;
  void check_pair(const std::string &input_symbol,
          const std::string &output_symbol);
  void add_diamond_transition(void);
  static bool empty(const HfstBasicTransducer &fsm);

 public:

  //! @brief Define the set of possible symbol-pairs.
  static void set_symbol_pairs(const HandySet<SymbolPair> &symbol_pairs);

  //! @brief Define the set of possible symbol-pairs.
  static void define_diacritics(const std::vector<std::string> &diacritics);

  //! @brief Set the type of transducer to be used
  static void set_transducer_type(ImplementationType transducer_type);

  //! @brief Construct empty transducer.
  OtherSymbolTransducer(void);

  //! @brief Construct transducer <i>input_symbol:output_symbol</i>.
  OtherSymbolTransducer(const std::string &input_symbol,
            const std::string &output_symbol);

  //! @brief Construct transducer <i>symbol:symbol</i>.
  OtherSymbolTransducer(const std::string &symbol);

  //! @brief Copy constructor.
  OtherSymbolTransducer(const OtherSymbolTransducer &another);

  //! @brief Set @a this equal to @another.
  OtherSymbolTransducer &operator=(const OtherSymbolTransducer &another);

  //! @brief Apply @a p onto @a this and minimize @a this.
  OtherSymbolTransducer &apply(HfstTransducerZeroArgMember p);

  //! @brief Apply @a p onto @a this taking @a another as argument and
  //! minimize @a this.
  //!
  //! Before applying @a p, harmonize the other-symbols in @a this and
  //! @a another.
  OtherSymbolTransducer
    &apply(const HfstTransducerOneArgMember,
       const OtherSymbolTransducer &another);

  OtherSymbolTransducer
    &apply(const HfstTransducerBoolArgMember,
       const OtherSymbolTransducer &another);

  //! @brief Call @a p of @a this taking @a another as argument.
  //!
  bool
    apply(const HfstTransducerOneArgMemberBool,
      const OtherSymbolTransducer &another) const;

  //! @brief Apply @a p onto @a this taking @a num as argument and
  //! minimize @a this.
  OtherSymbolTransducer
    &apply(const HfstTransducerOneNumArgMember,unsigned int number);

  //! @brief Apply @a p onto @a this taking @a num1 and @a num2 as arguments
  //! and minimize @a this.
  OtherSymbolTransducer
    &apply(const HfstTransducerTwoNumArgMember,unsigned int num1,
       unsigned int num2);

  //! @brief Apply @a p onto @a this taking @a pair as argument and
  //! minimize @a this.
  OtherSymbolTransducer
    &apply
    (const HfstTransducerOneSymbolPairArgMember,const SymbolPair &pair);

  OtherSymbolTransducer
    &apply
    (const HfstTransducerOneSymbolPairBoolArgMember,const SymbolPair &pair, bool b);

  //! @brief Apply @a p onto @a this taking @a str1, @a str2, @a b1 and @a b2
  //! as arguments and minimize @a this.
  OtherSymbolTransducer
    &apply(const HfstTransducerSubstMember p,const std::string &str1,
       const std::string &str2, bool b1, bool b2);

  //! @brief Apply @a p onto @a this taking @a p1 and @a p2 as arguments and
  //! minimize @a this.
  OtherSymbolTransducer
    &apply(const HfstTransducerSubstPairMember p,const SymbolPair &p1,
       const SymbolPair &p2);

  //! @brief Apply @a p onto @a this taking @a p1 and @a p2 as arguments and
  //! minimize @a this.
  OtherSymbolTransducer
    &apply(const HfstTransducerSubstPairFstMember p,const SymbolPair &p1,
           const OtherSymbolTransducer &t, bool b);


  //! @brief Add one transition from the start state of @a this to a new state
  //! with input and output symbol equal to @a info_symbol.
  OtherSymbolTransducer &add_info_symbol(const std::string &info_symbol);

  //! Add a transition to @a center_t (badly placed...).
  static void add_transition
    (HfstBasicTransducer &center_t, size_t source_state,size_t target_state,
     const std::string &input, const std::string &output);

  //! Return true, iff @a sym exists in the alphabet of @a t.
  static bool has_symbol(const HfstBasicTransducer &t,const std::string &sym);

  OtherSymbolTransducer &harmonize_diacritics(OtherSymbolTransducer &t);
    
  //! @brief Set the state @a state final.
  static void set_final(HfstBasicTransducer &center_t,size_t state);

  //! @brief Return true, iff the intersection of @a this and @a another is
  //! empty. If it is non-empty, store the first common string found in v.
  bool is_empty_intersection(const OtherSymbolTransducer &another,
                 StringVector &);

  //! @brief Return true, iff @a another is a subset of the @a this.
  bool is_subset(const OtherSymbolTransducer &another);

  //! @brief Return a copy where all output symbols are replaced
  //! by other-symbols.
  OtherSymbolTransducer get_inverse_of_upper_projection(void);

  //! @brief Perform the effect of <tt>?* X ?*</tt> where <tt>X</tt> is
  //! @a this.
  OtherSymbolTransducer &contained(void);

  //! @brief Perform the effect of <tt>?* X ?* - ?* X ?* X ?* </tt> where
  //! <tt>X</tt> is @a this.
  OtherSymbolTransducer &contained_once(void);

  //! @brief Perform the equivalent of <tt>?* - X</tt> where <tt>X</tt> is
  //! @a this.
  OtherSymbolTransducer &negated(void);

  //! @brief Perform the equivalent of <tt>? - X</tt> where <tt>X</tt> is
  //! @a this.
  OtherSymbolTransducer &term_complemented(void);

  //! @brief Return a rule context <tt>X D ?* D Y</tt> where <tt>X</tt> is the
  //! left context, <tt>Y</tt> is the right context, <tt>D</tt> is the
  //! diamond symbol <tt>__HFST_TWOLC_DIAMOND</tt>.
  static OtherSymbolTransducer get_context(OtherSymbolTransducer &left,
                       OtherSymbolTransducer &right);
  
  //! @brief Get a transducer recogninzing any pair.
  static OtherSymbolTransducer get_universal(void);

  //! @brief Add @a symbol to the alphabet of @a this. Prevents harmonization
  //! of the symbol.
  void add_symbol_to_alphabet(const std::string &symbol);

  //! @brief Replace diacritics from output-side.
  void remove_diacritics_from_output(void);

  HfstTransducer get_transducer(void) const;

  //! @brief Return the symbol pairs in the transitions from the start state.
  void get_initial_transition_pairs(SymbolPairVector &pair_container) const;

  //! @brief Return true if this is empty and false otherwise.
  bool is_empty(void) const;

  friend class Rule;

  friend std::ostream &operator<<(std::ostream &,
                  const OtherSymbolTransducer &);
};

//! @brief Container for OtherSymbolTransducers.
typedef std::vector<OtherSymbolTransducer> OtherSymbolTransducerVector;

//! @brief Container for named regular expressions represented as
//! @a OtherSymbolTransducer objects.
typedef std::map<std::string,OtherSymbolTransducer> NameToRegexMap;

//! @brief Display an @a OtherSymbolTransducer
std::ostream &operator<<(std::ostream &,const OtherSymbolTransducer &);

#endif // OTHER_SYMBOL_TRANSDUCER_H_
