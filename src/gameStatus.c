/**
 * \file gameStatus.c
 * \brief Functions to handle the state of the game
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "gameStatus.h"


void initGameStatus(GameStatus* status) {
   status->gameIsRunning = true;
   status->state = mainMenu; //intro
   status->level = 0;
   status->nextTick = 0;
   status->sleepTime = 0;
}

/*a refaire, peut etre avec des switchs*/
/*dans quel ordre faire les tests ? d'abord les directions*/
void updateGameStatus (GameStatus* status, Input* input) {

   switch (status->state) {

   case intro :
      updateIntro(status, input);
      break;
   case mainMenu :
      updateMainMenu(status, input);
      break;
   case newGameMenu :
      updateNewGameMenu(status, input);
      break;
   case continueMenu :
      updateContinueMenu(status, input);
      break;
   case optionsMenu :
      updateOptionsMenu(status, input);
      break;
   case creditsMenu :
      updateCreditsMenu(status, input);
      break;
   case inGame :
      updateInGame(status, input);
      break;
   case inGameMenu :
      updateInGameMenu(status, input);
      break;
   case inGamePopUp :
      updateInGamePopUp(status, input);
   }
   //faire le graph d'état, mais avant gérer les input
}



void updateIntro(GameStatus* status, Input* input) {

   if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateMainMenu(GameStatus* status, Input* input) {

   if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateNewGameMenu(GameStatus* status, Input* input) {

   if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateContinueMenu(GameStatus* status, Input* input) {

   if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateOptionsMenu(GameStatus* status, Input* input) {

   if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateCreditsMenu(GameStatus* status, Input* input) {

      if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateInGame(GameStatus* status, Input* input) {

      if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateInGameMenu(GameStatus* status, Input* input) {

      if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}

void updateInGamePopUp(GameStatus* status, Input* input) {

      if(input->left.pressed) {

   }
   if(input->left.down) {

   }
   if(input->up.pressed) {

   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {

   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {

   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {

   }
   if(input->escape.down) {

   }
   if(input->exit.pressed) {
      status->gameIsRunning = false;
   }
   if(input->exit.down) {
      status->gameIsRunning = false;
   }
}
