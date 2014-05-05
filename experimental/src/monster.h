#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "game.h"


void initializeMonster(GameObject* monster, int x, int y);
int collide(GameObject* player,GameObject* monster);
void updateMonsters(Game* game, GameObject* monster);
int checkFall(GameObject* monster, Map* map);

#endif // MONSTER_H_INCLUDED
