/**
 * @file GameSim.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * @brief This is just a C file disguised as C++ to help restart the implementation
 * 
 * 
 */


#include "Shoe.h"
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



//RNG values from random library
std::mt19937 rng;   

//Uniform distribution so we fairly can get from 0 to 51
std::uniform_int_distribution<uint32_t> dist(0,51); // range [0,51]

/**
 * @brief Populates the deck
 */
void readDeck(Deck *deck)
{
  //Create our Deck of Cards
  
  
  

  // int cardCount = 0;
	// string names[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	// string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	// int CardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
  // for(int i = 0; i < 4; i++){
  //   for(int j = 0; j < 13; j++){
  //     //Construct our Card here
  //     Deck[cardCount] = new Card(CardValue[j], suits[i], names[j]);
  //     cardCount++;
  //   }
  // }
	
	
  //Print out the cards we have
  cout << "Cards in order" << endl;
  Card *c;

	for(int i = 0; i < 52; i++){
    c = deck->dealCard();
		cout << *c << endl;
    deck->returnCard(c);
	}

  //Swap two randomly selected cards 500 times using that extra blank spot of space
	// for (int i = 0; i < 500; i++){
	// 	int a = dist(rng) % 52;
	// 	int b = dist(rng) % 52;
		
  //   //Swapping of cards now we just exchange pointers
	// 	Deck[52] = Deck[a];
	
  //   Deck[a] = Deck[b];
		
  //   Deck[b] = Deck[52];
		

	// }


  //Print out our shuffled deck
  deck->shuffleDeck();
  cout << endl << "Shuffled cards" << endl;
	for(int i = 0; i < 52; i++){
    c = deck->dealCard();
		cout << *c <<  endl;
    deck->returnCard(c);
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

  //Now we are using a shoe
  Shoe *shoe = new Shoe(6);
	

  //Count up our occurences and print them out
  int occurences[18] = {0};

  int rounds = 0;
  int reshuffles = 0;
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
  Card *a;
  Card *b;
  for(int i = 0; i < rounds; i++){
    
    //Only reshuffle if the flag is true
    if(shoe->getReshuffle()){
      reshuffles++;
      shoe->washDecks();
      shoe->setReshuffleCard();
    }


    //Need top 2 cards
    a = shoe->dealCard();
    b = shoe->dealCard();
    int score = a->getScore() + b->getScore();
    
    //If we got a 22 just change score to a 12 as one ace become a 1s
    //No reducing needed from Cards
    if(score == 22 && (a->getName().compare("Ace") ==0 || b->getName().compare("Ace")) ==0){
      score = 12;
    }

    //cout << score << endl;
    //Increase the value of our occurences
    occurences[score - 4] += 1;

    shoe->returnCard(a);
    shoe->returnCard(b);

  }
  
  //Print out our sim results
  cout << endl << endl;
  for(int i = 0; i < 18; i++){
    
    cout << "There are " << (occurences[i]) << " " << i + 4 << "'s" << endl;
  }
  cout << "Shoe was shuffled " << reshuffles << " times. (This includes the initial shuffling)" << endl;


  //We should be hovering around 18 to 20 as our most common cards since there are a lot more 10 values than others
  //However as we know a quarter of the cards are never used. About one and a half decks worth of cards

  
  delete shoe;
  return 0;
}