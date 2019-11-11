// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

/**
 * @file pmatch_utils.h
 *
 * @brief auxiliary functions for handling Xerox compatible regular expressions
 * (PMATCH).
 */

#ifndef GUARD_pmatch_utils_h
#define GUARD_pmatch_utils_h

#include <map>
#include <set>
#include <time.h>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "HfstTransducer.h"
#include "HfstXeroxRules.h"
#include "xre_utils.h"

#if USE_GLIB_UNICODE
#include <glib.h>
#elif USE_ICU_UNICODE
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#endif

void pmatchwarning(const char *msg);

namespace hfst { namespace pmatch {

struct PmatchFunction;
struct PmatchObject;
struct PmatchTransducerContainer;

typedef std::pair<std::string, std::string> StringPair;
typedef float WordVecFloat;
struct WordVector;

extern char* data;
extern char* startptr;
extern size_t len;
extern std::map<std::string, PmatchObject*> definitions;
extern std::map<std::string, std::string> variables;
extern std::vector<std::map<std::string, PmatchObject*> > call_stack;
extern std::map<std::string, PmatchObject*> def_insed_expressions;
extern std::set<std::string> inserted_names;
extern std::set<std::string> unsatisfied_insertions;
extern std::set<std::string> used_definitions;
extern std::set<std::string> function_names;
extern std::set<std::string> capture_names;
extern std::vector<WordVector> word_vectors;
extern ImplementationType format;
extern bool verbose;
extern bool flatten;
extern bool include_cosine_distances;
extern std::string includedir;
extern clock_t timer;
extern int minimization_guard_count;
extern bool need_delimiters;
extern WordVecFloat vector_similarity_projection_factor;

struct PmatchUtilityTransducers;
const std::string RC_ENTRY_SYMBOL = "@PMATCH_RC_ENTRY@";
const std::string RC_EXIT_SYMBOL = "@PMATCH_RC_EXIT@";
const std::string LC_ENTRY_SYMBOL = "@PMATCH_LC_ENTRY@";
const std::string LC_EXIT_SYMBOL = "@PMATCH_LC_EXIT@";
const std::string NRC_ENTRY_SYMBOL = "@PMATCH_NRC_ENTRY@";
const std::string NRC_EXIT_SYMBOL = "@PMATCH_NRC_EXIT@";
const std::string NLC_ENTRY_SYMBOL = "@PMATCH_NLC_ENTRY@";
const std::string NLC_EXIT_SYMBOL = "@PMATCH_NLC_EXIT@";
const std::string PASSTHROUGH_SYMBOL = "@PMATCH_PASSTHROUGH@";
const std::string BOUNDARY_SYMBOL = "@BOUNDARY@";
const std::string ENTRY_SYMBOL = "@PMATCH_ENTRY@";
const std::string EXIT_SYMBOL = "@PMATCH_EXIT@";

// These are used as arguments for casing functions
enum Side {
    Both,
    Upper,
    Lower
};

void add_to_pmatch_symbols(StringSet symbols);
void warn(std::string warning);
PmatchUtilityTransducers* get_utils();
void zero_minimization_guard();
bool symbol_in_global_context(std::string & sym);
bool symbol_in_local_context(std::string & sym);
PmatchObject * symbol_from_global_context(std::string & sym);
PmatchObject * symbol_from_local_context(std::string & sym);
bool string_set_has_meta_arc(StringSet & ss);
bool is_special(const std::string & symbol);

/**
 * @brief input handling function for flex that parses strings.
 */
int getinput(char *buf, int maxlen);

/**
 * @brief remove percent escaping from given string @a s.
 */
char* strip_percents(const char *s);

/**
 * @brief add percents to string to form valid PMATCH symbol.
 */
char* add_percents(const char* s);

/**
 * @brief remove final newline or CR.
 */
char* strip_newline(char *s);

/**
 * @brief get a transition name for use in Ins, RC and LC statements
 */
std::string get_Ins_transition(const char *s);
std::string get_RC_transition(const char *s);
std::string get_LC_transition(const char *s);

/**
 * @brief add special beginning and ending arcs for pmatch compatibility
 */
HfstTransducer * add_pmatch_delimiters(HfstTransducer * regex);

/**
 * @brief utility functions for making special arcs
 */
PmatchTransducerContainer * epsilon_to_symbol_container(std::string s);
PmatchTransducerContainer * make_end_tag(std::string tag);
PmatchTransducerContainer * make_capture_tag(std::string tag);
PmatchTransducerContainer * make_captured_tag(std::string tag);
PmatchObject * make_with_tag_entry(std::string key, std::string value);
PmatchObject * make_with_tag_exit(std::string key);

std::vector<std::pair<WordVector, WordVecFloat> > get_top_n(
    size_t n,
    const std::vector<WordVector> & vecs,
    WordVector & comparison_point);

std::vector<std::pair<WordVector, WordVecFloat> > get_top_n_transformed(
    size_t n,
    const std::vector<WordVector> & vecs,
    std::vector<WordVecFloat> plane_vec,
    std::vector<WordVecFloat> comparison_point,
    WordVecFloat translation_term,
    bool negative);

template<typename T> std::vector<T> pointwise_minus(std::vector<T> l,
                                                    std::vector<T> r);
template<typename T> std::vector<T> pointwise_plus(std::vector<T> l,
                                                   std::vector<T> r);
template<typename T> std::vector<T> pointwise_multiplication(T,
                                                             std::vector<T> r);
template<typename T> T dot_product(std::vector<T> l,
                                   std::vector<T> r);
template<typename T> T square_sum(std::vector<T> v);
template<typename T> T norm(std::vector<T> v);
WordVecFloat cosine_distance(WordVector left, WordVector right);
PmatchObject * compile_like_arc(std::string word1, std::string word2,
                                unsigned int nwords = 10, bool is_negative = false);
PmatchObject * compile_like_arc(std::string word,
                                unsigned int nwords = 10);

PmatchTransducerContainer * make_counter(std::string name);

StringSet get_non_special_alphabet(HfstTransducer * t);
HfstTransducer * make_list(HfstTransducer * t,
                           ImplementationType f = format);
HfstTransducer * make_exc_list(HfstTransducer * t,
                               ImplementationType f = format);
HfstTransducer * make_sigma(HfstTransducer * t);
PmatchTransducerContainer * make_minimization_guard();
PmatchTransducerContainer * make_passthrough();
PmatchTransducerContainer * make_rc_entry();
PmatchTransducerContainer * make_lc_entry();
PmatchTransducerContainer * make_nrc_entry();
PmatchTransducerContainer * make_nlc_entry();
PmatchTransducerContainer * make_rc_exit();
PmatchTransducerContainer * make_lc_exit();
PmatchTransducerContainer * make_nrc_exit();
PmatchTransducerContainer * make_nlc_exit();

/**
 * @brief find first segment from strign @a s delimited by char delim.
 */
char* get_delimited(const char *s, char delim);
char* get_delimited(const char *s, char delim_left, char delim_right);
char* get_escaped_delimited(const char *s, char delim);
char* get_escaped_delimited(const char *s, char delim_left, char delim_right);
char* unescape_delimited(char *s, char delim);

char* parse_quoted(const char *s);

unsigned int next_utf8_to_codepoint(unsigned char **c);
std::string codepoint_to_utf8(unsigned int codepoint);
PmatchTransducerContainer * parse_range(const char *s);

int* get_n_to_k(const char* s);

double get_weight(const char* s);

void init_globals();

string expand_includes(const string & script);

/**
 * @brief compile new transducer
 */
std::map<std::string, HfstTransducer*>
    compile(const std::string& pmatch,
            std::map<std::string,hfst::HfstTransducer*>& defs,
            hfst::ImplementationType type,
            bool be_verbose = false, bool do_flatten = false,
            bool include_cosine_distances = false,
            std::string includedir = "");

void print_size_info(HfstTransducer * net);

/**
 * @brief Given a text file, read it line by line and return an acceptor
 * of a disjunction of the lines
 */
HfstTransducer * read_text(std::string filename,
                           ImplementationType type = TROPICAL_OPENFST_TYPE,
                           bool spaced_text = false);

HfstTransducer * read_spaced_text(std::string filename,
                                  ImplementationType type = TROPICAL_OPENFST_TYPE);

/**
 * @brief Concatenate include directory with filename to get a real path
 * (unless the filename is already an absolute path)
 */
std::string path_from_filename(const char * filename);

struct WordVector
{
    std::string word;
    std::vector<WordVecFloat> vector;
    WordVecFloat norm;
};

/**
 * @brief Given a list of words and their vector representations, parse it into
 * hfst::pmatch::word_vectors
 */
void read_vec(std::string filename);

/**
 * @brief Given a text file, read it line by line and return a tokenized
 * list of arguments for a function to be applied on
 */
std::vector<std::vector<std::string> > read_args(char * filename, unsigned int argcount);

/** @brief Return a transducer that accepts a single string from an array of
 *  char *.
 */

/* First some magic templates for compile-time length checking */

template<typename T, size_t N>
    HfstTransducer * acceptor_from_cstr(
        T (&strings)[N],
        ImplementationType type) {
    HfstTokenizer tok;
    HfstTransducer * retval = new HfstTransducer(type);
    for (size_t i = 0; i < N; ++i) {
        retval->disjunct(HfstTransducer(strings[i], tok, type));
    }
    retval->minimize();
    return retval;
}

template<typename T, size_t N>
    size_t array_len(T(&strings)[N]) {
    return N;
}

// It is assumed that latin1_upper and latin1_lower have the same length!

