from sys import argv
newline=False
if len(argv) != 3 and len(argv) != 2:
    raise RuntimeError('Usage: hfst-pmatch.py [--newline] INFILE')
for arg in argv[1:]:
    if arg == '--newline':
        newline=True
    else:
        infilename = arg
import hfst

transducers = []
istr = hfst.HfstInputStream(infilename)
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
