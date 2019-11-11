import hfst
import hfst_commandline
options = hfst_commandline.hfst_getopt('',[],1)

if len(options[1]) == 0:
    raise RuntimeError('Usage: hfst-invert.py INFILE')

istr = hfst.HfstInputStream(options[1][0])
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr.invert()
    tr.write(ostr)
    ostr.flush()

istr.close()
ostr.close()
