/**
 * @file Deck.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the definition of the Deck header file and its prototypes
 */
#include "Deck.h"

//Constructor for a Deck
Deck::Deck()
{
  setCards();
  front = 0;
  back = 51;
}

//Destructor for a Deck
Deck::~Deck()
{
  delete [] cards;
}

//Setter for the cards array
void Deck::setCards()
{
  int cardCount = 0;
	string names[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	int CardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 13; j++){
      //Construct our Card here
      cards[cardCount] = new Card(CardValue[j], suits[i], names[j]);
      cardCount++;
    }
  }
}






