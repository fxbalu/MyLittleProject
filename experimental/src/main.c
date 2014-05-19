/**
 * \file main.c
 * \brief Main program.
 *
 * \author Vincent WERNER
 * \author Gwendal HENRY
 * \author François-Xavier BALU
 */

#include "common.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "object.h"
#include "menu.h"
#include "draw.h"

/**
 * \fn int main(int argc, char* argv[])
 * \brief Main function.
 * \param[in] argc  Number of argument passed to the program.
 * \param[in] argv  Arguments passed to the program.
 */
int main(int argc, char* argv[]) {

   unsigned int frameLimit;

   /*Create the Game structure*/
   Game* game = createGame();

   frameLimit = SDL_GetTicks()+16;

   /* initializes SDL */
   initGame("MyLittleProject",game);

   /* initializes player */
   initializePlayer(game->player);

   /* loads resources */
   loadGame(game);

   /* Main loop */
   while(game->go == 1) {
      /* reads input from keyboard */
      getInput(game->input, game);

      /* checks if menu is used */
      if(game->onMenu == 0) {
         /* updates game */
         updatePlayer(game->player,game);
         updateObject(game);
      } else {
         if(game->menuType == START) updateStartMenu(game->input,game);
      }


      /* checks if menu is used (same test as the previous one) */
      if(game->onMenu == 0) {
         /* displays everything */
         draw(game);
      } else {

         if(game->menuType == START)  drawStartMenu(game); // ya un bug ici !
      }

      /*set the framerate at 60 FPS*/
      delay(frameLimit);
      frameLimit = SDL_GetTicks()+16;
   }

   /*free everything*/
   destroyGame(game);

   return EXIT_SUCCESS;
}

