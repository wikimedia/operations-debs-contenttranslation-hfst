import hfst
import hfst_commandline
options = hfst_commandline.hfst_getopt('', [], 1)
istr = hfst_commandline.get_one_text_input_stream(options)

defs=None
from sys import stdin
if istr[0] == stdin:
    exp = str(istr[0].read())
    defs = hfst.compile_pmatch_expression(exp)
else:
    istr[0].close()
    defs = hfst.compile_pmatch_file(options[1][0]) # todo istr[1]

#    raise RuntimeError('error: hfst-pmatch2fst.py [INFILE]')

ostr = hfst_commandline.get_one_hfst_output_stream(options, hfst.ImplementationType.HFST_OLW_TYPE)[0]
for tr in defs:
    ostr.write(tr)
ostr.close()
