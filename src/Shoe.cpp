/**
 * @file Shoe.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * Definition of the shoe that is meant to be our source of cards for a true casino game
 */

#include "Shoe.h"

//Default constructor setting our deck up to have six decks
Shoe::Shoe()
{
  notUsing();
  setReshuffle();
  setDeckCount(6);
  //Generate the decks and a wash
  //setDecks();
  setWash();
}

Shoe::Shoe(int decks)
{
  if(decks > 8 || decks < 2){
    throw std::invalid_argument("Deck count cannot exceed 8");
  }
  notUsing();
  setReshuffle();
  setDeckCount(decks);

  //Now generate decks
  //setDecks();
  setWash();

}

Shoe::~Shoe()
{
  //We don't need to delete any Cards since the vector can do that for us
  wash.clear();

  #ifdef TEST
    std::cout << "Shoe destroyed" << std::endl;
  #endif
}


//Generate all of our decks when constructing
// void Shoe::setDecks()
// {
//   for(int i = 0; i < deckCount; i++){
//     //We need to add some sort of waiting so randomnes is maintained
//     srand(time(0));
//     //Sleep from 1 to 5 seconds
//     Sleep(3000);
//     decks[i] = new Deck(i);
//   }
// }



//Set ourself up with 15 instances of each number
void Shoe::setWash()
{

  string names[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
  int CardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
  //Essentially create a deck a certain amount of times pushing it onto the vector
  for(int k = 0; k < deckCount; k++){
    
	
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 13; j++){
      //Construct our Card here with the correct origin
      wash.push_back( new Card(CardValue[j], suits[i], names[j], 0));
      
    }
  }
  }
}





//Insert the card around 75% into the deck like a real shoe does
void Shoe::setReshuffleCard()
{
  std::mt19937 rng;   
  rng.seed(time(0));
  std::uniform_int_distribution<uint32_t> dist( DECK_SIZE * deckCount * .72,  DECK_SIZE * deckCount * .77); // ranges from 72 to 77 % into the wash

  

  //Use our random library rng
  //Our card will essentially be a Card with a -1 value

  int place = dist(rng);
  wash.push_back(new Card(-1, "Plastic", "Reshuffle"));

  //Swap place and back's pointers
  Card *c = wash[place];
  wash[place] = wash[deckCount * DECK_SIZE];
  wash[deckCount * DECK_SIZE] = c;
}

//Shuffle every deck then shuffle around our vector of ints
void Shoe::washDecks()
{
  
  //This should somewhat simulate shuffling around decks then merging together
  std::mt19937 rng;   
  rng.seed(time(0));
  //std::uniform_int_distribution<int32_t> dist(2000, 3000); //For shuffling the deck


  //int rounds = dist(rng);
  //Card *temp = wash[0];
  //Swap two randomly selected ints 2000 to 3000 times using the temp pointer
  //For this shuffling method will shuffle around 2/deckCount of the shoe. Merging around 2 decks basically
  
  for(int i = 0; i < deckCount - 1; i++){
    shuffle(wash.begin() + (i * DECK_SIZE), wash.begin() + ((i + 2) * DECK_SIZE), rng);
  }

  //Now just poker shuffle everything in a big pile
  shuffle(wash.begin(), wash.end(), rng);
	

  //We have shuffle up our deck so set the reshuffle flag to false
  reshuffle = false;

  

  
}


//Deal from the front and get an int
// int Shoe::dealFromWash()
// {
//   int ret = wash[0];
//   wash.erase(wash.begin());

//   //Put ret to the back
//   //wash.push_back(ret);

//   //We found the reshuffle card and it's time to shuffle
//   return ret;

// } 

//Return a card to the correct deck
void Shoe::returnCard(Card *card)
{
  //We need to just put the card at the back of the deck
  //We hope it was created using the new keyword
  card->setReducable();
  wash.push_back(card);
}

//Get a card from the Decks
// Card* Shoe::dealFromDecks(int origin)
// {
//   return decks[origin]->dealCard();
// }

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
//We need to always upon creation
void Shoe::setReshuffle()
{
  reshuffle = true;
}

bool Shoe::getReshuffle() const
{
  return reshuffle;
}


//Deal a Card and change our state ourselves
Card* Shoe::dealCard()
{
  //Get a card from our wash
  Card *c = wash.front();
  wash.erase(wash.begin());

  

  //We may have drawn a -1
  //If so reshuffle will have to become true and we need another card
  if(c->getScore() == -1){
    reshuffle = true;
    //Delete this card since it's no longer of use
    delete c;

    c = wash.front();
    wash.erase(wash.begin());
  }

  //Now deal a card from our correct deck of origin
  return c;

}

void Shoe::notUsing()
{
  inUse = false;
}
void Shoe::inUsing()
{
  inUse = true;
}
bool Shoe::getUsing() const
{
  return inUse;
}


