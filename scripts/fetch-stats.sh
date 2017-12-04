#!/bin/sh

if [ -f "results" -o -d "results" ]; then
    echo "file/directory 'results' exists"
    exit 1
fi
touch results

if [ -f "foo" -o -d "foo" ]; then
    echo "file/directory 'foo' exists"
    exit 1
fi

for year in 2016;
do
    for month in `seq --equal-width 39 52`;
    do
        url="http://apertium.projectjj.com/apt/stats/weekly/"$year"-"$month".html"
        if curl --output foo --silent --fail $url; then
            cat foo | perl -pe 's/<tr>/\n/g;' | grep '>hfst<' | perl -pe 's/[^0-9]*([0-9]+)[^0-9]*([0-9]+)[^0-9]*([0-9]+)[^0-9]*([0-9]+)[^0-9]*/\1 \2 \3 \4/;' >> results
            echo "" >> results
        fi
    done
done

col=1
for field in "Total" "Linux" "Win" "Mac";
do
    cut -d' ' -f$col results | perl -pe 's/\n/ + /g;' | perl -pe 's/(.*) \+ /\1/;' > foo
    echo "" >> foo
    echo $field": "
    cat foo | bc
    col=$((col+1))
done
