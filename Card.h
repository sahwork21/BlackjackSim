/**
 * @file Card.h
 * @author Sean Hinton (sahinto2)
 * This is the header file for the Card object containing prototypes and fields
 * 
 */

#ifndef CARD_H
#define CARD_H

#include <string>


using std::string;

//Container for our Card class
class Card
{

  //All cards have a suit, name, and score
  private:
    int score;
    string suit;
    string name;

    //Setters are private since a Card's fields should be immutable
    void setScore(int score);
    void setSuit(string suit);
    void setName(string name);

  public:
    //Prototype for constructor
    Card(int score, string suit, string name);
    //Destructor
    ~Card();

    //Getters for the Card
    int getScore();
    string &getSuit();
    string &getName();



  


};


#endif CARD_H