import hfst
import hfst_commandline

force=False
short_getopts='fS'
long_getopts=['force','safe']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-f' or opt[0] == '--force':
        force=True
    elif opt[0] == '-S' or opt[0] == '--safe':
        force=False
    else:
        pass

#    raise RuntimeError('Usage: hfst-prune-alphabet.py [-f|--force] [-S|--safe]')    

istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    tr = hfst.HfstBasicTransducer(tr)
    tr.prune_alphabet(force)
    tr = hfst.HfstTransducer(tr, istr.get_type())
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
