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
#ifndef _HFST_INPUTSTREAM_H_
#define _HFST_INPUTSTREAM_H_

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include "HfstDataTypes.h"

/** @file HfstInputStream.h 
    \brief Declaration of class HfstInputStream.
 */

namespace hfst
{

  namespace implementations {
#if HAVE_OPENFST
    class LogWeightInputStream;
#if HAVE_OPENFST_LOG
    class TropicalWeightInputStream;
#endif
#endif
#if HAVE_SFST
    class SfstInputStream;
#endif
#if HAVE_FOMA
    class FomaInputStream;
#endif    
#if HAVE_MY_TRANSDUCER_LIBRARY
    class MyTransducerLibraryInputStream;
#endif
    class HfstOlInputStream;
  }


  /** \brief A stream for reading HFST binary transducers. 

      An example:
\verbatim
#include "HfstInputStream.h"

...

HfstInputStream *in = NULL;

try 
{
  in = new HfstInputStream("testfile");
} 
catch (StreamNotReadableException e) 
{
    std::cerr << "ERROR: File does not exist." << std::endl;
    exit(1);
}

int transducers_read = 0;

while (not in->is_eof()) 
{
  if (in->is_bad()) 
  {
  std::cerr << "ERROR: Stream cannot be read." << std::endl;
  exit(1); 
  }
  HfstTransducer t(*in);
  std::cerr << "One transducer successfully read." << std::endl;
  transducers_read++;
}

std::cerr << "Read " 
          << transducers_read 
          << " transducers in total."
      << std::endl;
in->close();
delete in;
\endverbatim

For documentation on the HFST binary transducer format, see
<a href="HeaderFormatAndConversions.html">here</a>.

      @see HfstTransducer::HfstTransducer(HfstInputStream &in) **/
  class HfstInputStream
  {
  protected:

    union StreamImplementation
    {
#if HAVE_SFST
      hfst::implementations::SfstInputStream * sfst;
#endif
#if HAVE_OPENFST
      hfst::implementations::TropicalWeightInputStream * tropical_ofst;
#if HAVE_OPENFST_LOG
      hfst::implementations::LogWeightInputStream * log_ofst;
#endif
#endif
#if HAVE_FOMA
      hfst::implementations::FomaInputStream * foma;
#endif

#if HAVE_MY_TRANSDUCER_LIBRARY
      hfst::implementations::MyTransducerLibraryInputStream * 
        my_transducer_library;
#endif

      hfst::implementations::HfstOlInputStream * hfst_ol;
    };

    /* The backend implementation */
    StreamImplementation implementation; 
    /* Implementation type */
    ImplementationType type;             
    /* Name of next transducer, given in the hfst header */
    std::string name;                    
    std::map<std::string,std::string> props;
    /* How many bytes have been already read by the function 
       when processing the hfst header */
    unsigned int bytes_to_skip;          
    /* The name of the file, if stdin, name is "" */
    std::string filename;                
    /* Whether the current transducer has an hfst header */
    bool has_hfst_header;                

    /* A special case where an OpenFst transducer has no symbol tables but an
       SFST alphabet is appended at the end. Should not occur very often, but
       possible when converting old transducers into version 3.0. transducers */
    bool hfst_version_2_weighted_transducer;
 
    /* The stream that the reading operations use when reading the first
       transducer. Then the type of the transducer is not known so there 
       is no backend implementation whose reading functions could be used.
       If input_stream==NULL, the backend implementation is used */
    std::istream * input_stream;

    /* Basic stream operators, work on input_stream (if not NULL) or on 
       the stream implementation. */

    /* Extract one character from the stream */
    char stream_get(); 

    /* Extract one character from the stream and store it in @a c. */
    char &stream_get(char &c);

    /* Extract one short from the stream and store it in @a i. */
    short &stream_get(short &i);

    /* Extract one unsigned short from the stream and store it in @a i. */
    unsigned short &stream_get(unsigned short &i);

    /* Return character c to the stream */
    void stream_unget(char c); 
    /* Whether the stream is at end */
    bool stream_eof(); 
    /* Get a string from the stream */
    std::string stream_getstring(); 
    /* Return the next character in the stream without extracting it */
    char stream_peek();  
    /* The stream implementation ignores n bytes. */
    void ignore(unsigned int n);

    /* The type of a transducer not supported directly by HFST version 3.0 
       but which can occur in conversion functions. */
    enum TransducerType { 
      /* See the above variable. */
      HFST_VERSION_2_WEIGHTED, 
      /* An SFST transducer with no alphabet, not supported. */
      HFST_VERSION_2_UNWEIGHTED_WITHOUT_ALPHABET,
      /* Old header + ordinary SFST transducer. */                
      HFST_VERSION_2_UNWEIGHTED,
      /* An OpenFst transducer, can cause problems if it does not have 
         symbol tables. */ 
      OPENFST_TROPICAL_,
      OPENFST_LOG_,
      /* An SFST transducer. */ 
      SFST_, 
      /* A foma transducer. */ 
      FOMA_, 
      /* Your transducer type */
      //MY_TRANSDUCER_LIBRARY_,
      /* Transducer type not recognized. */ 
      ERROR_TYPE_ 
    };

    /* Read a transducer from the stream. */
    void read_transducer(HfstTransducer &t);
    /* Type of next transducer in the stream. */
    ImplementationType stream_fst_type();

    // methods used by function stream_fst_type
    TransducerType guess_fst_type(int &bytes_read);
    bool read_hfst_header(int &bytes_read);
    bool read_library_header(int &bytes_read);
    int get_header_size(int &bytes_read);                        
    StringPairVector get_header_data(int header_size);                
    void process_header_data
      (StringPairVector &header_data, bool warnings=false); 
    bool set_implementation_specific_header_data
      (StringPairVector &data, unsigned int index);


    bool read_library_header_old(int &bytes_read);
    ImplementationType get_fst_type_old(int &bytes_read); 

  public:

    /** \brief Create a stream to standard input for reading binary 
        transducers. 

        @throws StreamNotReadableException 
        @throws NotTransducerStreamException
        @throws EndOfStreamException
        @throws TransducerHeaderException
    */
    HfstInputStream(void);

    /** \brief Open a stream to file \a filename for reading binary 
        transducers. 

        @pre The file exists. Otherwise, a StreamNotReadableException
    is thrown.

        @throws StreamNotReadableException 
        @throws NotTransducerStreamException
        @throws EndOfStreamException
        @throws TransducerHeaderException
    */
    HfstInputStream(const std::string &filename);

    /** \brief Destructor. */
    ~HfstInputStream(void);

    /** \brief Close the stream.

        If the stream points to standard input, nothing is done. */
    void close(void);

    /** \brief Whether the stream is at end. */
    bool is_eof(void);
    /** \brief Whether badbit is set. */
    bool is_bad(void);
    /** \brief Whether the state of the stream is good for input operations. */
    bool is_good(void);
    
    /** \brief The type of the first transducer in the stream. 

        By default, all transducers in a stream have the same type, else
        a TransducerTypeMismatchException is thrown when reading the first
    transducer that has a different type than the previous ones. */
    ImplementationType get_type(void) const;

    friend class HfstTransducer;
  };


}



#endif
