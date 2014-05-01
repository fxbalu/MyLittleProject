/**
 * \file main.c
 * \brief Main program.
 *
 * \author Vincent WERNER
 * \author Gwendal HENRY
 * \author François-Xavier BALU
 */

#include "main.h"

/**
 * \brief Main function.
 * \param[in] argc  Number of argument passed to the program.
 * \param[in] argv  Arguments passed to the program.
 */
int main(int argc, char* argv[])
{

   unsigned int frameLimit;
   int go;

   frameLimit = SDL_GetTicks()+16;

   /* initializes SDL */
   init("MyLittleProject");

   /* initializes player */
   initializePlayer();

   /* loads resources */
   loadGame();

   /* calls cleanup function at program end */
   atexit(cleanup);

   go = 1;

   /* Main loop */
   while(go == 1)
   {
      /* reads input from keyboard */
      getInput();

      /* checks if menu is used */
      if(jeu.onMenu == 0)
      {
         /* updates game */
         updatePlayer();
         updateMonsters();
         updateObject();
      }
      else
      {
         if(jeu.menuType == START) updateStartMenu();
      }

      /* checks if menu is used (same test as the previous one) */
      if(jeu.onMenu == 0)
      {
         /* displays everything */
         draw();
      }
      else
      {
         if(jeu.menuType == START)
         {
            drawImage(map.backgroundMenu, 0, 0);
            /*displays menu*/
            drawStartMenu();
            SDL_Flip(jeu.screen);
            SDL_Delay(1);
         }

      }

      delay(frameLimit);                  /*on attends 16ms pour avoir un jeu tournant à max 60fps*/
      frameLimit = SDL_GetTicks()+16;
   }

   return EXIT_SUCCESS;
}

