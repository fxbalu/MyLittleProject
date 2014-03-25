/**
 * \file menu.h
 * \brief Prototypes of functions that draw the menu stuffs on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */


#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

/**
 * \struct Menu
 * \brief Informations to draw (just draw the current menu)the menu on the screen
 */
typedef struct Menu {
   char** contenu;/*nom a revoir */

   SDL_Surface* menuSpriteSheet; /* struct item menu a ajouter ?*/
   SDL_Surface* splashScreen;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;

} Menu;

void initMenu (Menu* menu);

void updateMenu();//gérer l'update dans game statut ?

void displayMenu(Menu* menu, SDL_Surface* screen);

void displayMenuBlock();

// void updateSplashScreen(Game* game); plus tard

void displaySplashScreen (Menu* menu, SDL_Surface* screen);

#endif
