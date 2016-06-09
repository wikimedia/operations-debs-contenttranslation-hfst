## @package libhfst 
# HFST API for Python

## @mainpage
#
# HFST - The Helsinki Finite-State Transducer technology is intended for creating and manipulating weighted or unweighted synchronic transducers implementing regular relations.
# UTF-8 is chosen as the character encoding used in HFST software. Currently, HFST has been implemented using the
# <a href="http://www.ims.uni-stuttgart.de/projekte/gramotron/SOFTWARE/SFST.html">SFST</a>, 
# <a href="http://www.openfst.org">OpenFst</a> and 
# <a href="http://code.google.com/p/foma/">foma</a> software libraries.
# Other versions may be added in some future release. SFST and foma implementations are unweighted and OpenFst implementation is weighted.
#
# Part of HFST interface has been implemented for HFST's own two transducer formats, HfstBasicTransducer and optimized lookup format.
# The previous is useful for accessing individual states and transitions of a transducer, converting between transducer formats and storing transducers in an implementation-independent format. 
# The latter is used for fast lookup of strings in a transducer.
#
# All back-end implementations - SFST, OpenFst and foma - work according to the same interface, so it is possible to compile the same piece of code using different back-end libraries.
# There are some differences related to weights, as only OpenFst supports them.
#
# For a quick start to the HFST interface with examples, see <a href="QuickStart.html">here</a>.
#
# The examples given in this documentation use <a href="http://www.fsmbook.com/">Xerox transducer notation</a>.
#
# <br>
#
# \section features Features
#
#   - Create transducers and apply \link libhfst.HfstTransducer operations\endlink on them
#
#   - Create transducers \link libhfst.HfstBasicTransducer from scratch\endlink
#
#   - \link libhfst.HfstBasicTransducer.states Iterate\endlink through a transducer's states and transitions
#
#   - Create transducers by \link libhfst.HfstTokenizer tokenizing\endlink UTF-8 strings with multicharacter symbols
#
#   - Apply two-level, replace, restriction and coercion \link libhfst.two_level_if rules\endlink
#
#
# \section tutorial Tutorial
#
#   - A <a href="QuickStart.html">quick start</a> to the HFST interface with examples
#
#   - <a href="HfstWithSFSTOpenFstAndFoma.html">Using HFST</a> with SFST, OpenFst and foma
#
# \section download_hfst Download
#
#   - <a href="https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstDownloads">Download and install</a> the HFST interface and command line tools
#
#
#\section links Links
#
#   - <a href="https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstCommandLineToolFunctionalities">Examples</a> of programs implemented using the HFST interface
#
#   - <a href="https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstHome">Documentation</a> of the HFST project
#
#   <br>


## Base class for HfstExceptions. Holds its own name and the file and line number where it was thrown.
class HfstException:
    ## The name of the exception. 
    self.name
    ## The source file where the exception originated.
    self.file
    ## The line of the source file where the exception originated.
    self.line

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
# Thrown by #libhfst.HfstOutputStream.write and #libhfst.HfstTransducer.write_att
class StreamCannotBeWrittenException(HfstException):
    pass

## Stream is closed. 
# 
# Thrown by #libhfst.HfstTransducer.write_att
# #libhfst.HfstOutputStream.write
# 
# An example: 
# 
# \verbatim
# try:
#     tr = libhfst.regex('foo')
#     outstr = libhfst.HfstOutputStream(filename='testfile')
#     outstr.close()
#     outstr.write(tr)
# except libhfst.StreamIsClosedException:
#     print("Could not write transducer: stream to file was closed.")
# \endverbatim
class StreamIsClosedException(HfstException):
    pass

## The stream is at end.
# 
#     Thrown by
#     #libhfst.HfstTransducer
#     #libhfst.HfstInputStream.__init__
class EndOfStreamException(HfstException):
    pass

## Transducer is cyclic. 
# 
#     Thrown by #libhfst.HfstTransducer.extract_paths. An example 
# \verbatim
# transducer = libhfst.regex('[a:b]*')
# try:
#     results = transducer.extract_paths(output='text')
#     print("The transducer has %i paths:" % len(results))
#     print(results)
# except libhfst.TransducerIsCyclicException:
#     print("The transducer is cyclic and has an infinite number of paths. Some of them:")
#     results = transducer.extract_paths(output='text', max_cycles=5)
#     print(results)
# \endverbatim
class TransducerIsCyclicException(HfstException):
    pass

## The stream does not contain transducers. 
# 
#     Thrown by 
#     #libhfst.HfstTransducer
#     #libhfst.HfstInputStream.__init__
# 
#     An example. 
# \verbatim
# f = open('foofile', 'w')
# f.write('This is an ordinary text file.\n')
# f.close()
# try:
#     instr = libhfst.HfstInputStream('foofile')
#     tr = instr.read()
#     print(tr)
#     instr.close()
# except libhfst.NotTransducerStreamException:
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
# f = libhfst.hfst_open('testfile1.att', 'r')
# try:
#     tr = libhfst.read_att(f)
# except libhfst.NotValidAttFormatException:
#     print('Could not read file: it is not in valid ATT format.')
# f.close()
# \endverbatim
#     thrown by 
#     #libhfst.HfstTransducer.__init__
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
# tr = libhfst.HfstBasicTransducer()
# tr.add_state(1)
# # An exception is thrown as state number 1 is not final
# try:
#     w = tr.get_final_weight(1)
# except libhfst.StateIsNotFinalException:
#     print("State is not final.")
# \endverbatim
# 
# You should use function #libhfst.HfstBasicTransducer.is_final_state if you are not sure whether a
# state is final.
# 
# Thrown by #libhfst.HfstBasicTransducer get_final_weight.
class StateIsNotFinalException(HfstException):
    pass

## Transducers given as rule context are not automata.
# @see libhfst.HfstTransducer.is_automaton()
class ContextTransducersAreNotAutomataException(HfstException):
    pass

## Transducers are not automata.
#
# Example: 
# \verbatim
# tr1 = libhfst.regex('foo:bar')
# tr2 = libhfst.regex('bar:baz')
# try:
#     tr1.cross_product(tr2)
# except libhfst.TransducersAreNotAutomataException:
#     print('Transducers must be automata in cross product.')
# \endverbatim 
#     This exception is thrown by
#     #libhfst.HfstTransducer.cross_product
#     when either input transducer does not have equivalent input and
#     output symbols in all its transitions.
class TransducersAreNotAutomataException(HfstException):
    pass

## The state number argument is not valid.
# 
#     An example :
# 
# \verbatim
# tr = libhfst.HfstBasicTransducer()
# tr.add_state(1)
# try:
#     w = tr.get_final_weight(2)
# except libhfst.StateIndexOutOfBoundsException:
#     print('State number 2 does not exist')
# \endverbatim
class StateIndexOutOfBoundsException(HfstException):
    pass

## Transducer has a malformed HFST header. 
# 
# Thrown by #libhfst.HfstTransducer.__init__ #libhfst.HfstInputStream
class TransducerHeaderException(HfstException):
    pass

## An OpenFst transducer does not have an input symbol table. 
# 
#     When converting from OpenFst to tropical or log HFST, the OpenFst transducer
#     must have at least an input symbol table. If the output symbol table
#     is missing, it is assumed to be equivalent to the input symbol table.
# 
#     Thrown by libhfst.HfstTransducer.__init__
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
# libhfst.set_default_fst_type(libhfst.TROPICAL_OPENFST_TYPE)
# tr1 = libhfst.regex('foo')
# tr2 = libhfst.regex('bar')
# tr2.convert(libhfst.FOMA_TYPE)
# try:
#     tr1.disjunct(tr2)
# except libhfst.TransducerTypeMismatchException:
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
#    is ERROR_TYPE.
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
#     @see #libhfst.HfstTransducer.__init__
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

## An SFST transducer, unweighted.
SFST_TYPE = _libhfst.SFST_TYPE

## An OpenFst transducer with tropical weights.
TROPICAL_OPENFST_TYPE = _libhfst.TROPICAL_OPENFST_TYPE

## An OpenFst transducer with logarithmic weights (limited support). 
LOG_OPENFST_TYPE = _libhfst.LOG_OPENFST_TYPE

## A foma transducer, unweighted.
FOMA_TYPE = _libhfst.FOMA_TYPE

## An HFST optimized lookup transducer, unweighted.
HFST_OL_TYPE = _libhfst.HFST_OL_TYPE

## An HFST optimized lookup transducer with weights.
HFST_OLW_TYPE = _libhfst.HFST_OLW_TYPE

## HFST2 header present, conversion required.
HFST2_TYPE = _libhfst.HFST2_TYPE

## Format left open by e.g. default constructor.
UNSPECIFIED_TYPE = _libhfst.UNSPECIFIED_TYPE

## Type not recognised. This type might be returned by a function if an error occurs.
ERROR_TYPE = _libhfst.ERROR_TYPE

## Push weights toward initial state.
# @see #libhfst.HfstTransducer.push_weights
TO_INITIAL_STATE = _libhfst.TO_INITIAL_STATE

## Push weights toward final state(s).
# @see #libhfst.HfstTransducer.push_weights
TO_FINAL_STATE = _libhfst.TO_FINAL_STATE


## A wrapper class for file operations.
# @see libhfst.hfst_open, libhfst.hfst_stdin, libhfst.hfst_stdout, libhfst.hfst_stderr
class HfstFile:
    ## Close the file. 
    def close(self):
        pass
    ## Write string to the file.
    # @param str String to be written.
    def write(self, str):
        pass
    ## Whether the file is at end.
    def is_eof(self):
        pass

## Open file named \a filename in mode \a mode.
# @param filename The name of the file.
# @param mode Mode in which the file is opened.
def hfst_open(filename, mode):
    pass
## Get file that points to standard input.
def hfst_stdin():
    pass
## Get file that points to standard output.
def hfst_stdout():
    pass
## Get file that points to standard error stream.
def hfst_stderr():
    pass

## Set the default implementation type.
# @param impl An libhfst.ImplementationType.
#
# Set the implementation type (SFST_TYPE, TROPICAL_OPENFST_TYPE, FOMA_TYPE) that is
# used by default by all operations that create transducers. The default value is
# TROPICAL_OPENFST_TYPE
def set_default_fst_type(impl):
    pass
## Get default transducer implementation type.
# If the default type is not set, it defaults to libhfst.TROPICAL_OPENFST_TYPE
def get_default_fst_type():
    pass
## Get a string representation of transducer implementation type \a type.
# @param type An libhfst.ImplementationType.
def fst_type_to_string(type):
    pass

## The string for epsilon symbol.
# An example:
# \verbatim
# fsm = libhfst.HfstBasicTransducer()
# fsm.add_state(1)
# fsm.set_final_weight(1, 2.0)
# fsm.add_transition(0, 1, "foo", libhfst.EPSILON)
# if not libhfst.HfstTransducer(fsm).compare(libhfst.regex('foo:0::2.0')):
#     raise RuntimeError('')
# \endverbatim
# @note In regular expressions, "0" is used for the epsilon.
# @see <a href="Symbols.html">Symbols</a>
EPSILON='@_EPSILON_SYMBOL_@'
## The string for unknown symbol.
# An example:
# \verbatim
# fsm = libhfst.HfstBasicTransducer()
# fsm.add_state(1)
# fsm.set_final_weight(1, -0.5)
# fsm.add_transition(0, 1, "foo", libhfst.UNKNOWN)
# fsm.add_transition(0, 1, "foo", "foo")
# if not libhfst.HfstTransducer(fsm).compare(libhfst.regex('foo:?::-0.5')):
#     raise RuntimeError('')
# \endverbatim
# @note In regular expressions, "?" on either or both sides of a transition is used for the unknown symbol.
# @see <a href="Symbols.html">Symbols</a>
UNKNOWN='@_UNKNOWN_SYMBOL_@'
## The string for identity symbol.
# An example:
# \verbatim
# fsm = libhfst.HfstBasicTransducer()
# fsm.add_state(1)
# fsm.set_final_weight(1, 1.5)
# fsm.add_transition(0, 1, libhfst.IDENTITY, libhfst.IDENTITY)
# if not libhfst.HfstTransducer(fsm).compare(libhfst.regex('?::1.5')):
#     raise RuntimeError('')
# \endverbatim
# @note In regular expressions, a single "?" is used for the identity symbol.
# @see <a href="Symbols.html">Symbols</a>
IDENTITY='@_IDENTITY_SYMBOL_@'

