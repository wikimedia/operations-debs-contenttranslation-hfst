import hfst
from sys import argv
if len(argv) != 3:
    raise RuntimeError('Usage: hfst-shuffle.py INFILE1 INFILE2')

istr1 = hfst.HfstInputStream(argv[1])
istr2 = hfst.HfstInputStream(argv[2])
if (istr1.get_type() != istr2.get_type()):
    raise RuntimeError('Error: transducer types differ in ' + argv[1] + ' and ' + argv[2])
ostr = hfst.HfstOutputStream(type=istr1.get_type())

while((not istr1.is_eof()) and (not istr2.is_eof())):
    tr1 = istr1.read()
    tr2 = istr2.read()
    tr1.shuffle(tr2)
    tr1.write(ostr)
    ostr.flush()

istr1.close()
istr2.close()
