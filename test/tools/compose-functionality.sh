#!/bin/sh
TOOLDIR=../../tools/src
COMPOSE_TOOL=
COMPARE_TOOL=
FORMAT_TOOL=

if [ "$1" = '--python' ]; then
    COMPOSE_TOOL="python3 ./hfst-compose.py"
    COMPARE_TOOL="python3 ./hfst-compare.py"
    FORMAT_TOOL="python3 ./hfst-format.py"
else
    COMPOSE_TOOL=$TOOLDIR/hfst-compose
    COMPARE_TOOL=$TOOLDIR/hfst-compare
    FORMAT_TOOL=$TOOLDIR/hfst-format
    for tool in $COMPOSE_TOOL $COMPARE_TOOL $FORMAT_TOOL;
    do
	if ! test -x $tool; then
	    exit 77;
	fi
    done
fi

for i in "" .sfst .ofst .foma; do 
    if ((test -z "$i") || $FORMAT_TOOL --list-formats | grep $i > /dev/null); then
        if test -f cat$i -a -f cat2dog$i ; then
            if ! $COMPOSE_TOOL cat$i cat2dog$i > test ; then
                echo cat$1 o cat2dog$i fail
                exit 1
            fi
            if ! $COMPARE_TOOL -s test cat2dog$i  ; then
                echo cat2do$i differs
                exit 1
            fi
            rm test;
            if test -f identity-star$i ; then
                if ! $COMPOSE_TOOL cat$i identity-star$i > test ; then
                    echo cat$1 o identitytstar$i fail
                    exit 1
                fi
                if ! $COMPOSE_TOOL -s cat$i test > /dev/null ; then
                    exit 1
                fi
            fi
            if test -f unknown-star$i ; then
                if ! $COMPOSE_TOOL cat$i identity-star$i > test ; then
                    exit 1
                fi
            fi
	    if test -f unknown2a$i && test -f identity$i ; then
	        if ! $COMPOSE_TOOL unknown2a$i identity$i > test ; then
		    exit 1
                fi
	        if $COMPARE_TOOL -s test unknown2a$i > /dev/null ; then
		    exit
	        fi
	    fi 
        fi
    fi
done
