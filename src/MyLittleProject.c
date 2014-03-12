/*
 ============================================================================
 Name        : My.c
 Author      : Dream Team
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "MyLittleProject.h"


int main(int argc, char **argv) {

	/*Initialisation SDL*/
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Unable to initialize SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	atexit(SDL_Quit);

	SDL_Surface* window = SDL_SetVideoMode(640, 448, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

	if(window == NULL){
		fprintf(stderr, "Unable to create the window : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	GameStatus status;
	initGameStatus(&status);

	SDL_Surface* picture = SDL_LoadBMP("icon.bmp");
	SDL_Rect dstrect;
	dstrect.x=dstrect.y=0;

	/*Variables for the FPS*/
	Uint32 nextTick, sleepTime;
	nextTick = SDL_GetTicks();
	/*Main Loop*/
	while(status.gameIsRunning){

		/*
		 * updateGame()
		 * displayGame()
		 */
		dstrect.x++;
		dstrect.y++;
		SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 255, 255, 255));
		SDL_BlitSurface(picture, NULL, window, &dstrect);
		SDL_Flip(window);
		/***/

		nextTick += SKIP_TICKS;
		sleepTime = nextTick - SDL_GetTicks();

		if(sleepTime>=0){
			SDL_Delay(sleepTime);
		}

		/*
		while(sleepTime >=0) {
			sleepTime = nextTick - SDL_GetTicks();
		}*/


	}


	return EXIT_SUCCESS;
}
