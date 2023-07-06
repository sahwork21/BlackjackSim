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
#include "../Shoe.h"
#include <vector>
#include <thread>
#include <semaphore>



//Class containing a collection of grids and what to do
//It will also have a hand of cards
class Individual
{
  private:
    //Moves are 0 hit, 1 stand, 2 split, 3 double down

    //Rows are your score columns is the dealer card
    int hardHands[17][10];
    //Rows are ace plus the other 9 card types
    int softHands[8][10];
    //Rows are the pair type
    int pairHands[10][10];
    //When playing a sim we check for pairs then softs then hards

    int fitness;

    //Underlying method that will play an individual hand if we split
    //Only splittable twice so if this method recursively calls itself set splittable to false
    //Just modify it and we will check on it later in playRounds
    void playHand(vector<Card*>& hand, Shoe& shoe, bool splittable);


  public:
    //The fields for our individual on this constructor are just random stuff for moves
    Individual();
    //Just fill in the arrays from what we have of a parent
    Individual(int hard[17][10], int soft[8][10], int pair[10][10]);

    //Destructor that just deletes the pointer
    //Since the fields are static allocated it should be good
    ~Individual();
    //Play the required amount of hands to get some idea of how good this model is
    //This will also determine fitness
    void playRounds(int rounds);

    //Compare this individual to another
    bool operator >(const Individual& rhs) const;

    //Get the fitness
    int getFitness() const;

};