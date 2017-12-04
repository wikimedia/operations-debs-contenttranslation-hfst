// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

// This is a swig interface file that is used to create python bindings for HFST.
// Everything will be visible under module 'libhfst', but will be wrapped under
// package 'hfst' and its subpackages 'hfst.exceptions' and 'hfst.rules' (see
// folder 'hfst' in the current directory).

%module libhfst
// Needed for type conversions between c++ and python.
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "std_set.i"
%include "std_map.i"
%include "exception.i"

// %feature("autodoc", "3");

// We want warnings to be printed to standard error.
%init %{
    hfst::set_warning_stream(&std::cerr);
%}

// Make swig aware of what hfst offers.
%{
#define HFSTIMPORT
#include "HfstDataTypes.h"
#include "HfstTransducer.h"
#include "HfstOutputStream.h"
#include "HfstInputStream.h"
#include "HfstExceptionDefs.h"
#include "HfstTokenizer.h"
#include "HfstFlagDiacritics.h"
#include "HfstXeroxRules.h"
#include "parsers/XreCompiler.h"
#include "parsers/LexcCompiler.h"
#include "parsers/XfstCompiler.h"
#include "parsers/SfstCompiler.h"
#include "implementations/HfstBasicTransition.h"
#include "implementations/HfstBasicTransducer.h"
#include "implementations/optimized-lookup/pmatch.h"
#include "parsers/TwolcCompiler.h"
namespace hfst { typedef std::vector<hfst::xeroxRules::Rule> HfstRuleVector; }

// Most of C++ extension code is located in separate files.
#include "hfst_regex_extensions.cpp"
#include "hfst_extensions.cpp"
#include "hfst_lexc_extensions.cpp"
#include "hfst_xfst_extensions.cpp"
#include "hfst_pmatch_extensions.cpp"
#include "hfst_sfst_extensions.cpp"
#include "hfst_lookup_extensions.cpp"
#include "hfst_rules_extensions.cpp"
#include "hfst_prolog_extensions.cpp"
%}

#ifdef _MSC_VER
%include <windows.h>
#endif

// Templates needed for conversion between c++ and python datatypes.
//
// Note that templating order matters; simple templates used as part of
// more complex templates must be defined first, e.g. StringPair must be
// defined before StringPairSet. Also templates that are not used as such
// but are used as part of other templates must be defined.

%include "typemaps.i"

namespace std {
%template(StringVector) vector<string>;
%template(StringPair) pair<string, string>;
%template(StringPairVector) vector<pair<string, string > >;
%template(FloatVector) vector<float>;
%template(StringSet) set<string>;
%template(StringPairSet) set<pair<string, string> >;
%template(HfstTransducerVector) vector<hfst::HfstTransducer>;
%template(HfstSymbolSubstitutions) map<string, string>;
%template(HfstSymbolPairSubstitutions) map<pair<string, string>, pair<string, string> >;
// needed for HfstBasicTransducer.states()
%template(BarBazFoo) vector<unsigned int>;
%template(HfstBasicTransitions) vector<hfst::implementations::HfstBasicTransition>;
%template(HfstOneLevelPath) pair<float, vector<string> >;
%template(HfstOneLevelPaths) set<pair<float, vector<string> > >;
%template(HfstTwoLevelPath) pair<float, vector<pair<string, string > > >;
%template(HfstTwoLevelPaths) set<pair<float, vector<pair<string, string > > > >;
%template(HfstTransducerPair) pair<hfst::HfstTransducer, hfst::HfstTransducer>;
%template(HfstTransducerPairVector) vector<pair<hfst::HfstTransducer, hfst::HfstTransducer> >;
%template(HfstRuleVector) vector<hfst::xeroxRules::Rule>;
}


%include "docstrings.i"

// ****************************************************** //
// ********** WHAT IS MADE AVAILABLE ON PYTHON ********** //
// ****************************************************** //

// *** HfstException and its subclasses (will be wrapped under module hfst.exceptions). *** //

class HfstException
{
  public:
    HfstException();
    HfstException(const std::string&, const std::string&, size_t);
    ~HfstException();
    std::string what() const;
};

class HfstTransducerTypeMismatchException : public HfstException { public: HfstTransducerTypeMismatchException(const std::string&, const std::string&, size_t); ~HfstTransducerTypeMismatchException(); std::string what() const; };
class ImplementationTypeNotAvailableException : public HfstException { public: ImplementationTypeNotAvailableException(const std::string&, const std::string&, size_t, hfst::ImplementationType type); ~ImplementationTypeNotAvailableException(); std::string what() const; hfst::ImplementationType get_type() const; };
class FunctionNotImplementedException : public HfstException { public: FunctionNotImplementedException(const std::string&, const std::string&, size_t); ~FunctionNotImplementedException(); std::string what() const; };
class StreamNotReadableException : public HfstException { public: StreamNotReadableException(const std::string&, const std::string&, size_t); ~StreamNotReadableException(); std::string what() const; };
class StreamCannotBeWrittenException : public HfstException { public: StreamCannotBeWrittenException(const std::string&, const std::string&, size_t); ~StreamCannotBeWrittenException(); std::string what() const; };
class StreamIsClosedException : public HfstException { public: StreamIsClosedException(const std::string&, const std::string&, size_t); ~StreamIsClosedException(); std::string what() const; };
class EndOfStreamException : public HfstException { public: EndOfStreamException(const std::string&, const std::string&, size_t); ~EndOfStreamException(); std::string what() const; };
class TransducerIsCyclicException : public HfstException { public: TransducerIsCyclicException(const std::string&, const std::string&, size_t); ~TransducerIsCyclicException(); std::string what() const; };
class NotTransducerStreamException : public HfstException { public: NotTransducerStreamException(const std::string&, const std::string&, size_t); ~NotTransducerStreamException(); std::string what() const; };
class NotValidAttFormatException : public HfstException { public: NotValidAttFormatException(const std::string&, const std::string&, size_t); ~NotValidAttFormatException(); std::string what() const; };
class NotValidPrologFormatException : public HfstException { public: NotValidPrologFormatException(const std::string&, const std::string&, size_t); ~NotValidPrologFormatException(); std::string what() const; };
class NotValidLexcFormatException : public HfstException { public: NotValidLexcFormatException(const std::string&, const std::string&, size_t); ~NotValidLexcFormatException(); std::string what() const; };
class StateIsNotFinalException : public HfstException { public: StateIsNotFinalException(const std::string&, const std::string&, size_t); ~StateIsNotFinalException(); std::string what() const; };
class ContextTransducersAreNotAutomataException : public HfstException { public: ContextTransducersAreNotAutomataException(const std::string&, const std::string&, size_t); ~ContextTransducersAreNotAutomataException(); std::string what() const; };
class TransducersAreNotAutomataException : public HfstException { public: TransducersAreNotAutomataException(const std::string&, const std::string&, size_t); ~TransducersAreNotAutomataException(); std::string what() const; };
class StateIndexOutOfBoundsException : public HfstException { public: StateIndexOutOfBoundsException(const std::string&, const std::string&, size_t); ~StateIndexOutOfBoundsException(); std::string what() const; };
class TransducerHeaderException : public HfstException { public: TransducerHeaderException(const std::string&, const std::string&, size_t); ~TransducerHeaderException(); std::string what() const; };
class MissingOpenFstInputSymbolTableException : public HfstException { public: MissingOpenFstInputSymbolTableException(const std::string&, const std::string&, size_t); ~MissingOpenFstInputSymbolTableException(); std::string what() const; };
class TransducerTypeMismatchException : public HfstException { public: TransducerTypeMismatchException(const std::string&, const std::string&, size_t); ~TransducerTypeMismatchException(); std::string what() const; };
class EmptySetOfContextsException : public HfstException { public: EmptySetOfContextsException(const std::string&, const std::string&, size_t); ~EmptySetOfContextsException(); std::string what() const; };
class SpecifiedTypeRequiredException : public HfstException { public: SpecifiedTypeRequiredException(const std::string&, const std::string&, size_t); ~SpecifiedTypeRequiredException(); std::string what() const; };
class HfstFatalException : public HfstException { public: HfstFatalException(const std::string&, const std::string&, size_t); ~HfstFatalException(); std::string what() const; };
class TransducerHasWrongTypeException : public HfstException { public: TransducerHasWrongTypeException(const std::string&, const std::string&, size_t); ~TransducerHasWrongTypeException(); std::string what() const; };
class IncorrectUtf8CodingException : public HfstException { public: IncorrectUtf8CodingException(const std::string&, const std::string&, size_t); ~IncorrectUtf8CodingException(); std::string what() const; };
class EmptyStringException : public HfstException { public: EmptyStringException(const std::string&, const std::string&, size_t); ~EmptyStringException(); std::string what() const; };
class SymbolNotFoundException : public HfstException { public: SymbolNotFoundException(const std::string&, const std::string&, size_t); ~SymbolNotFoundException(); std::string what() const; };
class MetadataException : public HfstException { public: MetadataException(const std::string&, const std::string&, size_t); ~MetadataException(); std::string what() const; };
class FlagDiacriticsAreNotIdentitiesException : public HfstException { public: FlagDiacriticsAreNotIdentitiesException(const std::string&, const std::string&, size_t); ~FlagDiacriticsAreNotIdentitiesException(); std::string what() const; };

