import libhfst

tr1 = libhfst.regex('föö:bär')
tr2 = libhfst.regex('0')
tr3 = libhfst.regex('0-0')

ostr = libhfst.HfstOutputStream()
ostr.write(tr1)
ostr.write(tr2)
ostr.write(tr3)
ostr.flush()
ostr.close()
