/**
 * @file Table.h
 * @author Sean Hinton (sahwork21@gmail.com)
 * This contains any objects and static methods that the Table will need to run a game
 */
#include "Shoe.h"
#include "Dealer.h"
#include "Better.h"
#include "Player.h"
#include <iostream>
#include <Windows.h>
#include <csignal>


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
void hitUser(User user, Card *c);