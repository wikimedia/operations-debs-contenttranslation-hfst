#! /bin/sh
# -*- coding: utf-8 -*-

TOOLDIR=../../tools/src
if [ "$srcdir" = "" ] ; then
    srcdir=. ;
fi

. $srcdir/pmatch-tester.sh


testset_begin "Testing Pmatch"

set_runner_opts -n


# Compilation

test_begin "Compilation"

# Bug (reported 2013-01-14): A commented-out definition caused a
# compilation error

check_compile "Commented-out definition" \
    '! Define foo bar;
Define TOP "foo";'

# Bug (reported 2013-01-22)

check_compile 'Comment at the end of file' \
    'Define TOP "foo";
! comment'

check_compile 'Semicolon in the middle of a comment' \
    '! foo; bar
Define TOP "foo";'

# Bug/feature (reported 2013-01-22)

check_compile_run 'Define name containing a 0' \
    'Define T0 [Alpha+ EndTag(A)]; Define TOP T0;' \
    '0abc1' '0<A>abc</A>1'


# Bug (reported 2013-02-05)

test_begin "String literal memory allocation"

for s in "xxxxxxxxxxxxxxxxxxxxxxxx" "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; do
    check_compile "String literal $s" 'Define TOP {'$s'};'
done


# Bug (reported 2013-01-22)

test_begin 'Semicolons'

check_compile_run \
    --codetempl 'Define TOP @1@ EndTag(X);' \
    --descrtempl 'Semicolon to be marked: @1@' \
    --templarg-single '[{;}]' '({;})' '{;}' '";"' '%;'\
    --inout '' 'a;b' 'a<X>;</X>b'


# Missing feature (reported 2013-01-23)

test_begin "Any character except in a set"

check_compile_run \
    --codetempl 'Define TOP @1@ EndTag(A);' \
    --descrtempl 'Any except Whitespace: @1@' \
    --templarg-single '[\Whitespace]+' '[? - Whitespace]+' \
    --inout '' 'ab c  de' '<A>ab</A> <A>c</A>  <A>de</A>'


# Bug (reported 2013-01-22)

test_begin "Referring to a double quote in a regexp"

check_compile_run \
    --codetempl 'Define TOP @1@ EndTag(Q);' \
    --descrtempl 'Double quote as @1@' \
    --templarg-single '"\x22"' '"\""' '{"}' '%"' \
    --inout '' 'a "b" c' 'a <Q>"</Q>b<Q>"</Q> c'


# Bug (reported 2013-01-14): RC() required a character between
# recognized string and context

test_begin "RC() with no character between the recognized string and context"

check_compile_run 'RC() separating space' \
    'Define TOP {a} RC({b}) EndTag(AB);' 'aba b' '<AB>a</AB>ba b'


# Bug (reported 2013-05-30): Ins() with a name containing "name" does
# not work

test_begin "Ins() with defined names containing 'name'"

check_compile_run \
    --codetempl 'Define @1@ [ Alpha+ ] EndTag(A) ;
Define TOP [ Ins(@1@) ] ;' \
    --descrtempl 'Ins(@1@)' \
    --templarg-single name Enamex Name nam ame \
    --inout '' 'abc' '<A>abc</A>'


# Missing feature (reported 2013-01-14)

test_begin "Different tag in different contexts"

check_compile_run '' \
    'Define TOP {a} [[RC({b}) EndTag(AB)] | [RC({c}) EndTag(AC)]];' \
    'ab ac' '<AB>a</AB>b <AC>a</AC>c'


# Not a bug (reported 2013-01-15; Sam clarified 2013-08-16)

test_begin "Multiple EndTags in a single define"

check_compile_run \
    --code 'EndTag, string, EndTag' \
    'Define TOP Define( [{a} EndTag(A)] ) {bcd} Define( [{e} EndTag(B)] );' \
    --code 'EndTag+RC, any, EndTag' \
    'Define TOP Define( [{a} EndTag(A) RC({bcd})] ) ?* Define( [{e} EndTag(B)] );' \
    --code 'EndTag, any, LC+EndTag' \
    'Define TOP Define( [{a} EndTag(A)] ) ?* Define( [{e} EndTag(B) LC({bcd})] );' \
    --code 'EndTag+RC, any, LC+EndTag' \
    'Define TOP Define( [{a} EndTag(A) RC({bc})] ) ?* Define( [{e} EndTag(B) LC({d})] );' \
    --code 'EndTag+RC, any, string, any, LC+EndTag' \
    'Define TOP Define( [{a} EndTag(A) RC({b})] ) ?* {c} ?* Define( [{e} EndTag(B) LC({d})] );' \
    --code 'EndTag+RC, any, string, EndTag' \
    'Define TOP Define( [{a} EndTag(A) RC({b})] ) ?* {cd} Define( [{e} EndTag(B)] );' \
    --code 'EndTag, string, any, EndTag+LC' \
    'Define TOP Define( [{a} EndTag(A)] ) {bc} ?* Define( [{e} EndTag(B) LC({d})] );' \
    --code 'EndTag+RC, any, EndTag+LC, RC+LC overlapping' \
    'Define TOP Define( [{a} EndTag(A) RC({bc})] ) ?* Define( [{e} EndTag(B) LC({cd})] );' \
    --code 'EndTag+RC, any, EndTag+LC, RC+LC equal coverage' \
    'Define TOP Define( [{a} EndTag(A) RC({bcd})] ) ?* Define( [{e} EndTag(B) LC({bcd})] );' \
    --inout 'No matches' 'ab' 'ab' \
    --inout 'Two matches' 'abcde' '<A>a</A>bcd<B>e</B>'

# Bug? (reported 2013-01-15)

test_begin "Removing tags by using transductions"

in='X <A>y</A>'
out='<X>X y</X>'

check_compile_run \
    --codetempl 'Define TOP {X } [{<A>} -> 0] @1@+ [{</A>} -> 0] EndTag(X);' \
    --descrtempl 'Remove tags (@1@)' \
    --templarg-single Alpha LowercaseAlpha \
    --inout '' "$in" "$out"

check_compile_run 'Remove tags only if they exist (Alpha)' \
    'Define TOP {X } [{<A>} .o. [{<A>} -> 0]] Alpha+ [{</A>} .o. [{</A>} -> 0]] EndTag(X);' \
    "$in" "$out"


# Bug (reported 2013-02-07)

test_begin "Order of contexts and EndTag"

check_compile_run \
    --codetempl 'Define TOP [ Alpha+ @1@ ] ;' \
    --templarg-single \
    'Simple, LC before EndTag' 'LC({ }) EndTag(A)' \
    'Simple, LC after EndTag' 'EndTag(A) LC({ })' \
    --inout 'No matches' 'abc' 'abc' \
    --inout 'Single match' 'a abc' 'a <A>abc</A>'

check_compile_run \
    --codetempl 'Define T1 [ Num [{ } Num]* @1@ EndTag(A) @2@ ] ;
Define T2 [ {xx} [{ } Alpha+]+ EndTag(A) @3@ ] ;
Define TOP [ [T1 | T2] LC({ }) ] ;' \
    --templargs 'Two-level, LC before EndTag' 'LC({ })' '' '' \
    --templargs 'Two-level, LC after EndTag' '' 'LC({ })' '' \
    --templargs 'Two-level, same context in TOP' '' 'LC({ })' 'LC({ })' \
    --templargs 'Context only in TOP' '' '' '' \
    --inout 'No matches' 'a abc def' 'a abc def' \
    --inout 'First rule matches' '1 2 3' '1 <A>2 3</A>' \
    --inout 'Second rule matches' 'a xx abc def' 'a <A>xx abc def</A>'

check_compile_run \
    --codetempl 'Define T [ Alpha+ EndTag(A) ] ;
Define TOP [ T::1 | [T @1@] ] ;' \
    --templargs 'LC before EndTag' 'LC({ }) EndTag(B)' \
    --templargs 'LC after EndTag' 'EndTag(B) LC({ })' \
    --inout 'Three-character match' 'abc' '<A>abc</A>' \
    --inout 'Single-character match' 'a' '<A>a</A>' \
    --inout 'Space-separated matches' 'ab abc' '<A>ab</A> <B><A>abc</A></B>' \
    --inout 'Dot-separated matches' 'ab.cd.ef' '<A>ab</A>.<A>cd</A>.<A>ef</A>' \
    --inout 'Dot-separated single-character matches' 'a.b.c' '<A>a</A>.<A>b</A>.<A>c</A>'


# Bug (reported 2013-02-07)

test_begin "Variable-length right context"

check_compile_run \
    --codetempl 'Define TOP [ Alpha+ @1@ ] ;' \
    --templargs 'RC before EndTag, star' 'RC({ } Alpha*) EndTag(A)' \
    --templargs 'RC before EndTag, plus' 'RC({ } Alpha+) EndTag(A)' \
    --templargs 'RC after EndTag, star' 'EndTag(A) RC({ } Alpha*)' \
    --templargs 'RC after EndTag, plus' 'EndTag(A) RC({ } Alpha+)' \
    --inout 'Two matching words' 'abc def ghi' '<A>abc</A> <A>def</A> ghi' \
    --inout 'One matching word' 'abc defghi' '<A>abc</A> defghi' \


# Bug (reported 2013-02-11)

test_begin "A context as an affix of another"

check_compile_run \
    --codetempl 'Define T1 [ {c} @1@ EndTag(A) ];
Define T2 [ {d} LC({b}) EndTag(A) ];
Define TOP [ T1 | T2 ];' \
    --templargs 'Same context (LC)' 'LC({b})' \
    --templargs 'Context as a suffix of another (LC)' 'LC({ab})' \
    --inout 'Longer context matches' 'abc' 'ab<A>c</A>' \
    --inout 'Only short context matches' 'abd' 'ab<A>d</A>'

check_compile_run \
    --code 'Non-affix contexts' \
'Define T1 [ {c} LC({a}) EndTag(A) ];
Define T2 [ {d} LC({b}) EndTag(A) ];
Define TOP [ T1 | T2 ];' \
    --inout 'First matches' 'bac' 'ba<A>c</A>' \
    --inout 'Second matches' 'abd' 'ab<A>d</A>'

check_compile_run \
    --code 'Context as a prefix of another (RC)' \
'Define T1 [ {c} EndTag(A) RC({ba}) ];
Define T2 [ {d} EndTag(A) RC({b}) ];
Define TOP [ T1 | T2 ];' \
    --inout 'Longer context matches' 'cba' '<A>c</A>ba' \
    --inout 'Only short context matches' 'dba' '<A>d</A>ba'


# Bug (reported 2013-02-12)

test_begin "Fix of a bug causing segmentation faults"

check_compile_run \
    --code 'No errors' 'Define TOP {a} EndTag(A);' \
    --inout 'Single character (ok)' 'a' '<A>a</A>' \
    --inout 'Two characters, single match (ok)' 'ab' '<A>a</A>b'

check_compile_run \
    --code 'Errors with EndTag' 'Define TOP {a}+ EndTag(A);' \
    --inout 'Single non-match character (ok)' 'b' 'b' \
    --inout 'Single character match (segfault)' 'a' '<A>a</A>'

check_compile_run \
    --code 'Errors without EndTag' 'Define TOP {a}+;' \
    --inout 'Single character' 'b' 'b' \
    --inout 'Single character (segfault)' 'a' 'a'


# Bug (reported 2013-02-12)
# This is probably an instance of the bug "adding characters with
# replacement" below.

test_begin "Converting tags with replacement"

code_preamble='Define AlphaToUpper
    ["a":"A" | "b":"B" | "c":"C" | "d":"D" | "e":"E" | "f":"F" | "g":"G" |
     "h":"H" | "i":"I" | "j":"J" | "k":"K" | "l":"L" | "m":"M" | "n":"N" |
     "o":"O" | "p":"P" | "q":"Q" | "r":"R" | "s":"S" | "t":"T" | "u":"U" |
     "v":"V" | "w":"W" | "x":"X" | "y":"Y" | "z":"Z" | UppercaseAlpha] ;
Define AlphaToUpper3 [AlphaToUpper AlphaToUpper AlphaToUpper] ;
Define MainTagName [{ENAMEX} | {NUMEX} | {TIMEX}] ;
Define ConvertStartTag [{<} MainTagName
			 [[] -> { TYPE=" }] AlphaToUpper3
			 [[] -> {" SBT="}] AlphaToUpper3
			 [[] -> {"}] {>}] ;
Define ConvertEndTag [{</} MainTagName [Alpha+ .o. [Alpha+ -> []]] {>}] ;'

in='<ENAMEXPrsHum>Johan</ENAMEXPrsHum>'

check_compile_run \
    --code 'Convert start tag only' \
    "$code_preamble
Define TOP ConvertStartTag;" \
    --inout '' "$in" '<ENAMEX TYPE="PRS" SBT="HUM">Johan</ENAMEXPrsHum>'

check_compile_run \
    --code 'Convert end tag only' \
    "$code_preamble
Define TOP ConvertEndTag;" \
    --inout '' "$in" '<ENAMEXPrsHum>Johan</ENAMEX>'

check_compile_run \
    --code 'Convert both start and end tag' \
    "$code_preamble
Define TOP [ConvertStartTag | ConvertEndTag] ;" \
    --inout '' "$in" '<ENAMEX TYPE="PRS" SBT="HUM">Johan</ENAMEX>'


# Missing feature (reported 2013-02-12)

test_begin "Regex^n"

check_compile_run \
    --code 'Regex^n' 'Define TOP {a}^3 EndTag(A);' \
    --inout 'No match' 'a' 'a' \
    --inout 'One match' 'aaa' '<A>aaa</A>' \
    --inout 'Two matches' 'aaaaaa' '<A>aaa</A><A>aaa</A>'

check_compile_run \
    --codetempl 'Define TOP {a}@1@ EndTag(A);' \
    --descrtempl '@1@' \
    --templarg-single '^2,4' '^{2,4}' \
    --inout 'No match' 'a' 'a' \
    --inout 'One match (min)' 'aa' '<A>aa</A>' \
    --inout 'One match (mid)' 'aaa' '<A>aaa</A>' \
    --inout 'One match (max)' 'aaaa' '<A>aaaa</A>' \
    --inout 'One match (max) + non-match' 'aaaaa' '<A>aaaa</A>a' \
    --inout 'Two matches' 'aaaaaa' '<A>aaaa</A><A>aa</A>'

check_compile_run \
    --code 'Regex^<n' 'Define TOP {a}^<3 EndTag(A);' \
    --inout 'One match 1' 'a' '<A>a</A>' \
    --inout 'One match 2' 'aa' '<A>aa</A>' \
    --inout 'Two matches' 'aaa' '<A>aa</A><A>a</A>' \

check_compile_run \
    --code 'Regex^>n' 'Define TOP {a}^>3 EndTag(A);' \
    --inout 'No match 3' 'aaa' 'aaa' \
    --inout 'Match 4' 'aaaa' '<A>aaaa</A>' \
    --inout 'Match 5' 'aaaaa' '<A>aaaaa</A>'


# Bug (reported 2013-02-12)

test_begin "Character literal escapes"

# Unicode escapes \uHHHH and octal escapes \0OOO not implemented in
# Pmatch

check_compile_run \
    --codetempl 'Define TOP [@1@ EndTag(A)];' \
    --descrtempl 'Matching @1@' \
    --templarg-single '"\x65"' \
    --inout '' 'ABCDEabcde' 'ABCDEabcd<A>e</A>'

check_compile_run \
    --codetempl 'Define TOP [{a} -> @1@];' \
    --descrtempl 'Replacement @1@' \
    --templarg-single '"\x65"' \
    --inout '' 'a' 'e'


# Bug (reported 2014-10-03) and features

test_begin "Backslash in string literals"

# In string literals {...}, backslash escapes } and itself, otherwise
# it is literal.

# Use printf here, since the processing of \ varies between shells;
# thus, double all backslashes to that should be literal for printf,
# and add an explicit trailing newline (\n) to the expected output.
check_compile_run \
    --printf \
    --codetempl 'Define TOP [{@1@} EndTag(A)];' \
    --input '\t\\t\\x65\\}' \
    --outtemplargs 'Backslash escapes }' '\t\\t\\x65\\<A>}</A>\n' '\\}' \
    --outtemplargs 'Literal backslash: @1@' '\t<A>\\t</A>\\x65\\}\n' '\\t' \
    --outtemplargs 'Literal backslash: @1@' '\t\\t<A>\\x65</A>\\}\n' '\\x65' \
    --outtemplargs 'Literal backslash: @1@' '\t<A>\\</A>t<A>\\</A>x65<A>\\</A>}\n' '\\\\' \
    --outtemplargs 'Literal backslash followed by }' '\t\\t\\x65<A>\\}</A>\n' '\\\\\\}'


# Bug (reported 2013-02-22)

test_begin "Input boundary"

check_compile_run \
    --code 'Input boundary' \
    'Define TOP [ [# {a} | {b} # | [{c} LC(#)] | [{d} RC(#)]] EndTag(A) ];' \
    --inout 'Beginning' 'a x' '<A>a</A> x' \
    --inout 'End' 'x b' 'x <A>b</A>' \
    --inout 'LC' 'c x' '<A>c</A> x' \
    --inout 'RC' 'x d' 'x <A>d</A>'


# Bug/feature (reported 2013-02-22)

test_begin "Replace semantics"

check_compile_run \
    --codetempl 'Define TOP [ [{a}+ {b}+] @1@ {X} ];' \
    --input 'aabb' \
    --outtemplargs 'Bare replacement ->' 'Xb' '->' \
    --outtemplargs 'Leftmost longest replacement @->' 'X' '@->' \
    --outtemplargs 'Leftmost shortest replacement @>' 'Xb' '@>' \
    --outtemplargs 'Rightmost longest replacement ->@' 'X' '->@' \
    --outtemplargs 'Rightmost shortest replacement >@' 'aX' '>@'


# Bug (reported 2013-02-22)

test_begin "Add characters with replacement or transduction"

check_compile_run \
    --codetempl 'Define TOP [ {<} Alpha+ [@1@ -> {>}] ] ;' \
    --descrtempl 'Replacing @1@' \
    --templarg-single '""' '[..]' \
    --inout 'Non-match' '<1' '<1' \
    --inout 'One Alpha' '<a' '<a>' \
    --inout 'Two Alphas' '<aa' '<aa>' \
    --inout 'Three consecutive Alphas' '<aaa' '<aaa>' \
    --inout 'Three separate occurrences' '<aa b <aa' '<aa> <b> <aa>' \
    --inout 'Occurrences separated by a colon' '<aa:<aa' '<aa>:<aa>' \
    --inout 'Consecutive occurrences' '<aaa<aaa<aaa' '<aaa><aaa><aaa>'

check_compile_run \
    --codetempl 'Define TOP [ {<} Alpha+ [@1@ -> {>}] {::} ] ;' \
    --descrtempl 'Replacing @1@, characters after replacement' \
    --templarg-single '""' '[..]' \
    --inout 'Non-match prefix' '<1::' '<1::' \
    --inout 'No matching suffix' '<aa' '<aa' \
    --inout 'One occurrence' '<aa::<aa' '<aa>::<aa' \
    --inout 'Two occurrences, separated' '<aa:: <aa::' '<aa>:: <aa>::' \
    --inout 'Two occurrences, consecutive' '<aa::<aa::' '<aa>::<aa>::' \
    --inout 'Three replacements, consecutive' '<aaa::<aaa::<aaa::' '<aaa>::<aaa>::<aaa>::'

check_compile_run \
    --codetempl 'Define TOP [{<} Alpha+ @2@ {>}] ;' \
    --descrtempl 'Single character after replacement, @1@' \
    --templargs 'replacing ""' '["" -> {x}]' \
    --templargs 'replacing [..]' '[[..] -> {x}]' \
    --templargs 'transduction from 0' '0:"x"' \
    --inout '' '<AB>B</AB>' '<ABx>B</AB>'

check_compile_run \
    --codetempl 'Define TOP [[{<} Alpha+ @2@ {>}] | [{</} Alpha+ {>}]] ;' \
    --descrtempl 'Single character after replacement, disjunction, @1@' \
    --templargs 'replacing ""' '["" -> {x}]' \
    --templargs 'replacing [..]' '[[..] -> {x}]' \
    --templargs 'transduction from 0' '0:"x"' \
    --inout '' '<AB>B</AB>' '<ABx>B</AB>'

check_compile_run \
    --code 'Transduction' 'Define TOP [ {<} Alpha+ 0:">" ] ;' \
    --inout 'Non-match' '<1' '<1' \
    --inout 'Single 1-char occurrence' '<a' '<a>' \
    --inout 'Single 3-char occurrence' '<aaa' '<aaa>' \
    --inout 'Two 2-char occurrences' '<aa<aa' '<aa><aa>'

check_compile_run \
    --code 'Transduction, suffix required' 'Define TOP [ {<} Alpha+ 0:">" {::} ] ;' \
    --inout 'Non-match prefix' '<1' '<1' \
    --inout 'No matching suffix' '<a' '<a' \
    --inout 'Single 1-char occurrence' '<a::' '<a>::' \
    --inout 'Single 3-char occurrence' '<aaa::' '<aaa>::' \
    --inout 'Two 2-char occurrences' '<aa::<aa::' '<aa>::<aa>::'



# Bug/feature (reported 2013-02-22)

test_begin "Transductions and replacements with EndTag"

check_compile_run \
    --codetempl 'Define TOP [ Alpha+ @1@ EndTag(A) ] ;' \
    --templarg-single 'Transductions' '["1":"X" | "2":"X" | "3":"X"]+' \
    'Composition and replacement' '[Num+ .o. [Num -> {X}]]' \
    --inout 'No match (Alpha)' 'abc' 'abc' \
    --inout 'No match (Num)' '123' '123' \
    --inout 'Single-char transduction' 'abc1' '<A>abcX</A>' \
    --inout 'Three-char transduction' 'abc123' '<A>abcXXX</A>' \
    --inout 'Three-char transduction, followed by non-match' \
    'abc123abc' '<A>abcXXX</A>abc'

check_compile_run \
    --code 'Replacement without composition' \
    'Define TOP [ Alpha+ [Num -> {X}]+ EndTag(A) ] ;' \
    --inout 'Non-replacement only' 'abc' '<A>abc</A>' \
    --inout 'Replacement only' '123' '123' \
    --inout 'Single-char replacement' 'abc1' '<A>abcX</A>' \
    --inout 'Three-char replacment' 'abc123' '<A>abcXXX</A>' \
    --inout 'Two consecutive matches' 'abc123abc' '<A>abcXXX</A><A>abc</A>'

# CHECK: The following outputs are as Pmatch outputs but are they
# correct?
check_compile_run \
    --codetempl 'Define TOP [ [Num -> {X}]@1@ EndTag(A) ] ;' \
    --templargs 'Only replacement in EndTag' '' \
    --templargs 'Only replacement in EndTag, with +' '+' \
    --inout 'Non-match' 'abc' 'abc' \
    --inout 'Non-match + three-char match' 'abc123' 'abc<A>XXX</A>' \
    --inout 'Non-match + single-char match' 'abc1' 'abc<A>X</A>' \
    --inout 'Single-char match between non-matches' 'abc1abc' 'abc<A>X</A>abc' \
    --inout 'Three-char match' '123' '<A>XXX</A>'


# Bug/feature (reported 2013-02-22)

test_begin "Transductions and replacements in EndTag context conditions (unsure about expected output)"

check_compile_run \
    --codetempl 'Define TOP [ Alpha+ LC(@1@) EndTag(A) ] ;' \
    --templargs 'Composition and replacement in LC, plus outside' \
    '[Num .o. [Num -> {X}]]+' \
    --templargs 'Composition and replacement in LC, plus inside' \
    '[Num+ .o. [Num -> {X}]]' \
    --templargs 'Composition and transductions in LC, plus outside' \
    '[Num .o. ["1":"X" | "2":"X" | "3":"X" | "4":"X"]]+' \
    --templargs 'Composition and transductions in LC, plus inside' \
    '[Num+ .o. ["1":"X" | "2":"X" | "3":"X" | "4":"X"]]' \
    --templargs 'Transductions without composition in LC, plus outside' \
    '["1":"X" | "2":"X" | "3":"X" | "4":"X"]+' \
    --templargs 'Transductions without composition in LC, no plus' \
    '["1":"X" | "2":"X" | "3":"X" | "4":"X"]' \
    --inout 'No context match' 'abc' 'abc' \
    --inout '1-char context' '1abc' '1<A>abc</A>' \
    --inout '2-char context' '12abc' '12<A>abc</A>' \
    --inout '3-char context' '123abc' '123<A>abc</A>' \
    --inout '4-char context' '1234abc' '1234<A>abc</A>'

check_compile_run \
    --codetempl 'Define TOP [ Alpha+ LC(@1@) EndTag(A) ] ;' \
    --templargs 'Replacement without composition in LC, plus outside' \
    '[Num -> {X}]+' \
    --templargs 'Replacement without composition in LC, no plus' \
    '[Num -> {X}]' \
    --inout 'No context match' 'abc' '<A>abc</A>' \
    --inout '1-char context' '1abc' '1<A>abc</A>' \
    --inout '2-char context' '12abc' '12<A>abc</A>' \
    --inout '3-char context' '123abc' '123<A>abc</A>' \
    --inout '4-char context' '1234abc' '1234<A>abc</A>'

check_compile_run \
    --codetempl 'Define TOP [ Alpha+ RC(@1@) EndTag(A) ] ;' \
    --templargs 'Composition and replacement in RC, plus outside' \
    '[Num .o. [Num -> {X}]]+' \
    --templargs 'Composition and replacement in RC, plus inside' \
    '[Num+ .o. [Num -> {X}]]' \
    --templargs 'Composition and transductions in RC, plus outside' \
    '[Num .o. ["1":"X" | "2":"X" | "3":"X" | "4":"X"]]+' \
    --templargs 'Composition and transductions in RC, plus inside' \
    '[Num+ .o. ["1":"X" | "2":"X" | "3":"X" | "4":"X"]]' \
    --templargs 'Transductions without composition in RC, plus outside' \
    '["1":"X" | "2":"X" | "3":"X" | "4":"X"]+' \
    --templargs 'Transductions without composition in RC, no plus' \
    '["1":"X" | "2":"X" | "3":"X" | "4":"X"]' \
    --inout 'No context match' 'abc' 'abc' \
    --inout '1-char context' 'abc1' '<A>abc</A>1' \
    --inout '2-char context' 'abc12' '<A>abc</A>12' \
    --inout '3-char context' 'abc123' '<A>abc</A>123' \
    --inout '4-char context' 'abc1234' '<A>abc</A>1234'

check_compile_run \
    --codetempl 'Define TOP [ Alpha+ RC(@1@) EndTag(A) ] ;' \
    --templargs 'Replacement without composition in RC, plus outside' \
    '[Num -> {X}]+' \
    --templargs 'Replacement without composition in RC, no plus' \
    '[Num -> {X}]' \
    --inout 'No context match' 'abc' '<A>abc</A>' \
    --inout '1-char context' 'abc1' '<A>abc</A>1' \
    --inout '2-char context' 'abc12' '<A>abc</A>12' \
    --inout '3-char context' 'abc123' '<A>abc</A>123' \
    --inout '4-char context' 'abc1234' '<A>abc</A>1234'


# Bug/feature (reported 2013-04-15)

test_begin "Tagging with context conditions"

eta="EndTag(A)"
etb="EndTag(B)"
lcws="LC(Whitespace)"
rcws="RC(Whitespace)"

check_compile_run \
    --codetempl 'Define TOP [ [UppercaseAlpha+ @1@] | [LowercaseAlpha+ @2@] ];' \
    --templargs 'No context conditions' "$eta" "$etb" \
    --templargs 'LC before second EndTag' "$eta" "$lcws $etb" \
    --templargs 'LC after second EndTag' "$eta" "$etb $lcws" \
    --templargs 'RC before first EndTag' "$rcws $eta" "$etb" \
    --templargs 'RC after first EndTag' "$eta $rcws" "$etb" \
    --templargs 'RC before second EndTag' "$eta" "$rcws $etb" \
    --templargs 'RC after second EndTag' "$eta" "$etb $rcws" \
    --templargs 'RC before both EndTags' "$rcws $eta" "$rcws $etb" \
    --templargs 'RC after both EndTags' "$eta $rcws" "$etb $rcws" \
    --inout '' 'A BC de .' '<A>A</A> <A>BC</A> <B>de</B> .'

check_compile_run \
    --codetempl 'Define TOP [ [UppercaseAlpha+ @1@] | [LowercaseAlpha+ @2@] ];' \
    --templargs 'LC before first EndTag' "$lcws $eta" "$etb" \
    --templargs 'LC after first EndTag' "$eta $lcws" "$etb" \
    --templargs 'LC before both EndTags' "$lcws $eta" "$lcws $etb" \
    --templargs 'LC after both EndTags' "$eta $lcws" "$etb $lcws" \
    --inout '' 'A BC de .' 'A <A>BC</A> <B>de</B> .'


# Bug/feature (reported 2013-04-15)

test_begin "Tagging with two-level context conditions"

eta="EndTag(A)"
etb="EndTag(B)"
lcws="LC(Whitespace)"
rcws="RC(Whitespace)"

check_compile_run \
    --codetempl 'Define TOP [ [UppercaseAlpha+ @1@] | [LowercaseAlpha+ @2@] ]
LC(Whitespace);' \
    --templargs 'Same LC before first EndTag' "$lcws $eta" "$etb" \
    --templargs 'Same LC after first EndTag' "$eta $lcws" "$etb" \
    --templargs 'Same LC before second EndTag' "$eta" "$lcws $etb" \
    --templargs 'Same LC after second EndTag' "$eta" "$etb $lcws" \
    --templargs 'Same LC before both EndTags' "$lcws $eta" "$lcws $etb" \
    --templargs 'Same LC after both EndTags' "$eta $lcws" "$etb $lcws" \
    --templargs 'LC only on top' "$eta" "$etb" \
    --templargs 'RC after first EndTag, same LC on top' "$eta $rcws" "$etb" \
    --templargs 'RC after second EndTag, same LC on top' "$eta" "$etb $rcws" \
    --inout '' 'A BC de .' 'A <A>BC</A> <B>de</B> .'

check_compile_run \
    --codetempl 'Define TOP [ [UppercaseAlpha+ @1@] | [LowercaseAlpha+ @2@] ]
LC(Whitespace);' \
    --templargs 'Different LC before second EndTag' "$eta" "LC({.}) $etb" \
    --templargs 'Different LC after second EndTag' "$eta" "$etb LC({.})" \
    --inout '' 'A BC de .' 'A <A>BC</A> de .'

check_compile_run \
    --codetempl 'Define TOP [ [UppercaseAlpha+ @1@] | [LowercaseAlpha+ @2@] ]
RC(Whitespace);' \
    --templargs 'Same RC before first EndTag' "$rcws $eta" "$etb" \
    --templargs 'Same RC after first EndTag' "$eta $rcws" "$etb" \
    --templargs 'Same RC before second EndTag' "$eta" "$rcws $etb" \
    --templargs 'Same RC after second EndTag' "$eta" "$etb $rcws" \
    --templargs 'Same RC before both EndTags' "$rcws $eta" "$rcws $etb" \
    --templargs 'Same C after both EndTags' "$eta $rcws" "$etb $rcws" \
    --templargs 'RC only on top' "$eta" "$etb" \
    --inout '' 'A BC de .' '<A>A</A> <A>BC</A> <B>de</B> .'

check_compile_run \
    --codetempl 'Define TOP [ [UppercaseAlpha+ @1@] | [LowercaseAlpha+ @2@] ]
RC(Whitespace);' \
    --templargs 'Different RC before second EndTag' "$eta" "RC({.}) $etb" \
    --templargs 'Different RC after second EndTag' "$eta" "$etb RC({.})" \
    --inout '' 'A BC de .' '<A>A</A> <A>BC</A> de .'

check_compile_run \
    --code 'LC after first EndTag, same RC on TOP' \
    'Define TOP [ [UppercaseAlpha+ EndTag(A) LC(Whitespace)] | [LowercaseAlpha+ EndTag(B)] ]
RC(Whitespace);' \
    --inout '' 'A BC de .' 'A <A>BC</A> <B>de</B> .'

check_compile_run \
    --code 'LC after second EndTag, same RC on TOP' \
    'Define TOP [ [UppercaseAlpha+ EndTag(A)] | [LowercaseAlpha+ EndTag(B) LC(Whitespace)] ]
RC(Whitespace);' \
    --inout '' 'A BC de .' '<A>A</A> <A>BC</A> <B>de</B> .'


# Bug (reported 2013-04-15)

test_begin "The last line of input without a trailing newline"

check_compile_run \
    --code '' 'Define TOP [ Alpha+ EndTag(A) ];' \
    --inout 'Trailing newline in input' '1abc2' '1<A>abc</A>2' \
    --inout --printf 'No trailing newline in input, match ends before end of line' \
    '1abc2' '1<A>abc</A>2\n' \
    --inout --printf 'No trailing newline in input, match ends at end of line' \
    '1abc' '1<A>abc</A>\n'


# Bug/feature (reported 2013-05-30)

test_begin "OptCap, ToUpper, ToLower"

check_compile_run \
    --code 'OptCap' 'Define TOP OptCap([{a}|{ä}|{š}| LowercaseAlpha LowercaseAlpha+]) EndTag(A) ;' \
    --inout 'ASCII' 'aA' '<A>a</A><A>A</A>' \
    --inout 'Multi-letter ASCII word' \
    '.abc.Abc.ABC.' '.<A>abc</A>.<A>Abc</A>.<A>A</A>BC.' \
    --inout 'Latin 1 non-ASCII' 'äÄ' '<A>ä</A><A>Ä</A>' \
    --inout 'Non-Latin 1' 'šŠ' '<A>š</A><A>Š</A>' \

check_compile_run \
    --code 'ToUpper' 'Define TOP ToUpper([{a}|{ä}|{š}| LowercaseAlpha LowercaseAlpha+]) EndTag(A) ;' \
    --inout 'ASCII' 'aA' 'a<A>A</A>' \
    --inout 'Multi-letter ASCII word' \
    '.abc.Abc.ABC.' '.abc.<A>A</A>bc.<A>ABC</A>.' \
    --inout 'Latin 1 non-ASCII' 'äÄ' 'ä<A>Ä</A>' \
    --inout 'Non-Latin 1' 'šŠ' 'š<A>Š</A>'

check_compile_run \
    --code 'ToLower' 'Define TOP ToLower([{A}|{Ä}|{Š}| UppercaseAlpha UppercaseAlpha+]) EndTag(A) ;' \
    --inout 'ASCII' 'aA' '<A>a</A>A' \
    --inout 'Multi-letter ASCII word' \
    '.abc.Abc.ABC.' '.<A>abc</A>.A<A>bc</A>.ABC.' \
    --inout 'Latin 1 non-ASCII' 'äÄ' '<A>ä</A>Ä' \
    --inout 'Non-Latin 1' 'šŠ' '<A>š</A>Š'

check_fn_singlechar () {
    fn=$1
    shift
    check_compile_run \
	--codetempl "Define TOP $fn([@1@]) EndTag(A);" \
	--templargs "$fn uppercase single-char pattern" '{B}' \
	--templargs "$fn lowercase single-char pattern" '{b}' \
	--templargs "$fn single LowercaseAlpha" 'LowercaseAlpha' \
	--templargs "$fn single UppercaseAlpha" 'UppercaseAlpha' \
	--templargs "$fn single Alpha" 'Alpha' \
	"$@"
}

check_fn_multichar () {
    fn=$1
    shift
    check_compile_run \
	--codetempl "Define TOP $fn([@1@]) EndTag(A);" \
	--templargs "$fn uppercase multi-char pattern" '{BCDE}' \
	--templargs "$fn lowercase multi-char pattern" '{bcde}' \
	--templargs "$fn multiple LowercaseAlpha" \
	'LowercaseAlpha LowercaseAlpha+' \
	--templargs "$fn multiple UppercaseAlpha" \
	'UppercaseAlpha UppercaseAlpha+' \
	--templargs "$fn multiple Alpha" 'Alpha Alpha+' \
	--templargs "$fn mixed-case pattern" '{bCdE}' \
	"$@"
}

check_fn_multiword () {
    fn=$1
    shift
    check_compile_run \
	--codetempl "Define TOP $fn([@1@]) EndTag(A);" \
	--templargs "$fn uppercase multi-word pattern" '{BCDE FGHI}' \
	--templargs "$fn lowercase multi-word pattern" '{bcde fghi}' \
	--templargs "$fn mixed-case pattern" '{bCdE fGhI}' \
	"$@"
}

check_fn_other () {
    fn=$1
    shift
    check_compile_run \
	--code "$fn other single-char pattern" \
	"Define TOP $fn({.}) EndTag(A);" \
	--inout 'Uppercase input' 'B' 'B' \
	--inout 'Lowercase input' 'b' 'b' \
	--inout 'Other input' '.' '<A>.</A>' \
	"$@"
}

check_fn_singlechar ToUpper \
    --inout 'Uppercase input' 'B' '<A>B</A>' \
    --inout 'Lowercase input' 'b' 'b' \
    --inout 'Other input' '+' '+'

check_fn_multichar ToUpper \
    --inout 'Uppercase input' 'BCDE' '<A>BCDE</A>' \
    --inout 'Lowercase input' 'bcde' 'bcde' \
    --inout 'Capitalized input' 'Bcde' 'Bcde' \
    --inout 'Other input' '++' '++'

check_fn_multiword ToUpper \
    --inout 'Uppercase input' 'BCDE FGHI' '<A>BCDE FGHI</A>' \
    --inout 'Lowercase input' 'bcde fghi' 'bcde fghi' \
    --inout 'Capitalized input' 'Bcde Fghi' 'Bcde Fghi' \
    --inout 'Mixed-case input' 'bCdE fGhI' 'bCdE fGhI'

check_fn_singlechar ToLower \
    --inout 'Uppercase input' 'B' 'B' \
    --inout 'Lowercase input' 'b' '<A>b</A>' \
    --inout 'Other input' '+' '+'

check_fn_multichar ToLower \
    --inout 'Uppercase input' 'BCDE' 'BCDE' \
    --inout 'Lowercase input' 'bcde' '<A>bcde</A>' \
    --inout 'Other input' '++' '++'

check_fn_multiword ToLower \
    --inout 'Uppercase input' 'BCDE FGHI' 'BCDE FGHI' \
    --inout 'Lowercase input' 'bcde fghi' '<A>bcde fghi</A>' \
    --inout 'Capitalized input' 'Bcde Fghi' 'Bcde Fghi' \
    --inout 'Mixed-case input' 'bCdE fGhI' 'bCdE fGhI'

check_fn_other ToUpper
check_fn_other ToLower

check_compile_run \
    --codetempl "Define TOP ToLower([@1@]) EndTag(A);" \
    --input 'Bcde' \
    --outtemplargs "ToLower uppercase multi-char pattern, Capitalized input" 'Bcde' '{BCDE}' \
    --outtemplargs "ToLower lowercase multi-char pattern, Capitalized input" 'Bcde' '{bcde}' \
    --outtemplargs "ToLower multiple LowercaseAlpha, Capitalized input" 'B<A>cde</A>' \
    'LowercaseAlpha LowercaseAlpha+' \
    --outtemplargs "ToLower multiple UppercaseAlpha, Capitalized input" 'B<A>cde</A>' \
    'UppercaseAlpha UppercaseAlpha+' \
    --outtemplargs "ToLower multiple Alpha, Capitalized input" 'B<A>cde</A>' 'Alpha Alpha+' \
    --outtemplargs "ToLower capitalized multi-char pattern, Capitalized input" 'Bcde' '{Bcde}' \
    --outtemplargs "ToLower mixed-case pattern, Capitalized input" 'Bcde' '{bCdE}'

check_compile_run \
    --codetempl 'Define TOP @1@([{+}|{+ +}]) EndTag(X);' \
    --descrtempl '@1@ punct pattern' \
    --templarg-single 'OptCap' 'ToUpper' 'ToLower' \
    --inout 'Single char' '+' '<X>+</X>' \
    --inout 'Multiple chars' '+ +' '<X>+ +</X>'

check_compile_run \
    --codetempl "Define TOP OptCap([@1@]) EndTag(A);" \
    --templargs "OptCap lowercase single-char pattern" '{b}' \
    --templargs "OptCap single LowercaseAlpha" 'LowercaseAlpha' \
    --templargs "OptCap single Alpha" 'Alpha' \
    --inout 'Uppercase input' 'B' '<A>B</A>' \
    --inout 'Lowercase input' 'b' '<A>b</A>' \
    --inout 'Other input' '+' '+'

check_compile_run \
    --codetempl "Define TOP OptCap([@1@]) EndTag(A);" \
    --templargs "OptCap uppercase single-char pattern" '{B}' \
    --templargs "OptCap single UppercaseAlpha" 'UppercaseAlpha' \
    --inout 'Uppercase input' 'B' '<A>B</A>' \
    --inout 'Lowercase input' 'b' '<A>b</A>' \
    --inout 'Other input' '+' '+'

check_compile_run \
    --codetempl "Define TOP OptCap([@1@]) EndTag(A);" \
    --templargs "OptCap lowercase multi-char pattern" '{bcde}' \
    --templargs "OptCap capitalized multi-char pattern" '{Bcde}' \
    --inout 'Lowercase input' 'bcde' '<A>bcde</A>' \
    --inout 'Capitalized input' 'Bcde' '<A>Bcde</A>' \
    --inout 'Uppercase input' 'BCDE' 'BCDE' \
    --inout 'Mixed-case input' 'bCdE' 'bCdE' \
    --inout 'Other input' '++' '++'

check_compile_run \
    --code 'OptCap multiple LowercaseAlpha' \
    "Define TOP OptCap([LowercaseAlpha LowercaseAlpha+]) EndTag(A);" \
    --inout 'Lowercase input' 'bcde' '<A>bcde</A>' \
    --inout 'Capitalized input' 'Bcde' '<A>Bcde</A>' \
    --inout 'Uppercase input' 'BCDE' 'BCDE' \
    --inout 'Mixed-case input' 'bCdE' 'b<A>Cd</A>E' \
    --inout 'Other input' '++' '++'

check_compile_run \
    --codetempl 'Define TOP OptCap([@1@]) EndTag(A);' \
    --templargs "OptCap uppercase multi-char pattern" '{BCDE}' \
    --templargs "OptCap multiple UppercaseAlpha" \
    'UppercaseAlpha UppercaseAlpha+' \
    --inout 'Uppercase input' 'BCDE' '<A>BCDE</A>' \
    --inout 'Lowercase input' 'bcde' 'bcde' \
    --inout 'Capitalized input' 'Bcde' 'Bcde' \
    --inout 'Other input' '++' '++'

check_compile_run \
    --codetempl 'Define TOP OptCap([@1@]) EndTag(A);' \
    --input 'bCdE' \
    --outtemplargs "OptCap uppercase multi-char pattern, Mixed-case input" \
    'bCdE' '{BCDE}' \
    --outtemplargs "OptCap multiple UppercaseAlpha, Mixed-case input" \
    '<A>bC</A><A>dE</A>' 'UppercaseAlpha UppercaseAlpha+'

check_compile_run \
    --code "OptCap multiple Alpha" 'Define TOP OptCap([Alpha Alpha+]) EndTag(A);' \
    --inout 'Lowercase input' 'bcde' '<A>bcde</A>' \
    --inout 'Capitalized input' 'Bcde' '<A>Bcde</A>' \
    --inout 'Uppercase input' 'BCDE' '<A>BCDE</A>' \
    --inout 'Mixed-case input' 'bCdE' '<A>bCdE</A>' \
    --inout 'Other input' '++' '++'

check_compile_run \
    --code 'OptCap mixed case pattern' 'Define TOP OptCap([{bCdE}]) EndTag(A);' \
    --inout 'Uppercase input' 'BCDE' 'BCDE' \
    --inout 'Lowercase input' 'bcde' 'bcde' \
    --inout 'Capitalized input' 'Bcde' 'Bcde' \
    --inout 'Mixed-case input' 'bCdE' '<A>bCdE</A>' \
    --inout 'Other input' '++' '++'

check_compile_run \
    --code 'OptCap uppercase multi-word pattern' \
    'Define TOP OptCap([{BCDE FGHI}]) EndTag(A);' \
    --inout 'Uppercase input' 'BCDE FGHI' '<A>BCDE FGHI</A>' \
    --inout 'Lowercase input' 'bcde fghi' 'bcde fghi' \
    --inout 'Capitalized input' 'Bcde Fghi' 'Bcde Fghi' \
    --inout 'Mixed-case input' 'bCdE fGhI' 'bCdE fGhI'

check_compile_run \
    --code 'OptCap lowercase multi-word pattern' \
    'Define TOP OptCap([{bcde fghi}]) EndTag(A);' \
    --inout 'Uppercase input' 'BCDE FGHI' 'BCDE FGHI' \
    --inout 'Lowercase input' 'bcde fghi' '<A>bcde fghi</A>' \
    --inout 'Capitalized input' 'Bcde Fghi' '<A>Bcde Fghi</A>' \
    --inout 'Mixed-case input' 'bCdE fGhI' 'bCdE fGhI'

check_compile_run \
    --code 'OptCap capitalized multi-word pattern' \
    'Define TOP OptCap([{Bcde Fghi}]) EndTag(A);' \
    --inout 'Uppercase input' 'BCDE FGHI' 'BCDE FGHI' \
    --inout 'Lowercase input' 'bcde fghi' 'bcde fghi' \
    --inout 'Capitalized input' 'Bcde Fghi' '<A>Bcde Fghi</A>' \
    --inout 'Mixed-case input' 'bCdE fGhI' 'bCdE fGhI'

check_compile_run \
    --code 'OptCap mixed-case multi-word pattern' \
    'Define TOP OptCap([{bCdE fGhI}]) EndTag(A);' \
    --inout 'Uppercase input' 'BCDE FGHI' 'BCDE FGHI' \
    --inout 'Lowercase input' 'bcde fghi' 'bcde fghi' \
    --inout 'Capitalized input' 'Bcde Fghi' 'Bcde Fghi' \
    --inout 'Mixed-case input' 'bCdE fGhI' '<A>bCdE fGhI</A>'


# Feature (reported 2013-08-24)

test_begin "Ins maximizing globally"

check_compile_run \
    --code 'Ins followed by a character contained in Ins expression' \
    'Define A [Alpha+]; Define TOP [Ins(A) {a} EndTag(A)];' \
    --inout '' 'aa' 'aa'

check_compile_run \
    --code 'Ins followed by a character not contained in Ins expression' \
    'Define A [Alpha+]; Define TOP [Ins(A) {1} EndTag(A)];' \
    --inout '' 'aa1' '<A>aa1</A>' \


# Bug (reported 2013-08-24)

test_begin "Difference and character sets in named expressions"

check_compile_run \
    --codetempl '@1@ Define TOP [[@2@ {a}] - {Ca}] EndTag(A);' \
    --templargs 'Alpha as named expression' 'Define Any Alpha;' 'Any' \
    --templargs 'Directly Alpha' '' 'Alpha' \
    --templargs '[Alpha|Num] as named expression' \
    'Define Any [Alpha|Num];' 'Any' \
    --templargs 'Directly [Alpha|Num]' '' '[Alpha|Num]' \
    --inout '' 'Aa Ba Ca' '<A>Aa</A> <A>Ba</A> Ca'


# Bug (reported 2013-09-03)

test_begin "Named expressions in OptCap, ToUpper"

check_compile_run \
    --code 'Literals in OptCap' \
    'Define TOP [ OptCap([{aa} | {bb}]) ] EndTag(A);' \
    --code 'Named expression in OptCap' \
    'Define AB [{aa} | {bb}]; Define TOP [ OptCap(AB) ] EndTag(A);' \
    --code 'Named expression and literal in OptCap' \
    'Define A [{aa}]; Define TOP [ OptCap([A | {bb}]) ] EndTag(A);' \
    --inout '' 'aa Aa AA bb Bb BB' \
    '<A>aa</A> <A>Aa</A> AA <A>bb</A> <A>Bb</A> BB'

check_compile_run \
    --code 'Literals in ToUpper' \
    'Define TOP [ ToUpper([{aa} | {bb}]) ] EndTag(A);' \
    --code 'Named expression in ToUpper' \
    'Define AB [{aa} | {bb}]; Define TOP [ ToUpper(AB) ] EndTag(A);' \
    --code 'Named expression and literal in ToUpper' \
    'Define A [{aa}]; Define TOP [ ToUpper([A | {bb}]) ] EndTag(A);' \
    --inout '' 'aa Aa AA bb Bb BB' 'aa Aa <A>AA</A> bb Bb <A>BB</A>'


# Bug (reported 2013-09-03)

test_begin "Named expressions in replace"

check_compile_run \
    --code 'Named expression in replace source' \
    'Define A {a}; Define TOP [A -> {b}];' \
    --code 'Named expression in replace target' \
    'Define B {b}; Define TOP [{a} -> B];' \
    --code 'Unnamed expressions in replace' 'Define TOP [{a} -> {b}];' \
    --inout '' 'ab' 'bb'


# Bug (reported 2013-09-10)

test_begin "Long input lines"

gen_input () {
    perl -e 'print "'$1'" x '$2' . "\n"'
}

a9999=`gen_input a 9999`
a10000=`gen_input a 10000`
a10001=`gen_input a 10001`
# The exact threshold for causing segfaults seemed to vary
a58178=`gen_input a 58178`
a58200=`gen_input a 58200`
a100001=`gen_input a 100001`

check_compile_run \
    --code '' 'Define TOP [Alpha+ EndTag(A)];' \
    --inout '9999 characters' "$a9999" "<A>$a9999</A>" \
    --inout '10000 characters' "$a10000" "<A>$a10000</A>" \
    --inout '10001 characters' "$a10001" "<A>$a10001</A>" \
    --inout '58178 characters' "$a58178" "<A>$a58178</A>" \
    --inout '58200 characters' "$a58200" "<A>$a58200</A>" \
    --inout '100001 characters' "$a100001" "<A>$a100001</A>"


# Bug (reported 2013-10-21)

test_begin "Ins should not throw std::out_of_range"

check_compile_run \
    --code 'Four empty defines, Ins in TOP' \
    'Define A ""; Define B ""; Define C ""; Define D ""; Define TOP [ Ins(A) ];' \
    --code 'Four defines; two Inses in TOP' \
    'Define C ""; Define CA ""; Define B {b}; Define D [ {d} EndTag(A) ]; Define TOP [ Ins(B) | Ins(D) ];' \
    --inout '' 'aa' 'aa'


# Bug(?) (reported 2013-09-22 by Juha)

test_begin "Disjunction of two Ins expressions"

check_compile_run \
    --codetempl 'Define S { }; Define NS [? - S]; Define A [NS* {a} NS*]; Define B [NS* {b} NS*]; Define C {c}; Define TOP [[[@1@] S C]+ EndTag(AB)];' \
    --templargs 'Without Ins' 'A | B' \
    --templargs 'With Ins' 'Ins(A) | Ins(B)' \
    --inout 'No match' 'k c' 'k c' \
    --inout 'Match first disjunct' 'a c' '<AB>a c</AB>' \
    --inout 'Match second disjunct' 'b c' '<AB>b c</AB>' \
    --inout 'Match X + first disjunct' 'ka c' '<AB>ka c</AB>' \
    --inout 'Match first disjunct + X' 'ak c' '<AB>ak c</AB>' \
    --inout 'Match X + first disjunct + X' 'kak c' '<AB>kak c</AB>' \
    --inout 'Match first disjunct * 2' 'aa c' '<AB>aa c</AB>' \
    --inout 'Match second disjunct * 2' 'bb c' '<AB>bb c</AB>' \
    --inout 'Match first + second disjunct' 'ab c' '<AB>ab c</AB>' \
    --inout 'Match second + first disjunct' 'ba c' '<AB>ba c</AB>' \
    --inout 'Match first + second + first disjucnt' 'aba c' '<AB>aba c</AB>' \
    --inout 'Match second + first + second disjucnt' 'bab c' '<AB>bab c</AB>' \
    --inout 'Match X + first + X + second disjunct' 'kakb c' '<AB>kakb c</AB>' \
    --inout 'Multiple matches' \
    'k c a c b c ka c ak c kak c aa c bb c ab c ba c aba c bab c kakb c' \
    'k c <AB>a c</AB> <AB>b c</AB> <AB>ka c</AB> <AB>ak c</AB> <AB>kak c</AB> <AB>aa c</AB> <AB>bb c</AB> <AB>ab c</AB> <AB>ba c</AB> <AB>aba c</AB> <AB>bab c</AB> <AB>kakb c</AB>'
