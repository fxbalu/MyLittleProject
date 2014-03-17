/**
 * \file level.c
 * \brief Functions to draw the level on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

 #include "level.h"

void initLevel(Game* game) {
   game->level = (Level*) malloc(sizeof(Level));
   game->level->imgTest = SDL_LoadBMP("res\\icon.bmp");
   game->level->src = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   game->level->src->x = game->level->src->y = 150;

   game->level->background = SDL_LoadBMP("res\\image\\background\\backgroundworld1.bmp");
}

void displayLevel(Game* game){
   displayBackground(game);
}

void displayBackground(Game* game) {
   SDL_BlitSurface(game->level->background, NULL, game->screen, NULL);/*il faudra gérer la caméra plus tard*/
}
