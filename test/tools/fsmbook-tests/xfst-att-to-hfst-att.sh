#!/bin/bash
# Convert the att format from xfst into the equivalent format of HFST.
perl -pe "s/(\s)\+(\s)/\1\@_IDENTITY_SYMBOL_\@\2/g;" |  # identity
perl -pe "s/(\s)\+$/\1\@_IDENTITY_SYMBOL_\@/g;" |       # identity
perl -pe "s/\*\*OTHER\*\*/\@_UNKNOWN_SYMBOL_\@/g;" |    # unknown
perl -pe "s/\*\*EPSILON\*\*/\@_EPSILON_SYMBOL_\@/g;" |  # epsilon
perl -pe "s/ /\@_SPACE_\@/g;" | # space
sed '
s/\\u00d3/Ó/g;
s/\\u00e0/à/g;
s/\\u00e1/á/g;
s/\\u00e2/â/g;
s/\\u00e3/ã/g;
s/\\u00e4/ä/g;
s/\\u00e5/å/g;
s/\\u00e6/æ/g;
s/\\u00e7/ç/g;
s/\\u00e8/è/g;
s/\\u00e9/é/g;
s/\\u00ea/ê/g;
s/\\u00eb/ë/g;
s/\\u00ec/ì/g;
s/\\u00ed/í/g;
s/\\u00ee/î/g;
s/\\u00ef/ï/g;
s/\\u00f0/ð/g;
s/\\u00f1/ñ/g;
s/\\u00f2/ò/g;
s/\\u00f3/ó/g;
s/\\u00f4/ô/g;
s/\\u00f5/õ/g;
s/\\u00f6/ö/g;
s/\\u00f7/÷/g;
s/\\u00f8/ø/g;
s/\\u00f9/ù/g;
s/\\u00fa/ú/g;
s/\\u00fb/û/g;
s/\\u00fc/ü/g;
s/\\u00fd/ý/g;
s/\\u00fe/þ/g;
s/\\u00ff/ÿ/g;'
