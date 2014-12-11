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

#ifndef _HFST_OL_TRANSDUCER_H_
#define _HFST_OL_TRANSDUCER_H_

#include <iostream>
#include <fstream>
#include "../HfstExceptionDefs.h"
#include "../HfstFlagDiacritics.h"
#include "../HfstExtractStrings.h"
#include "optimized-lookup/transducer.h"

/** @file HfstOlTransducer.h
    \brief Declaration of classes for HFST's optimized lookup 
    transducer format. */

namespace hfst { namespace implementations
{
  using std::ostream;
  using std::ofstream;
  using std::istream;
  using std::ifstream;
  using std::string;
  ;
  
  class HfstOlInputStream
  {
  private:
    std::string filename;
    ifstream i_stream;
    istream &input_stream;
    bool weighted;
    void skip_identifier_version_3_0(void);
    void skip_hfst_header(void);
  public:
    HfstOlInputStream(bool weighted);
    HfstOlInputStream(const std::string &filename, bool weighted);
    void open(void);
    void close(void);
    bool is_open(void) const;
    bool is_eof(void) const;
    bool is_bad(void) const;
    bool is_good(void) const;
    bool is_fst(void) const;

    char stream_get();
    short stream_get_short();
    void stream_unget(char c);
    void ignore(unsigned int n);
    
    bool operator() (void) const;
    hfst_ol::Transducer * read_transducer(bool has_header);
    
    // 1=unweighted, 2=weighted
    static int is_fst(FILE * f);
    static int is_fst(istream &s);
  };
  
  class HfstOlOutputStream 
  {
  private:
    std::string filename;
    ofstream o_stream;
    ostream &output_stream;
    bool weighted;
  public:
    HfstOlOutputStream(bool weighted);
    HfstOlOutputStream(const std::string &filename, bool weighted);
    void open(void);
    void close(void);
    void write(const char &c);
    void write_transducer(hfst_ol::Transducer * transducer);
  };
  
  class HfstOlTransducer
  {
   public:
    static hfst_ol::Transducer * create_empty_transducer(bool weighted);
    
    static bool is_cyclic(hfst_ol::Transducer* t);
    
    static void extract_paths
      (hfst_ol::Transducer * t, hfst::ExtractStringsCb& callback,
       int cycles=-1, const FdTable<hfst_ol::SymbolNumber>* fd=NULL, 
       bool filter_fd=false);
    static const FdTable<hfst_ol::SymbolNumber>* 
      get_flag_diacritics(hfst_ol::Transducer* t);
    static StringSet get_alphabet(hfst_ol::Transducer * t);

    
  };
  
} }

#endif
