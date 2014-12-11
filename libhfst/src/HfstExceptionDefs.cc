#include "HfstExceptionDefs.h"

std::string hfst_exception;
void hfst_set_exception(std::string name) {
  hfst_exception=name;
}
std::string hfst_get_exception() {
  return hfst_exception;
}

HfstException::HfstException(void) {}

HfstException::HfstException
(const std::string &name,const std::string &file,size_t line):
  name(name),
  file(file),
  line(line)
{}

std::string HfstException::operator() (void) const
{ 
  std::ostringstream o;
  o << "Exception: "<< name << " in file: " << file << " on line: " << line;
  return o.str();
}

//! Define a subclass of @a HfstException of type @a CHILD.
#define HFST_EXCEPTION_CHILD_DEFINITION(CHILD) \
    CHILD::CHILD \
      (const std::string &name,const std::string &file,size_t line):\
      HfstException(name,file,line)\
      {}

// Example defining an exception class SomeHfstException:
//HFST_EXCEPTION_CHILD_DEFINITION(SomeHfstException);

HFST_EXCEPTION_CHILD_DEFINITION(HfstTransducerTypeMismatchException);

HFST_EXCEPTION_CHILD_DEFINITION(ImplementationTypeNotAvailableException);

HFST_EXCEPTION_CHILD_DEFINITION(FunctionNotImplementedException);

HFST_EXCEPTION_CHILD_DEFINITION(StreamNotReadableException);

HFST_EXCEPTION_CHILD_DEFINITION(StreamCannotBeWrittenException);

HFST_EXCEPTION_CHILD_DEFINITION(StreamIsClosedException);

HFST_EXCEPTION_CHILD_DEFINITION(EndOfStreamException);

HFST_EXCEPTION_CHILD_DEFINITION(TransducerIsCyclicException);

HFST_EXCEPTION_CHILD_DEFINITION(NotTransducerStreamException);

HFST_EXCEPTION_CHILD_DEFINITION(NotValidAttFormatException);

HFST_EXCEPTION_CHILD_DEFINITION(NotValidPrologFormatException);

HFST_EXCEPTION_CHILD_DEFINITION(NotValidLexcFormatException);

HFST_EXCEPTION_CHILD_DEFINITION(StateIsNotFinalException);

HFST_EXCEPTION_CHILD_DEFINITION(ContextTransducersAreNotAutomataException);

HFST_EXCEPTION_CHILD_DEFINITION(TransducersAreNotAutomataException);

HFST_EXCEPTION_CHILD_DEFINITION(StateIndexOutOfBoundsException);

HFST_EXCEPTION_CHILD_DEFINITION(TransducerHeaderException);

HFST_EXCEPTION_CHILD_DEFINITION(MissingOpenFstInputSymbolTableException);

HFST_EXCEPTION_CHILD_DEFINITION(TransducerTypeMismatchException);

HFST_EXCEPTION_CHILD_DEFINITION(EmptySetOfContextsException);

HFST_EXCEPTION_CHILD_DEFINITION(SpecifiedTypeRequiredException);

HFST_EXCEPTION_CHILD_DEFINITION(HfstFatalException);

HFST_EXCEPTION_CHILD_DEFINITION(TransducerHasWrongTypeException);

HFST_EXCEPTION_CHILD_DEFINITION(IncorrectUtf8CodingException);

HFST_EXCEPTION_CHILD_DEFINITION(EmptyStringException);

HFST_EXCEPTION_CHILD_DEFINITION(SymbolNotFoundException);

HFST_EXCEPTION_CHILD_DEFINITION(MetadataException);

HFST_EXCEPTION_CHILD_DEFINITION(FlagDiacriticsAreNotIdentitiesException);

//HFST_EXCEPTION_CHILD_DEFINITION(SymbolRedefinedException); 
//HFST_EXCEPTION_CHILD_DEFINITION(TransducerHasNoStartStateException);
//HFST_EXCEPTION_CHILD_DEFINITION(TransducerHasMoreThanOneStartStateException);

