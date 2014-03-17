/**
 *\file structs.h
 *\brief Declare all the structures
 */

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <SDL/SDL.h>
#include "common.h"
#include "define.h"

/**
 * \enum State
 * \brief Enumeration of the different possible states of the game.
 */
typedef enum State {
   menu=0, options=1, inGame=2
} State;


/**
 * \struct GameStatus
 * \brief Informations on the state of the game and for the timers.
 */
typedef struct GameStatus {
   Boolean gameIsRunning;
   State state;
   int level;
   /*Variables for the FPS*/
   Uint32 nextTick;
   Uint32 sleepTime;
} GameStatus;


/**
 * \struct GameOptions
 * \brief Represent the options of the game, selected by the player in the options menu.
 */
typedef struct GameOptions {
   int windowWidth;
   int windowHeight;
   Boolean fullscreen;
} GameOptions;

/**
 * \struct Menu
 * \brief Informations to draw the menu on the screen
 */
typedef struct Menu {
   char** contenu;/* a revoir */
   int selection;
   SDL_Surface* menuSpriteSheet;
   SDL_Surface* splashScreen;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;
} Menu;

/**
 * \struct GameEvent
 *
 */
/*a revoir soon*/
typedef struct GameEvent {
   SDL_Event sdlEvent;
   Boolean eventInQueue;
} GameEvent;

/**
 * \struct Level
 * Informations on the current level.
 */
typedef struct Level {
   SDL_Surface* background;
   SDL_Rect* src;
} Level;

/*!
 * \struct Character
 * \brief Variables to manage the character.
 */
typedef struct Character{
   SDL_Rect* position;
}Character;

/**
 * \struct Game
 * \brief Variables necessaries to most of the game-related functions.
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


#endif
