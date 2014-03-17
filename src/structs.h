/**
 *\file structs.h
 *\brief Declare all the structures
 */

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <SDL/SDL.h>
#include "common.h"
#include "define.h"

typedef enum State {
   menu=0, options=1, inGame=2
} State;

/**
 * \struct GameStatus
 * informations on the state of the game and for the timers
 */
typedef struct GameStatus {
   Boolean gameIsRunning;
   State state;
   int level;
   /*Variables for the FPS*/
   Uint32 nextTick;
   Uint32 sleepTime;
} GameStatus;

typedef struct GameOptions {
   int windowWidth;
   int windowHeight;
   Boolean fullscreen;
} GameOptions;

typedef struct Menu {
   char** contenu;/* a revoir */
   int selection;
   SDL_Surface* menuSpriteSheet;
   SDL_Surface* splashScreen;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;
} Menu;

/**
 * \struct GameOptions
 * options for the game
 */
/*a revoir soon*/
typedef struct GameEvent {
   SDL_Event sdlEvent;
   Boolean eventInQueue;
} GameEvent;

typedef struct Level {
   SDL_Surface* imgTest;
   SDL_Surface* background;
   SDL_Rect* src;
} Level;

/*!
 * \struct Character
 * variables to manage the character
 */
typedef struct Character{
   SDL_Rect* position;
}Character;

/**
 * \struct Game
 * variables necessaries to most of the game-related functions
 */
typedef struct Game {
   SDL_Surface* screen;
   GameStatus* status;
   GameOptions* options;
   Menu* menu;
   GameEvent* event;
   Level* level;
   Character* player;
} Game;


#endif // STRUCTS_H_INCLUDED
