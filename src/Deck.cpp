/**
 * @file Deck.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the definition of the Deck header file and its prototypes
 */
#include "Deck.h"



//Constructor for a Deck
Deck::Deck()
{
  
  setCards();
  front = 0;
  //Back points to the next open spot in the array
  back = 0;
  size = DECK_SIZE;
}

//Destructor for a Deck
Deck::~Deck()
{
  for(int i = 0; i < DECK_SIZE; i++){
    #ifdef TEST
      std::cout << *cards[i] << " Was destroyed" << std::endl;
    #endif

    delete cards[i];
  }

  #ifdef TEST
    std::cout << "Deck was destroyed" << std::endl;
  #endif
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

  //If you try to deal from an empty deck you get nothing
  if(size == 0){
    return NULL;
  }
  
    //Get the top card
    Card *ret = cards[front];
  
    //Change our front value and we don't want it to get too large
    front = (front + 1) % DECK_SIZE;
    size--;
    return ret;
  


  

}

//Return a Card to our deck
void Deck::returnCard(Card *card) 
{

  //If you try to add to a full array just don't add it
  if(size < DECK_SIZE){
    

    //Put our card back in the queue
    cards[back] = card;

    //Change our back
    back = (back + 1) % DECK_SIZE;
    size++;
  }

  

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

int Deck::getSize() const
{
  return size;
}




