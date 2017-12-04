import sys
if len(sys.argv) < 3 or len(sys.argv) > 6:
    raise RuntimeError('Usage: compare.py [input1] [input2] [[PYTHONPATH]] [[--eliminate-flags]] [[-q]]')

eliminate_flags=False
for arg in sys.argv[3:]:
    if arg == '-q':
        pass
    elif arg == '--eliminate-flags':
        eliminate_flags=True
    else:
        sys.path.insert(0, arg)

import hfst

istr1 = hfst.HfstInputStream(sys.argv[1])
istr2 = hfst.HfstInputStream(sys.argv[2])

retval=0
while(True):
    try:
        tr1 = istr1.read()
        tr2 = istr2.read()
        if (eliminate_flags):
            tr1.eliminate_flags()
            tr2.eliminate_flags()
        if not (tr1.compare(tr2)):
            retval=1
            break
    except hfst.exceptions.EndOfStreamException as e:
        break

istr1.close()
istr2.close()
sys.exit(retval)
