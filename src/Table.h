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

//This is the user union that could either be a player or better
union user
{
  Player* player;
  Better* better;
};