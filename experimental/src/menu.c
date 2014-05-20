/**
 * \file menu.c
 * \brief
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#include "menu.h"
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
      //Si choice = O (il est sur start), on le met à 1 (quit)
      if(game->choice == 0)
         game->choice++;

      input->down = 0;
   }

   //Si on appuie sur HAUT
   if(input->up == 1) {
      //Si choice = 1 (il est sur Quit), on le met à 0 (Start)
      if(game->choice == 1)
         game->choice--;

      input->up = 0;
   }

   //Si on appuie sur Enter et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
   if(input->enter) {
      if(game->choice == 0) {
         initializePlayer(game->player);
         game->onMenu = 0;
      }
      //Sinon, on quitte le jeu
      else if(game->choice == 1) {
         game->go = 0;
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

   //Si l'option n'est pas en surbrillance, on l'affiche normalement, sinon on rajoute ">"
   if(game->choice != 0) {
      sprintf(text, "START");
      drawTileMenu(game->tileMenu,430,350,0, game);
      drawString(text, 460, 350, 255, 255, 255, game->fontMenu, game);
   }
   if(game->choice != 1) {
      sprintf(text, "QUIT");
      drawTileMenu(game->tileMenu,430,450,0, game);
      drawString(text, 470, 450, 255, 255, 255,game->fontMenu, game);
   }


   if(game->choice == 0) {
      sprintf(text, "START");
      drawTileMenu(game->tileMenu,430,350,1, game);
      drawString(text, 460, 350, 255, 255, 255, game->fontMenu, game);
   } else if(game->choice == 1) {
      sprintf(text, "QUIT");
      drawTileMenu(game->tileMenu,430,450,1, game);
      drawString(text, 470, 450, 255, 255, 255, game->fontMenu, game);
   }

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

}