## Get a transducer that recognizes one or more paths.
# @param arg See example below
#
# Possible inputs:
# \verbatim
# One unweighted identity path:
# 'foo'  ->  [f o o]
# Weighted path: a tuple of string and number, e.g. 
# ('foo',1.4)
# ('bar',-3)
# ('baz',0)
# Several paths: a list or a tuple of paths and/or weighted paths, e.g.
# ['foo', 'bar']
# ('foo', ('bar',5.0))
# ('foo', ('bar',5.0), 'baz', 'Foo', ('Bar',2.4))
# [('foo',-1), ('bar',0), ('baz',3.5)]
# A dictionary mapping strings to any of the above cases:
# {'foo':'foo', 'bar':('foo',1.4), 'baz':(('foo',-1),'BAZ')}
# \endverbatim
def fst(arg):
    pass

## Get a transducer that recognizes the concatenation of symbols or symbol pairs in \a arg.
# @param arg The symbols or symbol pairs that form the path to be recognized.
#
# Example 
# \verbatim
# import libhfst
# tok = libhfst.HfstTokenizer()
# tok.add_multichar_symbol('foo')
# tok.add_multichar_symbol('bar')
# tr = libhfst.tokenized_fst(tok.tokenize('foobar', 'foobaz'))
# \endverbatim
# will create the transducer [foo:foo bar:b 0:a 0:z]
def tokenized_fst(arg, weight=0):
    pass

## Get an empty transducer.
# Empty transducer has one state that is not final, i.e. it does not recognize any string.
def empty_fst():
    pass

## Get an epsilon transducer.
# @param weight The weight of the final state.
# Epsilon transducer has one state that is final (with final weight \a weight), i.e. it recognizes the empty string.
def epsilon_fst(weight=0):
    pass

## Get a transducer as defined by regular expression \a regexp.
# @param regexp The regular expression defined with <a href="http://www.fsmbook.com/">Xerox transducer notation</a>.
# @param kvargs Argumnets recognized are: error.
# @param error Where warnings and errors are printed. Possible values are sys.stdout, sys.stderr (the default), a StringIO or None, indicating a quiet mode.
def regex(regexp, **kvargs):
    pass

## Compile lexc file \a filename into a transducer.
# @param filename The name of the lexc file.
# @param kvargs Arguments recognized are: verbosity, with_flags, output.
# @param verbosity The verbosity of the compiler, defaults to 0 (silent). Possible values are: 0, 1, 2.
# @param with_flags Whether lexc flags are used when compiling, defaults to False.
# @param output Where output is printed. Possible values are sys.stdout, sys.stderr, a StringIO, sys.stderr being the default?
def compile_lexc_file(filename, **kvargs):
    pass

## Compile (is 'run' a better term?) xfst file \a filename.
# @param filename The name of the xfst file.
# @param kvargs Arguments recognized are: verbosity, quit_on_fail, output, type.
# @param verbosity The verbosity of the compiler, defaults to 0 (silent). Possible values are: 0, 1, 2.
# @param quit_on_fail Whether the script is exited on any error, defaults to True.
# @param output Where output is printed. Possible values are sys.stdout, sys.stderr, a StringIO, sys.stderr being the default?
# @param type Implementation type of the compiler, defaults to libhfst.get_default_fst_type().
def compile_xfst_file(filename, **kvargs):
    pass

## Start interactive xfst compiler.
# @param kvargs Arguments recognized are: type, quit_on_fail.
# @param quit_on_fail Whether the compiler exits on any error, defaults to False.
# @param type Implementation type of the compiler, defaults to libhfst.get_default_fst_type().
def start_xfst(**kvargs):
    pass

## Read AT&T input from the user and return a transducer.
# @return An HfstTransducer whose type is libhfst.get_default_fst_type().
# Read one AT&T line at a time from standard input and create an equivalent transducer.
# An empty line signals the end of input.
def read_att_input():
    pass

## Read a multiline string \a att and return a transducer.
# @param att A string in AT&& format that defines the transducer.
# @return An HfstTransducer whose type is libhfst.get_default_fst_type().
# Read \a att and create a transducer as defined in it.
def read_att_string(att):
    pass

## Read next transducer from AT&T file pointed by \a f. \a epsilonstr defines the symbol used for epsilon in the file.
# @param f A file pointer (#libhfst.HfstFile) to the file.
# @param epsilonstr How epsilon is represented in the file. By default, "@_EPSILON_SYMBOL_@" and "@0@" are both recognized.
#
# If the file contains several transducers, they must be separated by "--" lines.
    # In AT&T format, the transition lines are of the form:
    # 
    # \verbatim 
    # [0-9]+[\w]+[0-9]+[\w]+[^\w]+[\w]+[^\w]([\w]+(-)[0-9]+(\.[0-9]+)) 
    # \endverbatim
    # 
    # and final state lines:
    # 
    # \verbatim
    # [0-9]+[\w]+([\w]+(-)[0-9]+(\.[0-9]+))
    # \endverbatim
    # 
    # If several transducers are listed in the same file, they are separated by lines of 
    # two consecutive hyphens "--". If the weight 
    # \verbatim
    # ([\w]+(-)[0-9]+(\.[0-9]+))
    # \endverbatim
    # is missing, the transition or final state is given a zero weight.
    # 
    # NOTE: If transition symbols contains spaces, they must be escaped
    # as '\@_SPACE_\@' because spaces are used as field separators.
    # Both '\@0\@' and '\@_EPSILON_SYMBOL_\@' are always interpreted as
    # epsilons.
    # 
    # 
    # An example: 
    # \verbatim
    # 0      1      foo      bar      0.3
    # 1      0.5
    # --
    # 0      0.0
    # --
    # --
    # 0      0.0
    # 0      0      a        <eps>    0.2
    # \endverbatim
    # 
    # The example lists four transducers in AT&T format: 
    # one transducer accepting the string pair &lt;'foo','bar'&gt;, one
    # epsilon transducer, one empty transducer and one transducer 
    # that accepts any number of 'a's and produces an empty string
    # in all cases. The transducers can be read with the following commands (from a file named 
    # 'testfile.att'):
    # \verbatim
    # transducers = []
    # ifile = libhfst.hfst_open('testfile2.att', 'r')
    # try:
    #     while (not ifile.is_eof()):
    #         t = libhfst.read_att(ifile, '<eps>')
    #         transducers.append(t)
    #         print("read one transducer")
    # except libhfst.NotValidAttFormatException:
    #     print("Error reading transducer: not valid AT&T format.")
    # ifile.close()
    # print("Read %i transducers in total" % len(transducers))
    # \endverbatim
    # 
    # Epsilon will be represented as libhfst.EPSILON in the resulting transducer.
    # The argument \a epsilon_symbol only denotes how epsilons are represented 
    # in \a ifile.
    # 
    # @throws NotValidAttFormatException 
    # @throws StreamNotReadableException
    # @throws StreamIsClosedException
    # @throws EndOfStreamException
    # @see #write_att
def read_att(f, epsilonstr=libhfst.EPSILON):
    pass

## Read next transducer from prolog file pointed by \a f.
# @param f A file pointer (#libhfst.HfstFile) to the file.
#
# If the file contains several transducers, they must be separated by empty lines.
def read_prolog(f):
    pass

## A simple transducer class with tropical weights. 
#
#    An example of creating an HfstBasicTransducer [foo:bar baz:baz] 
#    with weight 0.4 from scratch:
#
# \verbatim
#  # Create an empty transducer
#  # The transducer has initially one start state (number zero) 
#  # that is not final
#  fsm = libhfst.HfstBasicTransducer()
#  # Add two states to the transducer
#  fsm.add_state(1)
#  fsm.add_state(2)
#  # Create a transition [foo:bar] leading to state 1 with weight 0.1
#  tr = libhfst.HfstBasicTransition(1, 'foo', 'bar', 0.1)
#  # and add it to state zero
#  fsm.add_transition(0, tr)
#  # Add a transition [baz:baz] with weight 0 from state 1 to state 2 
#  fsm.add_transition(1, libhfst.HfstBasicTransition(2, 'baz', 'baz', 0.0))
#  # Set state 2 as final with weight 0.3
#  fsm.set_final_weight(2, 0.3)
# \endverbatim
#
#    An example of iterating through the states and transitions of the above transducer
#    when printing them in AT&T format to standard output:
#
# \verbatim
#  # Go through all states
#  for state, arcs in enumerate(fsm):
#    for arc in arcs:
#      print('%i ' % (state), end='')
#      print(arc)
#    if fsm.is_final_state(state):
#      print('%i %f' % (state, fsm.get_final_weight(state)) )
# \endverbatim
#
# @see #libhfst.HfstBasicTransition
class HfstBasicTransducer:

    # OMIT:
    # HfstBasicTransducer(FILE *file);
    # HfstBasicTransducer &operator=(const HfstBasicTransducer &graph);
    # void add_symbols_to_alphabet(const HfstSymbolPairSet &symbols);
    # void prune_alphabet_after_substitution(const std::set<unsigned int> &symbols);
    # const HfstTransitions & operator[](HfstState s) const;
    # void write_in_xfst_format(std::ostream &os, bool write_weights=true);
    # void write_in_prolog_format(std::ostream & os, const std::string & name, bool write_weights=true);
    # static HfstBasicTransducer read_in_prolog_format(std::istream &is, FILE *file, unsigned int & linecount);
    # static HfstBasicTransducer read_in_prolog_format(std::istream &is, unsigned int & linecount);
    # void write_in_att_format(std::ostream &os, bool write_weights=true); 
    # void write_in_att_format_number(FILE *file, bool write_weights=true);
    # static HfstBasicTransducer read_in_att_format(std::istream &is, FILE *file, std::string epsilon_symbol, unsigned int & linecount);
    # static HfstBasicTransducer read_in_att_format(std::istream &is, std::string epsilon_symbol, unsigned int & linecount);
    # HfstBasicTransducer & substitute(bool (*func)(const HfstSymbolPair &sp, HfstSymbolPairSet &sps) );

    # ONE FUNCTION WITH KEYWORD ARGUMENTS HANDLES ALL THESE
    # HfstBasicTransducer &substitute(const HfstSymbol &old_symbol, const HfstSymbol  &new_symbol, bool input_side=true, bool output_side=true);
    # HfstBasicTransducer &substitute_symbols(const HfstSymbolSubstitutions &substitutions);
    # HfstBasicTransducer &substitute_symbol_pairs(const HfstSymbolPairSubstitutions &substitutions);
    # HfstBasicTransducer &substitute(const HfstSymbolPair &sp, const HfstSymbolPairSet &sps);
    # HfstBasicTransducer &substitute(const HfstSymbolPair &old_pair, const HfstSymbolPair &new_pair);         
    # HfstBasicTransducer &substitute(const HfstSymbolPair &sp, const HfstBasicTransducer &graph);

    # TODO?:
    # static HfstBasicTransducer intersect(HfstBasicTransducer & graph1, HfstBasicTransducer & graph2);
    # HfstBasicTransducer &complete();
    # std::vector<std::set<HfstState> > topsort(SortDistance dist) const;
    # std::vector<unsigned int> path_sizes();         
    # bool is_lookup_infinitely_ambiguous(const HfstOneLevelPath & s);
    # bool is_lookup_infinitely_ambiguous(const StringVector & s);         
    # void insert_transducer(HfstState state1, HfstState state2, const HfstBasicTransducer & graph);

    ## The length of the longest path in transducer.
    # 
    # Length of a path means number of arcs on that path.
    def longest_path_size(self):
        pass

    ## Whether the transducer is infinitely ambiguous.
    #
    # A transducer is infinitely ambiguous if there exists an input that will yield infinitely many results,
    # i.e. there are input epsilon loops that are traversed with that input.
    def is_infinitely_ambiguous(self):
        pass

    ## Whether the transducer is infinitely ambiguous with input \a str.
    #
    # @param str The input.
    #
    # A transducer is infinitely ambiguous with a given input if the input yields infinitely many results, i.e. there are
    # input epsilon loops that are traversed with the input.
    def is_lookup_infinitely_ambiguous(self, str):
        pass

    ## Lookup tokenized input \a input in the transducer minding flag diacritics.
    # @param str A list/tuple of strings to look up.
    # @param kvargs infinite_cutoff=-1, max_weight=None
    # @param infinite_cutoff Defaults to -1, i.e. infinite.
    # @param max_weight Defaults to None, i.e. infinity. 
    def lookup_fd(self, input, **kvargs):
        pass

    ## Add a new state to this transducer and return its number.      
    #  @return The next (smallest) free state number.
    def add_state(self):
        pass

    ## Add a state \a s to this graph.
    # @param state The number of the state to be added.
    # @return \a state
    #
    # If the state already exists, it is not added again.
    # All states with state number smaller than \a s are also
    # added to the transducer if they did not exist before.
    def add_state(self, state):
        pass

    ## The states of the transducer 
    # @return A tuple of state numbers.
    #
    # An example:
    # /verbatim
    # for state in fsm.states():
    # for arc in fsm.transitions(state):
    #     print('%i ' % (state), end='')
    #     print(arc)
    # if fsm.is_final_state(state):
    #    print('%i %f' % (state, fsm.get_final_weight(state)) )
    # /endverbatim
    def states(self):
        pass        

    ## The states and transitions of the transducer.
    # @return A tuple of tuples of HfstBasicTransitions.
    # @see libhfst.HfstBasicTransducer.__enumerate__
    def states_and_transitions(self):
        pass

    ## Explicitly add \a symbol to the alphabet of the graph.
    # @note Usually the user does not have to take care of the alphabet
    #       of a graph. This function can be useful in some special cases.
    # @ param symbol The string to be added.
    def add_symbol_to_alphabet(self, symbol):
        pass

    ## Explicitly add \a symbols to the alphabet of the graph.
    # @note Usually the user does not have to take care of the alphabet of a graph. This function can be useful in some special cases.
    # @param symbols A tuple of strings to be added.
    def add_symbols_to_alphabet(self, symbols):
        pass

    ## Add a transition \a transition to state \a state, \a add_symbols_to_alphabet defines whether the transition symbols are added to the alphabet.
    # @param state The number of the state where the transition is added. If it does not exist, it is created.
    # @param transition A libhfst.HfstBasicTransition that is added to \a state.
    # @param add_symbols_to_alphabet Whether the transition symbols are added to the alphabet of the transducer. (In special cases this is not wanted.)
    def add_transition(self, state, transition, add_symbols_to_alphabet=True):
        pass

    ## Add a transition from state \a source to state \a target with input symbol \a input, output symbol \a output and weight \a weight.
    # @param source The number of the state where the transition is added. If it does not exist, it is created.
    # @param target The number of the state where the transition leads. If it does not exist, it is created. (?)
    # @param input The input symbol of the transition.
    # @param output The output symbol of the transition.
    # @param weight The weight of the transition.
    def add_transition(self, source, target, input, output, weight=0):
        pass

    ## Remove transition \a transition from state \a s.
    # @param s The state which \a transition belongs to.
    # @param transition The transition to be removed.
    # @param remove_symbols_from_alphabet (?) 
    def remove_transition(self, s, transition, remove_symbols_from_alphabet=False):
        pass
    
    ## Disjunct this transducer with a one-path transducer defined by consecutive string pairs in \a spv that has weight \a weight.
    #
    # @pre This graph must be a trie where all weights are in final states,
    #      i.e. all transitions have a zero weight.
    #
    # There is no way to test whether a graph is a trie, so the use
    # of this function is probably limited to fast construction of a lexicon.
    # Here is an example: 
    # 
    # \verbatim
    # lexicon = libhfst.HfstBasicTransducer()
    # tok = libhfst.HfstTokenizer()
    # lexicon.disjunct(tok.tokenize('dog'), 0.3)
    # lexicon.disjunct(tok.tokenize('cat'), 0.5)
    # lexicon.disjunct(tok.tokenize('elephant'), 1.6)
    # \endverbatim
    def disjunct(self, stringpairpath, weight):
        pass

    ## The symbols in the alphabet of the transducer.     
    # The symbols do not necessarily occur in any transitions of the transducer. 
    # Epsilon, unknown and identity symbols are always included in the alphabet.
    # @return A tuple of strings.
    def get_alphabet(self):
        pass

    ## Get the final weight of state \a state in this transducer.
    # @param state The number of the state. If it does not exist, a StateIsNotFinalException is thrown.
    # @throws libhfst.StateIsNotFinalException.
    def get_final_weight(self, state):
        pass

    ## Get the biggest state number in use. 
    # @return The biggest state number in use.
    def get_max_state(self):
        pass

    ## Harmonize this transducer and \a another.
    #
    # In harmonization the unknown and identity symbols in transitions of both graphs
    # are expanded according to the symbols that are previously unknown to the graph.
    #
    # For example the graphs
    # \verbatim
    # [a:b ?:?]
    # [c:d ? ?:c]
    # \endverbatim
    # are expanded to
    # \verbatim
    # [ a:b [?:? | ?:c | ?:d | c:d | d:c | c:? | d:?] ]
    # [ c:d [? | a | b] [?:c| a:c | b:?] ]
    # \endverbatim
    # when harmonized.
    #
    # The symbol '?' means libhfst.UNKNOWN in either or both sides of a transition
    # (transitions of type [?:x], [x:?] and [?:?]). The transition [?] means libhfst.IDENTITY.
    #
    # @note This function is always called for all transducer arguments of functions
    #       that take two or more graphs as their arguments, unless otherwise said.
    def harmonize(self, another):
        pass

    ## Create a transducer with one initial state that has state number zero and is not a final state, i.e. create an empty transducer.
    def __init__(self):
        pass

    ## Create a transducer equivalent to \a transducer.
    # @param transducer The transducer to be copied, #libhfst.HfstBasicTransducer or #libhfst.HfstTransducer.
    def __init__(self, transducer):
        pass

    ## Read a transducer from prolog file \a f. \a linecount is incremented as lines are read (is it in python?).
    # @return A transducer constructed by reading from file \a file.
    # This function is a static one.
    def read_prolog(f, linecount):
        pass

    ## Write the transducer in prolog format to file \a f. Name the transducer \a name.
    def write_prolog(self, f, name, write_weights=True):
        pass

    ## Write the transducer in xfst format to file \a f.
    def write_xfst(self, f, write_weights=True):
        pass

    ## Read a transducer in AT&T format from file \a f. \a epsilon_symbol defines the symbol used for epsilon, \a linecount is incremented as lines are read.
    # @return A transducer constructed by reading from file \a file.
    # This function is a static one.
    def read_att(f, epsilon_symbol, linecount):
        pass

    ## Write this transducer in AT&T format to file \a f, \a write_weights defines whether weights are written.
    def write_att(f, bool write_weights=True):
        pass

    ## Insert freely any number of \a symbol_pair in the transducer with weight \a weight.
    # @param symbol_pair A string pair to be inserted.
    # @param weight The weight of the inserted symbol pair.
    def insert_freely(self, symbol_pair, weight):
        pass

    ## Insert freely any number of \a transducer in this transducer.
    # param transducer An HfstBasicTransducer to be inserted.
    def insert_freely(self, transducer):
        pass

    ## Whether state \a state is final. 
    # @param state The state whose finality is returned.
    def is_final_state(self, state):
        pass
    
    ## Get the transitions of state \a state in this transducer. 
    # If the state does not exist, a @a StateIndexOutOfBoundsException is thrown.
    # @return A tuple of HfstBasicTransitions.
    #
    # \verbatim
    # for state in fsm.states():
    # for arc in fsm.transitions(state):
    #     print('%i ' % (state), end='')
    #     print(arc)
    # if fsm.is_final_state(state):
    #    print('%i %f' % (state, fsm.get_final_weight(state)) )
    # \endverbatim
    def transitions(self, state):
        pass
    
    ## Remove all symbols that do not occur in transitions of the transducer from its alphabet. 
    #  Epsilon, unknown and identity symbols are always included in the alphabet.
    def prune_alphabet(self):
        pass
    
    ## Get a list of all symbols used in the transitions of this transducer. 
    def symbols_used(self):
        pass

    ## Get a list of all input/output symbol pairs used in the transitions of this transducer. 
    def get_transition_pairs(self):
        pass

    ## Remove symbol \a symbol from the alphabet of the graph. 
    #  @note Use with care, removing symbols that occur in the transitions of the graph can have unexpected results.
    # @param symbol The string to be removed.
    def remove_symbol_from_alphabet(self, symbol):
        pass
    
    ## Remove symbols \a symbols from the alphabet of the graph. 
    #  @note Use with care, removing symbols that occur in the transitions of the graph can have unexpected results.
    # @param symbols A tuple of strings to be removed.
    def remove_symbols_from_alphabet(self, symbols):
        pass

    ## Set the final weight of state \a state in this transducer to \a weight. 
    # If the state does not exist, it is created.
    def set_final_weight(self, state, weight):
        pass
    
    ## Sort the arcs of this transducer according to input and output symbols.
    # @return This transducer.
    def sort_arcs(self):
        pass

    ## Substitute symbols or transitions in the transducer.
    #
    # @param s The symbol or transition to be substituted. Can also be a dictionary of substitutions, if S == None.
    # @param S The symbol, transition, a tuple of transitions or a transducer (libhfst.HfstBasicTransducer) that substitutes \a s.
    # @param kvargs Arguments recognized are 'input' and 'output', their values can be False or True, True being the default.   
    #               These arguments are valid only if \a s and \a S are strings, else they are ignored.
    # @param input Whether substitution is performed on input side, defaults to True. Valid only if \a s and \a S are strings.
    # @param output Whether substitution is performed on output side, defaults to True. Valid only if \a s and \a S are strings.
    #
    # Possible combinations of arguments and their types are:
    #
    # (1) substitute(str, str, input=bool, output=bool): substitute symbol with symbol on input, output or both sides of each transition in the transducer.
    # (2) substitute(strpair, strpair): substitute transition with transition
    # (3) substitute(strpair, strpairtuple): substitute transition with several transitions
    # (4) substitute(strpair, transducer): substitute transition with a transducer
    # (5) substitute(dict): perform several symbol-to-symbol substitutions
    # (6) substitute(dict): perform several transition-to-transition substitutions
    #
    # Examples: 
    #
    # (1) tr.substitute('a', 'A', input=True, output=False): substitute lowercase a:s with uppercase ones
    # (2) tr.substitute(('a','b'),('A','B')): substitute transitions that map lowercase a into lowercase b with transitions that map uppercase a into uppercase b 
    # (3) tr.substitute(('a','b'), (('A','B'),('a','B'),('A','b'))): change either or both sides of a transition [a:b] to uppercase
    # (4) tr.substitute(('a','b'), libhfst.regex('[a:b]+')) change [a:b] transition into one or more consecutive [a:b] transitions
    # (5) tr.substitute({'a':'A', 'b':'B', 'c':'C'}) change lowercase a, b and c into their uppercase variants
    # (6) tr.substitute( {('a','a'):('A','A'), ('b','b'):('B','B'), ('c','c'):('C','C')} ): change lowercase a, b and c into their uppercase variants
    #
    # In case (4), epsilon transitions are used to attach copies of transducer \a S between the SOURCE and TARGET state of each transition that is substituted.
    # The transition itself is deleted, but its weight is copied to the epsilon transition leading from SOURCE to the initial state of \a S.
    # Each final state of \a S is made non-final and an epsilon transition leading to TARGET is attached to it. The final weight is copied to the epsilon transition.
    # 
    def substitute(self, s, S=None, **kvargs):
        pass

    ## Return an enumeration of the states and transitions of the transducer. 
    #
    # \verbatim
    # for state, arcs in enumerate(fsm):
    #   for arc in arcs:
    #     print('%i ' % (state), end='')
    #     print(arc)
    #   if fsm.is_final_state(state):
    #     print('%i %f' % (state, fsm.get_final_weight(state)) )
    # \endverbatim
    def __enumerate__(self):
        pass

    ## Return a string representation of the transducer.
    #
    # \verbatim
    # print(fsm)
    # \endverbatim
    def __str__(self):
        pass

## A transition class that consists of a target state, input and output symbols and a a tropical weight.
# @see libhfst.HfstBasicTransducer
class HfstBasicTransition:

    ## Create an HfstBasicTransition leading to target state \a state with input symbol \a input, output symbol \a output and weight \a weight.
    # @param state Number of the target state.
    # @param input The input string.
    # @param output The output string.
    # @param weight The weight.
    # @throws EmptyStringException
    def __init__(self, state, input, output, weight):
        pass

    ## Get the input symbol of the transition.
    def get_input_symbol(self):
        pass

    ## Get the output symbol of the transition.
    def get_output_symbol(self):
        pass

    ## Get number of the target state of the transition.
    def get_target_state(self):
        pass
        
    ## Get the weight of the transition.
    def get_weight(self):
        pass

    ## A string representation of the transition.
    #
    # @return "target_state input_symbol output_symbol, weight"
    def __str__(self)

## A synchronous finite-state transducer.
# 
# \section argument_handling Argument handling
# 
# Transducer functions modify their calling object and return 
# a reference to the calling object after modification, 
# unless otherwise mentioned.
# Transducer arguments are usually not modified.
# \verbatim
# # transducer is reversed
# transducer.reverse()
# # transducer2 is not modified, but a copy of it is disjuncted with
# # transducer1 
# transducer1.disjunct(transducer2)                                       
# # a chain of functions is possible
# transducer.reverse().determinize().reverse().determinize()      
# \endverbatim
# 
# \section implementation_types Implementation types
# 
# Currently, an HfstTransducer has three implementation types that are well supported.
# When an HfstTransducer is created, its type is defined with an argument.
# For functions that take a transducer as an argument, the type of the calling transducer
# must be the same as the type of the argument transducer:
# \verbatim
# # this will cause a TransducerTypeMismatchException:
# tropical_transducer.disjunct(foma_transducer)
# # this works, but weights are lost in the conversion
# tropical_transducer.convert(libhfst.SFST_TYPE).disjunct(sfst_transducer)     
# # this works, information is not lost
# tropical_transducer.disjunct(sfst_transducer.convert(libhfst.TROPICAL_OPENFST_TYPE)) 
# \endverbatim
# 
# \section creating_transducers Creating transducers
# 
# With HfstTransducer constructors it is possible to create empty, 
# epsilon, one-transition and single-path transducers.
# Transducers can also be created from scratch with #libhfst.HfstBasicTransducer
# and converted to an HfstTransducer.
# More complex transducers can be combined from simple ones with various functions.
class HfstTransducer:

    ## Whether HFST is linked to the transducer library needed by implementation type \a type.
    def is_implementation_type_available(type):
        pass

    ## Create an uninitialized transducer (use with care). 
    # 
    # @note This constructor leaves the backend implementation variable
    # uninitialized. An uninitialized transducer is likely to cause a
    # TransducerHasWrongTypeException at some point unless it is given
    # a value at some point. 
    def __init__(self):
        pass

    ## Create a deep copy of HfstTransducer \a another or a transducer equivalent to HfstBasicTransducer \a another.
    # @param another An HfstTransducer or HfstBasicTransducer.
    #
    # An example:
    #
    # \verbatim
    # tr1 = libhfst.regex('foo bar foo')
    # tr2 = libhfst.HfstTransducer(tr1)
    # tr2.substitute('foo','FOO')
    # tr1.concatenate(tr2)
    # \endverbatim
    def __init__(self, another):
        pass

    ## Create an HFST transducer equivalent to HfstBasicTransducer \a t. The type of the created transducer is defined by \a type.
    # @param t An HfstBasicTransducer.
    # @param type The type of the resulting transducer.
    # If you want to use the default type, you can just call
    # libhfst.HfstTransducer(fsm)
    def __init__(self, t, type):
        pass

    ## Rename the transducer \a name.
    # @param name The name of the transducer.
    # @see #get_name 
    def set_name(self, name):
        pass
 
    ## Get the name of the transducer. 
    # @see #set_name 
    def get_name(self):
        pass

    ## An AT&T representation of the transducer.
    # Defined for print command. An example:
    # \verbatim
    # >>> print(libhfst.regex('[foo:bar::2]+'))
    # 0       1       foo     bar     2.000000
    # 1       1       foo     bar     2.000000
    # 1       0.000000
    # \endverbatim
    # @todo Works only for small transducers.
    def __str__(self):
        pass

    ## Make transducer coaccessible.
    # A transducer is coaccessible iff there is a path from every state to a final state.
    def prune(self):
        pass

    ## Set arbitrary string property \a property to \a value.
    # @param property A string naming the property.
    # @param value A string expressing the value of \a property.
    #
    # set_property('name', 'name of the transducer') equals set_name('name of the transducer').
    #
    # @note  While this function is capable of creating endless amounts of arbitrary metadata, it is suggested that property names are
    # drawn from central repository, or prefixed with "x-". A property that does not follow this convention may affect the behavior of
    # transducer in future releases.
    def set_property(self, property, value):
        pass

    ## Get arbitrary string propert @a property.
    # @param property The name of the property whose value is returned.
    # get_property('name') works like get_name().
    def get_property(self, property):
        pass

    ## Get all properties from the transducer.
    # @return A dictionary whose keys are properties and whose values are the values of those properties.
    def get_properties(self):
        pass

    ## Get the alphabet of the transducer. 
    # 
    # The alphabet is defined as the set of symbols known to the transducer. 
    # @return A tuple of strings.
    def get_alphabet(self):
        pass

    ## Explicitly insert \a symbol to the alphabet of the transducer. 
    # @param symbol The symbol (string) to be inserted.
    #
    # @note Usually this function is not needed since new symbols are
    # added to the alphabet by default. 
    def insert_to_alphabet(self, symbol):
        pass
 
    ## Remove \a symbol from the alphabet of the transducer.
    # @param symbol The symbol (string) to be removed.
    # 
    # @pre \a symbol does not occur in any transition of the transducer.
    # @note Use with care, removing a symbol that occurs in a transition
    # of the transducer can have unexpected results. 
    def remove_from_alphabet(self, symbol):
        pass

    ## Eliminate flag diacritic \a symbol from the transducer.
    # @param symbol The flag to be eliminated. TODO: explain more.
    #
    # An equivalent transducer with no flags \a symbol.
    def eliminate_flag(self, symbol):
        pass

    ## Eliminate flag diacritics listed in \a symbols from the transducer.
    # @param symbols The flags to be eliminated. TODO: explain more.
    #
    # An equivalent transducer with no flags listed in \a symbols.
    def eliminate_flags(self, symbols):
        pass

    ## Whether each transition in the transducer has equivalent input and output symbols.
    # @note Transition with libhfst.UNKNOWN on both sides IS NOT a transition with equivalent input and output symbols.
    # @note Transition with libhfst.IDENTITY on both sides IS a transition with equivalent input and output symbols.
    def is_automaton(self):
        pass

    ## Whether the transducer is cyclic.
    def is_cyclic(self):
        pass

    ## The implementation type of the transducer.
    # @return libhfst.ImplementationType
    def get_type(self):
        pass
 
    ## Whether this transducer and \a another are equivalent.
    # @param another The compared transducer.
    # @pre \a self and \a another must have the same implementation type.
    # 
    # Two transducers are equivalent iff they accept the same input/output
    # string pairs with the same weights and the same alignments. 
    # @note For weighted transducers, the function often returns false negatives
    #       due to weight precision issues. 
    def compare(self, another):
        pass

    ## Remove all <i>epsilon:epsilon</i> transitions from the transducer so that the resulting transducer is equivalent to the original one. 
    def remove_epsilons(self):
        pass

    ## Determinize the transducer.
    # 
    # Determinizing a transducer yields an equivalent transducer that has
    # no state with two or more transitions whose input:output symbol
    # pairs are the same. 
    def determinize(self):
        pass
    
    ## The number of states in the transducer.
    def number_of_states(self):
        pass

    ## The number of transitions in the transducer.
    def number_of_arcs(self):
        pass

    ## Write the transducer in binary format to \a ostr.
    # @param ostr A libhfst.HfstOutputStream where the transducer is written.
    def write(self, ostr):
        pass

    ## Write the transducer in AT&T format to file \a f, \a write_weights defined whether weights are written.
    # @param f An libhfst.HfstFile where the transducer is written.
    # @param write_weights Whether weights are written.
    def write_att(self, f, write_weights=True):
        pass

    ## Write the transducer in prolog format with name \a name to file \a f, \a write_weights defined whether weights are written.
    # @param f An libhfst.HfstFile where the transducer is written.
    # @param name The name of the transducer that must be given in a prolog file.
    # @param write_weights Whether weights are written.
    def write_prolog(f, name, write_weights=True):
        pass

    ## Minimize the transducer.
    # 
    # Minimizing a transducer yields an equivalent transducer with 
    # the smallest number of states. 
    # 
    # @bug OpenFst's minimization algorithm seems to add epsilon transitions to weighted transducers? 
    def minimize(self):
        pass
    
    ## Extract \a n best paths of the transducer. 
    # 
    # In the case of a weighted transducer (#TROPICAL_OPENFST_TYPE or 
    # #LOG_OPENFST_TYPE), best paths are defined as paths with 
    # the lowest weight.
    # In the case of an unweighted transducer (#SFST_TYPE or #FOMA_TYPE), 
    # the function returns random paths.
    # 
    # This function is not implemented for #FOMA_TYPE or #SFST_TYPE.
    # If this function is called by an HfstTransducer of type #FOMA_TYPE 
    # or #SFST_TYPE, it is converted to #TROPICAL_OPENFST_TYPE,
    # paths are extracted and it is converted back to #FOMA_TYPE or 
    # #SFST_TYPE. If HFST is not linked to OpenFst library, an
    # ImplementationTypeNotAvailableException is thrown.
    def n_best(self, n):
        pass
    
    ## A concatenation of N transducers where N is any number from zero to infinity. 
    def repeat_star(self):
        pass
    
    ## A concatenation of N transducers where N is any number from one to infinity. 
    def repeat_plus(self):
        pass
    
    ## A concatenation of \a n transducers. 
    def repeat_n(self, n):
        pass
    
    ## A concatenation of N transducers where N is any number from zero to \a n, inclusive.
    def repeat_n_minus(self, n):
        pass
    
    ## A concatenation of N transducers where N is any number from \a n to infinity, inclusive.
    def repeat_n_plus(self, n):
        pass
    
    ## A concatenation of N transducers where N is any number from \a n to \a k, inclusive.
    def repeat_n_to_k(self, n, k):
        pass
    
    ## Disjunct the transducer with an epsilon transducer. 
    def optionalize(self):
        pass
    
    ## Swap the input and output symbols of each transition in the transducer. 
    def invert(self):
        pass
    
    ## Reverse the transducer. 
    # 
    # A reverted transducer accepts the string 'n(0) n(1) ... n(N)' 
    # iff the original
    # transducer accepts the string 'n(N) n(N-1) ... n(0)' 
    def reverse(self):
        pass
    
    ## Extract the input language of the transducer. 
    # 
    # All transition symbol pairs <i>isymbol:osymbol</i> are changed 
    # to <i>isymbol:isymbol</i>. 
    def input_project(self):
        pass
    
    ## Extract the output language of the transducer.
    # 
    # All transition symbol pairs <i>isymbol:osymbol</i> are changed 
    # to <i>osymbol:osymbol</i>. 
    def output_project(self):
        pass
    
    ## Compose this transducer with \a another.
    # @param another The second argument in the composition. Not modified.
    def compose(self, another):
        pass

    ## Perform a lenient composition on this transducer and \a another.
    # TODO: explain more.
    def lenient_composition(self, another):
        pass
    
    ## Compose this transducer with the intersection of
    # transducers in \a v. If \a invert is true, then compose the
    # intersection of the transducers in \a v with this transducer.
    # 
    # The algorithm used by this function is faster than intersecting 
    # all transducers one by one and then composing this transducer 
    # with the intersection. 
    # 
    # @pre The transducers in \a v are deterministic and epsilon-free.
    # @param v A tuple of transducers.
    # @param invert Whether the intersection of the transducers in \a v is composed with this transducer.
    def compose_intersect(self, v, invert=False):
        pass
    
    ## Concatenate this transducer with \a another. 
    def concatenate(self, another):
        pass
    
    ## Disjunct this transducer with \a another. 
    def disjunct(self, another):
        pass

    ## Intersect this transducer with \a another. 
    def intersect(self, another):
        pass
    
    ## Subtract transducer \a another from this transducer. 
    def subtract(self, another):
        pass

    ## Alias for subtract.
    # @see libhfst.HfstTransducer.subtract
    def minus(self, another):
        pass

    ## Alias for intersect.
    # @see libhfst.HfstTransducer.intersect
    def conjunct(self, another):
        pass

    ## Convert the transducer into an equivalent transducer in format \a type. 
    # 
    # If a weighted transducer is converted into an unweighted one, 
    # all weights are lost. In the reverse case, all weights are initialized to the 
    # semiring's one. 
    # 
    # A transducer of type #libhfst.SFST_TYPE, #libhfst.TROPICAL_OPENFST_TYPE,
    # #libhfst.LOG_OPENFST_TYPE or #libhfst.FOMA_TYPE can be converted into an 
    # #libhfst.HFST_OL_TYPE or #libhfst.HFST_OLW_TYPE transducer, but an #libhfst.HFST_OL_TYPE
    # or #libhfst.HFST_OLW_TYPE transducer cannot be converted to any other type.
    # 
    # @note For conversion between HfstBasicTransducer and HfstTransducer,
    # see #libhfst.HfstTransducer.__init__ and #libhfst.HfstBasicTransducer.__init__
    def convert(self, type, options=''):
        pass
    
    ## Write the transducer in AT&T format to file \a ofile, \a write_weights defines whether weights are written. 
    # 
    # The fields in the resulting AT&T format are separated by tabulator characters.
    # 
    # NOTE: If the transition symbols contain space characters,the spaces are printed as '\@_SPACE_\@' because
    # whitespace characters are used as field separators in AT&T format. Epsilon symbols are printed as '\@0\@'.
    # 
    # If several transducers are written in the same file, they must be separated by a line of two consecutive hyphens "--", so that
    # they will be read correctly by libhfst.read_att.
    # 
    # An example:
    # \verbatim
    # tr1 = libhfst.regex('[foo:bar baz:0 " "]::0.3')
    # tr2 = libhfst.empty_fst()
    # tr3 = libhfst.epsilon_fst(0.5)
    # tr4 = libhfst.regex('[foo]')
    # tr5 = libhfst.empty_fst()
    # 
    # f = libhfst.hfst_open('testfile.att', 'w')
    # for tr in [tr1, tr2, tr3, tr4]:
    #     tr.write_att(f)
    #     f.write('--\n')
    # tr5.write_att(f)
    # f.close()
    # \endverbatim
    # 
    # This will yield a file 'testfile.att' that looks as follows:
    # \verbatim
    # 0       1       foo     bar     0.299805
    # 1       2       baz     @0@     0.000000
    # 2       3       @_SPACE_@       @_SPACE_@       0.000000
    # 3       0.000000
    # --
    # --
    # 0       0.500000
    # --
    # 0       1       foo     foo     0.000000
    # 1       0.000000
    # --
    # \endverbatim
    # 
    # @throws StreamCannotBeWrittenException 
    # @throws StreamIsClosedException
    # 
    # @see #libhfst.HfstOutputStream.write
    # @see #libhfst.HfstTransducer.__init__
    def write_att(self, ofile, write_weights=True):
        pass

    ## Write the transducer in AT&T format to file named \a filename. \a write_weights defines whether weights are written.
    # 
    # If the file exists, it is overwritten. If the file does not exist, it is created. 
    def write_att(self, filename, write_weights=True):
        pass

    ## Make priority union of this transducer with \a another.
    #
    # For the operation t1.priority_union(t2), the result is a union of t1 and t2,
    # except that whenever t1 and t2 have the same string on left side,
    # the path in t2 overrides the path in t1.
    # 
    # Example
    # \verbatim
    # Transducer 1 (t1):
    # a : a
    # b : b
    # 
    # Transducer 2 (t2):
    # b : B
    # c : C
    # 
    # Result ( t1.priority_union(t2) ):
    # a : a
    # b : B
    # c : C
    # \endverbatim
    # For more information, read <a href="http://www.fsmbook.com/">fsmbook</a>.
    #  
    def priority_union(self, another):
        pass
    
    ## Make cross product of this transducer with \a another. It pairs every string of this with every string of \a another.
    # If strings are not the same length, epsilon padding will be added in the end of the shorter string.
    # @pre Both transducers must be automata, i.e. map strings onto themselves.
    def cross_product(self, another):
        pass
    
    ## Shuffle this transducer with transducer \a another.
    # 
    # If transducer A accepts string 'foo' and transducer B string 'bar',
    # the transducer that results from shuffling A and B accepts all strings
    # [(f|b)(o|a)(o|r)].
    #   
    # @pre Both transducers must be automata, i.e. map strings onto themselves.
    def shuffle(self, another):
        pass

    ## Freely insert a transition or a transducer into the transducer.
    # @param ins The transition or transducer to be inserted.
    # 
    # If \a ins is a transition, i.e. a 2-tuple of strings: A transition is added to each state in this transducer.
    # The transition leads from that state to itself with input and output symbols defined by \a ins.
    # The weight of the transition is zero.
    #
    # If \a ins is an #libhfst.HfstTransducer:
    # A copy of \a ins is attached with epsilon transitions 
    # to each state of this transducer. After the operation, for each 
    # state S in this transducer, there is an epsilon transition 
    # that leads from state S to the initial state of \a ins, 
    # and for each final state of \a ins, there is an epsilon transition
    # that leads from that final state to state S in this transducer.
    # The weights of the final states in \a ins are copied to the 
    # epsilon transitions leading to state S.
    def insert_freely(self, ins):
        pass
    
    ## Set the weights of all final states to \a weight. 
    # If the HfstTransducer is of unweighted type (#libhfst.SFST_TYPE or #libhfst.FOMA_TYPE), nothing is done.
    def set_final_weights(self, weight):
        pass
    
    ## Push weights towards initial or final state(s) as defined by \a type.
    # @param PushType defining if weights are pushed towards initial state or final states, possible values are libhfst.TO_INITIAL_STATE and libhst.TO_FINALSTATE
    # 
    # If the HfstTransducer is of unweighted type (#SFST_TYPE or #FOMA_TYPE), nothing is done.
    #
    # An example:
    # \verbatim
    # >>> import libhfst
    # >>> tr = libhfst.regex('[a::1 a:b::0.3 (b::0)]::0.7;')
    # >>> tr.push_weights(libhfst.TO_INITIAL_STATE)
    # >>> print(tr)
    # 0       1       a       a       2.000000
    # 1       2       a       b       0.000000
    # 2       3       b       b       0.000000
    # 2       0.000000
    # 3       0.000000
    # 
    # >>> tr.push_weights(libhfst.TO_FINAL_STATE)
    # >>> print(tr)
    # 0       1       a       a       0.000000
    # 1       2       a       b       0.000000
    # 2       3       b       b       0.000000
    # 2       2.000000
    # 3       2.000000
    # 
    # \endverbatim
    #
    # @see #libhfst.TO_INITIAL_STATE #libhfst.TO_FINAL_STATE
    # 
    def push_weights(self, type):
        pass

    ## Substitute symbols or transitions in the transducer.
    #
    # @param s The symbol or transition to be substituted. Can also be a dictionary of substitutions, if S == None.
    # @param S The symbol, transition, a tuple of transitions or a transducer (libhfst.HfstTransducer) that substitutes \a s.
    # @param kvargs Arguments recognized are 'input' and 'output', their values can be False or True, True being the default.   
    #               These arguments are valid only if \a s and \a S are strings, else they are ignored.
    # @param input Whether substitution is performed on input side, defaults to True. Valid only if \a s and \a S are strings.
    # @param output Whether substitution is performed on output side, defaults to True. Valid only if \a s and \ S are strings.
    #
    # For more information, see libhfst.HfstBasicTransducer.substitute. The function works similarly, with the exception
    # of argument \a S, which must be libhfst.HfstTransducer instead of libhfst.HfstBasicTransducer.
    #
    # @see libhfst.HfstBasicTransducer.substitute
    def substitute(self, s, S=None, **kvargs):
        pass

    ## Lookup string \a input.
    # @param input The input.
    # @param kvargs Possible parameters and their default values are: obey_flags=True, max_number=-1, time_cutoff=0.0, output='tuple'
    # @param obey_flags Whether flag diacritics are obeyed. Currently always True.
    # @param max_number Maximum number of results returned, defaults to -1, i.e. infinity.
    # @param time_cutoff How long the function can search for results before returning, expressed in seconds. Defaults to 0.0, i.e. infinitely.
    # @param output Possible values are 'tuple', 'text' and 'raw', 'tuple' being the default.
    #
    # @note This function is implemented only for optimized lookup format (libhfst.HFST_OL_TYPE or libhfst.HFST_OLW_TYPE). 
    #       Either convert to optimized lookup format or to HfstBasicTransducer if you wish to perform lookup.
    #       Conversion to OL might take a while but it lookup is fast.
    #       Conversion to HfstBasicTransducer is quick but lookup is slower.
    #
    def lookup(self, input, **kvargs):
        pass

    ## Extract paths that are recognized by the transducer. 
    #
    # @param kvargs Arguments recognized are filter_flags, max_cycles, max_number, obey_flags, output, random.
    # @param filter_flags Whether flags diacritics are filtered out from the result (default True).
    # @param max_cycles Indicates how many times a cycle will be followed, with negative numbers indicating unlimited (default -1 i.e. unlimited).
    # @param max_number The total number of resulting strings is capped at this value, with 0 or negative indicating unlimited (default -1 i.e. unlimited).
    # @param obey_flags Whether flag diacritics are validated (default True).
    # @param output Output format. Values recognized: 'text' (as a string, separated by newlines), 'raw' (a dictionary that maps each input string into a list of tuples of an output string and a weight), 'dict' (a dictionary that maps each input string into a tuple of tuples of an output string and a weight, the default). 
    # @param random Whether result strings are fetched randomly (default False).
    # @return The extracted strings. \a output controls how they are represented.
    #
    # @pre The transducer must be acyclic, if both \a max_number and \a max_cycles have unlimited values. Else a libhfst.TransducerIsCyclicException will be thrown.
    #
    # An example:
    # 
    # \verbatim
    # >>> tr = libhfst.regex('a:b+ (a:c+)')
    # >>> print(tr)
    # 0       1       a       b       0.000000
    # 1       1       a       b       0.000000
    # 1       2       a       c       0.000000
    # 1       0.000000
    # 2       2       a       c       0.000000
    # 2       0.000000
    #
    # >>> print(tr.extract_paths(max_cycles=1, output='text'))
    # a:b     0
    # aa:bb   0
    # aaa:bbc 0
    # aaaa:bbcc       0
    # aa:bc   0
    # aaa:bcc 0
    #
    # >>> print(tr.extract_paths(max_number=4, output='text'))
    # a:b     0
    # aa:bc   0
    # aaa:bcc 0
    # aaaa:bccc       0
    # 
    # >>> print(tr.extract_paths(max_cycles=1, max_number=4, output='text'))
    # a:b     0
    # aa:bb   0
    # aa:bc   0
    # aaa:bcc 0
    #
    # \endverbatim
    #
    # @throws TransducerIsCyclicException
    # @see #libhfst.HfstTransducer.n_best
    # @note <a href="Symbols.html">Special symbols</a> are printed as such.
    # @todo a link to flag diacritics
    def extract_paths(self, **kvargs):
        pass

    ## Extract shortest paths of the transducer.
    # @return A dictionary.
    def extract_shortest_paths():
        pass

    ## Extract longest paths of the transducer.
    # @return A dictionary.
    def extract_longest_paths(**kvargs):
        pass

    ## Get length of longest path of the transducer.
    def longest_path_size(**kvargs):
        pass

    # Lookup or apply a single tokenized string \a tok_input and return a maximum of \a limit results.
    # 
    # TODO: This is a version of lookup that handles flag diacritics as ordinary
    # symbols and does not validate the sequences prior to outputting. Currently, this function calls lookup_fd.
    #
    # @todo Handle flag diacritics as ordinary symbols instead of calling lookup_fd.
    # @sa lookup_fd
    # @return HfstOneLevelPaths pointer
    # @param tok_input A tuple of consecutive symbols (strings).
    # @param limit Number of strings to look up. -1 tries to look up all and may get stuck if infinitely ambiguous.
    # def lookup(tok_input, limit=-1):
    #    pass
    
    ## Lookup or apply a single string \a input and return a maximum of \a limit results.
    # 
    # This is an overloaded lookup function that leaves tokenizing to the transducer.
    # @return HfstOneLevelPaths pointer
    #def lookup(input, limit=-1):
    #    pass
    
    # Lookup or apply a single string \a input and return a maximum of \a limit results. \a tok defined how \a s is tokenized.
    #
    # This is an overloaded lookup function that leaves tokenizing to \a tok.
    # @return HfstOneLevelPaths pointer
    # def lookup(tok, input, limit=-1):
    #    pass
    
    
    # Lookup or apply a single string \a tok_input minding flag diacritics properly and return a maximum of \a limit results.
    #
    # Traverse all paths on logical first level of the transducer to produce
    # all possible outputs on the second.
    # This is in effect a fast composition of single path from left
    # hand side.
    #
    # This is a version of lookup that handles flag diacritics as epsilons
    # and validates the sequences prior to outputting.
    # Epsilons on the second level are represented by empty strings
    # in the results.
    #
    # @pre The transducer must be of type #libhfst.HFST_OL_TYPE or #libhfst.HFST_OLW_TYPE. This function is not implemented for other transducer types.
    #
    # @param tok_input  A tuple of consecutive symbols (strings) to look up.
    # @param limit  (Currently ignored.) Number of strings to look up. -1 tries to look up all and may get stuck if infinitely ambiguous.
    # 
    # @see #is_lookup_infinitely_ambiguous
    # @return HfstOneLevelPaths pointer
    #
    # @todo Do not ignore argument \a limit.
    # def lookup_fd(tok_input, limit = -1):
    #    pass
    
    # Lookup or apply a single string \a s minding flag diacritics properly and return a maximum of \a limit results.
    #
    # This is an overloaded lookup function that leaves tokenizing to the transducer.
    # @return HfstOneLevelPaths pointer
    # def lookup_fd(input, limit = -1):
    #    pass
    
    
    # Lookup or apply a single string \a input minding flag diacritics properly and return a maximum of \a limit results. \a tok defines how s is tokenized.
    #
    # This is an overloaded lookup function that leaves tokenizing to \a tok.
    # @return HfstOneLevelPaths pointer
    # def lookup_fd(tok, input, limit = -1):
    #    pass

    # Whether lookup of path \a input will have infinite results.
    #
    # Currently, this function will return whether the transducer
    # is infinitely ambiguous on any lookup path found in the transducer,
    # i.e. the argument \a input is ignored.
    #
    # @todo Do not ignore the argument \a input
    def is_lookup_infinitely_ambiguous(self, tok_input):
        pass

    ## Whether the transducer is infinitely ambiguous.
    #
    # A transducer is infinitely ambiguous if there exists an input that will yield infinitely many results,
    # i.e. there are input epsilon loops that are traversed with that input.
    def is_infinitely_ambiguous(self):
        pass

    ## Whether the transducer has flag diacritics in its transitions.
    def has_flag_diacritics(self):
        pass

# Detokenize \a tokenized_paths.
#
# Concatenate all transition symbols on input and output levels for each path in \a tokenized_paths.
# 
# @param tokenized_paths An HfstOneLevelPaths pointer or an HfstTwoLevelPaths.
# @return A tuple of HfstPaths.
# def detokenize_paths(tokenized_paths):
#    pass

# Detokenize and remove all flag diacritics from \a tokenized_paths.
#
# Concatenate all transition symbols except flag diacritics on input and output levels for each path in \a tokenized_paths.
# 
# @param tokenized_paths An HfstOneLevelPaths pointer or an HfstTwoLevelPaths.
# @return A tuple of HfstPaths.
# def detokenize_and_purge_paths(tokenized_paths):
#    pass

##  A stream for reading HFST binary transducers. 
#
# An example:
# \verbatim
# istr = libhfst.HfstInputStream('testfile1.hfst')
# transducers = []
# while not (istr.is_eof()):
#     transducers.append(istr.read())
# istr.close()
# print("Read %i transducers in total." % len(transducers))
# \endverbatim
#
# For documentation on the HFST binary transducer format, see
# <a href="HeaderFormatAndConversions.html">here</a>.
class HfstInputStream:

    ##  Create a stream for reading binary transducers.
    # @param filename The name of the transducer file. If not given, standard input is used.
    #
    # @throws StreamNotReadableException
    # @throws NotTransducerStreamException
    # @throws EndOfStreamException
    # @throws TransducerHeaderException
    def __init__(self, filename=None):
        pass

    ##  Close the stream.
    #
    # If the stream points to standard input, nothing is done.
    def close():
        pass

    ##  Whether the stream is at end.
    def is_eof():
        pass

    ##  Whether badbit is set.
    def is_bad():
        pass

    ##  Whether the state of the stream is good for input operations.
    def is_good():
        pass
    
    ## The type of the first transducer in the stream. 
    #
    # By default, all transducers in a stream have the same type, else
    # a TransducerTypeMismatchException is thrown when reading the first
    # transducer that has a different type than the previous ones.
    def get_type():
        pass

    ## Return next transducer.
    #
    # @throws EndOfStreamException
    def read():
        pass

## A stream for writing binary transducers. 
#
#  An example: 
# \verbatim
# res = ['foo:bar','0','0 - 0','"?":?','a* b+']
# ostr = libhfst.HfstOutputStream(filename='testfile1.hfst')
# for re in res:
#     ostr.write(libhfst.regex(re))
#     ostr.flush()
# ostr.close()
# \endverbatim
#
# For more information on HFST transducer structure, see <a href="HeaderFormatAndConversions.html">this page</a>.
class HfstOutputStream:

    ## Open a stream for writing binary transducers.
    # @param kvargs Arguments recognized are filename, hfst_format, type.
    # @param filename The name of the file where transducers are written. If the file exists, it is overwritten. If \a filename is not given, transducers are written to standard output.
    # @param hfst_format Whether transducers are written in hfst format (default is True) or as such in their backend format.
    # @param type The type of the transducers that will be written to the stream. Default is #libhfst.get_default_fst_type().
    def __init__(self, **kvargs):
        pass

    ## Flush the stream.
    def flush():
        pass

    ##  Write the transducer \a transducer in binary format to the stream. 
    #
    # All transducers must have the same type as the stream, else a TransducerTypeMismatchException is thrown. 
    #
    # @throws TransducerTypeMismatchException
    def write(transducer):
        pass

    ##  Close the stream. 
    # If the stream points to standard output, nothing is done.
    def close():
        pass

## TODO: documentation ???
class MultiCharSymbolTrie:
    ## TODO: documentation
    def __init__(self):
        pass
    ## TODO: documentation
    # @param string const char *
    def add(string):
        pass
    ## TODO: documentation
    # @param string const char *
    # @return const char *
    def find(string)  

  
## A tokenizer for creating transducers from UTF-8 strings.
#
# Strings are tokenized from left to right using longest match tokenization.
# For example, if the tokenizer contains a multicharacter symbol 
# 'foo' and a skip symbol 'fo', the string "foo" is tokenized as 'foo:foo'.
# If the tokenizer contains a multicharacter symbol 'fo' and a skip 
# symbol 'foo', the string "foo" is tokenized as an empty string.
#
# An example:
# \verbatim
# \endverbatim
#
# @note The tokenizer only tokenizes utf-8 strings. 
# Special symbols are not included in the tokenizer 
# unless added to it. TODO: should they ???
class HfstTokenizer:

    ## Create a tokenizer that recognizes utf-8 symbols. 
    def __init__(self):
        pass

    ## Add a symbol to be skipped to this tokenizer. 
    #
    # After skipping a symbol, tokenization is always started again.
    # For example if we have a multicharacter symbol 'foo' and a 
    # skip symbol 'bar', the string "fobaro" will be tokenized 
    # 'f' 'o' 'o', not 'foo'. 
    def add_skip_symbol(self, symbol):
        pass

    ## Add a multicharacter symbol \a symbol to this tokenizer. 
    #
    # If a multicharacter symbol has a skip symbol inside it, it is
    # not considered a multicharacter symbol. For example if we have 
    # a multicharacter symbol 'foo' and a skip symbol 'bar', the string
    # "fobaro" will be tokenized 'f' 'o' 'o', not 'foo'. 
    def add_multichar_symbol(self, symbol):
        pass

    ## Tokenize the string \a input_string. 
    # @return A tuple of string pairs.
    def tokenize(self, input_string):
        pass

    ## Tokenize the string \a input_string.
    # @return A tuple of strings.
    def tokenize_one_level(self, input_string):
        pass

    ## Tokenize the string pair \a input_string : \a output_string. 
    #
    # If one string has more tokens than the other, epsilons will be
    # inserted to the end of the tokenized string with less tokens
    # so that both tokenized strings have the same number of tokens.
    #
    # @return A tuple of string pairs.
    def tokenize(self, input_string, output_string):
        pass

    ## Tokenize \a str and skip all spaces.
    # @return A tuple of strings.
    def tokenize_space_separated(self, str):
        pass

    ## If \a input_string is not valid utf-8, throw an IncorrectUtf8CodingException.
    #
    # A string is non-valid if: 
    #   - It contains one of the unsigned bytes 192, 193, 245, 246 and 247.
    #   - If it is not made up of sequences of one initial byte (0xxxxxxx, 
    #     110xxxxx, 1110xxxx or 11110xxx) followed by an appropriate number 
    #     of continuation bytes (10xxxxxx).
    #     -# Initial bytes 0xxxxxxx represent ASCII chars and may not be
    #        followed by a continuation byte.
    #     -# Initial bytes 110xxxxx are followed by exactly one 
    #        continuation byte.
    #     -# Initial bytes 1110xxxx are followed by exactly two continuation
    #        bytes.
    #     -# Initial bytes 11110xxx are followed by exactly three 
    #        continuation bytes.
    # (For reference: http://en.wikipedia.org/wiki/UTF-8)
    #
    # This function is a static one.
    def check_utf8_correctness(input_string):
        pass


## A compiler holding information contained in lexc style lexicons.
# A single LexcCompiler can be extended by adding entries to it, but little
# else can be done with it. It is sufficient to implement clone of lexc.
class LexcCompiler:

  ## Create a lexc compiler for unspecified transducer format.
  def __init__(self):
      pass

  ## Create a lexc compiler with \a impl as transducer format.
  def __init__(self, impl):
      pass

  ## Create a lexc compiler with \a impl as transducer format.
  def __init__(self, impl, withFlags):
      pass

  ## Compile lexc description from \a infile into current compiler.
  def parse(infile):
      pass

  ## Compile lexc description from file @a filename into current compiler.
  def parse(filename):
      pass

  ## Set verbosity options. When \a verbose is true, LexcCompiler will output the messages that Xerox lexc compiler does.
  def setVerbosity(verbose):
      pass

  ## todo
  def isQuiet():
      pass
  ## todo
  def setTreatWarningsAsErrors(value):
      pass
  ## todo
  def areWarningsTreatedAsErrors():
      pass
  ## todo
  def setAllowMultipleSublexiconDefinitions(value):
      pass
  ## todo
  def setWithFlags(value):
      pass
  ## todo
  def setMinimizeFlags(value):
      pass
  ## todo
  def setRenameFlags(value):
      pass

  ## Add @a alphabet to multicharacter symbol set.
  # These symbols may be used for regular expression ? for backends that do
  # not support open alphabets.
  def addAlphabet(alphabet):
      pass

  ## todo
  def addNoFlag(lexname):
      pass

  ## Set current processing lexicon name to @a lexicon_name.
  def setCurrentLexiconName(lexicon_name):
      pass

  ## Add entry defined by a @a entry to current lexicon, pointing to @a continuation weighing @a weight to current lexicon.
  def addStringEntry(entry, continuation, weight):
      pass

  ## Add entry defined by @a upper:@a lower, pointing to @a continuation weighing @a weight to current lexicon.
  def addStringPairEntry(upper, lower, continuation, weight):
      pass

  ## Add entry defined by regular expression @a xre, pointing to @a continuation weighing @a weight to current lexicon.
  def addXreEntry(xre, continuation, weight):
      pass

  ## Add macro definition named @a name matching regular expression @a xre to known xerox regular expressions.
  def addXreDefinition(name, xre):
      pass

  ## Set start lexicon's name to @a lexicon_name.
  def setInitialLexiconName(lexicon_name):
      pass

  ## Create final usable version of current lexicons and entries.
  # @return HfstTransducer pointer.
  def compileLexical():
      pass

  ## Check that current morphotax is connected and print anomalies.
  # Works like xerox lexc, for compatibility.
  def printConnectedness():
      pass

## A compiler holding information needed to compile XREs.
class XreCompiler:

  ## Construct compiler for unknown format transducers.
  def __init__(self):
      pass

  ## Create compiler for \a impl format transducers
  def __init__(self, impl):
      pass

  ## Add a definition macro. Compilers will replace arcs labeled \a name, with the transducer defined by \a xre in later phases of compilation.
  def define(name, xre):
      pass

  ## todo
  def define_list(name, symbol_list):
      pass

  ## todo
  def define_function(name, arguments, xre):
      pass

  ## todo
  def undefine(name):
      pass

  ## Compile a transducer defined by @a xre.
  # May return a pointer to @e empty transducer on non-fatal error.
  # A None pointer is returned on fatal error, if abort is not called.
  # @return An HfstTransducer pointer.
  def compile(xre):
      pass

# For example the transducer 
# 
# \verbatim
# [[@U.FEATURE.FOO@ foo] | [@U.FEATURE.BAR@ bar]]  |  [[foo @U.FEATURE.FOO@] | [bar @U.FEATURE.BAR@]]
# \endverbatim
# 
# will yield the paths <CODE>[foo foo]</CODE> and <CODE>[bar bar]</CODE>.
# <CODE>[foo bar]</CODE> and <CODE>[bar foo]</CODE> are invalidated
# by the flag diacritics so they will not be included in \a results.

## Whether symbol \a symbol is a flag diacritic.
#
# Flag diacritics are of the form 
# \verbatim
# @[PNDRCU][.][A-Z]+([.][A-Z]+)?@
# \endverbatim
def is_diacritic(symbol):
    pass

## A transducer that obligatorily performs the mappings defined by \a mappings in the context \a context when the alphabet is \a alphabet. 
# 
# @param context A pair of transducers where the first transducer defines the left context and the second transducer the right context.
# @param mappings A set of mappings (a tuple of string pairs) that the resulting transducer will perform in the context given in \a context.
# @param alphabet The set of symbol pairs (a tuple of string pairs) that defines the alphabet (see the example).
# 
# For example, a transducer yielded by the following arguments (in pseudcode)
# \verbatim
# context = pair( [c|d], [e] )
# mappings = set(a:b)
# alphabet = set(a, a:b, b, c, d, e, ...)
# \endverbatim
# obligatorily maps the symbol a to b if c or d precedes and e follows. (Elsewhere,
# the mapping of a to b is optional). This expression is identical to ![.* [c|d] [a:. & !a:b] [e] .*]
# Note that the alphabet must contain the pair a:b here.        
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>
def two_level_if(context, mappings, alphabet):
    pass

     
## A transducer that allows the mappings defined by \a mappings only in the context \a context, when the alphabet is \a alphabet. 
#         
# If called with the same arguments as in the example of #two_level_if, the transducer
# allows the mapping of symbol a to b only if c or d precedes and e follows. 
# The mapping of a to b is optional in this context but cannot occur in any other context.
#
# The expression is equivalent to 
# ![  [ ![.* [c|d]] a:b .* ] | [ .* a:b ![[e] .*] ]  ]
#         
# @see #two_level_if
def two_level_only_if(context, mappings, alphabet):
    pass
 
## A transducer that always performs the mappings defined by \a mappings in the context \a context and only in that context, when the alphabet is \a alphabet. 
# 
# If called with the same arguments as in the example of #two_level_if, the transducer
# maps symbol a to b only and only if c or d precedes and e follows.
# The mapping of a to b is obligatory in this context and cannot occur in any other context.
#
# The expression is equivalent to ![.* [c|d] [a:. & !a:b] [e] .*]  &
# ![  [ ![.* [c|d]] a:b .* ] | [ .* a:b ![[e] .*] ]  ]
#         
# @see #two_level_if
def two_level_if_and_only_if(context, mappings, alphabet):
    pass
 
## A transducer that performs an upward mapping \a mapping in the context \a context when the alphabet is \a alphabet. \a optional defines whether the mapping is optional. 
# 
# @param context A pair of transducers where the first transducer defines the left context and the second transducer the right context. Both transducers must be automata, i.e. map strings onto themselves.
# @param mapping The mapping (transducer) that the resulting transducer will perform in the context given in \a context.
# @param optional Whether the mapping is optional.
# @param alphabet The set of symbol pairs that defines the alphabet (a tuple of string pairs).                         
# 
# Each substring s of the input string which is in the input language of the transducer \a mapping and whose left context is matched 
# by the expression [.* l] (where l is the first element of \a context) and whose right context is matched by [r .*] 
# (where r is the second element in the context) is mapped to the respective surface strings defined by transducer \a mapping. Any other 
# character is mapped to the characters specified in \a alphabet. The left and right contexts must
# be automata (i.e. transducers which map strings onto themselves).
# 
# For example, a transducer yielded by the following arguments (in pseudocode)
# \verbatim
# context = pair( [c], [c] )
# mappings = [ a:b a:b ]
# alphabet = set(a, b, c)
# \endverbatim
# would map the string "caacac" to "cbbcac".
# 
# Note that the alphabet must contain the characters a and b, but not the pair
# a:b (unless this replacement is to be allowed everywhere in the context).
# 
# Note that replace operations (unlike the two-level rules) have to be combined by composition
# rather than intersection.
# 
# @throws ContextTransducersAreNotAutomataException
# 
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>
def replace_up(context, mapping, optional, alphabet):
    pass

## The same as replace_up, but matching is done on the output side of \a mapping 
# 
# @see replace_up 
# <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
def replace_down(context, mapping, optional, alphabet):
    pass

## TODO: document
def replace_down_karttunen(context, mapping, optional, alphabet):
    pass
 
## The same as replace_up, but left context matching is done on the output side of \a mapping and right context on the input side of \a mapping.
# 
# @see replace_up 
def replace_left(context, mapping, optional, alphabet):
    pass

## The same as replace_up, but left context matching is done on the input side of \a mapping and right context on the output side of \a mapping. 
# 
# @see replace_up 
# <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
def replace_right(context, mapping, optional, alphabet):
    pass

## The same as replace_up but \a mapping is performed in every context. 
# 
# @see replace_up
def replace_up(mapping, optional, alphabet):
    pass

## The same as replace_down(context, mapping, optional, alphabet) but \a mapping is performed in every context.
# 
# @see replace_up
def replace_down(mapping, optional, alphabet):
    pass

## Inversion of the replace_up and the result needs to be composed on the upper side of the input language.
#
# B <- A is the inversion of A -> B.
# \a mapping is performed in every context.
# @see replace_up
def left_replace_up(mapping, optional, alphabet):
    pass

## Inversion of the replace_up and the result needs to be composed on the upper side of the input language.
#
# B <- A is the inversion of A -> B.
# @see replace_up
def left_replace_up(context, mapping, optional, alphabet):
    pass

## Inversion of the replace_up and the result needs to be composed on the upper side of the input language. However, matching is done on the output side of \a mapping.
#
# @see replace_up
def left_replace_down(context, mapping, optional, alphabet):
    pass
 
## Inversion of the replace_up and the result needs to be composed on the upper side of the input language. However, matching is done on the output side of \a mapping.
#
# @see replace_up
def left_replace_down_karttunen(context, mapping, optional, alphabet):
    pass
 
## Inversion of the replace_up and the result needs to be composed on the upper side of the input language. However, left context matching is done on the input side of \a mapping and right context on the output side of \a mapping.
#
# @see replace_up */
def left_replace_left(context, mapping, optional, alphabet):
    pass
 
## Inversion of the replace_up and the result needs to be composed on the upper side of the input language. However, left context matching is done on the output side of \a mapping and right context on the input side of \a mapping.
#
# @see replace_up
def left_replace_right(context, mapping, optional, alphabet):
    pass



## A transducer that allows any (substring) mapping defined by \a mapping only if it occurs in any of the contexts in \a contexts. Symbols outside of the matching substrings are mapped to any symbol allowed by \a alphabet. 
# 
# @throws EmptySetOfContextsException
# 
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def restriction(contexts, mapping, alphabet):
    pass

## A transducer that requires that one of the mappings defined by \a mapping must occur in each context in \a contexts. Symbols outside of the matching substrings are mapped to any symbol allowed by \a alphabet.
# 
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def coercion(contexts, mapping, alphabet):
    pass

## A transducer that is equivalent to the intersection of restriction and coercion and requires that the mappings defined by \a mapping occur always and only in the given contexts in \a contexts. Symbols outside of the matching substrings are mapped to any symbol allowed by \a alphabet.
# 
# @see #restriction #coercion <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def restriction_and_coercion(contexts, mapping, alphabet):
    pass

 
## A transducer that specifies that a string from the input language of the transducer \a mapping may only be mapped to one of its output strings (according to transducer \a mapping) if it appears in any of the contexts in \a contexts. Symbols outside of the matching substrings are mapped to any symbol allowed by \a alphabet.
# 
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def surface_restriction(contexts, mapping, alphabet):
    pass

## A transducer that specifies that a string from the input language of the transducer \a mapping always has to the mapped to one of its output strings according to transducer \a mapping if it appears in any of the contexts in \a contexts. Symbols outside of the matching substrings are mapped to any symbol allowed by \a alphabet.
# 
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def surface_coercion(contexts, mapping, alphabet):
    pass

## A transducer that is equivalent to the intersection of surface_restriction and surface_coercion.
# 
# @see #surface_restriction #surface_coercion <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def surface_restriction_and_coercion(contexts, mapping, alphabet):
    pass

## A transducer that specifies that a string from the output language of the transducer \a mapping may only be mapped to one of its input strings (according to transducer \a mappings) if it appears in any of the contexts in \a contexts.Symbols outside of the matching substrings are mapped to any symbol allowed by \a alphabet.
# 
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def deep_restriction(contexts, mapping, alphabet):
    pass

## A transducer that specifies that a string from the output language of the transducer \a mapping always has to be mapped to one of its input strings (according to transducer \a mappings) if it appears in any of the contexts in \a contexts. Symbols outside of the matching substrings are mapped to any symbol allowed by \a alphabet.
# 
# @see <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def deep_coercion(contexts, mapping, alphabet):
    pass

## A transducer that is equivalent to the intersection of deep_restriction and deep_coercion.
# 
# @see #deep_restriction #deep_coercion <a href="ftp://ftp.ims.uni-stuttgart.de/pub/corpora/SFST/SFST-Manual.pdf">SFST manual</a>.
# @param contexts A tuple of HfstTransducer pairs.
# @param mapping An HfstTransducer.
# @param alphabet A tuple of string pairs.
def deep_restriction_and_coercion(contexts, mapping, alphabet):
    pass

## @page Symbols.html Symbols in HFST
#
# A transducer maps strings into strings.Strings are tokenized (i.e. divided) into symbols. Each transition
# in a transducer has an input and output symbol. If the input symbol of a transition
# matches a symbol of an input string, it is consumed and an output symbol equal to the output symbol
# of the transition is produced.
#
# There are some special symbols: the epsilon, unknown and identity.
# Epsilon on input side consumes no symbol, epsilon on output side produces no symbol.
# The unknown on input side matches any symbol, the unknown on output side produces any symbol.
# If unknown is on both sides of a transition, it matches any symbol and produces any symbol other than the one that was matched on the input side.
# The identity matches any symbol and produces the same symbol. It must always occur on both sides of a transition.
# There is also a class of special symbols, called flag diacritics. They are of form 
# \verbatim
# @[PNDRCU][.][A-Z]+([.][A-Z]+)?@
# \endverbatim
#
# The internal string representation for epsilon is "@_EPSILON_SYMBOL_@" (libhfst.EPSILON), for unknown "@_UNKNOWN_SYMBOL_@" (libhfst.UNKNOWN) and for identity "@_IDENTITY_SYMBOL_@" (libhfst.IDENTITY).
# These strings are used when referring to those symbols in individual transitions, e.g.
#
# \verbatim
# fsm = libhfst.HfstBasicTransducer()
# fsm.add_state(1)
# fsm.add_state(2)
# fsm.set_final_weight(2, 0.5)
# fsm.add_transition(0, 1, libhfst.EPSILON, libhfst.UNKNOWN)
# fsm.add_transition(1, 2, libhfst.IDENTITY, libhfst.IDENTITY)
# \endverbatim
#
# or reading and printing transitions in AT&& format:
#
# \verbatim
# 0 1 @_EPSILON_SYMBOL@ @_UNKNOWN_SYMBOL_@ 0.0
# 1 2 @_IDENTITY_SYMBOL@ @_IDENTITY_SYMBOL_@ 0.0
# 2 0.5
# \endverbatim
#
# There is also a shorter string for epsilon in AT&T format, "@0@".
#
# The syntax of regular expressions follows the Xerox formalism,
# where the following symbols are used instead: "0" for epsilon, and "?" for unknown and identity.
# On either side of a transition, "?" means the unknown. As a single symbol, "?" means identity-to-identity transition.
# On both sides of a transition "?" means the combination of unknown-to-unknown AND identity-to-identity transitions.
# If unknown-to-unknown transition is needed, it can be given as the subtraction [?:? - ?]. Some examples:
# 
# \verbatim
# libhfst.regex('0:foo')       # epsilon to "foo"
# libhfst.regex('0:foo')       # "foo" to epsilon
# libhfst.regex('?:foo')       # any symbol to "foo"
# libhfst.regex('?:foo')       # "foo" to any symbol
# libhfst.regex('?:?')         # any symbol to any symbol
# libhfst.regex('?')           # any symbol to the same symbol
# libhfst.regex('?:? - ?')     # any symbol to any other symbol
# \endverbatim
#
# Note that unknowns and identities are expanded with the symbols that the expression becomes aware of during its compilation:
#
# \verbatim
# libhfst.regex('?')              # equal to [?]
# libhfst.regex('? foo')          # equal to [[?|foo] foo]
# libhfst.regex('? foo bar:?')    # equal to [[?|foo|bar] foo [bar:?|bar:bar|bar:foo]]
# \endverbatim
#
# In lookup, the epsilon is printed as empty string and unknowns and identities as those symbols that they are matched with:
# \verbatim
# >>> tr = libhfst.regex('foo:0 bar:? ?')
# >>> print(tr.lookup('foobara'))
# (('bara', 0.0), ('fooa', 0.0))
# \endverbatim
#
# In extract_paths, epsilon, unknown and identity are printed as such:
# \verbatim
# >>> tr = libhfst.regex('foo:0 bar:? ?')
# >>> print(tr.extract_paths())
# {'foobar@_IDENTITY_SYMBOL_@': [('@_EPSILON_SYMBOL_@@_UNKNOWN_SYMBOL_@@_IDENTITY_SYMBOL_@', 0.0), ('@_EPSILON_SYMBOL_@bar@_IDENTITY_SYMBOL_@', 0.0), ('@_EPSILON_SYMBOL_@foo@_IDENTITY_SYMBOL_@', 0.0)],
#  'foobarfoo': [('@_EPSILON_SYMBOL_@@_UNKNOWN_SYMBOL_@foo', 0.0), ('@_EPSILON_SYMBOL_@barfoo', 0.0), ('@_EPSILON_SYMBOL_@foofoo', 0.0)], 
#  'foobarbar': [('@_EPSILON_SYMBOL_@@_UNKNOWN_SYMBOL_@bar', 0.0), ('@_EPSILON_SYMBOL_@barbar', 0.0), ('@_EPSILON_SYMBOL_@foobar', 0.0)]}
# \endverbatim


## @page QuickStart.html Quick Start to HFST
# 
# \section using_hfst Using HFST in your own code
# 
# After <a href="InstallHfst.html">installing</a> HFST on your computer, start python and execute <code>import libhfst</code>.
# 
# For example, the following simple program 
#
# \verbatim
# import libhfst
# 
# tr1 = libhfst.regex('foo:bar')
# tr2 = libhfst.regex('bar:baz')
# tr1.compose(tr2)
# print(tr1)
# \endverbatim
# 
# should print to standard output the following text when run:
# 
# \verbatim
# 0      1     foo    baz    0
# 1      0
# \endverbatim
# 
# <BR>
# 
# \section hfst_structure Structure of the API
# 
# The HFST API is written in module libhfst that includes the following classes:
# 
#    - HfstTransducer: A class for creating transducers and performing operations on them.
# 
#    - HfstInputStream and HfstOutputStream: Classes for writing and reading binary transducers.
# 
#    - HfstBasicTransducer: A class for creating transducers from scratch and iterating through their states and transitions.
# 
#    - HfstTokenizer: A class used in creating transducers from UTF-8 strings.
#  
# There are also functions in module libhfst that are not part of any class. For example #libhfst.fst
#
# <BR>
# 
# \section hfst_examples Examples of HFST functionalities
# 
# An example of creating a simple transducer from scratch and converting between transducer formats and testing
# transducer properties and handling exceptions: 
# 
# \verbatim
# import libhfst
# # Create as HFST basic transducer [a:b] with transition weight 0.3 and final weight 0.5.
# t = libhfst.HfstBasicTransducer()
# t.add_state(1)
# t.add_transition(0, 1, 'a', 'b', 0.3)
# t.set_final_weight(1, 0.5)
#
# # Convert to tropical OpenFst format (the default) and push weights toward final state.
# T = libhfst.HfstTransducer(t)
# T.push_weights(libhfst.TO_FINAL_STATE)
#
# # Convert back to HFST basic transducer.
# tc = libhfst.HfstBasicTransducer(T)
# try:
#     # Rounding might affect the precision.
#     if (0.79 < tc.get_final_weight(1)) and (tc.get_final_weight(1) < 0.81):
#         print("TEST PASSED")
#         exit(0)
#     else:
#         print("TEST FAILED")
#         exit(1)
# # If the state does not exist or is not final
# except libhfst.HfstException:
#     print("TEST FAILED: An exception thrown.")
#     exit(1)
# \endverbatim
# 
# 
# An example of creating transducers from strings, applying rules to them and printing the string pairs recognized by the resulting transducer.
#  
# \verbatim
# import libhfst
# libhfst.set_default_fst_type(libhfst.FOMA_TYPE)
# 
# # Create a simple lexicon transducer [[foo bar foo] | [foo bar baz]].
# tok = libhfst.HfstTokenizer()
# tok.add_multichar_symbol('foo')
# tok.add_multichar_symbol('bar')
# tok.add_multichar_symbol('baz')
# 
# words = libhfst.tokenized_fst(tok.tokenize('foobarfoo'))
# t = libhfst.tokenized_fst(tok.tokenize('foobarbaz'))
# words.disjunct(t)
# 
# # Create a rule transducer that optionally replaces 'bar' with 'baz' between 'foo' and 'foo'.
# rule = libhfst.regex('bar (->) baz || foo _ foo')
# 
# # Apply the rule transducer to the lexicon.
# words.compose(rule).minimize()
# 
# # Extract all string pairs from the result and print them to standard output.
# results = 0
# try:
#     # Extract paths and remove tokenization
#     results = words.extract_paths(output='dict')
# except libhfst.TransducerIsCyclicException:
#     # This should not happen because transducer is not cyclic.
#     print("TEST FAILED")
#     exit(1)
# 
# for input,outputs in results.items():
#     print('%s:' % input)
#     for output in outputs:
#         print('  %s\t%f' % (output[0], output[1]))
# \endverbatim
#
# The output:
#
# \verbatim
# foobarfoo:
#   foobarfoo     0.000000
#   foobazfoo     0.000000
# foobarbaz:
#   foobarbaz     0.000000
# \endverbatim
# 
# <BR>

## @page HfstWithSFSTOpenFstAndFoma.html Using HFST with SFST, OpenFst and foma
# 
# A binary HfstTransducer consists of an HFST header (more on HFST headers on the
# <a href="https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstTransducerHeader">
# wiki pages</a>) and the transducer of the backend implementation. 
# If you want to write backend transducers as such, you can specify it with 
# the <i>hfst_format</i> keyword argument of HfstOutputStream constructor:
# 
# \verbatim
#    HfstOutputStream(hfst_format=True)
# \endverbatim
# 
# The following piece of code will write a native OpenFst transducer 
# with tropical weights to standard output:
# 
# test.py:
# \verbatim
# import libhfst
# ab = libhfst.regex('a:b::2.8')
# out = libhfst.HfstOutputStream(hfst_format=False)
# out.write(ab)
# out.flush()
# out.close()
# \endverbatim
#
# run on command line (fstprint is native OpenFst tool):
# \verbatim
# python test.py > ab.fst
# fstprint ab.fst
# \endverbatim
#
# output:
# \verbatim
# 0       1       a       b       2.79980469
# 1
# \endverbatim
#
# An libhfst.HfstInputStream can also read backend transducers that do not have an HFST header.
# If we have the following files
#
# symbols.txt:
# \verbatim
# EPSILON 0
# a 1
# b 2
# \endverbatim
#
# ab.txt:
# \verbatim
# 0 1 a b 0.5
# 1 0.3
# \endverbatim
#
# test.py:
# \verbatim
# import libhfst
# istr = libhfst.HfstInputStream()
# while not istr.is_eof():
#     tr = istr.read()
#     print('Read transducer:')
#     print(tr)
# istr.close()
# \endverbatim
#
# the commands
#
# \verbatim
# cat ab.txt | fstcompile --isymbols=symbols.txt --osymbols=symbols.txt --keep_isymbols --keep_osymbols | python test.py
# \endverbatim
#
# will compile a native OpenFst transducer (fstcompile is a native OpenFst tool), read it with HFST tools and print it to standard output in AT&T text format:
#
# \verbatim
# Read transducer:
# 0       1       a       b       0.500000
# 1       0.300000
#
# \endverbatim
#
# For more information on HFST transducer formats and conversions, see the
# <a href="https://kitwiki.csc.fi/twiki/bin/view/KitWiki/HfstTransducerFormats">
# wiki pages</a>.
# 
# 
# 
# <H3>An issue with foma</H3>
# 
# Foma writes its binary transducers in gzipped format using the gz tools.
# However, we experienced problems when trying to write to standard output or
# read from standard input with gz tools (foma tools do not write to or read
# from standard streams). So we choose to write, and accordingly read, 
# foma transducers unzipped when writing or reading binary HfstTransducers 
# of libhfst.FOMA_TYPE. As a result, when we write an HfstTransducer of FOMA_TYPE
# in its plain backend format, the user must zip it themselves before it 
# can be used by foma tools. (update: at least the newest releases of foma
# are able to read also unzipped transducers.) Similarily, a foma transducer must be unzipped 
# before it can be read by HFST tools.
# 
# Suppose we have written a FOMA_TYPE HfstTransducer and want to use it with
# foma tools. First we write it, in its plain backend format, to file 'ab.foma'
# with the following piece of code:
# 
# \verbatim
# import libhfst
# libhfst.set_default_fst_type(libhfst.FOMA_TYPE)
# ab = libfst.regex('a:b')
# out = libhfst.HfstOutputStream(hfst_format=False)
# out.write(ab)
# out.flush()
# out.close()
# \endverbatim
# 
# The command
# 
# \verbatim
# gzip ab.foma
# \endverbatim
# 
# will create a file 'ab.foma.gz' that can be used by (older) foma tools.
# 
# The same with command line tools:
# 
# \verbatim
#    echo 'a:b' | hfst-strings2fst -f foma > ab.hfst
#    hfst-fst2fst --use-backend-format -f foma > ab.foma
#    gzip ab.foma
# \endverbatim
# 
# An example of the opposite case follows. Suppose we have a foma transducer
# 'transducer.foma' and want to read it inside an HFST program.
# The name of the file must be appended a .gz extension so that the program 
# 'gunzip' knows it is a zipped file. The commands
# 
# \verbatim
# mv transducer.foma transducer.foma.gz
# gunzip transducer.foma.gz
# \endverbatim
# 
# overwrite the original file 'transducer.foma' with an unzipped version of the
# same file. Now the file can be used by HFST:
# 
# \verbatim
# instr = libhfst.HfstInputStream('transducer.foma')
# tr = instr.read()
# instr.close()
# \endverbatim
# 
# The same with command line tools:
# 
# \verbatim
#    mv transducer.foma transducer.foma.gz
#    gunzip transducer.foma.gz
#    hfst-sometool transducer.foma
# \endverbatim

## @page InstallHfst.html Installing the HFST API library and Swig/Python bindings
# 
# TODO
