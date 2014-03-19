/**
 * \file menu.c
 * \brief Functions to draw all the menu stuffs, options, credits, splashdcreen etc ...
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 */

#include "menu.h"

void initMenu (Game* game) {
   /*a faire apres avec xml peut etre ? */
   game->menu = (Menu*) malloc(sizeof(Menu));
   game->menu->menuSpriteSheet = IMG_Load("res/image/menu/blueSheet.png");
   game->menu->splashScreen = IMG_Load("res/image/menu/splashScreen.png");

   game->menu->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   game->menu->rectDst = (SDL_Rect*) malloc(sizeof(SDL_Rect));

   game->menu->itemsNumber = 4;
}

void updateMenu(Game* game) {
   if(game->)
}

void displayMenu(Game* game) {

   displaySplashScreen(game);
   displayMenuBlock(game);
   /*writeMenu(Game* game);*/
}

/* A améliorer, notament prendre en compte la r&solution, et le nombre d'item dans le menu*/
void displayMenuBlock(Game* game) {

   game->menu->rectSrc->x = 0;
   game->menu->rectSrc->y = 0;
   game->menu->rectSrc->w = 190; /*Should be done in the initMenu function*/
   game->menu->rectSrc->h = 49;

   game->menu->rectDst->x = game->options->windowWidth/2 - (190/2);
   game->menu->rectDst->y = game->options->windowHeight/2 + 60;
   game->menu->rectDst->w = 190;
   game->menu->rectDst->h = 49;

   SDL_BlitSurface(game->menu->menuSpriteSheet, game->menu->rectSrc, game->screen, game->menu->rectDst);

   game->menu->rectDst->y = game->options->windowHeight/2 + 120; /*écrire peut etre + offset*/

   SDL_BlitSurface(game->menu->menuSpriteSheet, game->menu->rectSrc, game->screen, game->menu->rectDst);

   game->menu->rectDst->y = game->options->windowHeight/2 + 180;

   SDL_BlitSurface(game->menu->menuSpriteSheet, game->menu->rectSrc, game->screen, game->menu->rectDst);
}

void updateSplashScreen(Game* game){

}

void displaySplashScreen (Game* game){

   SDL_BlitSurface(game->menu->splashScreen, NULL, game->screen, NULL);/* on fera mieux plus tard pour le splash screen*/
}
