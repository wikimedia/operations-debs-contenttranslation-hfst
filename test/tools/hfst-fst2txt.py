import hfst
import hfst_commandline

print_weights=True
output_format="att"
#infile=None
#outfile=None

short_getopts = 'Df:i:o:'
long_getopts = ['--do-not-print-weights','format=','input=','output=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)
for opt in options[0]:
    if opt[0] == '-D' or opt[0] == '--do-not-print-weights':
        print_weights = False
    elif opt[0] == '-f' or opt[0] == '--format':
        output_format = opt[1]
    else:
        pass
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
ostr = hfst_commandline.get_one_text_output_stream(options)[0]

# raise RuntimeError('Error: hfst-fst2txt.py [-i] [IFILE] [-o] [OFILE] [-D]')

if output_format == 'att' or output_format == 'prolog':
    pass
elif output_format == 'dot' or output_format == 'pckimmo':
    raise RuntimeError('Error: hfst-fst2txt.py: format ' + output_format + ' not supported')
else:
    raise RuntimeError('Error: hfst-fst2txt.py: format ' + output_format + ' not recognized (must be one of {att, dot, prolog, pckimmo})')
    
#istr=None
#if (infile == None):
#    istr = hfst.HfstInputStream()
#else:
#    istr = hfst.HfstInputStream(infile)

#from sys import stdout
#ofile = None
#if (outfile == None):
#    ofile = stdout
#else:
#    ofile = open(outfile, 'w')
    
for tr in istr:
    if output_format == 'att':
        tr.write_att(ostr, print_weights)
    elif output_format == 'prolog':
        tr.write_prolog(ostr, print_weights)
    else:
        raise RuntimeError('')

from sys import stdout
if (ostr != stdout):
    ostr.close()
istr.close()
