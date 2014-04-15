#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED




#include "structs.h"

/*Prototypes des fonctions utilisées*/

extern void init(char*);
extern void cleanup(void);
extern void getInput(void);
extern void draw(void);

extern void loadGame(void);
extern void delay(unsigned int frameLimit);
extern void updatePlayer(void);
extern void initializePlayer(void );

extern void updateMonsters(void);

/*déclaration des structures globales utilisées par le jeu*/

Input input;
Gestion jeu;
Map map;
GameObject player;
TTF_Font* font;
GameObject monster[MONSTRES_MAX];



#endif
