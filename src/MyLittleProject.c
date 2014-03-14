#include "MyLittleProject.h"


int main(int argc, char **argv) {

   Game game;

   if (gameInit(&game) == -1) {
      return EXIT_FAILURE;
   }

   /*Main Loop*/
   while(game.status->gameIsRunning) {

      gameUpdate(&game);
      gameDisplay(&game);


      gameDelay(&game);
   }

   return EXIT_SUCCESS;
}