namespace hfst
{

// Needed for conversion between c++ and python datatypes.

typedef std::vector<std::string> StringVector;
typedef std::pair<std::string, std::string> StringPair;
typedef std::vector<std::pair<std::string, std::string> > StringPairVector;
typedef std::vector<float> FloatVector;
typedef std::set<std::string> StringSet;
typedef std::set<std::pair<std::string, std::string> > StringPairSet;
typedef std::pair<float, std::vector<std::string> > HfstOneLevelPath;
typedef std::set<std::pair<float, std::vector<std::string> > > HfstOneLevelPaths;
typedef std::pair<float, std::vector<std::pair<std::string, std::string > > > HfstTwoLevelPath;
typedef std::set<std::pair<float, std::vector<std::pair<std::string, std::string> > > > HfstTwoLevelPaths;
typedef std::map<std::string, std::string> HfstSymbolSubstitutions;
typedef std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string> > HfstSymbolPairSubstitutions;
typedef std::vector<hfst::HfstTransducer> HfstTransducerVector;
typedef std::pair<hfst::HfstTransducer, hfst::HfstTransducer> HfstTransducerPair;
typedef std::vector<std::pair<hfst::HfstTransducer, hfst::HfstTransducer> > HfstTransducerPairVector;
typedef std::vector<hfst::xeroxRules::Rule> HfstRuleVector;

// *** Some enumerations *** //

enum ImplementationType
{ SFST_TYPE, TROPICAL_OPENFST_TYPE, LOG_OPENFST_TYPE, FOMA_TYPE,
  XFSM_TYPE, HFST_OL_TYPE, HFST_OLW_TYPE, HFST2_TYPE,
  UNSPECIFIED_TYPE, ERROR_TYPE };

  namespace xeroxRules
  {
    enum ReplaceType {REPL_UP, REPL_DOWN, REPL_RIGHT, REPL_LEFT};

    class Rule
    {
    public:
      Rule();
      Rule(const hfst::HfstTransducerPairVector&);
      Rule(const hfst::HfstTransducerPairVector&, const hfst::HfstTransducerPairVector&, ReplaceType);
      Rule(const Rule&);
      hfst::HfstTransducerPairVector get_mapping() const;
      hfst::HfstTransducerPairVector get_context() const;
      ReplaceType get_replType() const;
      void encodeFlags();
      // friend std::ostream& operator<<(std::ostream &out, const Rule &r);
    };

    // replace up, left, right, down
    hfst::HfstTransducer replace(const Rule &rule, bool optional);
    // for parallel rules
    hfst::HfstTransducer replace(const HfstRuleVector &ruleVector, bool optional);
    // replace up, left, right, down
%rename("xerox_replace_left") replace_left(const Rule &rule, bool optional);
    hfst::HfstTransducer replace_left(const Rule &rule, bool optional);
    // for parallel rules
%rename("xerox_replace_left") replace_left(const HfstRuleVector &ruleVector, bool optional);
    hfst::HfstTransducer replace_left(const HfstRuleVector &ruleVector, bool optional);
    // left to right
    hfst::HfstTransducer replace_leftmost_longest_match(const Rule &rule);
    // left to right
    hfst::HfstTransducer replace_leftmost_longest_match(const HfstRuleVector &ruleVector);
    // right to left
    hfst::HfstTransducer replace_rightmost_longest_match(const Rule &rule);

    // right to left
    hfst::HfstTransducer replace_rightmost_longest_match(const HfstRuleVector &ruleVector);

    hfst::HfstTransducer replace_leftmost_shortest_match(const Rule &rule);

    hfst::HfstTransducer replace_leftmost_shortest_match(const HfstRuleVector &ruleVector);
    hfst::HfstTransducer replace_rightmost_shortest_match(const Rule &rule);
    hfst::HfstTransducer replace_rightmost_shortest_match(const HfstRuleVector &ruleVector);

    // replace up, left, right, down
    hfst::HfstTransducer replace_epenthesis(const Rule &rule, bool optional);
    // replace up, left, right, down
    hfst::HfstTransducer replace_epenthesis(const HfstRuleVector &ruleVector, bool optional);

    // Restriction function "=>"
%rename("xerox_restriction") restriction(const hfst::HfstTransducer &automata, const hfst::HfstTransducerPairVector &context);
    hfst::HfstTransducer restriction(const hfst::HfstTransducer &automata, const hfst::HfstTransducerPairVector &context);
    hfst::HfstTransducer before(const hfst::HfstTransducer &left, const hfst::HfstTransducer &right);
    hfst::HfstTransducer after(const hfst::HfstTransducer &left, const hfst::HfstTransducer &right);

  }

// *** Some other functions *** //

bool is_diacritic(const std::string & symbol);
hfst::HfstTransducerVector compile_pmatch_expression(const std::string & pmatch) throw(HfstException);

// internal functions
%pythoncode %{
  def _is_string(s):
      if isinstance(s, str):
         return True
      else:
        return False
  def _is_string_pair(sp):
      if not isinstance(sp, tuple):
         return False
      if len(sp) != 2:
         return False
      if not _is_string(sp[0]):
         return False
      if not _is_string(sp[1]):
         return False
      return True
  def _is_string_vector(sv):
      if not isinstance(sv, tuple):
         return False
      for s in sv:
          if not _is_string(s):
             return False
      return True
  def _is_string_pair_vector(spv):
      if not isinstance(spv, tuple):
         return False
      for sp in spv:
          if not _is_string_pair(sp):
             return False
      return True

  def _two_level_paths_to_dict(tlps):
      retval = {}
      for tlp in tlps:
          input = ""
          output = ""
          for sp in tlp[1]:
              input += sp[0]
              output += sp[1]
          if input in retval:
              retval[input].append((output, tlp[0]))
          else:
              retval[input] = [(output, tlp[0])]
      return retval

  def _one_level_paths_to_tuple(olps):
      retval = []
      for olp in olps:
          path = ""
          for s in olp[1]:
              path += s
          retval.append((path, olp[0]))
      return tuple(retval)
%}

// *** HfstTransducer *** //

// NOTE: all functions returning an HfstTransducer& are commented out and extended
// by replacing them with equivalent functions that return void. This is done in
// order to avoid use of references that are not handled well by swig/python.
// Some constructors and the destructor are also redefined.

class HfstTransducer
{
public:
  void set_name(const std::string &name);
  std::string get_name() const;
  hfst::ImplementationType get_type() const;
  void set_property(const std::string& property, const std::string& value);
  std::string get_property(const std::string& property) const;
  const std::map<std::string,std::string>& get_properties() const;
  bool compare(const HfstTransducer&, bool harmonize=true) const throw(TransducerTypeMismatchException);
  unsigned int number_of_states() const;
  unsigned int number_of_arcs() const;
  StringSet get_alphabet() const;
  bool is_cyclic() const;
  bool is_automaton() const;
  bool is_infinitely_ambiguous() const;
  bool is_lookup_infinitely_ambiguous(const std::string &) const;
  bool has_flag_diacritics() const;
  void insert_to_alphabet(const std::string &);
  void remove_from_alphabet(const std::string &);
  static bool is_implementation_type_available(hfst::ImplementationType type);
  int longest_path_size(bool obey_flags=true) const;

%extend {

  // First versions of all functions returning an HfstTransducer& that return void instead:

  void concatenate(const HfstTransducer& tr, bool harmonize=true) throw(TransducerTypeMismatchException) { self->concatenate(tr, harmonize); }
  void disjunct(const HfstTransducer& tr, bool harmonize=true) throw(TransducerTypeMismatchException) { self->disjunct(tr, harmonize); }
  void subtract(const HfstTransducer& tr, bool harmonize=true) throw(TransducerTypeMismatchException) { self->subtract(tr, harmonize); }
  void intersect(const HfstTransducer& tr, bool harmonize=true) throw(TransducerTypeMismatchException) { self->intersect(tr, harmonize); }
  void compose(const HfstTransducer& tr, bool harmonize=true) throw(TransducerTypeMismatchException) { self->compose(tr, harmonize); }
  void compose_intersect(const HfstTransducerVector &v, bool invert=false, bool harmonize=true) { self->compose_intersect(v, invert, harmonize); }
  void priority_union(const HfstTransducer &another) { self->priority_union(another); }
  void lenient_composition(const HfstTransducer &another, bool harmonize=true) { self->lenient_composition(another, harmonize); }
  void cross_product(const HfstTransducer &another, bool harmonize=true) throw(TransducersAreNotAutomataException) { self->cross_product(another, harmonize); }
  void shuffle(const HfstTransducer &another, bool harmonize=true) { self->shuffle(another, harmonize); }
  void remove_epsilons() { self->remove_epsilons(); }
  void determinize() { self->determinize(); }
  void minimize() { self->minimize(); }
  void prune() { self->prune(); }
  void eliminate_flags() { self->eliminate_flags(); }
  void eliminate_flag(const std::string& f) throw(HfstException) { self->eliminate_flag(f); }
  void n_best(unsigned int n) { self->n_best(n); }
  void convert(ImplementationType impl) { self->convert(impl); }
  void repeat_star() { self->repeat_star(); }
  void repeat_plus() { self->repeat_plus(); }
  void repeat_n(unsigned int n) { self->repeat_n(n); }
  void repeat_n_to_k(unsigned int n, unsigned int k) { self->repeat_n_to_k(n, k); }
  void repeat_n_minus(unsigned int n) { self->repeat_n_minus(n); }
  void repeat_n_plus(unsigned int n) { self->repeat_n_plus(n); }
  void invert() { self->invert(); }
  void reverse() { self->reverse(); }
  void input_project() { self->input_project(); }
  void output_project() { self->output_project(); }
  void optionalize() { self->optionalize(); }
  void insert_freely(const StringPair &symbol_pair, bool harmonize=true) { self->insert_freely(symbol_pair, harmonize); }
  void insert_freely(const HfstTransducer &tr, bool harmonize=true) { self->insert_freely(tr, harmonize); }
  void _substitute_symbol(const std::string &old_symbol, const std::string &new_symbol, bool input_side=true, bool output_side=true) { self->substitute_symbol(old_symbol, new_symbol, input_side, output_side); }
  void _substitute_symbol_pair(const StringPair &old_symbol_pair, const StringPair &new_symbol_pair) { self->substitute_symbol_pair(old_symbol_pair, new_symbol_pair); }
  void _substitute_symbol_pair_with_set(const StringPair &old_symbol_pair, const hfst::StringPairSet &new_symbol_pair_set) { self->substitute_symbol_pair_with_set(old_symbol_pair, new_symbol_pair_set); }
  void _substitute_symbol_pair_with_transducer(const StringPair &symbol_pair, HfstTransducer &transducer, bool harmonize=true) { self->substitute_symbol_pair_with_transducer(symbol_pair, transducer, harmonize); }
  void _substitute_symbols(const hfst::HfstSymbolSubstitutions &substitutions) { self->substitute_symbols(substitutions); } // alias for the previous function which is shadowed
  void _substitute_symbol_pairs(const hfst::HfstSymbolPairSubstitutions &substitutions) { self->substitute_symbol_pairs(substitutions); } // alias for the previous function which is shadowed
  void set_final_weights(float weight, bool increment=false) { self->set_final_weights(weight, increment); };

  void push_weights_to_start() { self->push_weights(hfst::TO_INITIAL_STATE); };
  void push_weights_to_end() { self->push_weights(hfst::TO_FINAL_STATE); };

  // And some aliases:
  // 'union' is a reserved word in python, so it cannot be used as an alias for function 'disjunct'
  void minus(const HfstTransducer& t, bool harmonize=true) { $self->subtract(t, harmonize); }
  void conjunct(const HfstTransducer& t, bool harmonize=true) { $self->intersect(t, harmonize); }

  // Then the actual extensions:

  void lookup_optimize() { self->convert(hfst::HFST_OLW_TYPE); }
  void remove_optimization() { self->convert(hfst::get_default_fst_type()); }

    HfstTransducer() { return hfst::empty_transducer(); }
    HfstTransducer(const hfst::HfstTransducer & t) { return hfst::copy_hfst_transducer(t); }
    HfstTransducer(const hfst::implementations::HfstBasicTransducer & t) { return hfst::copy_hfst_transducer_from_basic_transducer(t); }
    HfstTransducer(const hfst::implementations::HfstBasicTransducer & t, hfst::ImplementationType impl) { return hfst::copy_hfst_transducer_from_basic_transducer(t, impl); }
    ~HfstTransducer()
    {
        if ($self->get_type() == hfst::UNSPECIFIED_TYPE || $self->get_type() == hfst::ERROR_TYPE)
        {
            return;
        }
        delete $self;
    }
    // For python's 'print'
    char *__str__() {
         std::ostringstream oss;
         hfst::implementations::HfstBasicTransducer fsm(*$self);
         fsm.write_in_att_format(oss,true);
         return strdup(oss.str().c_str());
    }
    void write(hfst::HfstOutputStream & os) { (void) os.redirect(*$self); }

    hfst::HfstTwoLevelPaths _extract_shortest_paths()
    {
        hfst::HfstTwoLevelPaths results;
        $self->extract_shortest_paths(results);
        return results;
    }
    hfst::HfstTwoLevelPaths _extract_longest_paths(bool obey_flags)
    {
        hfst::HfstTwoLevelPaths results;
        $self->extract_longest_paths(results, obey_flags);
        return results;
    }
    hfst::HfstTwoLevelPaths _extract_paths(int max_num=-1, int cycles=-1) const throw(TransducerIsCyclicException)
    {
      hfst::HfstTwoLevelPaths results;
      $self->extract_paths(results, max_num, cycles);
      return results;
    }
    hfst::HfstTwoLevelPaths _extract_paths_fd(int max_num=-1, int cycles=-1, bool filter_fd=true) const throw(TransducerIsCyclicException)
    {
      hfst::HfstTwoLevelPaths results;
      $self->extract_paths_fd(results, max_num, cycles, filter_fd);
      return results;
    }
    hfst::HfstTwoLevelPaths _extract_random_paths(int max_num) const
    {
      hfst::HfstTwoLevelPaths results;
      $self->extract_random_paths(results, max_num);
      return results;
    }
    hfst::HfstTwoLevelPaths _extract_random_paths_fd(int max_num, bool filter_fd) const
    {
      hfst::HfstTwoLevelPaths results;
      $self->extract_random_paths_fd(results, max_num, filter_fd);
      return results;
    }

    HfstOneLevelPaths _lookup_vector(const StringVector& s, int limit = -1, double time_cutoff = 0.0) const throw(FunctionNotImplementedException)
    {
      return hfst::lookup_vector($self, false /*fd*/, s, limit, time_cutoff);
    }
    HfstOneLevelPaths _lookup_fd_vector(const StringVector& s, int limit = -1, double time_cutoff = 0.0) const throw(FunctionNotImplementedException)
    {
      return hfst::lookup_vector($self, true /*fd*/, s, limit, time_cutoff);
    }
    HfstOneLevelPaths _lookup_fd_string(const std::string& s, int limit = -1, double time_cutoff = 0.0) const throw(FunctionNotImplementedException)
    {
      return hfst::lookup_string($self, true /*fd*/, s, limit, time_cutoff);
    }
    HfstOneLevelPaths _lookup_string(const std::string & s, int limit = -1, double time_cutoff = 0.0) const throw(FunctionNotImplementedException)
    {
      return hfst::lookup_string($self, false /*fd*/, s, limit, time_cutoff);
    }

%pythoncode %{

  def copy(self):
      """
      Return a deep copy of the transducer.
      """
      return HfstTransducer(self)

  def write_to_file(self, filename_):
      """
      Write the transducer in binary format to file *filename_*.
      """
      ostr = HfstOutputStream(filename=filename_, type=self.get_type(), hfst_format=True)
      ostr.write(self)
      ostr.close()

  def read_from_file(filename_):
      """
      Read a binary transducer from file *filename_*.
      """
      istr = HfstInputStream(filename_)
      tr = istr.read()
      istr.close()
      return tr

  def write_prolog(self, f, write_weights=True):
      """
      Write the transducer in prolog format with name *name* to file *f*,
      *write_weights* defined whether weights are written.

      Parameters
      ----------
      * `f` :
          A python file where the transducer is written.
      * `write_weights` :
          Whether weights are written.
      """
      fsm = HfstBasicTransducer(self)
      fsm.name = self.get_name()
      prologstr = fsm.get_prolog_string(write_weights)
      f.write(prologstr)

  def write_xfst(self, f, write_weights=True):
      """
      Write the transducer in xfst format to file *f*, *write_weights* defined whether
      weights are written.

      Parameters
      ----------
      * `f` :
          A python file where transducer is written.
      * `write_weights` :
          Whether weights are written.
      """
      fsm = HfstBasicTransducer(self)
      fsm.name = self.get_name()
      xfststr = fsm.get_xfst_string(write_weights)
      f.write(xfst)

  def write_att(self, f, write_weights=True):
      """
      Write the transducer in AT&T format to file *f*, *write_weights* defined whether
      weights are written.

      Parameters
      ----------
      * `f` :
          A python file where transducer is written.
      * `write_weights` :
          Whether weights are written.
      """
      fsm = HfstBasicTransducer(self)
      fsm.name = self.get_name()
      attstr = fsm.get_att_string(write_weights)
      f.write(attstr)

  def lookup(self, input, **kvargs):
      """
      Lookup string *input*.

      Parameters
      ----------
      * `input` :
          The input. A string or a pre-tokenized tuple of symbols (i.e. a tuple of strings).
      * `kvargs` :
          Possible parameters and their default values are: obey_flags=True,
          max_number=-1, time_cutoff=0.0, output='tuple'
      * `obey_flags` :
          Whether flag diacritics are obeyed. Always True for HFST_OL(W)_TYPE transducers.
      * `max_number` :
          Maximum number of results returned, defaults to -1, i.e. infinity.
      * `time_cutoff` :
          How long the function can search for results before returning, expressed in
          seconds. Defaults to 0.0, i.e. infinitely. Always 0.0 for transducers that are
          not of HFST_OL(W)_TYPE.
      * `output` :
          Possible values are 'tuple', 'text' and 'raw', 'tuple' being the default.

      Note: This function has an efficient implementation only for optimized lookup format
      (hfst.ImplementationType.HFST_OL_TYPE or hfst.ImplementationType.HFST_OLW_TYPE). Other formats perform the
      lookup via composition. Consider converting the transducer to optimized lookup format
      or to a HfstBasicTransducer. Conversion to HFST_OL(W)_TYPE might take a while but the
      lookup is fast. Conversion to HfstBasicTransducer is quick but lookup is slower.
      """
      obey_flags=True
      max_number=-1
      time_cutoff=0.0
      output='tuple' # 'tuple' (default), 'text', 'raw'

      for k,v in kvargs.items():
          if k == 'obey_flags':
             if v == 'True':
                pass
             elif v == 'False':
                obey_flags=False
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'True' and 'False'.")
          elif k == 'output':
             if v == 'text':
                output='text'
             elif v == 'raw':
                output='raw'
             elif v == 'tuple':
                output='tuple'
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'tuple' (default), 'text', 'raw'.")
          elif k == 'max_number' :
             max_number=v
          elif k == 'time_cutoff' :
             time_cutoff=v
          else:
             print('Warning: ignoring unknown argument %s.' % (k))

      retval=0

      if isinstance(input, tuple):
         if obey_flags:
            retval=self._lookup_fd_vector(input, max_number, time_cutoff)
         else:
            retval=self._lookup_vector(input, max_number, time_cutoff)
      elif isinstance(input, str):
         if obey_flags:
            retval=self._lookup_fd_string(input, max_number, time_cutoff)
         else:
            retval=self._lookup_string(input, max_number, time_cutoff)
      else:
         try:
            if obey_flags:
                retval=self._lookup_fd_string(str(input), max_number, time_cutoff)
            else:
                retval=self._lookup_string(str(input), max_number, time_cutoff)
         except:
            raise RuntimeError('Input argument must be string or tuple.')

      if output == 'text':
         return one_level_paths_to_string(retval)
      elif output == 'tuple':
         return _one_level_paths_to_tuple(retval)
      else:
         return retval

  def extract_longest_paths(self, **kvargs):
      """
      Extract longest paths of the transducer.

      Parameters
      ----------
      * `kvargs` :
          Possible parameters and their default values are: obey_flags=True,
          output='dict'
      * `obey_flags` :
          Whether flag diacritics are obeyed. The default is True.
      * `output` :
          Possible values are 'dict', 'text' and 'raw', 'dict' being the default.

      """
      obey_flags=True
      output='dict' # 'dict' (default), 'text', 'raw'

      for k,v in kvargs.items():
          if k == 'obey_flags':
             if v == 'True':
                pass
             elif v == 'False':
                obey_flags=False
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'True' and 'False'.")
          elif k == 'output':
             if v == 'text':
                output == 'text'
             elif v == 'raw':
                output='raw'
             elif v == 'dict':
                output='dict'
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'dict' (default), 'text', 'raw'.")
          else:
             print('Warning: ignoring unknown argument %s.' % (k))

      retval = self._extract_longest_paths(obey_flags)

      if output == 'text':
         return two_level_paths_to_string(retval)
      elif output == 'dict':
         return _two_level_paths_to_dict(retval)
      else:
         return retval

  def extract_shortest_paths(self, **kvargs):
      """
      Extract shortest paths of the transducer.

      Parameters
      ----------
      * `kvargs` :
          Possible parameters and their default values are: obey_flags=True.
      * `output` :
          Possible values are 'dict', 'text' and 'raw', 'dict' being the default.

      """
      output='dict' # 'dict' (default), 'text', 'raw'

      for k,v in kvargs.items():
          if k == 'output':
             if v == 'text':
                output == 'text'
             elif v == 'raw':
                output='raw'
             elif v == 'dict':
                output='dict'
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'dict' (default), 'text', 'raw'.")
          else:
             print('Warning: ignoring unknown argument %s.' % (k))

      retval = self._extract_shortest_paths()

      if output == 'text':
         return two_level_paths_to_string(retval)
      elif output == 'dict':
         return _two_level_paths_to_dict(retval)
      else:
         return retval

  def extract_paths(self, **kvargs):
      """

      Extract paths that are recognized by the transducer.

      Parameters
      ----------
      * `kvargs` :
          Arguments recognized are filter_flags, max_cycles, max_number, obey_flags,
          output, random.
      * `filter_flags` :
          Whether flags diacritics are filtered out from the result (default True).
      * `max_cycles` :
          Indicates how many times a cycle will be followed, with negative numbers
          indicating unlimited (default -1 i.e. unlimited).
      * `max_number` :
          The total number of resulting strings is capped at this value, with 0 or
          negative indicating unlimited (default -1 i.e. unlimited).
      * `obey_flags` :
          Whether flag diacritics are validated (default True).
      * `output` :
          Output format. Values recognized: 'text' (as a string, separated by
          newlines), 'raw' (a dictionary that maps each input string into a list of
          tuples of an output string and a weight), 'dict' (a dictionary that maps
          each input string into a tuple of tuples of an output string and a weight,
          the default).
      * `random` :
          Whether result strings are fetched randomly (default False).

      Returns
      -------
      The extracted strings. *output* controls how they are represented.

      pre: The transducer must be acyclic, if both *max_number* and *max_cycles* have
      unlimited values. Else a hfst.exceptions.TransducerIsCyclicException will be
      thrown.

      An example:

      >>> tr = hfst.regex('a:b+ (a:c+)')
      >>> print(tr)
      0       1       a       b       0.000000
      1       1       a       b       0.000000
      1       2       a       c       0.000000
      1       0.000000
      2       2       a       c       0.000000
      2       0.000000

      >>> print(tr.extract_paths(max_cycles=1, output='text'))
      a:b     0
      aa:bb   0
      aaa:bbc 0
      aaaa:bbcc       0
      aa:bc   0
      aaa:bcc 0

      >>> print(tr.extract_paths(max_number=4, output='text'))
      a:b     0
      aa:bc   0
      aaa:bcc 0
      aaaa:bccc       0

      >>> print(tr.extract_paths(max_cycles=1, max_number=4, output='text'))
      a:b     0
      aa:bb   0
      aa:bc   0
      aaa:bcc 0

      Exceptions
      ----------
      * `TransducerIsCyclicException` :

      See also: hfst.HfstTransducer.n_best
      """
      obey_flags=True
      filter_flags=True
      max_cycles=-1
      max_number=-1
      random=False
      output='dict' # 'dict' (default), 'text', 'raw'

      for k,v in kvargs.items():
          if k == 'obey_flags' :
             if v == 'True':
                pass
             elif v == 'False':
                obey_flags=False
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'True' and 'False'.")
          elif k == 'filter_flags' :
             if v == 'True':
                pass
             elif v == 'False':
                filter_flags=False
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'True' and 'False'.")
          elif k == 'max_cycles' :
             max_cycles=v
          elif k == 'max_number' :
             max_number=v
          elif k == 'random' :
             if v == 'False':
                pass
             elif v == 'True':
                random=True
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'True' and 'False'.")
          elif k == 'output':
             if v == 'text':
                output = 'text'
             elif v == 'raw':
                output='raw'
             elif v == 'dict':
                output='dict'
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'dict' (default), 'text', 'raw'.")
          else:
             print('Warning: ignoring unknown argument %s.' % (k))

      retval=0

      if obey_flags :
         if random :
            retval=self._extract_random_paths_fd(max_number, filter_flags)
         else :
            retval=self._extract_paths_fd(max_number, max_cycles)
      else :
         if random :
            retval=self._extract_random_paths(max_number)
         else :
            retval=self._extract_paths(max_number, max_cycles)

      if output == 'text':
         return two_level_paths_to_string(retval)
      elif output == 'dict':
         return _two_level_paths_to_dict(retval)
      else:
         return retval

  def substitute(self, s, S=None, **kvargs):
      """
      Substitute symbols or transitions in the transducer.

      Parameters
      ----------
      * `s` :
          The symbol or transition to be substituted. Can also be a dictionary of
          substitutions, if S == None.
      * `S` :
          The symbol, transition, a tuple of transitions or a transducer
          (hfst.HfstTransducer) that substitutes *s*.
      * `kvargs` :
          Arguments recognized are 'input' and 'output', their values can be False or
          True, True being the default. These arguments are valid only if *s* and *S*
          are strings, else they are ignored.
      * `input` :
          Whether substitution is performed on input side, defaults to True. Valid
          only if *s* and *S* are strings.
      * `output` :
          Whether substitution is performed on output side, defaults to True. Valid
          only if *s* and \\ S are strings.

      For more information, see hfst.HfstBasicTransducer.substitute. The function
      works similarly, with the exception of argument *S*, which must be
      hfst.HfstTransducer instead of hfst.HfstBasicTransducer.

      See also: hfst.HfstBasicTransducer.substitute
      """
      if S == None:
         if not isinstance(s, dict):
            raise RuntimeError('Sole input argument must be a dictionary.')

         subst_type=""

         for k, v in s.items():
             if _is_string(k):
                if subst_type == "":
                   subst_type="string"
                elif subst_type == "string pair":
                   raise RuntimeError('')
                if not _is_string(v):
                   raise RuntimeError('')
             elif _is_string_pair(k):
                if subst_type == "":
                   subst_type="string pair"
                elif subst_type == "string":
                   raise RuntimeError('')
                if not _is_string_pair(v):
                   raise RuntimeError('')
             else:
                raise RuntimeError('')

         if subst_type == "string":
            return self._substitute_symbols(s)
         else:
            return self._substitute_symbol_pairs(s)

      if _is_string(s):
         if _is_string(S):
            input=True
            output=True
            for k,v in kvargs.items():
                if k == 'input':
                   if v == False:
                      input=False
                elif k == 'output':
                   if v == False:
                      output=False
                else:
                   raise RuntimeError('Free argument not recognized.')
            return self._substitute_symbol(s, S, input, output)
         else:
            raise RuntimeError('...')
      elif _is_string_pair(s):
         if _is_string_pair(S):
            return self._substitute_symbol_pair(s, S)
         elif _is_string_pair_vector(S):
            return self._substitute_symbol_pair_with_set(s, S)
         elif isinstance(S, HfstTransducer):
            return self._substitute_symbol_pair_with_transducer(s, S, True)
         else:
            raise RuntimeError('...')
      else:
         raise RuntimeError('...')
%}

};

}; // class HfstTransducer


// *** HfstOutputStream *** //

hfst::HfstOutputStream * create_hfst_output_stream(const std::string & filename, hfst::ImplementationType type, bool hfst_format);

class HfstOutputStream
{
public:
~HfstOutputStream(void);
HfstOutputStream &flush();
void close(void);

%extend {

void write(hfst::HfstTransducer transducer) throw(StreamIsClosedException) { $self->redirect(transducer); }
HfstOutputStream() { return new hfst::HfstOutputStream(hfst::get_default_fst_type()); }

%pythoncode %{

def __init__(self, **kvargs):
    """
    Open a stream for writing binary transducers. Note: hfst.HfstTransducer.write_to_file
    is probably the easiest way to write a single binary transducer to a file.

    Parameters
    ----------
    * `kvargs` :
        Arguments recognized are filename, hfst_format, type.
    * `filename` :
        The name of the file where transducers are written. If the file exists, it
        is overwritten. If *filename* is not given, transducers are written to
        standard output.
    * `hfst_format` :
        Whether transducers are written in hfst format (default is True) or as such
        in their backend format.
    * `type` :
        The type of the transducers that will be written to the stream. Default is
        hfst.get_default_fst_type().

    Examples:

        # a stream for writing default type transducers in hfst format to standard output
        ostr = hfst.HfstOutputStream()
        transducer = hfst.regex('foo:bar::0.5')
        ostr.write(transducer)
        ostr.flush()

        # a stream for writing native sfst type transducers to a file
        ostr = hfst.HfstOutputStream(filename='transducer.sfst', hfst_format=False, type=hfst.ImplementationType.SFST_TYPE)
        transducer1 = hfst.regex('foo:bar')
        transducer1.convert(hfst.ImplementationType.SFST_TYPE)  # if not set as the default type
        transducer2 = hfst.regex('bar:baz')
        transducer2.convert(hfst.ImplementationType.SFST_TYPE)  # if not set as the default type
        ostr.write(transducer1)
        ostr.write(transducer2)
        ostr.flush()
        ostr.close()
    """
    filename = ""
    hfst_format = True
    type = _libhfst.get_default_fst_type()
    for k,v in kvargs.items():
        if k == 'filename':
           filename = v
        if k == 'hfst_format':
           hfst_format = v
        if k == 'type':
           type = v
    if filename == "":
       self.this = _libhfst.create_hfst_output_stream("", type, hfst_format)
    else:
       self.this = _libhfst.create_hfst_output_stream(filename, type, hfst_format)
%}

}

}; // class HfstOutputStream

// *** HfstInputStream *** //

class HfstInputStream
{
public:
    HfstInputStream(void) throw(StreamNotReadableException, NotTransducerStreamException, EndOfStreamException, TransducerHeaderException);
    HfstInputStream(const std::string &filename) throw(StreamNotReadableException, NotTransducerStreamException, EndOfStreamException, TransducerHeaderException);
    ~HfstInputStream(void);
    void close(void);
    bool is_eof(void);
    bool is_bad(void);
    bool is_good(void);
    ImplementationType get_type(void) const throw(TransducerTypeMismatchException);

%extend {

hfst::HfstTransducer * read() throw (EndOfStreamException) { return new hfst::HfstTransducer(*($self)); }

%pythoncode %{

def __iter__(self):
    """
    Return *self*. Needed for 'for ... in' statement.
    """
    return self

def next(self):
    """
    Read next transducer from stream and return it. Needed for 'for ... in' statement.
    """
    if self.is_eof():
        raise StopIteration
    else:
        return self.read();

def __next__(self):
    """
    Read next transducer from stream and return it. Needed for 'for ... in' statement.
    """
    return self.next()

%}

}

}; // class HfstInputStream


// *** HfstTokenizer *** //
  
