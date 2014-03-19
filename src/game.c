/**
 * \file game.c
 * \brief Major functions for the game.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "game.h"

/*décomposer plus cette fonction*/
int initGame(Game* game) {

   /*Initialisation SDL*/
   if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf(stderr, "Unable to initialize SDL : %s\n", SDL_GetError());
      return -1;
   }
   atexit(SDL_Quit);

   if(IMG_Init(IMG_INIT_PNG) < 0) {
      fprintf(stderr, "Unable to initialize SDL_image : %s\n", IMG_GetError());
      return -1;
   }
   atexit(IMG_Quit);

   /*Initialisation GameStatus*/
   initGameStatus(game);

   /*Initialisation GameOptions*/
   initGameOptions(game);

   /*Create the SDL window*/
   game->screen = SDL_SetVideoMode(game->options->windowWidth, game->options->windowHeight, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

   if(game->screen == NULL) {
      fprintf(stderr, "Unable to create the window : %s\n", SDL_GetError());
      return -1;
   }
   SDL_WM_SetCaption("My Little Project", NULL);
   SDL_WM_SetIcon(IMG_Load("res/icon.png"),NULL);

   initMenu(game);
   initCharacter(game);
   initLevel(game);

   /*Initialisation de la gestion d'event*/
   initInput(game);

   /*Initialisation des timers*/
   game->status->nextTick = SDL_GetTicks() + SKIP_TICKS;

   return 0;
}

void updateGame(Game* game) {

   getInput(game); /*on recupere les input*/

   updateGameStatus(game); /*on update d'abord le statud du jeu*/

   switch (game->status->state) { /*je sais pas trop pour ca*/
   case intro :
      /*updateIntro(game);*/
      break;

   case mainMenu :
      updateMenu(game);
      break;
   case newGameMenu :
      updateMenu(game);
      break;
   case continueMenu :
      updateMenu(game);
      break;
   case creditsMenu :
      updateMenu(game);
      break;
   case optionsMenu :
      updateMenu(game);
      break;

   case inGame :
      updateCharacter(game);
      updateLevel(game);
      break;
   case inGameMenu :
      break;
   case inGamePopUp :
      updateLevel(game);
      ;
   }
}


void clearScreen (Game* game) {

   SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 255, 255, 255));
}

void displayGame(Game* game) {

   clearScreen(game);

   switch (game->status->state) { /*je sais pas trop pour ca*/
   case intro :
      /*displayIntro(game);*/
      break;

   case mainMenu :
      displayMenu(game);
      break;
   case newGameMenu :
      displayMenu(game);
      break;
   case continueMenu :
      displayMenu(game);
      break;
   case creditsMenu :
      displayMenu(game);
      break;
   case optionsMenu :
      displayMenu(game);
      break;

   case inGame :
      displayLevel(game);
      displayCharacter(game);
      break;
   case inGameMenu :
      displayLevel(game);
      displayCharacter(game);
      break;
   case inGamePopUp :
      displayLevel(game);
      displayCharacter(game);
      break;
   }


   if(SDL_Flip(game->screen) == -1) {
      logError("Error when flipping screen", __FILE__, __LINE__);
   }
}

/**
 * \param game Pointer on a Game structure.
 * \brief Function to wait a brief amount of time so the game runs at a constant FPS.
 */
void delayGame(Game* game) {

   game->status->sleepTime = 0;

   if (game->status->nextTick > SDL_GetTicks()) {
      game->status->sleepTime = game->status->nextTick - SDL_GetTicks();
   }

   game->status->nextTick += SKIP_TICKS;

   SDL_Delay(game->status->sleepTime);
}