    static const char * latin1_upper[] =
    {
        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
        "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "À", "Á",
        "Â", "Ã", "Ä", "Å", "Æ", "Ç", "È", "É", "Ê", "Ë", "Ì", "Í", "Î", "Ï",
        "Ð", "Ñ", "Ò", "Ó", "Ô", "Õ", "Ö", "Ø", "Ù", "Ú", "Û", "Ü", "Ý", "Þ",
        "ẞ"
    };

    static const char * latin1_lower[] =
    {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
        "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "à", "á",
        "â", "ã", "ä", "å", "æ", "ç", "è", "é", "ê", "ë", "ì", "í", "î", "ï",
        "ð", "ñ", "ò", "ó", "ô", "õ", "ö", "ø", "ù", "ú", "û", "ü", "ý", "þ",
        "ß"
    };

    // MSVC compiler complains about \u strings...

    static const char * combining_accents[] =
    {
        // Combining accents: grave, acute, circumflex, tilde, overline,
        // diaresis, charon, cedilla
#ifndef _MSC_VER
        "\u0300", "\u0301", "\u0302", "\u0303", "\u0305", "\u0308", "\u030C", "\u0327",
#else
        "\xCC\x80", "\xCC\x81", "\xCC\x82", "\xCC\x83", "\xCC\x85", "\xCC\x88", "\xCC\x8C", "\xCC\xA7",
#endif

        // Small solidus and large combining solidus
#ifndef _MSC_VER
        "\u0337", "\u0338"
#else
        "\xCC\xB7", "\xCC\xB8"
#endif
    };

