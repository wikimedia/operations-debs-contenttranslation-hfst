import sys
sys.path.insert(1, '/home/eaxelson/hfst-git/hfst/python/')


# The examples given in doxygen documentation

import libhfst

# StreamIsClosedException
try:
    tr = libhfst.regex('foo')
    outstr = libhfst.HfstOutputStream(filename='testfile')
    outstr.close()
    outstr.write(tr)
except libhfst.StreamIsClosedException:
    print("Could not write transducer: stream to file was closed.")

# TransducerIsCyclicException
transducer = libhfst.regex('[a:b]*')
try:
    results = transducer.extract_paths(output='text')
    print("The transducer has %i paths:" % len(results))
    print(results)
except libhfst.TransducerIsCyclicException:
    print("The transducer is cyclic and has an infinite number of paths. Some of them:")
    results = transducer.extract_paths(output='text', max_cycles=5)
    print(results)

# NotTransducerStreamException
f = open('foofile', 'w')
f.write('This is an ordinary text file.\n')
f.close()
try:
    instr = libhfst.HfstInputStream('foofile')
    tr = instr.read()
    print(tr)
    instr.close()
except libhfst.NotTransducerStreamException:
    print("Could not print transducer: the file does not contain binary transducers.")

f = open('testfile1.att', 'w')
f.write('0 1 a b\n\
1 2 c\n\
2\n')
f.close()
f = libhfst.hfst_open('testfile1.att', 'r')
try:
    tr = libhfst.read_att(f)
except libhfst.NotValidAttFormatException:
    print('Could not read file: it is not in valid ATT format.')
f.close()

# StateIsNotFinalException
tr = libhfst.HfstBasicTransducer()
tr.add_state(1)
# An exception is thrown as state number 1 is not final
try:
    w = tr.get_final_weight(1)
except libhfst.StateIsNotFinalException:
    print("State is not final.")

# ContextTransducersAreNotAutomataException
# try:
#    tr = libhfst.regex('a -> b || c:c __ c:d')
# except libhfst.ContextTransducersAreNotAutomataException:
#    print("Context transducers must be automata.")

# TransducersAreNotAutomataException
tr1 = libhfst.regex('foo:bar')
tr2 = libhfst.regex('bar:baz')
try:
    tr1.cross_product(tr2)
except libhfst.TransducersAreNotAutomataException:
    print('Transducers must be automata in cross product.')

# StateIndexOutOfBoundsException
tr = libhfst.HfstBasicTransducer()
tr.add_state(1)
try:
    w = tr.get_final_weight(2)
except libhfst.StateIndexOutOfBoundsException:
    print('State number 2 does not exist')

# TransducerTypeMismatchException:
libhfst.set_default_fst_type(libhfst.TROPICAL_OPENFST_TYPE)
tr1 = libhfst.regex('foo')
tr2 = libhfst.regex('bar')
tr2.convert(libhfst.FOMA_TYPE)
try:
    tr1.disjunct(tr2)
except libhfst.TransducerTypeMismatchException:
    print('The implementation types of transducers must be the same.')

# fst
# One unweighted identity path:
if not libhfst.fst('foo').compare(libhfst.regex('{foo}')):
    raise RuntimeError('')
# Weighted path: a tuple of string and number, e.g. 
if not libhfst.fst(('foo',1.4)).compare(libhfst.regex('{foo}::1.4')):
    raise RuntimeError('')
if not libhfst.fst(('bar',-3)).compare(libhfst.regex('{bar}::-3')):
    raise RuntimeError('')
if not libhfst.fst(('baz',0)).compare(libhfst.regex('{baz}')):
    raise RuntimeError('')
# Several paths: a list or a tuple of paths and/or weighted paths, e.g.
if not libhfst.fst(['foo', 'bar']).compare(libhfst.regex('{foo}|{bar}')):
    raise RuntimeError('')
if not libhfst.fst(('foo', ('bar',5.0))).compare(libhfst.regex('{foo}|{bar}::5.0')):
    raise RuntimeError('')
if not libhfst.fst(('foo', ('bar',5.0), 'baz', 'Foo', ('Bar',2.4))).compare(libhfst.regex('{foo}|{bar}::5.0|{baz}|{Foo}|{Bar}::2.4')):
    raise RuntimeError('')
if not libhfst.fst([('foo',-1), ('bar',0), ('baz',3.5)]).compare(libhfst.regex('{foo}::-1|{bar}|{baz}::3.5')):
    raise RuntimeError('')
# A dictionary
if not libhfst.fst({'foo':'foo', 'bar':('foo',1.4), 'baz':(('foo',-1),'BAZ')}).compare(libhfst.regex('{foo}|{bar}:{foo}::1.4|{baz}:{foo}::-1|{baz}:{BAZ}')):
    raise RuntimeError('')

# tokenized_fst
tok = libhfst.HfstTokenizer()
tok.add_multichar_symbol('foo')
tok.add_multichar_symbol('bar')
tr = libhfst.tokenized_fst(tok.tokenize('foobar', 'foobaz'))
if not tr.compare(libhfst.regex('[foo:foo bar:b 0:a 0:z]')):
    raise RuntimeError('')

# HfstBasicTransducer
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
for state, arcs in enumerate(fsm):
    for arc in arcs:
        print('%i ' % (state), end='')
        print(arc)
    if fsm.is_final_state(state):
        print('%i %f' % (state, fsm.get_final_weight(state)) )

for state in fsm.states():
    for arc in fsm.transitions(state):
        print('%i ' % (state), end='')
        print(arc)
    if fsm.is_final_state(state):
        print('%i %f' % (state, fsm.get_final_weight(state)) )

# HfstBasicTransducer.disjunct
lexicon = libhfst.HfstBasicTransducer()
tok = libhfst.HfstTokenizer()
lexicon.disjunct(tok.tokenize('dog'), 0.3)
lexicon.disjunct(tok.tokenize('cat'), 0.5)
lexicon.disjunct(tok.tokenize('elephant'), 1.6)
lexicon = libhfst.HfstTransducer(lexicon)
if not lexicon.compare(libhfst.regex('{dog}::0.3|{cat}::0.5|{elephant}::1.6')):
    raise RuntimeError('')

# HfstBasicTransducer.transitions
for state in fsm.states():
    for arc in fsm.transitions(state):
        print('%i ' % (state), end='')
        print(arc)
    if fsm.is_final_state(state):
        print('%i %f' % (state, fsm.get_final_weight(state)) )

# HfstBasicTransducer.substitute and HfstTransducer.substitute
hfst = libhfst.regex('a:a')
basic = libhfst.HfstBasicTransducer(hfst)
hfst.substitute('a', 'A', input=True, output=False)
basic.substitute('a', 'A', input=True, output=False)

hfst = libhfst.regex('a a:b b')
basic = libhfst.HfstBasicTransducer(hfst)
hfst.substitute(('a','b'),('A','B'))
basic.substitute(('a','b'),('A','B'))

hfst = libhfst.regex('a a:b b')
basic = libhfst.HfstBasicTransducer(hfst)
hfst.substitute(('a','b'), (('A','B'),('a','B'),('A','b')))
basic.substitute(('a','b'), (('A','B'),('a','B'),('A','b')))

hfst = libhfst.regex('a a:b b')
basic = libhfst.HfstBasicTransducer(hfst)
hfst.substitute(('a','b'), libhfst.regex('[a:b]+'))
basic.substitute(('a','b'), libhfst.HfstBasicTransducer(libhfst.regex('[a:b]+')))

hfst = libhfst.regex('a b c d')
basic = libhfst.HfstBasicTransducer(hfst)
hfst.substitute({'a':'A', 'b':'B', 'c':'C'})
basic.substitute({'a':'A', 'b':'B', 'c':'C'})

hfst = libhfst.regex('a a:b b b:c c c:d d')
basic = libhfst.HfstBasicTransducer(hfst)
hfst.substitute( {('a','a'):('A','A'), ('b','b'):('B','B'), ('c','c'):('C','C')} )
basic.substitute( {('a','a'):('A','A'), ('b','b'):('B','B'), ('c','c'):('C','C')} )

# HfstBasicTransducer.enumerate
for state, arcs in enumerate(fsm):
    for arc in arcs:
        print('%i ' % (state), end='')
        print(arc)
    if fsm.is_final_state(state):
        print('%i %f' % (state, fsm.get_final_weight(state)) )

# HfstTransducer
# argument handling
transducer1 = libhfst.regex('foo:bar baz')
transducer2 = libhfst.regex('FOO:BAR BAZ')
transducer1.reverse()
transducer1.disjunct(transducer2)
if not transducer2.compare(libhfst.regex('FOO:BAR BAZ')):
    raise RuntimeError('')
transducer1.reverse()
transducer1.determinize()
transducer1.reverse()
transducer1.determinize()
# implementation types
tropical_transducer = libhfst.regex('foo')
tropical_transducer.convert(libhfst.TROPICAL_OPENFST_TYPE)
foma_transducer = libhfst.regex('foo')
foma_transducer.convert(libhfst.FOMA_TYPE)
# TODO: segfaults
try:
    tropical_transducer.compare(foma_transducer)
except libhfst.TransducerTypeMismatchException:
   print('Implementation types of transducers must be the same.')

