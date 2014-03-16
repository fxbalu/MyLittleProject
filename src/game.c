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
   initGameStatus(game);

   /*Creation de la fenetre */
   game->screen = SDL_SetVideoMode(game->options->windowWidth, game->options->windowHeight, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

   if(game->screen == NULL) {
      fprintf(stderr, "Unable to create the window : %s\n", SDL_GetError());
      return -1;
   }

   initLevel(game);

   /*Initialisation des timers*/
   game->status->nextTick = SDL_GetTicks()+SKIP_TICKS;

   /*Initialisation de la gestion d'event*/
   /*init GameEvent or Input*/
   game->event = (GameEvent*) malloc(sizeof(GameEvent));
   SDL_PollEvent(&game->event->sdlEvent);

   return 0;
}

void initGameStatus(Game* game){
   game->status = (GameStatus*) malloc(sizeof(GameStatus));
   game->status->gameIsRunning = true;
   game->options = (GameOptions*) malloc(sizeof(GameOptions));
   game->options->fullscreen = false;
   game->options->windowWidth = WINDOW_WIDTH_DEFAULT;
   game->options->windowHeight = WINDOW_HEIGHT_DEFAULT;
   game->status->nextTick = game->status->sleepTime = 0;

   game->status->fps=0;/*Temporary*/
   game->status->fpsStart = SDL_GetTicks();
   game->status->fpsEnd = SDL_GetTicks() + SKIP_TICKS;
}

void initLevel(Game* game){
   game->level = (Level*) malloc(sizeof(Level));
   game->level->imgTest = SDL_LoadBMP("icon.bmp");
   game->level->src = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   game->level->src->x = game->level->src->y = 150;
}

void gameDelay(Game* game) {

   game->status->sleepTime = 0;
   if (game->status->nextTick > SDL_GetTicks()){
      game->status->sleepTime = game->status->nextTick - SDL_GetTicks();
   }
   game->status->nextTick += SKIP_TICKS;

   if(game->status->sleepTime >= 0) {
      SDL_Delay(game->status->sleepTime); /*Pas terrible le sdl delay, à voir si on modifie ca*/
   }
}

void gameEvent(Game* game){

   SDL_PollEvent(&(game->event->sdlEvent));

   if(game->event->sdlEvent.type == SDL_QUIT){
      game->status->gameIsRunning = false;
   }
}

void gameUpdate(Game* game) {
   SDL_FillRect(game->screen, NULL, SDL_MapRGB(game->screen->format, 0, 0, 0));
}

void gameDisplay(Game* game){

   /*display background
   display tiles
   display character
   display HUD
   ...*/

   SDL_BlitSurface(game->level->imgTest, NULL, game->screen, game->level->src);
  /* game->status->fps++;
   game->status->fpsEnd = SDL_GetTicks();
   if(game->status->fpsEnd >10000)
      fprintf(stdout, "%d %d %d\n", game->status->fps,game->status->fpsEnd, game->status->fpsStart);*/
   SDL_Flip(game->screen);
   /*
   if(SDL_Flip(game->screen) == -1){
      logError("error during the flip screen", __FILE__, __LINE__);
   }*/
}
