/**
 * @file Shoe.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * Definition of the shoe that is meant to be our source of cards for a true casino game
 */

#include "Shoe.h"

//Default constructor setting our deck up to have six decks
Shoe::Shoe()
{
  setReshuffle();
  setDeckCount(6);
  //Generate the decks and a wash
  setDecks();
  setWash();
}

Shoe::Shoe(int decks)
{
  setReshuffle();
  setDeckCount(decks);

  //Now generate decks
  setDecks();
  setWash();

}

Shoe::~Shoe()
{
  //We don't need to delete any Cards since the deck will do that for us
  for(int i = 0; i < deckCount; i++){
    delete decks[i];
  }

  #ifdef TEST
    std::cout << "Shoe destroyed" << std::endl;
  #endif
}




//Generate a deck after we know how many decks to make
void Shoe::setDecks()
{
  for(int i = 0; i < deckCount; i++){
    //Construct with the righ origin
    decks.push_back(new Deck(i));
  }
}

//Set ourself up with 15 instances of each number
void Shoe::setWash()
{
  for(int i = 0; i < deckCount; i++){
    for(int i = 0; i < DECK_SIZE; i++){
      wash.push_back(i);
    }
  }
}

//Insert the card around 25% into the deck like a real shoe does
void Shoe::setReshuffleCard()
{
  std::mt19937 rng;   
  rng.seed(time(0));
  std::uniform_int_distribution<uint32_t> dist(.20 * DECK_SIZE * deckCount, .30 * DECK_SIZE * deckCount); // ranges from 20 to 30 % into the wash

  

  //Use our random library rng

  int place = dist(rng);
  wash.push_back(wash[place]);
  wash[place] = -1;
}

//Shuffle every deck then shuffle around our vector of ints
void Shoe::washDecks()
{
  //We want to shuffle every deck
  //Then shuffle our wash of ints
  for(int i = 0; i < deckCount; i++){
    decks[i]->shuffleDeck();
  }

  //This should somewhat simulate shuffling around decks then merging together
  std::mt19937 rng;   
  rng.seed(time(0));
  std::uniform_int_distribution<int32_t> dist(2000, 3000); //For shuffling the deck


  int rounds = dist(rng);
  int temp = 0;
  //Swap two randomly selected ints 2000 to 3000 times using the temp pointer
	for(int i = 0; i < rounds; i++){
		int a = dist(rng) % (DECK_SIZE * deckCount);
		int b = dist(rng) % (DECK_SIZE * deckCount);
		
    //Swapping of cards now we just exchange pointers
		temp = wash[a];
	
    wash[a] = wash[b];
		
    wash[b] = temp;
		

	}

  
}


//Deal from the front and get an int
int Shoe::dealFromWash()
{
  int ret = wash[0];
  wash.erase(wash.begin());

  //Put ret to the back
  wash.push_back(ret);
  return ret;

} 

//Return a card to the correct deck
void Shoe::returnCard(Card *card, int origin)
{
  decks[origin]->returnCard(card);
}

//Get a card from the Decks
Card* Shoe::dealFromDecks(int origin)
{
  return decks[origin]->dealCard();
}

//Set our count for our deck
void Shoe::setDeckCount(int decks)
{
  this->deckCount = decks;
}

int Shoe::getDeckCount() const
{
  return deckCount;
}

//Set and get our reshuffle flag
void Shoe::setReshuffle()
{
  reshuffle = false;
}

bool Shoe::getReshuffle() const
{
  return reshuffle;
}

