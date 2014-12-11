/**
 * @file pmatch.cc
 *
 * @brief implements pmatch routines.
 */

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include "pmatch_utils.h"
#include "HfstTransducer.h"
#include "tools/src/HfstUtf8.h"

using std::string;
using std::map;

extern int pmatchlineno;
extern char* pmatchtext;
extern int pmatchparse();
extern int pmatchnerrs;

int
pmatcherror(const char *msg)
{
#ifndef NDEBUG
    fprintf(stderr, "*** pmatch parsing failed: %s\n", msg);
    if (strlen(hfst::pmatch::data) < 60)
    {
        fprintf(stderr, "*** parsing %s [line %d, near %s]\n",
                hfst::pmatch::data, pmatchlineno, pmatchtext);
    }
    else
    {
        char buf[200];
        memcpy(buf, hfst::pmatch::data, 200 - 1);
        buf[200 - 1] = '\0';
        fprintf(stderr, "***    parsing %s [line %d, near %s]...\n", 
                buf, pmatchlineno, pmatchtext);
    }
#endif
    exit(0);

}

namespace hfst 
{ 
namespace pmatch 
{

char* data;
std::map<std::string, hfst::HfstTransducer*> definitions;
std::map<std::string, hfst::HfstTransducer*> def_insed_transducers;
std::set<std::string> inserted_transducers;
std::set<std::string> unsatisfied_insertions;
std::set<std::string> used_definitions;
std::map<std::string, PmatchFunction> functions;
std::vector<std::string> tmp_collected_funargs;
char* startptr;
hfst::ImplementationType format;
size_t len;
bool verbose;
bool flatten;
clock_t timer;
int minimization_guard_count;
bool need_delimiters;

std::map<std::string, hfst::HfstTransducer> named_transducers;
PmatchUtilityTransducers* utils=NULL;

void warn(std::string warning)
{
    std::cerr << "pmatch: warning: " << warning;
}

PmatchUtilityTransducers*
get_utils()
{
  if (utils == NULL) 
    {
      utils = new PmatchUtilityTransducers(); 
    }
  return utils;
}

void zero_minimization_guard(void)
{
    minimization_guard_count = 0;
}

HfstTransducer * get_minimization_guard(void)
{
    std::stringstream guard;
    if(minimization_guard_count == 0) {
        guard << hfst::internal_epsilon;
    } else {
        guard << "@PMATCH_GUARD_" << minimization_guard_count << "@";
    }
    ++minimization_guard_count;
    return new HfstTransducer(hfst::internal_epsilon, guard.str(), format);
}

int*
get_n_to_k(const char* s)
{
    int* rv = static_cast<int*>(malloc(sizeof(int)*2));
    char *endptr;
    char *finalptr;
    if (*(s + 1) == '{')
      {
        rv[0] = strtol(s + 2, &endptr, 10);
        rv[1] = strtol(endptr + 1, &finalptr, 10);
        assert(*finalptr == '}');
      }
    else
      {
        rv[0] = strtol(s + 1, &endptr, 10);
        rv[1] = strtol(endptr + 1, &finalptr, 10);
        assert(*finalptr == '\0');
      }
    return rv;
}



int
getinput(char *buf, int maxlen)
{
    int retval = 0;
    if ( maxlen > len ) {
        maxlen = len;
    }
    memcpy(buf, data, maxlen);
    data += maxlen;
    len -= maxlen;
    retval = maxlen;
    return retval;
}

char*
strip_percents(const char *s)
{
    const char *c = s;
    char *stripped = (char*)calloc(sizeof(char),strlen(s)+1);
    size_t i = 0;
    while (*c != '\0')
    {
        if (*c == '%')
        {
            if (*(c + 1) == '\0')
            {
                break;
            }
            else
            {
                stripped[i] = *(c + 1);
                i++;
                c += 2;
            }
        }
        else
        {
            stripped[i] = *c;
            i++;
            c++;
        }
    }
    stripped[i] = '\0';
    return stripped;
}

char*
add_percents(const char *s)
  {
    char* ns = static_cast<char*>(malloc(sizeof(char)*strlen(s)*2+1));
    char* p = ns;
    while (*s != '\0')
      {
        if ((*s == '@') || (*s == '-') || (*s == ' ') || (*s == '|') ||
            (*s == '!') || (*s == ':') || (*s == ';') || (*s == '0') ||
            (*s == '\\') || (*s == '&') || (*s == '?') || (*s == '$') ||
            (*s == '+') || (*s == '*') || (*s == '/') || (*s == '/') ||
            (*s == '_') || (*s == '(') || (*s == ')') || (*s == '{') ||
            (*s == '}') || (*s == '[') || (*s == ']'))
          {
            *p = '%';
            p++;
          }
        *p = *s;
        p++;
        s++;
      }
    *p = '\0';
    return ns;
  }

char *
get_Ins_transition(const char *s)
{
    char* rv = static_cast<char*>(malloc(sizeof(char)*(strlen(s) + 4 + 1)));
    rv = strcpy(rv, "@I.");
    rv = strcat(rv, s);
    rv = strcat(rv, "@");
    return rv;
}

char *
get_RC_transition(const char *s)
{
    char* rv = static_cast<char*>(malloc(sizeof(char)*(strlen(s) + 5 + 1)));
    rv = strcpy(rv, "@RC.");
    rv = strcat(rv, s);
    rv = strcat(rv, "@");
    return rv;
}

char *
get_LC_transition(const char *s)
{
    char* rv = static_cast<char*>(malloc(sizeof(char)*(strlen(s) + 5 + 1)));
    rv = strcpy(rv, "@LC.");
    rv = strcat(rv, s);
    rv = strcat(rv, "@");
    return rv;
}

HfstTransducer * add_pmatch_delimiters(HfstTransducer * regex)
{
    HfstTransducer * delimited_regex = new HfstTransducer(hfst::internal_epsilon,
                                                          ENTRY_SYMBOL,
                                                          regex->get_type());
    delimited_regex->concatenate(*regex);
    delimited_regex->concatenate(HfstTransducer(hfst::internal_epsilon,
                                                EXIT_SYMBOL,
                                                regex->get_type()));
    delete regex;
    return delimited_regex;
}

void add_end_tag(HfstTransducer * regex, std::string tag)
{
    HfstTransducer * end_tag = make_end_tag(tag);
    regex->concatenate(*end_tag);
    delete end_tag;
}

HfstTransducer * make_end_tag(std::string tag)
{
    HfstTransducer * end_tag = new HfstTransducer(
        hfst::internal_epsilon,
        "@PMATCH_ENDTAG_" + tag + "@",
        format);
    return end_tag;
}


char * get_delimited(const char *s, char delim_left, char delim_right)
{
    const char *qstart = strchr((char*) s, delim_left) + 1;
    const char *qend = strrchr((char*) s, delim_right);
    char* qpart = strdup(qstart);
    *(qpart+ (size_t) (qend - qstart)) = '\0';
    return qpart;
}

char * get_delimited(const char *s, char delim)
{
    return get_delimited(s, delim, delim);
}

char * get_escaped_delimited(const char *s, char delim_left, char delim_right)
{
    return unescape_delimited(get_delimited(s, delim_left, delim_right), delim_right);
}
char * get_escaped_delimited(const char *s, char delim)
{
    return unescape_delimited(get_delimited(s, delim, delim), delim);
}

char * unescape_delimited(char *s, char delim)
{
    char * read = s;
    char * write = s;
    while (*read != '\0') {
        if (*read == '\\' && (*(read + 1) == delim || *(read + 1) == '\\')) {
            *write = *(read + 1);
            read += 2;
            write += 1;
        } else {
            *write = *read;
            ++read;
            ++write;
        }
    }
    *write = '\0';
    return s;
}

char*
parse_quoted(const char *s)
{
    char* quoted = get_delimited(s, '"');
    // Mysteriously, when the quoted string is 24 + n * 16 bytes in length, an
    // extra byte is needed for rv.
    char* rv = static_cast<char*>(malloc(sizeof(char)*(strlen(quoted) + 1)));
    char* p = quoted;
    char* r = rv;
    while (*p != '\0')
      {
        if (*p != '\\')
          {
            *r = *p;
            ++r;
            ++p;
          }
        else if (*p == '\\')
          {
            switch (*(p + 1))
              {
              case '0':
              case '1':
              case '2':
              case '3':
              case '4':
              case '5':
              case '6':
              case '7':
                fprintf(stderr, "*** PMATCH unimplemented: "
                        "parse octal escape in %s", p);
                *r = '\0';
                p = p + 5;
                break;
              case 'a':
                *r = '\a';
                r++;
                p = p + 2;
                break;
              case 'b':
                *r = '\b';
                r++;
                p = p + 2;
                break;
              case 'f':
                *r = '\f';
                r++;
                p = p + 2;
                break;
              case 'n':
                *r = '\n';
                r++;
                p = p + 2;
                break;
              case 'r':
                *r = '\r';
                r++;
                p = p + 2;
                break;
              case 't':
                *r = '\t';
                r++;
                p = p + 2;
                break;
              case 'u':
                  if (strlen(p) < 6) {
                      // Can't be a valid escape sequence
                      *r++ = '\\';
                      *r++ = 'u';
                      p += 2;
                  } else {
                      char buf[5];
                      memcpy(buf, p+2, 4);
                      buf[4] = '\0';
                      unsigned int codepoint = strtol(buf, NULL, 16);
                      bool u_parse_err = false;
                      // The following is adapted from an answer at
                      // http://stackoverflow.com/questions/4607413/c-library-to-convert-unicode-code-points-to-utf8
                      // My understanding of the magic numbers:
                      // 0x80 = 128 = 2^7
                      // 64 = 2^6, 192 = 2^6 + 2^7
                      // 0x800 = 2048 = 2^11
                      // 0x1000 = 2^16 etc.
                      if (codepoint < 0x80) {
                          buf[0] = codepoint;
                          buf[1] = '\0';
                      } else if (codepoint < 0x800) {
                          buf[0] = 192 + codepoint / 64;
                          buf[1] = 128 + codepoint % 64;
                          buf[2] = '\0';
                      } else if (codepoint - 0xd800u < 0x800) {
                          u_parse_err = true;
                      } else if (codepoint < 0x10000) {
                          buf[0] = 224 + codepoint / 4096;
                          buf[1] = 128 + codepoint / 64 % 64;
                          buf[2] = 128 + codepoint % 64;
                          buf[3] = '\0';
                      } else if (codepoint < 0x110000) {
                          buf[0] = 240 + codepoint / 262144;
                          buf[1] = 128 + codepoint / 4096 % 64;
                          buf[2] = 128 + codepoint / 64 % 64;
                          buf[3] = 128 + codepoint % 64;
                          buf[4] = '\0';
                      } else {
                          u_parse_err = true;
                      }
                      if (u_parse_err) {
                          fprintf(stderr, "PMATCH: Failed to parse unicode codepoint\n");
                          *r++ = '\0';
                      } else {
                          strcpy(r, buf);
                          r += strlen(buf) + 1;
                      }
                      p += 6;
                  }
                  break;
              case 'v':
                *r = '\v';
                r++;
                p = p + 2;
                break;
              case 'x':
                  {
                    char* endp;
                    int i = strtol(p + 2, &endp, 16);
                    if ( 0 < i && i <= 127)
                      {
                        *r = static_cast<char>(i);
                      }
                    else
                      {
                        fprintf(stderr, "*** PMATCH unimplemented: "
                                "parse \\x%d\n", i);
                        *r = '\0';
                      }
                    r++;
                    assert(endp != p);
                    p = endp;
                   break;
                }
              case '\0':
                fprintf(stderr, "End of line after \\ escape\n");
                *r = '\0';
                r++;
                p++;
                break;
              default:
                *r = *(p + 1);
                r++;
                p += 2;
                break;
              }
          }
      }
    *r = '\0';
    free(quoted);
    return rv;
}

double
get_weight(const char *s)
{
    double rv = -3.1415;
    const char* weightstart = s;
    while ((*weightstart != '\0') && 
           ((*weightstart == ' ') || (*weightstart == '\t') ||
            (*weightstart == ';')))
    {
        weightstart++;
    }
    char* endp;
    rv = strtod(weightstart, &endp);
    assert(endp != weightstart);
    return rv;
}

void init_globals(void)
{
    definitions.clear();
    def_insed_transducers.clear();
    inserted_transducers.clear();
    unsatisfied_insertions.clear();
    used_definitions.clear();
    functions.clear();
    tmp_collected_funargs.clear();
    zero_minimization_guard();
    need_delimiters = false;
}

std::map<std::string, HfstTransducer*>
compile(const string& pmatch, map<string,HfstTransducer*>& defs,
        ImplementationType impl, bool be_verbose, bool do_flatten)
{
    // lock here?
    init_globals();
    data = strdup(pmatch.c_str());
    startptr = data;
    len = strlen(data);
    verbose = be_verbose;
    flatten = do_flatten;
//    definitions = defs;
    format = impl;
    if (hfst::pmatch::verbose) {
        timer = clock();
        std::cerr << std::endl;
    }
    pmatchparse();
    free(startptr);
    data = 0;
    len = 0;
    std::map<std::string, hfst::HfstTransducer*> retval;
    for (std::set<std::string>::const_iterator it =
             unsatisfied_insertions.begin();
         it != unsatisfied_insertions.end(); ++it) {
        if (definitions.count(*it) == 0) {
            std::cerr << "Inserted transducer "
                      << *it << " was never defined!\n";
            return retval;
        }
    }
    if (hfst::pmatch::verbose) {
        std::map<std::string, hfst::HfstTransducer *>::iterator defs_itr;
        for (defs_itr = definitions.begin(); defs_itr != definitions.end();
             ++defs_itr) {
            if (used_definitions.count(defs_itr->first) == 0 &&
                defs_itr->first.compare("TOP") != 0) {
                std::cerr << "Warning: " << defs_itr->first << " defined but never used\n";
            }
        }
    }

    if (pmatchnerrs != 0) {
        return retval;
    }
    // Our helper for harmonizing all the networks' alphabets with
    // each other
    if (hfst::pmatch::verbose) {
        std::cerr << "\nHarmonizing... ";
    }

    HfstTransducer dummy(format);
    // We keep TOP and any inserted transducers
    std::map<std::string, hfst::HfstTransducer *>::iterator defs_itr;
    for (defs_itr = definitions.begin(); defs_itr != definitions.end();
         ++defs_itr) {
        if (defs_itr->first.compare("TOP") == 0 ||
            inserted_transducers.count(defs_itr->first) != 0) {
            dummy.harmonize(*defs_itr->second);
        }
    }
    
    // Now that dummy is harmonized with everything, we harmonize everything
    // with dummy and insert them into the result
    for(defs_itr = definitions.begin(); defs_itr != definitions.end();
        ++defs_itr) {
        if (defs_itr->first.compare("TOP") == 0 ||
            inserted_transducers.count(defs_itr->first) != 0) {
            dummy.harmonize(*defs_itr->second);
            retval.insert(std::pair<std::string, hfst::HfstTransducer*>(
                              defs_itr->first,
                              defs_itr->second));
        } else {
            delete defs_itr->second;
        }
    }
    if (hfst::pmatch::verbose) {
        double duration = (clock() - hfst::pmatch::timer) /
            (double) CLOCKS_PER_SEC;
        hfst::pmatch::timer = clock();
        std::cerr << "harmonized in " << duration << " seconds\n";
    }
    return retval;
}

void print_size_info(HfstTransducer * net)
{
    HfstBasicTransducer tmp(*net);
    size_t states = 0;
    size_t arcs = 0;
    for(HfstBasicTransducer::const_iterator state_it = tmp.begin();
        state_it != tmp.end(); ++state_it) {
        ++states;
        for(HfstBasicTransducer::HfstTransitions::const_iterator tr_it =
                state_it->begin(); tr_it != state_it->end(); ++tr_it) {
            ++arcs;
        }
    }
    std::cerr << states <<
        " states and " << arcs << " arcs" << std::endl;
}

HfstTransducer * read_text(char * filename, ImplementationType type)
{
    std::ifstream infile;
    std::string line;
    infile.open(filename);
    HfstTokenizer tok;
    HfstTransducer * retval = new HfstTransducer(type);
    if(!infile.good()) {
        std::cerr << "Pmatch: could not open text file " << filename <<
            " for reading\n";
    } else {
        size_t n = 0;
        while(infile.good()) {
            std::getline(infile, line);
            if(!line.empty()) {
                ++n;
                StringPairVector spv = tok.tokenize(line);
                retval->disjunct(spv);
            }
        }
    }
    infile.close();
    return retval;
}

std::vector<std::vector<std::string> > read_args(char * filename, unsigned int argcount)
{
    std::ifstream infile;
    std::string line;
    infile.open(filename);
    std::vector<std::vector <std::string> > retval;
    std::vector<std::string> current_tokens;
    if(!infile.good()) {
        std::cerr << "Pmatch: could not open text file " << filename <<
            " for reading\n";
    } else {
        size_t n = 0;
        while(infile.good()) {
            std::getline(infile, line);
            if(!line.empty()) {
                current_tokens.clear();
                ++n;
                int curpos;
                int nextpos = -1;
                do {
                    curpos = nextpos + 1;
                    nextpos = line.find_first_of(" ", curpos);
                    current_tokens.push_back(line.substr(curpos, nextpos - curpos));
                } while (nextpos != std::string::npos);
                if (current_tokens.size() != argcount) {
                    std::cerr << "Pmatch: line " << n << " in " << filename << " contained "
                              << current_tokens.size() << " tokens, expected " << argcount << std::endl;
                } else {
                    retval.push_back(current_tokens);
                }
            }
        }
    }
    infile.close();
    return retval;
}

PmatchUtilityTransducers::PmatchUtilityTransducers(void)
{
    latin1_acceptor = make_latin1_acceptor();
    latin1_alpha_acceptor = make_latin1_alpha_acceptor();
    latin1_lowercase_acceptor = make_latin1_lowercase_acceptor();
    latin1_uppercase_acceptor = make_latin1_uppercase_acceptor();
    combining_accent_acceptor = make_combining_accent_acceptor();
    latin1_numeral_acceptor = make_latin1_numeral_acceptor();
    latin1_punct_acceptor = make_latin1_punct_acceptor();
    latin1_whitespace_acceptor = make_latin1_whitespace_acceptor();
    lowerfy = make_lowerfy();
    capify = make_capify();
}

PmatchUtilityTransducers::~PmatchUtilityTransducers(void)
{
    delete latin1_acceptor;
    delete latin1_alpha_acceptor;
    delete latin1_lowercase_acceptor;
    delete latin1_uppercase_acceptor;
    delete combining_accent_acceptor;
    delete latin1_numeral_acceptor;
    delete latin1_punct_acceptor;
    delete latin1_whitespace_acceptor;
    delete lowerfy;
    delete capify;
}

HfstTransducer * PmatchUtilityTransducers::make_latin1_acceptor(ImplementationType type)
  {
      HfstTransducer * retval = make_latin1_alpha_acceptor();
      HfstTransducer * tmp = make_latin1_numeral_acceptor();
      retval->disjunct(*tmp); delete tmp;
      tmp = make_latin1_punct_acceptor(); retval->disjunct(*tmp); delete tmp;
      tmp = make_latin1_whitespace_acceptor(); retval->disjunct(*tmp); delete tmp;
      retval->minimize();
      return retval;
  }

HfstTransducer * PmatchUtilityTransducers::make_latin1_alpha_acceptor(ImplementationType type)
  {
      HfstTransducer * retval = make_latin1_lowercase_acceptor();
      HfstTransducer * tmp = make_latin1_uppercase_acceptor();
      retval->disjunct(*tmp); delete tmp;
      retval->minimize();
      return retval;
  }

HfstTransducer * PmatchUtilityTransducers::make_latin1_lowercase_acceptor(ImplementationType type)
  {
      HfstTransducer * retval = acceptor_from_cstr(latin1_lower, type);
      HfstTransducer * tmp = make_combining_accent_acceptor();
      retval->disjunct(*tmp); delete tmp;
      retval->minimize();
      return retval;
  }

HfstTransducer * PmatchUtilityTransducers::make_latin1_uppercase_acceptor(ImplementationType type)
  {
      HfstTransducer * retval = acceptor_from_cstr(latin1_upper, type);
      HfstTransducer * tmp = make_combining_accent_acceptor();
      retval->disjunct(*tmp); delete tmp;
      retval->minimize();
      return retval;
  }

HfstTransducer * PmatchUtilityTransducers::make_combining_accent_acceptor(ImplementationType type)
  {
      return acceptor_from_cstr(combining_accents, type);
  }

HfstTransducer * PmatchUtilityTransducers::make_latin1_numeral_acceptor(ImplementationType type)
  {
      HfstTransducer * retval = new HfstTransducer(type);
      const std::string num =
          "0123456789";
      for (std::string::const_iterator it = num.begin(); it != num.end();
           ++it) {
          retval->disjunct(HfstTransducer(std::string(1, *it), type));
      }
      return retval;
      retval->minimize();
  }

HfstTransducer * PmatchUtilityTransducers::make_latin1_punct_acceptor(ImplementationType type)
  {
      return acceptor_from_cstr(latin1_punct, type);
  }

HfstTransducer * PmatchUtilityTransducers::make_latin1_whitespace_acceptor(ImplementationType type)
{
    return acceptor_from_cstr(latin1_whitespace, type);
}

HfstTransducer * PmatchUtilityTransducers::make_capify(ImplementationType type)
{
    HfstTransducer * retval = new HfstTransducer(type);
    HfstTokenizer tok;
    for (size_t i = 0; i < array_len(latin1_upper); ++i) {
        retval->disjunct(HfstTransducer(latin1_lower[i], latin1_upper[i],
                                        tok, type));
    }
    HfstTransducer accents(*combining_accent_acceptor);
    accents.optionalize();
    retval->concatenate(accents);
    retval->minimize();
    return retval;
}

HfstTransducer * PmatchUtilityTransducers::make_lowerfy(ImplementationType type)
{
    HfstTransducer * retval = new HfstTransducer(type);
    HfstTokenizer tok;
    for (size_t i = 0; i < array_len(latin1_upper); ++i) {
        retval->disjunct(HfstTransducer(latin1_upper[i], latin1_lower[i],
                                        tok, type));
    }
    HfstTransducer accents(*combining_accent_acceptor);
    accents.optionalize();
    retval->concatenate(accents);
    retval->minimize();
    return retval;
}

HfstTransducer * PmatchUtilityTransducers::optcap(HfstTransducer & t)
{
    HfstTokenizer tok;
    HfstTransducer optcap(*capify);
    optcap.disjunct(*lowerfy);
    optcap.disjunct(*latin1_alpha_acceptor);
    HfstTransducer anything(HfstTransducer::identity_pair(t.get_type()));
    HfstTransducer anything_but_whitespace(anything.subtract(
                                               *latin1_whitespace_acceptor));
    HfstTransducer optcap_one_word(optcap);
    optcap_one_word.concatenate(anything_but_whitespace.repeat_star());
    /* If we consider to cross the word boundary */ 
    HfstTransducer more_words(*latin1_whitespace_acceptor);
    more_words.concatenate(optcap_one_word);
    more_words.repeat_star();
    HfstTransducer * retval = new HfstTransducer(t);
    retval->compose(optcap_one_word.concatenate(more_words));
    retval->output_project();
    retval->disjunct(t);
    retval->minimize();
    return retval;
}

HfstTransducer * PmatchUtilityTransducers::tolower(HfstTransducer & t)
{
    HfstTokenizer tok;
    HfstTransducer lowercase(*lowerfy);
    lowercase.disjunct(*latin1_numeral_acceptor);
    lowercase.disjunct(*latin1_punct_acceptor);
    lowercase.disjunct(*latin1_whitespace_acceptor);
    lowercase.disjunct(*latin1_lowercase_acceptor);
    HfstTransducer * retval = new HfstTransducer(t);
    retval->compose(lowercase.repeat_star());
    retval->output_project();
    retval->minimize();
    return retval;
}

HfstTransducer * PmatchUtilityTransducers::toupper(HfstTransducer & t)
{
    HfstTokenizer tok;
    HfstTransducer uppercase(*capify);
    uppercase.disjunct(*latin1_numeral_acceptor);
    uppercase.disjunct(*latin1_punct_acceptor);
    uppercase.disjunct(*latin1_whitespace_acceptor);
    uppercase.disjunct(*latin1_uppercase_acceptor);
    HfstTransducer * retval = new HfstTransducer(t);
    retval->compose(uppercase.repeat_star());
    retval->output_project();
    retval->minimize();
    return retval;
}

HfstTransducer * PmatchFunction::evaluate(
    std::map<std::string,
             HfstTransducer *> & funargs)
{
    return root->evaluate(funargs);
}

HfstTransducer * PmatchAstNode::evaluate(
    std::map<std::string,
             HfstTransducer *> & funargs)
{
    if (type == AstTransducer) {
        return new HfstTransducer(*transducer);
    } else if (type == AstUnaryOp) {
        HfstTransducer * retval = left_child->evaluate(funargs);
        if (op == AstAddDelimiters) {
            return add_pmatch_delimiters(retval);
        } else if (op == AstOptionalize) {
            retval->optionalize();
            return retval;
        } else if (op == AstRepeatStar) {
            retval->repeat_star();
            return retval;
        } else if (op == AstRepeatPlus) {
            retval->repeat_plus();
            return retval;
        } else if (op == AstReverse) {
            retval->reverse();
            return retval;
        } else if (op == AstInvert) {
            retval->invert();
            return retval;
        } else if (op == AstInputProject) {
            retval->input_project();
            return retval;
        } else if (op == AstOutputProject) {
            retval->output_project();
            return retval;
        } else if (op == AstRepeatN) {
            retval->repeat_n(numeric_args[0]);
            return retval;
        } else if (op == AstRepeatNPlus) {
            retval->repeat_n_plus(numeric_args[0]);
            return retval;
        } else if (op == AstRepeatNMinus) {
            retval->repeat_n_minus(numeric_args[0]);
            return retval;
        } else if (op == AstRepeatNToK) {
            retval->repeat_n_to_k(numeric_args[0], numeric_args[1]);
            return retval;
        } else if (op == AstOptCap) {
            HfstTransducer * tmp = get_utils()->optcap(*retval);
            delete retval;
            return tmp;
        } else if (op == AstToLower) {
            HfstTransducer * tmp = get_utils()->tolower(*retval);
            delete retval;
            return tmp;
        } else if (op == AstToUpper) {
            HfstTransducer * tmp = get_utils()->toupper(*retval);
            delete retval;
            return tmp;
        }
    } else if (type == AstBinaryOp) {
        HfstTransducer * retval = left_child->evaluate(funargs);
        if (op == AstConcatenate) {
            retval->concatenate(*right_child->evaluate(funargs));
            return retval;
        } else if (op == AstCompose) {
            retval->compose(*right_child->evaluate(funargs));
            return retval;
        } else if (op == AstCrossProduct) {
            retval->cross_product(*right_child->evaluate(funargs));
            return retval;
        } else if (op == AstLenientCompose) {
            retval->lenient_composition(*right_child->evaluate(funargs));
            return retval;
        } else if (op == AstDisjunct) {
            retval->disjunct(*right_child->evaluate(funargs));
            return retval;
        } else if (op == AstIntersect) {
            retval->intersect(*right_child->evaluate(funargs));
            return retval;
        } else if (op == AstSubtract) {
            retval->subtract(*right_child->evaluate(funargs));
            return retval;
        }

    } else if (type == AstSymbol) {
        if (funargs.count(symbol) == 1) {
            return new HfstTransducer(*funargs[symbol]);
        } else {
            std::string errstring = "Symbol " + std::string(symbol) + " not found";
            pmatcherror(errstring.c_str());
            return new HfstTransducer(); // For some compilers and linters
        }        
    }
    return new HfstTransducer(); // For some compilers and linters
}


} }
