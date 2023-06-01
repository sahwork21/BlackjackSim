#!/bin/bash
rm BetterTest.exe

#Compile the tester with TEST flag set
g++ -Wall -std=c++17 -g BetterTest.cpp ../src/Player.cpp ../src/Better.cpp ../src/Card.cpp ../src/Deck.cpp -o BetterTest -DTEST

#Use -v and -ftime-report to see what the compiler is up to


#Make sure it compiled
if [ $? -ne 0 ]; then
    echo "Failed to compile Better Test"
    exit 1
fi

#otherwise we are good
exit 0