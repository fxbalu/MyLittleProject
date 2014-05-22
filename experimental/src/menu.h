#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "game.h"


void updateStartMenu(Input* input, Game* game);
void updateSelectLevelMenu(Input* input, Game* game);

void drawTileMenu(SDL_Surface *image,int x, int y , int frameNumber, Game* game);
void drawStartMenu(Game* game);
void drawSelectLevelMenu(Game* game);
void drawTileSelectLevel(Game* game, int x, int y, int selected);

#endif
