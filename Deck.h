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
#include <deque>
#include <stdexcept>
#include <string>


//Macros for our names and suits
#define NAMES {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}
#define SUITS {"Clubs", "Spades", "Hearts", "Diamonds"}

class Deck
{
  // Fields
private:
  std::deque<Card> Cards;
  int count;

public:
  // Constructors have to differentiate what the value of an ace is depending on our game
  // Default constructor setting aces to 11 for our concerns of Blackjack
  Deck()
  {
    Deck(11);
  }

  // Parametrized constructor only allow 11 or 1 for our blackjack game
  Deck(int aValue)
  {
    if (aValue != 1 && aValue != 11)
    {
      throw std::invalid_argument("Received invalid Ace value");
    }

    setCards(aValue);
    setCount(52);
  }

  // Destructor where we have to destroy all 52 cards by freeing them
  ~Deck()
  {
    for(int i = 0; i < 52; i++){
      Card c = Cards.front();
      Cards.pop_front();
      free(&c);
      //Just free all our cards from the deque
    }

    //Then destroy the deque
  }

  // Getters and setter
  std::deque<Card> getCards()
  {
    return Cards;
  }

  void setCards(int aValue)
  {
    //We need to construct 52 cards
    //Construct each of our Cards
    std::string suits[4] = SUITS;
    std::string names[13] = NAMES;


    //We need to heap allocate these cards so they don't go out of scope when this stack pops off
    for(int i = 0; i < 13; i++){
      for(int j = 0; j < 4; j++){
        Card *c = (Card *) malloc (sizeof(Card));
        Card *c = new Card(1, names[i], suits[j]);
        Cards.push_back(*c);
      }
    }
  }

  int getCount()
  {
    return count;
  }

  void setCount(int count){
    this->count = count;
  }
};
