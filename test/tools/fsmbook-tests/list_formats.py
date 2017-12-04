import sys
if len(sys.argv) > 2:
    raise RuntimeError('Usage: list_formats.py [[PYTHONPATH]]')
if len(sys.argv) == 2:
    sys.path.insert(0, sys.argv[1])
import hfst

print('Backend                         Names recognized')
if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.SFST_TYPE)):
    print('SFST                            sfst')
if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.TROPICAL_OPENFST_TYPE)):
    print('OpenFst (tropical weights)      openfst-tropical, openfst, ofst, ofst-tropical')
if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.LOG_OPENFST_TYPE)):
    print('OpenFst (logarithmic weights)   openfst-log, ofst-log')
if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.FOMA_TYPE)):
    print('foma                            foma')
if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.HFST_OL_TYPE)):
    print('Optimized lookup (weighted)     optimized-lookup-unweighted, olu')
if (hfst.HfstTransducer.is_implementation_type_available(hfst.ImplementationType.HFST_OLW_TYPE)):
    print('Optimized lookup (unweighted)   optimized-lookup-weighted, olw, optimized-lookup, ol')