    static const char * latin1_punct[] =
    {
        "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".",
        "/", ":", ";", "<", "=", ">", "?", "@", "[", "\\", "]", "^", "_",
        "{", "|", "}", "~", "`", "´", "¡", "«", "»", "¿"
    };

    static const char * latin1_whitespace[] =
    {
        " ", "\n", "\t",
        // Non-breaking space, CR
#ifndef _MSC_VER
        "\u00A0",
#else
        "\xC2\xA0",
#endif
        "\r",
        // punctuation space, thin space, line separator, par separator
#ifndef _MSC_VER
        "\u2008", "\u2009", "\u2028", "\u2029"
#else
        "\xE2\x80\x88", "\xE2\x80\x89", "\xE2\x80\xA8", "\xE2\x80\xA9"
#endif
    };


struct PmatchUtilityTransducers
{
    PmatchUtilityTransducers();
    ~PmatchUtilityTransducers();
    /**
     * Character class acceptors
     */

    const HfstTransducer * latin1_acceptor;
    const HfstTransducer * latin1_alpha_acceptor;
    const HfstTransducer * latin1_lowercase_acceptor;
    const HfstTransducer * latin1_uppercase_acceptor;
    const HfstTransducer * combining_accent_acceptor;
    const HfstTransducer * latin1_numeral_acceptor;
    const HfstTransducer * latin1_punct_acceptor;
    const HfstTransducer * latin1_whitespace_acceptor;
    const HfstTransducer * capify;
    const HfstTransducer * lowerfy;

