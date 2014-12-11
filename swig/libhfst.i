%module libhfst
%include "std_string.i"
%include "std_set.i"
%include "std_vector.i"
%include "std_pair.i"
%include "std_map.i"
%include "std_iostream.i"
%include "std_ios.i"
%include "file.i"
%include "exception.i"

%{
#define SWIG_FILE_WITH_INIT
#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstOutputStream.h"
#include "HfstDataTypes.h"
#include "HfstFlagDiacritics.h"
#include "parsers/XreCompiler.h"
#include "hfst_swig_extensions.h"
#include "HfstExceptionDefs.h"
#include "implementations/optimized-lookup/pmatch.h"
%}


class HfstPath {
public:
  float weight;
  std::string input;
  std::string output;
  ~HfstPath();
};

namespace std {
%template(StringVector) vector<string>;
%template(StringPairVector) vector<pair<string, string > >;
%template(OneLevelPath) pair<float, vector<string> >;
%template(OneLevelPathVector) vector<pair<float, vector<string> > >;
%template(OneLevelPaths) set<pair<float, vector<string> > >;
#%template(StringFloatVector) vector<pair<string, float> >;
%template(StringPair) pair<string, string>;
%template(StringPairSet) set<pair<string, string> >;
%template(StringSet) set<string>;
%template(HfstTransitions) vector<hfst::implementations::HfstBasicTransition>;
%template(IntVector) vector<unsigned int>;
%template(HfstTwoLevelPaths) set<pair<float, vector<pair <string, string> > > >;
%template(HfstPathVector) vector<HfstPath>;
%template(HfstSymbolSubstitutions) map<string, string>;
%template(HfstSymbolPairSubstitutions) map<pair<string, string>, pair<string, string> >;
%template(HfstTransducerPair) pair<hfst::HfstTransducer, hfst::HfstTransducer>;
%template(HfstTransducerPairVector) vector<pair<hfst::HfstTransducer, hfst::HfstTransducer> >;
}

%include <typemaps.i>
%apply unsigned int & INPUT { unsigned int & linecount };

class HfstException {
public:
HfstException(const std::string&, const std::string&, size_t);
    %extend {
    char *__str__() {
      std::string msg = $self->operator()();
      return strdup(msg.c_str());
    }
    }
};

class HfstTransducerTypeMismatchException: public HfstException {};
class ImplementationTypeNotAvailableException: public HfstException {};
class FunctionNotImplementedException: public HfstException {};
class StreamNotReadableException: public HfstException {};
class StreamCannotBeWrittenException: public HfstException {};
class StreamIsClosedException: public HfstException {};
class EndOfStreamException: public HfstException {};
class TransducerIsCyclicException: public HfstException {};
class NotTransducerStreamException: public HfstException {};
class NotValidAttFormatException: public HfstException {};
class NotValidLexcFormatException: public HfstException {};
class StateIsNotFinalException: public HfstException {};
class ContextTransducersAreNotAutomataException: public HfstException {};
class TransducersAreNotAutomataException: public HfstException {};
class StateIndexOutOfBoundsException: public HfstException {};
class TransducerHeaderException: public HfstException {};
class MissingOpenFstInputSymbolTableException: public HfstException {};
class TransducerTypeMismatchException: public HfstException {};
class EmptySetOfContextsException: public HfstException {};
class SpecifiedTypeRequiredException: public HfstException {};
class HfstFatalException: public HfstException {};
class TransducerHasWrongTypeException: public HfstException {};
class IncorrectUtf8CodingException: public HfstException {};
class EmptyStringException: public HfstException {};
class SymbolNotFoundException: public HfstException {};
class MetadataException: public HfstException {};

std::string hfst_get_exception();

namespace hfst
{

class HfstFile;

class HfstFile {
public:
  void close();
  void write(const char * str);
};
HfstFile hfst_open(const char * filename, const char * args);
HfstFile hfst_stdin();
HfstFile hfst_stdout();

/*
 * One of the (apparent) peculiarities of swig is that things break in the
 * wrapper very easily if things aren't defined in precisely the right order,
 * and often it's necessary to forward define things. For that reason there's
 * some overkill in the forward definitions in this file.
 */

