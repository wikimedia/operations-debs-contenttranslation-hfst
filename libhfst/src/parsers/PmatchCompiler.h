// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

//! @file PmatchCompiler.h
//!
//! @brief A class that encapsulates compilation of Xerox compatible regular
//!        expressions into HFST automata.
//!
//!        Xerox compatible regular expressions are a dialect of regular
//!        expressions commonly used for two-level finite state morphologies.
//!        The details can be found in Finite state morphology (2004) by
//!        Beesley and Karttunen.
//!
//!        This class is merely a wrapper around lex and yacc functions handling
//!        the parsing.

#ifndef GUARD_PmatchCompiler_h
#define GUARD_PmatchCompiler_h

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string>
#include "../HfstDataTypes.h"

namespace hfst {
//! @brief hfst::pmatch namespace is used for all functions related to Xerox
//! Regular Expresisions (PMATCH) parsing.
namespace pmatch {
//! @brief A compiler holding information needed to compile PMATCHs.
class PmatchCompiler
{
private:
    bool flatten;
    bool verbose;
    bool include_cosine_distances;
    std::string includedir;
  public:
  //! @brief Construct compiler for unknown format transducers.
  PmatchCompiler();
  //! @brief Create compiler for @a impl format transducers
  PmatchCompiler(hfst::ImplementationType impl);

  void set_flatten(bool val) { flatten = val; }
  void set_verbose(bool val) { verbose = val; }
  void set_include_cosine_distances(bool val)
        { include_cosine_distances = val; }

  //! @brief Add a definition macro.
  //!        Compilers will replace arcs labeled @a name, with the transducer
  //!        defined by @a pmatch in later phases of compilation.
  void define(const std::string& name, const std::string& pmatch);

  //! @brief Compile a transducer defined by @a pmatch.
  //!        May return a pointer to @e empty transducer on non-fatal error.
  //!        A null pointer is returned on fatal error, if abort is not called.
  std::map<std::string, HfstTransducer*> compile(const std::string& pmatch);
  void set_include_path(std::string path);

  private:
  std::map<std::string,hfst::HfstTransducer*> definitions_;
  hfst::ImplementationType format_;

}
;
}}
// vim:set ft=cpp.doxygen:
#endif