  class HfstTokenizer
  {
  public:
     HfstTokenizer();
     void add_skip_symbol(const std::string &symbol);
     void add_multichar_symbol(const std::string& symbol);
     StringPairVector tokenize(const std::string &input_string) const;
     StringVector tokenize_one_level(const std::string &input_string) const;
     static StringPairVector tokenize_space_separated(const std::string & str);
     StringPairVector tokenize(const std::string &input_string,
                              const std::string &output_string) const;
     static void check_utf8_correctness(const std::string &input_string);
  };

namespace implementations {

  class HfstBasicTransducer;
  class HfstBasicTransition;
  typedef unsigned int HfstState;

  typedef std::vector<hfst::implementations::HfstBasicTransition> HfstBasicTransitions;


// *** HfstBasicTransducer *** //

class HfstBasicTransducer {

  public:

    HfstBasicTransducer(void);
    HfstBasicTransducer(const HfstBasicTransducer &graph);
    HfstBasicTransducer(const hfst::HfstTransducer &transducer);

    std::string name;
    void add_symbol_to_alphabet(const std::string &symbol);
    void remove_symbol_from_alphabet(const std::string &symbol);
    void remove_symbols_from_alphabet(const StringSet &symbols);
    void add_symbols_to_alphabet(const StringSet &symbols);
    // shadowed by the previous function: void add_symbols_to_alphabet(const StringPairSet &symbols);
    std::set<std::string> symbols_used();
    void prune_alphabet(bool force=true);
    const std::set<std::string> &get_alphabet() const;
    StringPairSet get_transition_pairs() const;
    HfstState add_state(void);
    HfstState add_state(HfstState s);
    HfstState get_max_state() const;
    std::vector<HfstState> states() const;
    void add_transition(HfstState s, const hfst::implementations::HfstBasicTransition & transition, bool add_symbols_to_alphabet=true);
    void remove_transition(HfstState s, const hfst::implementations::HfstBasicTransition & transition, bool remove_symbols_from_alphabet=false);
    bool is_final_state(HfstState s) const;
    float get_final_weight(HfstState s) const throw(StateIsNotFinalException, StateIndexOutOfBoundsException);
    void set_final_weight(HfstState s, const float & weight);
    void remove_final_weight(HfstState s);
%rename("_transitions") transitions(HfstState s);
    hfst::implementations::HfstBasicTransitions & transitions(HfstState s);
    bool is_infinitely_ambiguous();
    bool is_lookup_infinitely_ambiguous(const StringVector & s);
    int longest_path_size();

%extend {

    void _substitute_symbol(const std::string &old_symbol, const std::string &new_symbol, bool input_side=true, bool output_side=true) { self->substitute_symbol(old_symbol, new_symbol, input_side, output_side); }
    void _substitute_symbol_pair(const StringPair &old_symbol_pair, const StringPair &new_symbol_pair) { self->substitute_symbol_pair(old_symbol_pair, new_symbol_pair); }
    void _substitute_symbol_pair_with_set(const StringPair &old_symbol_pair, const hfst::StringPairSet &new_symbol_pair_set) { self->substitute_symbol_pair_with_set(old_symbol_pair, new_symbol_pair_set); }
    void _substitute_symbol_pair_with_transducer(const StringPair &symbol_pair, HfstBasicTransducer &transducer) { self->substitute_symbol_pair_with_transducer(symbol_pair, transducer); }
    void _substitute_symbols(const hfst::HfstSymbolSubstitutions &substitutions) { self->substitute_symbols(substitutions); } // alias for the previous function which is shadowed
    void _substitute_symbol_pairs(const hfst::HfstSymbolPairSubstitutions &substitutions) { self->substitute_symbol_pairs(substitutions); } // alias for the previous function which is shadowed
    void insert_freely(const StringPair &symbol_pair, float weight) { self->insert_freely(symbol_pair, weight); }
    void insert_freely(const HfstBasicTransducer &tr) { self->insert_freely(tr); }
    void sort_arcs() { self->sort_arcs(); }
    void disjunct(const StringPairVector &spv, float weight) { self->disjunct(spv, weight); }
    void harmonize(HfstBasicTransducer &another) { self->harmonize(another); }

  HfstTwoLevelPaths _lookup(const StringVector &lookup_path, size_t * infinite_cutoff, float * max_weight, bool obey_flags)
  {
    hfst::HfstTwoLevelPaths results;
    $self->lookup(lookup_path, results, infinite_cutoff, max_weight, obey_flags);
    return results;
  }

  std::string get_prolog_string(bool write_weights)
  {
    std::ostringstream oss;
    $self->write_in_prolog_format(oss, self->name, write_weights);
    return oss.str();
  }

  std::string get_xfst_string(bool write_weights)
  {
    std::ostringstream oss;
    $self->write_in_xfst_format(oss, write_weights);
    return oss.str();
  }

  std::string get_att_string(bool write_weights)
  {
    std::ostringstream oss;
    $self->write_in_att_format(oss, write_weights);
    std::string retval = oss.str();
    if (retval == "") // empty transducer must be represented as empty line in python, else read_att fails...
      retval = std::string("\n");
    return retval;
  }

  char * __str__()
  {
    std::ostringstream oss;
    $self->write_in_att_format(oss, true);
    return strdup(oss.str().c_str());
  }

  void add_transition(HfstState source, HfstState target, std::string input, std::string output, float weight=0) {
    hfst::implementations::HfstBasicTransition tr(target, input, output, weight);
    $self->add_transition(source, tr);
  }

%pythoncode %{
  def transitions(self, s):
      """
      ...
      """
      tr = self._transitions(s)
      retval = []
      for i in range(0, len(tr)):
          retval.append(tr[i])
      return retval

  def states_and_transitions(self):
      """
      ...
      """
      retval = []
      for s in self.states():
          retval.append(self.transitions(s))
      return retval

  def __iter__(self):
      """
      Return states and transitions of the transducer.
      """
      return self.states_and_transitions().__iter__()

  def __enumerate__(self):
      """
      Return an enumeration of states and transitions of the transducer.
      """
      return enumerate(self.states_and_transitions())

  def write_prolog(self, f, write_weights=True):
      """
      Write the transducer in prolog format with name *name* to file *f*,
      *write_weights* defined whether weights are written.

      Parameters
      ----------
      * `f` :
          A python file where the transducer is written.
      * `write_weights` :
          Whether weights are written.
      """
      prologstr = self.get_prolog_string(write_weights)
      f.write(prologstr)

  def write_xfst(self, f, write_weights=True):
      """
      Write the transducer in xfst format to file *f*, *write_weights* defined whether
      weights are written.

      Parameters
      ----------
      * `f` :
          A python file where transducer is written.
      * `write_weights` :
          Whether weights are written.
      """
      xfststr = self.get_xfst_string(write_weights)
      f.write(prologstr)

  def write_att(self, f, write_weights=True):
      """
      Write the transducer in AT&T format to file *f*, *write_weights* defined whether
      weights are written.

      Parameters
      ----------
      * `f` :
          A python file where transducer is written.
      * `write_weights` :
          Whether weights are written.
      """
      attstr = self.get_att_string(write_weights)
      f.write(attstr)

  def lookup(self, lookup_path, **kvargs):
      """
      Lookup tokenized input *input* in the transducer.

      Parameters
      ----------
      * `str` :
          A list/tuple of strings to look up.
      * `kvargs` :
          infinite_cutoff=-1, max_weight=None, obey_flags=False
      * `max_epsilon_loops` :
          How many times epsilon input loops are followed. Defaults to -1, i.e. infinitely.
      * `max_weight` :
          What is the maximum weight of a result allowed. Defaults to None, i.e. infinity.
      * `obey_flags` :
          Whether flag diacritic constraints are obeyed. Defaults to False.
      """
      max_weight = None
      max_epsilon_loops = None
      obey_flags = False
      output='dict' # 'dict' (default), 'text', 'raw'

      for k,v in kvargs.items():
          if k == 'max_weight' :
             max_weight=v
          elif k == 'max_epsilon_loops' :
             infinite_cutoff=v
          elif k == 'obey_flags' :
             obey_flags=v
          elif k == 'output':
             if v == 'text':
                output == 'text'
             elif v == 'raw':
                output='raw'
             elif v == 'dict':
                output='dict'
             else:
                print('Warning: ignoring argument %s as it has value %s.' % (k, v))
                print("Possible values are 'dict' (default), 'text', 'raw'.")
          else:
             print('Warning: ignoring unknown argument %s.' % (k))

      retval = self._lookup(lookup_path, max_epsilon_loops, max_weight, obey_flags)

      if output == 'text':
         return _two_level_paths_to_string(retval)
      elif output == 'dict':
         return _two_level_paths_to_dict(retval)
      else:
         return retval

  def substitute(self, s, S=None, **kvargs):
      """

      Substitute symbols or transitions in the transducer.

      Parameters
      ----------
      * `s` :
          The symbol or transition to be substituted. Can also be a dictionary of
          substitutions, if S == None.
      * `S` :
          The symbol, transition, a tuple of transitions or a transducer
          (hfst.HfstBasicTransducer) that substitutes *s*.
      * `kvargs` :
          Arguments recognized are 'input' and 'output', their values can be False or
          True, True being the default. These arguments are valid only if *s* and *S*
          are strings, else they are ignored.
      * `input` :
          Whether substitution is performed on input side, defaults to True. Valid
          only if *s* and *S* are strings.
      * `output` :
          Whether substitution is performed on output side, defaults to True. Valid
          only if *s* and *S* are strings.

      Possible combinations of arguments and their types are:

      (1) substitute(str, str, input=bool, output=bool): substitute symbol with symbol
      on input, output or both sides of each transition in the transducer. (2)
      substitute(strpair, strpair): substitute transition with transition (3)
      substitute(strpair, strpairtuple): substitute transition with several
      transitions (4) substitute(strpair, transducer): substitute transition with a
      transducer (5) substitute(dict): perform several symbol-to-symbol substitutions
      (6) substitute(dict): perform several transition-to-transition substitutions

      Examples:

      (1) tr.substitute('a', 'A', input=True, output=False): substitute lowercase a:s
      with uppercase ones (2) tr.substitute(('a','b'),('A','B')): substitute
      transitions that map lowercase a into lowercase b with transitions that map
      uppercase a into uppercase b (3) tr.substitute(('a','b'),
      (('A','B'),('a','B'),('A','b'))): change either or both sides of a transition
      [a:b] to uppercase (4) tr.substitute(('a','b'), hfst.regex('[a:b]+')) change
      [a:b] transition into one or more consecutive [a:b] transitions (5)
      tr.substitute({'a':'A', 'b':'B', 'c':'C'}) change lowercase a, b and c into
      their uppercase variants (6) tr.substitute( {('a','a'):('A','A'),
      ('b','b'):('B','B'), ('c','c'):('C','C')} ): change lowercase a, b and c into
      their uppercase variants

      In case (4), epsilon transitions are used to attach copies of transducer *S*
      between the SOURCE and TARGET state of each transition that is substituted. The
      transition itself is deleted, but its weight is copied to the epsilon transition
      leading from SOURCE to the initial state of *S*. Each final state of *S* is made
      non-final and an epsilon transition leading to TARGET is attached to it. The
      final weight is copied to the epsilon transition.
      """
      if S == None:
         if not isinstance(s, dict):
            raise RuntimeError('First input argument must be a dictionary.')

         subst_type=""

         for k, v in s.items():
             if _is_string(k):
                if subst_type == "":
                   subst_type="string"
                elif subst_type == "string pair":
                   raise RuntimeError('')
                if not _is_string(v):
                   raise RuntimeError('')
             elif _is_string_pair(k):
                if subst_type == "":
                   subst_type="string pair"
                elif subst_type == "string":
                   raise RuntimeError('')
                if not _is_string_pair(v):
                   raise RuntimeError('')
             else:
                raise RuntimeError('')

         if subst_type == "string":
            return self._substitute_symbols(s)
         else:
            return self._substitute_symbol_pairs(s)

      if _is_string(s):
         if _is_string(S):
            input=True
            output=True
            for k,v in kvargs.items():
                if k == 'input':
                   if v == False:
                      input=False
                elif k == 'output':
                   if v == False:
                      output=False
                else:
                   raise RuntimeError('Free argument not recognized.')
            return self._substitute_symbol(s, S, input, output)
         else:
            raise RuntimeError('...')
      elif _is_string_pair(s):
         if _is_string_pair(S):
            return self._substitute_symbol_pair(s, S)
         elif _is_string_pair_vector(S):
            return self._substitute_symbol_pair_with_set(s, S)
         elif isinstance(S, HfstBasicTransducer):
            return self._substitute_symbol_pair_with_transducer(s, S)
         else:
            raise RuntimeError('...')
      else:
         raise RuntimeError('...')

%}

}
        
}; // class HfstBasicTransducer

// *** HfstBasicTransition *** //

class HfstBasicTransition {
  public:
    HfstBasicTransition();
    HfstBasicTransition(hfst::implementations::HfstState, std::string, std::string, float);
    ~HfstBasicTransition();
    HfstState get_target_state() const;
    std::string get_input_symbol() const;
    void set_input_symbol(const std::string & symbol);
    std::string get_output_symbol() const;
    void set_output_symbol(const std::string & symbol);
    float get_weight() const;
    void set_weight(float f);
  
%extend{
    char *__str__() {
      static char str[1024];
      sprintf(str, "%u %s %s %f", $self->get_target_state(), $self->get_input_symbol().c_str(), $self->get_output_symbol().c_str(), $self->get_weight());
      return str;
    }
}

}; // class HfstBasicTransition

} // namespace implementations


// *** XreCompiler: offer only a limited set of functions ***

namespace xre {
class XreCompiler
{
  public:
  XreCompiler();
  XreCompiler(hfst::ImplementationType impl);
  void define_list(const std::string& name, const std::set<std::string>& symbol_list);
  bool define_function(const std::string& name, unsigned int arguments, const std::string& xre);
  bool is_definition(const std::string& name);
  bool is_function_definition(const std::string& name);
  void undefine(const std::string& name);
  HfstTransducer* compile(const std::string& xre);
  void set_verbosity(bool verbose);
  bool getOutputToConsole();
  void set_expand_definitions(bool expand); // TODO: should this be set automatically to True?

