import sys
if len(sys.argv) > 2:
    raise RuntimeError('Usage: fst2strings.py [[PYTHONPATH]]')
if len(sys.argv) == 2:
    sys.path.insert(0, sys.argv[1])
import hfst

istr = hfst.HfstInputStream()
while(True):
    try:
        tr = istr.read()
        print((tr.extract_paths(output='text')).replace(hfst.EPSILON, ''))
    except hfst.exceptions.EndOfStreamException as e:
        break

