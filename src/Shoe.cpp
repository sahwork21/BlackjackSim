/**
 * @file Shoe.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * Definition of the shoe that is meant to be our source of cards for a true casino game
 */

#include "Shoe.h"

//Default constructor setting our deck up to have six decks
Shoe::Shoe()
{
  Shoe(6);
}

Shoe::Shoe(int decks)
{
  setDeckCount(decks);

  //Now generate decks
}

Shoe::~Shoe()
{
  //We don't need to delete any Cards since the deck will do that for us
  for(int i = 0; i < deckCount; i++){
    delete decks[i];
  }

  #ifdef TEST
    std::cout << "Shoe destroyed" << std::endl;
  #endif
}

//Set our count for our deck
void Shoe::setDeckCount(int decks)
{
  this->deckCount = decks;
}

//Generate a deck after we know how many decks to make
void Shoe::setDecks()
{
  for(int i = 0; i < deckCount; i++){
    
  }
}
