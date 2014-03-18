/**
 * \file character.c
 * \brief Functions used to manage the character.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "character.h"

void initCharacter (Game* game) {

   game->player = (Character*) malloc(sizeof(Character*));
   game->player->spriteCharacterSheet = IMG_Load("res/image/sprite/playerSpriteSheet.png");
   /*autres init plus tard*/
}

/*detecte les collisions, détermine la nouvelle position du perso*/
void updateCharacter(Game* game){

}

void displayCharacter(Game* game) {
   /*a revoir*/
   SDL_BlitSurface(game->player->spriteCharacterSheet, NULL, game->screen, NULL);
}
