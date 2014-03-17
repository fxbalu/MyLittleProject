/**
 * \file gameStatus.c
 * \brief Functions to handle the state of the game
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

 #include "gameStatus.h"

void initGameStatus(Game* game){
   game->status = (GameStatus*) malloc(sizeof(GameStatus));
   game->status->state = menu;
   game->status->level = 1;
   game->status->gameIsRunning = true;
   game->status->nextTick = game->status->sleepTime = 0;
}

void updateGameStatus(Game* game) {

}
