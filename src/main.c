/**
 * \file main.c
 * \brief Main function and main loop.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "game.h"

/**
 * \brief The main function initialize the game then runs the main loop of the game. When the game stops, the game is exit properly
 */
int main(int argc, char* argv[]) {

   Game game;

   /* Initialization of components of the game*/
   if (initGame(&game))
      return EXIT_FAILURE;

   /* Main Loop */
   while(game.status->gameIsRunning) {
      updateGame(&game);
      displayGame(&game);

      delayGame(&game);
   }
/*gerer fuites mémoires ici*/

   return EXIT_SUCCESS;
}
