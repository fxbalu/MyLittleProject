/**
 * \file character.c
 * \brief Functions used to manage the character.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "character.h"

/*utiliser parseur xml ???*/
void initCharacter (Character* player) {

   player->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   player->rectDst = (SDL_Rect*) malloc(sizeof(SDL_Rect));

   player->spriteCharacterSheet = loadImage("res/image/sprite/player/playerSpriteSheet.png");

   player->rectSrc->x = 0;
   player->rectSrc->y = 0;
   player->rectSrc->w = 72;/*definir des constantes !*/
   player->rectSrc->h = 97;

   player->rectDst->x = 500;
   player->rectDst->y = 300;

   player->state = idle;
   player->direction = right;
   player->frameCounter = 0;
   /*autres init plus tard*/
}


/*detecte les collisions, détermine la nouvelle position du perso*/
/*chande l'etat du perso, sa position etc*/
void updateCharacter (Character* player, Level* level, Input* input) {

   player->state = idle; //si pas d'appui, position : idle

   if(input->left.pressed) {
      player->direction = left;
      player->frameCounter = 0;
   }
   if(input->left.down) {
      player->state = run;
      player->frameCounter++;
   }
   if(input->up.pressed) {
      player->direction = up;
      player->frameCounter = 0;
   }
   if(input->up.down) {

   }
   if(input->right.pressed) {
      player->direction = right;
      player->frameCounter = 0;

   }
   if(input->right.down) {
      player->state = run;
      player->frameCounter++;
   }
   if(input->down.pressed) {
      player->direction = down;
      player->frameCounter = 0;
   }
   if(input->down.down) {

   }
   if(input->enter.pressed) {

   }
   if(input->enter.down) {

   }
   if(input->jump.pressed) {
      player->frameCounter = 0;
   }
   if(input->jump.down) {
      player->state = jump;
   }
   if(input->crouch.pressed) {

   }
   if(input->crouch.down) {
      player->state = crouch;
   }
   if(input->shoot.pressed) {

   }
   if(input->shoot.down) {

   }

}

void displayCharacter (Character* player, SDL_Surface* screen) {

   switch(player->state) {

   case idle :
      switch(player->direction) {
      case left :
         player->rectSrc->x = 0;
         player->rectSrc->y = 194;
         break;

      case up :
         player->rectSrc->x = 72;
         player->rectSrc->y = 194;
         break;

      case right :
         player->rectSrc->x = 144;
         player->rectSrc->y = 194;
         break;

      case down :
         player->rectSrc->x = 216;
         player->rectSrc->y = 194;
      }
      break;

   case walk :
      switch(player->direction) {
         if(player->frameCounter>7) {
            player->frameCounter = 0; //bouclage de l'animation
         }
      case left :
         player->rectSrc->x = player->frameCounter*72;
         player->rectSrc->y = 97;
         break;

      case right :
         player->rectSrc->x = player->frameCounter*72;
         player->rectSrc->y = 0;
         break;
      }
      break;

   case run :
      if(player->frameCounter>7) {
         player->frameCounter = 0; //bouclage de l'animation
      }
      switch(player->direction) {
      case left :
         player->rectSrc->x = player->frameCounter*72;
         player->rectSrc->y = 97;
         break;

      case right :
         player->rectSrc->x = player->frameCounter*72;
         player->rectSrc->y = 0;
      }
      break;

   case jump :
      switch(player->direction) {
         case left :
         player->rectSrc->x = 288;
         player->rectSrc->y = 194;
         break;
      case right :
         player->rectSrc->x = 360;
         player->rectSrc->y = 194;
         break;
      }
      break;

   case crouch :
      switch(player->direction) {
      case left :
         player->rectSrc->x = 432;
         player->rectSrc->y = 194;
         break;
      case right :
         player->rectSrc->x = 504;
         player->rectSrc->y = 194;
         break;

      default :
         player->rectSrc->x = 504;
         player->rectSrc->y = 194;
      }

      ;

   }

   SDL_BlitSurface(player->spriteCharacterSheet, player->rectSrc, screen, player->rectDst);
}
