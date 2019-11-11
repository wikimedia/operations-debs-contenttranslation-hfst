import hfst
import hfst_commandline
nlast=None
from_nth=None
infile=None

short_getopts='n:'
long_getopts=['n-last=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-n' or opt[0] == '--n-last':
        nlast = int(opt[1])
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
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
ostr.flush()
ostr.close()
