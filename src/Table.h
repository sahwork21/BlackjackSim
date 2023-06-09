/**
 * @file Table.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * This contains any objects and static methods that the Table will need to run a game
 */
#include "Shoe.h"
#include "Dealer.h"
#include "Better.h"
#include "Player.h"

//Windows compilation
#ifdef WINDOWS
#include <Windows.h>
#endif

//If You use linux use this and not windows or sleep may not work
#ifdef LINUX
#include <unistd.h>
#endif
//For signalling the program is over
#include <csignal>
//Getting inputs
#include <iostream>

#include <ios>
#include <limits>

//Methods needed for verifying input
using std::getline;
using std::stoi;


//Enum that detemines what type of user we have
typedef enum {PlayerType, BetterType} UserType;


//Struct that determines if we have better or player
typedef struct UserStruct
{
  //We have our enum for what type we have
  UserType type;
  union
  {
    Player* player;
    Better* better;
  };
} User;

//These are a bunch of methods that will do some of the actions for a user
//Just hit cards and stuff depending on what object is in the union
void hitUser(User *user, Card *c);

//Print out what our user has
void printHand(User *user);

//Prints out that we found the reshuffle card if we need to
void foundReshuffle();