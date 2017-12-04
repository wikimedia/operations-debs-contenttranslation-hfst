exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

AdjPrefix = hfst.regex('[( [m a l] | [n e] )]')
Adjectives = hfst.fst(["bon","long","jun","alt","grav"])
Adj = hfst.regex('[[e g] | [e t]]*')
AdjEnd = hfst.regex('[a]')
Number = hfst.regex('[(j)]')
Case = hfst.regex('[(n)]')
Result = hfst.regex('[0]')

for tr in [AdjPrefix, Adjectives, Adj, AdjEnd, Number, Case]:
    Result.concatenate(tr)

Result.minimize()
Result.write_to_file('Result')
