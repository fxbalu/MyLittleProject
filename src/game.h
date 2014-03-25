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
#include <SDL_image.h>

#include "define.h"
#include "common.h"

#include "gameStatus.h"
#include "gameOptions.h"
#include "input.h"
#include "menu.h"
#include "level.h"
#include "character.h"

/**
 * \struct Game
 * \brief Variables necessaries to most of the game-related functions.
 */
typedef struct Game {
   SDL_Surface* screen;
   GameStatus* status;
   GameOptions* options;
   Input* input;
   Menu* menu;
   Level* level;
   Character* player;
} Game;

int initGame(Game* game);
int initSDL();

void updateGame(Game* game);
void clearScreen(Game* game);
void displayGame(Game* game);
void delayGame(Game* game);

#endif
