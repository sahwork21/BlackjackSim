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
  score = 0;
  cardCount = 0;
  bust = false;
  hand = new std::vector<Card*>();
}

//We have to destroy our vector and all the cards that may be within it
Player::~Player()
{
  //Destroy all our vector elements
  int r = hand->size();
  for(int i = 0; i < r; i++){
    delete hand->at(i);
  }

  //Then destroy the vector
  delete hand;
}

Player::hit()
{
  
}