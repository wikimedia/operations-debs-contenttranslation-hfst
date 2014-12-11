import libhfst  

types = [libhfst.TROPICAL_OPENFST_TYPE, libhfst.SFST_TYPE, libhfst.FOMA_TYPE]

# Transducers which the rule transducers are compared with
rule1 = libhfst.HfstTransducer(libhfst.TROPICAL_OPENFST_TYPE)
rule2 = libhfst.HfstTransducer(libhfst.TROPICAL_OPENFST_TYPE)
rule3 = libhfst.HfstTransducer(libhfst.TROPICAL_OPENFST_TYPE)

for type in types:

    if not libhfst.HfstTransducer.is_implementation_type_available(type):
        continue
  
    print("HfstTransducer two_level_if(HfstTransducerPair &context, StringPairSet &mappings, StringPairSet &alphabet)")
    print("HfstTransducer two_level_only_if(HfstTransducerPair &context, StringPairSet &mappings, StringPairSet &alphabet)")
    print("HfstTransducer two_level_if_and_only_if(HfstTransducerPair &context, StringPairSet &mappings, StringPairSet &alphabet)")

    leftc = libhfst.HfstTransducer("c", type)
    rightc = libhfst.HfstTransducer("c", type)
    context = (leftc, rightc)
    mapping = ("a", "b")
    mappings = ("a", "b"),
    alphabet = ('a','a'), ('a','b'), ('b','b'), ('c','c')

    rule_transducer1 = libhfst.two_level_if(context, mappings, alphabet)
    rule_transducer2 = libhfst.two_level_only_if(context, mappings, alphabet)
    rule_transducer3 = libhfst.two_level_if_and_only_if(context, mappings, alphabet)

    # Compare rule transducers with tropical rule transducers
    if type != libhfst.TROPICAL_OPENFST_TYPE:
        rule_transducer1.convert(libhfst.TROPICAL_OPENFST_TYPE)
        rule_transducer2.convert(libhfst.TROPICAL_OPENFST_TYPE)
        rule_transducer3.convert(libhfst.TROPICAL_OPENFST_TYPE)
        assert(rule_transducer1.compare(rule1))
        assert(rule_transducer2.compare(rule2))
        assert(rule_transducer3.compare(rule3))
    else:
        rule1.assign(rule_transducer1)
        rule2.assign(rule_transducer2)
        rule3.assign(rule_transducer3)

exit(0)
