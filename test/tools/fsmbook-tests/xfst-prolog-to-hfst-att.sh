#!/bin/sh
# convert xfst prolog format to hfst att format
sed '
1,/network/ d
s/arc(net_[a-z0-9]*, //
s/, / /g

s/" "/"@_SPACE_@"/
s/"?":/"@_UNKNOWN_SYMBOL_@":/
s/:"?"/:"@_UNKNOWN_SYMBOL_@"/
s/ "?"/ "@_IDENTITY_SYMBOL_@"/

s/"0":/"@_EPSILON_SYMBOL_@":/
s/:"0"/:"@_EPSILON_SYMBOL_@"/
s/"0"/@_EPSILON_SYMBOL_@/g
s/"%0"/"0"/

s/"%?"/"?"/

s/"\(.*\)":"\(.*\)"/\1 \2/
s/"\(.*\)"/\1 \1/



s/"//g
s/).//
s/final(net_[a-z0-9]* //

/#/,$ d
/^symbol/ d
'
