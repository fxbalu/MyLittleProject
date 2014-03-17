/**
 * \file game.h
 * \brief structs and prototypes necessaries for the major functions of the game
 * \author fx.balu & a.dufac & g.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef DEFINED_GAME_H
#define DEFINED_GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "define.h"
#include "common.h"
#include "structs.h"
#include "gameStatus.h"
#include "gameOptions.h"
#include "menu.h"
#include "level.h"
#include "character.h"


int initGame(Game* game);

void updateGameEvent(Game* game); /* gestion d'events, a revoir soon*/
void updateGame(Game* game);
void displayGame(Game* game);
void delayGame(Game* game);

#endif
