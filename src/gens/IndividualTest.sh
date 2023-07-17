#!/bin/bash
rm IndividualTest.exe

#compile this junk
g++ -Wall -std=c++17 IndividualTest.cpp Individual.cpp ../Card.cpp ../Shoe.cpp -o IndividualTest

if [ $? -ne 0 ]; then
    echo "Failed to compile Individual test"
    exit 1

exit 0