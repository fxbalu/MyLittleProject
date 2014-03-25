/**
 * \file level.c
 * \brief Functions to draw the level on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "level.h"



void initLevel (Level* level) {

   level->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   level->rectSrc->x = level->rectSrc->y = 150;

   level->background = loadImage("res/image/background/backgroundworld1.png");
   level->tileset = loadImage("res/image/tileset/tilesetLevel.png");

   /*charger le niveau avec le parseur xml*/
}

void updateLevel (Level* level) {

}

void displayLevel (Level* level, SDL_Surface* screen) {
   displayBackground(level, screen);
}

void displayBackground (Level* level, SDL_Surface* screen) {
    SDL_BlitSurface(level->background, NULL, screen, NULL);/*il faudra gérer la caméra plus tard, double scrolling ?*/
}

