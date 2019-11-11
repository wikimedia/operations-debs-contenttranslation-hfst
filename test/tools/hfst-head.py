import hfst
import hfst_commandline
nfirst=None
infile=None

short_getopts='n:'
long_getopts=['n-first=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-n' or opt[0] == '--n-first':
        nfirst = int(opt[1])
    else:
        pass
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
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
