/**
 * \file menu.c
 * \brief Functions to draw all the menu stuffs, options, credits, splashdcreen etc ...
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 */

#include "menu.h"

//init du main menu au lancement du jeu
void initMenu (Menu* menu) {
   /*a faire apres avec xml peut etre ? */
   //menu->menuSpriteSheet = loadImage("res/image/menu/blueSheet.png"); //Ici on charge le fond du menu, on peut dierct le redimensionner à la taille du screen
   menu->splashScreen = loadImage("res/image/menu/splashScreen.png");//faster bicth !
   //menu->splashScreen = IMG_Load("res/image/menu/blueSheet.png"); // slower bitch !

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
void displayMenu(Menu* menu, SDL_Surface* screen) {

   displaySplashScreen(menu, screen);
   //displayMenuBlock();
   /*writeMenu();*/
}

/* A améliorer, notament prendre en compte la r&solution, et le nombre d'item dans le menu*/
void displayMenuBlock() {

}

void displaySplashScreen (Menu* menu, SDL_Surface* screen) {
   printf("%d before blit\n", SDL_GetTicks());
   SDL_BlitSurface(menu->splashScreen, NULL, screen, NULL);/* on fera mieux plus tard pour le splash screen*/

   printf("%d after blit\n", SDL_GetTicks());
}
