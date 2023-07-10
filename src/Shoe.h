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
#include <exception>
#include <algorithm>
//Windows compilation
#ifdef WINDOWS
#include <Windows.h>
#endif

//If You use linux use this and not windows or sleep may not work
#ifdef LINUX
#include <unistd.h>
#endif
using std::vector;
using std::shuffle;

class Shoe
{
  //We have a count on the decks
  //In real black jack games you can just ask or guess based on height
  private: 
    int deckCount;

    //Start as false until -1 is pulled from the wash
    bool reshuffle;

    //This is our vector of a bunch of cards
    vector<Card*> wash;

    //Construct the deck with the an origin
    //void setDecks();

    //is this deck currently in use
    //Useful for synchronization
    bool inUse;
    
    

    //Set up our wash of ints
    void setWash();


    //We need to be able to deal cards and give them back to us
    //Just draw from the front and send to back
    //Enevtually we will find the reshuffle card
    int dealFromWash();


    //Deal from the right deck based on origin
    //What is really happening when dealing from our wash of ints
    Card* dealFromDecks(int origin);


  public:
    //Constructors and destructors
    Shoe();
    Shoe(int decks);
    ~Shoe();


    //Getters and setters
    void setDeckCount(int deckCount);
    void setReshuffle();
    int getDeckCount() const;
    bool getReshuffle() const;
    

    
    

    //Method to place the card in the deck randomly
    //Needs to be done after shuffling decks and washing the cards together
    void setReshuffleCard();



    //We shuffle each deck of cards place them in the wash then shuffle that up
    void washDecks();


    
    //The black box switch that just deals a card. Flips the reshuffle flag itelf
    Card *dealCard();
    

    //Return a card with the correct origin
    void returnCard(Card *card);

    //Flip the flag for inUse
    void inUsing();
    void notUsing();    
    bool getUsing() const;


    
    



    
};

#endif 