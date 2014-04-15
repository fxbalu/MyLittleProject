#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED




#include "structs.h"

extern SDL_Surface* loadImage(char* name);
extern void loadMap(char* name);
extern void closeFont(TTF_Font *font);
extern TTF_Font *loadFont(char *, int);
extern void changeLevel(void);


extern void loadSound(void);
extern void freeSound(void);

extern Gestion jeu;
extern Map map;
extern TTF_Font *font;
extern GameObject player;
extern GameObject monster[MONSTRES_MAX];
extern void loadSong( char filename[200]);

#endif // INIT_H_INCLUDED