  enum ImplementationType
  {
    SFST_TYPE,
    TROPICAL_OPENFST_TYPE,
    LOG_OPENFST_TYPE,
    FOMA_TYPE,
    HFST_OL_TYPE,
    HFST_OLW_TYPE,
    HFST2_TYPE,
    UNSPECIFIED_TYPE,
    ERROR_TYPE
  };

  enum PushType
  {
    TO_INITIAL_STATE,
    TO_FINAL_STATE
  };


class HfstInputStream;
typedef HfstOneLevelPaths std::set<pair<float, vector<string> > >;
//class HfstTwoLevelPaths;
class HfstOutputStream;
class HfstTransducer;
class FdOperation;
class HfstTokenizer;
typedef std::vector<HfstTransducer> HfstTransducerVector;
typedef std::set<std::string> StringSet;
typedef std::pair<std::string, std::string> StringPair;
typedef std::set<std::pair<std::string, std::string> > StringPairSet;
typedef std::vector<std::string> StringVector;
typedef std::vector<std::pair<std::string, std::string> > StringPairVector;

typedef std::map<std::string, std::string> HfstSymbolSubstitutions;
typedef std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string> > HfstSymbolPairSubstitutions;

typedef std::set<std::pair<float, std::vector<std::pair <std::string, std::string> > > > HfstTwoLevelPaths; 

HfstTwoLevelPaths extract_paths(const HfstTransducer &t, int max_num=-1, int cycles=-1) throw (TransducerIsCyclicException);
HfstTwoLevelPaths extract_paths_fd(const HfstTransducer &t, int max_num=-1, int cycles=-1, bool filter_fd=false) throw (TransducerIsCyclicException);

typedef std::pair<HfstTransducer, HfstTransducer> HfstTransducerPair;
typedef std::vector<std::pair<HfstTransducer, HfstTransducer> > HfstTransducerPairVector;

namespace implementations {
class HfstBasicTransducer;
class HfstBasicTransition;

typedef unsigned int HfstState;

class HfstBasicTransducer {
public:

typedef std::vector<HfstBasicTransition> HfstTransitions;

HfstState add_state (void);
HfstState add_state (HfstState s);
std::vector<unsigned int> states() const;
void add_symbol_to_alphabet (const std::string &symbol);
void add_symbols_to_alphabet (const hfst::StringSet &symbols);
void add_transition (HfstState s, const HfstBasicTransition &transition, bool add_symbols_to_alphabet=true);
HfstBasicTransducer & disjunct(const StringPairVector &spv, float weight);
const StringSet &get_alphabet () const;
float get_final_weight (HfstState s) const throw (StateIsNotFinalException);
HfstState get_max_state () const;
HfstBasicTransducer &harmonize (HfstBasicTransducer &another);
HfstBasicTransducer (void);
HfstBasicTransducer (const HfstBasicTransducer &graph);
HfstBasicTransducer (const hfst::HfstTransducer &transducer);
HfstBasicTransducer (FILE *file) throw (NotValidAttFormatException);
HfstBasicTransducer (HfstFile &file) throw (NotValidAttFormatException);
HfstBasicTransducer & insert_freely (const StringPair &symbol_pair, float weight);
HfstBasicTransducer & insert_freely (const StringPairSet &symbol_pairs, float weight);
HfstBasicTransducer & insert_freely (const HfstBasicTransducer &graph);
bool is_final_state (HfstState s) const;
HfstBasicTransducer & assign (const HfstBasicTransducer &graph);
const HfstTransitions & transitions (HfstState s) const;
void prune_alphabet ();
void remove_symbol_from_alphabet (const std::string &symbol);
void set_final_weight (HfstState s, const float &weight);
HfstBasicTransducer & sort_arcs (void);
HfstBasicTransducer & substitute (const std::string &old_symbol, const std::string &new_symbol, bool input_side=true, bool output_side=true);
HfstBasicTransducer & substitute_symbols (const HfstSymbolSubstitutions &substitutions);
HfstBasicTransducer & substitute_symbol_pairs (const HfstSymbolPairSubstitutions &substitutions);
HfstBasicTransducer & substitute (const StringPair &sp, const StringPairSet &sps);
HfstBasicTransducer & substitute (const StringPair &old_pair, const StringPair &new_pair);
HfstBasicTransducer & substitute (bool(*func)(const StringPair &sp, StringPairSet &sps));
HfstBasicTransducer & substitute (const StringPair &sp, const HfstBasicTransducer &graph);
void write_in_att_format (std::ostream &os, bool write_weights=true);
void write_in_att_format (FILE *file, bool write_weights=true);
void write_in_att_format_number (FILE *file, bool write_weights=true);

