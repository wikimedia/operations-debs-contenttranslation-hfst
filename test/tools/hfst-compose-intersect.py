import hfst
import hfst_commandline

options = hfst_commandline.hfst_getopt('1:2:',[],2)
istreams = hfst_commandline.get_two_hfst_input_streams(options)
istr1 = istreams[0][0]
istr2 = istreams[1][0]

if (istr1.get_type() != istr2.get_type()):
    raise RuntimeError('Error: transducer types differ in ' + istreams[0][1] + ' and ' + istreams[1][1])

tr1 = istr1.read()
if not istr1.is_eof():
    raise RuntimeError('Error: ' + infile1 + ' must contain exactly one transducer')
istr1.close()

transducers = []
while(not istr2.is_eof()):
    transducers.append(istr2.read())
istr2.close()

tr1.compose_intersect(transducers, False)
ostr = hfst.HfstOutputStream(type=tr1.get_type())
ostr.write(tr1)
ostr.flush()
ostr.close()
