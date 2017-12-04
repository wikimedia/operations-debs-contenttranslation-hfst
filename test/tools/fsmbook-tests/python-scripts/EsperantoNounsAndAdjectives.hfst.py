exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

NounRoots = hfst.fst(["bird","hund","kat","elefant"])

AdjRoots = hfst.fst(["bon","long","jun","alt","grav"])

NounPrefix = hfst.regex('[(g e)]')

AdjPrefixes = hfst.regex('[ ([m a l] | [n e]) ]')

Nend = hfst.regex('[o]')
Nend.write_to_file('Nend')

Adjend = hfst.regex('[a]')
Adjend.write_to_file('Adjend')

Number = hfst.regex('[(j)]')

Case = hfst.regex('[(n)]')

Nmf = hfst.regex('[ ([i n] | [e t] | [e g])* [@"Nend" | @"Adjend"] ]')

Adj = hfst.regex('([e g] | [e t])* [@"Adjend" | [e c @"Nend"]]')

NounStem = hfst.concatenate([NounPrefix, NounRoots, Nmf])

AdjectiveStem = hfst.concatenate([AdjPrefixes, AdjRoots, Adj])

Stems = hfst.disjunct([NounStem, AdjectiveStem])

Result = hfst.concatenate([Stems, Number, Case])
Result.minimize()
Result.write_to_file('Result')
