exec(compile(open('CompileOptions.py', 'rb').read(), 'CompileOptions.py', 'exec'))

comp = hfst.XreCompiler(hfst.get_default_fst_type())

def regex(name, expression):
    tr = comp.compile(expression)
    if name == None:
        return tr
    else:
        comp.define_transducer(name, tr)                

# From one to nine.

OneToNine = hfst.fst({'1':'one',
                      '2':'two',
                      '3':'three',
                      '4':'four',
                      '5':'five',
                      '6':'six',
                      '7':'seven',
                      '8':'eight',
                      '9':'nine'})

# Numbers to prefixes that can preceed "-teen" or "-ten".

TeenTen = hfst.fst({'3':'thir',
                    '5':'fif',
                    '6':'six',
                    '7':'seven',
                    '8':'eigh',
                    '9':'nine'})

# Special numbers.

Special = hfst.fst({'10':'ten',
                    '11':'eleven',
                    '12':'twelve',
                    '14':'fourteen'})

# Here we handle ordinary teens and disjunct them with the special numbers.

Epsilon2Teen = hfst.fst({'':'teen'})
One2Epsilon = hfst.fst({'1':''})
Teens_ = hfst.concatenate((One2Epsilon, TeenTen, Epsilon2Teen))
Teens = hfst.disjunct((Special, Teens_))

# Special stems.

TenStem = hfst.disjunct((hfst.fst({'2':'twen', '4':'for'}), TeenTen))

# TenStem is followed either by "ty" paired with a zero or by "ty-" mapped to an epsilon and followed by one number.

TMP = hfst.concatenate((hfst.fst({'':'ty-'}), OneToNine))
Tens = hfst.concatenate((TenStem, hfst.disjunct((hfst.fst({'0':'ty'}), TMP))))

# We finally disjunct all numbers.

Result = hfst.disjunct((OneToNine, Teens, Tens))
Result.minimize()
Result.write_to_file('Result')
