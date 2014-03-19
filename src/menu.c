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

   game->menu->numberItem = 4;
   game->menu->selectItem = 0;
}

void updateMenu(Game* game) {

   switch (game->status->state) {
   case mainMenu :
      game->menu->numberItem = 4;
      /*game->menu->contenu*/
      break;
   case newGameMenu :
      game->menu->numberItem = 3;
      /*game->menu->contenu*/
      break;
   case continueMenu :
      game->menu->numberItem = 2;
      /*game->menu->contenu*/
      break;
   case optionsMenu :
      game->menu->numberItem = 1;
      /*game->menu->contenu*/
      break;
   case creditsMenu :
      game->menu->numberItem = 0;
      /*game->menu->contenu*/
      break;
   default :
      ;
   }
   if (game->input->up) {
      game->menu->selectItem--;
      clearInput(game); /*éviter que ca défile tout seule*/

      if (game->menu->selectItem < 0) {
         game->menu->selectItem = game->menu->numberItem - 1;
      }
   } else if (game->input->down) {
      game->menu->selectItem++;
      clearInput(game);
      if (game->menu->selectItem >= game->menu->numberItem) {
         game->menu->selectItem = 0;
      }
   }
}

void displayMenu(Game* game) {

   displaySplashScreen(game);
   displayMenuBlock(game);
   /*writeMenu(Game* game);*/
}

/* A améliorer, notament prendre en compte la r&solution, et le nombre d'item dans le menu*/
void displayMenuBlock(Game* game) {

   int i;

   game->menu->rectSrc->x = 0;
   game->menu->rectSrc->y = 0;
   game->menu->rectSrc->w = 190; /*Should be done in the initMenu function*/
   game->menu->rectSrc->h = 49;

   game->menu->rectDst->x = game->options->windowWidth/2 - (190/2);
   game->menu->rectDst->y = game->options->windowHeight/2 + 100;

   for(i=0 ; i<game->menu->numberItem ; i++) {
      if (i == game->menu->selectItem) {
         game->menu->rectSrc->x = 0;
         game->menu->rectSrc->y = 192;
         game->menu->rectSrc->w = 190;
         game->menu->rectSrc->h = 45;

         game->menu->rectDst->y += 4;
      }
      SDL_BlitSurface(game->menu->menuSpriteSheet, game->menu->rectSrc, game->screen, game->menu->rectDst);

      game->menu->rectSrc->x = 0;
      game->menu->rectSrc->y = 0;
      game->menu->rectSrc->w = 190;
      game->menu->rectSrc->h = 49;
      game->menu->rectDst->y += 60;
   }
}

void updateSplashScreen(Game* game) {

}

void displaySplashScreen (Game* game) {

   SDL_BlitSurface(game->menu->splashScreen, NULL, game->screen, NULL);/* on fera mieux plus tard pour le splash screen*/
}
