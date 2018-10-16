import hfst, sys

explicit_ifile1=None
explicit_ifile2=None
arg1=None
arg2=None
silent=False
harmonize=True
eliminate_flags=False
retval=0

from sys import argv
if len(argv) < 2 or len(argv) > 5:
    raise RuntimeError('Usage: hfst-compare.py INFILE1 INFILE2')
for arg in argv[1:]:
    if arg == '-s' or arg == '--silent' or arg == '-q' or arg == '--quiet':
        silent = True
    elif arg == '-H' or arg == '--do-not-harmonize':
        harmonize = False
    elif arg == '-e' or arg == '--eliminate-flags':
        eliminate_flags=True
    elif arg == '-1':
        explicit_ifile1 = '<next>'
    elif arg == '-2':
        explicit_ifile2 = '<next>'
    elif explicit_ifile1 == '<next>':
        explicit_ifile1 = arg
    elif explicit_ifile2 == '<next>':
        explicit_ifile2 = arg
    elif arg1 == None:
        arg1 = arg
    elif arg2 == None:
        arg2 = arg
    else:
        raise RuntimeError('Usage: hfst-compare.py INFILE1 INFILE2')

istr1 = None
istr2 = None

def get_input_stream(filename):
    if filename == '-':
        return hfst.HfstInputStream()
    elif filename != None:
        return hfst.HfstInputStream(filename)
    else:
        return None

istr1 = get_input_stream(explicit_ifile1)
istr2 = get_input_stream(explicit_ifile2)

if istr1 != None and istr2 != None:
    pass
elif istr1 == None and istr2 != None:
    if arg1 == None:
        arg1 = '-'
    istr1 = get_input_stream(arg1)
elif istr1 != None and istr2 == None:
    if arg1 == None:
        arg1 = '-'
    istr2 = get_input_stream(arg1)
else:
    if arg2 == None:
        istr1 = get_input_stream('-')
        istr2 = get_input_stream(arg1)
    else:
        istr1 = get_input_stream(arg1)
        istr2 = get_input_stream(arg2)

if (istr1.get_type() != istr2.get_type()):
    raise RuntimeError('Error: transducer types differ in ' + argv[1] + ' and ' + argv[2])

while((not istr1.is_eof()) and (not istr2.is_eof())):
    tr1 = istr1.read()
    tr2 = istr2.read()
    if eliminate_flags:
        tr1.eliminate_flags()
        tr2.eliminate_flags()
    if (tr1.compare(tr2, harmonize)):
        if not silent:
            print(tr1.get_name() + ' == ' + tr2.get_name())
    else:
        if not silent:
            print(tr1.get_name() + ' != ' + tr2.get_name())
        retval=1

istr1.close()
istr2.close()
sys.exit(retval)
