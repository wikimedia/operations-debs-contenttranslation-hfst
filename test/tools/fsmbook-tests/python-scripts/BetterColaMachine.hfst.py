exec(compile(open('CompileOptions.py', "rb").read(), 'CompileOptions.py', 'exec'))

tr = hfst.regex(' [ D -> N^2, Q -> N^5 ] ')
tr.write_to_file('Result')

