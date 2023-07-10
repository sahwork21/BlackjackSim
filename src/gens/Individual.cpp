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
//Remember 0 = hit, 1 = stand, 2 = double down, 3 = split
//Splitting only available when in pairs
Individual::Individual() : fitness(0)
{
  //Seed time and then just generate some random numbers
  srand(time(NULL));

  //Fill hards softs then pairs
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 10; j++){
      hardHands[i][j] = rand() % 3;
    }
  }

  //Fill in softs then hards then pairs
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 10; j++){
      softHands[i][j] = rand() % 3;
    }
  }
  //Fill in softs then hards then pairs
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      pairHands[i][j] = rand() % 4;
    }
  }
}


//Constructor from an existing 2d array of moves
Individual::Individual(Move hard[16][10], Move soft[8][10], Move pair[10][10]) : fitness(0)
{
  //Just use memcpy to copy in the parameters
  memcpy(&hardHands, &hard, sizeof(hardHands));
  memcpy(&softHands, &soft, sizeof(softHands));
  memcpy(&pairHands, &pair, sizeof(pairHands));

}

void Individual::playHand(vector<Card*>& hand, Shoe& shoe, vector<int>& scores, int dealerCard, bool splittable)
{
  
  
  //Lock out the other threads before doing stuff
  //Check a conditional variable if the shoe is not currently being used
  lock.lock();

  //You can enter the critical section when the shoe is not in use
  //When this flag is false you may pass
  while(shoe.getUsing()){
    cv.wait(lock);
  }

  //set the flag to true and lock out all the other threads
  shoe.inUsing();

  Move instruction = Hit;

  int score = hand[0]->getScore() + hand[1]->getScore();

  //Now we need to check our table out for what to do
  //Keep going until we are told to stand, split, or 21 is reached
  while(score < 21 && instruction == Hit){
    //Check pairs then if we have an ace for a softhand
    if(hand.size == 2 && (hand[0]->getName().compare(hand[1]->getName()) || hand[0]->getScore() == hand[1]->getScore())){
      
      instruction = pairHands[hand[1]->getScore() - 2][dealerCard - 2];
      
    }

    //Check softhands if there is an ace that is reducable
    else if(hand[0]->getName().compare("Ace")){
      instruction = softHands[hand[1]->getScore() - 2][dealerCard - 2];
    }
    else if(hand[1]->getName().compare("Ace")){
      instruction = softHands[hand[0]->getScore() - 2][dealerCard - 2];
    }

    //Check hard hands next if we have no move or we will split and its unsplittable
    if(instruction == -1 || (instruction == Split && !splittable)){
      instruction = hardHands[score - 5][dealerCard - 2];
    }
    
  }


  //Unlock the critical section and let some other thread in
  shoe.notUsing();

  //Add scores to back
  int scores
  scores.push_back();
  lock.unlock();
  cv.notify_one();

  

}

//Just statically allocate a six deck shoe of cards like GameSim does and play against a dealer
void Individual::playRounds(int rounds)
{
  //Seed our random values
  rng.seed(time(0));

  //Now we are using a shoe
  Shoe *shoe = new Shoe(6);

  //Now play our game
  //
  vector<int> scores;
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

    int dealerScore = dealer[0]->getScore() + dealer[1]->getScore();

    //Reduce an ace if needed
    if(hand[0]->getScore() + hand[1]->getScore() == 22){
     
      hand[0]->reduce();
      
    }

    if(dealerScore == 22){
     
      dealer[0]->reduce();
      dealerScore = 12;
    }



    //Now we check for pairs then check if we have an ace then we will play the game
    //Keep playing until we get a 1 to stand
    //This should be played like a thread

    //We will wait and continue to wait until this is done before dealing cards to our dealer
    //We need to wait on this hand thread to end and we rejoin with it
    //We will have to use a mutex lock to make sure that only one hand is getting cards at a time
    //If we have 21 just skip to the comparing part

    if(hand[0]->getScore() + hand[1]->getScore() != 21){
      thread hand(playHand, &hand, &shoe, &scores, dealer[1]->getScore(), true);

      //Wait for hand thread to finish up
      hand.join();
    }
    else{
      scores.push_back(21);
    }


    //Play the dealer's hand out
    while(dealerScore < 17){
      dealer.push_back(shoe->dealCard());

      //If we went bust we need to check for anything to reduce
      if(dealerScore > 21){
        int len = dealer.size();
        int i = 0;
        while(i < len && dealerScore > 21){

          //We can reduce something
          if(dealer[i]->getReducable()){
            dealer[i]->reduce();
            score -= 10;
          }
        }
      }

      
    }

    //Now compare scores and add to fitness
    int len = scores.size();
    for(int i = 0; i < len; i++){

      //We win if we are under 21 and the dealer went bust or we have a greater score
      if(scores[i] > 21){
        if(dealerScore <= 21){
          fitness--;
        }
      
      }
      else{
        if(scores[i] > dealerScore || dealerScore > 21){
          fitness++;
        }
      }
    }

    //Now return the dealer's cards
    //The player's cards should return themsevles when being counted up

    while(dealer.size() > 0){
      shoe->returnCard(dealer[0]);
    }

    scores.clear();


  }
}


