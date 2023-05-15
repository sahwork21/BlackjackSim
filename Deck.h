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
#include <vector>
#include <stdexcept>
#include <string>
#include <memory>
#include <cstdlib>



//Macros for our names and suits
#define NAMES {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}
#define SUITS {"Clubs", "Spades", "Hearts", "Diamonds"}

class Deck
{
  // Fields
private:
  std::deque<Card> *Cards;
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
    Cards = new std::deque<Card>;
    setCards(aValue);
    setCount(52);
  }

  // Destructor where we have to destroy the deque
  ~Deck()
  {
    delete Cards;
  }

  // Getters and setter
  std::deque<Card>* getCards() const
  {
    return Cards;
  }

  void setCards(int aValue)
  {
    //We need to construct 52 cards
    //Construct each of our Cards
    std::string suits[4] = SUITS;
    std::string names[13] = NAMES;


    //Just make each card now using smart pointers
    for(int i = 0; i < 13; i++){
      int val = 1;
      for(int j = 0; j < 4; j++){
        //Card *c = (Card *) malloc (sizeof(Card));
        switch (i){
        //Ace case
        case 0:{
          std::shared_ptr<Card> c (new Card(aValue, names[i], suits[j]));
          Cards->push_back(*c);
          break;
        }
        default:
        {
          std::shared_ptr<Card> c (new Card(val, names[i], suits[j]));
          Cards->push_back(*c);
          break;
        }
        }
        
      }
      if(i < 10){
        //We need jack, queen, king to stay the same value
        val++;
      }
    }
  }

  int getCount() const
  {
    return count;
  }

  void setCount(int count)
  {
    this->count = count;
  }

  //Decks need to be able to shuffle themselves
  /**
   * This is the shuffle function for the deck that uses a riffle shuffle.
   * Just uses both iterators at the beginning and end to shuffle cards randomly to the end of the deque
   */
  void shuffle()
  {
    int left = 0;
    int right = 0;

    //Move one iterator to the front and card 27
    std::deque<Card>::iterator leftIt = Cards->begin();
    std::deque<Card>::iterator rightIt = Cards->begin();

    for(int i = 0; i < 27; i++){
      rightIt++;
    }

    //Keep moving cards to the end randomly 
    while(left < 26 && right < 26){
      //Move 1 to 3 cards to the back for each half of the deck
      int moves = rand() % 3 + 1;
      
      for(int i = 0; i < moves; i++){
        Cards->push_back(*leftIt);
        leftIt++;
      }
      left += moves;

      moves = rand() % 3 + 1;

      for(int i = 0; i < moves; i++){
        Cards->push_back(*rightIt);
        rightIt++;
      }
      right += moves;
    }

  }

  /**
   * This is the method that makes an initial dealing of cards to the player or dealer
   * @return a pair of Card objects to the calling method
   */
  std::pair<Card, Card> dealHand()
  {
    //Pop off the front of the deque and return the two cards at the front of the deque
    std::pair<Card, Card> hand (Cards->front(), Cards->front());
    Cards->pop_front();
    hand.second = Cards->front();
    Cards->pop_front();
    count -= 2;

    //Now return the hand to the player
    return hand;
  }

  /**
   * Deals a card to the player or dealer upon its call
   * @return the front card in the deque
   * 
   */
  Card hit()
  {
    Card ret = Cards->front();
    Cards->pop_front();
    count--;
    return ret;
  }

  /**
   * Returns the cards from the hands of the dealer and player to be put back into the deck
   */
  void returnHand(std::vector<Card> hand, int count)
  { 
    for(int i = 0; i < count; i++){
      Cards->push_back(hand[i]);
    }
    this->count += count;
  }
};
