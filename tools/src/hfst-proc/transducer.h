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

#ifndef _HFST_PROC_TRANSDUCER_H_
#define _HFST_PROC_TRANSDUCER_H_

#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include "hfst-proc.h"
#include "tokenizer.h"
#include "alphabet.h"

#include "implementations/optimized-lookup/transducer.h"

using namespace hfst_ol;

class ProcTransducer;

typedef LookupPath* (*InitialPathCreator)(const ProcTransducer&);

class ProcTransducer : public Transducer
{
 protected:
  static InitialPathCreator initial_path_creators[2][2];

  /**
   * Check if the transducer accepts an input string consisting of just a blank
   */
  bool check_for_blank() const;
 public:
  ProcTransducer(std::istream& is);

  const ProcTransducerAlphabet& get_alphabet() const {return *static_cast<ProcTransducerAlphabet*>(alphabet);}

  bool is_epsilon(const Transition& transition) const;

  /**
   * Create a new lookup path appropriate for initializing a lookup operation.
   * @return a new lookup path pointing to the beginning of the transducer
   */
  LookupPath* get_initial_path() const;
};

#endif
