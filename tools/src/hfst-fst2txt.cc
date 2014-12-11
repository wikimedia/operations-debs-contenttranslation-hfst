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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WINDOWS
#include <io.h>
#endif


#include <iostream>
#include <fstream>
#include <set>
#include <map>

using std::set;
using std::map;

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <errno.h>

#include "hfst-commandline.h"
#include "hfst-program-options.h"
#include "HfstTransducer.h"
#include "HfstInputStream.h"
#include "HfstOutputStream.h"

#include "inc/globals-common.h"
#include "inc/globals-unary.h"

using hfst::HfstTransducer;
using hfst::HfstInputStream;
using hfst::HfstBasicTransducer;
using hfst::implementations::HfstState;

// add tools-specific variables here
static bool use_numbers=false;
static bool print_weights=false;
static bool do_not_print_weights=false;

enum fst_text_format {
    ATT_TEXT, // AT&T / OpenFst compatible TSV
    DOT_TEXT, // Graphviz / dotty
    PCKIMMO_TEXT, // PCKIMMO format
    PROLOG_TEXT, // prolog format
};

static fst_text_format format=ATT_TEXT;

void
print_usage()
{
    // c.f. http://www.gnu.org/prep/standards/standards.html#g_t_002d_002dhelp
    fprintf(message_out, "Usage: %s [OPTIONS...] [INFILE]\n"
        "Print transducer in AT&T, dot, prolog or pckimmo format\n"
        "\n", program_name);

    print_common_program_options(message_out);
    print_common_unary_program_options(message_out);
    fprintf(message_out, "Text format options:\n"
        "  -w, --print-weights          If weights are printed in all cases\n"
        "  -D, --do-not-print-weights   If weights are not printed in any "
        "case\n"
        "  -f, --format=TFMT            Print output in TFMT format "
        "[default=att]\n");
    fprintf(message_out, "\n");
    fprintf(message_out,
          "If OUTFILE or INFILE is missing or -, "
      "standard streams will be used.\n"
          "Unless explicitly requested with option -w or -D, "
      "weights are printed\n" 
          "if and only if the transducer is in weighted format.\n"
          "TFMT is one of {att, dot, prolog, pckimmo}.\n"
    );
    fprintf(message_out, "\n");
    print_report_bugs();
    fprintf(message_out, "\n");
    print_more_info();
}

int
parse_options(int argc, char** argv)
{
    extend_options_getenv(&argc, &argv);
    // use of this function requires options are settable on global scope
    while (true)
    {
        static const struct option long_options[] =
        {
        HFST_GETOPT_COMMON_LONG,
        HFST_GETOPT_UNARY_LONG,
          // add tool-specific options here
            {"print-weights",        no_argument,       0, 'w'},
            {"do-not-print-weights", no_argument,       0, 'D'},
            {"use-numbers",          no_argument,       0, 'n'},
            {"format",               required_argument, 0, 'f'},
            {0,0,0,0}
        };
        int option_index = 0;
        // add tool-specific options here 
        char c = getopt_long(argc, argv, HFST_GETOPT_COMMON_SHORT
                             HFST_GETOPT_UNARY_SHORT "wDnf:",
                             long_options, &option_index);
        if (-1 == c)
        {
            break;
        }

        switch (c)
        {
#include "inc/getopt-cases-common.h"
#include "inc/getopt-cases-unary.h"
          // add tool-specific cases here
        case 'w':
            print_weights = true;
            break;
    case 'D':
        do_not_print_weights = true;
        break;
    case 'n':
        use_numbers = true;
        break;
    case 'f':
        if ((strcmp(optarg, "att") == 0) || (strcmp(optarg, "AT&T") == 0) ||
            (strcmp(optarg, "openfst") == 0) || 
            (strcmp(optarg, "OpenFst") == 0))
          {
            format = ATT_TEXT;
          }
        else if ((strcmp(optarg, "dot") == 0) || 
            (strcmp(optarg, "graphviz") == 0) || 
            (strcmp(optarg, "GraphViz") == 0))
          {
            format = DOT_TEXT;
          }
        else if (strcmp(optarg, "pckimmo") == 0)
          {
            format = PCKIMMO_TEXT;
          }
        else if ((strcmp(optarg, "prolog") == 0) ||
                 (strcmp(optarg, "Prolog") == 0))
          {
            format = PROLOG_TEXT;
          }
        else
          {
            error(EXIT_FAILURE, 0, "Cannot parse %s as text format; Use one of "
                  "att, pckimmo, dot, prolog", optarg);
          }
        break;
#include "inc/getopt-cases-error.h"
        }
    }

#include "inc/check-params-common.h"
#include "inc/check-params-unary.h"
    return EXIT_CONTINUE;
}

static
void
print_dot(FILE* out, HfstTransducer& t)
  {
    fprintf(out, "// This graph generated with hfst-fst2txt\n");
    if (t.get_name() != "")
      {
        fprintf(out, "digraph \"%s\" {\n", t.get_name().c_str());
      }
    else
      {
        fprintf(out, "digraph H {\n");
      }
    fprintf(out, "charset = UTF8;\n");
    fprintf(out, "rankdir = LR;\n");
    fprintf(out, "node [shape=circle,style=filled,fillcolor=yellow]\n");
    HfstBasicTransducer* mutt = new HfstBasicTransducer(t);
    HfstState s = 0;
    // for some reason, dot works nicer if I first have all nodes, then arcs
    for (HfstBasicTransducer::const_iterator state = mutt->begin();
         state != mutt->end();
         ++state)
      {
        if (mutt->is_final_state(s))
          {
            if (mutt->get_final_weight(s) > 0)
              {
                fprintf(out, "q%d [shape=doublecircle,"
                       "label=\"q%d/\\n%.2f\"] \n",
                        s, s, mutt->get_final_weight(s));
              }
            else
              {
                fprintf(out, "q%d [shape=doublecircle,"
                       "label=\"q%d\"] \n",
                        s, s);
              }
          }
        else
          {
            fprintf(out, "q%d [label=\"q%d\"] \n", 
                    s, s);
          }
        ++s;
      } // each state
    s = 0;
    for (HfstBasicTransducer::const_iterator state = mutt->begin();
         state != mutt->end();
         ++state)
      {
        map<HfstState, string> target_labels;
        for (HfstBasicTransducer::HfstTransitions::const_iterator arc = 
             state->begin();
             arc != state->end();
             ++arc)
          {
            string old_label = target_labels[arc->get_target_state()];
            string first = arc->get_input_symbol();
            string second = arc->get_output_symbol();
            if (first == hfst::internal_epsilon)
              {
                first = string("00");
              }
            else if (first == hfst::internal_identity)
              {
                first = string("??");
              }
            else if (first == hfst::internal_unknown)
              { 
                first = string("?1");
              }
            if (second == hfst::internal_epsilon)
              {
                second = string("00");
              }
            else if (second == hfst::internal_identity)
              {
                second = string("??");
              }
            else if (second == hfst::internal_unknown)
              {
                second = string("?2");
              }
#define DOT_MAX_LABEL_SIZE 64
            char* l = static_cast<char*>(malloc(sizeof(char) * 
                                                DOT_MAX_LABEL_SIZE));
            if (first == second)
              {
                if (arc->get_weight() > 0)
                  {
                    errno = 0;
                    if (old_label != "")
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                             "%s, %s/%.2f", old_label.c_str(),
                             first.c_str(),
                             arc->get_weight()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                 "sprinting dot arc label");
                          }
                      }
                    else 
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                                     "%s/%.2f", first.c_str(),
                                     arc->get_weight()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                 "sprinting dot arc label");
                          }
                      }  // if old label empty
                  } // if weighted
                else
                  {
                    errno = 0;
                    if (old_label != "")
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                             "%s, %s", old_label.c_str(),
                             first.c_str()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                 "sprinting dot arc label");
                          }
                      }
                    else 
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                                     "%s", first.c_str()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                 "sprinting dot arc label");
                          }
                      } // if old label empty
                  } // if weighted 
              } // if id pair
            else
              {
                if (arc->get_weight() > 0)
                  {
                    errno = 0;
                    if (old_label != "")
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                                     "%s, %s:%s/%.2f", old_label.c_str(),
                                    first.c_str(), second.c_str(),
                                    arc->get_weight()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                  "sprinting dot arc label");
                          }
                      }
                    else
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                                     "%s:%s/%.2f",
                                    first.c_str(), second.c_str(),
                                    arc->get_weight()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                  "sprinting dot arc label");
                          }
                      }  // old label empty
                  } // if weighted
                else
                  {
                    errno = 0;
                    if (old_label != "")
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                                     "%s, %s:%s", old_label.c_str(),
                                    first.c_str(), second.c_str()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                  "sprinting dot arc label");
                          }
                      }
                    else
                      {
                        if (snprintf(l, DOT_MAX_LABEL_SIZE,
                                     "%s:%s",
                                    first.c_str(), second.c_str()) < 0)
                          {
                            error(EXIT_FAILURE, errno, 
                                  "sprinting dot arc label");
                          }
                      } // if old label empty
                  } // if weighted
              } // if id pair
            target_labels[arc->get_target_state()] = l;
            free(l);
          } // each arc
        for (map<HfstState,string>::const_iterator tl = target_labels.begin();
             tl != target_labels.end();
             ++tl)
          {
            fprintf(out, "q%d -> q%d ", s, tl->first);
            fprintf(out, "[label=\"%s \"];\n", tl->second.c_str());
          }
        ++s;
      } // each state
    fprintf(out, "}\n");
  }