    static HfstTransducer * make_latin1_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

    static HfstTransducer * make_latin1_alpha_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

    static HfstTransducer * make_latin1_lowercase_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

    static HfstTransducer * make_latin1_uppercase_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

    static HfstTransducer * make_combining_accent_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

/** @brief Return a transducer that accepts one arabic numeral character.
 */
    static HfstTransducer * make_latin1_numeral_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

/** @brief Return a transducer that accepts one utf-8 symbol that is also a
 *  latin-1 punctuation character.
 */
    static HfstTransducer * make_latin1_punct_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

/** @brief Return a transducer that accepts one utf-8 symbol that is also a
 *  latin-1 whitespace character.
 */

    static HfstTransducer * make_latin1_whitespace_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

    HfstTransducer * make_lowerfy(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

    HfstTransducer * make_capify(
        ImplementationType type = TROPICAL_OPENFST_TYPE);

    // Unicode handling, if available
    #if USE_GLIB_UNICODE
    std::string string_from_g_unichar(gunichar ch);
    #endif
    HfstTransducer get_uppercase_acceptor_from_transducer(HfstTransducer & t);
    HfstTransducer get_lowercase_acceptor_from_transducer(HfstTransducer & t);
    HfstTransducer uppercaser_from_transducer(HfstTransducer & t);
    HfstTransducer lowercaser_from_transducer(HfstTransducer & t);
    
    HfstTransducer * cap(HfstTransducer & t, Side side = Both,
                         bool optional = false);
    HfstTransducer * tolower(HfstTransducer & t, Side side = Both,
                             bool optional = false);
    HfstTransducer * toupper(HfstTransducer & t, Side side = Both,
                             bool optional = false );
};

struct PmatchObject {
    std::string name; // optional, given if the object appears as a definition
    double weight;
    int line_defined;
    clock_t my_timer;
    HfstTransducer * cache;
    bool parent_is_context;
    PmatchObject();
    virtual ~PmatchObject() throw() = default;
    void start_timing()
        {
            if (verbose && name != "") {
                my_timer = clock();
            }
        }
    void report_time()
        {
            if (verbose && name != "") {
                double duration = (clock() - my_timer) /
                    (double) CLOCKS_PER_SEC;
                std::cerr << name << " compiled in " << duration << " seconds\n";

            }
        }
    bool should_use_cache()
        {
            return name != "" && call_stack.size() == 0;
        }

