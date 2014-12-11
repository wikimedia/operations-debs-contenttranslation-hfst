import libhfst

types = [libhfst.SFST_TYPE, libhfst.TROPICAL_OPENFST_TYPE, libhfst.FOMA_TYPE]

for type in types:

    if not libhfst.HfstTransducer.is_implementation_type_available(type):
        continue

    # Test the lexc parser
    print(" Testing...")

    # (1) A file in valid lexc format
    print(" valid file, parse... ")
    compiler = libhfst.LexcCompiler(type)
    compiler.parse("test_lexc.lexc")
    print("")
    parsed = compiler.compileLexical()
    assert(parsed != 0)
    tok = libhfst.HfstTokenizer()
    cat = libhfst.HfstTransducer("cat", tok, type)
    dog = libhfst.HfstTransducer("dog", tok, type)
    mouse = libhfst.HfstTransducer("mouse", tok, type)

    animals = libhfst.HfstTransducer(type)
    animals.disjunct(cat)
    animals.disjunct(dog)
    animals.disjunct(mouse)

    assert(animals.compare(libhfst.ptrvalue(parsed)))
    del(parsed)


    #try:
    #    print(" valid file, read_lexc... ")
    #    rlexc = libhfst.HfstTransducer.read_lexc("test_lexc.lexc", type)
    #    assert(animals.compare(rlexc))
    #except libhfst.FunctionNotImplementedException:
    #    assert(False)


    # (2) A file that does not follow lexc format
    compiler2 = libhfst.LexcCompiler(type)
    print(" invalid file, parse... ")
    compiler2.parse("test_lexc_fail.lexc")
    parsed = compiler2.compileLexical()
    assert(parsed == None)

    # (3) A file that does not exist
    compiler3 = libhfst.LexcCompiler(type)
    print(" missing file, parse... ")
    compiler3.parse("nonexistent.lexc")
    parsed = compiler3.compileLexical()
    assert(parsed == None)
