exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

# We first construct BidirEnglish that
# contains all the words whose reverse is also a word of English,
# for example, "madam" and "dog". We wish to keep "madam" (reversed "madam") and
# eliminate "dog" (reversed "god").

with open('lexicon/english_lexicon.txt') as f:
    words = f.readlines()
English = hfst.fst(words)
English.substitute('\n', hfst.EPSILON)
English.minimize()

# We intersect English with its reverse. We only take into account
# words that contain at least two characters. (Words like "a"
# and "I" are not interesting here.)

MinTwoChars = hfst.regex('[? ?+]')

RevEnglish = English.copy()
RevEnglish.reverse()

BidirEnglish = hfst.intersect((English, RevEnglish, MinTwoChars))
BidirEnglish.minimize()

# Next we print all strings recognized by =BidirPaths= and construct a stream
# of transducers where each transducer contains one string recognized
# by =BidirPaths=. Then we create a corresponding stream of reversed transducers and
# conjunct the streams. The resulting stream will contain transducers that
# represent a palindrom (e.g. "madam") and empty transducers (e.g. the transducers
# resulting from the intersection of "dog" and "god" and vice versa).

bidir_paths = BidirEnglish.extract_paths()
Result = hfst.empty_fst()
for path in bidir_paths:
    tr1 = hfst.fst(path)
    tr2 = tr1.copy()
    tr2.reverse()
    tr2.minimize()
    TR = hfst.intersect((tr1, tr2))
    Result.disjunct(TR)

Result.minimize()
Result.write_to_file('Result')


