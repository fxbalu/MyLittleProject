/*!
 * \file main.c
 * \brief fonction main et boucle principale
 * \author fx.balu & a.dufac & g.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "include.h"

int main(int argc, char* argv[]){

   Game game;

   /* Initialization of components of the game*/
   if (gameInit(&game))
      return EXIT_FAILURE;

   /* Main Loop */
   while(game.status->gameIsRunning){
      gameEvent(&game);
      gameDisplay(&game);
      //gameDelay(&game); ### a recoder, la fonction ne tourne pas :)
   }

   return EXIT_SUCCESS;
}
