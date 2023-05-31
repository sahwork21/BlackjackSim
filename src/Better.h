/**
 * @file Better.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * Header file for a player subclass that can make bets
 * 
 */

#ifndef BETTER_H
#define BETTER_H

#include "Player.h"

class Better: public Player
{
  private:
    //Betters really just can only make bets
    int money;
  
  public:
    //Constructors and destructors
    Better();
    Better(int money);
    ~Better();

    //Setters and getters for money and checks for bankruptcy
    void setMoney(int money);
    int getMoney();

    bool checkBankruptcy();

    //Make bets
    bool makeBet(int bet);
    //Return money to the better
    void returnWinnings(int winnings);


};

#endif