import hfst_commandline
import hfst

short_getopts='f:'
long_getopts=['format=',]

impl = hfst.ImplementationType.TROPICAL_OPENFST_TYPE
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts)
for opt in options[0]:
    if opt[0] == '-f' or opt[0] == '--format':
        impl = hfst_commandline.get_implementation_type(opt[1])

hfst.set_default_fst_type(impl)
result = hfst.compile_sfst_file("")
result.convert(hfst.get_default_fst_type())
ostr = hfst.HfstOutputStream(type=hfst.get_default_fst_type())
ostr.write(result)
