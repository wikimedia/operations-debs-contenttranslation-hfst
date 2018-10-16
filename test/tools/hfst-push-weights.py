import hfst
from sys import argv
if len(argv) != 4:
    raise RuntimeError('Usage: hfst-push-weights.py INFILE -p [input|output]')

ifile=None
direction=None
for arg in argv[1:]:
    if arg == '-p' or arg == '--push':
        direction='<next>'
    elif direction == '<next>':
        if arg == 'start' or arg == 'initial' or arg == 'begin':
            direction = 'start'
        elif arg == 'end' or arg == 'final':
            direction = 'end'
        else:
            raise RuntimeError('hfst-push-weights: push direction must be one of the following [[start|initial|begin]|[end|final]]')
    else:
        ifile = arg

if direction == None or direction == '<next>' or ifile == None:
    raise RuntimeError('Usage: hfst-push-weights.py INFILE -p [input|output]')
        
istr = hfst.HfstInputStream(ifile)
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
