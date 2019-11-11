import hfst
import hfst_commandline

inputfilename=None
outputfilename=None
has_spaces=False
pairstrings=False
impl=hfst.ImplementationType.TROPICAL_OPENFST_TYPE

short_getopts = 'f:i:o:Sp'
long_getopts = ['format=','input=','output=','has-spaces','pairstrings']
options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)

for opt in options[0]:
    if opt[0] == '-f' or opt[0] == '--format':
        impl = hfst_commandline.get_implementation_type(opt[1])
    elif opt[0] == '-S' or opt[0] == '--has-spaces':
        has_spaces = True
    elif opt[0] == '-p' or opt[0] == '--pairstrings':
        pairstrings = True
    else:
        pass
istr = hfst_commandline.get_one_text_input_stream(options)[0]
ostr = hfst_commandline.get_one_hfst_output_stream(options, impl)[0]
hfst.set_default_fst_type(impl)

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
