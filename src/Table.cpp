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

void foundReshuffle()
{
  cout << "Reshuffle card has been drawn. The shoe will be reshuffled after this hand" << endl;
  Sleep(2000);
}

//This will be our handles for hitting and returning stuff so we don't have to wait so long
void hitUser(User *user, Card *c)
{
  //Just hit depending on what is filling our union
  if(user->type == BetterType){
    user->better->hitCard(c);
  } 
  else{
    user->player->hitCard(c);
  }
}

void printHand(User *user)
{
  cout << "You have a " << endl;
  if(user->type == BetterType){
    cout << user->better->getScore() << " with a: " << endl; 
    cout << *(user->better->getHandCopy()[0]) << endl << *(user->better->getHandCopy()[1]) << endl;
  } 
  else{
    cout << user->player->getScore() << " with a: " << endl; 
    cout << *(user->player->getHandCopy()[0]) << endl << *(user->player->getHandCopy()[1]) << endl;
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
  int ties = 0;


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
    player.type = BetterType;
    player.better = new Better();
  }
  else{
    player.type = PlayerType;
    player.player = new Player();
   
  }


  //Shuffle our shoe and place the reshuffle card
  shoe->washDecks();
  shoe->setReshuffle();

  Sleep(3000);
  //Keep playing until the flag is turned off
  while(contFlag){


    //Whenever we draw the reshuffle dummy card we need to tell the user
    if(shoe->getReshuffle()){
      cout << "Shuffling the Shoe" << endl;
      shoe->washDecks();
      shoe->setReshuffleCard();
    }
    Sleep(5000);

    cout << "Remember to do ctrl^C to end the game" << endl;
    Sleep(3000);



    //Flush input then deal our cards out
    cin.clear();
    //Ignore all the characters until an EOF
    cin.ignore(INT_MAX);




    //Ask for bets if we have a better
    int bet = 0;
    if(option == 'y'){

      cout << "How much do you want to bet?" << endl;
      

      string line;
      int temp = 0;
      //Make sure they actually put in valid bets
      do{
        getline(cin, line);

        //Just use stoi and check we have reached a return case after
        temp = stoi(line);

        //Make sure we have entered a new line 
        char nextC;
        cin.get(nextC);

        //Need to either be a \r or \n
        if(nextC == '\r'){
          cin.get(nextC);
          if(nextC == '\n'){
            bet = temp;
          }
        }
        else if(nextC  == '\n' || nextC  == EOF){
          bet = temp;
        }

        

        //Flush input then deal our cards out
        cin.clear();
        //Ignore all the characters until an EOF
        cin.ignore(INT_MAX);
        

        //Check make bet was allowed
        if(bet > player.better->getMoney()){
          bet = 0;
        }

      } while (bet != 0);

      
      cout << "You bet "<< bet << endl;
      player.better->makeBet(bet);
      //Deal our cards to player then dealer
      Sleep(1000);
      
      
    }

    cout << "Dealing Cards" << endl;
    hitUser(&player, shoe->dealCard());
    dealer->hitCard(shoe->dealCard());
    hitUser(&player, shoe->dealCard());
    dealer->hitCard(shoe->dealCard());
    Sleep(3000);

    //Check for the redraw card
    if(shoe->getReshuffle()){
      foundReshuffle();
    }

    //Print out what they have
    printHand(&player);
    Sleep(2000);
    //Print out the dealer's hole card card 2
    cout << "The dealer has a " << *(dealer->getHandCopy()[1]) << endl;
    Sleep(3000);


    //If either party has a blackjack goto END label
    if(player.type == BetterType){
      if(player.better->getScore() == 21){
        goto BLACKJACK;
      }
    }
    else{
      if(player.player->getScore() == 21){
        goto BLACKJACK;
      }   
    }
    if(dealer->getScore() == 21){
      goto BLACKJACK;
    }
    
    

    //Ask the player to hit or stand
    char action = '\0';
    do{
      cout << "Do you want to [h]it or [s]tand?" << endl;
      cin >> action;

      //If it's hit do as the person says
      if(action == 'h'){
        Card *c = shoe->dealCard();
        hitUser(&player, c);
        //Check for the redraw card
        if(shoe->getReshuffle()){
          foundReshuffle();
        }
        
        cout << "Dealing card" << endl;
        Sleep(1000);
        cout << "You got a " << *c << endl;
        Sleep(1000);

        //Tell them what their hand is at now and then bust them if needed
        //If they have reached a 21 or busted they will exit this state
        if(player.type == BetterType){
          cout << "You have a score of " << player.better->getScore() << endl;
          Sleep(1000);
          if(player.better->getScore() == 21){
            action = 's';
          }
          if(player.better->getBust()){
            action = 's';
            cout << "You have gone bust" << endl;
          }
        }
        else{
          cout << "You have a score of " << player.player->getScore() << endl;
          Sleep(1000);
          if(player.player->getScore() == 21){
            action = 's';
          }
          if(player.player->getBust()){
            action = 's';
            cout << "You have gone bust" << endl;
          }
        } 

      }
      //Otherwise it's some invlaid char
      else if(action != 's' && action != 'h'){
        cout << "Make sure to enter a valid character" << endl;
      }
      cin.clear();
      cin.ignore(INT_MAX);
      Sleep(500);

    }while(action != 's');


    cout << "Dealer's turn " << endl;
    //Now the dealer will player their hand


    //Draw our cards and then print them out
    //The user won't know
    while(dealer->getScore() < 17){
      dealer->hitCard(shoe->dealCard());
        //Check for the redraw card
      if(shoe->getReshuffle()){
        foundReshuffle();
      }
    }

    //Print out our cards
    int len = dealer->getHandCopy().size();
    for(int i = 2; i < len; i++){
      cout << "Dealer drew a " << *(dealer->getHandCopy()[i]) << endl;
      Sleep(1000);
    }

    //Flip over the hidden card
    cout << "Dealer flips hidden card " << endl;
    Sleep(1000);
    cout << "It's a " << *(dealer->getHandCopy()[0]);

    //Print out our dealers score
    cout << "Dealer has a " << dealer->getScore() << endl;
    if(dealer->getBust()){
      cout << "Dealer has gone bust"<< endl;
    }

    //Now compare and make a decision
    //This goto label is for if a black jack occurs
    BLACKJACK:

    if(player.type == BetterType){
      //Path if the player has busted
      if(player.better->getBust()){
        //If the dealer has gone bust it's a tie or the dealer wins otherwise and do nothing
        if(dealer->getBust()){
          ties++;
          //Return the bet to the better and increase our ties count
          cout << "Dealer and you are bust. Returning bet" << endl;
          player.better->returnWinnings(bet);
        }
        else{
          cout << "Dealer wins" << endl;
        }
        
      }

      //Dealer has gone bust
      
      else if(dealer->getBust())
      {
        //If you have reached here you have won
        wins++;
        cout << "Dealer went bust. You win with a " << player.better->getScore() << endl;
        player.better->returnWinnings(bet * 2);
      }

      //Neither is bust so just compare scores
      //If you have a blackjack payout by 2.5
      else{
        //Tie
        if(player.better->getScore() == dealer->getScore()){
          ties++;
          cout << "Dealer and you both have a. Returning bet "<< dealer->getScore() << endl;
          player.better->returnWinnings(bet);
        }
        //Loss
        else if(player.better->getScore() < dealer->getScore()){
          cout << "Dealer has a "<< dealer->getScore() << ". You have a " << player.better->getScore() << endl;
          cout << "You lose." << endl;

        }
        //Win
        else{
          wins++;
          cout << "Dealer has a "<< dealer->getScore() << ". You have a " << player.better->getScore() << endl;
          cout << "You win." << endl;
          
          //Check for a black jack
          //2 cards, 21 score, and one is ace 
          if(player.better->getScore() == 21 && player.better->getHandCopy().size() == 2){
            cout << "Blackjack you win 2.5 times your bet" << endl;
            player.better->returnWinnings(bet * 2.5 + 1);
          }
          else{
            player.better->returnWinnings(bet * 2);
          }
        }
      }


      //Return cards to the shoe
      int len = player.better->getHandCopy().size();
      for(int i = 0; i < len; i++){
        shoe->returnCard(player.better->getHandCopy()[i], player.better->getHandCopy()[i]->getOrigin());
      }
      player.better->returnHand();

    }
    else{
      //Path if the player has busted
      if(player.player->getBust()){
        //If the dealer has gone bust it's a tie or the dealer wins otherwise and do nothing
        if(dealer->getBust()){
          ties++;
          //Return the bet to the better and increase our ties count
          cout << "Dealer and you are bust. Returning bet" << endl;
        }
        else{
          cout << "Dealer wins" << endl;
        }
        
      }

      //Dealer has gone bust
      
      else if(dealer->getBust())
      {
        //If you have reached here you have won
        wins++;
        cout << "Dealer went bust. You win with a " << player.player->getScore() << endl;
        
      }

      //Neither is bust so just compare scores
      //If you have a blackjack payout by 2.5
      else{
        //Tie
        if(player.player->getScore() == dealer->getScore()){
          ties++;
          cout << "Dealer and you both have a. Returning bet "<< dealer->getScore() << endl;
          
        }
        //Loss
        else if(player.player->getScore() < dealer->getScore()){
          cout << "Dealer has a "<< dealer->getScore() << ". You have a " << player.player->getScore() << endl;
          cout << "You lose." << endl;

        }
        //Win
        else{
          wins++;
          cout << "Dealer has a "<< dealer->getScore() << ". You have a " << player.player->getScore() << endl;
          cout << "You win." << endl;
          
          //Check for a black jack
          //2 cards, 21 score, and one is ace 
          if(player.better->getScore() == 21 && player.better->getHandCopy().size() == 2)
            cout << "Blackjack" << endl;
          
        }
      }
      int len = player.player->getHandCopy().size();
      for(int i = 0; i < len; i++){
        shoe->returnCard(player.player->getHandCopy()[i], player.player->getHandCopy()[i]->getOrigin());
      }
      player.player->returnHand();
    }


    //Empty out our dealer's hands
    int len = dealer->getHandCopy().size();
    for(int i = 0; i < len; i++){
      shoe->returnCard(dealer->getHandCopy()[i], dealer->getHandCopy()[i]->getOrigin());
    }
    dealer->returnHand();


    played++;

    Sleep(5000);

    //Print out the money our better has left
    if(player.type == BetterType){
      cout << "You have " << player.better->getMoney() << endl;
      
      //If they are bankrupt the game is over
      if(player.better->checkBankruptcy()){
        cout << "You have gone bankrupt and you are thrown out of this casino" << endl;
        contFlag = 0;
      }
    }

    
    Sleep(5000);
    

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

  return 0;


}