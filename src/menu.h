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
#include "define.h"
#include "common.h"
#include "gameStatus.h"

/**
 * \struct Menu
 * \brief Informations to draw (just draw the current menu)the menu on the screen
 */
typedef struct ItemMenu {
   //enum pour indiquier le type de l'item
} ItemMenu;

/**
 * \struct Menu
 * \brief Informations to draw (just draw the current menu)the menu on the screen
 */
typedef struct Menu {
   ItemMenu** itemList;/*nom a revoir, tableau représentant le menu */

   SDL_Surface* menuSpriteSheet; /* struct item menu a ajouter ?*/
   SDL_Surface* splashScreen;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;

} Menu;

void initMenu (Menu* menu);

void updateMenu();//gérer l'update dans game statut ? oui ! mais aussi un updatee ici si on veux un truc de dynamique

void displayMenu(Menu* menu, GameStatus* status, SDL_Surface* screen);

void displayMenuBlock(Menu* menu, GameStatus* status, SDL_Surface* screen);

// void updateSplashScreen(Game* game); plus tard

void displaySplashScreen (Menu* menu, SDL_Surface* screen);

#endif
