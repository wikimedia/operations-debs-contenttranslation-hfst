import hfst
from sys import argv

istr = hfst.HfstInputStream(argv[1])
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr.reverse()
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
