/**
 * @file Card.cpp
 * @author Sean Hinton (sahwork21@gmail.com)
 * Class containing information on a Card. Cards are just containers of ints and strings.
 * This is the implementation of the header file
 *
 */
#include "Card.h"
//Class for a Card containing its value, name, and suit

//Our default constructor should really never be called
Card::Card()
{
  Card(0, "", "", 0);
}

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

void Card::setOrigin(int origin)
{
  this->origin = origin;
}


//Parametrized constructor for a singular, stand-alone deck
Card::Card(int score, string suit, string name)
{
  setScore(score);  
  setName(name);
  setSuit(suit);
  setReducable();
  setOrigin(0);
}


// Parametrized constructor for a card in a shoe
Card::Card(int score, string suit, string name, int origin)
{
  setScore(score);  
  setName(name);
  setSuit(suit);
  setReducable();
  setOrigin(origin);
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

int Card::getOrigin() const
{
  return origin;
}

//Change our reducable field only valid for aces
void Card::setReducable()
{
  this->reducable = false;
  if(name.compare("Ace") == 0){
    reducable = true;
  }
  
}

void Card::reduce()
{
  reducable = false;
}

void Card::restoreReduce()
{
  reducable = true;
}


bool Card::getReducable() const
{
  return reducable;
}


std::ostream& operator<<(std::ostream& strm, const Card &card)
{
  strm << card.name << " of " << card.suit<< ": Value of " << std::to_string(card.score);
  return strm;
}






