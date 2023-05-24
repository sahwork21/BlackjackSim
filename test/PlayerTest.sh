#!/bin/bash
rm PlayerTest.exe

#Compile the tester with TEST flag set
g++ -Wall -std=c++17 -g PlayerTest.cpp ../src/Player.cpp ../src/Card.cpp ../src/Deck.cpp -o PlayerTest -DTEST

#Make sure it compiled
if [ $? -ne 0 ]; then
    echo "Failed to compile Player Test"
    exit 1
fi

#otherwise we are good
exit 0