import hfst_commandline
import hfst

short_getopts='r:X:'
long_getopts=['random=','xfst=']
nrandom=None
xfst=None
obeyflags=False
infilename=None

options = hfst_commandline.hfst_getopt(short_getopts, long_getopts, 1)
for opt in options[0]:
    if opt[0] == '-r' or opt[0] == '--random':
        pass #nrandom = int(opt[1]) todo: fix the tests...
    elif opt[0] == '-X' or opt[0] == '--xfst':
        if opt[1] == 'obey-flags':
            obeyflags=True
            xfst=None
        else:
            raise RuntimeError('error: hfst-fst2strings.py: option --xfst supports only variable obey-flags')
    else:
        pass
istr = hfst_commandline.get_one_hfst_input_stream(options)[0]

for tr in istr:
    weighted = tr.get_type() != hfst.ImplementationType.SFST_TYPE and tr.get_type() != hfst.ImplementationType.FOMA_TYPE
    paths=None
    if nrandom != None:
        paths = tr.extract_paths(obey_flags=obeyflags, random=nrandom)
    else:
        paths = tr.extract_paths(obey_flags=obeyflags)
    for key,values in paths.items():
        for value in values:
            print(key, end='')
            if (key != value[0]):
                print(':' + value[0], end='')
            #if weighted:
            #    print('\t' + str(value[1]), end='')
            print('', end='\n')
istr.close()
