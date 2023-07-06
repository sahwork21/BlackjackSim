#!/bin/bash

#First we must clean out our directory of old objects and executables
rm *.o *.exe

#Then we need to create our object then compile
#Make sure we are checking for successful compilation. It is 0
g++ -Wall -std=c++17 -g -c src/Card.cpp -o Card.o
if [ $? -ne 0 ]; then
    echo "Failed to make Card object"
    exit 1
fi


g++ -Wall -std=c++17 -g -c src/Deck.cpp -o Deck.o
if [ $? -ne 0 ]; then
    echo "Failed to make Deck object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c src/Shoe.cpp -o Shoe.o
if [ $? -ne 0 ]; then
    echo "Failed to make Shoe object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c src/GameSim.cpp -o GameSim.o
if [ $? -ne 0 ]; then
    echo "Failed to make GameSim object"
    exit 1
fi


#Finally compile our executable
g++ -Wall -std=c++17 -g GameSim.o Card.o Deck.o Shoe.o -o GameSim


#Check that what we compiled is there or not
FILE=./GameSim.exe
if test -f "$FILE"; then
    echo "$FILE was successfully created"
    exit 0
fi


#Otherwise we messed up
echo "$FILE failed to compile"
exit 1