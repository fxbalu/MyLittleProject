/**
 * \file character.h
 * \brief structures and prototypes of functions used to manage the character
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef DEFINED_CHARACTER_H
#define DEFINED_CHARACTER_H

#include <SDL.h>
#include <SDL_image.h>
#include "common.h"
#include "level.h"

/**
 * \enum Direction
 * \brief Enumeration of the different directions possible of the character.
 */
typedef enum Direction {
   left,up, right,down
} Direction;


/**
 * \enum CharacterState
 * \brief Enumeration of the different states possible of the character.
 */
typedef enum CharacterState {
   idle, walk, run, jump, crouch
} CharacterState;

/*!
 * \struct Character
 * \brief Variables to manage the character.
 */
typedef struct Character {
   SDL_Surface* spriteCharacterSheet;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;

   int x; /*coordonnées du personnage ,om a changer peut etre*/
   int y;

   CharacterState state;
   Direction direction;
   int frameCounter;
} Character;

void initCharacter (Character* player);

void updateCharacter (Character* player, Level* level, Input* input);

void displayCharacter (Character* player, SDL_Surface* screen);

#endif
