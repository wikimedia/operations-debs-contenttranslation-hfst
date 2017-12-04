exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

comp = hfst.XreCompiler(hfst.get_default_fst_type())

def regex(name, expression):
    tr = comp.compile(expression)
    if name == None:
        return tr
    else:
        comp.define_transducer(name, tr)


regex('FrontV', '[ i | e | é | ä ]')

regex('BackV', '[ u | o | ó | a ]')

regex('MorphoV', '[ %^U | %^O | %^Ó | %^A ]')

regex('Root', '[ [ ? - [ BackV | MorphoV ] ]+ & $[ FrontV ] ] | [ [ ? - [ FrontV | MorphoV ] ]+ & $[ BackV ] ]')
      
regex('Suff1', '[ %+Int .x. [ %^U %^U k ] ]')

regex('Suff2', '[ %+Perf .x. [ %^O n ] ] | [ %+Imperf .x. [ %^Ó m b ] ] | [ %+Opt .x. [ %^U d d ] ]')

regex('Suff3', '[ %+True .x. [ %^A n k ] ] | [ %+Belief .x. [ %^A %^A v %^O  t ] ] |[ %+Doubt .x. [ %^U %^U z ] ] | [ %+False .x. [ %^Ó q ] ]')

regex('Suff4', '[ %+1P %+Sg .x. %^A %^A b %^A ] | [ %+2P %+Sg .x. %^Ó m %^A ] | [ %+3P %+Sg .x. %^U v v %^U ] | [ %+1P %+Pl %+Excl .x. %^A %^A b %^O r %^A ] | [ %+1P %+Pl %+Incl .x. %^A %^A b %^U g %^A ] | [ %+2P %+Pl .x. %^Ó m %^O r %^A ] | [ %+3P %+Pl .x. %^U v v %^O r %^U ]')

Rule1 = regex(None, '[ %^U -> u , %^O -> o , %^Ó -> ó , %^A -> a || BackV ?* _ ]')

Rule2 = regex(None, '[ %^U -> i , %^O -> e , %^Ó -> é , %^A -> ä ]')

tmp = regex(None, '[ Root (Suff1) Suff2 (Suff3) Suff4 ]')

Result = hfst.compose((tmp, Rule1, Rule2))
Result.minimize()
Result.write_to_file('Result')
