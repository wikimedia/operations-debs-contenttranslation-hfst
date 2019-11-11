from sys import argv, stdin, stdout
from hfst import ImplementationType, HfstInputStream, HfstOutputStream

# check if option opt is listed in short_getopts or long_getopts
# '-' chars are stripped from the beginning of opt before comparing
# ':' chars in short_getopts and '=' chars in long_getopts are ignored
def _check_option(opt, short_getopts, long_getopts, errmsg='TODO'):
    opt_ = opt.lstrip('-')
    if (len(opt_) == 1 and opt_ in short_getopts):
        return
    for longopt in long_getopts:
        if opt_ in longopt:
            return
    raise RuntimeError('argument not recognized: ' + opt)

def get_implementation_type(val):
    if val == 'sfst':
        return ImplementationType.SFST_TYPE
    elif val == 'openfst-tropical':
        return ImplementationType.TROPICAL_OPENFST_TYPE
    elif val == 'foma':
        return ImplementationType.FOMA_TYPE
    else:
        raise RuntimeError('type not recognized: ' + val)

# check command line parameters:
# - that any optional arguments are allowed (given as --foo FOO or --foo=FOO)
# - that parameters are listed in short_getopts or long_getopts
# - that number of free parameters is not bigger than free_params
def hfst_getopt(short_getopts, long_getopts, free_params=0, errmsg='TODO'):
    import getopt
    global argv
    options = getopt.gnu_getopt(argv[1:], short_getopts, long_getopts)
    for opt in options[0]:
        _check_option(opt[0], short_getopts, long_getopts, errmsg)
    if len(options) == 2:
        if len(options[1]) > free_params:
            raise RuntimeError('too many free parameters given (' + str(len(options[1])) + '), maximum is ' + str(free_params))
    return options

def _get_input_stream(filename, stream_type):
    if stream_type != 'hfst' and stream_type != 'text':
        raise RuntimeError('stream_type ' + stream_type + 'not recognized')
    if filename == '-':
        if stream_type == 'hfst':
            return HfstInputStream()
        else:
            return stdin
    elif filename != None:
        if stream_type == 'hfst':
            return HfstInputStream(filename)
        else:
            return open(filename, 'r') # TODO: encoding?
    else:
        return None
    
def _get_output_stream(filename, stream_type, impl=None):
    if stream_type != 'hfst' and stream_type != 'text':
        raise RuntimeError('stream_type ' + stream_type + 'not recognized')
    if filename == '-':
        if stream_type == 'hfst':
            return HfstOutputStream(type=impl)
        else:
            return stdout
    elif filename != None:
        if stream_type == 'hfst':
            return HfstOutputStream(filename, type=impl)
        else:
            return open(filename, 'w') # TODO: encoding?
    else:
        return None

def _get_one_output_stream(options, stream_type, impl=None):
    explicit_file=None
    stream=None
    name='TODO'
    # 1) given with -o or --output
    for opt in options[0]:
        if opt[0] == '-o' or opt[0] == '--output':
            explicit_file = opt[1]
            stream = _get_output_stream(explicit_file, stream_type, impl)
            return (stream, name)
    # 2) not given, defaults to standard output
    stream = _get_output_stream('-', stream_type, impl)
    return (stream, name)

# any number of free arguments may be given but none will be
# interpreted as OFILE
def get_one_hfst_output_stream(options, impl):
    return _get_one_output_stream(options, 'hfst', impl)

def get_one_text_output_stream(options):
    return _get_one_output_stream(options, 'text')

def _get_one_input_stream(options, stream_type):
    explicit_file=None
    arg=None
    stream=None
    name='TODO'
    # 1) given with -i or --input (overrides free argument)
    for opt in options[0]:
        if opt[0] == '-i' or opt[0] == '--input':
            explicit_file = opt[1]
            stream = _get_input_stream(explicit_file, stream_type)
            return (stream, name)
    if len(options) == 2:
        # 2) given as free argument
        if len(options[1]) >= 1:
            arg = options[1][0]
            stream = _get_input_stream(arg, stream_type)
            return (stream, name)
    # 3) not given, defaults to standard input
    stream = _get_input_stream('-', stream_type)
    return (stream, name)

def get_one_text_input_stream(options):
    return _get_one_input_stream(options, 'text')

# any number of free arguments may be given but the first one
# will be interpreted as IFILE (unless -i or --input is used)
def get_one_hfst_input_stream(options):
    return _get_one_input_stream(options, 'hfst')

# no more than two free arguments may be given and they are always
# interpreted as IFILE1 and IFILE2 (unless -1, -2, --input1 or --input2 are used)
def get_two_hfst_input_streams(options):
    explicit_ifile1=None
    explicit_ifile2=None
    arg1=None
    arg2=None
    name1='TODO'
    name2='TODO'
    for opt in options[0]:
        if opt[0] == '-1' or opt[0] == '--input1':
            explicit_ifile1 = opt[1] 
        elif opt[0] == '-2' or opt[0] == '--input2':
            explicit_ifile2 = opt[1]
        else:
            pass
    # free arguments were given
    if len(options) == 2:
        # at least one
        if len(options[1]) >= 1:
            arg1 = options[1][0]
            # and a second one
        if len(options[1]) == 2:
            arg2 = options[1][1]
    istr1 = None
    istr2 = None
    istr1 = _get_input_stream(explicit_ifile1, 'hfst')
    istr2 = _get_input_stream(explicit_ifile2, 'hfst')
    if istr1 != None and istr2 != None:
        pass
    elif istr1 == None and istr2 != None:
        if arg1 == None:
            arg1 = '-'
        istr1 = _get_input_stream(arg1, 'hfst')
    elif istr1 != None and istr2 == None:
        if arg1 == None:
            arg1 = '-'
        istr2 = _get_input_stream(arg1, 'hfst')
    else:
        if arg2 == None:
            istr1 = _get_input_stream('-', 'hfst')
            istr2 = _get_input_stream(arg1, 'hfst')
        else:
            istr1 = _get_input_stream(arg1, 'hfst')
            istr2 = _get_input_stream(arg2, 'hfst')
    return ((istr1, name1), (istr2, name2))
