/**
 * @file Player.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the definition for the Player object
 * 
 */

#include "Player.h"



//Default constructor sets us up with 500 money
Player::Player()
{
  Player(500);
}

Player::Player(int money)
{
  setMoney(500);
  this->score = 0;
  //cardCount = 0;
  this->bust = false;
  
}

//We have to destroy our vector and all the cards that may be within it
Player::~Player()
{
  //Destroy all our vector elements

  // int r = hand->size();
  // for(int i = 0; i < r; i++){
  //   #ifdef TEST
  //     std::cout << *(hand->at(i)) << " Was destroyed" << endl;
  //   #endif
  //   delete hand->at(i);
    
  // }

  //Then destroy the vector
  #ifdef TEST
      std::cout << "Hand vector was destroyed" << std::endl;
    #endif
  delete hand;
}

//Just add the card to back and update our fields
void Player::hit(Card *c)
{
  hand->push_back(c);
  score += c->getScore();
  
  //Run some checks to see if the score can be reduced
  //Can convert an ace from 11 to 1
  int i = 0;
  int count = hand->size();
  while(score > 21 && i < count){
    //Check if this is an ace that has reducable set to true
    if(hand->at(i)->getReducable()){
      hand->at(i)->reduce();
      score -= 10;
      //Ace has gone from 11 to 1S
    }
    i++;
  }

  //If we couldn't reduce our score you have gone bust
  if(score > 21){
    bust = true;
  }

}

//Clear our vector of the card pointers since we don't need the container

int Player::getScore() const
{
  return score;
}
int Player::getMoney() const
{
  return money;
}
int Player::getCardCount() const
{
  return hand->size();
}
bool Player::getBust() const
{
  return bust;
}
vector<Card*> *Player::getHand() const
{
  return hand;
}

void Player::setMoney(int money)
{
  this->money = money;
}

//std::ostream & operator<<(std::ostream &os, const Player &player);