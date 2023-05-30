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


using std::vector;

/**
 * PLayer objects contain a score and a collection of cards
 * It also checks if the player has busted or not
 */
class Player
{
  friend std::ostream & operator<<(std::ostream &os, const Player &player);
  //Should have a score and hand everything else can just be calculated
  private:
    int score;
    vector<Card*> hand;
  
  public:
    //Constructors
    Player();
    //Destructor has to do nothing since new was never called
    ~Player();

    
    void setScore(int score);
    int getScore() const;
    bool getBust() const;
    vector<Card*> getHandCopy() const;

    //Method to add a card to the hand
    void hitCard(Card* c);

    void returnHand();

  

};

#endif 