// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _HFST_OUTPUTSTREAM_H_
#define _HFST_OUTPUTSTREAM_H_

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include "HfstDataTypes.h"

#include "hfstdll.h"

/** @file HfstOutputStream.h
    \brief Declaration of class HfstOutputStream. */

namespace hfst
{

  namespace implementations {
#if HAVE_OPENFST
#if HAVE_OPENFST_LOG || HAVE_LEAN_OPENFST_LOG
    class LogWeightOutputStream;
#endif
    class TropicalWeightOutputStream;
#endif
#if HAVE_SFST || HAVE_LEAN_SFST
    class SfstOutputStream;
#endif
#if HAVE_FOMA
    class FomaOutputStream;
#endif
#if HAVE_XFSM
    class XfsmOutputStream;
#endif
#if HAVE_MY_TRANSDUCER_LIBRARY
    class MyTransducerLibraryOutputStream;
#endif
    class HfstOlOutputStream;
  }


  /** \brief A stream for writing binary transducers.

      An example:
\verbatim
#include "HfstOutputStream.h"

      ...

      // Write three HFST transducers in binary format to file named "testfile"
      HfstOutputStream out("testfile", FOMA_TYPE);
      out << foma_transducer1
          << foma_transducer2
          << foma_transducer3;
      out.close();
\endverbatim

For more information on HFST transducer structure, see
<a href="HeaderFormatAndConversions.html">this page</a>.

  **/
  class HfstOutputStream
  {
  protected:
    union StreamImplementation
    {
#if HAVE_OPENFST
#if HAVE_OPENFST_LOG || HAVE_LEAN_OPENFST_LOG
      hfst::implementations::LogWeightOutputStream * log_ofst;
#endif
      hfst::implementations::TropicalWeightOutputStream * tropical_ofst;
#endif
#if HAVE_SFST || HAVE_LEAN_SFST
      hfst::implementations::SfstOutputStream * sfst;
#endif
#if HAVE_FOMA
      hfst::implementations::FomaOutputStream * foma;
#endif
#if HAVE_XFSM
      hfst::implementations::XfsmOutputStream * xfsm;
#endif

#if HAVE_MY_TRANSDUCER_LIBRARY
      hfst::implementations::MyTransducerLibraryOutputStream *
        my_transducer_library;
#endif

      hfst::implementations::HfstOlOutputStream * hfst_ol;
    };
    ImplementationType type; // type of the stream implementation
    // whether an hfst header is written before every transducer
    bool hfst_format;
    StreamImplementation implementation; // backend implementation

    // write data to stream
    void write(const std::string &s);
    void write(const std::vector<char> &s);
    void write(const char &c);

    // if file is open
    bool is_open;

    // append string s to vector str and a '\0'
    static void append(std::vector<char> &str, const std::string &s);

    // append obligatory HFST header data to \a header
    void append_hfst_header_data(std::vector<char> &header);
    /* append implementation-specific header data collected from
       \a transducer to \a header */
    void append_implementation_specific_header_data
      (std::vector<char> &header, HfstTransducer &transducer);


  public:

    /** \brief Create a stream to standard output for writing
        binary transducers of type \a type.
        \a hfst_format defines whether transducers are written
        in hfst format or as such in their backend format.
    */
    HFSTDLL HfstOutputStream(ImplementationType type, bool hfst_format=true);

    /** \brief Open a stream to file \a filename for writing binary transducers
        of type \a type.
        \a hfst_format defines whether transducers are written in hfst format
        or as such in their backend format.

        If the file exists, it is overwritten.
    */
    HFSTDLL HfstOutputStream(const std::string &filename, ImplementationType type, bool hfst_format=true);

    /** \brief Destructor. */
    HFSTDLL ~HfstOutputStream(void);

    /** \brief Flush the stream.

     If the stream is of XFSM_TYPE, all transducers inserted with the operator<<
     are actually written to the stream. Else, does nothing. */
    HFSTDLL HfstOutputStream &flush();

    /** \brief Write the transducer \a transducer in binary format
        to the stream.

        All transducers must have the same type as the stream, else a
        TransducerTypeMismatchException is thrown.

        If the stream is of XFSM_TYPE, \a transducer is stored to a list
        and written when flush() is called for the stream.

        @throws TransducerTypeMismatchException
    */
    HFSTDLL HfstOutputStream &operator<< (HfstTransducer &transducer);

    /** @brief An alias for operator<<.

     @see operator<< */
    HFSTDLL HfstOutputStream& redirect (HfstTransducer &transducer);

    /** \brief Close the stream.

        If the stream points to standard output, nothing is done. */
    HFSTDLL void close(void);
  };




}



#endif
