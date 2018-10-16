import hfst
from sys import argv
if len(argv) != 2:
    raise RuntimeError('Usage: hfst-determinize.py INFILE')

istr = hfst.HfstInputStream(argv[1])
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr.determinize()
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
