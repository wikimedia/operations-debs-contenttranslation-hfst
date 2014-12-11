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

namespace hfst { namespace pmatch {

class PmatchFunction;

extern char* data;
extern char* startptr;
extern size_t len;
extern std::map<std::string, HfstTransducer *> definitions;
extern std::map<std::string, HfstTransducer *> def_insed_transducers;
extern std::set<std::string> inserted_transducers;
extern std::set<std::string> unsatisfied_insertions;
extern std::set<std::string> used_definitions;
extern std::map<std::string, PmatchFunction> functions;
extern std::vector<std::string> tmp_collected_funargs;
extern ImplementationType format;
extern bool verbose;
extern bool flatten;
extern clock_t timer;
extern int minimization_guard_count;
extern bool need_delimiters;

struct PmatchUtilityTransducers;
//extern PmatchUtilityTransducers* utils;
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
HfstTransducer * get_minimization_guard(void);

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
 * @brief get a transition name for use in Ins, RC and LC statements
 */
char* get_Ins_transition(const char *s);
char* get_RC_transition(const char *s);
char* get_LC_transition(const char *s);

/**
 * @brief add special beginning and ending arcs for pmatch compatibility
 */
HfstTransducer * add_pmatch_delimiters(HfstTransducer * regex);

/**
 * @brief concatenate with an appropriate end tag transducer
 */
void add_end_tag(HfstTransducer * regex, std::string tag);
HfstTransducer * make_end_tag(std::string tag);

/**
 * @brief find first segment from strign @a s delimited by char delim.
 */
char* get_delimited(const char *s, char delim);
char* get_delimited(const char *s, char delim_left, char delim_right);
char* get_escaped_delimited(const char *s, char delim);
char* get_escaped_delimited(const char *s, char delim_left, char delim_right);
char* unescape_delimited(char *s, char delim);

char* parse_quoted(const char *s);

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

    static const char * combining_accents[] =
    {
        // Combining accents: grave, acute, circumflex, tilde, overline,
        // diaresis, charon, cedilla
        "\u0300", "\u0301", "\u0302", "\u0303", "\u0305", "\u0308", "\u030C", "\u0327",
        // Small solidus and large combining solidus
        "\u0337", "\u0338"
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
        "\u00A0",
        "\r",
        // punctuation space, thin space, line separator, par separator
        "\u2008", "\u2009", "\u2028", "\u2029"
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
    
    HfstTransducer * make_latin1_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
    HfstTransducer * make_latin1_alpha_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
    HfstTransducer * make_latin1_lowercase_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
    HfstTransducer * make_latin1_uppercase_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
    HfstTransducer * make_combining_accent_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
/** @brief Return a transducer that accepts one arabic numeral character. 
 */
    HfstTransducer * make_latin1_numeral_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
/** @brief Return a transducer that accepts one utf-8 symbol that is also a
 *  latin-1 punctuation character.
 */
    HfstTransducer * make_latin1_punct_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
/** @brief Return a transducer that accepts one utf-8 symbol that is also a
 *  latin-1 whitespace character.
 */

    HfstTransducer * make_latin1_whitespace_acceptor(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
    HfstTransducer * make_lowerfy(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
    HfstTransducer * make_capify(
        ImplementationType type = TROPICAL_OPENFST_TYPE);
    
    HfstTransducer * optcap(HfstTransducer & t);
    HfstTransducer * tolower(HfstTransducer & t);
    HfstTransducer * toupper(HfstTransducer & t);
};

enum PmatchAstOperation {
    AstAddDelimiters,
    AstConcatenate,
    AstCompose,
    AstCrossProduct,
    AstLenientCompose,
    AstOptionalize,
    AstDisjunct,
    AstIntersect,
    AstSubtract,
    AstRepeatStar,
    AstRepeatPlus,
    AstReverse,
    AstInvert,
    AstInputProject,
    AstOutputProject,
    AstRepeatN,
    AstRepeatNPlus,
    AstRepeatNMinus,
    AstRepeatNToK,
    AstOptCap,
    AstToLower,
    AstToUpper,
    None
};

enum PmatchAstType { AstTransducer, AstSymbol, AstBinaryOp, AstUnaryOp };

struct PmatchAstNode {


    PmatchAstNode * left_child;
    PmatchAstNode * right_child;
    HfstTransducer * transducer;
    PmatchAstOperation op;
    std::string symbol;
    PmatchAstType type;
    std::vector<int> numeric_args;

    PmatchAstNode(PmatchAstNode * l,
                  PmatchAstNode * r,
                  PmatchAstOperation o):
        left_child(l), right_child(r), op(o), type(AstBinaryOp),
        transducer(NULL) { }
    
    PmatchAstNode(HfstTransducer * l,
                  HfstTransducer * r,
                  PmatchAstOperation o):
        left_child(new PmatchAstNode(l)),
        right_child(new PmatchAstNode(r)),
        op(o), type(AstBinaryOp),
        transducer(NULL) { }
    
    PmatchAstNode(HfstTransducer * l,
                  PmatchAstNode * r,
                  PmatchAstOperation o):
    left_child(new PmatchAstNode(l)),
        right_child(r),
        op(o), type(AstBinaryOp),
        transducer(NULL) { }
    
    PmatchAstNode(PmatchAstNode * l,
              HfstTransducer * r,
              PmatchAstOperation o):
    left_child(l),
    right_child(new PmatchAstNode(r)),
        op(o), type(AstBinaryOp),
        transducer(NULL) { }
    
    PmatchAstNode(PmatchAstNode * l,
                  PmatchAstOperation o):
    left_child(l), right_child(NULL), op(o), type(AstUnaryOp),
        transducer(NULL) {}

    PmatchAstNode(HfstTransducer * l,
                  PmatchAstOperation o):
        left_child(new PmatchAstNode(l)), right_child(NULL), op(o), type(AstUnaryOp),
        transducer(NULL) {}

PmatchAstNode(std::string sym): symbol(sym), type(AstSymbol) {}
    
    PmatchAstNode(const HfstTransducer * t): transducer(new HfstTransducer(*t)),
    left_child(NULL), right_child(NULL), op(None), type(AstTransducer) {}
    
    PmatchAstNode(HfstTransducer & t): transducer(new HfstTransducer(t)),
    left_child(NULL), right_child(NULL), op(None), type(AstTransducer) {}
    
    ~PmatchAstNode(void) {
        delete left_child;
        delete right_child;
        delete transducer;
    }

    HfstTransducer * evaluate(std::map<std::string,
                              HfstTransducer *> & funargs);

    HfstTransducer * compile(void);

    void push_numeric_arg(int arg)
        { numeric_args.push_back(arg); }

};

struct PmatchFunction {
    std::vector<std::string> args;
    PmatchAstNode * root;
    
    PmatchFunction(std::vector<std::string> argument_vector,
                   PmatchAstNode * function_root):
    args(argument_vector), root(function_root) { }

    PmatchFunction(void) {}

    HfstTransducer * evaluate(std::map<std::string,
                              HfstTransducer *> & funargs);
};

} } // namespaces
#endif
// vim: set ft=cpp.doxygen:
