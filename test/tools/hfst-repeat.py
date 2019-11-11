import hfst
import hfst_commandline
minimum=0
maximum='inf'

short_getopts='f:t:'
long_getopts=['from=', 'to=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-f' or opt[0] == '--from':
        minimum = int(opt[1])
    elif opt[0] == '-t' or opt[0] == '--to':
        maximum = int(opt[1])
    else:
        pass

istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
ostr = hfst.HfstOutputStream(type=istr.get_type())

tr = istr.read()

if (maximum == 'inf'):
    tr.repeat_n_plus(minimum)
else:
    tr.repeat_n_to_k(minimum, maximum)

tr.write(ostr)
ostr.flush()
istr.close()
ostr.close()
