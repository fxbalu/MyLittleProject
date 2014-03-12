/*
 * GameStatus.h
 *
 *  Created on: 11 mars 2014
 *      Author: Gwendal
 */

#ifndef GAMESTATUS_H_
#define GAMESTATUS_H_

#include "Define.h"

typedef struct GameStatus {
	bool gameIsRunning;
	int status;

} GameStatus;

void initGameStatus(GameStatus* status);

#endif /* GAMESTATUS_H_ */
