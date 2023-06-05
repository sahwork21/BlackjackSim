/**
 * @file ShoeTest.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * This is the test file for the Shoe object
 * Make sure we can deal cardss and stuff
 */

#include "../src/Shoe.h"
#include "../src/Card.h"

using std::cout;
using std::endl;
using std::cerr;
//Reports how many of the cases are passes
static int report(int pass, int total)
{
  cout << "Shoe: Passing " << pass << " of " << total << " tests" << endl;
  if(pass != total){
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

int main()
{
  int total = 0;
  int passing = 0;
  //Make sure the default construction works
  Shoe *s = new Shoe();
  Shoe *s2 = new Shoe(2);

  total++;
  if(s->getDeckCount() != 6){
    delete s;
    delete s2;
    cerr << "Defaultly start with 6 decks in the shoe" << endl;
    report(passing, total);
  }

  if(s2->getDeckCount() != 2){
    delete s;
    delete s2;
    cerr << "Parametrized shoe needs 2 decks in the shoe" << endl;
    report(passing, total);
  }


  
  if(s->getReshuffle() != false || s->getReshuffle() != false){
    delete s;
    delete s2;
    cerr << "Always start with false for a shoe" << endl;
    report(passing, total);
  }

  
  passing++;


  //We should be able to deal a card from the wash and get ace of diamonds origin 0
  Card *c;
  total++;
  c = s->dealCard();
  Card *c2 = s2->dealCard();
  if(c->getOrigin() != 0 || c2->getOrigin() != 0){
    delete s;
    delete s2;
    cout << c << endl;
    cout << c2 << endl;
    cerr << "Should be getting Ace of Diamonds from deck 0" << endl;
    report(passing, total);
  }
  passing++;


  //Return those cards then reshuffle and insert the -1 reshuffle card
  s->returnCard(c, c->getOrigin());
  s2->returnCard(c2, c2->getOrigin());

  
  //Lets work with s2 since it will take less time to get to the place holder
  s2->setReshuffleCard();

  total++;
  //If we get to that origin 0 ace of diamonds we didn't make it
  while(!s2->getReshuffle()){
    c = s2->dealCard();
    cout << *c << endl;


    //Ace of diamonds check
    if(c->getName().compare("Ace") == 0 && c->getOrigin() == 0 && c->getSuit().compare("Diamonds") == 0){
      cerr << "We drew the whole deck without getting the reshuffle card" << endl;
      delete s;
      delete s2;
      report(passing, total);
    }
    s2->returnCard(c, c->getOrigin());
  }
  passing++;
  

  //Let's just check if shuffling works
  //Print out ten cards that were shuffled up

  
  //Let's try to shuffle up s2 and retry this test
  s2->washDecks();
  s2->setReshuffleCard();

  total++;
  while(!s2->getReshuffle()){
    c = s2->dealCard();
    cout << *c << endl;


    
  }
  passing++;


  delete s;
  delete s2;
  report(passing, total);
  return 0;


}