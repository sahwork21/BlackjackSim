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
static int report(int total, int pass)
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
  //vector<Card*> v = p->getHand();

  //Assert that reference semantics held and fields are default
  total++;
  if(p->getBust()){
    cerr << "Player should not start in a bust position" << endl;
    delete p;
    
    exit(report(total, passing));
  }
  passing++;

  //Score should start at 0
  total++;
  if(p->getScore() != 0){
    cerr << "Player should start at a score of 0" << endl;
    delete p;

    exit(report(total, passing));
  }
  passing++;

  //We should start with an empty vector
  total++;
  if(p->getHandCopy().size() != 0){
    cerr << "Player should start with an empty vector" << endl;
    delete p;

    exit(report(total, passing));
  }
  passing++;

  

  //Now try putting some cards in the hand
  Card *c1 = new Card(11, "Spades", "Ace");
  Card *c2 = new Card(10, "Spades", "Ten");
  Card *c3 = new Card(11, "Hearts", "Ace");
  Card *c4 = new Card(10, "Hearts", "Ten");


  p->hitCard(c1);
  p->hitCard(c2);

  //Add an ace and ten to get to 21
  total++;
  if(p->getHandCopy().size() != 2){
    cerr << "Player should have 2 cards now" << endl;
    delete p;

    exit(report(total, passing));
  }

  if(p->getBust()){
    cerr << "Player should not be bust right now" << endl;
    delete p;

    exit(report(total, passing));
  }

  cout << p->getScore() << endl;
  if(p->getScore() != 21){
    cerr << "Player should have 21 right now" << endl;
    delete p;

    exit(report(total, passing));
  }
  

  //Also assert our ace has not been reduced
  cout << "Ace reducable is " << p->getHandCopy()[0]->getReducable() << endl;
  if(!p->getHandCopy()[0]->getReducable()){
    cerr << "First ace should not be reduced" << endl;
    delete p;

    exit(report(total, passing));
  }

  //And our ten should not be reducable
  cout << "Ten reducable is " << p->getHandCopy()[1]->getReducable() << endl;
  if(p->getHandCopy()[1]->getReducable()){
    cerr << "First Ten should be reduced" << endl;
    delete p;

    exit(report(total, passing));
  }
  passing++;


  //Now go over the limit with another ace to get score to 12
  total++;
  p->hitCard(c3);
  if(p->getHandCopy().size() != 3){
    cerr << "Player should have 3 cards now" << endl;
    delete p;

    exit(report(total, passing));
  }

  if(p->getBust()){
    cerr << "Player should not be bust right now" << endl;
    delete p;

    exit(report(total, passing));
  }

  cout << p->getScore() << endl;
  if(p->getScore() != 12){
    cerr << "Player should have 12 right now" << endl;
    delete p;

    exit(report(total, passing));
  }
  passing++;

  //Assert our aces have been reduced

  total++;
  cout << "Ace reducable is " << p->getHandCopy()[0]->getReducable() << endl;
  cout << "Ten reducable is " << p->getHandCopy()[1]->getReducable() << endl;
  cout << "Ace reducable is " << p->getHandCopy()[2]->getReducable() << endl;
  if(p->getHandCopy()[0]->getReducable() || p->getHandCopy()[1]->getReducable() || p->getHandCopy()[2]->getReducable()){
    cerr << "Player should have no reducable cards" << endl;
    delete p;

    exit(report(total, passing));
  }
  passing++;


  //Assert our toString works
  cout << *p << endl;




  //Now go bust by adding a ten
  total++;
  p->hitCard(c4);
  if(p->getHandCopy().size() != 4){
    cerr << "Player should have 4 cards now" << endl;
    delete p;

    exit(report(total, passing));
  }

  if(!p->getBust()){
    cerr << "Player should be bust right now" << endl;
    delete p;

    exit(report(total, passing));
  }

  cout << p->getScore() << endl;
  if(p->getScore() != 22){
    cerr << "Player should have 22 and bust right now" << endl;
    delete p;

    exit(report(total, passing));
  }
  passing++;

  //Now lets return all of our cards

  total++;
  //Just pull them out of the array and see if things have changed
  //Only the vector hand should change not other stuff since this is the last action in a game
  p->returnHand();
  

  //All the aces should now be reduced
  cout << "Ace reducable is " << c1->getReducable() << endl;
  cout << "Ten reducable is " << c2->getReducable() << endl;
  cout << "Ace reducable is " << c3->getReducable() << endl;
  cout << "Ten reducable is " << c4->getReducable() << endl;
  if(!c1->getReducable() || c2->getReducable() || !c3->getReducable() || c4->getReducable()){
    cerr << "Player should have aces as reducable cards" << endl;
    delete p;

    exit(report(total, passing));
  }

  

  //Should have 0 cards now
  if(p->getHandCopy().size() != 0){
    cerr << "Player should have 0 cards now" << endl;
    delete p;

    exit(report(total, passing));
  }

  if(p->getScore() !=0){
    cerr << "Player should have 0 score right now" << endl;
    delete p;

    exit(report(total, passing));
  }


  passing++;







  
  delete p;
  delete c1;
  delete c2;
  delete c3;
  delete c4;

  exit(report(total, passing));
  


}
