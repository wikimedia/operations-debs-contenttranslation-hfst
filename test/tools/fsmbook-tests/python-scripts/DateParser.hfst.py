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

# Numbers from one to nine.
regex('OneToNine', '[1|2|3|4|5|6|7|8|9]')
regex('ZeroToNine', '["0"|OneToNine]')
regex('Even', '[{0} | 2 | 4 | 6 | 8]')
regex('Odd', '[1 | 3 | 5 | 7 | 9]')
regex('Number', '[Even | Odd]')


# Days of the week.
regex('Day', '[{Monday} | {Tuesday} | {Wednesday} | {Thursday} | {Friday} | {Saturday} | {Sunday}]')

# A special month that usually has only 28 days.
regex('Month29', '{February}')
# Months that have 30 days.
regex('Month30', '[{April} | {June} | {September} | {November}]')
# Months that have 31 days.
regex('Month31', '[{January} | {March} | {May} | {July} | {August} | {October} | {December}]')
# All months.
regex('Month', '[Month29 | Month30 | Month31]')


# Numbers from 1 to 31
regex('Date', '[OneToNine | [1 | 2] ZeroToNine | 3 [%0 | 1]]')

# Numbers from 1 to 9999

#regex('Year', '[OneToNine ZeroToNine^<4]')
#hfst-repeat -t 3 ZeroToNine | hfst-concatenate -1 OneToNine > Year;
regex('Year', '[OneToNine [ZeroToNine]^<4]')
  
# Day or [Month and Date] with optional Day and Year
# define AllDates [Day | (Day {, }) Month { } Date ({, } Year)];
regex('AllDates', '[Day | (Day {, }) Month { } Date ({, } Year)]')


# Constraints on dates 30 and 31
regex('MaxDays30', '~$[Month29 { 30}]')
regex('MaxDays31', '~$[[Month29 | Month30] { 31}]')

# Combining constraints on dates 30 and 31
regex('MaxDays', '[MaxDays30 & MaxDays31]')




# Divisible by 4
# Of single digit numbers, 4 and 8 are divisible by 4.
# In larger numbers divisible with 4, if the penultimate
# is even, the last number is 0, 4, or 8. If the penultimate
# is odd, the last number is 2 or 6.
regex('Div4', '[4 | 8 | Number* [Even [%0 | 4 | 8] | Odd [2 | 6]]]')


# Leap years are divisible by 4 but we subtract centuries
# that are not divisible by 400. Note the double
# subtraction. [[N+ - Div4] {00}] includes 1900 but not 2000.
regex('LeapYear', '[Div4 - [[Number+ - Div4] {00}]]')

# Note the [.#. | \N] at the end of the right context.
# 2405 is not a leap year although the year 240 was (in principle).
regex('LeapDates', '{February 29, } => _ LeapYear [.#. | \\Number ]')

regex('ValidDates', '[AllDates & MaxDays & LeapDates]')

Result = regex(None, '[ValidDates @-> "<DATE>" ... "</DATE>"]')
Result.write_to_file('Result')