  // *** Some wrappers *** //
%extend{
  void define_xre(const std::string& name, const std::string& xre)
  {
    self->set_expand_definitions(true);
    self->define(name, xre);
  }
  void define_transducer(const std::string& name, const HfstTransducer & transducer)
  {
    self->set_expand_definitions(true);
    self->define(name, transducer);
  }
  void setOutputToConsole(bool value)
  {
    (void)self->setOutputToConsole(value);
  }
}

};
}

// *** The LexcCompiler functions are offered only because they are needed in some python functions... *** //

namespace lexc {
  class LexcCompiler
  {
    public:
      LexcCompiler();
      LexcCompiler(hfst::ImplementationType impl);
      LexcCompiler(hfst::ImplementationType impl, bool withFlags, bool alignStrings);
      LexcCompiler& setVerbosity(unsigned int verbose);
      void setOutputToConsole(bool);
  };

}

// *** The XfstCompiler functions are offered only because they are needed in some python functions... *** //

namespace xfst {
  class XfstCompiler
  {
    public:
      XfstCompiler();
      XfstCompiler(hfst::ImplementationType impl);
      XfstCompiler& setOutputToConsole(bool value);
      XfstCompiler& setReadInteractiveTextFromStdin(bool Value);
      XfstCompiler& setReadline(bool value);
      XfstCompiler& setVerbosity(bool verbosity);
      XfstCompiler& set(const char* name, const char* text);
      char * get_prompt() const;
      XfstCompiler& apply_up(const char* indata);
      XfstCompiler& apply_down(const char* indata);
      int parse_line(std::string line);
      bool quit_requested() const;
  };
}

// internal functions

std::string hfst::get_hfst_regex_error_message();
hfst::HfstTransducer * hfst::hfst_regex(hfst::xre::XreCompiler & comp, const std::string & regex_string, const std::string & error_stream);

char * hfst::get_hfst_xfst_string_one();
char * hfst::get_hfst_xfst_string_two();
int hfst::hfst_compile_xfst_to_string_one(hfst::xfst::XfstCompiler & comp, std::string input);
int hfst::hfst_compile_xfst(hfst::xfst::XfstCompiler & comp, std::string input, const std::string & output_stream, const std::string & error_stream);

std::string hfst::get_hfst_lexc_output();
hfst::HfstTransducer * hfst::hfst_compile_lexc(hfst::lexc::LexcCompiler & comp, const std::string & filename, const std::string & error_stream);

std::string hfst::get_hfst_sfst_output();
hfst::HfstTransducer * hfst::hfst_compile_sfst(const std::string & filename, const std::string & error_stream, bool verbose, bool output_to_console);

std::string hfst::one_level_paths_to_string(const HfstOneLevelPaths &);
std::string hfst::two_level_paths_to_string(const HfstTwoLevelPaths &);

bool parse_prolog_network_line(const std::string & line, hfst::implementations::HfstBasicTransducer * graph);
bool parse_prolog_arc_line(const std::string & line, hfst::implementations::HfstBasicTransducer * graph);
bool parse_prolog_symbol_line(const std::string & line, hfst::implementations::HfstBasicTransducer * graph);
bool parse_prolog_final_line(const std::string & line, hfst::implementations::HfstBasicTransducer * graph);


// fuctions visible under module hfst

void hfst::set_default_fst_type(hfst::ImplementationType t);
hfst::ImplementationType hfst::get_default_fst_type();
std::string hfst::fst_type_to_string(hfst::ImplementationType t);


// *** hfst_rules (will be wrapped under module hfst.rules) *** //

namespace hfst_rules {

