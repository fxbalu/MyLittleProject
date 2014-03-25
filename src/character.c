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

    player->rectDst->x = 0;
    player->rectDst->y = 0;

    player->state = idle;
    player->direction = right;
    /*autres init plus tard*/
}


/*detecte les collisions, détermine la nouvelle position du perso*/
/*chande l'etat du perso, sa position etc*/
void updateCharacter (Character* player, Level* level) {

}

void displayCharacter (Character* player, SDL_Surface* screen) {
    /*a revoir*/
    /*refaire le sprite aussi*/
    /*changement de sdl rect ici ( ajouter ca dans une autre fct selectSprite charach?*/

    SDL_BlitSurface(player->spriteCharacterSheet, player->rectSrc, screen, player->rectDst);
}
