from __future__ import print_function

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
        paths = tr.extract_paths(output='raw')
        for path in paths:
            for tokenpair in path[1]:
                if tokenpair[0] == tokenpair[1]:
                    print(tokenpair[0], end=' ')
                else:
                    print(tokenpair[0]+':'+tokenpair[1], end=' ')
    except hfst.exceptions.EndOfStreamException as e:
        break

