/**
 * @file Shoe.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is a container for a multideck shoe of cards to play BlackJack from
 * A shoe can consist of 6 or 8 decks shuffled together
 */

#ifndef SHOE_H
#define SHOE_H

#include "Deck.h"
#include <vector>

using std::vector;

class Shoe
{
  //We have a count on the decks
  //In real black jack games you can just ask or guess based on height
  private: 
    int deckCount;
    //We have a vector of decks that we will shuffle and then wash together into a queue
    vector<Deck*> decks;

    //A wash is really just some values from 1 to 6 or 8.
    //This number indicates which deck we will draw from
    vector<int> wash;

    //Index of a card indicating the final hand and a reshuffle is coming
    //Place around a quarter into the whole wash
    int reshuffleCard;

    


  public:
    //Constructors and destructors
    Shoe();
    Shoe(int decks);
    ~Shoe();


    //Getters and setters
    void setDeckCount(int deckCount);
    int getDeckCount() const;
    void setDecks();

    //Method to place the card in the deck randomly
    //Needs to be done after shuffling decks and washing the cards together
    void setReshuffleCard();


    //We shuffle each deck of cards place them in the wash then shuffle that up
    void washDecks();


    //We need to be able to deal cards and give them back to us



    



    
};

#endif 