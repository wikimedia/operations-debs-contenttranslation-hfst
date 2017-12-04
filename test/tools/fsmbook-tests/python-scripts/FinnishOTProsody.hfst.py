exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

comp = hfst.XreCompiler(hfst.get_default_fst_type())

def regex(name, expression):
    tr = comp.compile(expression)
    if name == None:
        return tr
    else:
        comp.define_transducer(name, tr)

# Data
regex('FinnWords', "{kalastelet} | {kalasteleminen} | {ilmoittautuminen} | \
                 {järjestelmättömyydestänsä} | {kalastelemme} | \
                 {ilmoittautumisesta} | {järjestelmällisyydelläni} | \
                 {järjestelmällistämätöntä} | {voimisteluttelemasta} | \
                 {opiskelija} | {opettamassa} | {kalastelet} | \
                 {strukturalismi} | {onnittelemanikin} | {mäki} | \
                 {perijä} | {repeämä} | {ergonomia} | {puhelimellani} | \
                 {matematiikka} | {puhelimistani} | {rakastajattariansa} | \
                 {kuningas} | {kainostelijat} | {ravintolat} | \
                 {merkonomin} ;")

# Basic definitions

regex('HighV', '[u | y | i]')                          # High vowel
regex('MidV', '[e | o | ö]')                          # Mid vowel
regex('LowV', '[a | ä]')                             # Low vowel
regex('USV', '[HighV | MidV | LowV]')                  # Unstressed Vowel

regex('C', "[b | c | d | f | g | h | j | k | l | m | n | p | q | r | s | t | v | w | x | z]")  # Consonant

regex('MSV', '[á | é | í | ó | ú | ý | ä´ | ö´ ]')
regex('SSV', '[à | è | ì | ò | ù | y` | ä` | ö`]')
regex('SV', '[MSV | SSV]')                              # Stressed vowel
regex('V', '[USV | SV] ')                               # Vowel

regex('P', '[V | C]')                                   # Phone
regex('B', '[[\P+] | .#. ]')                             # Boundary

regex('E', '.#. | "."')                                 # Edge
regex('SB', '[~$"." "." ~$"."]')                        # At most one syllable boundary

regex('Light', '[C* V]')                                # Light syllable
regex('Heavy', '[Light P+]')                            # Heavy syllable

regex('S', '[Heavy | Light]')                           # Syllable
regex('SS', '[S & $SV]')                                # Stressed syllable

regex('US', '[S & ~$SV]')                               # Unstressed syllable
regex('MSS', '[S & $MSV] ')                             # Syllable with main stress
regex('BF', '[S "." S]')                                # Binary foot


# Gen
#echo "-- GEN ---"

# A diphthong is a combination of two unlike vowels that together form
# the nucleus of a syllable. In general, Finnish diphthongs end in a high vowel.
# However, there are three exceptional high-mid diphthongs: ie, uo, and yö
# that historically come from long ee, oo, and öö, respectively.
# All other adjacent vowels must be separated by a syllable boundary.

regex('MarkNonDiphthongs', ' [. .] -> "." || [HighV | MidV] _ LowV , i _ [MidV - e] , u _ [MidV - o] , y _ [MidV - ö] ;')

# The general syllabification rule has exceptions. In particular, loan
# words such as ate.isti 'atheist' must be partially syllabified in the
# lexicon.


regex('Syllabify', 'C* V+ C* @-> ... "." || _ C V')


# Optionally adds primary or secondary stress to the first vowel
# of each syllable.

regex('Stress', 'a (->) á|à , e (->) é|è , i (->) í|ì , o (->) ó|ò , u (->) ú|ù , y (->) ý|y` , ä (->) ä´|ä` , ö (->) ö´|ö` || E C* _ ')
              

# Scan the word, optionally dividing it to any combination of
# unary, binary, and ternary feet. Each foot must contain at least
# one stressed syllable.


regex('Scan', '[[S ("." S ("." S)) & $SS] (->) "(" ... ")" || E _ E]')

# In keeping with the idea of "richness of the base", the Gen
# function produces a great number of output candidates for
# even short words. Long words have millions of possible outputs.

regex('Gen', '[MarkNonDiphthongs .o. Syllabify .o. Stress .o. Scan]')

# OT constraints

#echo "--- OT constraints --- "

# We use asterisks to mark constraint violations. Ordinary constraints
# such as Lapse assign single asterisks as the violation marks and the
# candidate with the fewest number is selected. Gradient constraints
# such as AllFeetFirst mark violations with sequences of asterisks.
# The number increases with distance from the word edge.

# Every instance of * in an output candidate is a violation.

regex('Viol', '${*}')



# We prune candidates with "lenient composition" that eliminates
# candidates that violate the constraint provided that at least
# one output candidate survives.

regex('Viol0', '~Viol')         # No violations
regex('Viol1', '~[Viol^2]')     # At most one violation
regex('Viol2', '~[Viol^3]')     # At most two violations
regex('Viol3', '~[Viol^4]')     # etc.
regex('Viol4', '~[Viol^5]')
regex('Viol5', '~[Viol^6]')
regex('Viol6', '~[Viol^7]')
regex('Viol7', '~[Viol^8]')
regex('Viol8', '~[Viol^9]')
regex('Viol9', '~[Viol^10]')
regex('Viol10', '~[Viol^11]')
regex('Viol11', '~[Viol^12]')
regex('Viol12', '~[Viol^13]')
regex('Viol13', '~[Viol^14]')
regex('Viol14', '~[Viol^15]')
regex('Viol15', '~[Viol^16]')




# This eliminates the violation marks after the candidate set has
# been pruned by a constraint.

regex('Pardon', '{*} -> 0')




