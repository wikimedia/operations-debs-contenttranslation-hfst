import hfst
import hfst_commandline

#treat_warnings_as_errors=False
output_format=hfst.ImplementationType.TROPICAL_OPENFST_TYPE
WithFlags=False

shortopts = 'f:Fi:o:'
longopts = ['format=', 'withFlags', 'Werror', 'input=', 'output=']
options = hfst_commandline.hfst_getopt(shortopts, longopts, 1)

for opt in options[0]:
#    if opt[0] == '--Werror':
#        treat_warnings_as_errors=True
    if opt[0] == '-F' or opt[0] == '--withFlags':
        WithFlags=True
    elif opt[0] == '-f' or opt[0] == '--format':
        output_format = hfst_commandline.get_implementation_type(opt[1])
    else:
        pass

istr = hfst_commandline.get_one_input_text_stream(options)
ostr = hfst_commandline.get_one_output_hfst_stream(options, output_format)
istr[0].close()
ostr[0].close()

hfst.set_default_fst_type(output_format)
tr = hfst.compile_lexc_file(istr[1], with_flags=WithFlags)
tr.write_to_file(ostr[1])
