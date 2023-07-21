#!/bin/bash
rm IndividualTest.exe

#compile this junk
g++ -Wall -std=c++17 -g IndividualTest.cpp Individual.cpp ../Card.cpp ../Shoe.cpp -o IndividualTest -DTEST

if [ $? -ne 0 ]; then
    echo "Failed to compile Individual test"
    exit 1

fi
exit 0