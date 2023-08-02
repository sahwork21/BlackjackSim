#!/bin/bash
#rm GenerationTest.exe
rm *.o *.exe
#compile this junk
#one object at a time because c++ hates me
g++ -Wall -std=c++17 -g -c ../Card.cpp -o Card.o
if [ $? -ne 0 ]; then
    echo "Failed to make Card object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c ../Deck.cpp -o Deck.o
if [ $? -ne 0 ]; then
    echo "Failed to make Deck object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c ../Shoe.cpp -o Shoe.o
if [ $? -ne 0 ]; then
    echo "Failed to make Shoe object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c Individual.cpp -o Individual.o
if [ $? -ne 0 ]; then
    echo "Failed to make Individual object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c Generation.cpp -o Generation.o
if [ $? -ne 0 ]; then
    echo "Failed to make Generation object"
    exit 1
fi



g++ -Wall -std=c++17 -g Generation.o Individual.o Shoe.o Deck.o Card.o -o GenerationTest -DTEST

if [ $? -ne 0 ]; then
    echo "Failed to compile Generation test"
    exit 1

fi
exit 0