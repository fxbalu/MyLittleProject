/**
 * \file gameStatus.h
 * \brief Prototypes of functions used in to handle the state of the game.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef GAMESTATUS_H_INCLUDED
#define GAMESTATUS_H_INCLUDED

#include <SDL.h>
#include "define.h"
#include "common.h"
#include "input.h"

/**
 * \enum State
 * \brief Enumeration of the different possible states of the game.
 */
typedef enum State {
   intro, mainMenu , newGameMenu, continueMenu, optionsMenu, creditsMenu, inGame, inGameMenu, inGamePopUp /*peut etre ajoouter un état start, revoir les noms peut etre*/
} State;


/**
 * \struct GameStatus
 * \brief Informations on the state of the game and for the timers.
 */
typedef struct GameStatus { //toutes les infos sur l'état !!!!!
   Boolean gameIsRunning;
   State state; /*enumeration des etats*/

   int level; /* on peut mettre  si pas chargé ou si pas dans un niveau*/
   int menuSelection;/*nom a modifier, a revoir toute la gestion des menu*/

   /*Variables for the FPS*/
   Uint32 frames;
   Uint32 time; /*temp, pour le debug surtout*/

   Uint32 nextTick;
   Uint32 sleepTime;
} GameStatus;



void initGameStatus(GameStatus* status);

void updateGameStatus(GameStatus* status, Input* input);

//appeler dans le switch de update gamestatus
void updateIntro(GameStatus* status, Input* input);
void updateMainMenu(GameStatus* status, Input* input);
void updateNewGameMenu(GameStatus* status, Input* input);
void updateContinueMenu(GameStatus* status, Input* input);
void updateOptionsMenu(GameStatus* status, Input* input);
void updateCreditsMenu(GameStatus* status, Input* input);
void updateInGame(GameStatus* status, Input* input);
void updateInGameMenu(GameStatus* status, Input* input);
void updateInGamePopUp(GameStatus* status, Input* input);

#endif
