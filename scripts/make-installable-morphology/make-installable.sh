#!/bin/bash

function print_help()
{
    echo
    echo 'make-installable.sh langname langcode [--dir dirname] [--unweighted] [--capcase] [--punct]'
    echo
    echo 'Expects to have an analyzing morphology in the directory'
    echo 'hfst-[langname] under the name "langname.hfst", where'
    echo '"langname" is the name of the language in question. hfst-[langname]'
    echo 'should be under the working directory, or you can specify its full'
    echo 'name and path with --dir, eg. for French,'
    echo
    echo './make-installable.sh french fr --dir /path/to/french [--unweighted] [--capcase] [--punct]'
    echo
    echo 'fr is the language code'
    echo '--unweighted controls whether the analyzer will be weighted'
    echo '--capcase controls whether to compose in a casing handler'
    echo '--punct controls whether to include a punctuation handler'
}

if [ $# -lt 2 ] ; then
    print_help
    exit 1
fi

langname=$1
langcode=$2
shift 2

dir=hfst-${langname}-installable

fst2fstcommand="hfst-fst2fst -w"
capcase="false"
punct="false"

while test -n "$1"; do
    case "$1" in
	-h|--help)
	    print_help
	    exit 1
	    ;;
	--unweighted)
	    fst2fstcommand="hfst-fst2fst -O"
	    ;;
	--capcase)
	    capcase="true"
	    ;;
	--punct)
	    punct="true"
	    ;;
	--dir)
	    if [ -z "$2" ]; then
		print_help
		exit 1
	    fi
	    dir=$2
	    shift
	    ;;
	*)
	    print_help
	    exit 1
    esac
    shift
done

target_dir=${dir}/hfst-${langname}-installable

set -x

mkdir -p $target_dir
rm -rf $target_dir/*

hfst-fst2fst -t ${dir}/${langname}.hfst > ${langname}_tmp.hfst

if [ "$punct" == "true" ]; then
    hfst-strings2fst -j punct.txt | hfst-disjunct -1 - -2 ${langname}_tmp.hfst > ${langname}_with_punct.hfst
    mv ${langname}_with_punct.hfst ${langname}_tmp.hfst
fi

hfst-invert ${langname}_tmp.hfst | hfst-minimize | $fst2fstcommand > \
    ${target_dir}/${langname}-generation.hfst.ol

if [ "$capcase" == "true" ]; then
    hfst-pmatch2fst <<< 'set need-separators off regex (OptDownCase(?, L)) ?*;' | hfst-fst2fst -t | hfst-compose -1 - -2 ${langname}_tmp.hfst > ${langname}_capcase.hfst
    mv ${langname}_capcase.hfst ${langname}_tmp.hfst
fi

# normalize fancy unicode apostrophes, just about all transducers need this
echo "\"’\" (->) \"'\"" | hfst-regexp2fst | hfst-compose -1 - -2 ${langname}_tmp.hfst > ${langname}_normalized.hfst
mv ${langname}_normalized.hfst ${langname}_tmp.hfst

sed s/LANGNAME/${langname}/g < analyze.sh > ${target_dir}/${langname}-analyze-words
sed s/LANGNAME/${langname}/g < generate.sh > ${target_dir}/${langname}-generate-words
sed -e s/LANGNAME/${langname}/g -e s/LANGCODE/${langcode}/g < Makefile-skeleton > \
    ${target_dir}/Makefile

typeset -u firstletter=${langname:0:1}
rest=${langname:1}

sed -e s/Langname/$firstletter$rest/g -e s/LANGNAME/${langname}/g < README-skeleton > \
    ${target_dir}/README

sed -e s/LANG/${langname}_tmp.hfst/g < tokenizer-skeleton > ${langname}-tokenizer.txt
if [ -e ${langname}-tokenizer-patch.txt ]; then
    patch ${langname}-tokenizer.txt ${langname}-tokenizer-patch.txt
fi

hfst-pmatch2fst ${langname}-tokenizer.txt > ${target_dir}/${langname}-tokenize.pmatch
rm -f ${langname}-tokenizer.txt ${langname}_tmp.hfst
