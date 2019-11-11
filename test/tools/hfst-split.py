import hfst
import hfst_commandline

options = hfst_commandline.hfst_getopt('', [], 0)
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
n=1
for tr in istr:
    ostr = hfst.HfstOutputStream(filename=str(n) + ".hfst", type=tr.get_type())
    ostr.write(tr)
    ostr.flush()
    ostr.close()
    n = n + 1
istr.close()
