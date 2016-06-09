======================================
 Formats for representing transducers
======================================

HFST can read and write transducers in various formats, this page describes
the formats that can be used by various HFST tools and programs as well as
libraries.

The transducer binary formats supported are determined by the
underlying libraries included in libhfst, if openfst is included all openfst
formats are read into hfst transducers etc. The HFST tools by default write
HFST container format (akin to AVI for video formats), which includes header
identifying transducer type before the binary data.

The tabular text formats the library supports reading the format used in
OpenFst tools, with tab separated values and different amount of fields per
line for final states, transitions, weights and so on. The path transducers
can be represented by different finite UTF-8 encoded strings. HFST tools
support only Xerox dialect of regular expressions.

Binary formats
--------------

The HFST3 binary format starts with signature HFST3\0, which can be used for
file type detection. Next is is zero terminated identification string, followed
by header(?). After this comes the binary data as it is handled by underlying
library. HFST3 also supports files without header, then it tries its best to
guess the underlying format, but this is not always possible. To remove HFST3
headers in order to use the transducer with non-hfst tools, utilities like
hfst-strip-header or hfst-convert may be used.

Tabular formats
---------------

The supported tabular format is OpenFst's fstcompile format, it consists of
tab separated lines. The meaning of line depends on number of fields:

1. final state: state number

2. weighted final state: state number and weight

3. not used

4. unweighted transition: start state number, end state number, input symbol
   identifier and output symbol identifier

5. weighted transition: start state number, end state number, input symbol
   identifier, output symbol identifier, weight

State number is a long integer, identifier is a UTF-8 string and weight is a
decimal number.

String formats
--------------

The supported string formats for defining paths in two-tape automata are plain
strings (identity path), sfst style strings of character pairs, space separated
strings of characters or pairs, and lexc style pair of strings. The level
separator is always a colon. The weights are not supported for string formatted
paths(?).  For example:

+------------------------------------------+--------------+------------------+-----------------------+---------------+
| Transducer form                          | plain string | SFST string      | space separated       | string pair   |
+==========================================+==============+==================+=======================+===============+
| 3 transitions: c:c,a:a,t:t               | cat          | cat (c:ca:at:t)  | c a t (c:c a:a t:t)   | cat (cat:cat) |
+------------------------------------------+--------------+------------------+-----------------------+---------------+
| 3 transitions: C:c,A:a,T:t               | n/a          | C:cA:aT:t        | C:c A:a T:t           | CAT:cat       |
+------------------------------------------+--------------+------------------+-----------------------+---------------+
| 4 transitions: c:c,a:a,t:t,+pl:s         | n/a          | cat+pl:s         | c a t +pl:s           | cat+pl:cats   |
+------------------------------------------+--------------+------------------+-----------------------+---------------+
| 7 transitions: m:m,o:i,u:0,s:c,e:e,+pl:0 | n/a          | mo:iu:0s:ce+pl:0 | m o:i u:0 s:c e +pl:0 | mouse+pl:mice |
+------------------------------------------+--------------+------------------+-----------------------+---------------+

Regular expression formats
--------------------------

The regular expression formats to support two tape automata are not many; from
these HFST supports Xerox style in few applications and SFST style in few
others. Xerox style is detailed in the book, SFST style is mostly POSIX extended
with additional use of colon for writing up two-levels.
