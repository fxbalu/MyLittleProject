/**
 * \file game.h
 * \brief Prototypes of functions used in the main function.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef DEFINED_GAME_H
#define DEFINED_GAME_H

#include <SDL.h>           /* SDL_Surface */
#include "intro.h"
#include "gameStatus.h"    /* GameStatus */
#include "gameOptions.h"   /* GameOptions */
#include "input.h"         /* Input */
#include "menu.h"          /* Menu */
#include "level.h"         /* Level */
#include "character.h"     /* Character */

// #include <SDL_image.h>
// #include "define.h"
// #include "common.h"
// #include "log.h"

/**
 * \struct Game
 * \brief Variables necessaries to most of the game-related functions.
 *
 * \warning Why does it use pointer ?
 */
typedef struct Game {
   SDL_Surface* screen;
   Intro* intro;
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