  HfstTransducer two_level_if(const HfstTransducerPair & context, const StringPairSet & mappings, const StringPairSet & alphabet);
  HfstTransducer two_level_only_if(const HfstTransducerPair &context, const StringPairSet &mappings, const StringPairSet &alphabet);
  HfstTransducer two_level_if_and_only_if(const HfstTransducerPair &context, const StringPairSet &mappings, const StringPairSet &alphabet);
  HfstTransducer replace_down(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer replace_down_karttunen(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer replace_right(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer replace_left(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer replace_up(const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer replace_down(const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer left_replace_up(const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer left_replace_up(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer left_replace_down(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer left_replace_down_karttunen(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer left_replace_left(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer left_replace_right(const HfstTransducerPair &context, const HfstTransducer &mapping, bool optional, const StringPairSet &alphabet);
  HfstTransducer restriction(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer coercion(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer restriction_and_coercion(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer surface_restriction(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer surface_coercion(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer surface_restriction_and_coercion(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer deep_restriction(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer deep_coercion(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);
  HfstTransducer deep_restriction_and_coercion(const HfstTransducerPairVector &contexts, const HfstTransducer &mapping, const StringPairSet &alphabet);

} // namespace hfst_rules


} // namespace hfst

namespace hfst {
  namespace twolc {
    class TwolcCompiler
    {
    public:
      static int compile(const std::string & inputfile, const std::string & outputfile,
			 bool silent, bool verbose, bool resolve_left_conflicts,
			 bool resolve_right_conflicts, hfst::ImplementationType type);
    };
  }
}

// *** PmatchContainer *** //

namespace hfst_ol {
    class PmatchContainer
    {
    public:
        PmatchContainer(void);
        PmatchContainer(hfst::HfstTransducerVector transducers);
        ~PmatchContainer(void);
        std::string match(const std::string & input, double time_cutoff = 0.0);
        std::string get_profiling_info(void);
        void set_verbose(bool b);
        //void set_extract_tags_mode(bool b);
        void set_profile(bool b);

}; // class PmatchContainer
} // namespace hfst_ol
 
%pythoncode %{

class ImplementationType:
    """
    Back-end implementation.

    Attributes:

        SFST_TYPE:               SFST type, unweighted
        TROPICAL_OPENFST_TYPE:   OpenFst type with tropical weights
        LOG_OPENFST_TYPE:        OpenFst type with logarithmic weights (limited support)
        FOMA_TYPE:               FOMA type, unweighted
        XFSM_TYPE:               XFST type, unweighted (limited support)
        HFST_OL_TYPE:            HFST optimized-lookup type, unweighted
        HFST_OLW_TYPE:           HFST optimized-lookup type, weighted
        HFST2_TYPE:              HFST version 2 legacy type
        UNSPECIFIED_TYPE:        type not specified
        ERROR_TYPE:              (something went wrong)

    """
    SFST_TYPE = _libhfst.SFST_TYPE
    TROPICAL_OPENFST_TYPE = _libhfst.TROPICAL_OPENFST_TYPE    
    LOG_OPENFST_TYPE = _libhfst.LOG_OPENFST_TYPE
    FOMA_TYPE = _libhfst.FOMA_TYPE
    XFSM_TYPE = _libhfst.XFSM_TYPE
    HFST_OL_TYPE = _libhfst.HFST_OL_TYPE
    HFST_OLW_TYPE = _libhfst.HFST_OLW_TYPE
    HFST2_TYPE = _libhfst.HFST2_TYPE
    UNSPECIFIED_TYPE = _libhfst.UNSPECIFIED_TYPE
    ERROR_TYPE = _libhfst.ERROR_TYPE

class ReplaceType:
    """
    Replace type in Xerox-type rules.

    Attributes:

        REPL_UP:      Match contexts on input level
        REPL_DOWN:    Match contexts on output level
        REPL_RIGHT:   Match left contexts on input level and right contexts on output level
        REPL_LEFT:    Match left contexts on output level and right contexts on input level

    """
    REPL_UP = _libhfst.REPL_UP
    REPL_DOWN = _libhfst.REPL_DOWN
    REPL_RIGHT = _libhfst.REPL_RIGHT
    REPL_LEFT = _libhfst.REPL_LEFT

%}
