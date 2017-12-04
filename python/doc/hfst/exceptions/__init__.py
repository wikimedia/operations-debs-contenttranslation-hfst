## @package hfst.exceptions
## exceptions...

## Base class for HfstExceptions. Holds its own name and the file and line number where it was thrown.
class HfstException:
    ## A message describing the error in more detail.
    def what():
        pass

## Two or more HfstTransducers are not of the same type. Same as HfstTransducerTypeMismatchException ???
class HfstTransducerTypeMismatchException(HfstException):
    pass


## The library required by the implementation type requested is not linked to HFST.
class ImplementationTypeNotAvailableException(HfstException):
    pass


## Function has not been implemented (yet).
class FunctionNotImplementedException(HfstException):
    pass


## Flag diacritics encountered on one but not the other side of a transition.
class FlagDiacriticsAreNotIdentitiesException(HfstException):
    pass


## The input is not in valid prolog format.
class NotValidPrologFormatException(HfstException):
    pass


## Stream cannot be read.
class StreamNotReadableException(HfstException):
    pass


## Stream cannot be written.
#
# Thrown by #hfst.HfstOutputStream.write and #hfst.HfstTransducer.write_att
class StreamCannotBeWrittenException(HfstException):
    pass


## Stream is closed.
#
# Thrown by #hfst.HfstTransducer.write_att
# #hfst.HfstOutputStream.write
#
# An example:
#
# \verbatim
# try:
#     tr = hfst.regex('foo')
#     outstr = hfst.HfstOutputStream(filename='testfile')
#     outstr.close()
#     outstr.write(tr)
# except hfst.exceptions.StreamIsClosedException:
#     print("Could not write transducer: stream to file was closed.")
# \endverbatim
class StreamIsClosedException(HfstException):
    pass


## The stream is at end.
#
#     Thrown by
#     #hfst.HfstTransducer
#     #hfst.HfstInputStream.__init__
class EndOfStreamException(HfstException):
    pass


## Transducer is cyclic.
#
#     Thrown by #hfst.HfstTransducer.extract_paths. An example
# \verbatim
# transducer = hfst.regex('[a:b]*')
# try:
#     results = transducer.extract_paths(output='text')
#     print("The transducer has %i paths:" % len(results))
#     print(results)
# except hfst.exceptions.TransducerIsCyclicException:
#     print("The transducer is cyclic and has an infinite number of paths. Some of them:")
#     results = transducer.extract_paths(output='text', max_cycles=5)
#     print(results)
# \endverbatim
class TransducerIsCyclicException(HfstException):
    pass


## The stream does not contain transducers.
#
#     Thrown by
#     #hfst.HfstTransducer
#     #hfst.HfstInputStream.__init__
#
#     An example.
# \verbatim
# f = open('foofile', 'w')
# f.write('This is an ordinary text file.\n')
# f.close()
# try:
#     instr = hfst.HfstInputStream('foofile')
#     tr = instr.read()
#     print(tr)
#     instr.close()
# except hfst.exceptions.NotTransducerStreamException:
#     print("Could not print transducer: the file does not contain binary transducers.")
# \endverbatim
class NotTransducerStreamException(HfstException):
    pass


## The stream is not in valid AT&T format.
#
#     An example:
# \verbatim
# f = open('testfile1.att', 'w')
# f.write('0 1 a b\n\
# 1 2 c\n\
# 2\n')
# f.close()
# f = hfst.hfst_open('testfile1.att', 'r')
# try:
#     tr = hfst.read_att(f)
# except hfst.exceptions.NotValidAttFormatException:
#     print('Could not read file: it is not in valid ATT format.')
# f.close()
# \endverbatim
#     thrown by
#     #hfst.HfstTransducer.__init__
class NotValidAttFormatException(HfstException):
    pass


## The input is not in valid LexC format.
class NotValidLexcFormatException(HfstException):
    pass


