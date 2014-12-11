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

#ifndef _HFST_PROC_LOOKUP_PATH_
#define _HFST_PROC_LOOKUP_PATH_

#include "hfst-proc.h"
#include "transducer.h"
#include "HfstFlagDiacritics.h"

/**
 * Represents a (possibly partial) path through a transducer. This is used
 * during lookup for storing lookup paths that are continued as input symbols
 * are provided.
 */
class LookupPath
{
 protected:
  const ProcTransducer& transducer;
 
  /**
   * Points to the state in the transition index table or the transition table
   * where the path ends. This follows the normal semantics whereby values less
   * than TRANSITION_TARGET_TABLE_START reference the transition index table
   * while values greater than or equal to TRANSITION_TARGET_TABLE_START
   * reference the transition table
   */
  TransitionTableIndex index;
  
  /**
   * Whether the path ends at a final state
   */
  bool final;
  
  /**
   * The output symbols of the transitions this path has followed
   */
  SymbolNumberVector output_symbols;
  
 public:
  LookupPath(const ProcTransducer& t, const TransitionTableIndex initial): 
    transducer(t), index(initial), final(false), output_symbols() {}
  
  LookupPath(const LookupPath& o):
    transducer(o.transducer), index(o.index), final(o.final), output_symbols(o.output_symbols) {}
  
  virtual ~LookupPath() {}
  
  virtual LookupPath* clone() const {return new LookupPath(*this);}
  
  /**
   * Follow the transition index, modifying our index
   * @param index the index to follow
   */
  virtual void follow(const TransitionIndex& index);
  
  /**
   * Follow the transition, appending the output symbol
   * @param transition the transition to follow
   * @true if following the transition succeeded. This can fail because of
   *       e.g. flag diacritics in some subclasses
   */
  virtual bool follow(const Transition& transition);
  
  
  static bool compare_pointers(LookupPath* p1, LookupPath* p2) {return *p1<*p2;}
  
  virtual bool operator<(const LookupPath& o) const;
  
  TransitionTableIndex get_index() const {return index;}
  bool at_final() const {return final;}
  const SymbolNumberVector& get_output_symbols() const {return output_symbols;}
};

typedef std::set<LookupPath*, bool (*)(LookupPath*,LookupPath*)> LookupPathSet;

/**
 * A base class used by lookup path types that handle flag diacritics
 */
class PathFd
{
 protected:
  /**
   * The values of the flag diacritic features at the end of the path
   */
  FdState<SymbolNumber> fd_state;
  
  bool evaluate_flag_diacritic(SymbolNumber s);
  
  PathFd(const FdTable<SymbolNumber>& table):
    fd_state(table) {}
  PathFd(const PathFd& o): fd_state(o.fd_state) {}
  virtual ~PathFd() {}
};

/**
 * A lookup path which additionally stores the state of the flag diacritics on
 * the path and whose follow is conditional based on evaluation diacritics
 */
class LookupPathFd : public LookupPath, PathFd
{
 public:
  LookupPathFd(const ProcTransducer& t, const TransitionTableIndex initial):
    LookupPath(t, initial), PathFd(t.get_alphabet().get_fd_table()) {}
  LookupPathFd(const LookupPathFd& o): LookupPath(o), PathFd(o) {}
  
  virtual LookupPath* clone() const {return new LookupPathFd(*this);}
  
  virtual bool follow(const Transition& transition);
};

/**
 * A lookup path which additionally stores the summed weight of the path
 */
class LookupPathW : public LookupPath
{
 protected:
  /**
   * The summed weight of the transitions this path has followed
   */
  Weight weight;
  
  /**
   * An extra weight that is added to the sum when the path is at a final state
   */
  Weight final_weight;
 public:
  LookupPathW(const ProcTransducer& t, const TransitionTableIndex initial): 
  	LookupPath(t, initial), weight(0.0f), final_weight(0.0f) {}
  LookupPathW(const LookupPathW& o): LookupPath(o), weight(o.weight),
    final_weight(o.final_weight) {}
  
  virtual LookupPath* clone() const {return new LookupPathW(*this);}

  virtual void follow(const TransitionIndex& index);
  virtual bool follow(const Transition& transition);
  
  /**
   * This sorts first by weight then by the value of output_symbols
   */
  virtual bool operator<(const LookupPathW& o) const;
  
  Weight get_weight() const {return at_final() ? weight+final_weight : weight;}
};

/**
 * A lookup path with weight and flag diacritics
 */
class LookupPathWFd : public LookupPathW, PathFd
{
 public:
  LookupPathWFd(const ProcTransducer& t, const TransitionTableIndex initial):
    LookupPathW(t, initial), PathFd(t.get_alphabet().get_fd_table()) {}
  LookupPathWFd(const LookupPathWFd& o): LookupPathW(o), PathFd(o) {}
  
  virtual LookupPath* clone() const {return new LookupPathWFd(*this);}
  
  virtual bool follow(const Transition& transition);
};

#endif
