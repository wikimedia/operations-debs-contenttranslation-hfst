import hfst
print_weights=True
output_format="att"
infile=None
outfile=None
from sys import argv
for arg in argv[1:]:
    if arg == '-D' or arg == '--do-not-print-weights':
        print_weights=False
    elif arg == '-f' or arg == '--format':
        output_format = '<next>'
    elif arg == '-i' or arg == '--input':
        infile = '<next>'
    elif arg == '-o' or arg == '--output':
        outfile = '<next>'
    elif output_format == '<next>':
        output_format = arg
    elif infile == '<next>':
        infile = arg
    elif outfile == '<next>':
        outfile = arg
    elif infile == None:
        infile = arg
    elif outfile == None:
        outfile = arg
    else:
        raise RuntimeError('Error: hfst-fst2txt.py [-i] [IFILE] [-o] [OFILE] [-D]')

if output_format == 'att' or output_format == 'prolog':
    pass
elif output_format == 'dot' or output_format == 'pckimmo':
    raise RuntimeError('Error: hfst-fst2txt.py: format ' + output_format + ' not supported')
else:
    raise RuntimeError('Error: hfst-fst2txt.py: format ' + output_format + ' not recognized (must be one of {att, dot, prolog, pckimmo})')
    
istr=None
if (infile == None):
    istr = hfst.HfstInputStream()
else:
    istr = hfst.HfstInputStream(infile)

from sys import stdout
ofile = None
if (outfile == None):
    ofile = stdout
else:
    ofile = open(outfile, 'w')
    
for tr in istr:
    if output_format == 'att':
        tr.write_att(ofile, print_weights)
    elif output_format == 'prolog':
        tr.write_prolog(ofile, print_weights)
    else:
        raise RuntimeError('')

if (outfile != None):
    ofile.close()

