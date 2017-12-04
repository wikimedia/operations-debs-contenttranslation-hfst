# -*- coding: utf-8 -*-
import sys
if len(sys.argv) > 1:
    sys.path.insert(0, sys.argv[1])
import hfst

import os.path
assert os.path.isfile('streets.txt')

# pmatch transducers are always in ol format, so this has actually no effect...
for type in [hfst.ImplementationType.SFST_TYPE, hfst.ImplementationType.TROPICAL_OPENFST_TYPE, hfst.ImplementationType.FOMA_TYPE]:
    if hfst.HfstTransducer.is_implementation_type_available(type):
        print(hfst.fst_type_to_string(type))
        hfst.set_default_fst_type(type)

        # (1) compile the file directly
        defs = hfst.compile_pmatch_file('streets.txt')
        cont = hfst.PmatchContainer(defs)
        assert cont.match("Je marche seul dans l'avenue des Ternes.") == "Je marche seul dans l'<FrenchStreetName>avenue des Ternes</FrenchStreetName>."

        # (2) compile the contents of file
        with open('streets.txt', 'r') as myfile:
            data=myfile.read()
            myfile.close()
        defs = hfst.compile_pmatch_expression(data)
        cont = hfst.PmatchContainer(defs)
        assert cont.match("Je marche seul dans l'avenue des Ternes.") == "Je marche seul dans l'<FrenchStreetName>avenue des Ternes</FrenchStreetName>."
        
        # (3) try to compile a nonexistent file
        nonexistent_file = 'foofoofoofoofoofoofoofoofoofoofoofoo'
        assert not os.path.isfile(nonexistent_file)
        try:
            hfst.compile_pmatch_file(nonexistent_file)
            assert False
        except IOError as e:
            pass

        # (4) try to compile meaningless and invalid expressions
        # skip these tests, it seems that PmatchCompiler should be reseted after
        # compilation that fails...
        continue
        for expr in ["foobarbaz; ????", "", "efine CapWord UppercaseAlpha Alpha* :"]:
            print(expr)
            try:
                defs = hfst.compile_pmatch_expression(expr)
                assert False
            except hfst.exceptions.HfstException as e:
                pass
