exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

comp = hfst.XreCompiler(hfst.get_default_fst_type())

def regex(name, expression):
    tr = comp.compile(expression)
    if name == None:
        return tr
    else:
        comp.define_transducer(name, tr)

regex('Stems', "[ {bet} | {béb} | {bomb} | {bóndel} | {bóngol} | {bót} | {búk} | \
 {fung} | {kabol} | {kang} | {kom} | {kund} | {kóm} | {lakis} | \
 {lí}  | {lob} | {luk} | {ndim} | {palangan} | {pangwis} | {sál} | \
 {sepel} | {sómb} | {tál} | {támbol} | {tambwis} | {tataban} | \
 {tún} | {yébis} \
]")

regex('L', "[a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|á|é|í|ó|ú]")

regex('Person1', '[Per ":" 1]')
regex('Person2', '[Per ":" 2]')
regex('Person3', '[Per ":" 3]')
regex('Number', '[Num ":" [Sg|Pl] ]')

# define Gender [Gen ":" [[1["0"|1]|2|3|4|5|6|7|8|9] "." [1[4|5]|[1|9|10]a]]];
regex('Gender3', '[Gen ":" [1 "." 2 | 1a "." 2 | 3 "." 4 | 5 "." 6 | 7 "." 8 | 9a "." "10a" | "10" | 11 "." 6 | 14 "." 6 | 15]]')
 
# define Reflexive [No | Yes];

# Passive: -am-
# Causative: -is-
# Reciprocal: -an-
# Applicative:l -el-
# Reversive: -ol-
# Iterative: reduplication of the root or root plus other morpheme;
#  the two copies are separated by -a-; the second copy of the root
#  has low tone on the first syllable
# That is, the order of the morphemes is: REV, CAUS, PASS, APPL, RECIP

# alobaloba 'he/she speak SP ITER'
# alíalia   'he eat SP ITER'

regex('PastTense', '[Past ":" [Rec|Hist|MoreRem|MostRem]]')
regex('PresTense', '[Pres ":" [Cont|Hab1|Hab2]]')
regex('FutTense', '[Fut ":" [Immed|MostRem]]')

# define Reflexive [Refl ":" [No|Yes]];
regex('Tense', '[Tns ":" [PastTense|PresTense|FutTense]]')
# define Polarity [Pol ":" [Pos|Neg]];

regex('Agreement', ' [[[Person1 | Person2] " " Number] | [Person3 " " Number " " Gender3]]')

                
# For Gender 15 we have only singular subject marker, no plural
# and no object markers. Missing info?

regex('SubjAgr', '[Sub ":" Agreement]  - [$Pl & $15]')
regex('ObjAgr', '[Obj ":" Agreement] - $15 ')
regex('Agr', '[Func ":" Agreement]')

#define Features [SubjAgr " " ObjAgr " "  Tense " " Polarity];

regex('Features', '[SubjAgr " " ObjAgr " " Tense]')

regex('VerbLex', '"<" Stems "," Features ">" ')

# Common singular agreement markers.

regex('RAgr1', '[[. .] -> {mo} || "<" _ [$[Agr & $Person3 & $Sg & $4]]]')
regex('RAgr2', '[[. .] -> {li} || "<" _ [$[Agr & $Person3 & $Sg & $5]]]')
regex('RAgr3', '[[. .] -> e  || "<" _ [$[Agr & $Person3 & $Sg & $[9a "." "10a"]]]]')
regex('RAgr4', '[[. .] -> {lo} || "<" _ [$[Agr & $Person3 & $Sg & $["10"|11]]]]')
regex('RAgr5', '[[. .] -> {bo} || "<" _ [$[Agr & $Person3 & $Sg & $14]]]')
# Common plural agreement markers

regex('RAgr6', '[[. .] -> {bo} || "<" _ [$[Agr & $Person2 & $Pl]]] ')
regex('RAgr7', '[[. .] -> {ba} || "<" _ [$[Agr & $Person3 & $Pl & $2]]]')
regex('RAgr8', '[[. .] -> {mi} || "<" _ [$[Agr & $Person3 & $Pl & $4]]]')
regex('RAgr9', '[[. .] -> {ma} || "<" _ [$[Agr & $Person3 & $Pl & $[5|6]]]]')
regex('RAgr10', '[[. .] -> {bi}  || "<" _ [$[Agr & $Person3 & $Pl & $7]]]')
regex('RAgr11', '[[. .] -> i  || "<" _ [$[Agr & $Person3 & $Pl & $[9a|"10"]]]]')

