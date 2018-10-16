import hfst
from sys import argv
outputfilename=None
impl=hfst.ImplementationType.TROPICAL_OPENFST_TYPE
skip_next = False
for i in range(1, len(argv)):
    if skip_next:
        skip_next = False
        continue
    arg = argv[i]
    if arg == '-f':
        skip_next= True
        val = argv[i+1]
        if val == 'sfst':
            impl = hfst.ImplementationType.SFST_TYPE
        elif val == 'openfst-tropical':
            impl = hfst.ImplementationType.TROPICAL_OPENFST_TYPE
        elif val == 'foma':
            impl = hfst.ImplementationType.FOMA_TYPE
        else:
            raise RuntimeError('type not recognized: ' + val)
    elif arg == '-o':
        skip_next= True
        outputfilename = argv[i+1]
    elif arg == '-w':
        impl = hfst.ImplementationType.TROPICAL_OPENFST_TYPE
    else:
        raise RuntimeError('argument not recognized: ' + arg)

istr = hfst.HfstInputStream()
ostr = None
if outputfilename != None:
    ostr = hfst.HfstOutputStream(filename=outputfilename, type=impl)
else:
    ostr = hfst.HfstOutputStream(type=impl)

for tr in istr:
    tr.convert(impl)
    ostr.write(tr)

istr.close()
ostr.close()
