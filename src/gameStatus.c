/**
 * \file gameStatus.c
 * \brief Functions to handle the state of the game
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "gameStatus.h"


void initGameStatus(GameStatus* status) {
    status->gameIsRunning = true;
    status->state = intro;
    status->level = 0;
    status->nextTick = 0;
    status->sleepTime = 0;
}

/*a refaire, peut etre avec des switchs*/
/*dans quel ordre faire les tests ?*/
void updateGameStatus(GameStatus* status) {
   //faire le graph d'état, mais avant gérer les input
}


