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
   game->player->rectDst->w = 72;/*definir des constantes !*/
   game->player->rectDst->h = 97;

   game->player->state = idle;
   game->player->direction = right;
   /*autres init plus tard*/
}

/*detecte les collisions, détermine la nouvelle position du perso*/
void updateCharacter(Game* game) {
   /*a revoir*/
   if(game->input->left) {
      game->player->direction = left;
   }
   if(game->input->right) {
      game->player->direction = right;
   }
}

void displayCharacter(Game* game) {
   /*a revoir*/

   /*changement de sdl rect ici ( ajouter ca dans une autre fct ?*/
/*
   switch (game->player->direction) {
   case left :
      game->player->rectSrc->y=97;
      break;
   case right :
      game->player->rectSrc->y=0;

   }*/

   /*SDL_BlitSurface(game->player->spriteCharacterSheet, game->player->rectSrc, game->screen, game->player->rectDst);*/
   if (game->input->left){
         SDL_BlitSurface(game->player->spriteCharacterSheet, NULL, game->screen, NULL);
   }
}
