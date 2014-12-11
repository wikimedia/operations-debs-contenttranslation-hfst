# Creates transducers of all implementation types from a set of regular expressions.
# Prints regexps and their resulting transducers to standard output for tropical openfst type.
# For other implementation types, compares the results with the result for tropical openfst type.
# To make sure that everything is working, the user must hand-check the output.

import libhfst

types = [libhfst.SFST_TYPE, libhfst.TROPICAL_OPENFST_TYPE, libhfst.FOMA_TYPE]

# A dictionary that maps transducer implementation types to
# lists of transducer pointers
transducers = {}

# The regexps that we convert into transducers and store in
# the lists in the dictionary
regexps = ['a:b', '0:c', 'foo:bar', 'a:b c:d', 'baz:"0"*', 'a b+ a:c'] # , 'Var d Var'] TODO

for type in types:

    if not libhfst.HfstTransducer.is_implementation_type_available(type):
        continue

    transducers[type] = []
    compiler = libhfst.XreCompiler(type)
    # compiler.define('Var', 'v a r') TODO

    for regexp in regexps:
        # Print only results from tropical openfst implementation
        if type == libhfst.TROPICAL_OPENFST_TYPE:
            print("{0}".format(regexp))
        # Compile the regexp and append it to the list
        tr = compiler.compile(regexp)
        transducers[type].append(tr)
        # Print only results from tropical openfst implementation
        if type == libhfst.TROPICAL_OPENFST_TYPE:
            print(tr)


# Compare all the transducers with the transducers for tropical openfst type
for type_ind, type_val in enumerate(transducers):
    for tr_ind, tr_val in enumerate(transducers[type_val]):
        # Convert the transducer that we are comparing into tropical openfst format
        tr = libhfst.ptrvalue(transducers[type_val][tr_ind].convert(libhfst.TROPICAL_OPENFST_TYPE))
        # Get the transducer which we are comparing with
        tr_tropical = libhfst.ptrvalue(transducers[libhfst.TROPICAL_OPENFST_TYPE][tr_ind])
        # Compare
        assert(tr.compare(tr_tropical))

