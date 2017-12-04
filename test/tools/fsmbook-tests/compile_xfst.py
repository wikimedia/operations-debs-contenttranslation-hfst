import sys
if len(sys.argv) < 3 or len(sys.argv) > 4:
    raise RuntimeError('Usage: compile_xfst.py [sfst|openfst|foma] FILENAME [[PYTHONPATH]]')
if len(sys.argv) == 4:
    sys.path.insert(0, sys.argv[3])
import hfst

if (sys.argv[1] == 'sfst'):
    if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.SFST_TYPE)):
        hfst.set_default_fst_type(hfst.ImplementationType.SFST_TYPE)
    else:
        raise RuntimeError('Format sfst is not available.')
elif (sys.argv[1] == 'openfst' or sys.argv[1] == "openfst-tropical"):
    if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.TROPICAL_OPENFST_TYPE)):
        hfst.set_default_fst_type(hfst.ImplementationType.TROPICAL_OPENFST_TYPE)
    else:
        raise RuntimeError('Format openfst is not available.')
elif (sys.argv[1] == 'foma'):
    if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.FOMA_TYPE)):
        hfst.set_default_fst_type(hfst.ImplementationType.FOMA_TYPE)
    else:
        raise RuntimeError('Format foma is not available.')
else:
    raise RuntimeError('Transducer format "' + sys.argv[1] + '" not recognized.')
    
if hfst.compile_xfst_file(sys.argv[2]) != 0 :
    raise RuntimeError('Compiling file "' + sys.argv[2] + '" failed.')
