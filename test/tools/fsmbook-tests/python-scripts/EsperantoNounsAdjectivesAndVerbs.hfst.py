exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

NounPrefix = hfst.regex('([MF%+:g 0:e])')

NounRoots = hfst.fst(["bird","hund","kat","elefant"]) 

AdjRoots = hfst.fst(["bon","long","jun","alt","grav"]) 

VerbRoots = hfst.fst(["don","est","pens","dir","fal"]) 

VerbPrefixes = hfst.regex('([Op%+:m 0:a 0:l] | [Neg%+:n 0:e])')

Verb = hfst.regex('[%+Verb:0]')

Aspect = hfst.regex('([%+Cont:a 0:d])')

Vend = hfst.regex('[%+Inf:i] | [%+Pres:a 0:s] | [%+Past:i 0:s] | [%+Fut:o 0:s] | \
                   [%+Cond:u 0:s] | [%+Subj:u]')

Nmf = hfst.regex('%+Noun:0')

Nend = hfst.regex('%+NSuff:o')
Nend.write_to_file('Nend')

Adjend = hfst.regex('%+ASuff:a')
Adjend.write_to_file('Adjend')

AugDimFem  = hfst.regex('[[%+Fem:i 0:n] | [%+Dim:e 0:t] | [%+Aug:e 0:g]]* [@"Nend" | @"Adjend"]')

AdjPrefixes = hfst.regex('([Op%+:m 0:a 0:l] | [Neg%+:n 0:e])')

AugDimNize = hfst.regex('[[%+Aug:e 0:g] | [%+Dim:e 0:t]]* [[[%+Nize:e 0:c] @"Nend"]|[@"Adjend"]]')

Adj = hfst.regex('%+Adj:0')

Number = hfst.regex('%+Pl:j | %+Sg:0')

Case = hfst.regex('(%+Acc:n)')


NounStem = hfst.concatenate([NounPrefix, NounRoots, Nmf, AugDimFem])

AdjectiveStem = hfst.concatenate([AdjPrefixes, AdjRoots, Adj, AugDimNize])

NounAdjStems = hfst.disjunct([NounStem, AdjectiveStem])

NounAdjs = hfst.concatenate([NounAdjStems, Number, Case])

Verbs = hfst.concatenate([VerbPrefixes, VerbRoots, Verb, Aspect, Vend])

Result = hfst.disjunct([NounAdjs, Verbs])
Result.minimize()
Result.write_to_file('Result')
