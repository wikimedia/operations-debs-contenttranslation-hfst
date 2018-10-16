import hfst

istr = hfst.HfstInputStream()
n=1
for tr in istr:
    ostr = hfst.HfstOutputStream(filename=str(n) + ".hfst", type=tr.get_type())
    ostr.write(tr)
    ostr.flush()
    ostr.close()
    n = n + 1
istr.close()
