import hfst
nfirst=None
infile=None
from sys import argv
for arg in argv[1:]:
    if arg == '-n' or arg == '--n-first':
        nfirst='<next>'
    elif nfirst == '<next>':
        nfirst = int(arg)
    else:
        infile = arg
        
istr=None
if infile != None:
    istr = hfst.HfstInputStream(infile)
else:
    istr = hfst.HfstInputStream()
ostr = hfst.HfstOutputStream(type=istr.get_type())

if nfirst > 0:
    n=0
    for tr in istr:
        if n >= nfirst:
            break
        ostr.write(tr)
        n = n + 1
elif nfirst < 0:
    transducers=[]
    for tr in istr:
        transducers.append(tr)
    n=0
    for tr in transducers:
        if n < (len(transducers) + nfirst):
            ostr.write(tr)
        n = n + 1
else:
    pass

istr.close()
ostr.close()
