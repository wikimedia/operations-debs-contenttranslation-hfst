import libhfst

t = libhfst.HfstBasicTransducer()
s1 = t.add_state()
s2 = t.add_state()
s3 = t.add_state()
s4 = t.add_state()
s5 = t.add_state()
s6 = t.add_state()
t.set_final_weight(s6, 0)
  
fd1 = "@U.FEATURE.FOO@"
fd2 = "@U.FEATURE.BAR@"
  
t.add_transition(0, libhfst.HfstBasicTransition(s1, fd1, fd1, 0))
t.add_transition(0, libhfst.HfstBasicTransition(s2, "a", "a", 0))
t.add_transition(s1, libhfst.HfstBasicTransition(s3, "b", "b", 0))
t.add_transition(s2, libhfst.HfstBasicTransition(s3, fd2, fd2, 0))
t.add_transition(s3, libhfst.HfstBasicTransition(s4, "c", "c", 0))
t.add_transition(s3, libhfst.HfstBasicTransition(s5, "d", "d", 0))
t.add_transition(s4, libhfst.HfstBasicTransition(s6, fd2, fd2, 0))
t.add_transition(s5, libhfst.HfstBasicTransition(s6, fd1, fd1, 0))


types = [libhfst.SFST_TYPE, libhfst.TROPICAL_OPENFST_TYPE, libhfst.FOMA_TYPE]

for type in types:

    if not libhfst.HfstTransducer.is_implementation_type_available(type):
        continue


    print("Identitites with flags")

    id = libhfst.HfstTransducer("@_IDENTITY_SYMBOL_@", type)
    id.repeat_star()
    ab_flag = libhfst.HfstTransducer("a", "b", type)
    flag = libhfst.HfstTransducer("@U.F.A@", type)
    ab_flag.disjunct(flag)

    ab_flag.concatenate(id)
    id.minimize()

    a_tr = libhfst.HfstTransducer("a", type)
    b_tr = libhfst.HfstTransducer("b", type)
    abid = libhfst.HfstTransducer("@_IDENTITY_SYMBOL_@", type)
    abid.disjunct(a_tr)
    abid.disjunct(b_tr)
    abid.repeat_star()
    abid.minimize()

    assert(abid.compare(id))


    print("Unification flags")
      
    tr = libhfst.HfstTransducer(t, type)
    results = libhfst.extract_paths_fd(tr)
    
    assert(len(results) == 2)    
    print(results)

    #assert(result_strings.find(StringPair("ac","ac")) 
    #       != result_strings.end())
    #assert(result_strings.find(StringPair("bd","bd")) 
    #       != result_strings.end())
      


