/**
 * @file hfst-tool-metadata.h
 *
 * @brief common functions for adding metadata related to tools to automata.
 * This file contains interface specifications for hfst tool related metadata
 * editing. The tools should primarily use these functions to edit metadata of
 * the created automata.
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


#ifndef GUARD_hfst_tool_metadata_h
#define GUARD_hfst_tool_metadata_h

#if HAVE_CONFIG_H
#  include <config.h>
#endif


#include "HfstTransducer.h"
#include "HfstDataTypes.h"

void hfst_set_name(hfst::HfstTransducer& dest, const std::string& src,
                   const std::string& op);
void hfst_set_name(hfst::HfstTransducer& dest, const hfst::HfstTransducer& src,
                   const std::string& op);
void hfst_set_name(hfst::HfstTransducer& dest, const hfst::HfstTransducer& lhs,
                   const hfst::HfstTransducer& rhs, const std::string& op);

void hfst_set_formula(hfst::HfstTransducer& dest, const std::string& src,
                      const std::string& op);
void hfst_set_formula(hfst::HfstTransducer& dest,
                      const hfst::HfstTransducer& src,
                      const std::string& op);
void hfst_set_formula(hfst::HfstTransducer& dest,
                      const hfst::HfstTransducer& lhs,
                      const hfst::HfstTransducer& rhs,
                      const std::string& op);
void hfst_set_commandline_def(hfst::HfstTransducer& dest,
                              int argc, const char** argv);
void hfst_set_commandline_def(hfst::HfstTransducer& dest,
                              const hfst::HfstTransducer& src,
                              int argc, const char** argv);
void hfst_set_commandline_def(hfst::HfstTransducer& dest,
                              const hfst::HfstTransducer& lhs,
                              const hfst::HfstTransducer& rhs,
                              int argc, const char** argv);

char* hfst_get_name(const hfst::HfstTransducer& arg,
                    const std::string& filename);
   


#endif
// vim: set ft=cpp.doxygen:
