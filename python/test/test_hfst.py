import sys
sys.path.insert(1, '/home/eaxelson/hfst-git/hfst/python/')

import libhfst
import os.path
from inspect import currentframe

def get_linenumber():
    cf = currentframe()
    return cf.f_back.f_lineno

for type in (libhfst.TROPICAL_OPENFST_TYPE, libhfst.FOMA_TYPE):

    print('\n--- Testing implementation type %s ---\n' % libhfst.fst_type_to_string(type))

    libhfst.set_default_fst_type(type)

    tr1 = None
    tr2 = None
    tr3 = None

    if not os.path.isfile('foobar.hfst'):
        raise RuntimeError('Missing file: foobar.hfst')

    istr = libhfst.HfstInputStream('foobar.hfst')
    numtr = 0
    try:
        tr1 = istr.read()
        numtr += 1
        tr2 = istr.read()
        numtr += 1
        tr3 = istr.read()
        numtr += 1
    except libhfst.EndOfStreamException:
        pass
    except:
        raise RuntimeError(get_linenumber())
    istr.close()

    if numtr != 2:
        raise RuntimeError(get_linenumber())

    tr1.convert(libhfst.get_default_fst_type())
    tr2.convert(libhfst.get_default_fst_type())

    ostr = libhfst.HfstOutputStream(filename='foobar2.hfst')
    ostr.write(tr1)
    ostr.write(tr2)
    ostr.flush()
    ostr.close()

    TR1 = None
    TR2 = None
    TR3 = None

    istr = libhfst.HfstInputStream('foobar2.hfst')
    numtr = 0
    try:
        TR1 = istr.read()
        numtr += 1
        TR2 = istr.read()
        numtr += 1
        TR3 = istr.read()
        numtr += 1
    except libhfst.EndOfStreamException:
        pass
    except:
        raise RuntimeError(get_linenumber())
    istr.close()

    if numtr != 2:
        raise RuntimeError(get_linenumber())
    
    if not (TR1.compare(tr1)):
        raise RuntimeError(get_linenumber())
    if not (TR2.compare(tr2)):
        raise RuntimeError(get_linenumber())

    # Copy constructor
    transducer = libhfst.HfstTransducer(TR1)
    if not (TR1.compare(transducer)):
        raise RuntimeError(get_linenumber())
    if not (transducer.compare(TR1)):
        raise RuntimeError(get_linenumber())

    # Read lexc
    tr = libhfst.compile_lexc_file('test.lexc')
    tr.insert_freely(tr1)
    tr.minimize()
    tr.insert_freely(('A','B'))
    tr.minimize()

    # Substitute
    tr = libhfst.regex('a a:b b;')
    tr.substitute('a', 'A', input=True, output=False)
    eq = libhfst.regex('A:a A:b b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    tr.substitute('a', 'A', input=False, output=True)
    eq = libhfst.regex('a:A a:b b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    tr.substitute('a','A')
    eq = libhfst.regex('A A:b b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    tr.substitute(('a','b'),('A','B'))
    eq = libhfst.regex('a A:B b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    tr.substitute(('a','b'),(('A','B'),('B','C'),('C','D')))
    eq = libhfst.regex('a [A:B|B:C|C:D] b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    tr.substitute(('a','b'),(('A','B'),('B','C'),('C','D')))
    eq = libhfst.regex('a [A:B|B:C|C:D] b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    tr.substitute({'a':'A', 'b':'B', 'c':'C'})
    eq = libhfst.regex('A A:B B;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    tr.substitute({('a','a'):('A','a'), ('a','b'):('a','B'), ('c','c'):('C','c')})
    eq = libhfst.regex('A:a a:B b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    tr = libhfst.regex('a a:b b;')
    sub = libhfst.regex('[c:d]+;')
    tr.substitute(('a','b'),sub)
    eq = libhfst.regex('a [c:d]+ b;')
    if not (tr.compare(eq)):
        raise RuntimeError(get_linenumber())

    # push weights
    tr = libhfst.regex('[a::1 a:b::0.3 b::0]::0.7;')
    tr.push_weights(libhfst.TO_INITIAL_STATE)
    tr.push_weights(libhfst.TO_FINAL_STATE)

    # set final weights
    tr = libhfst.regex('(a a:b (b));')
    tr.set_final_weights(0.1)
    tr.set_final_weights(0.4, True)

    # reading and writing in text format
    f = open('testfile.att', 'w')
    f.write('0 1 foo bar 0.5\n\
0 1 fo ba 0.2\n\
0 1 f b 0\n\
1 2 baz baz\n\
2 0.1\n\
--\n')
    f.close()

    numtr = 0
    f = libhfst.hfst_open('testfile.att', 'r')
    while not f.is_eof():
        TR = libhfst.read_att(f)
        numtr += 1
    try:
        libhfst.read_att(f)
    except libhfst.EndOfStreamException:
        pass
    f.close()
    if numtr != 2:
        raise RuntimeError(get_linenumber())

    f = libhfst.hfst_open('foo_att_prolog', 'w')
    f.write('-- in ATT format --\n')
    TR.write_att(f)
    f.write('-- in prolog format --\n')
    TR.write_prolog(f, 'FOOBAR_TRANSDUCER')
    f.close()

    fsm = libhfst.read_att_string(' 0\t 1 a b\n\
                                1 2 c   d 0.5\n\
2 \n\
2 3 \t\te f\n\
                                    3   0.3 ')
    #if not fsm.compare(libhfst.regex('a:b c:d::0.5 (e:f::0.3)')):
    #    raise RuntimeError('read_att_string failed')

    # Lookup and path extraction
    tr = libhfst.regex('foo:bar::0.5 | foo:baz')

    print('tr.lookup')
    try:
        print(tr.lookup('foo', max_number=5, output='text'))
    except libhfst.FunctionNotImplementedException:
        print('converting...')
        TR = libhfst.HfstTransducer(tr)
        TR.convert(libhfst.HFST_OLW_TYPE)
        print(TR.lookup('foo', max_number=5, output='text'))

#  def lookup_fd(self, lookup_path, **kvargs):
#      max_weight = None
#      infinite_cutoff = -1 # Is this right?
#      output='dict' # 'dict' (default), 'text', 'raw'


    fsm = libhfst.HfstBasicTransducer(tr)
    print(fsm.lookup_fd((('foo'))))

    print('tr.extract_paths')
    print(tr.extract_paths(obey_flags='True', filter_flags='False', max_number=3, output='dict'))

    def test_fst(input, result):
        tr1_ = libhfst.fst(input)
        tr2_ = libhfst.regex(result)
        if not tr1_.compare(tr2_):
            raise RuntimeError('test_fst failed with input: ' + input)

    # Create automaton:
    # unweighted
    test_fst('foobar', '[f o o b a r]')
    test_fst(['foobar'], '[f o o b a r]')
    test_fst(['foobar', 'foobaz'], '[f o o b a [r|z]]')
    # with weights
    test_fst(('foobar', 0.3), '[f o o b a r]::0.3')
    test_fst([('foobar', 0.5)], '[f o o b a r]::0.5')
    test_fst(['foobar', ('foobaz', -2)], '[ f o o b a [r|[z::-2]] ]')
    # Special inputs
    test_fst('*** FOO ***', '{*** FOO ***}')

    try:
        foo = libhfst.fst('')
        raise RuntimeError(get_linenumber())
    except RuntimeError as e:
        if not e.__str__() == 'Empty word.':
            raise RuntimeError(get_linenumber())

    # Create transducer:
    # unweighted
    test_fst({'foobar':'foobaz'}, '[f o o b a r:z]')
    test_fst({'foobar':['foobar','foobaz']}, '[f o o b a [r|r:z]]')
    test_fst({'foobar':('foobar','foobaz')}, '[f o o b a [r|r:z]]')
    test_fst({'foobar':'foobaz', 'FOOBAR':('foobar','FOOBAR'), 'Foobar':['Foo','bar','Foobar']}, '[f o o b a r:z] | [F O O B A R] | [F:f O:o O:o B:b A:a R:r] | [F o o b:0 a:0 r:0] | [F:b o:a o:r b:0 a:0 r:0] | [F o o b a r]')

    # with weights
    test_fst({'foobar':('foobaz', -1)}, '[f o o b a r:z]::-1')
    test_fst({'foobar':['foobar',('foobaz',-2.0)]}, '[f o o b a [r|r:z::-2.0]]')
    test_fst({'foobar':('foobar',('foobaz',3.5))}, '[f o o b a [r|r:z::3.5]]')
    test_fst({'foobar':('foobaz', -1), 'FOOBAR':('foobar',('FOOBAR', 2)), 'Foobar':[('Foo',2.5),'bar',('Foobar',0.3)]}, '[f o o b a r:z]::-1 | [F O O B A R]::2 | [F:f O:o O:o B:b A:a R:r] | [F o o b:0 a:0 r:0]::2.5 | [F:b o:a o:r b:0 a:0 r:0] | [F o o b a r]::0.3')

    # Special inputs
    test_fst({'*** FOO ***':'+++ BAR +++'}, '{*** FOO ***}:{+++ BAR +++}')

    try:
        foo = libhfst.fst({'':'foo'})
        raise RuntimeError(get_linenumber())
    except RuntimeError as e:
        if not e.__str__() == 'Empty word.':
            raise RuntimeError(get_linenumber())
    try:
        foo = libhfst.fst({'foo':''})
        raise RuntimeError(get_linenumber())
    except RuntimeError as e:
        if not e.__str__() == 'Empty word.':
            raise RuntimeError(get_linenumber())

    # Tokenized input
    def test_tokenized(tok, pathin, pathout, exp, weight=0):
        tokenized = None
        if (pathout == None):
            tokenized = tok.tokenize_one_level(pathin)
        else:
            tokenized = tok.tokenize(pathin, pathout)
        if not libhfst.tokenized_fst(tokenized, weight).compare(libhfst.regex(exp)):
            if pathout == None:
                raise RuntimeError('test_tokenized failed with input: ' + pathin)
            else:
                raise RuntimeError('test_tokenized failed with input: ' + pathin + ", " + pathout)

    tok = libhfst.HfstTokenizer()

    test_tokenized(tok, 'foobar', None, '[f o o b a r]')
    test_tokenized(tok, 'foobar', 'foobar', '[f o o b a r]')
    test_tokenized(tok, 'foobar', 'foobaz', '[f o o b a r:z]')
    test_tokenized(tok, 'fööbär?', None, '[f ö ö b ä r "?"]')
    test_tokenized(tok, 'fööbär?', 'fööbär?', '[f ö ö b ä r "?"]')
    test_tokenized(tok, 'fööbär?', 'fööbäz!', '[f ö ö b ä r:z "?":"!"]::0.5', 0.5)

    test_tokenized(tok, 'foo', None, '[f o o]')
    test_tokenized(tok, 'foobar', 'foo', '[f o o b:0 a:0 r:0]')
    test_tokenized(tok, 'bar', 'foobaz', '[b:f a:o r:o 0:b 0:a 0:z]')
    test_tokenized(tok, 'bär?', None, '[b ä r "?"]')
    test_tokenized(tok, 'fööbär?', 'bär?', '[f:b ö:ä ö:r b:"?" ä:0 r:0 "?":0]')
    test_tokenized(tok, 'bär?', 'fööbäz!', '[b:f ä:ö r:ö "?":b 0:ä 0:z 0:"!"]')

    tok.add_skip_symbol('fö')
    tok.add_multichar_symbol('föö')
    tok.add_multichar_symbol('fööbär')

    test_tokenized(tok, 'föbär', None, '[b ä r]')
    test_tokenized(tok, 'fööbär', None, '[fööbär]')
    test_tokenized(tok, 'föfööfö', None, '[föö]')

    test_tokenized(tok, 'föbär', 'foofö', '[b:f ä:o r:o]')
    test_tokenized(tok, 'fööbär', 'föbar', '[fööbär:b 0:a 0:r]')
    test_tokenized(tok, 'föfööfö', 'föföföföö', '[föö]')

    tok = libhfst.HfstTokenizer()
    tok.add_skip_symbol('?')
    tok.add_skip_symbol(' ')
    test_tokenized(tok, 'How is this tokenized?', None, '[H o w i s t h i s t o k e n i z e d]')
    tok.add_skip_symbol(' is ')
    test_tokenized(tok, 'How is this tokenized?', None, '[H o w t h i s t o k e n i z e d]')

    tok = libhfst.HfstTokenizer()
    tok.add_multichar_symbol(libhfst.EPSILON) # TODO: should this be included by default???
    test_tokenized(tok, '@_EPSILON_SYMBOL_@foo', None, '[f o o]')

    if not libhfst.tokenized_fst([(libhfst.EPSILON,'b'),('f','a'),('o','a'),('o','r')]).compare(libhfst.regex('[0:b f:a o:a o:r]')):
        raise RuntimeError(get_linenumber())

    # Is this ok???
    if not libhfst.regex('"' + libhfst.EPSILON + '"').compare(libhfst.regex('[0]')):
        raise RuntimeError(get_linenumber())
    if not libhfst.regex('"' + libhfst.IDENTITY + '"').compare(libhfst.regex('[?]')):
        raise RuntimeError(get_linenumber())
    if not libhfst.regex('"' + libhfst.UNKNOWN + '":"' + libhfst.UNKNOWN + '"').compare(libhfst.regex('[?:?]')):
        raise RuntimeError(get_linenumber())

    # other python functions
    if not libhfst.empty_fst().compare(libhfst.regex('[0-0]')):
        raise RuntimeError(get_linenumber())
    if not libhfst.epsilon_fst().compare(libhfst.regex('[0]')):
        raise RuntimeError(get_linenumber())
    if not libhfst.epsilon_fst(-1.5).compare(libhfst.regex('[0]::-1.5')):
        raise RuntimeError(get_linenumber())

    # Non-ascii characters and unknowns/identities
    tr1 = libhfst.regex('Ä:é å ?;')
    tr2 = libhfst.regex('? Ö;')
    tr1.concatenate(tr2)
    result = libhfst.regex('Ä:é å [Ä|é|å|Ö|?] [Ä|é|å|Ö|?] Ö;')
    if not tr1.compare(result):
        raise RuntimeError(get_linenumber())

    tr1 = libhfst.regex('ñ ?:á;')
    tr2 = libhfst.regex('Ê:?;')
    tr1.concatenate(tr2)
    result = libhfst.regex('ñ [ñ:á|á|Ê:á|?:á] [Ê:ñ|Ê|Ê:á|Ê:?];')
    if not tr1.compare(result):
        raise RuntimeError(get_linenumber())

    # Other functions (TODO: more extensixe checks)
    tr = libhfst.regex('[foo]|[foo bar]|[f o o bar baz]')
    if not tr.longest_path_size() == 5:
        raise RuntimeError(get_linenumber())
    result = tr.extract_longest_paths()
    if not len(result) == 1:
        raise RuntimeError(get_linenumber())
    result = tr.extract_shortest_paths()    
    if not len(result) == 1:
        raise RuntimeError(get_linenumber())

    # XfstCompiler
    if libhfst.compile_xfst_file('test_pass.xfst') != 0:
        raise RuntimeError(get_linenumber())
    if libhfst.compile_xfst_file('test_fail.xfst') == 0:
        raise RuntimeError(get_linenumber())
    if libhfst.compile_xfst_file('test_fail.xfst', quit_on_fail=False, verbosity=0) != 0:
        raise RuntimeError(get_linenumber())

    # regex compiler
    import io
    msg = io.StringIO()
    msg.write('This is the error message:\n')
    tr = libhfst.regex('foo\\', error=msg)
    if (tr == None):
        msg.write('This was the error message.\n')
        print(msg.getvalue())
    import sys
    msg = sys.stdout
    tr = libhfst.regex('foo\\', error=msg)

    # lexc compiler
    msg = io.StringIO()
    tr = libhfst.compile_lexc_file('test.lexc', output=msg, verbosity=2)
    print('This is the output from lexc:')
    print(msg.getvalue())

print('\n--- Testing HfstBasicTransducer ---\n')

# Create basic transducer, write it to file, read it, and test equivalence
fsm = libhfst.HfstBasicTransducer()
fsm.add_state(0)
fsm.add_state(1)
fsm.set_final_weight(1, 0.3)
tr = libhfst.HfstBasicTransition(1, 'foo', 'bar', 0.5)
fsm.add_transition(0, tr)
fsm.add_transition(0, 0, 'baz', 'baz')
fsm.add_transition(0, 0, 'baz', 'BAZ', 0.1)

f = libhfst.hfst_open('foo_basic', 'w')
fsm.write_att(f)
f.close()

f = libhfst.hfst_open('foo_basic', 'r')
fsm2 = libhfst.HfstBasicTransducer.read_att(f, libhfst.EPSILON)
f.close()

FSM = libhfst.HfstTransducer(fsm, libhfst.FOMA_TYPE)
FSM2 = libhfst.HfstTransducer(fsm2, libhfst.FOMA_TYPE)
    
if not (FSM.compare(FSM2)):
    raise RuntimeError(get_linenumber())

for type in (libhfst.TROPICAL_OPENFST_TYPE, libhfst.FOMA_TYPE):
    FSM.convert(type)
    Fsm = libhfst.HfstBasicTransducer(FSM)
    FSM2.convert(type)
    Fsm2 = libhfst.HfstBasicTransducer(FSM2)


# Print basic transducer
fsm = libhfst.HfstBasicTransducer()
for state in [0,1,2]:
    fsm.add_state(state)
fsm.add_transition(0,1,'foo','bar',1)
fsm.add_transition(0,1,'foo','BAR',2)
fsm.add_transition(1,2,'baz','baz',0)
fsm.set_final_weight(2,0.5)

# Different ways to print the transducer
for state in fsm.states():
    for arc in fsm.transitions(state):
        print('%i ' % (state), end='')
        print(arc)
    if fsm.is_final_state(state):
        print('%i %f' % (state, fsm.get_final_weight(state)) )

for state, arcs in enumerate(fsm):
    for arc in arcs:
        print('%i ' % (state), end='')
        print(arc)
    if fsm.is_final_state(state):
        print('%i %f' % (state, fsm.get_final_weight(state)) )

index=0
for state in fsm.states_and_transitions():
    for transition in state:
        print('%u\t%u\t%s\t%s\t%.2f' % (index, transition.get_target_state(), transition.get_input_symbol(), transition.get_output_symbol(), transition.get_weight()))
    if fsm.is_final_state(index):
        print('%s\t%.2f' % (index, fsm.get_final_weight(index)))
    index = index + 1

print(fsm)

tr = libhfst.HfstBasicTransducer(libhfst.regex('foo'))
tr.substitute({'foo':'bar'})
tr.substitute({('foo','foo'):('bar','bar')})
