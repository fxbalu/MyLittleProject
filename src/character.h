/*!
 * \file character.h
 * \brief structures and prototypes of functions used to manage the character
 * \author fx.balu & a.dufac & g.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#ifndef DEFINED_CHARACTER_H
#define DEFINED_CHARACTER_H

#include <SDL.h>

/*!
 * \struct Character
 * variables to manage the character
 */
typedef struct Character{
   SDL_Rect* position;
}Character;

#endif // DEFINED_CHARACTER_H
