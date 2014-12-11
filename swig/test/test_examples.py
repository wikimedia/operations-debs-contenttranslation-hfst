import libhfst
import os
import sys

for file in 'foofile', 'testfile', 'testfile.att', 'testfile.hfst':
    if os.path.exists(file):
        pass # doesn't work on MinGW..
        #os.remove(file)

types = [libhfst.SFST_TYPE, libhfst.TROPICAL_OPENFST_TYPE, libhfst.FOMA_TYPE]

# The library required by the implementation type requested is not linked to HFST.
# --------------------------------------------------------------------------------
print("ImplementationTypeNotAvailableException")

for type in types:
    try:
        tr = libhfst.HfstTransducer("foo", "bar", type)
    except: # libhfst.ImplementationTypeNotAvailableException:
        assert(libhfst.hfst_get_exception() == "ImplementationTypeNotAvailableException")
        pass

assert(libhfst.hfst_get_exception() == "")

# Stream cannot be read. 
# ----------------------
#print "StreamNotReadableException"
#
#try:
#    instr = libhfst.HfstInputStream("foofile")
#except libhfst.StreamNotReadableException:
#    print "ERROR: file cannot be read."


# Stream cannot be written. 
# -------------------------
#print "StreamCannotBeWrittenException"
#
#for type in types:
#    try:
#        tr = libhfst.HfstTransducer("foo", type)
#        out = libhfst.HfstOutputStream("testfile", type)
#        out.redirect(tr)
#    except libhfst.StreamCannotBeWrittenException:
#        print "ERROR: file cannot be written."


# Stream is closed.
# -----------------
print("StreamIsClosedException")

for type in types:
    try:
        tr = libhfst.HfstTransducer("foo", type)
        out = libhfst.HfstOutputStream("testfile", type)
        out.close()
        out.redirect(tr)
        assert(False)
    except: # libhfst.StreamIsClosedException:
        assert(libhfst.hfst_get_exception() == "StreamIsClosedException")
        pass


# Transducer is cyclic. 
# ---------------------
print("TransducerIsCyclicException")

for type in types:
    transducer = libhfst.HfstTransducer("a", "b", type)
    transducer.repeat_star()
    try:
        results = libhfst.detokenize_paths(libhfst.extract_paths(transducer))
        print("The transducer has {0} paths".format(len(results)))
        assert(False)
    except: # libhfst.TransducerIsCyclicException:
        print("The transducer is cyclic and has an infinite number of paths.")


# The stream does not contain transducers. 
# ----------------------------------------
print("NotTransducerStreamException")

foofile = open('foofile', 'wb')
foofile.write('This is a text file.\n'.encode('ascii'))
foofile.write('Here is another line.\n'.encode('ascii'))
foofile.write('The file ends here.'.encode('ascii'))
foofile.close()
try:
    instr = libhfst.HfstInputStream("foofile")
except: # libhfst.NotTransducerStreamException:
    print("file does not contain transducers.")


# The stream is not in valid AT&T format. 
# ---------------------------------------
print("NotValidAttFormatException")

testfile_att = open("testfile.att", "wb")
testfile_att.write('0 1 a b\n'.encode('ascii'))
testfile_att.write('1\n'.encode('ascii'))
testfile_att.write('c\n'.encode('ascii'))
testfile_att.close()

for type in types:
    transducers = []
    ifile = libhfst.hfst_open("testfile.att", "r")
    try:
        t = libhfst.HfstTransducer(ifile, type, "epsilon")
        transducers.append(t)
        print("read one transducer")
    except: # libhfst.NotValidAttFormatException:
        print("Error reading transducer: not valid AT&T format.")

ifile.close()
print("Read {0} transducers in total.".format(len(transducers)))


# State is not final (and cannot have a final weight). 
# ----------------------------------------------------
print("StateIsNotFinalException")

tr = libhfst.HfstBasicTransducer()
tr.add_state(1)
# An exception is thrown as state number 1 is not final
try:
    w = tr.get_final_weight(1)
    assert(False)
except: # libhfst.StateIsNotFinalException:
    assert(libhfst.hfst_get_exception() == "StateIsNotFinalException")
    pass


# Context transducers are not automata.
# -------------------------------------
print("ContextTransducersAreNotAutomataException")

for type in types:
    # The second context transducer is 
    contexts = (libhfst.HfstTransducer("c", type), libhfst.HfstTransducer("c", "d", type))
    mapping = libhfst.HfstTransducer("a", "b", type)
    alphabet = (('a','a'), ('b','b'), ('c','c'), ('d','d'))
    # An exception is thrown
    # rule = libhfst.replace_up(contexts, mapping, True, alphabet)


# The state number argument is not valid.
# ---------------------------------------
print("NotValidStateNumberException")

# tr = libhfst.HfstBasicTransducer()
# tr.add_state(1)
# An exception is thrown as there is no state number 2
# w = tr.get_final_weight(2)


# Two or more transducers do not have the same type.
# --------------------------------------------------
print("TransducerTypeMismatchException")

foo = libhfst.HfstTransducer("foo", libhfst.SFST_TYPE)
bar = libhfst.HfstTransducer("bar", libhfst.FOMA_TYPE)
try:
    foo.disjunct(bar)
    assert(False)
except: # libhfst.TransducerTypeMismatchException:
    assert(libhfst.hfst_get_exception() == "TransducerTypeMismatchException")
    pass


# TODO: The set of transducer pairs is empty. 
# -------------------------------------------
#print "EmptyFooFoo"
#
#contexts = ()  # contexts is empty
#restr = libhfst.restriction(contexts, mapping, alphabet, direction)
## @package libhfst 
# Documentation for libhfst


# HfstBasicTransducer
# -------------------
print("HfstBasicTransducer")

# Create an empty transducer
# The transducer has initially one start state (number zero) 
# that is not final
fsm = libhfst.HfstBasicTransducer()
# Add two states to the transducer
fsm.add_state(1)
fsm.add_state(2)
# Create a transition [foo:bar] leading to state 1 with weight 0.1
tr = libhfst.HfstBasicTransition(1, 'foo', 'bar', 0.1)
# and add it to state zero
fsm.add_transition(0, tr)
# Add a transition [baz:baz] with weight 0 from state 1 to state 2 
fsm.add_transition(1, libhfst.HfstBasicTransition(2, 'baz', 'baz', 0.0))
# Set state 2 as final with weight 0.3
fsm.set_final_weight(2, 0.3)

# Go through all states
for state in fsm.states(): 
    # Go through all transitions
    for transition in fsm.transitions(state):
        print("{0} {1} {2} {3} {4}".format(state, transition.get_target_state(), transition.get_input_symbol(), transition.get_output_symbol(), transition.get_weight()))

    if fsm.is_final_state(state): 
        print("{0} {1}".format(state, fsm.get_final_weight(state)))
    
# HfstBasicTransducer.disjunct
# ----------------------------
print("HfstBasicTransducer.disjunct")

lexicon = libhfst.HfstBasicTransducer()
TOK = libhfst.HfstTokenizer()
lexicon.disjunct(TOK.tokenize('dog'), 0.3)
lexicon.disjunct(TOK.tokenize('cat'), 0.5)
lexicon.disjunct(TOK.tokenize('elephant'), 1.6)


# HfstTransducer
# --------------
print("HfstTransducer")

for type in types:
    transducer = libhfst.HfstTransducer('foo','bar', type)
    # transducer is reversed
    transducer.reverse()
    # transducer2 is not modified, but a copy of it is disjuncted with transducer1 
    transducer.disjunct(transducer)                                       
    # a chain of functions is possible
    transducer.reverse().determinize().reverse().determinize()      

tropical_transducer = libhfst.HfstTransducer('foo', 'bar', libhfst.TROPICAL_OPENFST_TYPE)
sfst_transducer = libhfst.HfstTransducer('foo', 'bar', libhfst.SFST_TYPE)
try:
    tropical_transducer.disjunct(sfst_transducer)
    assert(False)
except: # libhfst.TransducerTypeMismatchException:
    assert(libhfst.hfst_get_exception() == "TransducerTypeMismatchException")
    pass

tropical_transducer = libhfst.HfstTransducer('foo', 'bar', libhfst.TROPICAL_OPENFST_TYPE)
tropical_transducer.convert(libhfst.SFST_TYPE).disjunct(sfst_transducer)     
tropical_transducer = libhfst.HfstTransducer('foo', 'bar', libhfst.TROPICAL_OPENFST_TYPE)
tropical_transducer.disjunct(sfst_transducer.convert(libhfst.TROPICAL_OPENFST_TYPE)) 


# In the xerox formalism used here, "?" means the unknown symbol and "?:?" the identity pair 
tr1 = libhfst.HfstBasicTransducer()
tr1.add_state(1)
tr1.set_final_weight(1, 0)
tr1.add_transition(0, libhfst.HfstBasicTransition(1, '@_UNKNOWN_SYMBOL_@', 'foo', 0) )
# tr1 is now [ ?:foo ]

tr2 = libhfst.HfstBasicTransducer()
tr2.add_state(1)
tr2.add_state(2)
tr2.set_final_weight(2, 0)
tr2.add_transition(0, libhfst.HfstBasicTransition(1, '@_IDENTITY_SYMBOL_@', '@_IDENTITY_SYMBOL_@', 0) )
tr2.add_transition(1, libhfst.HfstBasicTransition(2, 'bar', 'bar', 0) )
# tr2 is now [ [ ?:? ] [ bar:bar ] ]

type = libhfst.SFST_TYPE
Tr1 = libhfst.HfstTransducer (tr1, type)
Tr2 = libhfst.HfstTransducer (tr2, type)
Tr1.disjunct(Tr2)
# Tr1 is now [ [ ?:foo | bar:foo ]  |  [[ ?:? | foo:foo ] [ bar:bar ]] ] 


## Create a transducer by tokenizing the utf8 string \a utf8_string with tokenizer \a multichar_symbol_tokenizer. The type of the transducer is defined by \a type. 
print("HfstTransducer.__init__")

for type in types:
    ustring = 'foobar'
    TOK = libhfst.HfstTokenizer()
    tr = libhfst.HfstTransducer(ustring, TOK, type)
    input = 'foo'
    output = 'barr'
    TOK = libhfst.HfstTokenizer()
    tr = libhfst.HfstTransducer(input, output, TOK, type)

    ## Create a transducer of type \a type as defined in AT&T format in file \a ifile. \a epsilon_symbol defines how epsilons are represented.

testfile_att = open("testfile.att", "wb")
testfile_att.write("0      1      foo      bar      0.3\n".encode('ascii'))
testfile_att.write("1      0.5\n".encode('ascii'))
testfile_att.write("--\n".encode('ascii'))
testfile_att.write("0      0.0\n".encode('ascii'))
testfile_att.write("--\n".encode('ascii'))
testfile_att.write("--\n".encode('ascii'))
testfile_att.write("0      0.0\n".encode('ascii'))
testfile_att.write("0      0      a        <eps>    0.2".encode('ascii'))
testfile_att.close()

for type in types:
    transducers = []
    ifile = libhfst.hfst_open("testfile.att", "rb")
    while (True):
        try:
            t = libhfst.HfstTransducer(ifile, type, "<eps>")
            transducers.append(t)
            # print("read one transducer")
        except: # libhfst.NotValidAttFormatException:
            if libhfst.hfst_get_exception() == "NotValidAttFormatException":
                print("Error reading transducer: not valid AT&T format.")
                ifile.close()
                assert(False)
                break
            else:
                break # End of file
    assert len(transducers) == 4


## Write the transducer in AT&T format to file \a ofile, \a write_weights defines whether weights are written.
print("HfstTransducer.write_in_att_format")

for type in types:

    foobar = libhfst.HfstTransducer("foo","bar",type)
    epsilon = libhfst.HfstTransducer("@_EPSILON_SYMBOL_@",type)
    empty = libhfst.HfstTransducer(type)
    a_star = libhfst.HfstTransducer("a",type)
    a_star.repeat_star()
    
    ofile = libhfst.hfst_open("testfile.att", "w")
    foobar.write_in_att_format(ofile)
    ofile.write("--\n")
    epsilon.write_in_att_format(ofile)
    ofile.write("--\n")
    empty.write_in_att_format(ofile)
    ofile.write("--\n")
    a_star.write_in_att_format(ofile)
    ofile.close()


## Extract a maximum of \a max_num paths that are recognized by \a transducer following a maximum of \a cycles cycles.
print("extract_paths")

for type in types:
    tr1 = libhfst.HfstTransducer("a", "b", type)
    tr1.repeat_star()
    tr2 = libhfst.HfstTransducer("c", "d", type)
    tr2.repeat_star()
    tr1.concatenate(tr2).minimize()
    results = libhfst.detokenize_paths(libhfst.extract_paths(tr1, 5, 2))

    for path in results:
        print("{0} : {1}".format(path.input, path.output))


## A stream for writing binary transducers. 
print("HfstOutputStream")

for type in types:
    # Write three HFST transducers in binary format to file named "testfile.hfst"
    out = libhfst.HfstOutputStream("testfile.hfst", type)
    out.redirect(libhfst.HfstTransducer('a', 'b', type)) 
    out.redirect(libhfst.HfstTransducer('c', 'd', type)) 
    out.redirect(libhfst.HfstTransducer('e', 'f', type)) 
    out.close()

##  A stream for reading HFST binary transducers. 
print("HfstInputStream")

instr = 0
try:
    instr = libhfst.HfstInputStream("testfile.hfst") 
except: # StreamNotReadableException: 
    print("ERROR: File does not exist.")
    exit(1)

transducers_read = 0

while not instr.is_eof(): 
    if instr.is_bad():
        print("ERROR: Stream cannot be read.")
        exit(1) 
    t = libhfst.HfstTransducer(instr)
    print("One transducer successfully read.")
    transducers_read += 1

print("Read {0} transducers in total".format(transducers_read))
instr.close()
assert(transducers_read == 3)
    

## A tokenizer for creating transducers from UTF-8 strings.
print("HfstTokenizer")

TOK = libhfst.HfstTokenizer()
TOK.add_multichar_symbol("<br />")
TOK.add_skip_symbol("<p>")
TOK.add_skip_symbol("</p>")
spv = TOK.tokenize("<p>A<br />paragraph!</p>")
assert spv == (('A','A'), ('<br />','<br />'), ('p','p'), ('a','a'), ('r','r'), ('a','a'), ('g','g'), ('r','r'), ('a','a'), ('p','p'), ('h','h'), ('!','!'))


## Quick Start to HFST
print("Tutorials")

for type in types: 
    tr1 = libhfst.HfstTransducer("foo", "bar", type)
    tr2 = libhfst.HfstTransducer("bar", "baz", type)
    tr1.compose(tr2)
    tr1.write_in_att_format(libhfst.hfst_stdout());


# Create an HFST basic transducer [a:b] with transition weight 0.3 and final weight 0.5.
t = libhfst.HfstBasicTransducer()
t.add_state(1)
t.add_transition(0, libhfst.HfstBasicTransition(1, "a", "b", 0.3))
t.set_final_weight(1, 0.5)

# Convert to tropical OpenFst format and push weights toward final state.
T = libhfst.HfstTransducer(t, libhfst.TROPICAL_OPENFST_TYPE)
T.push_weights(libhfst.TO_FINAL_STATE)

# Convert back to HFST basic transducer.
tc = libhfst.HfstBasicTransducer(T)
try:
    # Rounding might affect the precision. 
    if (0.79 < tc.get_final_weight(1)) and (tc.get_final_weight(1) < 0.81):
        # print "TEST OK"
        # exit(0)
        pass
    else:
        print("TEST FAILED")
        exit(1)
# If the state does not exist or is not final */
except: # libhfst.HfstException:
    print("TEST FAILED: An exception thrown.")
    exit(1)


# An example of creating transducers from strings, applying rules to them and printing the string pairs recognized by the resulting transducer.
 
for type in types:

    # Create a simple lexicon transducer [[foo bar foo] | [foo bar baz]].
 
    tok = libhfst.HfstTokenizer()
    tok.add_multichar_symbol("foo")
    tok.add_multichar_symbol("bar")
    tok.add_multichar_symbol("baz")
  
    words = libhfst.HfstTransducer("foobarfoo", tok, type)
    t = libhfst.HfstTransducer("foobarbaz", tok, type);
    words.disjunct(t)

  
    # Create a rule transducer that optionally replaces "bar" with "baz" between "foo" and "foo".

    context = (libhfst.HfstTransducer("foo", type), libhfst.HfstTransducer("foo", type) )
    mapping = libhfst.HfstTransducer("bar", "baz", type)
    optional = True
    alphabet = (('foo','foo'), ('bar','bar'), ('baz','baz'))

    rule = libhfst.HfstTransducer(type) #libhfst.replace_up(context, mapping, optional, alphabet) TODO

    # Apply the rule transducer to the lexicon. 
    words.compose(rule).minimize()
  
  
    # Extract all string pairs from the result and print them to standard output.
    results = 0
    try:
        # Extract paths and remove tokenization
        results = libhfst.detokenize_paths(libhfst.extract_paths(words))
    except: # libhfst.TransducerIsCyclicException:
        # This should not happen because transducer is not cyclic.
        print("TEST FAILED")
        exit(1)

    # Go through all paths and print them.
    for path in results:
        print("{0} : {1}   {2}".format(path.input, path.output, path.weight))


for file in 'foofile', 'testfile', 'testfile.att', 'testfile.hfst':
    if os.path.exists(file):
        pass # os.remove(file) doesn't work on MinGW..
