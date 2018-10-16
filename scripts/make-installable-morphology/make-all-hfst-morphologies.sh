#!/bin/bash

set -x

rootpath=$1

if [ -z $rootpath ]; then
    echo "You forgot to give the root path!"
    exit 1
fi

./make-installable.sh french fr --dir ${rootpath}/hfst-french --capcase --punct --unweighted &

./make-installable.sh italian it --dir ${rootpath}/hfst-italian --capcase --unweighted &

./make-installable.sh finnish fi --dir ${rootpath}/hfst-finnish &

./make-installable.sh turkish tr --dir ${rootpath}/hfst-turkish --punct --capcase --unweighted &

./make-installable.sh swedish sv --dir ${rootpath}/hfst-swedish --punct --capcase --unweighted &

./make-installable.sh german de --dir ${rootpath}/hfst-german --unweighted &

./make-installable.sh english en --dir ${rootpath}/hfst-english --capcase &

wait
