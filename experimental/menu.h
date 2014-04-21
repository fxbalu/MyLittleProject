#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "structs.h"

/* Structures globales */
extern Gestion jeu;
extern TTF_Font *font;
extern TTF_Font *fontMenu;
extern Input input;

extern void drawString(char *text, int x, int y, TTF_Font *font);
extern void changeLevel(void);
extern void initializePlayer(void);
extern void drawImage();




#endif
