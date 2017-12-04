exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

Nouns = hfst.fst(["bird","hund","kat","elefant"])

Nmf = hfst.regex('[ [i n] | [e t] | [e g] ]*')

Nend = hfst.regex('[o]')

Number = hfst.regex('[(j)]')

Case = hfst.regex('[(n)]')

Result = hfst.regex('[0]')

tr = hfst.concatenate([Result, Nouns, Nmf, Nend, Number, Case])
tr.minimize()
tr.write_to_file('Result')
