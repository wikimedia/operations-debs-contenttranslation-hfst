#
#   Test file for HfstBasicTransducer.
#   Some of the functions are already tested in other test files,
#   because some HfstTransducer functions are implemented only 
#   for HfstBasicTransducer.
#

import libhfst
import os
import sys

def alphabet_contains(alphabet, symbol):
    try:
        ind = alphabet.index(symbol)
    except ValueError:
        return False
    return True


print("HfstBasicTransducer construction")

# Create an HfstBasicTransducer [a:b c:d] with weight 3.0
t = libhfst.HfstBasicTransducer()
assert(not t.is_final_state(0))
s1 = t.add_state()
assert(s1 == 1)
t.add_transition(0, libhfst.HfstBasicTransition(s1, "a", "b", 1.2))
assert(not t.is_final_state(s1))
s2 = t.add_state()
assert(s2 == 2)
t.add_transition(s1, libhfst.HfstBasicTransition(s2, "c", "d", 0.8))
assert(not t.is_final_state(s2))
t.set_final_weight(s2, 1.0)
assert(t.is_final_state(s2) and t.get_final_weight(s2) == 1.0)

# Take a copy
tc = libhfst.HfstBasicTransducer(t);

print("HfstBasicTransducer exceptions")

# Asking the weight of a non-final state
for s in range(5):
    if s != s2:
        try:
            w = t.get_final_weight(s)
            assert(False)
        except: # libhfst.StateIsNotFinalException:
            assert(libhfst.hfst_get_exception() == "StateIsNotFinalException")
            pass

# Reading a file in non-valid AT&T format
ofile = open('test.att', 'wb')
ofile.write("0\n0\t1\ta\tb\n1\t2\tb\n2\n".encode('ascii'))
ofile.close()
ifile = libhfst.hfst_open('test.att', 'rb') # ERROR On MinGW, using libhfst.hfst_open fails..

try:
    foo = libhfst.HfstBasicTransducer(ifile)
    ifile.close()
    os.remove('test.att')
    assert(False)
except: # libhfst.NotValidAttFormatException:
    assert(libhfst.hfst_get_exception() == "NotValidAttFormatException")
    ifile.close()
    os.remove('test.att')

  
print("HfstBasicTransducer: symbol handling")

t.add_symbol_to_alphabet("foo")
assert(alphabet_contains(t.get_alphabet(), "foo"))
t.prune_alphabet()
alphabet = t.get_alphabet()
assert(len(alphabet) == 7)
for alpha in ['a', 'b', 'c', 'd']:
    assert(alphabet_contains(alphabet, alpha))
assert(not alphabet_contains(alphabet, "foo"))


  
print('HfstBasicTransducer: substitute')

tr = libhfst.HfstBasicTransducer()
tr.add_state()
tr.add_transition(0, libhfst.HfstBasicTransition(s1, "a", "b", 0))
tr.add_transition(0, libhfst.HfstBasicTransition(s1, "a", "b", 0))
tr.set_final_weight(1, 0)

sps = (("A","B"), ("C","D"))
tr.substitute(("a","b"), sps);


print("HfstBasicTransducer: EmptyStringException")
  
try:
    empty_symbol = libhfst.HfstBasicTransducer()
    empty_symbol.add_transition(0, libhfst.HfstBasicTransition(0, "", "", 0))
    assert(False)
except: # libhfst.EmptyStringException:
    assert(libhfst.hfst_get_exception() == "EmptyStringException")
    pass

  
print("HfstBasicTransducer: unknown and indentity symbols")

# In the xerox formalism used here, "?" means the unknown symbol
# and "?:?" the identity pair 
   
tr1 = libhfst.HfstBasicTransducer()
tr1.add_state(1)
tr1.set_final_weight(1, 0)
tr1.add_transition(0, libhfst.HfstBasicTransition(1, "@_UNKNOWN_SYMBOL_@", "foo", 0) )

# tr1 is now [ ?:foo ]
# print(tr1)

tr2 = libhfst.HfstBasicTransducer()
tr2.add_state(1)
tr2.add_state(2)
tr2.set_final_weight(2, 0)
tr2.add_transition(0, libhfst.HfstBasicTransition(1, "@_IDENTITY_SYMBOL_@", "@_IDENTITY_SYMBOL_@", 0) )
tr2.add_transition(1, libhfst.HfstBasicTransition(2, "bar", "bar", 0) )

# tr2 is now [ [ ?:? ] [ bar:bar ] ]
# print(tr2)

if libhfst.HfstTransducer.is_implementation_type_available(libhfst.SFST_TYPE):
    Tr1 = libhfst.HfstTransducer(tr1, libhfst.SFST_TYPE)
    Tr2 = libhfst.HfstTransducer(tr2, libhfst.SFST_TYPE)
    Tr1.disjunct(Tr2).minimize()
    # Tr1 is now [ [ ?:foo | bar:foo ]  |  [[ ?:? | foo:foo ] [ bar:bar ]]]
    # print(Tr1)

print("HfstBasicTransducer: iterating through");

for state in t.states():
    for transition in t.transitions(state):
        # print '%i\t%i\t%s\t%s\t%f' % (state, transition.get_target_state(), transition.get_input_symbol(), transition.get_output_symbol(), transition.get_weight())
        print("{0}\t{1}\t{2}\t{3}\t{4}".format(state, transition.get_target_state(), transition.get_input_symbol(), transition.get_output_symbol(), transition.get_weight()))
    if t.is_final_state(state):
        # print '%i\t%f' % (state, t.get_final_weight(state))
        print("{0}\t{1}".format(state, t.get_final_weight(state)))
