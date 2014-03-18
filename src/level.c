/**
 * \file level.c
 * \brief Functions to draw the level on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "level.h"

void initLevel(Game* game) {
   game->level = (Level*) malloc(sizeof(Level));
   game->level->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   game->level->rectSrc->x = game->level->rectSrc->y = 150;

   game->level->background = IMG_Load("res/image/background/backgroundworld1.png");
   game->level->tileset = IMG_Load("res/image/tile_tileset.png");

   /*charger le niveau avec le parseur xml*/
}

void updateLevel(Game* game) {

}

void displayLevel(Game* game) {
   displayBackground(game);
}

void displayBackground(Game* game) {
   SDL_BlitSurface(game->level->background, NULL, game->screen, NULL);/*il faudra gérer la caméra plus tard*/
}
