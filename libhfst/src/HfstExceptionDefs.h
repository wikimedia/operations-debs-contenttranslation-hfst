// Copyright (c) 2016 University of Helsinki
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// See the file COPYING included with this distribution for more
// information.

#ifndef _HFST_EXCEPTION_DEFS_H_
#define _HFST_EXCEPTION_DEFS_H_

#include <string>
#include <sstream>

void hfst_set_exception(std::string name);
std::string hfst_get_exception();

#include "hfstdll.h"
#include "HfstDataTypes.h"

//! @file HfstExceptionDefs.h
//! @brief A file for exceptions

//! @brief Base class for HfstExceptions. Holds its own name and the file
//! and line number where it was thrown.
struct HfstException
{
  std::string name;
  std::string file;
  size_t line;
  HfstException(void);
  HfstException(const std::string &name,const std::string &file,size_t line);
  ~HfstException();
  //! @brief Get the error message.
  HFSTDLL std::string operator() (void) const;
  // An alias for python
  HFSTDLL std::string what() const;
};

//! @brief Macro to throw an exception of type @a E.
//! Use @a THROW instead of regular @a throw with subclasses of HfstException.
#define HFST_THROW(E) do {                              \
    hfst_set_exception(std::string(#E));                \
    throw E(#E,__FILE__,__LINE__);                    } \
  while(false)

//! @brief Macro to throw an exception of type @a E with message @a M.
//! Use @a THROW instead of regular @a throw with subclasses of HfstException.
#define HFST_THROW_MESSAGE(E,M) do {            \
    hfst_set_exception(std::string(#E));        \
    throw E(std::string(#E)+": "+std::string(M) \
            ,__FILE__,__LINE__); }              \
  while(false)

//! @brief Declare a subclass of @a HfstException of type @a CHILD.
#define HFST_EXCEPTION_CHILD_DECLARATION(CHILD) \
    struct CHILD : public HfstException \
    { CHILD(const std::string &name,const std::string &file,size_t line); }

//! Define a subclass of @a HfstException of type @a CHILD.
#define HFST_EXCEPTION_CHILD_DEFINITION(CHILD) \
    CHILD::CHILD \
      (const std::string &name,const std::string &file,size_t line):\
      HfstException(name,file,line)\
      {}

//! @brief Macro to catch exceptions thrown with HFST_THROW
#define HFST_CATCH(E)                                                   \
    catch (const E &e)                                                  \
    {                                                                   \
    std::cerr << e.file << ", line " << e.line << ": " <<       \
        e() << std::endl;                       \
    }

// Example declaring an exception class SomeHfstException:
//HFST_EXCEPTION_CHILD_DECLARATION(SomeHfstException);


//! @brief Two or more HfstTransducers are not of the same type
HFST_EXCEPTION_CHILD_DECLARATION(HfstTransducerTypeMismatchException);

/** \brief The library required by the implementation type requested
    is not linked to HFST.

An example:
\verbatim
try {
  HfstTransducer("foo", "bar", type);
} catch (ImplementationTypeNotAvailableException e) {
  fprintf(stderr, "ERROR: Type requested is not available.\n");
}
\endverbatim
*/
//HFST_EXCEPTION_CHILD_DECLARATION(ImplementationTypeNotAvailableException);

class ImplementationTypeNotAvailableException : public HfstException
{
 private:
  hfst::ImplementationType type;
 public:
  ImplementationTypeNotAvailableException(const std::string &name,const std::string &file,size_t line, hfst::ImplementationType type);
  hfst::ImplementationType get_type() const;
};


/** \brief Function has not been implemented (yet). */
HFST_EXCEPTION_CHILD_DECLARATION(FunctionNotImplementedException);

/** \brief Stream cannot be read.

Thrown by
hfst::HfstTransducer(const hfst::HfstInputStream&) and
hfst::HfstTransducer(FILE*, ImplementationType, const std::string&)

An example:
\verbatim
try {
  HfstInputStream in("foofile");
} catch (StreamNotReadableException e) {
  fprintf(stderr, "ERROR: file cannot be read.\n");
}
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(StreamNotReadableException);

/** \brief Stream cannot be written.

Thrown by hfst::HfstOutputStream::operator<< and
hfst::HfstTransducer::write_in_att_format

An example:
\verbatim
try {
  HfstTransducer tr("foo", FOMA_TYPE);
  HfstOutputStream out("testfile");
  out << tr;
} catch (StreamCannotBeWrittenException e) {
  fprintf(stderr, "ERROR: file cannot be written.\n");
}
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(StreamCannotBeWrittenException);

/** \brief Stream is closed.

    Thrown by hfst::HfstTransducer::write_in_att_format
    hfst::HfstTransducer(FILE*, ImplementationType, const std::string&)
    hfst::HfstTransducer(const hfst::HfstInputStream&)
    hfst::HfstOutputStream::operator<<

    An example:

\verbatim
try {
  HfstTransducer tr("foo", LOG_OPENFST_TYPE);
  HfstOutputStream out("testfile");
  out.close();
  out << tr;
} catch (StreamIsClosedException e) {
  fprintf(stderr, "ERROR: stream to file is closed.\n");
}
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(StreamIsClosedException);

/** \brief The stream is at end.

    Thrown by
    hfst::HfstTransducer(const hfst::HfstInputStream&)
    hfst::HfstInputStream()
    hfst::HfstInputStream(const std::string&)
*/
HFST_EXCEPTION_CHILD_DECLARATION(EndOfStreamException);

/** \brief Transducer is cyclic.

    thrown by hfst::HfstTransducer::extract_paths and
    hfst::HfstTransducer::extract_paths_fd. An example:
\verbatim
HfstTransducer transducer("a", "b", TROPICAL_OPENFST_TYPE);
transducer.repeat_star();
try {
  HfstTwoLevelPaths results;
  transducer.extract_paths(results);
  fprintf(stderr, "The transducer has %i paths\n", results.size());
} catch (TransducerIsCyclicException e) {
    fprintf(stderr, "The transducer is cyclic "
            " and has an infinite number of paths.\n");
}
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(TransducerIsCyclicException);


/** \brief The stream does not contain transducers.

    Thrown by
    hfst::HfstTransducer(const hfst::HfstInputStream&)
    hfst::HfstInputStream()
    hfst::HfstInputStream(const std::string&)

    An example. The file "foofile" contains
\verbatim
This is a text file.
Here is another line.
The file ends here.
\endverbatim

When we try to read it, an exception will be thrown:

\verbatim
try {
  HfstInputStream in("foofile");
} catch (NotTransducerStreamException e) {
  fprintf(stderr, "ERROR: file does not contain transducers.\n");
}
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(NotTransducerStreamException);

HFST_EXCEPTION_CHILD_DECLARATION(FileIsInGZFormatException);

/** \brief The stream is not in valid AT&T format.

    An example. The file "testfile.att" contains

\verbatim
0       1       a      b
1
c
\verbatim

When we try to read it, an exception is thrown:

\verbatim
std::vector<HfstTransducer> transducers;
FILE * ifile = fopen("testfile.att", "rb");
try {
  while (not eof(ifile))
    {
    HfstTransducer t(ifile, TROPICAL_OPENFST_TYPE, "epsilon");
    transducers.push_back(t);
    printf("read one transducer\n");
    }
} catch (NotValidAttFormatException e) {
    printf("Error reading transducer: not valid AT&T format.\n"); }
fclose(ifile);
fprintf(stderr, "Read %i transducers in total.\n", (int)transducers.size());
\endverbatim


    thrown by
    hfst::HfstTransducer::HfstTransducer(FILE*,ImplementationType,const std::string&)
*/
HFST_EXCEPTION_CHILD_DECLARATION(NotValidAttFormatException);

HFST_EXCEPTION_CHILD_DECLARATION(NotValidPrologFormatException);

HFST_EXCEPTION_CHILD_DECLARATION(NotValidLexcFormatException);

/** \brief State is not final (and cannot have a final weight).

    An example:

\verbatim
HfstBasicTransducer tr;
tr.add_state(1);
// An exception is thrown as state number 1 is not final
float w = tr.get_final_weight(1);
\endverbatim

You should use function is_final_state if you are not sure whether a
state is final.

    Thrown by hfst::implementations::HfstTransitionGraph::get_final_weight. */
HFST_EXCEPTION_CHILD_DECLARATION(StateIsNotFinalException);



/** \brief Context transducers are not automata.

    This exception is thrown by
    hfst::rules::replace_up(HfstTransducerPair&, HfstTransducer&, bool, StringPairSet&)
    when either context transducer does not have equivalent input and
    output symbols in all its transitions.

    An example:

\verbatim
ImplementationType type = SFST_TYPE;
// The second context transducer is
HfstTransducerPair contexts(HfstTransducer("c", type),
                            HfstTransducer("c", "d", type));
HfstTransducer mapping("a", "b", type);
StringPairSet alphabet;
alphabet.insert(StringPair("a", "a"));
alphabet.insert(StringPair("b", "b"));
alphabet.insert(StringPair("c", "c"));
alphabet.insert(StringPair("d", "d"));
hfst::rules::replace_up(contexts, mapping, true, alphabet);
\endverbatim

*/
HFST_EXCEPTION_CHILD_DECLARATION(ContextTransducersAreNotAutomataException);



/** \brief Transducers are not automata.

    This exception is thrown by
    hfst::cross_product( HfstTransducer&)

    when either input transducer does not have equivalent input and
    output symbols in all its transitions.
*/
HFST_EXCEPTION_CHILD_DECLARATION(TransducersAreNotAutomataException);

HFST_EXCEPTION_CHILD_DECLARATION(TransducerIsNotAutomatonException);

/** \brief The StateId argument is not valid.

    An example:

\verbatim
HfstBasicTransducer tr;
tr.add_state(1);
// An exception is thrown as there is no state number 2
float w = tr.get_final_weight(2);
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(StateIndexOutOfBoundsException);


/** \brief Transducer has a malformed HFST header.

    Thrown by hfst::HfstTransducer(HfstInputStream&)
    hfst::HfstInputStream()
    hfst::HfstInputStream(const std::string&)
*/
HFST_EXCEPTION_CHILD_DECLARATION(TransducerHeaderException);


/** \brief An OpenFst transducer does not have an input symbol table.

    When converting from OpenFst to tropical or log HFST, the OpenFst transducer
    must have at least an input symbol table. If the output symbol table
    is missing, it is assumed to be equivalent to the input symbol table.

    Thrown by hfst::HfstTransducer(HfstInputStream&)
*/
HFST_EXCEPTION_CHILD_DECLARATION(MissingOpenFstInputSymbolTableException);


/** \brief Two or more transducers do not have the same type.

    This can happen if (1) the calling and called transducer in a binary
    operation, (2) two transducers in an HfstTransducerPair,
    (3) two consecutive transducers coming from an HfstInputStream or
    (4) two transducers in a function taking two or more transducers as
    arguments do not have the same type.

    Thrown e.g. by
    HfstTransducer::disjunct(const HfstTransducer&)
    rules::two_level_if
    HfstTransducer(HfstInputStream&)

An example:
\verbatim
HfstTransducer foo("foo", SFST_TYPE);
HfstTransducer bar("bar", FOMA_TYPE);
foo.disjunct(bar);   // an exception is thrown
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(TransducerTypeMismatchException);



/** \brief The set of transducer pairs is empty.

    Thrown by rule functions in namespace #hfst::rules. An example:

\verbatim
    HfstTransducerPairVector contexts; // contexts is empty
    HfstTransducer rest = hfst::rules::restriction
      (contexts, mapping, alphabet, twol_type, direction);
\endverbatim
*/
HFST_EXCEPTION_CHILD_DECLARATION(EmptySetOfContextsException);



/* \brief The type of a transducer is not specified.

   This exception is thrown when an ImplementationType argument
   is ERROR_TYPE.

   @see hfst::ImplementationType
 */
HFST_EXCEPTION_CHILD_DECLARATION(SpecifiedTypeRequiredException);




/** \brief An error happened probably due to a bug in the HFST code. */
HFST_EXCEPTION_CHILD_DECLARATION(HfstFatalException);


/** \brief Transducer has wrong type.

    This exception suggests that an HfstTransducer has not been properly
    initialized, probably due to a bug in the HFST library. Alternatively
    the default constructor of HfstTransducer has been called at some point.

    @see hfst::HfstTransducer() */
HFST_EXCEPTION_CHILD_DECLARATION(TransducerHasWrongTypeException);

/** \brief String is not valid utf-8.

    This exception suggests that an input string is not valid utf8.

*/
HFST_EXCEPTION_CHILD_DECLARATION(IncorrectUtf8CodingException);

HFST_EXCEPTION_CHILD_DECLARATION(EmptyStringException);

HFST_EXCEPTION_CHILD_DECLARATION(SymbolNotFoundException);

HFST_EXCEPTION_CHILD_DECLARATION(FlagDiacriticsAreNotIdentitiesException);

//HFST_EXCEPTION_CHILD_DECLARATION(SymbolRedefinedException);
//HFST_EXCEPTION_CHILD_DECLARATION(TransducerHasNoStartStateException);
//HFST_EXCEPTION_CHILD_DECLARATION(TransducerHasMoreThanOneStartStateException);

HFST_EXCEPTION_CHILD_DECLARATION(MetadataException);


#endif // #ifndef _HFST_EXCEPTION_DEFS_H_
