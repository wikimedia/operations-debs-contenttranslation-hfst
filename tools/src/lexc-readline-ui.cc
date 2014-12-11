//! @file hfst-lexc-compiler.cc
//!
//! @brief Lexc compilation command line tool
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

// c.f. <http://sourceforge.net/tracker/?func=detail&aid=954616&group_id=3275&atid=103275>
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#if HAVE_READLINE // HAVE_READLINE_READLINE_H
#  include <readline/readline.h>
#endif
#if HAVE_READLINE // HAVE_READLINE_HISTORY_H
#  include <readline/history.h>
#endif

#include "HfstTransducer.h"
#include "HfstOutputStream.h"
#include "parsers/LexcCompiler.h"
#include "hfst-commandline.h"

using hfst::HfstTransducer;
using hfst::HfstTransducerVector;
using hfst::HfstInputStream;
using hfst::HfstOutputStream;
using hfst::ImplementationType;

//static HfstTransducer* source_ = 0;
//static HfstTransducer* result_ = 0;
static HfstTransducerVector rules_;

void
lexc_banner()
{
  fprintf(message_out, 
          "         *******************************************************\n"
          "         *   Helsinki FS Lexicon Compiler %s (" PACKAGE_VERSION ")     *\n"
          "         *         cloned from Xerox original by               *\n"
          "         *           HFST research group                       *\n"
          "         *    Copyleft    2011 by University of Helsinki       *\n"
          "         *                 All Rights Reversed.                *\n"
          "         *******************************************************\n"
          "\n",
          hfst_tool_version);
}

void
lexc_qmark()
{
  fprintf(message_out,
          "Input/Output ------------------------------------------------------------------\n"
          "    Source:      compile-source, merge-source, read-source, result-to-source,\n"
          "                 save-source.\n"
          "    Rules:       read-rules.\n"
          "    Result:      merge-result, read-result, save-result, source-to-result.\n"
          "    Properties:  add-props, reset-props, save-props.\n"
          "Operations --------------------------------------------------------------------\n"
          "    Composition: compose-result, extract-surface-forms, invert-source, invert-result.\n"
          "    Checking:    check-all, lookdown, lookup, random, random-lex, random-surf.\n"
          "    Switches:    ambiguities, duplicates, failures, obey-flags, print-space,\n"
          "                 recode-cp1252, quit-on-fail, show-flags, singles, time, utf8-mode.\n"
          "    Scripts:     begin-script, end-script, run-script.\n"
          "Display -----------------------------------------------------------------------\n"
          "    Misc:        banner, labels, props, status, storage.\n"
          "    Help:        completion, help, history, ?.\n"
          "Type `quit' to exit.\n"
          "\n");
}





int
lexc_readline_loop(hfst::ImplementationType format)
{
  lexc_banner();
  lexc_qmark();
  char* command = 0;
  while ((command = hfst_readline("lexc> ")) != NULL)
    {
      char *p = command;
      while (isspace(*p))
        {
          p++;
        }

      if (strncmp(p, "banner", strlen("banner")) == 0)
        {
          lexc_banner();
        }
      else if (strncmp(p, "?", strlen("?")) == 0)
        {
          lexc_qmark();
        }
      else if (strncmp(p, "quit", strlen("quit")) == 0)
        {
          return EXIT_SUCCESS;
        }
      else
        {
          fprintf(message_out, "unrecognised ommand %s; currently supported"
                  "are `banner', `?' and `quit'\n", command);
        }
    }
  return EXIT_SUCCESS;
}

