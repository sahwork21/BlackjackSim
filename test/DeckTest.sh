#!/bin/bash
rm DeckTest.exe

#Compile the tester with TEST flag set
g++ -Wall -std=c++17 -g DeckTest.cpp ../src/Deck.cpp ../src/Card.cpp -o DeckTest -DTEST

#Make sure it compiled
if [ $? -ne 0 ]; then
    echo "Failed to compile Deck Test"
    exit 1
fi

#otherwise we are good
exit 0