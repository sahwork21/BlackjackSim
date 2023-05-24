/**
 * @file Card.h
 * @author Sean Hinton (sahinto2)
 * This is the header file for the Card object containing prototypes and fields
 * 
 */

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using std::string;

/**
 * Container for our Card objects
 * Each card has a value, name, and string
 * 
 */
class Card
{

  //All cards have a suit, name, and score
  private:
    int score;
    string suit;
    string name;
    //If the card can be reduced this should be true
    bool reducable;

    //Setters are private since a Card's fields should be immutable
    void setScore(int score);
    void setSuit(string suit);
    void setName(string name);
    void setReducable();

  public:
    //Default constructor for Card
    Card();

    //Prototype for constructor
    Card(int score, string suit, string name);
    //Destructor
    ~Card();

    //Getters for the Card
    int getScore() const;
    string getSuit() const;
    string getName() const;
    string toString() const;

    //This is the accessible versions of the reducable field
    void reduce();    
    void restoreReduce();
    bool getReducable() const;

    
    //Output stream for a Card object
  friend std::ostream& operator<<(std::ostream& strm, const Card &card);

  


};


#endif