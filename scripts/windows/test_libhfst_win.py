import libhfst

print('')
print('Creating a word list foo::2, bar::3.5, baz::0')
print('')
tr = libhfst.word_list([
('foo',2),
('bar',3.5),
('baz',)])
print(tr)

print('')
print('Creating a word pair list foo:FOO::2, bar:BAR::3.5, baz:baz::0')
print('')
tr = libhfst.word_pair_list([
('foo','FOO',2),
('bar','BAR',3.5),
('baz','baz')])
print(tr)

print('')
print('Testing lookup')
print('')
holps = tr.lookup_fd('foo', 5)
for path in holps:
	print('weight\toutput')
	print(path[0],end='')
	print('\t',end='')
	print(path[1])
	print()

#print('Testing libhfst module...')

#import libhfst

#print(libhfst.fst_type_to_string(libhfst.get_default_fst_type()))

#print(libhfst.fst('foo'))
#print(libhfst.fst('foo', 'bar'))
#print(libhfst.regex('[f o o]:[b a r]'))
#print(libhfst.word('foo'))
#print(libhfst.word_pair('foo', 'bar'))

#print(libhfst.word_list(['foo', 'bar', 'baz']))
#spv = libhfst.StringPairVector((('foo', 'bar'), ('bar', 'baz'), ('foo', 'foo')))
#print(libhfst.word_pair_list(spv))

#tr1 = libhfst.HfstTransducer('foo', 'bar', libhfst.TROPICAL_OPENFST_TYPE)
#tr2 = libhfst.HfstTransducer('bar', 'baz', libhfst.TROPICAL_OPENFST_TYPE)

#tr1.concatenate(tr2)
#print(tr1)
#print('--')
#print(tr2)

#print('Tests passed.')
