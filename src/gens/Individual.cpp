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
      hardHands[i][j] = moveCollection[rand() % 3];
    }
  }

  //Fill in softs then hards then pairs
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 10; j++){
      softHands[i][j] = moveCollection[rand() % 3];
    }
  }
  //Fill in softs then hards then pairs
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      pairHands[i][j] = moveCollection[rand() % 4];
    }
  }

  //lock = PTHREAD_MUTEX_INITIALIZER;
  //cv = PTHREAD_COND_INITIALIZER;

}


//Constructor from an existing 2d array of moves
Individual::Individual(Move hard[16][10], Move soft[8][10], Move pair[10][10]) : fitness(0)
{
  //Just use memcpy to copy in the parameters
  std::memcpy(hardHands, hard, sizeof(hardHands));
  std::memcpy(softHands, soft, sizeof(softHands));
  std::memcpy(pairHands, pair, sizeof(pairHands));
  //lock = PTHREAD_MUTEX_INITIALIZER;
  //cv = PTHREAD_COND_INITIALIZER;

}

void Individual::playHand(vector<Card*>& hand, Shoe& shoe, vector<int>& scores, int dealerCard, bool splittable, int depth)
{
  
  
  //Lock out the other threads before doing stuff
  //Check a conditional variable if the shoe is not currently being used
  //pthread_mutex_lock(&lock);

  //You can enter the critical section when the shoe is not in use
  //When this flag is false you may pass
  // while(shoe.getUsing()){
  //   cv.wait(lk);
  // }

  //set the flag to true and lock out all the other threads
  shoe.inUsing();

  Move instruction = Hit;

  int score = hand[0]->getScore() + hand[1]->getScore();

  //Now we need to check our table out for what to do
  //Keep going until we are told to stand, split, or 21 is reached
  while(score < 21 && instruction == Hit){
    //Check pairs then if we have an ace for a softhand
    if(hand.size() == 2 && (hand[0]->getName().compare(hand[1]->getName()) == 0 || hand[0]->getScore() == hand[1]->getScore())){
      
      instruction = pairHands[hand[1]->getScore() - 2][dealerCard - 2];
      
    }

    //Check softhands if there is an ace that is reducable
    else if(hand[0]->getName().compare("Ace") == 0){
      instruction = softHands[hand[1]->getScore() - 2][dealerCard - 2];
    }
    else if(hand[1]->getName().compare("Ace") == 0){
      instruction = softHands[hand[0]->getScore() - 2][dealerCard - 2];
    }

    //Check hard hands next if we found no move in any of the tables
    else{
      instruction = hardHands[score - 5][dealerCard - 2];
    }

    //If we are in a split in a non splittable hand just pick from the hards

    //Hit or double down if told to do so
    if(instruction == Hit || instruction == DoubleDown){
      hand.push_back(shoe.dealCard());
      score += hand.back()->getScore();
      //Check if we have exceeded 21 before reentering the loop
      bool reduce = false;
      int len = hand.size();
      if(score > 21){
        for(int i = 0; i < len; i++){
          //If our card is reducable and reduce is false reduce the ace and decrease the score
          if(hand[i]->getReducable() && !reduce){
            hand[i]->reduce();
            reduce = true;
            score -= 10;
          }
        }
      }
    }

    
    
  }

  if(instruction == Split){
    #ifdef TEST
      std::cout << *(hand[0]) << std::endl;
      std::cout << *(hand[1]) << std::endl;
      std::cout << "Splitting" << std::endl;
    #endif


    //Create two vectors and make two more threads
    vector<Card*> one;
    one.push_back(hand.front());
    one.push_back(shoe.dealCard());
    vector<Card*> two;
    two.push_back(hand.back());
    two.push_back(shoe.dealCard());
    //We should probably wait on threads to finish so their resources don't disappear, but I don't know if they do
    //Maybe it's like Java or not
    hand.pop_back();
    hand.pop_back();
    
    if(depth <= 1){
      playHand(one, shoe, scores, dealerCard, true, depth + 1);
      playHand(two, shoe, scores, dealerCard, true, depth + 1);

      
    }
    else{
      playHand(one, shoe, scores, dealerCard, false, depth + 1);
      playHand(two, shoe, scores, dealerCard, false, depth + 1);
      
    }

  }
  //Unlock the critical section and let some other thread in
  // shoe.notUsing();  
  // lk.unlock();
  // cv.notify_one();
  //End of critical section

  //Either we have to split the hand or just tally up the score 
  
  else{
    //Tally up the score and return our cards
    #ifdef TEST
      std::cout << "Score is " << score << std::endl;
    #endif
    scores.push_back(score);
    while(hand.size() > 0){
      hand.pop_back();
    }
  }

  

  

}

