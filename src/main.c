/**
 * \file main.c
 * \brief Main function and main loop.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "game.h"

/**
 * \brief The main function initialize the game then runs the main loop of the game.
 * When the game stops, the game is exit properly
 */
int main(int argc, char* argv[]) {

   Game game;

   /* Initialization of components of the game*/
   if (initGame(&game)) {
      logError("Useful message.", __FILE__, __LINE__);
      return EXIT_FAILURE;
   }

   /* Main Loop */
   while(game.status->gameIsRunning) {

      printf("%d before update\n", SDL_GetTicks()); // verif des timings + des fps
      updateGame(&game);
      printf("%d before display\n", SDL_GetTicks());
      displayGame(&game);
      printf("%d before delay\n\n", SDL_GetTicks());
      delayGame(&game);

      //printInput(game.input);
   }
   //Gerer fuites mémoires ici

   return EXIT_SUCCESS;
}
