/**
 * @file hfst-tool-metadata.cc
 *
 * @brief 
 */
//       This program is free software: you can redistribute it and/or modify
//       it under the terms of the GNU General Public License as published by
//       the Free Software Foundation, version 3 of the License.
//
//       This program is distributed in the hope that it will be useful,
//       but WITHOUT ANY WARRANTY; without even the implied warranty of
//       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//       GNU General Public License for more details.
//
//       You should have received a copy of the GNU General Public License
//       along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "hfst-tool-metadata.h"

#include <stdexcept>
#include <string>

using std::string;

void
hfst_set_name(hfst::HfstTransducer& dest, const string& src,
              const string& op)
  {
    dest.set_name(op + "(" + src + ")");
  }

void
hfst_set_name(hfst::HfstTransducer& dest, const hfst::HfstTransducer& src,
              const std::string& op)
  {
    if (src.get_name() != "")
      {
        dest.set_name(op + "(" + src.get_name() + ")");
      }
    else
      {
        dest.set_name(op + "(?stdin?)");
      }
  }

void
hfst_set_name(hfst::HfstTransducer& dest, const hfst::HfstTransducer& lhs,
              const hfst::HfstTransducer& rhs,
              const std::string& op)
  {
    if ((lhs.get_name() != "") && (rhs.get_name() != ""))
      {
        dest.set_name(op + "(" + lhs.get_name() + ", " + rhs.get_name() + ")");
      }
    else if ((lhs.get_name() == "") && (rhs.get_name() != ""))
      {
        dest.set_name(op + "(?stdin?, " + rhs.get_name() + ")");
      }
    else if ((lhs.get_name() != "") && (rhs.get_name() == ""))
      {
        dest.set_name(op + "(" + lhs.get_name() + ", ?stdin?)");
      }
    else if ((lhs.get_name() == "") && (rhs.get_name() == ""))
      {
        dest.set_name(op + "(?stdin?, ?stdin?)");
      }
    else
      {
        throw std::logic_error("!(a && b) || (!a && b) || (a && !b) || (!a && !b)");
      }
  } 

void
hfst_set_formula(hfst::HfstTransducer& dest, const string& src,
                  const string& op)
  {
    if ((0 < src.at(0))  && (src.at(0) < 128))
      {
        dest.set_property("formulaic-definition", op + " " + src.substr(0, 1));
      }
    else 
      {
        dest.set_property("formulaic-definition", op + " U8");
      }
  }

void
hfst_set_formula(hfst::HfstTransducer& dest, const hfst::HfstTransducer& src,
                 const std::string& op)
  {

    if (src.get_property("formulaic-definition") != "")
      {
        dest.set_property("formulaic-definition", 
                          op + " " + src.get_property("formulaic-definition"));
      }
    else
      {
        dest.set_property("formulaic-definition", op + " .");
      }
  }

void
hfst_set_formula(hfst::HfstTransducer& dest, const hfst::HfstTransducer& lhs,
                 const hfst::HfstTransducer& rhs,
                 const std::string& op)
  {
    if ((lhs.get_property("formulaic-definition") != "") &&
        (rhs.get_property("formulaic-definition") != ""))
      {
        dest.set_property("formulaic-definition",
                          lhs.get_property("formulaic-definition") + 
                          " " + op + " " +
                          rhs.get_property("formulaic-definition"));
      }
    else if ((lhs.get_property("formulaic-definition") == "") &&
             (rhs.get_property("formulaic-definition") != ""))
      {
        dest.set_property("formulaic-definition",
                          ". " + op + " " + 
                          rhs.get_property("formulaic-definition"));
      }
    else if ((lhs.get_property("formulaic-definition") != "") &&
             (rhs.get_property("formulaic-definition") == ""))
      {
        dest.set_property("formulaic-definition",
                          lhs.get_property("formulaic-definition") + 
                          " " + op + " .");
      }
    else
      {
        dest.set_property("formulaic-definition",
                          ". " + op + " .");
      }
  }

void 
hfst_set_commandline_def(hfst::HfstTransducer& dest,
                              int argc, const char** argv)
  {
    string cmdline = "";
    bool o = false;
#if HAVE_BASENAME
    cmdline += basename(argv[0]);
#else
    cmdline += argv[0];
#endif
    for (int i = 1; i <= argc; i ++)
      {
        if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--verbose") == 0))
          {
            continue;
          }
        else if ((strcmp(argv[i], "-o") == 0) ||
                  (strcmp(argv[i] , "--output") == 0) )
          {
            o = true;
          }
        cmdline += argv[i];
      }
    if (o == false)
      {
        cmdline += " > ??? ";
      }
    dest.set_property("commandline-definition", cmdline);
  }

void 
hfst_set_commandline_def(hfst::HfstTransducer& dest,
                              const hfst::HfstTransducer& src,
                              int argc, const char** argv)
  {
    string cmdline = src.get_property("commandline-definition");
    if (cmdline != "")
      {
        cmdline += "; ";
      }
    bool o = false;
#if HAVE_BASENAME
    cmdline += basename(argv[0]);
#else
    cmdline += argv[0];
#endif
    for (int i = 1; i <= argc; i ++)
      {
        if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--verbose") == 0))
          {
            continue;
          }
        else if ((strcmp(argv[i], "-o") == 0) ||
                  (strcmp(argv[i] , "--output") == 0) )
          {
            o = true;
          }
        cmdline += argv[i];
      }
    if (o == false)
      {
        cmdline += " > ??? ";
      }
    dest.set_property("commandline-definition", cmdline);
  }
    

void hfst_set_commandline_def(hfst::HfstTransducer& dest,
                              const hfst::HfstTransducer& lhs,
                              const hfst::HfstTransducer& rhs,
                              int argc, const char** argv)
  {
    string cmdline = lhs.get_property("commandline-definition");
    if (cmdline != "")
      {
        cmdline += "&& ";
      }
    if (rhs.get_property("commandline-definition") != "")
      {
        cmdline += rhs.get_property("commandline-definition");
      }
    if (cmdline != "")
      {
        cmdline += "; ";
      }
    bool o = false;
#if HAVE_BASENAME
    cmdline += basename(argv[0]);
#else
    cmdline += argv[0];
#endif
    for (int i = 1; i <= argc; i ++)
      {
        if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--verbose") == 0))
          {
            continue;
          }
        else if ((strcmp(argv[i], "-o") == 0) ||
                  (strcmp(argv[i] , "--output") == 0) )
          {
            o = true;
          }
        cmdline += argv[i];
      }
    if (o == false)
      {
        cmdline += " > ??? ";
      }
    dest.set_property("commandline-definition", cmdline);
  }

char*
hfst_get_name(const hfst::HfstTransducer& arg,
              const std::string& filename)
  {
    if (arg.get_name() != "")
      {
        return strdup(arg.get_name().c_str());;
      }
    else
      {
        return strdup(filename.c_str());
      }
  }