    %extend {
    char *__str__() {
    	 static char tmp[1024]; 
    	 $self->write_in_att_format(tmp);
	 return tmp;    
    }
    };

};

class HfstBasicTransition {
public:
	HfstBasicTransition(HfstState s, const std::string &input, const std::string &output, float weight) throw (EmptyStringException);
	~HfstBasicTransition();
	std::string get_input_symbol() const;
	std::string get_output_symbol() const;
	HfstState get_target_state() const;
	float get_weight() const;
	
    %extend {
    char *__str__() {
    	 static char tmp[1024];
    	 sprintf(tmp, "%s\t%s\t%i\t%f\n", 
	 $self->get_input_symbol().c_str(), 
	 $self->get_output_symbol().c_str(), 
	 $self->get_target_state(), 
	 $self->get_weight());
	 return tmp;    
    }
    };

};

}

// From hfst_swig_extensions.h
std::vector<std::pair <float, std::vector<std::string> > > vectorize(hfst::HfstOneLevelPaths * olps);
std::vector<std::pair <float, std::vector<std::pair<std::string, std::string> > > > vectorize(hfst::HfstTwoLevelPaths tlps);
std::vector<std::pair <float, std::vector<std::string> > > purge_flags(std::vector<std::pair<float, std::vector<std::string> > > olpv);
std::vector<HfstPath> detokenize_vector(OneLevelPathVector olpv);
std::vector<HfstPath> detokenize_paths(hfst::HfstOneLevelPaths * olps);
std::vector<HfstPath> detokenize_and_purge_paths(hfst::HfstOneLevelPaths * olps);
std::vector<HfstPath> detokenize_vector(TwoLevelPathVector tlpv);
std::vector<HfstPath> detokenize_paths(hfst::HfstTwoLevelPaths tlps);
std::vector<HfstPath> detokenize_and_purge_paths(hfst::HfstTwoLevelPaths tlps);

class HfstInputStream{
public:
    HfstInputStream(const std::string & filename) throw (NotTransducerStreamException);
    HfstInputStream(void);
    void close(void);
    bool is_bad(void);
    bool is_eof(void);
    bool is_good(void);
    ~HfstInputStream(void);
};

class HfstOutputStream{
public:
    HfstOutputStream(const std::string & filename, ImplementationType type, bool hfst_format=true);
    HfstOutputStream(ImplementationType type, bool hfst_format=true);
    void close(void);
    HfstOutputStream & redirect (HfstTransducer & transducer) throw (StreamIsClosedException);
    ~HfstOutputStream(void);
};

class HfstTransducer {
public:
    // First all the constructors
    HfstTransducer();
    HfstTransducer(HfstInputStream & in) throw (EndOfStreamException);
    HfstTransducer(const HfstTransducer &another);
    HfstTransducer(const std::string &utf8_str, const HfstTokenizer &multichar_symbol_tokenizer, ImplementationType type);
    HfstTransducer(const std::string &input_utf8_str, const std::string &output_utf8_str, const HfstTokenizer &multichar_symbol_tokenizer, ImplementationType type);
    HfstTransducer(const hfst::implementations::HfstBasicTransducer &t, ImplementationType type);
    HfstTransducer(ImplementationType type);
    HfstTransducer(const std::string &symbol, ImplementationType type);
    HfstTransducer(const std::string &isymbol, const std::string &osymbol, ImplementationType type);
    HfstTransducer(FILE *ifile, ImplementationType type, const std::string &epsilon_symbol) throw (EndOfStreamException, NotValidAttFormatException);
    HfstTransducer(HfstFile &ifile, ImplementationType type, const std::string &epsilon_symbol) throw (EndOfStreamException, NotValidAttFormatException);
    
