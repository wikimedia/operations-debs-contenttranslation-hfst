import hfst
nlast=None
from_nth=None
infile=None
from sys import argv
for arg in argv[1:]:
    if arg == '-n' or arg == '--n-last':
        nlast='<next>'
    elif nlast == '<next>':
        if arg[0] == '+':
            from_nth = int(arg[1:])
            nlast = None
        else:
            nlast = int(arg)
    else:
        infile = arg
        
istr=None
if infile != None:
    istr = hfst.HfstInputStream(infile)
else:
    istr = hfst.HfstInputStream()
ostr = hfst.HfstOutputStream(type=istr.get_type())

if from_nth != None:
    n=1
    for tr in istr:
        if n >= from_nth:            
            ostr.write(tr)
        n = n + 1
elif nlast != None:
    transducers=[]
    for tr in istr:
        transducers.append(tr)
    i=0
    for tr in transducers:
        if i >= len(transducers) - nlast:
            ostr.write(tr)
        i = i + 1
else:
    pass

istr.close()
ostr.close()
