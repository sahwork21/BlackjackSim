/**
 * @file GameSim.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * @brief This is just a C file disguised as C++ to help restart the implementation
 * 
 * 
 */


#include "Card.h"
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <string>
#include <random>

#define MAX_ROUNDS 500



//We will be using strings in our cards struct
using std::string;
using std::cout;
using std::cerr;
using std::endl;


//Our deck of cards which is an array of pointers to some objects
Card *Deck[53];


//RNG values from random library
std::mt19937 rng;   

//Uniform distribution so we fairly can get from 0 to 51
std::uniform_int_distribution<uint32_t> dist(0,51); // range [0,51]

/**
 * @brief Populates the deck
 */
void populateDeck()
{
  
  

  int cardCount = 0;
	string names[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	int CardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 13; j++){
      //Construct our Card here
      Deck[cardCount] = new Card(CardValue[j], suits[i], names[j]);
      cardCount++;
    }
  }
	
	
  //Print out the cards we have
  cout << "Cards in order" << endl;
	for(int x = 0; x < 52; x ++){
		cout << Deck[x]->getName() << " of " << Deck[x]->getSuit() << ": Value of " << Deck[x]->getScore() << endl;
	}

  //Swap two randomly selected cards 500 times using that extra blank spot of space
	for (int i = 0; i < 500; i++){
		int a = dist(rng) % 52;
		int b = dist(rng) % 52;
		
    //Swapping of cards now we just exchange pointers
		Deck[52] = Deck[a];
	
    Deck[a] = Deck[b];
		
    Deck[b] = Deck[52];
		

	}

  //Print out our shuffled deck
  cout << endl << "Shuffled cards" << endl;
	for(int i = 0; i < 52; i++){
		cout << Deck[i]->getName() << " of " << Deck[i]->getSuit() << " : Value of " << Deck[i]->getScore() <<  endl;
	}
}

/**
 * @brief Runs the sim for a game of black jack and prints out the occurences
 * @return the exit code
 */
int main(int argc, char *argv[])
{

  if(argc != 2){
    cerr << "Usage: ./GameSim [Rounds of Simulation]" << endl; 
    exit(EXIT_FAILURE);
  }

  //Seed our random values
  rng.seed(time(0));

	populateDeck();

  //Count up our occurences and print them out
  int occurences[18] = {0};

  int rounds = 0;
  int match = sscanf(argv[1], "%d", &rounds);



  //Check the input
  if(match != 1){
    cerr << "Need an int for rounds of simming" << endl; 
    exit(EXIT_FAILURE);
  }

  //Don't want too many rounds
  if(rounds < 0 || rounds > MAX_ROUNDS){
    cerr << "Need an int value from 0 to 500" << endl; 
    exit(EXIT_FAILURE);
  }

  //Simulate giving 2 random cards to the player then return them
  for(int i = 0; i < rounds; i++){
    int a = dist(rng) % 52;
    int b;
    //Need 2 unique cards
    do{
      b = dist(rng) % 52;
    }while(b == a);

    int score = Deck[a]->getScore() + Deck[b]->getScore();
    
    //If we got a 22 just change score to a 12 as one ace become a 1s
    if(score == 22 && (Deck[a]->getName().compare("Ace") || Deck[b]->getName().compare("Ace"))){
      score = 12;
    }

    cout << score << endl;
    //Increase the value of our occurences
    occurences[score - 4] += 1;

  }

  //Print out our sim results
  cout << endl << endl;
  for(int i = 0; i < 18; i++){
    cout << "There are " << occurences[i] << " " << i + 4 << "'s" << endl;
  }

  

  return 0;
}