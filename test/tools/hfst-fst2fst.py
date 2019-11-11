import hfst_commandline
import hfst

short_getopts='f:o:w'
long_getopts=['format=','--output=']

impl = hfst.ImplementationType.TROPICAL_OPENFST_TYPE
outputfilename = None
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts)
for opt in options[0]:
    if opt[0] == '-f' or opt[0] == '--format':
        impl = hfst_commandline.get_implementation_type(opt[1])
    elif opt[0] == '-o' or opt[0] == '--output':
        outputfilename = opt[1]
    elif opt[0] == '-w':
        impl = hfst.ImplementationType.TROPICAL_OPENFST_TYPE
    else:
        pass

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
