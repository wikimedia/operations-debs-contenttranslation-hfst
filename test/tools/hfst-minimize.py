import hfst
import hfst_commandline
options = hfst_commandline.hfst_getopt('',[],1)

istr = None
if len(options[1]) == 0:
    istr = hfst.HfstInputStream()
else:
    istr = hfst.HfstInputStream(options[1][0])

ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr.minimize()
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