    // Then everything else, in the (alphabetic) order in the API manual
    bool compare(const HfstTransducer &another) const;
    HfstTransducer & compose(const HfstTransducer &another);
    HfstTransducer & compose_intersect(const HfstTransducerVector &v,
                                       bool invert=false);
    HfstTransducer & concatenate(const HfstTransducer &another);
    HfstTransducer & convert(ImplementationType type, std::string options="");
    HfstTransducer & determinize(void);
    HfstTransducer & disjunct(const HfstTransducer &another) throw (TransducerTypeMismatchException);
    void extract_paths(HfstTwoLevelPaths &results, int max_num=-1, int cycles=-1) const;
    void extract_paths_fd(HfstTwoLevelPaths &results, int max_num=-1, int cycles=-1, bool filter_fd=true) const;
    StringSet get_alphabet(void) const;
    std::string get_name(void) const;
    ImplementationType get_type(void) const;
    HfstTransducer & input_project(void);
    HfstTransducer & insert_freely(const StringPair &symbol_pair);
    HfstTransducer & insert_freely(const HfstTransducer &tr);
    void insert_to_alphabet(const std::string &symbol);
    HfstTransducer & intersect(const HfstTransducer &another) throw (TransducerTypeMismatchException);
    HfstTransducer & invert(void);
    bool is_cyclic(void) const;
    bool is_lookdown_infinitely_ambiguous(const StringVector &s) const;
    bool is_lookup_infinitely_ambiguous (const StringVector &s) const;
    hfst::HfstOneLevelPaths *	lookdown(const StringVector &s, ssize_t limit=-1) const;
    hfst::HfstOneLevelPaths *	lookdown_fd(StringVector &s, ssize_t limit=-1) const;
    hfst::HfstOneLevelPaths * lookup(const StringVector &s, ssize_t limit=-1) const;
    hfst::HfstOneLevelPaths *	lookup(const std::string &s, ssize_t limit=-1) const;
    hfst::HfstOneLevelPaths *	lookup(const HfstTokenizer &tok, const std::string &s, ssize_t limit=-1) const;
    hfst::HfstOneLevelPaths * lookup_fd(const std::string & s, ssize_t limit = -1) const;
    HfstTransducer & minimize(void);
    HfstTransducer & n_best(unsigned int n);
    HfstTransducer & assign (const HfstTransducer & another) throw (TransducerTypeMismatchException);
    HfstTransducer & optionalize(void);
    HfstTransducer & output_project(void);
    HfstTransducer & priority_union (const HfstTransducer &another)  throw (TransducerTypeMismatchException);
    HfstTransducer & push_weights(PushType type);
    HfstTransducer & remove_epsilons(void);
    void remove_from_alphabet(const std::string &symbol);
    HfstTransducer & repeat_n(unsigned int n);
    HfstTransducer & repeat_n_minus(unsigned int n);
    HfstTransducer & repeat_n_plus(unsigned int n);
    HfstTransducer & repeat_n_to_k(unsigned int n, unsigned int k);
    HfstTransducer & repeat_plus(void);
    HfstTransducer & repeat_star(void);
    HfstTransducer & reverse (void);
    HfstTransducer & set_final_weights(float weight);
    void set_name(const std::string &name);
    HfstTransducer & shuffle(const HfstTransducer &another) throw (TransducersAreNotAutomataException, TransducerTypeMismatchException);
    HfstTransducer & substitute(bool(*func)(const StringPair &sp, StringPairSet &sps));
    HfstTransducer & substitute(const StringPair &old_symbol_pair, const StringPairSet &new_symbol_pair_set);
    HfstTransducer & substitute(const StringPair &symbol_pair, HfstTransducer &transducer);
    HfstTransducer & substitute(const std::string &old_symbol, const std::string &new_symbol, bool input_side=true, bool output_side=true);
    HfstTransducer & substitute(const StringPair &old_symbol_pair, const StringPair &new_symbol_pair);
    HfstTransducer & substitute_symbols(const HfstSymbolSubstitutions &substitutions);
    HfstTransducer & substitute_symbol_pairs(const HfstSymbolPairSubstitutions &substitutions);
    HfstTransducer & subtract(const HfstTransducer &another) throw (TransducerTypeMismatchException);
    HfstTransducer & transform_weights(float(*func)(float));
    void write_in_att_format(const std::string &filename, bool write_weights=true) const;
    void write_in_att_format(FILE *ofile, bool write_weights=true) const;
    void write_in_att_format(HfstFile &ofile, bool write_weights=true) const;
    void write_in_att_format(char * buffer, bool write_weights=true) const;
    virtual ~HfstTransducer(void);
    static HfstTransducer read_lexc(const std::string &filename, ImplementationType type, bool );
    static HfstTransducer universal_pair(ImplementationType type);

