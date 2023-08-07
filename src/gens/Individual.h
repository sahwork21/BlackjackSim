/**
 * @file Individual.cpp
 * @author your name (you@domain.com)
 * This is an individual player in a game of BlackJack
 * It will have to consider things like hand and aces in hand when playing the game
 * The available moves will be stand, hit, double down, and split
 * Blackjacks pay out 3:2 and dealers will hit until 17 or more is their score
 * 
 * Individuals will have a table of what to do when they have an ace, pair, or regular hand. Also has to consider dealers hole card
 * They will also have to consider bets but we can do that later
 * 
 * I made those other classes as a practice and a waste of time
 * 
 * 
 */
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "../Shoe.h"

#include <vector>
#include <stdio.h>
#include <cstring>
#include <random>

#ifdef TEST
#include <iostream>
#endif

// #include <thread>
// #include <mutex>  
// #include <condition_variable>  
//#include <pthread.h>



typedef enum{Hit, Stand, DoubleDown, Split} Move;



#define HARD_ROWS 16;
#define SOFT_ROWS 8;
#define PAIR_ROWS 10;
#define COLS 10;
//Class containing a collection of grids and what to do
//It will also have a hand of cards
class Individual
{
  private:
    //Our mutex lock for playing hands
    //pthread_mutex_t lock;
    

    //Conditional variable to check if the shoe is currently in use
    //pthread_cond_t cv;

    //***************TODO make split work with some synchronization
    //Moves are 0 hit, 1 stand, 2 double down, 3 is split for future
    //0 row is the lowest scores

    //Rows are your score columns is the dealer card
    Move hardHands[16][10];
    //Rows are ace plus the other 9 card types
    Move softHands[8][10];
    //Rows are the pair type
    Move pairHands[10][10];
    //When playing a sim we check for pairs then softs then hards

    int fitness;

    //Collection of moves for construction purposes
    

    //Underlying method that will play an individual hand if we split
    //Only splittable twice so if this method recursively calls itself set splittable to false
    //Just modify it and we will check on it later in playRounds
    void playHand(vector<Card*>& hand, Shoe& shoe, vector<int>& scores, int dealerCard, bool splittable, int depth);


    //Random number generator for creating new Individuals and move tables
    //Engine for a random numbers
    //std::mt19937 nums;
    //population distribution selector. Goes 0 to 11 so we don't need distributions
    //std::uniform_int_distribution<int> moveDist;
    //Generate a random digit 1 - 100 to get probabilites
    //std::uniform_int_distribution<int> crossDist;

  public:
    //The fields for our individual on this constructor are just random stuff for moves
    Individual();
    //Just fill in the arrays from what we have of a parent
    Individual(Move hard[16][10], Move soft[8][10], Move pair[10][10]);

    //Special constructor that makes new individuals by combining two existing ones
    //Individual(Individual *i1, Individual *i2, int mutatePercent, int crossPercent);

    //Destructor that just deletes the pointer
    //Since the fields are static allocated it should be good
    ~Individual();
    //Play the required amount of hands to get some idea of how good this model is
    //This will also determine fitness
    void playRounds(int rounds);

    //Compare this individual to another
    //Return true if we are greater, false otherwise
    bool operator>(const Individual& other) const;


    //Default sort operator
    bool operator<(const Individual& other) const;

    //Get the fitness
    int getFitness() const;


    //Get move squares
    Move getHardHands(int r, int c) const;
    Move getSoftHands(int r, int c) const;
    Move getPairHands(int r, int c) const;

    #ifdef TEST
    void setFitness(int fitness);
    #endif

    //Set fitness to 0
    void resetFitness();

    Move moveCollection[4] = {Hit, Stand, DoubleDown, Split};

};



#endif