/**
 * @file Dealer.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the class definition for a dealer
 * 
 */
#include "Dealer.h"

//Just use our Player class to do this stuff
Dealer::Dealer()
{
  setScore(0);
}

Dealer::~Dealer()
{
  #ifdef TEST
    std::cout << "Dealer destroyed" << std::endl;
  #endif
}

//Just keep hitting until score is greater than or equal to 17
//Just give us the deck for the game to modify
void Dealer::playHand(Deck *d)
{
  while(getScore() < 17){
    hitCard(d->dealCard());
  }

}

//Only show the first card and hide the second
string Dealer::showInitialHand()
{
  return "Dealer has " + getHandCopy()[0]->getName() + " of " + getHandCopy()[0]->getSuit();
  
}

std::ostream& operator<<(std::ostream & os, const Dealer & d)
{
  os << "Dealer has a score of " << d.getScore() << std::endl << "Dealer has: " << std::endl;

  //List out all the cards we have
  int len = d.getHandCopy().size();
  for(int i = 0; i < len; i++){
    os << d.getHandCopy()[i]->getName() << " of " << d.getHandCopy()[i]->getSuit() << std::endl;
  }

  return os;
}