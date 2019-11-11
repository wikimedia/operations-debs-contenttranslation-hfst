import hfst
import hfst_commandline
ofile = None
ifile = None
from_file = None
silent = False
from_label = None
to_label = None

short_getopts = 'so:i:F:f:t:'
long_getopts = ['silent','output=','input=','from-file=','from-label=','to-label=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)
for opt in options [0]:
    if opt[0] == '-s' or opt[0] == '--silent':
        silent = True
    elif opt[0] == '-F' or opt[0] == '--from-file':
        from_file = opt[1]
    elif opt[0] == '-f' or opt[0] == '--from-label':
        from_label = opt[1]
    elif opt[0] == '-t' or opt[0] == '--to-label':
        to_label = opt[1]
    else:
        pass

istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
ostr = hfst_commandline.get_one_hfst_output_stream(options, istr.get_type())[0]

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
