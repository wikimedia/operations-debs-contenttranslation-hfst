import sys
if len(sys.argv) < 2 or len(sys.argv) > 3:
    raise RuntimeError('Usage: prolog2fst.py [sfst|openfst|foma] [[PYTHONPATH]]')
if len(sys.argv) == 3:
    sys.path.insert(0, sys.argv[2])
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

ostr = hfst.HfstOutputStream()

# Works for python 3 only
input_stream=None
if sys.version_info[0] > 2:
	import io
	input_stream = io.TextIOWrapper(sys.stdin.buffer, encoding='utf-8')
else:
	raise RuntimeError('Cannot read utf-8 input from standard input with python version 2.')

while(True):
    try:
        tr = hfst.read_prolog_transducer(input_stream)
        ostr.write(tr)
        ostr.flush()
    except hfst.exceptions.EndOfStreamException as e:
        break

