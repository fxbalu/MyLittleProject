/**
 * \file input.h
 * \brief Prototypes of functions to get and process the user's input.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 18 mars 2014
 */


#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <SDL.h>
#include "common.h"
#include "GameOptions.h"

/*ok pour le nom ?*/
/**
 * \struct Control
 * \brief
 */
typedef struct Control {
   Boolean pressed;
   Boolean down; //revoir les noms
} Control;

/**
 * \struct Input
 * \brief
 */
typedef struct Input {
   SDL_Event* event;

   Control* left;
   Control* up; // pointeur sur control c'est bien non ?
   Control* right;
   Control* down;

   Control* enter; /*on peut appuyer sur plusieurs touches en meme temps, donc pas faire juste une enumeration*/
   Control* jump;/* note : les control sont des flags, ils sont a appliqur dans une fonction getinput, et en fonction de gameOptions*/
   Control* crouch;
   Control* shoot;

   Control* escape;
   Control* exit;
} Input;


/*void ou int pour gestion erreur */
void initInput(Input* input);

void clearInput(Input* input);

void clearInputPressed(Input* input);

void getInput(Input* input, GameOptions* options);

void freeInput(Input* input);

#endif
