import libhfst

transducers = []
istr = libhfst.HfstInputStream()
while not istr.is_eof():
    transducers.append(istr.read())
istr.close()

if not len(transducers) == 3:
    raise RuntimeError('Wrong number of transducers read.')

i = 0
for re in ['föö:bär','0','0-0']:
    if not transducers[i].compare(libhfst.regex(re)):
        raise RuntimeError('Transducers are not equivalent.')
    i += 1

if len(transducers) > 0:
    f = libhfst.hfst_stdout()
    i=0
    transducers[i].write_att(f)
    i += 1
    while i < len(transducers):
        f.write('--\n')
        transducers[i].write_att(f)
        i += 1
