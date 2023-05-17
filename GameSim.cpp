/**
 * @file GameSim.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * @brief This is just a C file disguised as C++ to help restart the implementation
 * 
 * 
 */
#include <stdio.h>
#include <ctime>
#include <iostream>
#include <string>

//We will be using strings in our cards struct
using std::string;
using std::cout;
using std::cin;
using std::endl;

struct DefineCard
{
	string suit;
	string name;
	int score;   // Score is the name of the card or Ace which can be 11 or 1
} Deck[53]; // We need extra space to shuffle


int main()
{
	int cardCount = 0;
	string names[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	int CardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 13; j++){
      Deck[cardCount].name = names[j];
		  Deck[cardCount].suit = suits[i];
		  Deck[cardCount].score = CardValue[j];
      cardCount++;
    }
  }
	
	
  //Print out the cards we have
  cout << "Cards in order" << endl;
	for(int x = 0; x < 52; x ++){
		cout << Deck[x].name << " of " << Deck[x].suit << ": Value of " << Deck[x].score << endl;
	}

  //Swap two randomly selected cards 500 times using that extra blank spot of space
	for (int i = 0; i < 500; i++){
		int a = rand() % 52;
		int b = rand() % 52;
		
		Deck[52].name = Deck[a].name;
		Deck[52].suit = Deck[a].suit;
		Deck[52].score = Deck[a].score;
		

		Deck[a].name = Deck[b].name;
		Deck[a].suit = Deck[b].suit;
		Deck[a].score = Deck[b].score;
		

		Deck[b].name = Deck[52].name;
		Deck[b].suit = Deck[52].suit;
		Deck[b].score = Deck[52].score;
		

	}

  //Print out our shuffled deck
  cout << endl << "Shuffled cards" << endl;
	for(int i = 0; i < 52; i++){
		cout << Deck[i].name << " of " << Deck[i].suit << " : Value of " << Deck[i].score <<  endl;
	}

	
	
  return 0;
}