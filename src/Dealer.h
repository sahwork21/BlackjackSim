/**
 * @file Dealer.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * Dealers are subclasses of players that will hit until they get to 21
 * They should have their own special to Strings
 * Dealers will keep hitting until they are over 21 in score
 */
#ifndef DEALER_H
#define DEALER_H
#include "Player.h"
#include "Deck.h"


class Dealer: public Player
{

  friend std::ostream& operator<< (std::ostream &os, const Player &d);

  public:
    Dealer();
    ~Dealer();

    //Keep hitting cards from the deck until 17 is reached
    void playHand(Deck *d);
    //Show only the hole card and hide the second
    string showInitialHand();
};

#endif