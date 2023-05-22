/**
 * @file Deck.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the definition of the Deck header file and its prototypes
 */
#include "Deck.h"

using std::invalid_argument;

//Constructor for a Deck
Deck::Deck()
{
  
  setCards();
  front = 0;
  //Back points to the next open spot in the array
  back = DECK_SIZE;
}

//Destructor for a Deck
Deck::~Deck()
{
  for(int i = 0; i < DECK_SIZE; i++){
    delete cards[i];
  }
}

//Setter for the cards array
void Deck::setCards()
{
  
  int cardCount = 0;
	string names[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	int CardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 13; j++){
      //Construct our Card here
      cards[cardCount] = new Card(CardValue[j], suits[i], names[j]);
      cardCount++;
    }
  }
}

//Simply gets the card at the front of the array
Card* Deck::dealCard()
{

  //Need an exception for an empty deck
  //Exception occurs when front = back so we are trying to get from an empty spot
  if(front % DECK_SIZE == back % DECK_SIZE){
    throw invalid_argument("Attempting to deal a Card from an empty deck");
  }


  //Get the top card
  Card *ret = cards[(++front) % DECK_SIZE];
  
  //Change our front value and we don't want it to get too large
  front %= DECK_SIZE;

  return ret;

}

//Return a Card to our deck
void Deck::returnCard(Card *card)
{

  //We are trying to return a Card to a full array
  if(front % DECK_SIZE == back % DECK_SIZE){
    throw invalid_argument("Attempting to deal a Card from an empty deck");
  }

  //Put our card back in the queue
  cards[(++back) % 52] = card;

  //Change our back
  back %= back;

}

//Shuffles our deck by randomly swapping cards
void Deck::shuffleDeck()
{
  //RNG values from  random library
  std::mt19937 rng;   
  rng.seed(time(0));

  //Uniform distribution so we fairly can get from 0 to 51
  std::uniform_int_distribution<uint32_t> dist(0,51); // range [0,51]
  std::uniform_int_distribution<int32_t> roundDist(500, 700);
  
  Card *temp = cards[0];
  int rounds = roundDist(rng);
  //Swap two randomly selected cards 500 to 700 times using the temp pointer
	for(int i = 0; i < rounds; i++){
		int a = dist(rng) % 52;
		int b = dist(rng) % 52;
		
    //Swapping of cards now we just exchange pointers
		temp = cards[a];
	
    cards[a] = cards[b];
		
    cards[b] = temp;
		

	}
}