    virtual bool is_unweighted_disjunction_of_strings()
        { return false; }
    virtual void collect_strings_into(StringVector & strings) { return; }
    virtual void collect_initial_symbols_into(
        StringSet & allowed, StringSet & disallowed);
    virtual StringSet get_real_initial_symbols();
    virtual StringSet get_real_initial_symbols_from_right();
    virtual bool is_left_concatenation_with_context();
    virtual bool is_context();
    virtual bool is_delimiter();
    virtual StringSet get_initial_symbols_from_unary_root();
    virtual StringSet get_initial_RC_initial_symbols();
    virtual StringSet get_initial_NRC_initial_symbols();
    void expand_Ins_arcs(StringSet & ss);
    virtual HfstTransducer * evaluate() = 0;
    virtual HfstTransducer * evaluate(std::vector<PmatchObject *> args);
    virtual PmatchObject * evaluate_as_arg();
    virtual void mark_context_children() { parent_is_context = true; }
    virtual std::string as_string() { return ""; }
    virtual StringPair as_string_pair()
        { return StringPair("", ""); }
};

struct PmatchSymbol: public PmatchObject {
    // This handles argumentless function calls and definition invocations,
    // which are the same thing under the hood.
    std::string sym;
    PmatchSymbol(std::string str): sym(str) { }
    HfstTransducer * evaluate();
    void collect_strings_into(StringVector & strings);
    PmatchObject * evaluate_as_arg(void);
    std::string as_string(void) { return sym; }
};

struct PmatchString: public PmatchObject {
    std::string string;
    bool multichar;
    PmatchString(std::string str, bool is_multichar = false):
        string(str), multichar(is_multichar) { }
    HfstTransducer * evaluate();
    std::string as_string() { return string; }
    StringPair as_string_pair()
        { return StringPair(string, string); }
    bool is_unweighted_disjunction_of_strings()
        { return weight == 0.0 && (multichar || (string.size() < 2)); }
    void collect_strings_into(StringVector & strings);
    PmatchObject * evaluate_as_arg();
};

struct PmatchQuestionMark: public PmatchObject {
    HfstTransducer * evaluate();
    std::string as_string() { return hfst::internal_unknown; }
    StringPair as_string_pair()
        { return StringPair(
                hfst::internal_identity, hfst::internal_identity); }
};

enum PmatchUnaryOp {
    AddDelimiters,
    Optionalize,
    RepeatStar,
    RepeatPlus,
    Reverse,
    Invert,
    InputProject,
    OutputProject,
    Complement,
    Containment,
    ContainmentOnce,
    ContainmentOptional,
    TermComplement,
    Cap,
    OptCap,
    ToLower,
    ToUpper,
    OptToLower,
    OptToUpper,
    AnyCase,
    CapUpper,
    OptCapUpper,
    ToLowerUpper,
    ToUpperUpper,
    OptToLowerUpper,
    OptToUpperUpper,
    AnyCaseUpper,
    CapLower,
    OptCapLower,
    ToLowerLower,
    ToUpperLower,
    OptToLowerLower,
    OptToUpperLower,
    AnyCaseLower,
    MakeSigma,
    MakeList,
    MakeExcList,
    LC,
    NLC,
    RC,
    NRC,
    Explode,
    Implode
};

enum PmatchBinaryOp {
    Concatenate,
    Compose,
    CrossProduct,
    LenientCompose,
    Disjunct,
    Intersect,
    Subtract,
    UpperSubtract,
    LowerSubtract,
    UpperPriorityUnion,
    LowerPriorityUnion,
    Shuffle,
    Before,
    After,
    InsertFreely,
    IgnoreInternally,
    Merge
};

enum PmatchTernaryOp {
    Substitute
};

enum PmatchNumericOp {
    RepeatN,
    RepeatNPlus,
    RepeatNMinus,
    RepeatNToK
};

enum PmatchPredefined {
    Alpha,
    UppercaseAlpha,
    LowercaseAlpha,
    Numeral,
    Punctuation,
    Whitespace
};

enum PmatchBuiltin {
    Interpolate
};

struct PmatchNumericOperation: public PmatchObject{
    PmatchNumericOp op;
    PmatchObject * root;
    std::vector<int> values;
    PmatchNumericOperation(PmatchNumericOp _op, PmatchObject * _root):
        op(_op), root(_root) {}
    HfstTransducer * evaluate();
    void mark_context_children()
        {
            parent_is_context = true;
            root->mark_context_children();
        }
};

struct PmatchUnaryOperation: public PmatchObject{
    PmatchUnaryOp op;
    PmatchObject * root;
    PmatchUnaryOperation(PmatchUnaryOp _op, PmatchObject * _root):
        op(_op), root(_root) {}
    HfstTransducer * evaluate();
    StringSet get_initial_RC_initial_symbols();
    StringSet get_initial_NRC_initial_symbols();
    bool is_context();
    bool is_delimiter();
    StringSet get_initial_symbols_from_unary_root();
    void mark_context_children()
        {
            parent_is_context = true;
            root->mark_context_children();
        }
};

struct PmatchBinaryOperation: public PmatchObject{
    PmatchBinaryOp op;
    PmatchObject * left;
    PmatchObject * right;
    PmatchBinaryOperation(PmatchBinaryOp _op, PmatchObject * _left, PmatchObject * _right):
        op(_op), left(_left), right(_right) {}
    HfstTransducer * evaluate();
    StringPair as_string_pair();
    bool is_unweighted_disjunction_of_strings();
    void collect_strings_into(StringVector & strings);
    StringSet get_real_initial_symbols_from_right();
    bool is_left_concatenation_with_context();
    StringSet get_initial_RC_initial_symbols();
    StringSet get_initial_NRC_initial_symbols();
    void mark_context_children()
        {
            parent_is_context = true;
            left->mark_context_children();
            right->mark_context_children();
        }
};

struct PmatchTernaryOperation: public PmatchObject{
    PmatchTernaryOp op;
    PmatchObject * left;
    PmatchObject * middle;
    PmatchObject * right;
    PmatchTernaryOperation(PmatchTernaryOp _op, PmatchObject * _left, PmatchObject * _middle, PmatchObject * _right):
        op(_op), left(_left), middle(_middle), right(_right) {}
    HfstTransducer * evaluate();
    void mark_context_children()
        {
            parent_is_context = true;
            left->mark_context_children();
            middle->mark_context_children();
            right->mark_context_children();
        }
};

struct PmatchTransducerContainer: public PmatchObject{
    HfstTransducer * t;
    PmatchTransducerContainer(HfstTransducer * target):
        t(target) {}
    ~PmatchTransducerContainer() throw() { delete t; }
    HfstTransducer * evaluate() {
        if (t->get_type() != format) {
            t->convert(format);
        }
        HfstTransducer * retval = new HfstTransducer(*t);
        retval->set_final_weights(hfst::double_to_float(weight), true);
        if (name != "") {
            retval->set_name(name);
        }
        return retval;
    }
};

struct PmatchFunction: public PmatchObject {
    std::vector<std::string> args;
    PmatchObject * root;

