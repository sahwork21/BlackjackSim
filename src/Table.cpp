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


//This will be our handles for hitting and returning stuff so we don't have to wait so long
void hitUser(User user, Card *c)
{
  //Just hit depending on what is filling our union
  if(){
    user.better->hitCard(c);
  } 
}



//This is the flag to flip off our game
//It will exit our loop and delete objects
static volatile sig_atomic_t contFlag = 1;
/**
 * On a sig interrupt ctrl C we need to write out our quit message
 */
void signalHandle(int signum)
{
  contFlag = 0;
}


/**
 * This is the main component that will be responsible for constructing objects and taking bets
 * It will take care of making deck operations and betting.
 */
int main()
{

  //Keep our wins and hands played
  int played = 0;
  int wins = 0;


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
  User player;
  if(option == 'y'){

    player.better = new Better();
  }
  else{
    player.player = new Player();
   
  }


  //Shuffle our shoe and place the reshuffle card
  shoe->washDecks();
  shoe->setReshuffle();

  Sleep(3000);
  //Keep playing until the flag is turned off
  while(contFlag){
    cout << "Remember to do ctrl^C to end the game" << endl;
    Sleep(3000);



    //Flush input then deal our cards out
    cin.clear();
    //Ignore all the characters until an EOF
    cin.ignore(INT_MAX);




    //Ask for bets if we have a better
    if(option == 'y'){

      cout << "How much do you want to bet?" << endl;
      int bet;
      cin >> bet;
      bool cont = player.better->makeBet(bet);
      //Deal our cards to player then dealer
      Sleep(1000);
      cout << "Dealing Cards" << endl;
      player.better->hitCard(shoe->dealCard());
      player.better->hitCard(shoe->dealCard());

      dealer->hitCard(shoe->dealCard());
      dealer->hitCard(shoe->dealCard());
      Sleep(3000);
      
      //Tell them what we have
    }
    else{
      //Deal our cards to player then dealer
      Sleep(1000);
      cout << "Dealing Cards" << endl;
      player.player->hitCard(shoe->dealCard());
      player.player->hitCard(shoe->dealCard());

      dealer->hitCard(shoe->dealCard());
      dealer->hitCard(shoe->dealCard());
      Sleep(3000);
    }

    
    
  }
  
 

  //Print out our winnings
  cout << "You won " << wins << " games of " << played << endl;
  if(option == 'y'){
    cout << "You made " << player.better->getMoney() - 500 << " net money" << endl;
  }



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