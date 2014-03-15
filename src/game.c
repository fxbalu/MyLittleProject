/*!
 * \file game.c
 * \brief major functions for the game
 * \author fx.balu & a.dufac & g.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "game.h"

int gameInit(Game* game) {

   /*Initialisation SDL*/
   if(SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "Unable to initialize SDL : %s\n", SDL_GetError());
      return -1;
   }
   atexit(SDL_Quit);

   /* Initialisation GameStatus*/
   game->status = (GameStatus*) malloc(sizeof(GameStatus));
   initGameStatus(game);

   /*Creation de la fenetre */
   game->screen = SDL_SetVideoMode(game->options->windowWidth, game->options->windowHeight, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

   if(game->screen == NULL) {
      fprintf(stderr, "Unable to create the window : %s\n", SDL_GetError());
      return -1;
   }

   /*Initialisation des timers*/
   game->status->nextTick = SDL_GetTicks();

   /*Initialisation de la gestion d'event*/
   SDL_PollEvent(&game->event);

   return 0;
}

void initGameStatus(Game* game){
   game->status->gameIsRunning = true;
   game->options = (GameOptions*) malloc(sizeof(GameOptions));
   game->options->fullscreen = false;
   game->options->windowWidth = WINDOW_WIDTH_DEFAULT;
   game->options->windowHeight = WINDOW_HEIGHT_DEFAULT;
   game->status->nextTick = game->status->sleepTime = 0;
}

void gameDelay(Game* game) {

   game->status->nextTick += SKIP_TICKS;
   game->status->sleepTime = game->status->nextTick - SDL_GetTicks();

   if(game->status->sleepTime >= 0) {
      SDL_Delay(game->status->sleepTime); /*Pas terrible le sdl delay, àvoir si on modifie ca*/
   }
}

void gameEvent(Game* game){

   while(SDL_PollEvent(&game->event)){
      if(game->event.type==SDL_QUIT)
         game->status->gameIsRunning=0;
   }
}

void gameDisplay(Game* game){

   //display background
   //display tiles
   //display character
   //display HUD
   //...

}
