//! @file hfst-fst2txt.cc
//!
//! @brief Transducer array printing command line tool
//!
//! @author HFST Team


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

#ifndef HEADER_FUNCTIONAL_TRANSDUCER_H
#define HEADER_FUNCTIONAL_TRANSDUCER_H

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <set>
#include <string>

typedef std::set<std::string> StringSet;

#include <hfst/HfstTransducer.h>

using hfst::implementations::HfstBasicTransducer;
using hfst::HfstTokenizer;
using hfst::implementations::HfstBasicTransition;
using hfst::StringVector;

#define EPSILON_SYMBOL "@_EPSILON_SYMBOL_@"
#define ZERO "0"

typedef std::set<HfstBasicTransition> TransitionSet;

class FunctionalTransducer
{
 public:
  FunctionalTransducer(const HfstBasicTransducer &);
  std::string apply_on_input(const std::string &) const;
  std::string apply_on_output(const std::string &) const;
  bool test_on_string_pair(const std::string &,const std::string &) const;
  bool test_on_pair_string(const std::string &,const std::string &) const;
  
  static void set_verbose_print(std::ostream &);
 protected:
  static std::ostream * verbose_out;
 
  const HfstBasicTransducer &fst;
  HfstTokenizer input_tokenizer;
  HfstTokenizer output_tokenizer;

  void collect_symbols_from_fst
    (StringSet &,StringSet &, const HfstBasicTransducer &) const;
  void define_multichar_symbols(const StringSet &,HfstTokenizer &);
  StringVector apply(const StringVector &,bool input) const;
  void follow_epsilon_transitions
    (StringVector::iterator it,StringVector::iterator end,
     HfstState,bool,StringStringVector &,StateSet &);
  void follow_transitions    
    (StringVector::iterator it,StringVector::iterator end,
     HfstState,bool,StringStringVector &);
  void join_and_uniquify(StringVectorVector &);

  static StringVector tokenize(const std::string &,const HfstTokenizer &);
  static void verbose_print(const std::string &);
  static std::string join(const StringVector &,const std::string &joiner=" ",
     bool replace_epsilons=false);
};

#endif // HEADER_FUNCTIONAL_TRANSUCER_H
