/**
 * \file game.h
 * \brief Prototypes of functions used in the main function.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef DEFINED_GAME_H
#define DEFINED_GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "define.h"
#include "common.h"
#include "structs.h"
#include "gameStatus.h"
#include "gameOptions.h"
#include "input.h"
#include "menu.h"
#include "level.h"
#include "character.h"


int initGame(Game* game);

void updateGame(Game* game);
void clearScreen (Game* game);
void displayGame(Game* game);
void delayGame(Game* game);

#endif
