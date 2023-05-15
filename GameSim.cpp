/**
 * @file GameSim.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * @brief This is the simulator for a game of BlackJack that prints the results of a given amount of games
 * It is used to produce a rough probability distribution of each card
 */

#include "Deck.h"
#include <iostream>

//Value for the upper limit of sims you can run
#define SIM_LIMIT 5000


/**
 * Main method that does the simulating some amount of times
 * @param argc the argument count
 * @param argv the cmdline arguments to how many times you want to sim
 * @return 0 on a successful sim 1 if not
 */
int main(int argc, char *argv[])
{
  //We are reading in arguments for how many games you want to play
  //It probably should be at a minimum 30 plays, but it should probably go even higher
  //The created probability distribution will be discrete

  //Not enough arguments given
  if(argc != 2){
    std::cerr << "Usage: ./GameSim RoundsOfSims" << std::endl;
    exit(EXIT_FAILURE);
  }

  //Scan in the rounds of simming argument and it better be a number
  int rounds;
  int match = scanf("%d", &rounds);
  if(match != 1){
    std::cerr << "Enter an integer for rounds of sims" << std::endl;
    exit(EXIT_FAILURE);
  }

  if(rounds < 0 || rounds > SIM_LIMIT){
    std::cerr << "Enter a value between 0 and 5000 for rounds of sims" << std::endl;
    exit(EXIT_FAILURE);
  }


  //Construct our deck of cards with aces on 11's
  Deck *deck = new Deck(11);


  //Now we can run our simulator
  //Hands are just Vectors of Card objects that each person has
  for(int i = 0; i < rounds; i++){
    //We make deal a hand to the player
    std::vector<Card> player;
    std::pair<Card, Card> initHand = deck->dealHand();
  }



  //Destroy all our objects 
  delete deck;



}