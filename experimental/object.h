#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "structs.h"


extern Map map;
extern Input input;
extern GameObject player;
extern Gestion jeu;

extern void getItem();
extern void endLevel();
extern void playerGameover();
extern void getInput();
extern void changeLevel();
extern void initializePlayer();
extern void playSoundFx(int type);
extern void isSolid(GameObject* entity,GameObject* object);
extern void activateSwitch(int colorBlock);
extern void desactivateSwitch(int colorBlock);

extern void drawTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy);
extern void initializeMonsters(int x, int y);

#endif // OBJECT_H_INCLUDED
