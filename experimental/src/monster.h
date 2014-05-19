/**
 * \file monster.h
 * \brief header of monster.c
 *
 *  Declaration of initializeMonster(), collide(), updateMonsters(), checkFall()
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "game.h"


void initializeMonster(GameObject* monster, int x, int y);
int collide(GameObject* player,GameObject* monster);
void updateMonsters(Game* game, GameObject* monster);
int checkFall(GameObject* monster, Map* map);

#endif // MONSTER_H_INCLUDED