# Rule Block 1
# Singular specific subject markers

regex('R101', '[[. .] -> {na} || "<" _ [$[SubjAgr & $Person1 & $Sg]]] ')
regex('R102', '[[. .] -> o || "<" _ [$[SubjAgr & $Person2 & $Sg]]] ')
regex('R103', '[[. .] -> a || "<" _ [$[SubjAgr & $Person3 & $Sg & $2]]]')
regex('R104', '[[. .] -> e  || "<" _ [$[SubjAgr & $Person3 & $Sg & $7]]]')
regex('R105', '[[. .] -> {ei} || "<" _[$[SubjAgr & $Person3 & $Sg & $15]]]')

# Rules of referral for singular subject markers
regex('R106', '`[RAgr1, Func, Sub]')
regex('R107', '`[RAgr2, Func, Sub]')
regex('R108', '`[RAgr3, Func, Sub]')
regex('R109', '`[RAgr4, Func, Sub]')
regex('R110', '`[RAgr5, Func, Sub]')
# Plural specific subject markers

regex('R111', '[[. .] -> {to} || "<" _ [$[SubjAgr & $Person1 & $Pl]]] ')

# Rules of referral for plural subject markers.

regex('R112', '`[RAgr6, Func, Sub]')
regex('R113', '`[RAgr7, Func, Sub]')
regex('R114', '`[RAgr8, Func, Sub]')
regex('R115', '`[RAgr9, Func, Sub]')
regex('R116', '`[RAgr10, Func, Sub]')
regex('R117', '`[RAgr11, Func, Sub]')

regex('R201', '[[. .] -> {ko} || "<" _ [$[Fut":"Immed]]] ')

# Singular specific object markers

regex('R301', '[[. .] -> n || "<" _ [$[ObjAgr & $Person1 & $Sg]]] ')
regex('R302', '[[. .] -> {ko} || "<" _ [$[ObjAgr & $Person2 & $Sg]]] ')
regex('R303', '[[. .] -> {mo} || "<" _ [$[ObjAgr & $Person3 & $Sg & $2]]]')
regex('R304', '[[. .] -> {ei}  || "<" _ [$[ObjAgr & $Person3 & $Sg & $7]]]')

# Rules of referral for singular object markers

regex('R305', '`[RAgr1, Func, Obj]')
regex('R306', '`[RAgr2, Func, Obj]')
regex('R307', '`[RAgr3, Func, Obj]')
regex('R308', '`[RAgr4, Func, Obj]')
regex('R309', '`[RAgr5, Func, Obj]')

# Plural specific object markers

regex('R310', '[[. .] -> {lo} || "<" _ [$[ObjAgr & $Person1 & $Pl]]] ')

# Rules of referral for plural object markers

regex('R311', '`[RAgr6, Func, Obj]')
regex('R312', '`[RAgr7, Func, Obj]')
regex('R313', '`[RAgr8, Func, Obj]')
regex('R314', '`[RAgr9, Func, Obj]')
regex('R315', '`[RAgr10, Func, Obj]')
regex('R316', '`[RAgr11, Func, Obj]')

# Tense rules
regex('R401', '[[. .] -> {ak} || _ "," [$[Pres ":" [Hab1|Hab2]| Past ":" [Hist|MostRem]]]]')
regex('R402', '[[. .] -> a    || _ "," [$[Pres ":" Cont|Fut ":" Immed]]]')

regex('R501', '[[. .] -> i || _ "," [$[Fut ":" MostRem|Past ":" [Rec|Hist]]]]')

# Eliminate Features and auxiliary symbols from the lower side.
regex('Cleanup', '\\L -> 0')

# Build the Lingala Verb Transducer
Result = regex(None, 'VerbLex .o. R301 .o. R302 .o. R303 .o. R304 .o. R305 .o. R306 .o. R307 .o. R308 .o. R309 .o. R310 .o. R311 .o. R312 .o. R313 .o. R314 .o. R315 .o. R316 .o. R201 .o. R101 .o. R102 .o. R103 .o. R104 .o. R105 .o. R106 .o. R107 .o. R108 .o. R109 .o. R110 .o. R111 .o. R112 .o. R113 .o. R114 .o. R115 .o. R116 .o. R117 .o. R401 .o. R402 .o. R501 .o. Cleanup ')
Result.minimize()
Result.write_to_file('Result')
