#include "Game.h"

int gameInit(Game* game) {

   /*Initialisation SDL*/
   if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      fprintf(stderr, "Unable to initialize SDL : %s\n", SDL_GetError());
      return -1;
   }
   atexit(SDL_Quit);

   /* Initialisation GameStatus*/
   game->status = (GameStatus*) malloc(sizeof(GameStatus));
   initGameStatus(game->status);

   /*Creation de la fenetre */
   game->screen = SDL_SetVideoMode(game->status->options->windowWidth, game->status->options->windowHeight, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

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

void gameDelay(Game* game) {

   game->status->nextTick += SKIP_TICKS;
   game->status->sleepTime = game->status->nextTick - SDL_GetTicks();

   if(game->status->sleepTime >= 0) {
      SDL_Delay(game->status->sleepTime); /*Pas terrible le sdl delay, �voir si on modifie ca*/
   }
}

void gameUpdate(Game* game){
   //check events (to be able to close this fuckin' window
   //...
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