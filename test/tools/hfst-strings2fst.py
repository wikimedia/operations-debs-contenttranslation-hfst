import hfst
from sys import argv, stdin

inputfilename=None
outputfilename=None
has_spaces=False
pairstrings=False
impl=hfst.ImplementationType.TROPICAL_OPENFST_TYPE

skip_next = False
for i in range(1, len(argv)):
    if skip_next:
        skip_next = False
        continue
    arg = argv[i]
    if arg == '-f' or arg == '--format':
        skip_next= True
        val = argv[i+1]
        if val == 'sfst':
            impl = hfst.ImplementationType.SFST_TYPE
        elif val == 'openfst-tropical':
            impl = hfst.ImplementationType.TROPICAL_OPENFST_TYPE
        elif val == 'foma':
            impl = hfst.ImplementationType.FOMA_TYPE
        else:
            raise RuntimeError('type not recognized: ' + val)
    elif arg == '-i':
        skip_next= True
        inputfilename = argv[i+1]
    elif arg == '-o':
        skip_next= True
        outputfilename = argv[i+1]
    elif arg == '-S' or arg == '--has-spaces':
        has_spaces=True
    elif arg == '-p' or arg == '--pairstrings':
        pairstrings=True
    elif inputfilename == None:
        inputfilename = arg
    elif outputfilename == None:
        outputfilename = arg
    else:
        raise RuntimeError('Unknown option: ' + arg)

hfst.set_default_fst_type(impl)

istr = None
if inputfilename != None:
    istr = open(inputfilename, 'r')
else:
    istr = stdin

ostr = None
if outputfilename != None:
    ostr = hfst.HfstOutputStream(filename=outputfilename, type=impl)
else:
    ostr = hfst.HfstOutputStream(type=impl)

for line in istr:
    line = line.rstrip()
    weight = None
    line_and_weight = line.split('\t')
    if len(line_and_weight) == 2:
        weight = float(line_and_weight[1])
        line = line_and_weight[0]
    tr = None
    if not pairstrings:
        input_and_output = line.split(':')
        if len(input_and_output) == 2:
            input_and_output[0] = input_and_output[0].strip().rstrip()
            input_and_output[1] = input_and_output[1].strip().rstrip()
            if not has_spaces:
                tr = hfst.fst(input_and_output[0])
                tr2 = hfst.fst(input_and_output[1])
                tr.cross_product(tr2)
            else:
                inputstr = input_and_output[0].split(' ')
                outputstr = input_and_output[1].split(' ')
                tr = hfst.tokenized_fst(inputstr)
                tr2 = hfst.tokenized_fst(outputstr)
                tr.cross_product(tr2)
        else:
            if not has_spaces:
                tr = hfst.fst(line)
            else:
                line = line.split(' ')
                tr = hfst.tokenized_fst(line)
    elif has_spaces:
        line = line.split(' ')
        symbols = []
        for pair in line:
            symbol_pair = pair.split(':')
            if len(symbol_pair) == 1: # HFST 4.0: accept also single symbols (identities)
                symbol_pair.append(symbol_pair[0])
            symbols.append(symbol_pair)
        tr = hfst.tokenized_fst(symbols)
    else: # pairstrings but no spaces
        symbols = []
        s = 0
        while(s < len(line)):
            pair = []
            pair.append(line[s])
            if s+1 == len(line): # last symbol
                pair.append(line[s])
                s = s+1
            elif line[s+1] == ':': # symbol pair
                pair.append(line[s+2])
                s = s+3
            else: # identity
                pair.append(line[s])
                s = s+1
            symbols.append(pair)
        tr = hfst.tokenized_fst(symbols)
    if weight != None:
        tr.set_final_weights(weight)
    ostr.write(tr)
    ostr.flush()

if inputfilename != None:
    istr.close()
ostr.close()
