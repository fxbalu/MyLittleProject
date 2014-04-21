/**
 * \file gameStatus.c
 * \brief Functions to handle the state of the game
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "gameStatus.h"


void initGameStatus(GameStatus* status) {
   status->gameIsRunning = true;
   status->state = intro; //on démarre le jeu à l'intro
   status->menuSelection = 0;
   status->numberItemsMenu = 4;
   status->level = 0;
   status->nextTick = 0;
   status->sleepTime = 0;
}

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
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->left.down) {

   }
   if(input->up.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->up.down) {

   }
   if(input->right.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->right.down) {

   }
   if(input->down.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->jump.down) {

   }
   if(input->crouch.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->crouch.down) {

   }
   if(input->shoot.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
   }
   if(input->shoot.down) {

   }
   if(input->escape.pressed) {
         // appeler la fonction fin d'intro !!
      status->state = mainMenu;
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
      status->menuSelection--;
      if(status->menuSelection < 0) {
         status->menuSelection = status->numberItemsMenu - 1;
      }
   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {
      status->menuSelection++;
      if(status->menuSelection >= status->numberItemsMenu) {
         status->menuSelection = 0;
      }
   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {
      switch (status->menuSelection) { // faire une fonction d'évolution pour les menu ?
      case 0 :
         status->state = newGameMenu;
         status->menuSelection = 0;
         status->numberItemsMenu = 3;
         break;
      case 1 :
         status->state = continueMenu;
         status->menuSelection = 0;
         status->numberItemsMenu = 2;
         break;
      case 2 :
         status->state = optionsMenu;
         status->menuSelection = 0;
         status->numberItemsMenu = 4;
         break;
      case 3 :
         status->state = creditsMenu;
         status->menuSelection = 0;
         status->numberItemsMenu = 0;  //quand 0 items menu spécile !!
      }
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
      status->menuSelection--;
      if(status->menuSelection < 0) {
         status->menuSelection = status->numberItemsMenu - 1;
      }
   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {
      status->menuSelection++;
      if(status->menuSelection >= status->numberItemsMenu) {
         status->menuSelection = 0;
      }
   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {
      switch (status->menuSelection) { // faire une fonction d'évolution pour les menu ?
      case 0 :
         status->state = inGame;
         break;
      case 1 :
         break;
      case 2 :
         status->state = mainMenu;
         status->numberItemsMenu = 4;
         status->menuSelection = 0;
         //LoadMenu(mainMenu)
      }
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
      status->state = mainMenu;
      //LoadMenu(mainMenu)
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
      status->menuSelection--;
      if(status->menuSelection < 0) {
         status->menuSelection = status->numberItemsMenu - 1;
      }
   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {
      status->menuSelection++;
      if(status->menuSelection >= status->numberItemsMenu) {
         status->menuSelection = 0;
      }
   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {
      switch (status->menuSelection) { // faire une fonction d'évolution pour les menu ?
      case 0 :
         status->state = inGame;
         break;
      case 1 :
         status->state = mainMenu;
         status->numberItemsMenu = 4;
         status->menuSelection = 0;
         //LoadMenu(mainMenu)
      }
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
      status->state = mainMenu;
      //LoadMenu(mainMenu)
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
      status->menuSelection--;
      if(status->menuSelection < 0) {
         status->menuSelection = status->numberItemsMenu - 1;
      }
   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {
      status->menuSelection++;
      if(status->menuSelection >= status->numberItemsMenu) {
         status->menuSelection = 0;
      }
   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {
      switch (status->menuSelection) { // faire une fonction d'évolution pour les menu ?
      case 0 :
         break;
      case 1 :
         break;
      case 2 :
         break;
      case 3 :
         status->state = mainMenu;
         status->numberItemsMenu = 4;
         status->menuSelection = 0;
         //LoadMenu(mainMenu)
      }
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
               status->state = mainMenu;
         status->numberItemsMenu = 4;
         status->menuSelection = 0;
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
      status->menuSelection--;
      if(status->menuSelection < 0) {
         status->menuSelection = status->numberItemsMenu - 1;
      }
   }
   if(input->up.down) {

   }
   if(input->right.pressed) {

   }
   if(input->right.down) {

   }
   if(input->down.pressed) {
      status->menuSelection++;
      if(status->menuSelection >= status->numberItemsMenu) {
         status->menuSelection = 0;
      }
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
      status->state = mainMenu;
      status->numberItemsMenu = 4;
      status->menuSelection = 0;
      //LoadMenu(mainMenu)
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
      status->state = mainMenu;
      status->numberItemsMenu = 4;
      status->menuSelection = 0;
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
