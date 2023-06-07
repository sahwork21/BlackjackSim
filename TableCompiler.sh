#!/bin/bash
rm Table.exe
rm *.o

# Compile the objects and then throw them all together
#Make sure we are checking for successful compilation. It is 0
g++ -Wall -std=c++17 -g -c src/Card.cpp -o Card.o
if [ $? -ne 0 ]; then
    echo "Failed to make Card object"
    exit 1
fi

#Compile the deck
g++ -Wall -std=c++17 -g -c src/Deck.cpp -o Deck.o
if [ $? -ne 0 ]; then
    echo "Failed to make Deck object"
    exit 1
fi

#Compile the shoe object
g++ -Wall -std=c++17 -g -c src/Shoe.cpp -o Shoe.o
if [ $? -ne 0 ]; then
    echo "Failed to make Shoe object"
    exit 1
fi


#Compile the Players then better and dealer
g++ -Wall -std=c++17 -g -c src/Player.cpp -o Player.o
if [ $? -ne 0 ]; then
    echo "Failed to make Player object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c src/Dealer.cpp -o Dealer.o
if [ $? -ne 0 ]; then
    echo "Failed to make Dealer object"
    exit 1
fi

g++ -Wall -std=c++17 -g -c src/Better.cpp -o Better.o
if [ $? -ne 0 ]; then
    echo "Failed to make Better object"
    exit 1
fi




#Finally compile our Table object
g++ -Wall -std=c++17 -g -c src/Table.cpp -o Table.o -DWINDOWS
if [ $? -ne 0 ]; then
    echo "Failed to make Table object"
    exit 1
fi

#Finally compile our executable
g++ -Wall -std=c++17 -g Table.o Shoe.o Dealer.o Better.o Deck.o Card.o Player.o -o Table -DWINDOWS


#Check that what we compiled is there or not
FILE=./Table.exe
if test -f "$FILE"; then
    echo "$FILE was successfully created"
    exit 0
fi


#Otherwise we messed up
echo "$FILE failed to compile"
exit 1 