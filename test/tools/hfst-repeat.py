import hfst
from sys import argv

minimum=0
maximum='inf'
infile=None
for arg in argv[1:]:
    if arg == '-f' or arg == "--from":
        minimum='<next>'
    elif arg == '-t' or arg == "--to":
        maximum='<next>'
    elif minimum == '<next>':
        minimum = int(arg)
    elif maximum == '<next>':
        maximum = int(arg)
    else:
        infile = arg

istr=None
if infile != None:
    istr = hfst.HfstInputStream(infile)
else:
    istr = hfst.HfstInputStream()
ostr = hfst.HfstOutputStream(type=istr.get_type())

tr = istr.read()

if (maximum == 'inf'):
    tr.repeat_n_plus(minimum)
else:
    tr.repeat_n_to_k(minimum, maximum)

tr.write(ostr)
ostr.flush()
istr.close()
ostr.close()