    static bool is_implementation_type_available(ImplementationType impl);

    %extend {

    char *__str__() {
    	 static char tmp[1024]; 
    	 $self->write_in_att_format(tmp);
	 return tmp;    
    }
    };

};


  class MultiCharSymbolTrie;
  typedef std::vector<MultiCharSymbolTrie*> MultiCharSymbolTrieVector;
  typedef std::vector<bool> SymbolEndVector;

  class MultiCharSymbolTrie
  {
  public:
    MultiCharSymbolTrie(void);
    ~MultiCharSymbolTrie(void);
    void add(const char * p);
    const char * find(const char * p) const;  
  };
  
  class HfstTokenizer
  {  
  public:

    HfstTokenizer();
    void add_skip_symbol(const std::string &symbol);
    void add_multichar_symbol(const std::string& symbol);
    StringPairVector tokenize(const std::string &input_string) const;
    StringVector tokenize_one_level(const std::string &input_string) const;
    StringPairVector tokenize(const std::string &input_string,
                              const std::string &output_string) const;
    static void check_utf8_correctness(const std::string &input_string);
  };

  HfstTransducer ptrvalue(const HfstTransducer * t);

  namespace lexc {

  class LexcCompiler
  {
  public:
    LexcCompiler();
    LexcCompiler(hfst::ImplementationType impl);
    LexcCompiler& parse(FILE* infile);
    LexcCompiler& parse(const char* filename);
    LexcCompiler& setVerbosity(bool verbose);
    LexcCompiler& addAlphabet(const std::string& alphabet);
    LexcCompiler& setCurrentLexiconName(const std::string& lexicon_name);
    LexcCompiler& addStringEntry(const std::string& entry, const std::string& continuation, const double weight);
    LexcCompiler& addStringPairEntry(const std::string& upper, const std::string& lower, const std::string& continuation, const double weight);
    LexcCompiler& addXreEntry(const std::string& xre, const std::string& continuation, const double weight);
    LexcCompiler& addXreDefinition(const std::string& name, const std::string& xre);
    LexcCompiler& setInitialLexiconName(const std::string& lexicon_name);
    hfst::HfstTransducer * compileLexical();
    //const std::map<std::string,hfst::HfstTransducer>& getStringTries() const;
    //const std::map<std::string,hfst::HfstTransducer>& getRegexpUnions() const;
    const LexcCompiler& printConnectedness(bool & warnings) const;
  };
  };

  namespace xre {

