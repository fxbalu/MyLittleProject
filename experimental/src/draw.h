/**
 * \file draw.c
 * \brief header of draw.c
 *
 * Contains declarations of:
 * drawTile(), drawImage(), drawHud(), drawString(), draw(), loadImage(), delay()
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "game.h"

void drawTile(SDL_Surface *image, int destx,int desty,int srcx, int srcy, Game* game);
void drawImage(SDL_Surface* image,int x,int y, Game* game);
void drawHud(Game* game);
void draw(Game* game);
SDL_Surface* loadImage(char *name);
void delay(unsigned int frameLimit);
void drawString(char* text, int x, int y, int r,int b, int g, TTF_Font* font, Game* game);

#endif
