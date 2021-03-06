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

#ifndef _HFST_PROC_LOOKUP_STATE_H_
#define _HFST_PROC_LOOKUP_STATE_H_

#include "hfst-proc.h"
#include "lookup-path.h"

/**
 * Represents the current state of a lookup operation
 */
class LookupState
{
 private:
  /**
   * The transducer in which the lookup is occurring
   */
  const ProcTransducer& transducer;
  
  /**
   * The active paths in a lookup operation. At the start of a lookup this will
   * contain one path. The lookup has failed if it is ever empty.
   */
  LookupPathVector paths;
  
  
  /**
   * Delete all active paths and clear the list
   */
  void clear_paths();
  
  /**
   * Add a new path to the list of active paths
   * @param path the path to add
   */
  void add_path(LookupPath& path);
  
  /**
   * Get rid of the current paths and replace the list with a new list.
   * @param new_paths the new list of paths to store in the lookup state
   */
  void replace_paths(const LookupPathVector& new_paths);
  
  
  /**
   * Setup the state with a single initial path ending at starting state and
   * try epsilons at the initial position
   * @param initial an initial path to start the lookup
   */
  void init(LookupPath* initial);
  
  
  /**
   * Find any paths in the state that point to epsilon indices or epsilon
   * transitions, and generate additional paths by following the epsilons.
   * Because the additional paths are appended as they are generated, any
   * new epsilons generated by the epsilons will be properly handled
   */
  void try_epsilons();
  
  /**
   * If the given path points to a place in the index table with an epsilon
   * index, generate an additional path by following it
   * @param path a path pointing to the transition index table
   */
  void try_epsilon_index(const LookupPath& path);
  
  /**
   * If the given path points to one or more epsilon transitions, generate
   * additional paths by following them
   * @param path a path pointing to the beginning of a state in the transition
   *             table or directly to transitions
   */
  void try_epsilon_transitions(const LookupPath& path);
  
  
  /**
   * Find any paths in the state that have an index or transitions that match
   * the input symbol and generate a new set of paths by following the index
   * and/or transitions
   * @param input the input symbol to apply
   * @param altinput a secondary input symbol to try when input fails
   */
  void apply_input(const SymbolNumber input, const SymbolNumber altinput);
  
  /**
   * If the given path points to a place in the index table with an index for
   * the given input symbol, call try_transitions after having the path follow
   * the index
   * @param new_paths any new paths generated get appended here
   * @param path a path pointing to the transition index table
   * @param input the input symbol to look up in the transition index table
   * @return whether the path has a continuation with the given input
   */
  bool try_index(LookupPathVector& new_paths,
                 const LookupPath& path, const SymbolNumber input) const;
  
  /**
   * If the given path points to one or more transitions whose inputs match
   * the given input symbol, generate new paths by following them
   * @param new_paths any new paths generated get appended here
   * @param path a path pointing to the beginning of a state in the transition
   *             table or directly to transitions
   * @param input the input symbol to look up in the transition table
   * @return whether the path has a continuation with the given input
   */
  bool try_transitions(LookupPathVector& new_paths,
                       const LookupPath& path, const SymbolNumber input) const;
  
 public:
  /**
   * Set up a new lookup state, initializing it for doing a lookup in the
   * given transducer
   * @param t the transducer in which the lookup will occur
   */
  LookupState(const ProcTransducer& t): transducer(t), paths()
  {
    reset();
  }
  
  LookupState(const LookupState& o): transducer(o.transducer), paths()
  {
    for(LookupPathVector::const_iterator it=o.paths.begin(); it!=o.paths.end(); it++)
      paths.push_back((*it)->clone());
  }
  
  ~LookupState()
  {
    clear_paths();
  }
  
  /**
   * Clear any current lookup paths and prepare it for a new lookup
   */
  void reset()
  {
    init(transducer.get_initial_path());
  }
  
  /**
   * Determine whether there are any active paths
   * @true if there are any active paths
   */
  bool is_active() const
  {
    return !paths.empty();
  }
  
  int num_active() {return paths.size();}
  
  /**
   * Determine whether any active paths are at a final state
   * @true if an active path is at a final state
   */
  bool is_final() const;
  
  /**
   * Get a list of active paths that are at a final state
   * @return the active paths that are at a final state
   */
  const LookupPathVector get_finals() const;
  
  /**
   * Get the finals with duplicates removed
   */
  const LookupPathSet get_finals_set() const;
  
  /**
   * Do a lookup using all the given symbols. This is equivalent to stepping the
   * state with each of the symbols in the vector.
   */
  void lookup(const SymbolNumberVector& input, CapitalizationMode mode);
  
  /**
   * Apply a new input symbol to the state's active paths, and then follow any
   * epsilon transitions. If NO_SYMBOL_NUMBER is given, it has the effect of
   * "killing" all active paths. If altinput is anything besides
   * NO_SYMBOL_NUMBER, it will be used as a fallback to try in case the
   * symbol in input would result in terminating an active path.
   * @param input the new input symbol
   */
  void step(const SymbolNumber input, const SymbolNumber altinput = NO_SYMBOL_NUMBER);
  
  /**
   * Call the main step function, calculating what to pass for altinput based
   * on the given capitalization mode.
   * @param input the new input symbol
   * @param mode how to deal with capitalization. The modes are used as follows:
   *             IgnoreCase     - if input is lowercase then input as given and
   *                              no altinput. If input is uppercase then input
   *                              as given and altinput is the lowercase version
   *             CaseSensitive  - input as given, no altinput
   *             DictionaryCase - same as IgnoreCase
   */
  void step(const SymbolNumber input, CapitalizationMode mode);
};

#endif
