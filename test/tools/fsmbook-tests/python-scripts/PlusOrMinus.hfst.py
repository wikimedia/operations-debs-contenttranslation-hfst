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

regex('N', '[1|2|3|4|5|6|7|8|9]')
regex('Z', '["0" | N]')

# Insert an initial 1 in front of a sequence of zeros. To make
# this relation functional in both directions, we need two
# replace expressions. One introduces 1, the other removes 1.
# The composition of the two is a relation that uniquely maps,
# for example, 100 to 99 and, conversely, 99 to 100.

regex('CarryUp', '[ 1 <- [. .] || .#. _ "0"+ .#. ] .o.  [ 1 -> 0 || .#. _ "0"+ .#. ]')

regex('AddUp', ' [ 1 <- "0", 2 <- 1, 3 <- 2, 4 <- 3,  5  <- 4, 6 <-  5 , 7 <- 6, 8 <- 7, 9 <- 8, "0" <- 9 || .#. ("+") Z* _ 9* .#. ]')

regex('NoLeadingZero', ' [ "0" => .#. N Z* _ , .#. _ .#. ]')

# PlusOrMinusOne.hfst maps any natural number N to (N-1), and vice versa.

regex('PlusOrMinusOne', 'CarryUp .o. AddUp .o. NoLeadingZero')
regex('PlusOrMinusTwo', 'PlusOrMinusOne .o. PlusOrMinusOne')
regex('PlusOrMinusThree', 'PlusOrMinusTwo .o. PlusOrMinusOne')
regex('PlusOrMinusFour', 'PlusOrMinusThree .o. PlusOrMinusOne')
regex('PlusOrMinusFive', 'PlusOrMinusFour .o. PlusOrMinusOne')
regex('PlusOrMinusSix', 'PlusOrMinusFive .o. PlusOrMinusOne')
regex('PlusOrMinusSeven', 'PlusOrMinusSix .o. PlusOrMinusOne')
regex('PlusOrMinusEight', 'PlusOrMinusSeven .o. PlusOrMinusOne')
regex('PlusOrMinusNine', 'PlusOrMinusEight .o. PlusOrMinusOne')
regex('PlusOrMinusTen', 'PlusOrMinusNine .o. PlusOrMinusOne')

ostr = hfst.HfstOutputStream(filename='Result')
for i in ('One', 'Two', 'Three', 'Four', 'Five', 'Six', 'Seven', 'Eight', 'Nine', 'Ten'):
    ostr.write(regex(None, 'PlusOrMinus' + i))
ostr.flush()
ostr.close()
