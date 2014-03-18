/**
 * \file gameStatus.h
 * \brief Prototypes of functions that draw the level on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */


#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "structs.h"

void initLevel(Game* game);

void updateLevel(Game* game);

void displayLevel(Game* game);

void displayBackground(Game* game);

#endif // LEVEL_H_INCLUDED
