/**
 * \file menu.h
 * \brief Prototypes of functions that draw the menu stuffs on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */


#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "structs.h"
#include "input.h"

void initMenu (Game* game);

void updateMenu(Game* game);

void displayMenu(Game* game);

void displayMenuBlock(Game* game);

void updateSplashScreen(Game* game);

void displaySplashScreen (Game* game);

#endif
