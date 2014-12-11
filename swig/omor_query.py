'''This is a demo python script to show how you might do lookup through
libhfst, in this case using an omorfi installation.'''

import os, sys
from itertools import ifilterfalse as ffilter
import libhfst
datadir = "/usr/local/share/hfst/fi"
omorfipath = os.path.abspath(datadir + "/morphology.finntreebank.hfstol")

def process_result_vector(vector):
    results = []
    for entry in vector:
        if len(entry) < 2:
            continue
        weight = entry[0]
        string = ''.join(ffilter(libhfst.FdOperation.is_diacritic, entry[1]))
        results.append((string, weight))
    return results

istr = libhfst.HfstInputStream(omorfipath)
transducer = libhfst.HfstTransducer(istr)
input = raw_input()
while input:
    results = process_result_vector(libhfst.vectorize(transducer.lookup_fd(input)))
    for result in results:
        print result[0] + '\t' + str(result[1])
    try:
        input = raw_input()
    except EOFError:
        sys.exit()
