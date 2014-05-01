#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "structs.h"


extern Map map;
extern GameObject player;
extern Gestion jeu;

extern void getItem();
extern void drawTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy);
extern void initializeMonsters(int x, int y);

#endif // OBJECT_H_INCLUDED
