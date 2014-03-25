/**
 * \file menu.c
 * \brief Functions to draw all the menu stuffs, options, credits, splashdcreen etc ...
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 */

#include "menu.h"

//init du main menu au lancement du jeu
void initMenu (Menu* menu) {
   /*a faire apres avec xml peut etre ? */
   menu->menuSpriteSheet = loadImage("res/image/menu/spriteSheetMenu.png");
   menu->splashScreen = loadImage("res/image/menu/splashScreen.png");


   menu->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   menu->rectDst = (SDL_Rect*) malloc(sizeof(SDL_Rect));
}

void updateMenu() {

}

/*a faire apres avec xml peut etre ? */
//  quand on change de menu
/*void loadMenu (Menu* menu, State State) {

}
*/
//display le menu qui est chargé !
void displayMenu(Menu* menu, GameStatus* status, SDL_Surface* screen) {

   displaySplashScreen(menu, screen);
   displayMenuBlock(menu, status, screen); // structure correcte ?
   /*writeMenu();*/
}

/* A améliorer, notament prendre en compte la résolution, et le nombre d'item dans le menu*/
void displayMenuBlock(Menu* menu, GameStatus* status, SDL_Surface* screen) {

   int i = 0;
   menu->rectDst->x = (WINDOW_WIDTH_DEFAULT - WIDTH_MENU_ITEM_DEFAULT)/2;
   menu->rectDst->y = 380;//WINDOW_HEIGHT_DEFAULT*2/3;

   for(i=0 ; i<status->numberItemsMenu ; i++) {

      if(status->menuSelection == i) {
         menu->rectSrc->x = WIDTH_MENU_ITEM_DEFAULT;
         menu->rectSrc->y = 0;
         menu->rectSrc->w = WIDTH_MENU_ITEM_DEFAULT;
         menu->rectSrc->h = HEIGHT_MENU_ITEM_SELECTED_DEFAULT;

         menu->rectDst->y = 380 + i*MENU_OFFSET - (4);

      } else {
         menu->rectSrc->x = 0;
         menu->rectSrc->y = 0;
         menu->rectSrc->w = WIDTH_MENU_ITEM_DEFAULT;
         menu->rectSrc->h = HEIGHT_MENU_ITEM_DEFAULT;

         menu->rectDst->y = 380 + i*MENU_OFFSET;
      }



      SDL_BlitSurface(menu->menuSpriteSheet, menu->rectSrc, screen, menu->rectDst);
   }
}

void displaySplashScreen (Menu* menu, SDL_Surface* screen) {
   printf("%d before blit\n", SDL_GetTicks());
   SDL_BlitSurface(menu->splashScreen, NULL, screen, NULL);/* on fera mieux plus tard pour le splash screen*/

   printf("%d after blit\n", SDL_GetTicks());
}
