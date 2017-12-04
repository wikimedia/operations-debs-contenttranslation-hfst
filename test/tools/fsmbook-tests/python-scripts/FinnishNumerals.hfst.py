exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))


# First, we create a transducer that maps numbers 2 ... 9 to the corresponding numerals:
two_to_nine = hfst.fst({'2':'kaksi',
                        '3':'kolme',
                        '4':'neljä',
                        '5':'viisi',
                        '6':'kuusi',
                        '7':'seitsemän',
                        '8':'kahdeksan',
                        '9':'yhdeksän'})

# and 1 ... 9:
tmp = hfst.fst({'1':'yksi'})
one_to_nine = hfst.disjunct((tmp, two_to_nine))

# 10 is handled as a separate case:
ten = hfst.fst({'10':'kymmenen'})

# From 11 to 19, i.e.  [ 1:0 1to9 0:toista ]:
one_to_eps = hfst.fst({'1':''})
eps_to_toista = hfst.fst({'':'toista'})
eleven_to_nineteen = hfst.concatenate((one_to_eps, one_to_nine, eps_to_toista))

# From 20 to 99, i.e.  [ 2to9 0:kymmentä ( "0":0 | 1to9 ) ]:
eps_to_kymmenta = hfst.fst({'':'kymmentä'})
zero_to_eps = hfst.fst({'0':''})
TMP = hfst.concatenate((two_to_nine, eps_to_kymmenta))
tmp = hfst.disjunct((one_to_nine, zero_to_eps))
twenty_to_ninetynine = hfst.concatenate((TMP, tmp))

# Finally, from 1 to 99:
FinnishNumerals = hfst.disjunct((one_to_nine, ten, eleven_to_nineteen, twenty_to_ninetynine))
FinnishNumerals.minimize()

# To get transducers that map Finnish to English numerals and vice versa, we use
# composition and inversion.
# NOTE: we assume that the file NumbersToNumerals is already created
tr = hfst.HfstTransducer.read_from_file('tmpdir/NumbersToNumerals')
tr.convert(hfst.get_default_fst_type())
FinnishNumerals.invert()
FinnishNumerals.compose(tr)
FinnishNumerals.minimize()
FinnishNumerals.invert()
FinnishNumerals.minimize()
FinnishNumerals.write_to_file('Result')
