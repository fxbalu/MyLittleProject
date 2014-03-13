#include "MyLittleProject.h"


int main(int argc, char **argv) {

   GameStatus status;
   initGameStatus(&status);

   /*Initialisation SDL*/
   if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      fprintf(stderr, "Unable to initialize SDL : %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }

   atexit(SDL_Quit);

   /*Creation de la fenetre */
   SDL_Surface* window = SDL_SetVideoMode(status.options->windowWidth, status.options->windowHeight, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

   if(window == NULL) {
      fprintf(stderr, "Unable to create the window : %s\n", SDL_GetError());
      return EXIT_FAILURE;
   }



   /*Variables for the FPS*/
   Uint32 nextTick, sleepTime;
   nextTick = SDL_GetTicks();

   /*Main Loop*/
   while(status.gameIsRunning) {

      /*
       updateGame(&window, &status)
       updateGameStatus()
       displayGame()
       */

      nextTick += SKIP_TICKS;
      sleepTime = nextTick - SDL_GetTicks();

      if(sleepTime>=0) {
         SDL_Delay(sleepTime); /*Pas terrible le sdl delay*/
      }

   }


   return EXIT_SUCCESS;
}
