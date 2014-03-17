/**
 * \file menu.c
 * \brief Functions to draw all the menu stuffs, options, credits, splashdcreen etc ...
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 */

#include "menu.h"

void initMenu (Game* game) {
   game->menu = (Menu*) malloc(sizeof(Menu));
   game->menu->menuSpriteSheet = SDL_LoadBMP("res\\blueSheet.bmp");
   game->menu->splashScreen = SDL_LoadBMP("res\\splashScreen.bmp");
}


void displayMenu(Game* game) {
   SDL_BlitSurface(game->menu->splashScreen, NULL, game->screen, NULL);
   SDL_BlitSurface(game->menu->menuSpriteSheet, NULL, game->screen, NULL);
}
