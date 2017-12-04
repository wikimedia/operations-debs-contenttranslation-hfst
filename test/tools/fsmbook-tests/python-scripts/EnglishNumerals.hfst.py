exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))


# From "one" to "nine":
OneToNine = hfst.fst(["one","two","three","four","five","six","seven","eight","nine"])
#OneToNine.write_to_file('OneToNine.hfst')

# It is convenient to define a set of prefixes that can be followed either by "teen" or by "ty":
TeenTen = hfst.fst(["thir","fif","six","seven","eigh","nine"])
#TeenTen.write_to_file('TeenTen.hfst')
              
# From "ten" to "nineteen":

TenElevenTwelve = hfst.fst(["ten","eleven","twelve"])
Teen = hfst.fst("teen")
Four = hfst.fst("four")

Teens = hfst.HfstTransducer(Four)
Teens.disjunct(TeenTen)
Teens.concatenate(Teen)
Teens.disjunct(TenElevenTwelve)

# echo "four" | $2/$TOOLDIR/hfst-strings2fst -f $1 | $2/$TOOLDIR/hfst-disjunct TeenTen.hfst | $2/$TOOLDIR/hfst-concatenate -2 Teen.hfst | $2/$TOOLDIR/hfst-disjunct TenElevenTwelve.hfst > Teens.hfst;

# Let's define a set of prefixes that can be followed by "ty".

TenStem = hfst.fst(["twen","for"])
TenStem.disjunct(TeenTen)

#echo "twen
#for" | $2/$TOOLDIR/hfst-strings2fst -j -f $1 | $2/$TOOLDIR/hfst-disjunct TeenTen.hfst > TenStem.hfst;

# TenStem is followed either by "ty" or by ty-" and a number from OneToNine.

TMP = hfst.HfstTransducer(TenStem)
Ty = hfst.fst("ty")
TMP.concatenate(Ty)
Epsilon = hfst.epsilon_fst()
Hyphen = hfst.fst("-")
Hyphen.concatenate(OneToNine)
Hyphen.disjunct(Epsilon)
TMP.concatenate(Hyphen)
Tens = TMP

OneToNine.disjunct(Teens)
OneToNinetyNine = OneToNine
OneToNinetyNine.disjunct(Tens)

OneToNinetyNine.write_to_file('Result')

#echo "ty" | $2/$TOOLDIR/hfst-strings2fst -f $1 | $2/$TOOLDIR/hfst-concatenate -1 TenStem.hfst > TMP.hfst;
#echo "" | $2/$TOOLDIR/hfst-strings2fst -f $1 > Epsilon.hfst;
#echo "-" | $2/$TOOLDIR/hfst-strings2fst -f $1 | $2/$TOOLDIR/hfst-concatenate -2 OneToNine.hfst | $2/$TOOLDIR/hfst-disjunct Epsilon.hfst | $2/$TOOLDIR/hfst-concatenate -1 TMP.hfst > Tens.hfst;

#$2/$TOOLDIR/hfst-disjunct OneToNine.hfst Teens.hfst | $2/$TOOLDIR/hfst-disjunct -2 Tens.hfst > OneToNinetyNine.hfst;


