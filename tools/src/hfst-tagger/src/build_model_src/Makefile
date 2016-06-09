test:string_handling WeightedStringVectorCollection ModelBuilder \
	SequenceModelBuilder LexicalModelBuilder TaggerBuilder
	./string_handling
	./WeightedStringVectorCollection
	./ModelBuilder
	./SequenceModelBuilder
	./LexicalModelBuilder
	./TaggerBuilder

string_handling:
	g++ -g -O3 -c -o string_handling.o string_handling.cc
	g++ -g -O3 -DMAIN_TEST -o string_handling string_handling.o \
	string_handling.cc ../unit_test_aux.cc -lhfst

WeightedStringVectorCollection:string_handling.cc \
WeightedStringVectorCollection.cc
	g++ -g -O3 -c -o string_handling.o string_handling.cc
	g++ -g -O3 -c -o WeightedStringVectorCollection.o \
	WeightedStringVectorCollection.cc
	g++ -g -O3 -DMAIN_TEST -o WeightedStringVectorCollection \
	string_handling.o WeightedStringVectorCollection.o \
	WeightedStringVectorCollection.cc ../unit_test_aux.cc -lhfst

ModelBuilder:string_handling.cc WeightedStringVectorCollection.cc \
	FstBuilder.cc ModelBuilder.cc
	g++ -g -O3 -c -o string_handling.o string_handling.cc
	g++ -g -O3 -c -o WeightedStringVectorCollection.o \
	WeightedStringVectorCollection.cc
	g++ -g -O3 -c -o FstBuilder.o FstBuilder.cc
	g++ -g -O3 -c -o ModelBuilder.o ModelBuilder.cc
	g++ -g -O3 -DMAIN_TEST -o ModelBuilder ModelBuilder.o FstBuilder.o \
	string_handling.o WeightedStringVectorCollection.o \
	ModelBuilder.cc ../unit_test_aux.cc -lhfst

SequenceModelBuilder:string_handling.cc WeightedStringVectorCollection.cc \
	FstBuilder.cc ModelBuilder.cc SequenceModelBuilder.cc
	g++ -g -O3 -c -o string_handling.o string_handling.cc
	g++ -g -O3 -c -o WeightedStringVectorCollection.o \
	WeightedStringVectorCollection.cc
	g++ -g -O3 -c -o FstBuilder.o FstBuilder.cc
	g++ -g -O3 -c -o ModelBuilder.o ModelBuilder.cc
	g++ -g -O3 -c -o SequenceModelBuilder.o SequenceModelBuilder.cc
	g++ -g -O3 -DMAIN_TEST -o SequenceModelBuilder ModelBuilder.o \
	FstBuilder.o string_handling.o WeightedStringVectorCollection.o \
	SequenceModelBuilder.o SequenceModelBuilder.cc ../unit_test_aux.cc \
	-lhfst

LexicalModelBuilder:string_handling.cc WeightedStringVectorCollection.cc \
	FstBuilder.cc ModelBuilder.cc LexicalModelBuilder.cc
	g++ -g -O3 -c -o string_handling.o string_handling.cc
	g++ -g -O3 -c -o WeightedStringVectorCollection.o \
	WeightedStringVectorCollection.cc
	g++ -g -O3 -c -o FstBuilder.o FstBuilder.cc
	g++ -g -O3 -c -o ModelBuilder.o ModelBuilder.cc
	g++ -g -O3 -c -o LexicalModelBuilder.o LexicalModelBuilder.cc
	g++ -g -O3 -DMAIN_TEST -o LexicalModelBuilder ModelBuilder.o \
	FstBuilder.o string_handling.o WeightedStringVectorCollection.o \
	LexicalModelBuilder.o LexicalModelBuilder.cc ../unit_test_aux.cc \
	-lhfst

TaggerBuilder:string_handling.cc WeightedStringVectorCollection.cc \
	FstBuilder.cc ModelBuilder.cc LexicalModelBuilder.cc TaggerBuilder.cc
	g++ -g -O3 -c -o string_handling.o string_handling.cc
	g++ -g -O3 -c -o WeightedStringVectorCollection.o \
	WeightedStringVectorCollection.cc
	g++ -g -O3 -c -o FstBuilder.o FstBuilder.cc
	g++ -g -O3 -c -o ModelBuilder.o ModelBuilder.cc
	g++ -g -O3 -c -o LexicalModelBuilder.o LexicalModelBuilder.cc 
	g++ -g -O3 -c -o SequenceModelBuilder.o SequenceModelBuilder.cc
	g++ -Wall -Wextra -g -O3 -c -o TaggerBuilder.o TaggerBuilder.cc
	g++ -g -O3 -DMAIN_TEST -o TaggerBuilder ModelBuilder.o \
	FstBuilder.o string_handling.o WeightedStringVectorCollection.o \
	TaggerBuilder.o LexicalModelBuilder.o SequenceModelBuilder.o \
	TaggerBuilder.cc \
	../unit_test_aux.cc -lhfst
