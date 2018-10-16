import hfst
from sys import argv
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
    else:
        raise RuntimeError('argument not recognized: ' + arg)

hfst.set_default_fst_type(impl)
result = hfst.compile_sfst_file("")
result.convert(impl)
ostr = hfst.HfstOutputStream(type=hfst.get_default_fst_type())
ostr.write(result)
