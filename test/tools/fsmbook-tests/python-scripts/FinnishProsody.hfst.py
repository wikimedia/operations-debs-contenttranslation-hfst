exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

comp = hfst.XreCompiler(hfst.get_default_fst_type())

verbose_regex=False

def regex(name, expression):
    tr = comp.compile(expression)
    if name == None:
        return tr
    else:
        comp.define_transducer(name, tr)
        if verbose_regex:
            print("defined transducer '" + expression + "':")
            print(tr)

# The data
FinnWords = hfst.fst(("kalastelet",
                      "kalasteleminen",
                      "ilmoittautuminen",
                      "järjestelemättömyydestänsä",
                      "kalastelemme",
                      "ilmoittautumisesta",
                      "järjestelmällisyydelläni",
                      "järjestelmällistämätöntä",
                      "voimisteluttelemasta",
                      "opiskelija",
                      "opettamassa",
                      "kalastelet",
                      "strukturalismi",
                      "onnittelemanikin",
                      "mäki",
                      "perijä",
                      "repeämä",
                      "ergonomia",
                      "puhelimellani",
                      "matematiikka",
                      "puhelimistani",
                      "rakastajattariansa",
                      "kuningas",
                      "kainostelijat",
                      "ravintolat",
                      "merkonomin"))

# Some definitions:

regex('HighV', '[u | y | i]')
regex('MidV', '[e | o | ö]')
regex('LowV', '[a | ä]')
regex('USV', '[ HighV | MidV | LowV ]')

regex('C', '[ b | c | d | f | g | h | j | k | l | m | n | p | q | r | s | t | v | w | x | z ]')

regex('MSV', '[á | é | í | ó | ú | ý | ä´ | ö´ ]')
regex('SSV', '[à | è | ì | ò | ù | y` | ä` | ö` ]')
regex('SV', '[ MSV | SSV ]')
regex('V', '[ USV | SV ]')

regex('P', '[ V | C ]')

regex('B', '[[\P+] | .#.]')
regex('E', '[ .#. | "."]')
regex('SB', '[~$"." "." ~$"."]')

regex('Light', '[ C* V ]')
regex('Heavy', '[ Light P+ ]')

regex('S', '[ Heavy | Light ]')
regex('SS', '[ S & $SV ]')
regex('US', '[ S & ~SV ]')
regex('MSS', '[ S & $MSV ]')

regex('BF', '[ S "." S ]')

# Rules for prosody:

MarkNonDiphtongs = regex(None,
                         '[ [. .] -> "." || [ HighV | MidV ] _ LowV,\
                         i _ [MidV - e],\
                         u _ [MidV - o],\
                         y _ [MidV - ö] ]')

# The general syllabification rule has exceptions. In particular, loan
# words such as ate.isti 'atheist' must be partially syllabified in the
# lexicon.

Syllabify = regex(None, ' C*  V+ C* @-> ... "." || _ C V ')

TernaryFeet = regex(None,
                    ' BF "." Light @-> "(" ... ")" \
                    // [{).} | .#.] [BF "."]*  _ \
                    ["." Heavy "." S ] | .#. ')

# Scan all the unfooted material into binary feet.
                     
BinaryFeet = regex(None, ' BF @-> "(" ... ")" || .#.|"." _ .#.|"." ')

# Assign the primary stress to the first vowel of the first syllable.

MainStress = regex(None,
                   ' a -> á, e -> é, i -> í, o -> ó,\
                   u -> ú, y -> ý, ä -> "ä´", ö -> "ö´" || .#. "(" C* _')

# Assign secondary stress to all initial vowels of non-initial syllables.

SecondaryStress = regex(None,
                        ' a -> à, e -> è, i -> ì, o -> ò,\
                        u -> ù, y -> "y`", ä -> "ä`", ö -> "ö`"\
                        || "(" C* _ ')

# Assign an optional secondary stress to an unfooted final syllable
# if it is heavy.

OptFinalStress = regex(None,
                       'a (->) à, e (->) è, i (->) ì,\
                       o (->) ò, u (->) ù, y (->) "y`",\
                       ä (->) "ä`", ö (->) "ö`" || "." C* _ P .#. ')

# Calculate the composition of rules from =MarkNonDiphtongs= to =OptFinalStress=
# and compose the lexicon with the composition of rules.

Rules = hfst.compose((MarkNonDiphtongs, Syllabify, TernaryFeet, BinaryFeet, MainStress, SecondaryStress, OptFinalStress))

FinnProsody = hfst.compose((FinnWords, Rules))

FinnProsody.write_to_file('Result')
