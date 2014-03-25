/**
 * \file game.c
 * \brief Major functions for the game.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "game.h"

//le level n'est initialiser qu'apres le menu !!!
/*décomposer plus cette fonction, tout revoir*/
// malloc chaque structure de Game puis lancer init.....*/
int initGame(Game* game) {

   if(initSDL()) {
      return -1;
   }

   game->status = (GameStatus*) malloc(sizeof(GameStatus));
   initGameStatus(game->status);

   game->options = (GameOptions*) malloc(sizeof(GameOptions));
   initGameOptions(game->options);

   game->input = (Input*) malloc(sizeof(Input));
   initInput(game->input);

   game->menu = (Menu*) malloc(sizeof(Menu));  // ou alors on peut faire game->menu = initMenu();
   initMenu(game->menu);

   /*Create the SDL window*/
   game->screen = SDL_SetVideoMode(game->options->windowWidth, game->options->windowHeight, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

   if(game->screen == NULL) {
      fprintf(stderr, "Unable to create the window : %s\n", SDL_GetError());
      return -1;
   }
   SDL_WM_SetCaption("My Little Project", NULL);
   SDL_WM_SetIcon(IMG_Load("res/icon.png"),NULL);


   /*Initialisation des timers*/ //function initTicks
   game->status->nextTick = SDL_GetTicks() + SKIP_TICKS;
   printf("%d initTicks\n", game->status->nextTick);

   return 0;
}

/**
 * Initialisation of SDL and SDL image
 */
int initSDL () {
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
   return 0;
}

void updateGame(Game* game) {

   getInput(game->input, game->options); /*on recupere les inputs, arche bien pour l'instant*/

   updateGameStatus(game->status, game->input); /*on update d'abord le statud du jeu*/

//puis switch pour update la partie qui va bien
}



void clearScreen (Game* game) {
   SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 255, 255, 255));
}

void displayGame(Game* game) {
   printf("%d before clear screen\n", SDL_GetTicks());
   clearScreen(game);

   switch (game->status->state) {

   case intro :
      //displayIntro();
      break;
   case mainMenu :
      displayMenu(game->menu, game->screen);
      break;
   case newGameMenu :
      displayMenu(game->menu, game->screen);
      break;
   case continueMenu :
      displayMenu(game->menu, game->screen);
      break;
   case optionsMenu :
      displayMenu(game->menu, game->screen);
      break;
   case creditsMenu :
      displayMenu(game->menu, game->screen);
      break;
   case inGame :
      displayLevel(game->level, game->screen);
      displayCharacter(game->player, game->screen);
      break;
   case inGameMenu :
      displayCharacter(game->player, game->screen);
      break;
   case inGamePopUp :
      displayCharacter(game->player, game->screen);
   }

   printf("%d before Flipping the screen\n", SDL_GetTicks());

   if(SDL_Flip(game->screen) == -1) {
      logError("Error when flipping screen", __FILE__, __LINE__);
   }
}

/**
 * \param game Pointer on a Game structure.
 * \brief Wait a brief amount of time so the game runs at a constant FPS.
 */
void delayGame(Game* game) {

   Uint32 tick = SDL_GetTicks();
   game->status->sleepTime = 0;

   if (game->status->nextTick > tick) {
      game->status->sleepTime = game->status->nextTick - tick;
      SDL_Delay(game->status->sleepTime);
   }
   printf(" sleeptime : %d\n\n",game->status->sleepTime);

   game->status->nextTick += SKIP_TICKS;
}
