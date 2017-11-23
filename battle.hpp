

#ifndef battle_h
#define battle_h

#include <iostream>
#include <time.h>
#include "creature.hpp"
#include "ghost.hpp"
#include "merman.hpp"
#include "cultist.hpp"
//#include "cetus.hpp"
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_World.hpp"

void battle(Player *p1, Creature* c2, int modifier);
void randomEnemyGenerator(Room*, int);
void gameEnd();
#endif
