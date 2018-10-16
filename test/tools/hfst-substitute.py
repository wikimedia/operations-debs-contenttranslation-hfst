import hfst

ofile = None
ifile = None
from_file = None
silent = False
from_label = None
to_label = None

from sys import argv
for arg in argv[1:]:
    if arg == '-s' or arg == '--silent':
        silent=True
    elif arg == '-o' or arg == '--output':
        ofile = '<next>'
    elif arg == '-i' or arg == '--input':
        ifile = '<next>'
    elif arg == '-F' or arg == '--from-file':
        from_file = '<next>'
    elif arg == '-f' or arg == '--from-label':
        from_label = '<next>'
    elif arg == '-t' or arg == '--to-label':
        to_label = '<next>'
    elif ofile == '<next>':
        ofile = arg
    elif ifile == '<next>':
        ifile = arg
    elif from_file == '<next>':
        from_file = arg
    elif from_label == '<next>':
        from_label = arg
    elif to_label == '<next>':
        to_label = arg
    elif ifile == None:
        ifile = arg
    elif ofile == None:
        ofile = arg
    else:
        raise RuntimeError('Error: hfst-substitute.py: unknown option: ' + arg)

istr = None
if ifile != None:
    istr = hfst.HfstInputStream(ifile)
else:
    istr = hfst.HfstInputStream()

ostr = None
if ofile != None:
    ostr = hfst.HfstOutputStream(filename=ofile, type=istr.get_type())
else:
    ostr = hfst.HfstOutputStream(type=istr.get_type())

def eps(s):
    if s == "@0@":
        return hfst.EPSILON
    else:
        return s

substitutions = {}
if from_file != None:
    f = open(from_file)
    for line in f:
        line = line.rstrip()
        repl = line.split('\t')
        if len(repl) != 2:
            raise RuntimeError('hfst-substitute.py: --from-file FILE: FILE must list substitutions line by line, input and output symbols separated by tabulators.')
        substitutions[repl[0]] = eps(repl[1])
    f.close()
elif from_label != None and to_label != None: # HFST 4.0: accept also one-length tuples; "@0@" should be accepted as epsilon, also in other functions
    f = tuple(from_label.split(':'))
    if len(f) == 1:
        f = eps(f[0])
    t = tuple(to_label.split(':'))
    if len(t) == 1:
        t = eps(t[0])
    substitutions[f] = t
else:
    raise RuntimeError('hfst-substitute.py: substitutions must be given with --from-file or --from-label and --to-label')

for tr in istr:
    tr.substitute(substitutions)
    ostr.write(tr)

istr.close()
ostr.close()
