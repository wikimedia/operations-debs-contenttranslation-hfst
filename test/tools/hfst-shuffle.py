import hfst
import hfst_commandline

short_getopts = 'i:o:'
long_getopts = ['input=','output=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 2)
istreams = hfst_commandline.get_two_hfst_input_streams(options)
istr1 = istreams[0][0]
istr2 = istreams[1][0]

# raise RuntimeError('Usage: hfst-shuffle.py INFILE1 INFILE2')
if (istr1.get_type() != istr2.get_type()):
    raise RuntimeError('Error: transducer types differ in ' + argv[1] + ' and ' + argv[2])
ostr = hfst_commandline.get_one_hfst_output_stream(options, istr1.get_type())[0]

while((not istr1.is_eof()) and (not istr2.is_eof())):
    tr1 = istr1.read()
    tr2 = istr2.read()
    tr1.shuffle(tr2)
    tr1.write(ostr)
    ostr.flush()

istr1.close()
istr2.close()
ostr.close()
