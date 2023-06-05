/**
 * @file Table.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the main top level component of the whole blackjack project
 * It will create instances of betters and pit them against a dealer.
 * Multithreading will be used to shuffle the deck and take bets concurrently.
 * We should also wait in between actions so no cheating can occur
 */

#include "Table.h"


using std::cin;
using std::cout;
using std::endl;

/**
 * This is the main component that will be responsible for constructing objects and taking bets
 * It will take care of making deck operations and betting.
 */
int main()
{

  

  //Ask how many decks we should have in our shoe
  cout << "How many decks should we have in the shoe? Between 1 and 8" << endl;

  int decks = 0;
  
  //If someone put an ineligible amount of decks it will just throw an exception
  cin >> decks;

  Shoe *shoe = new Shoe(decks);


  //Wait 2 seconds before proceeding
  Sleep(2000);

  Dealer *dealer = new Dealer();



  //Create our dealer and player
  char option = '\0';
  cout << "Do you want to take bets or play for fun? [y]es to bet or [n]o to play for fun" << endl;

  //Just keep looping until they give us an actual character and not stupid input
  cin >> option;
  while(option != 'y' && option != 'n'){
    cout << "Enter 'y' for bets 'n' for no bets"<< endl;
    cin >> option;
    
  }


  //If it's a y make a better. n make a player
  user player;
  if(option == 'y'){

    player.better = new Better();
  }
  else{
    player.player = new Player();
   
  }



  //Flush



  //Delete all our new objects
  delete shoe;  

  if(option == 'y'){
    delete player.better;
  }
  else{
    delete player.player;
  }
  delete dealer;



}