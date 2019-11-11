import hfst
import hfst_commandline
short_getopts=''
long_getopts=[]
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

#    raise RuntimeError('Usage: hfst-remove-epilons.py INFILE')

istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr.remove_epsilons()
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
