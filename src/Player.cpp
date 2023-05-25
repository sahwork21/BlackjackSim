/**
 * @file Player.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the definition for the Player object
 * 
 */

#include "Player.h"



//Default constructor sets
Player::Player()
{
  score = 0;
  
}

Player::~Player()
{

  #ifdef TEST
    std::cout << "Player destroyed" << std::endl;
  #endif
}

int Player::getScore() const
{
  return score;
}

bool Player::getBust() const
{
  if(score > 21){
    return true;
  }
  return false;
}

vector<Card*> Player::getHandCopy() const
{
  return hand;
}

//Hit action
void Player::hitCard(Card* c)
{
  hand.push_back(c);
  score += c->getScore();

  //Change our card if needed
  int i = 0;
  int len = hand.size();
  while(score > 21 && i < len){
    if(hand[i]->getReducable()){
      //We have an ace so we can reduce it and deduct score points
      hand[i]->reduce();
      score -= 10;
    }
    i++;
  }
}

//Return our cards and change them back
//This should be fine since a Player will get cards from a deck and the deck should destroy them
void Player::returnHand()
{
  //Revert every ace back to reducable
  
  //We probably don't have to worry about dropping bits since a hand can only be so big
  int j = hand.size();
  for(int i = 0; i < j; i++){
    if(hand.back()->getName().compare("Ace") == 0){
      hand.back()->restoreReduce();
    }

    //Pop it off our vector
    hand.pop_back();

  }

  //Score should be reduced back to 0 now
  score = 0;
  
}


//std::ostream & operator<<(std::ostream &os, const Player &player);