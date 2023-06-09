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
#include <string>
#include <stdexcept>
#include <ctime>
#define DECK_SIZE 52

//This is how we will represent Cards easily using enums and 
//enum suits{Diamonds, Clubs, Hearts, Spades};

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
    Card *cards[52]; //Nobody should be able to access these values through getters
    int front;
    int back;
    int size;

    //We have our origin identifier to help make a Card
    int origin;

    //Method for setting the Deck of Cards up
    void setCards();

    

  public:
    //Constructor for the deck of cards
    Deck();

    //Constructor for making a deck with tracable origins 
    Deck(int origin);

    //Destructor for the deck of cards that needs to delete all its cards
    ~Deck();

    


    //Deal method that removes from the front of the queue
    Card *dealCard();

    //Method that returns Cards
    void returnCard(Card *card);


    //Method for shuffling a deck of Cards by randomly swapping two cards
    void shuffleDeck();

    //Returns the number of cards left
    int getSize() const;

    //Set and get the origin int
    int getOrigin() const;
    void setOrigin(int origin);


  
};


#endif