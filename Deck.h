/**
 * @file Deck.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the header containing prototypes for Deck object functions
 * 
 */
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <random>

/**
 * Container for a deck of Card objects
 * The Deck is really a queue which we contain as a circular array only accessible by some methods
 * Needs to be able to deal cards and return them
 */
class Deck
{
  /**
   * Decks have an Array of 53 card objects. I don't know smart pointers yet
   * It also contains the front and back so we can maintain a circular array for a queue
   */
  private:
    Card *cards[53]; //Nobody should be able to access these values through getters
    int front;
    int back;

    //Method for setting the Deck of Cards up
    void setCards();

  public:
    //Constructor for the deck of cards
    Deck();

    //Destructor for the deck of cards that needs to delete all its cards
    ~Deck();

    //Deal method that removes from the front of the queue
    Card *dealCard();

    //Method that returns Cards
    void returnCard();


    //Method for shuffling a deck of Cards by randomly swapping two cards
    void shuffleDeck();


  
};


#endif