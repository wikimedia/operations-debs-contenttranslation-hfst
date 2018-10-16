import hfst
from sys import argv

istr = None
if len(argv) == 2:
    istr = hfst.HfstInputStream(argv[1])
else:
    istr = hfst.HfstInputStream()

ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr.minimize()
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
