/**
 * @file Individual.cpp
 * @author your name (you@domain.com)
 * This is an individual player in a game of BlackJack
 * It will have to consider things like hand and aces in hand when playing the game
 * The available moves will be stand, hit, double down, and split
 * Blackjacks pay out 3:2 and dealers will hit until 17 or more is their score
 * 
 * Individuals will have a table of what to do when they have an ace, pair, or regular hand
 * 
 * I made those other classes as a practice and a waste of time
 * 
 * 
 */
#include "Individual.h"




//Simple destructor
Individual::~Individual()
{
  //Nothing is really destroyed since we never use a new keyword
}

//Randomly construct our moves using a random value
//Remember 0 = hit, 1 = stand, 2 = split, 3 = double down
Individual::Individual() : fitness(0)
{
  //Seed time and then just generate some random numbers
  srand(time(NULL));

  //Fill in softs then hards then pairs
  for(int i = 0; i < 17; i++){
    for(int j = 0; j < 10; j++){
      softHands[i][j] = rand() % 4;
    }
  }

  //Fill in softs then hards then pairs
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 10; j++){
      hardHands[i][j] = rand() % 4;
    }
  }
  //Fill in softs then hards then pairs
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      hardHands[i][j] = rand() % 4;
    }
  }
}


//Constructor from an existing 2d array of moves
Individual::Individual(int hard[17][10], int soft[8][10], int pair[10][10]) : fitness(0)
{
  //Just use memcpy to copy in the parameters
  memcpy(&hardHands, &hard, sizeof(hardHands));
  memcpy(&softHands, &soft, sizeof(softHands));
  memcpy(&pairHands, &pair, sizeof(pairHands));

}

void Individual::playHand(vector<Card*>& hand, Shoe& shoe, bool splittable)
{
  //Lock out the other threads before doing stuff
  //Check a conditional variable if the shoe is not currently being used
  while(){

  }

}

//Just statically allocate a six deck shoe of cards like GameSim does and play against a dealer
void Individual::playRounds(int rounds)
{
  //Seed our random values
  rng.seed(time(0));

  //Now we are using a shoe
  Shoe *shoe = new Shoe(6);

  //Now play our game
  vector<Card*> hand;
  vector<Card*> dealer;
  for(int i = 0; i < rounds; i++){
    

    //Only reshuffle if the flag is true
    if(shoe->getReshuffle()){
      
      shoe->washDecks();
      shoe->setReshuffleCard();
    }
    
    //Deal our initial hands
    hand.push_back(shoe->dealCard());
    dealer.push_back(shoe->dealCard());
    hand.push_back(shoe->dealCard());
    dealer.push_back(shoe->dealCard());


    //Now we check for pairs then check if we have an ace then we will play the game
    //Keep playing until we get a 1 to stand
    //This should be played like a thread

    //We will wait and continue to wait until this is done before dealing cards to our dealer
    //We need to wait on this hand thread to end and we rejoin with it
    //We will have to use a mutex lock to make sure that only one hand is getting cards at a time

    thread hand(playHand, &hand, &shoe, true);

    //Wait for hand thread to finish up
    hand.join();



  }
}


