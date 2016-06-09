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
#include "HfstTransducer.h"
#include "HfstXeroxRules.h"
#include "xre_utils.h"

void pmatchwarning(const char *msg);

namespace hfst { namespace pmatch {

struct PmatchFunction;
struct PmatchObject;
struct PmatchTransducerContainer;

typedef std::pair<std::string, std::string> StringPair;

extern char* data;
extern char* startptr;
extern size_t len;
extern std::map<std::string, PmatchObject*> definitions;
extern std::vector<std::map<std::string, PmatchObject*> > call_stack;
extern std::map<std::string, PmatchObject*> def_insed_expressions;
extern std::set<std::string> inserted_names;
extern std::set<std::string> unsatisfied_insertions;
extern std::set<std::string> used_definitions;
extern std::set<std::string> function_names;
extern ImplementationType format;
extern bool verbose;
extern bool flatten;
extern clock_t timer;
extern clock_t tmp_timer;
extern int minimization_guard_count;
extern bool need_delimiters;

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

void add_to_pmatch_symbols(StringSet symbols);
void warn(std::string warning);
PmatchUtilityTransducers* get_utils();
void zero_minimization_guard(void);
bool symbol_in_global_context(std::string & sym);
bool symbol_in_local_context(std::string & sym);
bool should_use_cache(void);
PmatchObject * symbol_from_global_context(std::string & sym);
PmatchObject * symbol_from_local_context(std::string & sym);

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
PmatchTransducerContainer * make_counter(std::string name);
HfstTransducer * make_list(HfstTransducer * t,
                           ImplementationType f = format);
HfstTransducer * make_exc_list(HfstTransducer * t,
                               ImplementationType f = format);
HfstTransducer * make_sigma(HfstTransducer * t);
PmatchTransducerContainer * make_minimization_guard(void);
PmatchTransducerContainer * make_passthrough(void);
PmatchTransducerContainer * make_rc_entry(void);
PmatchTransducerContainer * make_lc_entry(void);
PmatchTransducerContainer * make_nrc_entry(void);
PmatchTransducerContainer * make_nlc_entry(void);
PmatchTransducerContainer * make_rc_exit(void);
PmatchTransducerContainer * make_lc_exit(void);
PmatchTransducerContainer * make_nrc_exit(void);
PmatchTransducerContainer * make_nlc_exit(void);

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

void init_globals(void);

/**
 * @brief compile new transducer
 */
std::map<std::string, HfstTransducer*>
    compile(const std::string& pmatch,
            std::map<std::string,hfst::HfstTransducer*>& defs,
            hfst::ImplementationType type,
            bool be_verbose, bool do_flatten);

void print_size_info(HfstTransducer * net);

/**
 * @brief Given a text file, read it line by line and return an acceptor
 * of a disjunction of the lines
 */
HfstTransducer * read_text(char * filename,
                           ImplementationType type = TROPICAL_OPENFST_TYPE);

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
    
    HfstTransducer * cap(HfstTransducer & t);
    HfstTransducer * optcap(HfstTransducer & t);
    HfstTransducer * tolower(HfstTransducer & t);
    HfstTransducer * toupper(HfstTransducer & t);
    HfstTransducer * opt_tolower(HfstTransducer & t);
    HfstTransducer * opt_toupper(HfstTransducer & t);
};

struct PmatchObject;

enum PmatchEvalType {
    InputSide,
    OutputSide,
    Transducer
};

struct PmatchObject {
    std::string name; // optional, given if the object appears as a definition
    double weight;
    int line_defined;
    HfstTransducer * cache;
    PmatchObject(void);
    void start_timing(void)
        {
            if (verbose && name != "") {
                tmp_timer = clock();
            }
        }
    void report_time(void)
        {
            if (verbose && name != "") {
                double duration = (clock() - tmp_timer) /
                    (double) CLOCKS_PER_SEC;
                std::cerr << name << " compiled in " << duration << " seconds\n";
            }
        }
    virtual HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer) = 0;
    virtual HfstTransducer * evaluate(std::vector<PmatchObject *> args);
    virtual std::string as_string(void) { return ""; }
    virtual StringPair as_string_pair(void)
        { return StringPair("", ""); }
};