# read_att from file
f = open('testfile2.att', 'w')
f.write(
"""0 1 foo bar 0.3
1 0.5
--
0 0.0
--
--
0 0.0
0 0 a <eps> 0.2
""")
f.close()

transducers = []
ifile = libhfst.hfst_open('testfile2.att', 'r')
try:
    while (not ifile.is_eof()):
        t = libhfst.read_att(ifile, '<eps>')
        transducers.append(t)
        print("read one transducer")
except libhfst.NotValidAttFormatException:
    print("Error reading transducer: not valid AT&T format.")
ifile.close()
print("Read %i transducers in total" % len(transducers))

# read_att from string
#att_str = """0 1 a b
#1 2 c d
#2
#"""
#print(att_str)
#tr = libhfst.read_att(att_str, '@0@')
#print(tr)
#exit(0)

# write_att
tr1 = libhfst.regex('[foo:bar baz:0 " "]::0.3')
tr2 = libhfst.empty_fst()
tr3 = libhfst.epsilon_fst(0.5)
tr4 = libhfst.regex('[foo]')
tr5 = libhfst.empty_fst()

f = libhfst.hfst_open('testfile3.att', 'w')
for tr in [tr1, tr2, tr3, tr4]:
    tr.write_att(f)
    f.write('--\n')
tr5.write_att(f)
f.close()

# extract_paths
tr = libhfst.regex('a:b+ (a:c+)')
print(tr)
print(tr.extract_paths(max_cycles=1, output='text'))
print(tr.extract_paths(max_number=4, output='text'))
print(tr.extract_paths(max_cycles=1, max_number=4, output='text'))

# HfstOutputStream
res = ['foo:bar','0','0 - 0','"?":?','a* b+']
ostr = libhfst.HfstOutputStream(filename='testfile1.hfst')
for re in res:
    ostr.write(libhfst.regex(re))
    ostr.flush()
ostr.close()

# HfstInputStream
istr = libhfst.HfstInputStream('testfile1.hfst')
transducers = []
while not (istr.is_eof()):
    transducers.append(istr.read())
istr.close()
if not len(transducers) == len(res):
    raise RuntimeError('')
i=0
for tr in transducers:
    if not tr.compare(libhfst.regex(res[i])):
        raise RuntimeError('')
    i+=1

# push_weights

# QuickStart (1/3)

tr1 = libhfst.regex('foo:bar')
tr2 = libhfst.regex('bar:baz')
tr1.compose(tr2)
print(tr1)

# QuickStart (2/3)

# Create as HFST basic transducer [a:b] with transition weight 0.3 and final weight 0.5.
t = libhfst.HfstBasicTransducer()
t.add_state(1)
t.add_transition(0, 1, 'a', 'b', 0.3)
t.set_final_weight(1, 0.5)

# Convert to tropical OpenFst format (the default) and push weights toward final state.
T = libhfst.HfstTransducer(t)
T.push_weights(libhfst.TO_FINAL_STATE)

# Convert back to HFST basic transducer.
tc = libhfst.HfstBasicTransducer(T)
try:
    # Rounding might affect the precision.
    if (0.79 < tc.get_final_weight(1)) and (tc.get_final_weight(1) < 0.81):
        print("TEST PASSED")
    else:
        raise RuntimeError('')
# If the state does not exist or is not final
except libhfst.HfstException:
    print("TEST FAILED: An exception thrown.")
    raise RuntimeError('')

# QuickStart (3/3)

libhfst.set_default_fst_type(libhfst.FOMA_TYPE)

# Create a simple lexicon transducer [[foo bar foo] | [foo bar baz]].
tok = libhfst.HfstTokenizer()
tok.add_multichar_symbol('foo')
tok.add_multichar_symbol('bar')
tok.add_multichar_symbol('baz')

words = libhfst.tokenized_fst(tok.tokenize('foobarfoo'))
t = libhfst.tokenized_fst(tok.tokenize('foobarbaz'))
words.disjunct(t)

# Create a rule transducer that optionally replaces 'bar' with 'baz' between 'foo' and 'foo'.
rule = libhfst.regex('bar (->) baz || foo _ foo')

# Apply the rule transducer to the lexicon.
words.compose(rule)
words.minimize()

# Extract all string pairs from the result and print them to standard output.
results = 0
try:
    # Extract paths and remove tokenization
    results = words.extract_paths(output='dict')
except libhfst.TransducerIsCyclicException:
    # This should not happen because transducer is not cyclic.
    print("TEST FAILED")
    exit(1)

for input,outputs in results.items():
    print('%s:' % input)
    for output in outputs:
        print('  %s\t%f' % (output[0], output[1]))


# Foma issue