    PmatchFunction(std::vector<std::string> argument_vector,
                   PmatchObject * function_root):
    args(argument_vector), root(function_root) { }

    HfstTransducer * evaluate(std::vector<PmatchObject *> funargs);
    HfstTransducer * evaluate();

};

struct PmatchFuncall: public PmatchObject {
    std::vector<PmatchObject * >* args;
    PmatchFunction * fun;
    PmatchFuncall(std::vector<PmatchObject *>* argument_vector,
                  PmatchFunction * function): args(argument_vector),
                                              fun(function) { }
    HfstTransducer * evaluate();
    void mark_context_children()
        {
            for (std::vector<PmatchObject *>::iterator it = args->begin();
                 it != args->end(); ++it) {
                (*it)->mark_context_children();
            }
            parent_is_context = true;
        }
};

struct PmatchBuiltinFunction: public PmatchObject {
    std::vector<PmatchObject *>* args;
    PmatchBuiltin type;
    PmatchBuiltinFunction(PmatchBuiltin _type,
                          std::vector<PmatchObject*>* argument_vector):
    args(argument_vector), type(_type) {}
    HfstTransducer * evaluate();
    void mark_context_children()
        {
            parent_is_context = true;
            for (std::vector<PmatchObject *>::iterator it = args->begin();
                 it != args->end(); ++it) {
                (*it)->mark_context_children();
            }
        }
};

using hfst::xeroxRules::ReplaceArrow;
using hfst::xeroxRules::ReplaceType;

typedef std::pair<HfstTransducer*, HfstTransducer*> TransducerPointerPair;

struct PmatchObjectPair
{
    PmatchObject * left;
    PmatchObject * right;
    PmatchObjectPair(PmatchObject * l, PmatchObject * r): left(l), right(r) {}
    virtual TransducerPointerPair evaluate_pair() {
        TransducerPointerPair retval;
        retval.first = left->evaluate();
        retval.second = right->evaluate();
        return retval;
    }
    virtual ~PmatchObjectPair() { delete left; delete right; }
};

typedef std::vector<PmatchObjectPair*> MappingPairVector;

struct PmatchRestrictionContainer: public PmatchObject
{
    PmatchObject * left;
    MappingPairVector * contexts;
    PmatchRestrictionContainer(PmatchObject * l, MappingPairVector * c):
        left(l), contexts(c) { }
    HfstTransducer * evaluate();
    void mark_context_children()
        {
            parent_is_context = true;
            left->mark_context_children();
        }
};

struct PmatchMarkupContainer: public PmatchObjectPair
{
    PmatchObject * left_of_arrow;
    PmatchMarkupContainer(PmatchObject * loa, PmatchObject * lom, PmatchObject * rom):
        PmatchObjectPair(lom, rom), left_of_arrow(loa) {}
    TransducerPointerPair evaluate_pair() override;
    ~PmatchMarkupContainer() { delete left_of_arrow; }
};

struct PmatchMappingPairsContainer: public PmatchObject
{
    ReplaceArrow arrow;
    MappingPairVector mapping_pairs;
    PmatchMappingPairsContainer(ReplaceArrow a, MappingPairVector pairs):
        arrow(a), mapping_pairs(pairs) {}
    PmatchMappingPairsContainer(ReplaceArrow a,
                                PmatchObject * left, PmatchObject * right):
        arrow(a) { mapping_pairs.push_back(new PmatchObjectPair(left, right)); }
    PmatchMappingPairsContainer(ReplaceArrow a,
                                PmatchObjectPair * pair):
        arrow(a) { mapping_pairs.push_back(pair); }
    void push_back(PmatchMappingPairsContainer * one_pair)
        {
            for(MappingPairVector::iterator it = one_pair->mapping_pairs.begin();
                it != one_pair->mapping_pairs.end(); ++it) {
                mapping_pairs.push_back(new PmatchObjectPair(
                                            (*it)->left, (*it)->right));
            }
        }
    HfstTransducer * evaluate();
};

struct PmatchContextsContainer: public PmatchObject
{
    ReplaceType type;
    MappingPairVector context_pairs;
    PmatchContextsContainer(ReplaceType t, MappingPairVector pairs):
        type(t), context_pairs(pairs) {}
    PmatchContextsContainer(ReplaceType t, PmatchContextsContainer * context):
        type(t), context_pairs(context->context_pairs)
        { /* check for type compatibility */ }
    PmatchContextsContainer(PmatchContextsContainer * context):
        type(context->type), context_pairs(context->context_pairs) {}
    PmatchContextsContainer(PmatchObject * left, PmatchObject * right)
        { context_pairs.push_back(new PmatchObjectPair(left, right)); }
    void push_back(PmatchContextsContainer * one_context)
        {
            for(MappingPairVector::iterator it = one_context->context_pairs.begin();
                it != one_context->context_pairs.end(); ++it) {
                context_pairs.push_back(new PmatchObjectPair(
                                            (*it)->left, (*it)->right));
            }
        }
    HfstTransducer * evaluate();
};

struct PmatchReplaceRuleContainer: public PmatchObject
{
    ReplaceArrow arrow;
    ReplaceType type;
    MappingPairVector mapping;
    MappingPairVector context;
    PmatchReplaceRuleContainer(
        ReplaceArrow a,
        ReplaceType t,
        MappingPairVector m,
        MappingPairVector c):
        arrow(a), type(t), mapping(m), context(c) {}
    PmatchReplaceRuleContainer(PmatchMappingPairsContainer * pairs):
        arrow(pairs->arrow), mapping(pairs->mapping_pairs) {}
    PmatchReplaceRuleContainer(PmatchMappingPairsContainer * pairs,
                               PmatchContextsContainer * contexts):
        arrow(pairs->arrow), type(contexts->type),
          mapping(pairs->mapping_pairs), context(contexts->context_pairs) {}
    hfst::xeroxRules::Rule make_mapping();
    HfstTransducer * evaluate();
};

struct PmatchParallelRulesContainer: public PmatchObject
{
    ReplaceArrow arrow;
    std::vector<PmatchReplaceRuleContainer *> rules;
    PmatchParallelRulesContainer(PmatchReplaceRuleContainer * rule):
        arrow(rule->arrow), rules(1, rule) {}
    std::vector<hfst::xeroxRules::Rule> make_mappings();
    HfstTransducer * evaluate();
};

struct PmatchEpsilonArc: public PmatchObject
{
    HfstTransducer * evaluate()
        { return new HfstTransducer(hfst::internal_epsilon, format); }
    std::string as_string() { return hfst::internal_epsilon; }
};

struct PmatchEmpty: public PmatchObject
{
    HfstTransducer * evaluate()
        { return new HfstTransducer(format); }
};

struct PmatchAcceptor: public PmatchObject
{
    PmatchPredefined set;
    PmatchAcceptor(PmatchPredefined s): set(s) {}
    HfstTransducer * evaluate();
};

} } // namespaces
#endif
// vim: set ft=cpp.doxygen:
