#!/bin/sh
TOOLDIR=../../tools/src

for i in "" .sfst .ofst .foma; do 
    if ((test -z "$i") || $TOOLDIR/hfst-format --list-formats | grep $i > /dev/null); then
        if test -f cat$i -a -f cat2dog$i ; then
            if ! $TOOLDIR/hfst-compose cat$i cat2dog$i > test ; then
                echo cat$1 o cat2dog$i fail
                exit 1
            fi
            if ! $TOOLDIR/hfst-compare -s test cat2dog$i  ; then
                echo cat2do$i differs
                exit 1
            fi
            rm test;
            if test -f identity-star$i ; then
                if ! $TOOLDIR/hfst-compose cat$i identity-star$i > test ; then
                    echo cat$1 o identitytstar$i fail
                    exit 1
                fi
                if ! $TOOLDIR/hfst-compare -s cat$i test > /dev/null ; then
                    exit 1
                fi
            fi
            if test -f unknown-star$i ; then
                if ! $TOOLDIR/hfst-compose cat$i identity-star$i > test ; then
                    exit 1
                fi
            fi
	    if test -f unknown2a$i && test -f identity$i ; then
	        if ! $TOOLDIR/hfst-compose unknown2a$i identity$i > test ; then
		    exit 1
                fi
	        if $TOOLDIR/hfst-compare -s test unknown2a$i > /dev/null ; then
		    exit
	        fi
	    fi 
        fi
    fi
done
