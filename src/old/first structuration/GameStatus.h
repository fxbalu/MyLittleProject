/*
 * GameStatus.h
 *
 *  Created on: 11 mars 2014
 *      Author: Gwendal
 */

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

#include "Define.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

typedef struct GameOptions {

   int windowWidth;
   int windowHeight;

   bool fullscreen;

} GameOptions;

typedef struct GameStatus {

   bool gameIsRunning;
   int status;

   GameOptions* options;

   /*Variables for the FPS*/
   Uint32 nextTick;
   Uint32 sleepTime;

} GameStatus;



void initGameStatus(GameStatus* status);

#endif /* GAMESTATUS_H_ */
