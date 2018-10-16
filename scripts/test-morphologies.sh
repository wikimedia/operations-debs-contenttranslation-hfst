#!/bin/sh

test_case()
{
    # input on one line
    if ! echo $2 | $1-analyze-words | cut -f 2- > tmp; then
	echo "$1: input \"$2\" (space-separated words) failed"
    fi
    if [ "$3" != "" ]; then
	if test -f "$3"; then 
	    if ! diff tmp $3 > /dev/null; then
		echo "$1: output of \"$2\" (space-separated words) differs from expected"
	    fi
	fi
    fi
    # each word on its own line
    if ! echo $2 | perl -pe 's/ /\n/;' | $1-analyze-words | cut -f 2- > tmp; then
	echo "$1: input \"$2\" (line-separated words) failed"
    fi
    if [ "$3" != "" ]; then
	if test -f "$3"; then 
	    if ! diff tmp $3 > /dev/null; then
		echo "$1: output of \"$2\" (line-separated words) differs from expected"
	    fi
	fi
    fi
}

test_lang()
{
    echo $1
    test_case $1 "$2" "$1-analyze-words.output"
    test_case $1 " "
    test_case $1 ""
}

test_lang "english" "TODO"
test_lang "finnish" "TODO"
test_lang "french" "TODO"
test_case "german" "TODO"
test_lang "italian" "TODO"
test_lang "swedish" "TODO"
test_lang "turkish" "TODO"
