import hfst, sys
import hfst_commandline

silent=False
harmonize=True
eliminate_flags=False
retval=0

short_getopts='sqHe'
long_getopts=['silent','quiet','do-not-harmonize','eliminate-flags']
errmsg='Usage: hfst-compare.py INFILE1 INFILE2'
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 2, errmsg)

#for arg in argv[1:]:
for opt in options[0]:
    if opt[0] == '-s' or opt[0] == '--silent' or opt[0] == '-q' or opt[0] == '--quiet':
        silent = True
    elif opt[0] == '-H' or opt[0] == '--do-not-harmonize':
        harmonize = False
    elif opt[0] == '-e' or opt[0] == '--eliminate-flags':
        eliminate_flags=True
    else:
        pass # unknown options were already checked in hfst_getopt

streams = hfst_commandline.get_two_hfst_input_streams(options)
istr1 = streams[0][0]
istr1_name = streams[0][1]
istr2 = streams[1][0]
istr2_name = streams[1][1]

if (istr1.get_type() != istr2.get_type()):
    raise RuntimeError('Error: transducer types differ in ' + istr1_name + ' and ' + istr2_name)

while((not istr1.is_eof()) and (not istr2.is_eof())):
    tr1 = istr1.read()
    tr2 = istr2.read()
    if eliminate_flags:
        tr1.eliminate_flags()
        tr2.eliminate_flags()
    if (tr1.compare(tr2, harmonize)):
        if not silent:
            print(tr1.get_name() + ' == ' + tr2.get_name())
    else:
        if not silent:
            print(tr1.get_name() + ' != ' + tr2.get_name())
        retval=1

istr1.close()
istr2.close()
sys.exit(retval)
