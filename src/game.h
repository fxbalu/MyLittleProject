/*!
 * \file game.h
 * \brief structs and prototypes necessaries for the major functions of the game
 * \author fx.balu & a.dufac & g.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef DEFINED_GAME_H
#define DEFINED_GAME_H

#include "include.h"

/*!
 * \struct GameStatus
 * informations on the state of the game and for the timers
 */
typedef struct GameStatus {
   Booleen gameIsRunning;
   int status;
   /*Variables for the FPS*/
   Uint32 nextTick;
   Uint32 sleepTime;
} GameStatus;

/*!
 * \struct GameOptions
 * options for the game
 */
typedef struct GameOptions {
   int windowWidth;
   int windowHeight;
   Booleen fullscreen;
} GameOptions;

/*!
 * \struct Game
 * variables necessaries to most of the game-related functions
 */
typedef struct Game {
   SDL_Surface* screen;
   GameStatus* status;
   GameOptions* options;
   SDL_Event event;
   Player* player;
} Game;

int gameInit(Game* game);  //initialiser les paramètres du jeu
void initGameStatus(Game* game);
void gameDelay(Game* game);
void gameEvent(Game* game); // gestion d'events
void gameDisplay(Game* game);

#endif // DEFINED_GAME_H
