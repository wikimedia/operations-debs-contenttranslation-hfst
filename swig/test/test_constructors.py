#
#   Test file for HfstTransducer constructors, destructor, operator=
#   and member functions set_name, get_name and get_type.
#

import libhfst

types = [libhfst.SFST_TYPE, libhfst.TROPICAL_OPENFST_TYPE, libhfst.FOMA_TYPE]

for type in types:

    if not libhfst.HfstTransducer.is_implementation_type_available(type):
        continue

    # The empty transducer
    print("The empty transducer")
    empty = libhfst.HfstTransducer(type)

    # The epsilon transducer
    print("The epsilon transducer")
    epsilon = libhfst.HfstTransducer("@_EPSILON_SYMBOL_@", type)
    
    # One-transition transducer
    print("One-transition transducer")
    foo = libhfst.HfstTransducer("foo", type)
    foobar = libhfst.HfstTransducer("foo", "bar", type)
    
    # The copy constructor
    print("The copy constructor")
    foobar_copy = libhfst.HfstTransducer(foobar)
    assert(foobar.compare(foobar_copy))
    
    # Conversion from HfstBasicTransducer
    print("Conversion from HfstBasicTransducer")
    basic = libhfst.HfstBasicTransducer()
    basic.add_state(1)
    basic.add_transition(0, libhfst.HfstBasicTransition(1, "foo", "bar", 0))
    basic.set_final_weight(1, 0)
    foobar_basic = libhfst.HfstTransducer(basic, type)
    assert(foobar.compare(foobar_basic))
    
    # By tokenizing
    print("Construction by tokenization")
    tok = libhfst.HfstTokenizer()
    tok.add_skip_symbol("baz")
    tok.add_multichar_symbol("foo")
    tok.add_multichar_symbol("bar")
    foo_tok = libhfst.HfstTransducer("bazfoobaz", tok, type)
    foobar_tok = libhfst.HfstTransducer("bazfoo", "barbaz", tok, type)
    assert(foo.compare(foo_tok))
    assert(foobar.compare(foobar_tok))
        
    # Function assign
    print("Function assign()")
    foobar2 = libhfst.HfstTransducer("baz", type)
    foobar.set_name("foobar")
    assert(foobar.get_name() == "foobar")
    foobar2.assign(foobar)
    assert(foobar2.get_name() == "foobar")
    assert(foobar.compare(foobar2))
    empty_ol = libhfst.HfstTransducer(libhfst.HFST_OL_TYPE)
    empty_olw = libhfst.HfstTransducer(libhfst.HFST_OLW_TYPE)
    # reserving props in copy constructor (bug: #3405831)
    t = libhfst.HfstTransducer("a", libhfst.TROPICAL_OPENFST_TYPE)
    t.convert(libhfst.HFST_OLW_TYPE)
    t.set_name("foo")
    s = libhfst.HfstTransducer(t)
    assert(s.get_name() == t.get_name())
    try:
        empty_ol = foobar2.convert(libhfst.HFST_OL_TYPE)
        empty_olw = foobar2.convert(libhfst.HFST_OLW_TYPE)
        assert(empty_ol.get_name() == "foobar")
        assert(empty_olw.get_name() == "foobar")
    except: # libhfst.FunctionNotImplementedException:
        assert(False)
    

