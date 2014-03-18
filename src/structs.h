/**
 *\file structs.h
 *\brief Declare all the structures
 */

#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "common.h"
#include "define.h"

/**
 * \enum State
 * \brief Enumeration of the different possible states of the game.
 */
typedef enum State {
   intro, mainMenu , newGameMenu, continueMenu, optionsMenu, creditsMenu, inGame, inGameMenu, inGamePopUp/*peut etre ajoouter un état start, revoir les noms peut etre*/
} State;


/**
 * \struct GameStatus
 * \brief Informations on the state of the game and for the timers.
 */
typedef struct GameStatus {
   Boolean gameIsRunning;
   State state;
   int level;
   int menuSelection;/*nom a modifier*/
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
 * \struct Input
 * \brief
 */
typedef struct Input {
   SDL_Event* event;
   Control left;
   Control up;
   Control right;
   Control down;

   Control enter;
   Control jump;/* note : les control sont des flags, ils sont a appliqur dans une fonction getinput, et en fonction de gameOptions*/
   Control crouch;
   Control shoot;

   Control escape;
   Control exit;
} Input;


/**
 * \struct Menu
 * \brief Informations to draw the menu on the screen
 */
typedef struct Menu {
   char** contenu;/*nom a revoir */
   SDL_Surface* menuSpriteSheet;
   SDL_Surface* splashScreen;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;
} Menu;

/*peut etre une strucure GameEvent pour le detecteur de collision*/

/**
 * \struct Level
 * Informations on the current level(to draw it).
 */
typedef struct Level {
   SDL_Surface* background;
   SDL_Surface* tileset;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;
} Level;

/*!
 * \struct Character
 * \brief Variables to manage the character.
 */
typedef struct Character {
   SDL_Surface* spriteCharacterSheet;
   SDL_Rect* position; /*nom a changer*/
}Character;

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


#endif
