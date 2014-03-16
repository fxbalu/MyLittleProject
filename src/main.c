/*!
 * \file main.c
 * \brief main function and main loop
 * \author fx.balu & a.dufac & g.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "common.h"
#include "game.h"

int main(int argc, char* argv[]){

   Game game;

   /* Initialization of components of the game*/
   if (gameInit(&game))
      return EXIT_FAILURE;

   /* Main Loop */
   while(game.status->gameIsRunning){
      gameEvent(&game);
      gameUpdate(&game);
      gameDisplay(&game);

      gameDelay(&game);
   }

   return EXIT_SUCCESS;
}
