#include "gameStatus.h"

void initGameStatus(Game* game){
   game->status = (GameStatus*) malloc(sizeof(GameStatus));
   game->status->state = menu;
   game->status->level = 1;
   game->status->gameIsRunning = true;
   game->status->nextTick = game->status->sleepTime = 0;
}
