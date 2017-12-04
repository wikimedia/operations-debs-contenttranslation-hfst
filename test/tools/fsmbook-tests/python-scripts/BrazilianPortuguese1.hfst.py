
exec(compile(open('CompileOptions.py', "rb").read(), 'CompileOptions.py', 'exec'))

tr = hfst.regex("[ a | e | i | o | u \
                 | á | é | í | ó | ú \
                 | â | ê |     ô     \
                 | ã |         õ     \
                 | à                 \
                 |                 ü \
                 ]")

tr.write_to_file('Vowel')

tr = hfst.regex('[ s -> z || @"Vowel" _ @"Vowel" ] \
  .o. \
  [ ç -> s ] \
  .o. \
       [ c h -> %$ ] \
        .o.  \
       [ c -> s || _ [ e | i | é | í | ê ] ] \
        .o.  \
  [ c -> k ] \
   .o.  \
  [ s s -> s ] \
   .o.  \
  [ n h -> N ] \
   .o.  \
  [ l h -> L ] \
   .o.  \
  [ h -> 0 ] \
   .o.  \
  [ r r -> R ] \
   .o.  \
  [ r -> R || .#. _ ] \
   .o.  \
  [ e -> i || _ (s) .#. , .#. p _ r ] \
   .o.  \
  [ o -> u || _ (s) .#. ] \
   .o.  \
  [ d -> J || _ [ i | ì ] ] \
   .o.  \
  [ t -> C || _ [ i | ì ] ] \
   .o.  \
  [ z -> s || _ .#. ]' )

tr.write_to_file('Result')
