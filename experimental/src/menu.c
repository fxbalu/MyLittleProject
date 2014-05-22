/**
 * \file menu.c
 * \brief
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#include "menu.h"
#include "map.h"
#include "player.h"
#include "draw.h"


/**
 * \fn void updateStartMenu(Input* input, Game* game)
 * \brief
 *
 * \param[in] input
 * \param[in] game
 *
 */
void updateStartMenu(Input* input, Game* game) {

   if(input->down == 1) {

      game->choice++;

      if(game->choice > 2) {
         game->choice = 0;
      }

      input->down = 0;
   }

   else if(input->up == 1) {

      game->choice--;

      if(game->choice < 0) {
         game->choice = 2;
      }

      input->up = 0;
   }


   //Si on appuie sur Enter et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
   else if(input->enter) {

      switch(game->choice) {

      case 0:
         //initializePlayer(game->player); /*start the game and leave the menu*/
         game->onMenu = 0;
         break;
      case 1:
         game->menuType = SELECT_LEVEL; /*selectLevel menu*/
         game->choice = 0;
         break;
      case 2:
         game->go = 0; /*stop the game*/
      }
      input->enter = 0;
   }

}


/**
 * \fn void updateSelectLevelMenu(Input* input, Game* game)
 * \brief
 *
 * \param[in] input
 * \param[in] game
 *
 */
void updateSelectLevelMenu(Input* input, Game* game) {

   char level[200];/*selected level*/

   if(input->right){
      game->choice++;

      if(game->choice > 9){
         game->choice = 0;
      }
      input->right = 0;
   }
   if(input->down){
      if(game->choice == 9){
         game->choice =0;
      }
      else{
         game->choice += 3;
         if(game->choice > 9){
            game->choice = 9;
         }
      }

      input->down = 0;
   }
   if(input->left){
      game->choice--;

      if(game->choice < 0){
         game->choice = 9;
      }
      input->left = 0;
   }
   if(input->up){
      game->choice -= 3;

      if(game->choice < 0){
         game->choice = 9;
      }

      input->up = 0;
   }

   /*select level or back to the start menu*/
   if(input->enter){

      if(game->choice == 9){
         game->choice = 0;
         game->menuType = START;
      }
      else {
         game->choice = 0;
         game->onMenu = 0;

         game->level = game->choice;


         sprintf(level, "data/map/map%d.tmx", game->level );
         loadMap(level, game->map, game); /*load the selected level*/
      }

      input->enter = 0;
   }
}

/**
 * \fn void drawTileMenu(SDL_Surface *image,int x, int y , int frameNumber, Game* game)
 * \brief Draw an item of a menu
 *
 * \param[in] image
 * \param[in] x
 * \param[in] y
 * \param[in] frameNumber
 * \param[in] game
 *
 */
void drawTileMenu(SDL_Surface *image,int x, int y , int frameNumber, Game* game) {
   SDL_Rect dest;

   dest.x = x;
   dest.y = y;
   dest.w = image->w;
   dest.h = image->h;

   SDL_Rect src;

   src.x = frameNumber * 190;
   src.y = 0;
   src.h = image->h;
   src.w = 190;

   SDL_BlitSurface(image, &src, game->screen, &dest);
}


/**
 * \fn int main(int argc, char* argv[])
 * \brief Main function.
 *
 * \param[in] game
 *
 */
void drawStartMenu(Game* game) {

   //On crée une varuiable qui contiendra notre texte
   char text[200];

   drawImage(game->map->backgroundMenu, 0, 0, game);

   if(game->choice == 0) {
      drawTileMenu(game->tileMenu,430,350,1, game);
   } else {
      drawTileMenu(game->tileMenu,430,350,0, game);
   }

   if(game->choice == 1) {
      drawTileMenu(game->tileMenu,430,400,1, game);
   } else {
      drawTileMenu(game->tileMenu,430,400,0, game);
   }

   if(game->choice == 2) {
      drawTileMenu(game->tileMenu,430,450,1, game);
   } else {
      drawTileMenu(game->tileMenu,430,450,0, game);
   }


   sprintf(text, "START");
   drawString(text, 460, 350, 255, 255, 255, game->fontMenu, game);

   sprintf(text, "LEVELS");
   drawString(text, 460, 400, 255, 255, 255, game->fontMenu, game);

   sprintf(text, "QUIT");
   drawString(text, 475, 450, 255, 255, 255,game->fontMenu, game);

   //drawTileMenu(game->tileMenu,430,350,1, game);

   SDL_Flip(game->screen);
   SDL_Delay(1);

}

/**
 * \fn void drawSelectLevelMenu(Game* game)
 * \brief
 *
 * \param[in] game
 *
 */
void drawSelectLevelMenu(Game* game) {

   drawImage(game->map->backgroundMenu, 0, 0, game);
   int i;
   int x;
   int y;

   for (i=0 ; i<9 ; i++){

      x = (i%3)*150 + 325;
      y = ((int)i/3)*150 + 200;

      if(game->choice == i){
         drawTileSelectLevel(game, x, y, 1);
      }
      else {
         drawTileSelectLevel(game, x, y, 0);
      }
   }
   if(game->choice == 9){
      drawTileMenu(game->tileMenu,430,630,1, game);
   }
   else{
      drawTileMenu(game->tileMenu,430,630,0, game);
   }
   drawString("BACK", 470, 630, 255, 255, 255, game->fontMenu, game);

   SDL_Flip(game->screen);
}

/**
 * \fn void drawTileSelectLevel(Game* game, int x, int y, int selected)
 * \brief
 *
 * \param[in] game
 * \param[in] x
 * \param[in] y
 * \param[in] selected
 *
 */
void drawTileSelectLevel(Game* game, int x, int y, int selected) {

   SDL_Rect dest;

   dest.x = x;
   dest.y = y;

   SDL_Rect src;

   src.x = 100*selected;
   src.y = 0;
   src.w = 100;
   src.h = 100;

   SDL_BlitSurface(game->tileSelectLevel, &src, game->screen, &dest);
}
