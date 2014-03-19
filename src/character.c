/**
 * \file character.c
 * \brief Functions used to manage the character.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "character.h"

/*utiliser parseur xml ???*/
void initCharacter (Game* game) {

   game->player = (Character*) malloc(sizeof(Character*));
   game->player->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   game->player->rectDst = (SDL_Rect*) malloc(sizeof(SDL_Rect));

   game->player->spriteCharacterSheet = IMG_Load("res/image/sprite/playerSpriteSheet.png");

   game->player->rectSrc->x = 0;
   game->player->rectSrc->y = 0;
   game->player->rectSrc->w = 72;/*definir des constantes !*/
   game->player->rectSrc->h = 97;

   game->player->rectDst->x = 0;
   game->player->rectDst->y = 0;

   game->player->state = idle;
   game->player->direction = right;
   /*autres init plus tard*/
}

/*detecte les collisions, détermine la nouvelle position du perso*/
/*chande l'etat du perso etc*/
void updateCharacter(Game* game) {
   /*a revoir*/
   if(game->input->left) {
      game->player->direction = left;
      game->player->state=walk;
   }
   if(game->input->right) {
      game->player->direction = right;
      game->player->state=walk;
   }
   if(game->input->jump) {
      game->player->state=jump;
   }
   if(!game->input->right && ! game->input->left) {
      game->player->state=idle;
   }
}

void displayCharacter(Game* game) {
   /*a revoir*/
   /*refaire le sprite aussi*/
   /*changement de sdl rect ici ( ajouter ca dans une autre fct selectSprite charach?*/

   switch (game->player->state) {
   case idle :
      game->player->rectSrc->x=0;   /*rajouter une direction*/
      game->player->rectSrc->y=97*3;
      break;

   case walk :
      switch (game->player->direction) {
      case left :
         game->player->rectSrc->x = 0;
         game->player->rectSrc->y = 97;
         break;
      case right :
         game->player->rectSrc->x = 0;
         game->player->rectSrc->y = 0;
      }
      break;

   case run : /*pas encore gérer*/
      break;

   case jump :
      game->player->rectSrc->x=0;
      game->player->rectSrc->y=97*2;/*rajouter une direction de saut*/
   }

   /*WTFFF! peut etre parce que dans le prortype c'est mis const ?*/
   game->player->rectSrc->w = 72;/*definir des constantes !*/
   game->player->rectSrc->h = 97;

   /*
   game->player->rectSrc->x = 0;
   game->player->rectSrc->y = 0;
   game->player->rectSrc->w = 72;//si je ne note pas tout le rectangle ca ne marche pas Dafuk ?
   game->player->rectSrc->h = 97;*/

   SDL_BlitSurface(game->player->spriteCharacterSheet, game->player->rectSrc, game->screen, game->player->rectDst);
}
