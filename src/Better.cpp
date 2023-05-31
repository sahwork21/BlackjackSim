/**
 * @file Better.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * Better definition class
 * 
 * 
 */

#include "Better.h"

//Default Constructor setting money to 500
Better::Better()
{
  Better(500);
}

Better::Better(int money)
{
  setMoney(money);
}

Better::~Better()
{
  #ifdef TEST
    std::cout << "Better destroyed" << std::endl;
  #endif
}

//Setters and getters for money
void Better::setMoney(int money)
{
  this->money = money;
}

int Better::getMoney()
{
  return money;
}

//Check if we are bankrupt
//If we have no more money return true to bankruptcy
bool Better::checkBankruptcy()
{
  if(money <= 0){
    return true;
  }
  return false;
}

//Make a bet. Make sure to verify their input
//If they made an invalid bet return false
bool Better::makeBet(int bet)
{
  //Check if bet is more than the money there is
  if(bet > money){
    return false;
  }

  //Remove our money and then return true
  money -= bet;

  return true;

}

//Return winnings to our better
void Better::returnWinnings(int winnings)
{
  money += winnings;
}