    class XreCompiler
    {
    public:
      XreCompiler();
      XreCompiler(hfst::ImplementationType impl);
      void define(const std::string& name, const std::string& xre);
      void set_expand_definitions(bool);
      HfstTransducer* compile(const std::string& xre); // TODO: Warning 321: 'compile' conflicts with a built-in name in python
    };

  };

  namespace rules {

    HfstTransducer two_level_if(HfstTransducerPair &context, StringPairSet &mappings, StringPairSet &alphabet);
    HfstTransducer two_level_only_if(HfstTransducerPair &context, StringPairSet &mappings, StringPairSet &alphabet);
    HfstTransducer two_level_if_and_only_if(HfstTransducerPair &context, StringPairSet &mappings, StringPairSet &alphabet);
    HfstTransducer replace_up(HfstTransducerPair &context, HfstTransducer &mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer replace_down(HfstTransducerPair &context, HfstTransducer &mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer replace_down_karttunen(HfstTransducerPair &context, HfstTransducer &mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer replace_right(HfstTransducerPair &context, HfstTransducer &mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer replace_left(HfstTransducerPair &context, HfstTransducer &mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer replace_up(HfstTransducer &mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer replace_down(HfstTransducer &mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer left_replace_up(HfstTransducer&mapping, bool optional, StringPairSet  &alphabet);
    HfstTransducer left_replace_up( HfstTransducerPair  &context, HfstTransducer &mapping,bool optional, StringPairSet  &alphabet);
    HfstTransducer left_replace_down(HfstTransducerPair &context, HfstTransducer &mapping, bool optional, StringPairSet&alphabet);
    HfstTransducer left_replace_down_karttunen( HfstTransducerPair &context, HfstTransducer&mapping, bool optional, StringPairSet &alphabet);
    HfstTransducer left_replace_left(HfstTransducerPair &context, HfstTransducer &mapping, bool optional, StringPairSet&alphabet);
    HfstTransducer left_replace_right(HfstTransducerPair&context,HfstTransducer &mapping,bool optional,StringPairSet &alphabet);
    HfstTransducer restriction(HfstTransducerPairVector &contexts,HfstTransducer &mapping,StringPairSet &alphabet);
    HfstTransducer coercion(HfstTransducerPairVector &contexts, HfstTransducer &mapping, StringPairSet &alphabet);
    HfstTransducer restriction_and_coercion(HfstTransducerPairVector &contexts,HfstTransducer &mapping, StringPairSet &alphabet);
    HfstTransducer surface_restriction(HfstTransducerPairVector &contexts, HfstTransducer &mapping, StringPairSet &alphabet);
    HfstTransducer surface_coercion(HfstTransducerPairVector &contexts,HfstTransducer &mapping,StringPairSet &alphabet);
    HfstTransducer surface_restriction_and_coercion (HfstTransducerPairVector &contexts,HfstTransducer &mapping,StringPairSet &alphabet);
    HfstTransducer deep_restriction(HfstTransducerPairVector &contexts,HfstTransducer &mapping,StringPairSet &alphabet);
    HfstTransducer deep_coercion(HfstTransducerPairVector &contexts, HfstTransducer &mapping, StringPairSet &alphabet);
    HfstTransducer deep_restriction_and_coercion (HfstTransducerPairVector &contexts,HfstTransducer &mapping, StringPairSet &alphabet);

  }; 

class FdOperation{
public:
    FdOperation(const hfst::FdOperation&);
    static bool is_diacritic(const std::string& diacritic_str);
};

}

namespace hfst_ol{
class PmatchContainer {
public:
//    PmatchContainer(std::ifstream filename, bool verbose=false, bool extract_tags=false);
    std::string match(std::string input);
//    std::string locate(std::string input);

    // From hfst_swig_extensions
};
}
hfst_ol::PmatchContainer & load_pmatch(std::string filename);

%pythoncode %{
def lookup_clean(transducer, string):
    '''
    fd-lookup string from transducer, purge flags, return
    list of HfstPaths
    '''
    return detokenize_paths(purge_flags(transducer.lookup_fd(input)))
%}