## State is not final (and cannot have a final weight).
#
#     An example :
#
# \verbatim
# tr = hfst.HfstBasicTransducer()
# tr.add_state(1)
# # An exception is thrown as state number 1 is not final
# try:
#     w = tr.get_final_weight(1)
# except hfst.exceptions.StateIsNotFinalException:
#     print("State is not final.")
# \endverbatim
#
# You should use function #hfst.HfstBasicTransducer.is_final_state if you are not sure whether a
# state is final.
#
# Thrown by #hfst.HfstBasicTransducer get_final_weight.
class StateIsNotFinalException(HfstException):
    pass


## Transducers given as rule context are not automata.
# @see hfst.HfstTransducer.is_automaton()
class ContextTransducersAreNotAutomataException(HfstException):
    pass


## Transducers are not automata.
#
# Example:
# \verbatim
# tr1 = hfst.regex('foo:bar')
# tr2 = hfst.regex('bar:baz')
# try:
#     tr1.cross_product(tr2)
# except hfst.exceptions.TransducersAreNotAutomataException:
#     print('Transducers must be automata in cross product.')
# \endverbatim
#     This exception is thrown by
#     #hfst.HfstTransducer.cross_product
#     when either input transducer does not have equivalent input and
#     output symbols in all its transitions.
class TransducersAreNotAutomataException(HfstException):
    pass


## The state number argument is not valid.
#
#     An example :
#
# \verbatim
# tr = hfst.HfstBasicTransducer()
# tr.add_state(1)
# try:
#     w = tr.get_final_weight(2)
# except hfst.exceptions.StateIndexOutOfBoundsException:
#     print('State number 2 does not exist')
# \endverbatim
class StateIndexOutOfBoundsException(HfstException):
    pass


## Transducer has a malformed HFST header.
#
# Thrown by #hfst.HfstTransducer.__init__ #hfst.HfstInputStream
class TransducerHeaderException(HfstException):
    pass


## An OpenFst transducer does not have an input symbol table.
#
#     When converting from OpenFst to tropical or log HFST, the OpenFst transducer
#     must have at least an input symbol table. If the output symbol table
#     is missing, it is assumed to be equivalent to the input symbol table.
#
#     Thrown by hfst.HfstTransducer.__init__
class MissingOpenFstInputSymbolTableException(HfstException):
    pass


## Two or more transducers do not have the same type.
#
#     This can happen if (1) the calling and called transducer in a binary
#     operation, (2) two transducers in a pair of transducers,
#     (3) two consecutive transducers coming from an HfstInputStream or
#     (4) two transducers in a function taking two or more transducers as
#     arguments do not have the same type.
#
# An example:
# \verbatim
# hfst.set_default_fst_type(hfst.types.TROPICAL_OPENFST_TYPE)
# tr1 = hfst.regex('foo')
# tr2 = hfst.regex('bar')
# tr2.convert(hfst.types.FOMA_TYPE)
# try:
#     tr1.disjunct(tr2)
# except hfst.exceptions.TransducerTypeMismatchException:
#     print('The implementation types of transducers must be the same.')
# \endverbatim
class TransducerTypeMismatchException(HfstException):
    pass


## The set of transducer pairs is empty.
#
#     Thrown by rule functions.
class EmptySetOfContextsException(HfstException):
    pass


## The type of a transducer is not specified.
#
#    This exception is thrown when an implementation type argument
#    is hfst.types.ERROR_TYPE.
class SpecifiedTypeRequiredException(HfstException):
    pass


## An error happened probably due to a bug in the HFST code.
class HfstFatalException(HfstException):
    pass


## Transducer has wrong type.
#
#     This exception suggests that an HfstTransducer has not been properly
#     initialized, probably due to a bug in the HFST library. Alternatively
#     the default constructor of HfstTransducer has been called at some point.
#
#     @see #hfst.HfstTransducer.__init__
class TransducerHasWrongTypeException(HfstException):
    pass


## String is not valid utf-8.
#
#     This exception suggests that an input string is not valid utf8.
#
class IncorrectUtf8CodingException(HfstException):
    pass


## An argument string is an empty string.
# A transition symbol cannot be an empty string.
class EmptyStringException(HfstException):
    pass


## A bug in the HFST code.
class SymbolNotFoundException(HfstException):
    pass


## A piece of metadata in an HFST header is not supported.
class MetadataException(HfstException):
    pass
