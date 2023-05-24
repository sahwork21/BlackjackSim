/**
 * @file Player.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the header file for the player object which is the super class for dealer and user
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>
#include <stdbool.h>

using std::vector;

/**
 * PLayer objects contain a score and a collection of cards
 * It also checks if the player has busted or not
 */
class Player
{
  //Fields are the score, money, have they gone bust, and their hand of cards
  private:
    int score;
    int money;
    //int cardCount;
    bool bust;
    vector<Card*> hand;
  


  public:
    //Default constructor that gives a definite 500 of inital bettings
    Player();

    //Destructor
    ~Player();

    //Parametrized constructor that determines money
    Player(int money);

    

    //Hit a card
    void hit(Card *c);

    //Clear the hand and send our cards back to the deck
    //void clear();

    //Make a bet that will be done soon
    //void bet(int bet);

    //Getters and Setters
    int getScore() const;
    int getMoney() const;
    int getCardCount() const;
    bool getBust() const;
    vector<Card*> getHand() const; 

    void setMoney(int money);

  //Output stream which the subclasses will have to define later on
  //friend std::ostream & operator<<(std::ostream &os, const Player &player);
  


};

#endif 