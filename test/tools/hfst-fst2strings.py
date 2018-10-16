import hfst
nrandom=None
xfst=None
obeyflags=False
infile=None
from sys import argv
for arg in argv[1:]:
    if arg == '--random' or arg == '-r':
        random = '<next>'
    elif arg == '--xfst' or arg == '-X':
        xfst = '<next>'
    elif nrandom == '<next>':
        nrandom = int(arg)
    elif xfst == '<next>':
        if arg == 'obey-flags':
            obeyflags=True
            xfst=None
        else:
            raise RuntimeError('error: hfst-fst2strings.py: option --xfst supports only variable obey-flags')
    else:
        infile = arg

istr = hfst.HfstInputStream(infile)
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
