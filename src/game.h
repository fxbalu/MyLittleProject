/*!
 * \file game.h
 * \brief structs and prototypes necessaries for the major functions of the game
 * \author fx.balu & a.dufac & g.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef DEFINED_GAME_H
#define DEFINED_GAME_H

#include "common.h"
#include "character.h"

/*!
 * \def WINDOW_WIDTH_DEFAULT
 * width of the window of the game
 */
#define WINDOW_WIDTH_DEFAULT 640

/*!
 * \def WINDOW_HEIGHT_DEFAULT
 * height of the window of the game
 */
#define WINDOW_HEIGHT_DEFAULT 480

/*!
 * \def FPS
 * number of frames per seconds of the game
 */
#define FPS 60

/*!
 * \def SKIP_TICKS
 * ### TO B-B-B-B-BE DEFIIINEED BY -----> GWEEEENDOU <------ mouaahahahaha
 */
#define SKIP_TICKS (1000/FPS)

/*!
 * \struct GameStatus
 * informations on the state of the game and for the timers
 */
typedef struct GameStatus {
   Boolean gameIsRunning;
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
   Boolean fullscreen;
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
   Character* player;
} Game;

int gameInit(Game* game);  //initialiser les paramètres du jeu
void initGameStatus(Game* game);
void gameDelay(Game* game);
void gameEvent(Game* game); // gestion d'events
void gameDisplay(Game* game);

#endif // DEFINED_GAME_H
