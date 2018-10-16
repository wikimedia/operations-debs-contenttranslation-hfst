import hfst
from sys import argv, stdin, stderr
impl=hfst.ImplementationType.TROPICAL_OPENFST_TYPE
skip_next = False
harmonize=True
semicolons=False
infile=stdin
transducers_written=0

for i in range(1, len(argv)):
    if skip_next:
        skip_next = False
        continue
    arg = argv[i]
    if arg == '-f':
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
    elif arg == '-H' or arg == '--do-not-harmonize':
        harmonize=False
    elif arg == '-S' or arg == '--semicolon':
        semicolons=True
    else:
        infile = open(arg, 'r')

ostr = hfst.HfstOutputStream(type=impl)
comp = hfst.XreCompiler(impl)
comp.set_harmonization(harmonize)
if (semicolons):
    data = infile.read()
    i=0
    while(i < len(data)):
        tr_and_chars_read = comp.compile_first(data[i:]) # HFST 4.0: document this
        tr = tr_and_chars_read[0]
        i = i + tr_and_chars_read[1]
        if tr != None:
            ostr.write(tr)
            transducers_written = transducers_written + 1
        else:
            if comp.contained_only_comments(): # HFST 4.0: should return a str 'only comments' instead?
                pass
            else:
                import sys
                sys.exit(1)
                raise RuntimeError('error in regexp compilation')
else:
    for line in infile:
        tr = comp.compile(line)
        if tr != None:
            ostr.write(tr)
            transducers_written = transducers_written + 1
        else:
            if comp.contained_only_comments(): # HFST 4.0: should return a str 'only comments' instead?
                pass
            else:
                import sys
                sys.exit(1)
                raise RuntimeError('error in regexp compilation')

ostr.close()
if infile != stdin:
    infile.close()

if transducers_written == 0:
    import sys
    sys.exit(1)
    raise RuntimeError('no transducer was written')