# Constraints

#echo "CONSTRAINTS---"

# In this section we define nine constraints for Finnish prosody,
# listed in the order of their ranking: MainStress, Clash, AlignLeft,
# FootBin, Lapse, NonFinal, StressToWeight, Parse, and AllFeetFirst.
# For the one inviolable constraint, we assign no violation marks.
# Clash, Align-Left and Foot-Bin are always satisfiable in Finnish
# but we assign violation marks as not to depend on that knowledge.

# Main Stress: The primary stress in Finnish is on the first
#              syllable. This is an inviolable constraint.

regex('MainStress', '[B MSS ~$MSS]')


# Clash: No stress on adjacent syllables.
# define Clash SS -> ... {*} || SS B _ ;
regex('Clash', 'SS -> ... {*} || SS B _ ')



# Align-Left: The stressed syllable is initial in the foot.

regex('AlignLeft', 'SV -> ... {*} || .#. ~[?* "(" C*] _ ')


# Foot-Bin: Feet are minimally bimoraic and maximally bisyllabic.
# define FootBin ["(" Light ")" | "(" S ["." S]^>1] -> ... {*} ;
regex('FootBin', '["(" Light ")" | "(" S ["." S]^>1] -> ... {*} ')


# Lapse: Every unstressed syllable must be adjacent to a stressed
# syllable.
# define Lapse US -> ... {*} || [B US B] _ [B US B];
regex('Lapse', 'US -> ... {*} || [B US B] _ [B US B]')


# Non-Final: The final syllable is not stressed.

regex('NonFinal', 'SS -> ... {*} || _ ~$S .#.')


# Stress-To-Weight: Stressed syllables are heavy.

regex('StressToWeight', '[SS & Light] -> ... {*} || _ ")"| E')


# License-&#963;: Syllables are parsed into feet.

regex('Parse', 'S -> ... {*} || E _ E')


# All-Ft-Left: Every foot starts at the beginning of a
#              prosodic word.

regex('AllFeetFirst', '[ "(" -> ... {*} || .#. SB _ .o. "(" -> ... {*}^2 || .#. SB^2 _ .o. "(" -> ... {*}^3 || .#. SB^3 _ .o. "(" -> ... {*}^4 || .#. SB^4 _ .o. "(" -> ... {*}^5 || .#. SB^5 _ .o. "(" -> ... {*}^6 || .#. SB^6 _ .o. "(" -> ... {*}^7 || .#. SB^7 _ .o. "(" -> ... {*}^8 || .#. SB^8 _ ]')
#echo '"(" -> ... {*} || .#. SB _ ' | $2/hfst-regexp2fst -f $1 > a0
#echo '"(" -> ... {*}^2 || .#. SB^2 _ '  | $2/hfst-regexp2fst -f $1 > a1
#echo '"(" -> ... {*}^3 || .#. SB^3 _ '  | $2/hfst-regexp2fst -f $1 > a2
#echo '"(" -> ... {*}^4 || .#. SB^4 _ '  | $2/hfst-regexp2fst -f $1 > a3
#echo '"(" -> ... {*}^5 || .#. SB^5 _ '  | $2/hfst-regexp2fst -f $1 > a4
#echo '"(" -> ... {*}^6 || .#. SB^6 _ '  | $2/hfst-regexp2fst -f $1 > a5
#echo '"(" -> ... {*}^7 || .#. SB^7 _ '  | $2/hfst-regexp2fst -f $1 > a6
#echo '"(" -> ... {*}^8 || .#. SB^8 _ ' | $2/hfst-regexp2fst -f $1 > a7


# Evaluation
# Computing the prosody for FinnWords

# Some constraints can always be satisfied; some constraints are
# violated many times. The limits have been chosen to produce
# a unique winner in all the 25 test cases in FinnWords.

Result = regex(None, '[FinnWords .o. Gen .o. MainStress .o. Clash .O. Viol0 .o. Pardon .o. AlignLeft .O. Viol0 .o. FootBin .O. Viol0 .o. Pardon .o. Lapse .O. Viol3 .O. Viol2 .O. Viol1 .O. Viol0 .o. Pardon .o. NonFinal .O. Viol0 .o. Pardon .o. StressToWeight .O. Viol3 .O. Viol2 .O. Viol1 .O. Viol0 .o. Pardon .o. Parse .O. Viol3 .O. Viol2 .O. Viol1 .O. Viol0 .o. Pardon .o. AllFeetFirst .O. Viol15 .O. Viol14 .O. Viol13 Viol12 .O. Viol11 .O. Viol10 .O. Viol9 .O. Viol8 .O. Viol7 .O. Viol6  .O. Viol5  .O. Viol4  .O. Viol3 .O. Viol2 .O. Viol1 .O. Viol0 .o. Pardon ]')
Result.minimize()
Result.write_to_file('Result')


#echo '[ MainStress .o. Clash .O. Viol0 .o. Pardon .o. AlignLeft .O. Viol0 ]' | $2/hfst-regexp2fst -f $1 > FinnishOTProsody.hfst.hfst






#echo '[FinnWords .o. Gen .o. MainStress .o. Clash .O. Viol0 .o. Pardon .o. AlignLeft .O. Viol0 .o. FootBin .O. Viol0 .o. Pardon .o. Lapse .O. Viol3 .O. Viol2 .O. Viol1 .O. Viol0 .o. Pardon .o. NonFinal .O. Viol0 .o. Pardon .o. StressToWeight .O. Viol3 .O. Viol2 .O. Viol1 .O. Viol0 .o. Pardon .o. Parse .O. Viol3 .O. Viol2 .O. Viol1 ]' | $2/hfst-regexp2fst -f $1 > Result

