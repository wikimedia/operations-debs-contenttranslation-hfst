import hfst
from sys import argv
infile1=None
infile2=None
for arg in argv[1:]:
    if arg == '-1':
        infile1 = '<next>'
    elif arg == '-2':
        infile2 = '<next>'
    elif infile1 == '<next>':
        infile1 = arg
    elif infile2 == '<next>':
        infile2 = arg
    elif infile1 == None:
        infile1 = arg
    elif infile2 == None:
        infile2 = arg
    else:
        raise RuntimeError('Usage: hfst-compose-intersect.py [-1] INFILE1 [-2] INFILE2')

istr1 = hfst.HfstInputStream(infile1)
istr2 = hfst.HfstInputStream(infile2)
if (istr1.get_type() != istr2.get_type()):
    raise RuntimeError('Error: transducer types differ in ' + infile1 + ' and ' + infile2)

tr1 = istr1.read()
if not istr1.is_eof():
    raise RuntimeError('Error: ' + infile1 + ' must contain exactly one transducer')
istr1.close()

transducers = []
while(not istr2.is_eof()):
    transducers.append(istr2.read())
istr2.close()

tr1.compose_intersect(transducers, False)
ostr = hfst.HfstOutputStream(type=tr1.get_type())
ostr.write(tr1)
ostr.flush()
ostr.close()
