/**
 * @file Card.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * Class containing information on a Card. Cards are just containers of ints and strings.
 * This is the implementation of the header file
 *
 */
#include "Card.h"
//Class for a Card containing its value, name, and suit


void Card::setScore(int score)
{
  this->score = score;
}

void Card::setName(string name)
{
  this->name = name;
}

void Card::setSuit(string suit)
{
  this->suit = suit;
}


// Parametrized constructor
Card::Card(int score, string suit, string name)
{
  setScore(score);  
  setName(name);
  setSuit(suit);
}

Card::~Card()
{

}

//Getters implementation
int Card::getScore() const
{
  return score;
}

string Card::getName() const
{
  return name;
}

string Card::getSuit() const
{
  return suit;
}

string Card::toString() const
{
  return getName() + "of" + getSuit() + " : Value of " + std::to_string(getScore()) + "\n";
}






