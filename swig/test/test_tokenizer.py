import libhfst


# From one string

print("Tokenization from one string with multichar symbol 'foo' and skip symbol 'bar'")

tok1 = libhfst.HfstTokenizer()
tok1.add_multichar_symbol("foo")
tok1.add_skip_symbol("bar")
tokenization1 = tok1.tokenize("fobaro")
assert(len(tokenization1) == 3)
assert(tokenization1[0] == ("f","f"))
assert(tokenization1[1] == ("o","o"))
assert(tokenization1[2] == ("o","o"))

print("Tokenization from one string with multichar symbol 'foo' and skip symbol 'fo'")

tok2 = libhfst.HfstTokenizer()
tok2.add_multichar_symbol("foo")
tok2.add_skip_symbol("fo")
tokenization2 = tok2.tokenize("foo")
assert(len(tokenization2) == 1)
assert(tokenization2[0] == ("foo","foo"))

print("Tokenization from one string with multichar symbol 'fo' and skip symbol 'foo'")

tok3 = libhfst.HfstTokenizer()
tok3.add_multichar_symbol("fo")
tok3.add_skip_symbol("foo")
tokenization3 = tok3.tokenize("foo")
assert(len(tokenization3) == 0)


# From two strings

print("Tokenization from two strings with multichar symbol 'foo' and skip symbol 'bar'")

tok4 = libhfst.HfstTokenizer()
tok4.add_multichar_symbol("foo")
tok4.add_skip_symbol("bar")
tokenization4 = tok4.tokenize("fooba", "foobar")
assert(len(tokenization4) == 3)
assert(tokenization4[0] == ("foo","foo"))
assert(tokenization4[1] == ("b","@_EPSILON_SYMBOL_@"))
assert(tokenization4[2] == ("a","@_EPSILON_SYMBOL_@"))


# Utf-8 correctness testing
utf8_tokenizer = libhfst.HfstTokenizer()

# Positive cases

# Empty string
try:
    utf8_tokenizer.check_utf8_correctness("")
except: # (libhfst.IncorrectUtf8CodingException):
    assert(False)

# ASCII string "ab"
try:
    utf8_tokenizer.check_utf8_correctness("ab")
except: # (libhfst.IncorrectUtf8CodingException):
    assert(False)

# The rest of the tests don't work yet
# TODO: find out how to convert binary data into strings
exit(0)

# Four byte, three byte, two byte and single byte sequence
#print("Case: 11110000, 10000000, 10000000, 10000000")
#print("11100000, 10000000, 10000000, 11010000, 10000000")
#print("01000000")

try:
    utf8_tokenizer.check_utf8_correctness(b"11110000"b"10000000"b"10000000"b"10000000"b"11100000"b"10000000"b"10000000"b"11010000"b"10000000"b"01000000")
except: # (libhfst.IncorrectUtf8CodingException):
    assert(False)


# Negative Cases

# String with byte 192
try:
    utf8_tokenizer.check_utf8_correctness(b"0b11000000"b"0b10000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# String with byte 193
try:
    utf8_tokenizer.check_utf8_correctness(b"11000001"b"10000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# String with byte 245
try:
    utf8_tokenizer.check_utf8_correctness(b"11110101"b"10000000"b"10000000"b"10000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# String with byte 246
try:
    utf8_tokenizer.check_utf8_correctness(b"11110110"b"10000000"b"10000000"b"10000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# String with byte 247
try:
    utf8_tokenizer.check_utf8_correctness(b"11110111"b"10000000"b"10000000"b"10000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# ASCII character followed by a continuation character
try:
    utf8_tokenizer.check_utf8_correctness(b"01000000"b"10000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# 11010000 followed by ASCII character
try:
    utf8_tokenizer.check_utf8_correctness(b"11010000"b"01000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# 11100000 followed by one continuation character and an ASCII character
try:
    utf8_tokenizer.check_utf8_correctness(b"11100000"b"10000000"b"01000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# 11110000 followed by two continuation characters and an ASCII character
try:
    utf8_tokenizer.check_utf8_correctness(b"11110000"b"10000000"b"10000000"b"01000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# 11110000 followed by two continuation characters and an ASCII character
try:
    utf8_tokenizer.check_utf8_correctness(b"11110000"b"10000000"b"10000000"b"01000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass

# 11110000 followed by two continuation characters and 1101000010000000
try:
    utf8_tokenizer.check_utf8_correctness(b"11110000"b"10000000"b"10000000"b"11010000"b"10000000")
    assert(False)
except: # (libhfst.IncorrectUtf8CodingException):
    pass
