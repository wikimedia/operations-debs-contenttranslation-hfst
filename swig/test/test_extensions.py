import libhfst
import io

tr = libhfst.HfstTransducer('a', 'b', libhfst.TROPICAL_OPENFST_TYPE)
paths = libhfst.extract_paths(tr)
for path in libhfst.detokenize_paths(paths):
    print("{0}:{1}  {2}".format(path.input, path.output, path.weight))

tr = libhfst.HfstTransducer('a', 'b', libhfst.TROPICAL_OPENFST_TYPE)
tr.convert(libhfst.HFST_OLW_TYPE)
for path in libhfst.detokenize_paths(tr.lookup("a")):
    print("{0}  {1}".format(path.output, path.weight))

