import hfst
defs=None
from sys import argv
if len(argv) < 2:
    from sys import stdin
    exp = str(stdin.read())
    defs = hfst.compile_pmatch_expression(exp)
elif len(argv) == 2:
    defs = hfst.compile_pmatch_file(argv[1])    
else:
    raise RuntimeError('error: hfst-pmatch2fst.py [INFILE]')

ostr = hfst.HfstOutputStream(type=hfst.ImplementationType.HFST_OLW_TYPE)
for tr in defs:
    ostr.write(tr)
ostr.close()
