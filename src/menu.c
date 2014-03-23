/**
 * \file menu.c
 * \brief Functions to draw all the menu stuffs, options, credits, splashdcreen etc ...
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 */

#include "menu.h"

void initMenu (Menu* menu) {
   /*a faire apres avec xml peut etre ? */
   menu->menuSpriteSheet = IMG_Load("res/image/menu/blueSheet.png"); //Ici on charge le fond du menu, on peut dierct le redimensionner à la taille du screen
   menu->splashScreen = IMG_Load("res/image/menu/splashScreen.png");

   menu->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   menu->rectDst = (SDL_Rect*) malloc(sizeof(SDL_Rect));

   menu->numberItem = 4;
   menu->selectItem = 0;
}

void updateMenu() {

}

void displayMenu(Menu* menu, SDL_Surface* screen) {

   displaySplashScreen(menu, screen);
   displayMenuBlock();
   /*writeMenu();*/
}

/* A améliorer, notament prendre en compte la r&solution, et le nombre d'item dans le menu*/
void displayMenuBlock() {

}

void displaySplashScreen (Menu* menu, SDL_Surface* screen) {

   SDL_BlitSurface(menu->splashScreen, NULL, screen, NULL);/* on fera mieux plus tard pour le splash screen*/
}
