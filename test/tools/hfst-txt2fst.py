import hfst
import hfst_commandline

epsilonstr=hfst.EPSILON
inputfilename=None
outputfilename=None
prolog=False
impl=hfst.ImplementationType.TROPICAL_OPENFST_TYPE

short_getopts = 'f:e:i:o:'
long_getopts = ['format=','epsilon=','input=','output=','prolog']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-f' or opt[0] == '--format':
        impl = hfst_commandline.get_implementation_type(opt[1])
    elif opt[0] == '-e' or opt[0] == '--epsilon':
        epsilonstr = opt[1]
    elif opt[0] == '--prolog':
        prolog = True
    else:
        skip
istr = hfst_commandline.get_one_text_input_stream(options)[0]
ostr = hfst_commandline.get_one_hfst_output_stream(options, impl)[0]

reader = None
if prolog:
    reader = hfst.PrologReader(istr)
else:
    reader = hfst.AttReader(istr, epsilonstr)

for tr in reader:
    TR = hfst.HfstTransducer(tr) # TODO: why doesn't (tr, impl) work?
    TR.convert(impl)
    ostr.write(TR)
    ostr.flush()

from sys import stdin
if istr != stdin:
    istr.close()
ostr.close()
