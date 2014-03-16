#include "background.h"

void displayBackground(Game* game){

       game->background= SDL_LoadBMP("res/image/background/backgroundworld1.bmp");


        SDL_BlitSurface(game->background, NULL, game->screen, NULL);

}
