/**
 * \file gameOptions.h
 * \brief Prototypes of functions used in to handle all of the game's options.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

 #ifndef GAMEOPTIONS_H_INCLUDED
#define GAMEOPTIONS_H_INCLUDED

#include "define.h"
#include "common.h"

/**
 * \struct GameOptions
 * \brief Represent the options of the game, selected by the player in the options menu.
 */
typedef struct GameOptions {
   Boolean fullscreen;
   int windowWidth;
   int windowHeight;

   int controlerDown;
   int controlerUp;

   int left;   /*Garde en mémoire les préférences de commandes de l'utilisateur*/
   int up;
   int right;
   int down;

   int enter;
   int jump;
   int crouch;
   int shoot;

   int escape;
   int exit;
} GameOptions;

void initGameOptions(GameOptions* options);

#endif