static
void
print_pckimmo(FILE* out, HfstTransducer& t)
  {
    HfstBasicTransducer* mutt = new HfstBasicTransducer(t);
    HfstState s = 0;
    HfstState last = 0;
    set<pair<string,string> > pairs;
    for (HfstBasicTransducer::const_iterator state = mutt->begin();
         state != mutt->end();
         ++state)
      {
        for (HfstBasicTransducer::HfstTransitions::const_iterator arc = 
             state->begin();
             arc != state->end();
             ++arc)
          {
            string first = arc->get_input_symbol();
            string second = arc->get_output_symbol();
            pairs.insert(pair<string,string>(first, second));
          }
        ++last;
      }
    // width of the first column
    unsigned int numwidth = 0;
    for (unsigned int i = 1; i < last; i *= 10, numwidth++)
      {}
    // first line is input symbols per pair 
    // (left corner is digit width + 2)
    fprintf(out, "%*s  ", numwidth, " ");
    for (set<pair<string, string> >::const_iterator p = pairs.begin();
         p != pairs.end();
         ++p)
      {
        if (p->first == hfst::internal_epsilon)
          {
            fprintf(out, "%.*s ", numwidth, "0");
          }
        else if (p->first == hfst::internal_unknown)
          {
            fprintf(out, "%.*s ", numwidth, "@");
          }
        else
          {
            fprintf(out, "%.*s ", numwidth, p->first.c_str());
          }
      }
    // second line is output symbols per pair
    fprintf(out, "\n");
    // (left corner is digit width + 2)
    fprintf(out, "%*s  ", numwidth, " ");
    for (set<pair<string, string> >::const_iterator p = pairs.begin();
         p != pairs.end();
         ++p)
      {
        if (p->second == hfst::internal_epsilon)
          {
            fprintf(out, "%.*s ", numwidth, "0");
          }
        else if (p->second == hfst::internal_unknown)
          {
            fprintf(out, "%.*s ", numwidth, "@");
          }
        else
          {
            fprintf(out, "%.*s ", numwidth, p->second.c_str());
          }

      }
    // the transition table per state
    fprintf(out, "\n");
    for (HfstBasicTransducer::const_iterator state = mutt->begin();
         state != mutt->end();
         ++state)
      {
        if (mutt->is_final_state(s))
          {
            fprintf(out, "%.*d. ", numwidth, s + 1);
          }
        else
          {
            fprintf(out, "%.*d: ", numwidth, s + 1);
          }
        // map everything to sink state 0 first
        map<pair<string,string>,HfstState> transitions;
        for(set<pair<string,string> >::const_iterator p = pairs.begin();
            p != pairs.end();
            ++p)
          {
            transitions[*p] = -1;
          }
        for (HfstBasicTransducer::HfstTransitions::const_iterator arc = 
             state->begin();
             arc != state->end();
             ++arc)
          {
            string first = arc->get_input_symbol();
            string second = arc->get_output_symbol();
            transitions[pair<string,string>(first,second)] = 
                arc->get_target_state();
          }
        for(map<pair<string,string>,HfstState>::const_iterator trans = 
            transitions.begin();
            trans != transitions.end();
            ++trans)
          {
            fprintf(out, "%.*d ", numwidth, trans->second + 1);
          }
        fprintf(out, "\n");
        ++s;
      } // for each state
  }

