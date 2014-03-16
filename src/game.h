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
 * ### time (in ms) between two frames
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

   Uint32 fps;
   Uint32 fpsStart; /*temporary variable to calculate the fps rate*/
   Uint32 fpsEnd;
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

typedef struct GameEvent {
   SDL_Event sdlEvent;
   Boolean eventInQueue;
} GameEvent;

typedef struct Level {
   SDL_Surface* imgTest;
   SDL_Rect* src;
} Level;

/*!
 * \struct Game
 * variables necessaries to most of the game-related functions
 */
typedef struct Game {
   SDL_Surface* screen;
   GameStatus* status;
   GameOptions* options;
   GameEvent* event;
   Level* level;
   Character* player;
} Game;

int gameInit(Game* game);  /* initialiser les paramètres du jeu */
void initGameStatus(Game* game);
void initLevel(Game* game);

void gameDelay(Game* game);
void gameEvent(Game* game); /* gestion d'events */
void gameUpdate(Game* game);
void gameDisplay(Game* game);

#endif // DEFINED_GAME_H
