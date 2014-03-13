/*
 * GameStatus.h
 *
 *  Created on: 11 mars 2014
 *      Author: Gwendal
 */

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

#include "Define.h"

typedef struct GameOptions {

   int windowWidth;
   int windowHeight;

   bool fullscreen;

} GameOptions;

typedef struct GameStatus {

   GameOptions* options;

   bool gameIsRunning;
   int status;

} GameStatus;



void initGameStatus(GameStatus* status);
void updateGameStatus(GameStatus* status);

#endif /* GAMESTATUS_H_ */
