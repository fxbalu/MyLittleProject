/**
 * \file game.c
 * \brief Major functions for the game.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include <stdio.h>   /* malloc() */
#include <SDL.h>     /* SDL_SetVideoMode() */
#include "game.h"    /* Game */
#include "log.h"     /* logError(), logMem() */

//le level n'est initialiser qu'apres le menu !!!
/*décomposer plus cette fonction, tout revoir*/
// malloc chaque structure de Game puis lancer init.....*/

/**
 * \brief Initialize the global Game structure
 *
 * \return Error code, 0 if everything is fine.
 * \todo use an unique code for each error.
 */
int initGame(Game* game) {

   /** \warning fxbalu: why initGame should initialize SDL ? */
   if(initSDL() != 0) {
      return -1;
   }

   if(game == NULL) {
      logError("Trying to initialize a NULL game structure", __FILE__, __LINE__);
      return -1;
   } else {
      /* initialize game status */
      if((game->status = (GameStatus*) malloc(sizeof(GameStatus))) == NULL) {
         logError("Can't allocate memory for a GameStatus", __FILE__, __LINE__);
         return -1;
      } else {
         logMem(LOG_ALLOC, game->status, "GameStatus", "game's status", __FILE__, __LINE__);
         initGameStatus(game->status);
      }

      /* initialize game options */
      if((game->options = (GameOptions*) malloc(sizeof(GameOptions))) == NULL) {
         logError("Can't allocate memory for a GameOptions", __FILE__, __LINE__);
         return -1;
      } else {
         logMem(LOG_ALLOC, game->options, "GameOptions", "game's options", __FILE__, __LINE__);
         initGameOptions(game->options);
      }

      /* Create the SDL window after the options (because options contains the dimensions of the window*/
      game->screen = SDL_SetVideoMode(game->options->windowWidth,
                                      game->options->windowHeight,
                                      32,
                                      SDL_HWSURFACE|SDL_DOUBLEBUF);
      if(game->screen == NULL) {
         logError("Unable to create the window.", __FILE__, __LINE__);
         //fprintf(stderr, "Unable to create the window : %s\n", SDL_GetError());
         return -1;
      }

      /* initialize game's input */
      if((game->input = (Input*) malloc(sizeof(Input))) == NULL) {
         logError("Can't allocate memory for an Input", __FILE__, __LINE__);
         return -1;
      } else {
         logMem(LOG_ALLOC, game->input, "Input", "game's input", __FILE__, __LINE__);
         initInput(game->input);
      }

            if((game->intro = (Intro*) malloc(sizeof(Intro))) == NULL) {
         logError("Can't allocate memory for an Intro", __FILE__, __LINE__);
         return -1;
      } else {
         logMem(LOG_ALLOC, game->status, "Intro", "game's intro", __FILE__, __LINE__);
         initIntro(game->intro);
      }

      // ou alors on peut faire game->menu = initMenu();
      // fxbalu: On devrait faire ça pour tout en fait.
      /* initialize game's menu */
      if((game->menu = (Menu*) malloc(sizeof(Menu))) == NULL) {
         logError("Can't allocate memory for a Menu", __FILE__, __LINE__);
         return -1;
      } else {
         logMem(LOG_ALLOC, game->menu, "Menu", "game's menu", __FILE__, __LINE__);
         initMenu(game->menu);
      }

      /* initialize game's level */
      if((game->level = (Level*) malloc(sizeof(Level))) == NULL) {
         logError("Can't allocate memory for a Level", __FILE__, __LINE__);
         return -1;
      } else {
         logMem(LOG_ALLOC, game->level, "Level", "game's level", __FILE__, __LINE__);
         initLevel(game->level);
      }

      /* initialize game's main character, the player */
      if((game->player = (Character*) malloc(sizeof(Character))) == NULL) {
         logError("Can't allocate memory for a Character", __FILE__, __LINE__);
         return -1;
      } else {
         logMem(LOG_ALLOC, game->player, "Character", "game's player", __FILE__, __LINE__);
         initCharacter(game->player);
      }
   }

   /**
    * \warning fxbalu: wtf, hard coded window's name and files' path !
    */
   SDL_WM_SetCaption("My Little Project", NULL);
   SDL_WM_SetIcon(IMG_Load("res/icon.png"),NULL);


   /*Initialisation des timers*/ //function initTicks
   game->status->nextTick = SDL_GetTicks() + SKIP_TICKS;
   //printf("%d initTicks\n", game->status->nextTick);

   return 0;
}


