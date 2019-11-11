import hfst
import hfst_commandline

direction=None
short_getopts='p:'
long_getopts=['push=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-p' or opt[0] == '--push':
        if opt[1] == 'start' or opt[1] == 'initial' or opt[1] == 'begin':
            direction = 'start'
        elif opt[1] == 'end' or opt[1] == 'final':
            direction = 'end'
        else:
            raise RuntimeError('hfst-push-weights: push direction must be one of the following [[start|initial|begin]|[end|final]]')

if direction == None:
    raise RuntimeError('Usage: hfst-push-weights.py INFILE -p [input|output]')
        
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    if (direction == 'start'):
        tr.push_weights_to_start()
    elif (direction == 'end'):
        tr.push_weights_to_end()
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