struct PmatchSymbol: public PmatchObject {
    // This handles argumentless function calls and definition invocations,
    // which are the same thing under the hood.
    std::string sym;
    PmatchSymbol(std::string str): sym(str) { }
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchString: public PmatchObject {
    std::string string;
    bool multichar;
    PmatchString(std::string str, bool is_multichar = false):
        string(str), multichar(is_multichar) {}
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
    std::string as_string(void) { return string; }
    StringPair as_string_pair(void)
        { return StringPair(string, string); }
};

struct PmatchQuestionMark: public PmatchObject {
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
    std::string as_string(void) { return hfst::internal_unknown; }
    StringPair as_string_pair(void)
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
    MakeSigma,
    MakeList,
    MakeExcList
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
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchUnaryOperation: public PmatchObject{
    PmatchUnaryOp op;
    PmatchObject * root;
    PmatchUnaryOperation(PmatchUnaryOp _op, PmatchObject * _root):
        op(_op), root(_root) {}
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchBinaryOperation: public PmatchObject{
    PmatchBinaryOp op;
    PmatchObject * left;
    PmatchObject * right;
    PmatchBinaryOperation(PmatchBinaryOp _op, PmatchObject * _left, PmatchObject * _right):
        op(_op), left(_left), right(_right) {}
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
    StringPair as_string_pair(void);
};

struct PmatchTernaryOperation: public PmatchObject{
    PmatchTernaryOp op;
    PmatchObject * left;
    PmatchObject * middle;
    PmatchObject * right;
    PmatchTernaryOperation(PmatchTernaryOp _op, PmatchObject * _left, PmatchObject * _middle, PmatchObject * _right):
        op(_op), left(_left), middle(_middle), right(_right) {}
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchTransducerContainer: public PmatchObject{
    HfstTransducer * t;
    PmatchTransducerContainer(HfstTransducer * target):
        t(target) {}
    ~PmatchTransducerContainer(void) { delete t; }
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer) {
        if (t->get_type() != format) {
            t->convert(format);
        }
        HfstTransducer * retval = new HfstTransducer(*t);
        retval->set_final_weights(weight, true);
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
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchFuncall: public PmatchObject {
    std::vector<PmatchObject * >* args;
    PmatchFunction * fun;
    PmatchFuncall(std::vector<PmatchObject *>* argument_vector,
                  PmatchFunction * function): args(argument_vector),
                                              fun(function) { }
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer)
        {
            std::vector<PmatchObject * > evaluated_args;
            for (std::vector<PmatchObject *>::iterator it = args->begin();
                 it != args->end(); ++it) {
                evaluated_args.push_back(
                    new PmatchTransducerContainer((*it)->evaluate()));
            }
            HfstTransducer * retval = fun->evaluate(evaluated_args);
            for (std::vector<PmatchObject *>::iterator it =
                     evaluated_args.begin(); it != evaluated_args.end();
                 ++it) {
                delete static_cast<PmatchTransducerContainer*>(*it);
            }
            return retval;
        }
};

struct PmatchBuiltinFunction: public PmatchObject {
    std::vector<PmatchObject *>* args;
    PmatchBuiltin type;
    PmatchBuiltinFunction(PmatchBuiltin _type,
                          std::vector<PmatchObject*>* argument_vector):
        type(_type), args(argument_vector) {}
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

using hfst::xeroxRules::ReplaceArrow;
using hfst::xeroxRules::ReplaceType;
typedef std::pair<PmatchObject *, PmatchObject *> PmatchObjectPair;
typedef std::vector<PmatchObjectPair> MappingPairVector;

struct PmatchRestrictionContainer: public PmatchObject
{
    PmatchObject * left;
    MappingPairVector * contexts;
    PmatchRestrictionContainer(PmatchObject * l, MappingPairVector * c):
        left(l), contexts(c) { }
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchMarkupContainer: public PmatchObject
{
    PmatchObject * left;
    PmatchObject * right;
    PmatchMarkupContainer(PmatchObject * l, PmatchObject * r):
        left(l), right(r) {}
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchMappingPairsContainer: public PmatchObject
{
    ReplaceArrow arrow;
    MappingPairVector mapping_pairs;
    PmatchMarkupContainer * markup_marks;
    PmatchMappingPairsContainer(ReplaceArrow a, MappingPairVector pairs):
        arrow(a), mapping_pairs(pairs) {}
    PmatchMappingPairsContainer(ReplaceArrow a,
                                PmatchObject * left, PmatchObject * right):
        arrow(a) { mapping_pairs.push_back(PmatchObjectPair(left, right)); }
    void push_back(PmatchMappingPairsContainer * one_pair)
        {
            for(MappingPairVector::iterator it = one_pair->mapping_pairs.begin();
                it != one_pair->mapping_pairs.end(); ++it) {
                mapping_pairs.push_back(PmatchObjectPair(
                                            it->first, it->second));
            }
        }
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
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
        { context_pairs.push_back(PmatchObjectPair(left, right)); }
    void push_back(PmatchContextsContainer * one_context)
        {
            for(MappingPairVector::iterator it = one_context->context_pairs.begin();
                it != one_context->context_pairs.end(); ++it) {
                context_pairs.push_back(PmatchObjectPair(
                                            it->first, it->second));
            }
        }
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
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
        arrow(pairs->arrow), mapping(pairs->mapping_pairs),
        context(contexts->context_pairs), type(contexts->type) {}
    hfst::xeroxRules::Rule make_mapping(void);
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchParallelRulesContainer: public PmatchObject
{
    ReplaceArrow arrow;
    std::vector<PmatchReplaceRuleContainer *> rules;
    PmatchParallelRulesContainer(PmatchReplaceRuleContainer * rule):
        arrow(rule->arrow), rules(1, rule) {}
    std::vector<hfst::xeroxRules::Rule> make_mappings(void);
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

struct PmatchEpsilonArc: public PmatchObject
{
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer)
        { return new HfstTransducer(hfst::internal_epsilon, format); }
    std::string as_string(void) { return hfst::internal_epsilon; }
};

struct PmatchEmpty: public PmatchObject
{
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer)
        { return new HfstTransducer(format); }
};

struct PmatchAcceptor: public PmatchObject
{
    PmatchPredefined set;
    PmatchAcceptor(PmatchPredefined s): set(s) {}
    HfstTransducer * evaluate(PmatchEvalType eval_type = Transducer);
};

} } // namespaces
#endif
// vim: set ft=cpp.doxygen:
