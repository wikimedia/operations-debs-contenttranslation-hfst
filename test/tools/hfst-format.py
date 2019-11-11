import hfst
import hfst_commandline

list_formats=False
test_format=None
shortopts = 'l'
longopts = ['list-formats', 'test-format=']
options = hfst_commandline.hfst_getopt(shortopts, longopts, 1)
for opt in options[0]:
    if opt[0] == '-l' or opt[0] == '--list-formats':
        list_formats=True
    elif opt[0] == '--test-format':
        test_format = opt[1]
    else:
        pass

if (not list_formats) and test_format == None and len(options[1]) == 0:
    raise RuntimeError('error: hfst-format.py: input file, option --list-formats or option --test-format FMT must be given')

aval = hfst.HfstTransducer.is_implementation_type_available

if list_formats:
    print('Backend                         Names recognized')
    print('')
    if aval(hfst.ImplementationType.SFST_TYPE):
        print('SFST                            sfst')
    if aval(hfst.ImplementationType.TROPICAL_OPENFST_TYPE):
        print('OpenFst (tropical weights)      openfst-tropical, openfst, ofst, ofst-tropical')
    if aval(hfst.ImplementationType.LOG_OPENFST_TYPE):
        print('OpenFst (logarithmic weights)   openfst-log, ofst-log')
    if aval(hfst.ImplementationType.FOMA_TYPE):
        print('foma                            foma')
    if aval(hfst.ImplementationType.HFST_OL_TYPE):
        print('Optimized lookup (weighted)     optimized-lookup-unweighted, olu')
    if aval(hfst.ImplementationType.HFST_OLW_TYPE):
        print('Optimized lookup (unweighted)   optimized-lookup-weighted, olw, optimized-lookup, ol')

if test_format != None:
    from sys import exit
    if test_format == 'sfst':
        if aval(hfst.ImplementationType.SFST_TYPE):
            exit(0)
        else:
            exit(1)
    elif test_format == 'openfst-tropical' or test_format == 'openfst' or test_format == 'ofst' or test_format == 'ofst-tropical':
        if aval(hfst.ImplementationType.TROPICAL_OPENFST_TYPE):
            exit(0)
        else:
            exit(1)
    elif test_format == 'openfst-log' or test_format == 'ofst-log':
        if aval(hfst.ImplementationType.LOG_OPENFST_TYPE):
            exit(0)
        else:
            exit(1)
    elif test_format == 'foma':
        if aval(hfst.ImplementationType.FOMA_TYPE):
            exit(0)
        else:
            exit(1)
    elif test_format == 'optimized-lookup-unweighted' or test_format == 'olu':
        if aval(hfst.ImplementationType.HFST_OL_TYPE):
            exit(0)
        else:
            exit(1)
    elif test_format == 'optimized-lookup-weighted' or test_format == 'olw' or test_format == 'optimized-lookup' or test_format == 'ol':
        if aval(hfst.ImplementationType.HFST_OLW_TYPE):
            exit(0)
        else:
            exit(1)
    else:
        raise RuntimeError('hfst-format.py: format ' + test_format + ' not recognized')

if len(options[1]) != 0:
    istr = hfst.HfstInputStream(options[1][0])
    for tr in istr:
        t = tr.get_type()
        print(hfst.fst_type_to_string(t))
    istr.close()


