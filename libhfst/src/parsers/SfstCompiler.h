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

#ifndef _HFST_COMPILER_H_
#define _HFST_COMPILER_H_

#include "HfstDataTypes.h"
#include "SfstAlphabet.h"
#include <iosfwd>
#include <fstream>

namespace hfst
{
  using implementations::SfstAlphabet;

  typedef unsigned int Character;

    typedef struct range_t {
      Character character;
      struct range_t *next;
    } Range;
    
    typedef struct ranges_t {
      Range  *range;
      struct ranges_t *next;
    } Ranges;
    
    typedef struct contexts_t {
      HfstTransducer *left, *right;
      struct contexts_t *next;
    } Contexts;

    typedef enum {twol_left,twol_right,twol_both} Twol_Type;
    typedef enum {repl_left,repl_right,repl_up,repl_down} Repl_Type;

    
    /* A library class that forms a bridge between the SFST programming language parser
       and the HFST library and contains some extra functions needed by the parser.
       Most of these functions either directly use the SFST interface or are generalized
       versions of corresponding SFST functions that work on all types of HfstTransducers. */
    class SfstCompiler {
      
      struct ltstr {
    bool operator()(const char* s1, const char* s2) const
    { return strcmp(s1, s2) < 0; }
      };
      
      struct eqstr {
    bool operator()(const char* s1, const char* s2) const
    { return strcmp(s1, s2) == 0; }
      };
      
      typedef std::set<char*, ltstr> RVarSet;
      // using std::(tr1::)unordered_map directive comes from SfstAlphabet.h
      typedef unordered_map<char*,HfstTransducer*> VarMap;
      typedef unordered_map<char*,Range*> SVarMap;
      
    private:
      VarMap VM;
      SVarMap SVM;
      RVarSet RS;
      RVarSet RSS;
      HfstTransducer * result_;
      
    public:
      bool Verbose;
      bool Alphabet_Defined;
      SfstAlphabet TheAlphabet;
      ImplementationType compiler_type;
      std::string filename;
      std::string foldername;
      int switch_;
      
      SfstCompiler( ImplementationType type, bool verbose=false );
      
    public:
      void set_result(HfstTransducer * tr);
      HfstTransducer * get_result();
      void set_input(FILE * input);
      void set_filename(const std::string & name);
      void set_foldername(const std::string & name);
      void set_switch(int value);
      void parse();

      HfstTransducer * make_transducer(Range *r1, Range *r2, ImplementationType type);
      static void warn(const char *msg);
      HfstTransducer *new_transducer( Range*, Range*, ImplementationType );
      HfstTransducer *read_words( const char *folder, char *filename, ImplementationType type);
      HfstTransducer *read_transducer( const char *folder, char *filename, ImplementationType type );
      HfstTransducer *var_value( char *name );
      HfstTransducer *rvar_value( char *name, ImplementationType );
      Range *svar_value( char *name );
      Range *complement_range( Range* );
      Range *rsvar_value( char *name );
      Character character_code( unsigned int uc );
      Character symbol_code( char *s );
      //static unsigned int utf8toint( char *s );
      
      void write_to_file(HfstTransducer *t, const char *folder, char *filename);
      
      static Range *add_value( Character, Range*);
      static Range *add_var_values( char *name, Range*);
      Range *add_values( unsigned int, unsigned int, Range*);
      static Range *append_values( Range *r2, Range *r );
      static Ranges *add_range( Range*, Ranges* );
      //static void add_alphabet( HfstTransducer* );
      
      static Contexts *make_context( HfstTransducer *l, HfstTransducer *r );
      static Contexts *add_context( Contexts *nc, Contexts *c );
      
      HfstTransducer * substitute(HfstTransducer *t, Character old_char, Character new_char);
      HfstTransducer * substitute(HfstTransducer *t, Character old_char_in, Character old_char_out,
                  Character new_char_in, Character new_char_out);
      HfstTransducer * substitute(HfstTransducer *t, Character old_char_in, Character old_char_out,
                  HfstTransducer *tr);

      HfstTransducer * insert_freely(HfstTransducer *t, Character input, Character output);
      HfstTransducer * negation( HfstTransducer *t );
      
      // expand agreement variable markers
      HfstTransducer * explode( HfstTransducer *t );
      
      // rule operators
      HfstTransducer * replace_in_context(HfstTransducer * mapping, Repl_Type repl_type, Contexts *contexts, bool optional);
      HfstTransducer * replace(HfstTransducer * mapping, Repl_Type repl_type, bool optional);
      HfstTransducer * restriction( HfstTransducer * t, Twol_Type type, Contexts *c, int direction );
      HfstTransducer * make_rule( HfstTransducer * lc, Range * lower_range, Twol_Type type,
                  Range * upper_range, HfstTransducer * rc, ImplementationType implementation_type );
      
      void def_alphabet( HfstTransducer *a );
      bool def_var( char *name, HfstTransducer *a );
      bool def_rvar( char *name, HfstTransducer *a );
      bool def_svar( char *name, Range *r );
      
      HfstTransducer *make_mapping( Ranges*, Ranges*, ImplementationType );
      HfstTransducer *result( HfstTransducer*, bool );
      
      // from SFST's interface.C
      static void free_values( Range * );
      static void free_values( Ranges * );
      static bool in_range( unsigned int c, Range *r );
      static unsigned int utf8toint( char * );

      static Range *copy_values( const Range *r );
      

      static void error( const char *message );
      static void error2( const char *message, char *input );
    };
}

#endif
  

