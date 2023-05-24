/**
 * @file PlayerTest.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the testing program for the player object
 * 
 */

#include "../src/Player.h"
#include "../src/Deck.h"
#include "../src/Card.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;
using std::invalid_argument;
//Reports how many of the cases are passes
int report(int pass, int total)
{

  cout << "Player: Passing " << pass << " of " << total << " tests" << endl;
  if(pass != total){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/**
 * @brief Test functions for the Player class
 * 
 * @return 0 if all tests pass, 1 if not including how many unit tests passed
 */
int main()
{

  int passing = 0;
  int total = 0;
  //Test the constructor works
  Player *p = new Player();

  //We should have all 0's on fields
  vector<Card*> v = p->getHand();

  //Assert that reference semantics held and fields are default
  total++;
  if(p->getBust() != false){
    cerr << "Bust should start out as false" << endl;
    delete p;
    
    report(total, passing);
  }
  passing++;

  total++;
  if(p->getCardCount() != 0){
    cerr << "Card count should start as 0" << endl;
    delete p;
    
    report(total, passing);
  }
  passing++;

  total++;
  if(p->getMoney() != 500){
    cerr << "Default construction should set money to 500" << endl;
    delete p;
    
    report(total, passing);
  }
  passing++;

  total++;
  if(p->getScore() != 0){
    cerr << "Score should start as 0" << endl;
    delete p;
    
    report(total, passing);
  }
  passing++;

  total++;
  if(v.size() != 0){
    cerr << "Card size should be 0" << endl;
    delete p;
    
    report(total, passing);
  }
  passing++;


  //Create a deck and see if we can properly transfer some cards around
  Deck *d = new Deck();
  Card *c = d->dealCard();
  p->hit(c);

  //See if things did in fact change
  total++;
  if(p->getCardCount() != 1 && d->getSize() != 51){
    cerr << "There should be a card in the hand now and 51 in the deck" << endl;
    delete p;
    
    delete d;
    report(total, passing);
  }
  passing++;

  //Assert they are the same objects
  total++;
  if(p->getHand().at(0) != c){
    cerr << "Wrong card in hand" << endl;
    delete p;
    
    delete d;
    report(total, passing);
  }
  passing++;

  

  //Now return it and clear the vector of cards
  total++;
  d->returnCard(v.at(0));

  //Assert things changed
  if(p->getCardCount() != 0 && d->getSize() != 52){
    cerr << "Failed to return card back to deck" << endl;
    delete p;
    
    delete d;
    report(total, passing);
  }
  passing++;

  //Let's try and go bust
  int i = 0;
  while(p->getBust()){
    p->hit(d->dealCard());
    i++;
  }

  //Assert sizes did in fact change
  total++;
  if(p->getCardCount() != i && d->getSize() != 52 - i){
    cerr << "Couldn't update sizes over a series of ops" << endl;
    delete p;
   
    delete d;
    report(total, passing);
  }
  passing++;

  //Now destroy everything

  delete c;
  delete p;

  


  report(passing, total);
  


}
