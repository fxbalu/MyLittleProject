/**
 * \file gameStatus.c
 * \brief Functions to handle the state of the game
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "gameStatus.h"

/*au lancement du jeu*/
void initGameStatus(Game* game) {
   game->status = (GameStatus*) malloc(sizeof(GameStatus));
   game->status->state = mainMenu;
   game->status->level = 0;
   game->status->gameIsRunning = true;
   game->status->nextTick = game->status->sleepTime = 0;
}

/*a refaire, peut etre avec des switchs*/
/*juste pour montrer que ca marche */
/*dans quel ordre faire les tests ?*/
/*clear inut a chaque changements*/
void updateGameStatus(Game* game) {

   if(game->input->exit) {
      game->status->gameIsRunning = false;
   }

   if(game->status->state==inGame && game->input->escape) {
      game->status->state=mainMenu;
      clearInput(game);
   }
   if(game->status->state==mainMenu && game->input->enter) {
      game->status->state=newGameMenu;
      clearInput(game);
   }
   if (game->status->state == newGameMenu && game->input->escape) {
      game->status->state=optionsMenu;
      clearInput(game);

   }
   if(game->status->state==mainMenu && game->input->escape) {
      game->status->state=optionsMenu;
      clearInput(game);

   }
}
