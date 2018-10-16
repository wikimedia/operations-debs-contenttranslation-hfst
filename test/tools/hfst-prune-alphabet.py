import hfst

force=False
from sys import argv
if len(argv) > 3:
    raise RuntimeError('Usage: hfst-prune-alphabet.py [-f|--force] [-S|--safe]')
for arg in argv[1:]:
    if arg == '-f' or arg == '--force':
        force=True
    elif arg == '-S' or arg == '--safe':
        force=False
    else:
        raise RuntimeError('unknown option: ' + arg)

istr = hfst.HfstInputStream()
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr = hfst.HfstBasicTransducer(tr)
    tr.prune_alphabet(force)
    tr = hfst.HfstTransducer(tr, istr.get_type())
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