/**
 * \brief Initialize SDL and SDL image.
 *
 * \return Error code, 0 if everything was correctly initialized,
 *         -1 if SDL was not initialized, -2 if SDL_image was not initialized.
 *
 * \warning fxbalu: why is it in game.c ?
 */
int initSDL() {
   /* initialize SDL*/
   if(SDL_Init(SDL_INIT_VIDEO) < 0) {
      logError("Unable to initialize SDL", __FILE__, __LINE__);
      // fprintf(stderr, "Unable to initialize SDL : %s\n", SDL_GetError());
      return -1;
   } else {
      atexit(SDL_Quit);
   }

   /* initialize SDL_image */
   if(IMG_Init(IMG_INIT_PNG) < 0) {
      logError("Unable to initialize SDL_image", __FILE__, __LINE__);
      // fprintf(stderr, "Unable to initialize SDL_image : %s\n", IMG_GetError());
      return -2;
   } else {
      atexit(IMG_Quit);
   }

   return 0;
}


/**
 * \brief Function called at each frame, update all the state of the game, character, level ...
 */
void updateGame(Game* game) {

   getInput(game->input, game->options); /*on recupere les inputs, marche bien*/

   updateGameStatus(game->status, game->input); /*on update d'abord le status du jeu (le graphe d'état)*/

// update les éléments du jeu
   switch (game->status->state) {
   case intro :
      break;
   case mainMenu :
      break;
   case newGameMenu :
      break;
   case continueMenu :
      break;
   case optionsMenu :
      break;
   case creditsMenu :
      break;
   case inGame :
      updateCharacter(game->player, game->level, game->input);
      updateLevel(game->level, game->input);
      break;
   case inGameMenu :
      break;
   case inGamePopUp :
      ;
   }

//puis switch pour update la partie qui va bien
}


/**
 * \brief fills the window with white.
 * \warning fxbalu: why is it in game.c ?
 */
void clearScreen (Game* game) {
   SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 255, 255, 255));
}

/**
 * \brief Function called at each frame, display the game on the screen.
 */
void displayGame(Game* game) {

   clearScreen(game);

   switch (game->status->state) {

   case intro :
      displayIntro(game->intro, game->screen);
      break;
   case mainMenu :
      displayMenu(game->menu, game->status, game->screen);
      break;
   case newGameMenu :
      displayMenu(game->menu, game->status, game->screen);
      break;
   case continueMenu :
      displayMenu(game->menu, game->status, game->screen);
      break;
   case optionsMenu :
      displayMenu(game->menu, game->status, game->screen);
      break;
   case creditsMenu :
      displayMenu(game->menu, game->status, game->screen); // or display credits !
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

   //printf("%d before Flipping the screen\n", SDL_GetTicks());

   if(SDL_Flip(game->screen) == -1) {
      logError("Error when flipping screen", __FILE__, __LINE__);
   }
}


/**
 * \brief Wait a brief amount of time so the game runs at a constant FPS.
 * \param game Pointer on a Game structure.
 */
void delayGame(Game* game) {

   Uint32 tick = SDL_GetTicks();
   game->status->sleepTime = 0;

   if (game->status->nextTick > tick) {
      game->status->sleepTime = game->status->nextTick - tick;
      SDL_Delay(game->status->sleepTime);
   }
   //printf(" sleeptime : %d\n\n",game->status->sleepTime);

   game->status->nextTick += SKIP_TICKS;
}
