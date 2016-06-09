import libhfst
ab = libhfst.regex('a:b::2.8')
out = libhfst.HfstOutputStream(hfst_format=False)
out.write(ab)
out.flush()
out.close()