//Just statically allocate a six deck shoe of cards like GameSim does and play against a dealer
void Individual::playRounds(int rounds)
{
  //Seed our random values
  srand(time(0));

  //Now we are using a shoe
  Shoe *shoe = new Shoe(6);

  //Now play our game
  //
  vector<int> scores;
  vector<Card*> hand;
  vector<Card*> dealer;
  //pthread_t pid;
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
    //We know these are both aces 
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
      //This thread will not return anything it just modifies scores
      //pthread_create(&pid, );
      playHand(hand, *shoe, scores, dealer[1]->getScore(), false, 0);
      //Wait for hand thread to finish up
      //hand.join();
    }
    else{
      #ifdef TEST
      std::cout << "Score is 21" << std::endl;
      #endif
      scores.push_back(21);
      //Return our cards too
      shoe->returnCard(hand[hand.size() - 1]);
      hand.pop_back();
      shoe->returnCard(hand[hand.size() - 1]);
      hand.pop_back();
    }


    //Play the dealer's hand out
    while(dealerScore < 17){
      dealer.push_back(shoe->dealCard());
      //add up the score from the last card
      dealerScore += dealer[dealer.size() - 1]->getScore();

      //If we went bust we need to check for anything to reduce
      if(dealerScore > 21){
        int len = dealer.size();
        int i = 0;
        while(i < len && dealerScore > 21){
        
          //We can reduce something
          if(dealer[i]->getReducable()){
            dealer[i]->reduce();
            dealerScore -= 10;
          }
          i++;
        }
      }

      
    }

    //Now compare scores and add to fitness
    int len = scores.size();
    for(int i = 0; i < len; i++){
      #ifdef TEST
      std::cout << "Dealer Score vs Ind Score: " << dealerScore << " " << scores[i] << std::endl;
      #endif
      //We win if we are under 21 and the dealer went bust or we have a greater score
      if(scores[i] > 21){

        //We busted and the dealer didn't so we lose
        if(dealerScore <= 21){
          fitness--;
        }
      
      }
      else{

        //We didn't bust and we have a better score or dealer busted
        if(scores[i] > dealerScore || dealerScore > 21){
          fitness++;
        }
        else if(dealerScore > scores[i]){
          fitness--;
        }
      }
    }

    //Now return the dealer's cards
    //The player's cards should return themsevles when being counted up

    while(dealer.size() > 0){
      shoe->returnCard(dealer[dealer.size() - 1]);
      dealer.pop_back();
    }

    scores.clear();


  }

  #ifdef TEST
  std::cout << "Fitness: " << fitness << std::endl;
  #endif
}


//Just compare the fitness of two of these objects
bool Individual::operator>(const Individual & other) const
{
  return this->fitness > other.getFitness();
}

bool Individual::operator<(const Individual & other) const
{
  return this->fitness < other.getFitness();
  
}

int Individual::getFitness() const
{
  return fitness;
}

#ifdef TEST
void Individual::setFitness(int fitness)
{
  this->fitness = fitness;
}
#endif

