#!/bin/sh

# Run this script in the xml directory where you have generated xml output from Doxygen.
# Dependencies: doxy2swig.py script.

rm doc.i &&
touch doc.i &&
for f in \
classhfst_1_1AttReader.xml \
classhfst_1_1HfstBasicTransducer.xml \
classhfst_1_1HfstBasicTransition.xml \
classhfst_1_1HfstInputStream.xml \
classhfst_1_1HfstOutputStream.xml \
classhfst_1_1HfstTokenizer.xml \
classhfst_1_1HfstTransducer.xml \
classhfst_1_1MultiCharSymbolTrie.xml \
classhfst_1_1PmatchContainer.xml \
classhfst_1_1PrologReader.xml \
classhfst_1_1XreCompiler.xml \
exceptions_2____init_____8py.xml \
____init_____8py.xml \
namespacehfst_1_1exceptions.xml \
namespacehfst_1_1rules.xml \
namespacehfst_1_1types.xml \
namespacehfst.xml \
rules_2____init_____8py.xml \
types_2____init_____8py.xml \
classhfst_1_1exceptions_1_1*.xml ;
do
    echo "generating documentation for file "$f"..." &&
    ./doxy2swig.py $f tmp &&
    cat tmp >> doc.i;
done

sed -i 's/\(%feature("docstring").*\)"$/\1\n"""/; s/";$/"""/;' doc.i
