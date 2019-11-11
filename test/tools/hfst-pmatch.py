import hfst
import hfst_commandline

newline=False
shortopts = 'n'
longopts = ['newline']
options = hfst_commandline.hfst_getopt(shortopts, longopts, 1)
for opt in options[0]:
    if opt[0] == '-n' or opt[0] == '--newline':
        newline = True
    else:
        pass
#    raise RuntimeError('Usage: hfst-pmatch.py [--newline] INFILE')
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]

transducers = []
for tr in istr:
    transducers.append(tr)
istr.close()
cont = hfst.PmatchContainer(transducers)

from sys import stdin
if newline:
    for line in stdin:
        print(cont.match(line), end='')
else:
    exp=''
    for line in stdin:
        exp = exp + line
        if line == '':
            print(cont.match(line), end='')
    if line != '':
        print(cont.match(line), end='')
