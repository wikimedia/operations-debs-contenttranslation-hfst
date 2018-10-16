import hfst

ofile = None
ifile = None
treat_warnings_as_errors=False
output_format=hfst.ImplementationType.TROPICAL_OPENFST_TYPE
WithFlags=False

from sys import argv
for arg in argv[1:]:
    if arg == '--Werror':
        treat_warnings_as_errors=True
    elif arg == '-F' or arg == '--withFlags':
        WithFlags=True
    elif arg == '-o' or arg == '--output':
        ofile = '<next>'
    elif arg == '-i' or arg == '--input':
        ifile = '<next>'
    elif arg == '-f' or arg == '--format':
        output_format = '<next>'
    elif ofile == '<next>':
        ofile = arg
    elif ifile == '<next>':
        ifile = arg
    elif output_format == '<next>':
        if arg == 'openfst-tropical' or arg == 'openfst':
            output_format = hfst.ImplementationType.TROPICAL_OPENFST_TYPE
        elif arg == 'foma':
            output_format = hfst.ImplementationType.FOMA_TYPE
        elif arg == 'sfst':
            output_format = hfst.ImplementationType.SFST_TYPE
        else:
            raise RuntimeError('Error: hfst-lexc.py: format ' + arg + ' not recognized.')
        hfst.set_default_fst_type(output_format)
    elif ifile == None:
        ifile = arg
    elif ofile == None:
        ofile = arg
    else:
        raise RuntimeError('Error: hfst-lexc.py: unknown option: ' + arg)

tr = hfst.compile_lexc_file(ifile, with_flags=WithFlags)
tr.write_to_file(ofile)
