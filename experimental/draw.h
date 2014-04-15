#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED




#include "structs.h"

extern void drawMap(void);
extern void drawAnimatedEntity(GameObject* entity);
extern void drawHud(void);
extern void drawString(char *text, int x, int y, TTF_Font *font);

extern Gestion jeu;
extern Map map;
extern TTF_Font *font;
extern GameObject player;
extern GameObject monster[];


#endif
