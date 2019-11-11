import hfst
import hfst_commandline

level=None
short_getopts='p:'
long_getopts=['project=']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-p' or opt[0] == '--project':
        level = opt[1]
        
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]
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
