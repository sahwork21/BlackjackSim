/**
 * @file Deck.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * @brief This is the Deck object which is really a vector of 52 cards.
 * It should also have the capabilities of intializing cards and shuffling the deck.
 * It will also have deal and return cards but these are really just push_back and remove
 * front.
 * 
 * 
 */
#include "Card.h"
#include <vector>

class Deck
{
  private:
    std::vector<Card> Cards;
};
