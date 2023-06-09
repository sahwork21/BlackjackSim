#!/bin/bash
rm ShoeTest.exe

#Compile the tester with TEST flag set
g++ -Wall -std=c++17 -g ShoeTest.cpp ../src/Shoe.cpp ../src/Card.cpp ../src/Deck.cpp -o ShoeTest -DWINDOWS

#Use -v and -ftime-report to see what the compiler is up to


#Make sure it compiled
if [ $? -ne 0 ]; then
    echo "Failed to compile Shoe Test"
    exit 1
fi

#otherwise we are good
exit 0