#!/bin/sh

# ****************************************************************** #
# Find out the number of bytes definitely lost for HFST unary tools  #
# with different implementation formats for a small test transducer, #
# a bigger test transducer and a stream of five small transducers    #
# and print the information to standard output.                      #
# ****************************************************************** #

VALGRIND="valgrind --tool=memcheck --leak-check=full "

SHORTER_TEST_STRING="(a:bc:de:fg:hi:jk:lm:no:pq:rs:tu:vw:xy:z)| \
(A:BC:DE:FG:HI:JK:LM:NO:PQ:RS:TU:VW:XY:Z)"

LONGER_TEST_STRING="(a:bc:de:fg:hi:jk:lm:no:pq:rs:tu:vw:xy:z)| \
(A:BC:DE:FG:HI:JK:LM:NO:PQ:RS:TU:VW:XY:Z)| \
(1:bc:de:fg:hi:jk:lm:no:pq:rs:tu:vw:xy:2)| \
(3:BC:DE:FG:HI:JK:LM:NO:PQ:RS:TU:VW:XY:4)"

for impl in sfst openfst-tropical foma;
do
    # The smaller test transducer
    echo $SHORTER_TEST_STRING | ./hfst-calculate -f $impl > tr.$impl;
    # The bigger test transducer
    echo $LONGER_TEST_STRING | ./hfst-calculate -f $impl > TR.$impl;
done

tr=omorfi
TR=TR

if [ "$1" = "--all" ]; then
    echo "Performing an extensive check";
    echo "Tool,implementation,1xsmall,5xsmall,1xbig" | ./align.sh
else
    echo "Testing program $1 for implementation type $2...";
    $VALGRIND .libs/$1 -i tr.$2 -o /dev/null 2> log;
    $VALGRIND .libs/$1 -i TR.$2 -o /dev/null 2> LOG;
    echo "Wrote log to files log and LOG."
    exit 0;
fi

# The tools to be tested
UNARY_TOOLS="hfst-determinize \
hfst-fst2fst \
hfst-fst2strings \
hfst-fst2txt \
hfst-head \
hfst-invert \
hfst-minimize \
hfst-name \
hfst-project \
hfst-push-weights \
hfst-remove-epsilons \
hfst-repeat \
hfst-reverse \
hfst-reweight \
hfst-substitute \
hfst-summarize \
hfst-tail \
hfst-txt2fst"

# Store each line here before aligning and printing it
rm -f TMP

# For all unary tools,
for tool in $UNARY_TOOLS;
do
    # for all implementation formats,
    for impl in sfst; #openfst-tropical foma;
    do
	# test the following cases:
	echo -n "$tool,$impl:," >> TMP ;

	# The smaller transducer
	$VALGRIND .libs/$tool -i $tr.$impl -o /dev/null 2> log;
	grep "definitely" log | grep -v "are" | tr '\n' ' ' | perl -pe "s/.* ([^ ]*) bytes.*/\1,/g;" >> TMP ;

	# A stream of five consecutive small transducers
	cat $tr.$impl $tr.$impl $tr.$impl $tr.$impl $tr.$impl > tr5;
	$VALGRIND .libs/$tool -i tr5 -o /dev/null 2> LOG;
	grep "definitely" LOG | grep -v "are" | tr '\n' ' ' | perl -pe "s/.* ([^ ]*) bytes.*/\1,/g;" >> TMP ;
	rm tr5;

	# The bigger transducer
	#$VALGRIND .libs/$tool -i $TR.$impl -o /dev/null 2> Log;
	#grep "definitely" Log | grep -v "are"  | perl -pe "s/.* ([^ ]*) bytes.*/\1/g;" >> TMP ;

	# Print the number of bytes definitely lost and align them
	#cat TMP | ./align.sh ;
	#rm -f TMP ;
    done;
done

# Remove temporary files
rm $tr.sfst $tr.openfst-tropical $tr.foma
rm LOG log Log
