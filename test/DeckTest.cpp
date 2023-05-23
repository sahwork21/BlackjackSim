/**
 * @file DeckTest.cpp
 * @author your name (you@domain.com)
 * This is a file for unit testing the Deck class
 * 
 * 
 */
#include "../src/Deck.h"
#include "../src/Card.h"
#include <iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::cerr;
using std::invalid_argument;
//Reports how many of the cases are passes
int report(int pass, int total)
{

  cout << "Deck: Passing " << pass << " of " << total << " tests" << endl;
  if(pass != total){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Test functions for the Deck class
 * 
 * @return 0 if all tests pass, 1 if not including how many unit tests passed
 */
int main()
{

  int passing = 0;
  int total = 0;
  //Test the constructor works
  Deck *d = new Deck();

  //Assert our size is right
  total++;
  if(d->getSize() != 52){
    cerr << "Failed to construct with the right size" << endl;
    
    delete d;
    return report(passing, total);
  }
  passing++;


  //Try to add a Card beyond the allowed limit
  Card *c = new Card(1, "Diam", "Ace");

  total++;
  d->returnCard(c);


  //Deck should not have grown
  if(d->getSize() != 52){
    //We failed
    cerr << "Failed to get exception when inserting to full deck" << endl;
    delete c;
    delete d;
    return report(passing, total);
    

  //We need to get an invalid argument when trying to insert
  } 
    
  passing++;

  delete c;


  //We should be able to remove 52 cards then be unable to draw again
  for(int i = 0; i < 52; i++){
    d->dealCard();
  }

  //Assert size is 0
  total++;
  if(d->getSize() != 0){
    cerr << "Failed to update size when dealing cards" << endl;
    
    delete d;
    return report(passing, total);
  }
  passing++;

  //We have deleted all the cards in our deck
  total++;
  Card *n = d->dealCard();

  if(n != NULL){
    //We failed
    cerr << "Failed to get exception when dealing from an empty decks" << endl;
    delete d;
    report(passing, total);

  //We need to get an invalid argument when trying to insert
  } 
  passing++;

  //Scrap the old deck
  delete d;
  d = new Deck();


  //Test the ability to deal some cards and shuffle our deck
  //Just imagine playing a game or something
  total++;
  c = d->dealCard();
  if(d->getSize() != 51){
    //We failed
    cerr << "Failed to decrement deck size" << endl;
    delete d;
    report(passing, total);
  }

  Card *c2 = d->dealCard();
  Card *c3 = c2;
  if(d->getSize() != 50){
    //We failed
    cerr << "Failed to decrement deck size" << endl;
    delete d;
    report(passing, total);
  }

  //Return a card then deal another
  d->returnCard(c2);
  if(d->getSize() != 51){
    //We failed
    cerr << "Failed to increment deck size" << endl;
    delete d;
    report(passing, total);
  }

  c2 = d->dealCard();
  
  if(d->getSize() != 50){
    //We failed
    cerr << "Failed to decrement deck size" << endl;
    delete d;
    report(passing, total);
  }

  //c2 should also be a new card
  if(c2 == c3){
    cerr << "Failed to draw a random card" << endl;
    delete d;
    report(passing, total);
  }

  //Now return everything
  d->returnCard(c2);
  d->returnCard(c);

  if(d->getSize() != 52){
    //We failed
    cerr << "Failed to increment deck size back to original" << endl;
    delete d;
    report(passing, total);
  }
  passing++;


  


  //Now check that destruction works properly
  //Has to be done by the programmor since I don't want to dup2 and read a file
  delete d;





  report(passing, total);
  


}