int
process_stream(HfstInputStream& instream, FILE* outf)
{
  //instream.open();
    size_t transducer_n = 0;
    while(instream.is_good())
    {
        transducer_n++;
        HfstTransducer* t=NULL;
        try 
          {
            t = new HfstTransducer(instream);
          }
        catch (const TransducerTypeMismatchException &e)
          {
            error(EXIT_FAILURE, 0, "input transducers do not have the same type");
          }
        char* inputname = strdup(t->get_name().c_str());
        if (strlen(inputname) <= 0)
          {
            inputname = strdup(inputfilename);
          }
        if (transducer_n == 1)
        {
          verbose_printf("Converting %s...\n", inputname); 
        }
        else
        { 
          verbose_printf("Converting %s..." SIZE_T_SPECIFIER "\n", inputname,
                         transducer_n); 
        }


        if(transducer_n > 1)
            fprintf(outf, "--\n");

        bool printw; // whether weights are printed
        hfst::ImplementationType type = t->get_type();
        if (print_weights)
          printw=true;
        else if (do_not_print_weights)
          printw=false;
        else if ( (type == hfst::SFST_TYPE || type == hfst::FOMA_TYPE) )
          printw = false;
        else if ( (type == hfst::TROPICAL_OPENFST_TYPE || type == hfst::LOG_OPENFST_TYPE) )
          printw = true;
        else  // this should not happen
          printw = true;
    switch (format)
      {
      case ATT_TEXT:
        if (use_numbers)
          t->write_in_att_format_number(outf,printw);
        else
          t->write_in_att_format(outf,printw);
        break;
      case DOT_TEXT:
        print_dot(outf, *t);
        break;
      case PCKIMMO_TEXT:
        print_pckimmo(outf, *t);
        break;
      case PROLOG_TEXT:
        {
          HfstBasicTransducer fsm(*t);
          std::string namestr = t->get_name();
          if (namestr == "")
            namestr = "NO_NAME";
          fsm.write_in_prolog_format(outf,namestr,printw);
          break;
        }
      default:
        error(EXIT_FAILURE, 0, "Unknown print format");
      }
    delete t;
    }
    instream.close();
    if (outf != stdout)
      {
        fclose(outf);
      }
    return EXIT_SUCCESS;
}


int main( int argc, char **argv ) 
{
#ifdef WINDOWS
  _setmode(0, _O_BINARY);
#endif

    hfst_set_program_name(argv[0], "0.3", "HfstFst2Txt");
    int retval = parse_options(argc, argv);
    if (retval != EXIT_CONTINUE)
    {
        return retval;
    }
    // close buffers, we use streams
    if (inputfile != stdin)
    {
        fclose(inputfile);
    }
    
    verbose_printf("Reading from %s, writing to %s\n", 
        inputfilename, outfilename);
    // here starts the buffer handling part
    HfstInputStream* instream = NULL;
    try {
      instream = (inputfile != stdin) ?
        new HfstInputStream(inputfilename) : new HfstInputStream();
    } catch(const HfstException e)  {
        error(EXIT_FAILURE, 0, "%s is not a valid transducer file",
              inputfilename);
        return EXIT_FAILURE;
    }
    
    retval = process_stream(*instream, outfile);

    delete instream;
    free(inputfilename);
    free(outfilename);
    return retval;
}

