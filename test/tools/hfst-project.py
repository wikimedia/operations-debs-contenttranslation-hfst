import hfst
from sys import argv
if len(argv) != 4:
    raise RuntimeError('Usage: hfst-project.py INFILE -p [input|output]')

ifile=None
level=None
for arg in argv[1:]:
    if arg == '-p' or arg == '--project':
        level='next'
    elif level == 'next':
        level = arg
    else:
        ifile = arg
        
istr = hfst.HfstInputStream(ifile)
ostr = hfst.HfstOutputStream(type=istr.get_type())

while(not istr.is_eof()):
    tr = istr.read()
    if (level == 'input'):
        tr.input_project()
    elif (level == 'output'):
        tr.output_project()
    else:
        raise RuntimeError('hfst-project: projection level must be defined with -p [input|output]')
    tr.write(ostr)
    ostr.flush()
      
istr.close()
ostr.close()
