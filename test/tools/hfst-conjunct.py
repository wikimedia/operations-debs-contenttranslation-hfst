import hfst
import hfst_commandline
harmonize=True

options = hfst_commandline.hfst_getopt('H1:2:',['--do-not-harmonize'],2)
for opt in options[0]:
    if opt[0] == '-H' or opt[0] == '--do-not-harmonize':
        harmonize=False
    else:
        pass # raise RuntimeError('Usage: hfst-compose.py INFILE1 INFILE2')

istreams = hfst_commandline.get_two_hfst_input_streams(options)
istr1 = istreams[0][0]
istr2 = istreams[1][0]

if (istr1.get_type() != istr2.get_type()):
    raise RuntimeError('Error: transducer types differ in ' + argv[1] + ' and ' + argv[2])
ostr = hfst.HfstOutputStream(type=istr1.get_type())

while((not istr1.is_eof()) and (not istr2.is_eof())):
    tr1 = istr1.read()
    tr2 = istr2.read()
    tr1.conjunct(tr2, harmonize)
    tr1.write(ostr)
    ostr.flush()

istr1.close()
istr2.close()
