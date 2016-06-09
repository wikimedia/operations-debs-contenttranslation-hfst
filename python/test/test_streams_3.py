import libhfst

f = libhfst.hfst_stdin()
while not f.is_eof():
    print(libhfst.read_att(f))
