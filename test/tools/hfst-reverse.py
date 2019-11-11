import hfst
import hfst_commandline

short_getopts=''
long_getopts=[]
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)
istr = hfst_commandline.get_one_hfst_input_stream(options)
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr.reverse()
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
