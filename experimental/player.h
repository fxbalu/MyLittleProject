#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include "structs.h"

extern Gestion jeu;
extern GameObject player;
extern Input input;
extern Map map;
extern TTF_Font *font;
extern TTF_Font* fontGameover;



/* Prototype des fonctions externes que nous allons utiliser ensuite */
extern SDL_Surface *loadImage(char *name);
extern void centerScrollingOnPlayer(void);
extern void loadSong();
extern void getInput();
extern void drawString(char *text, int x, int y, int r, int b, int g, TTF_Font *font);


extern void mapCollision(GameObject *entity);
extern void loadMap(char *name);
extern void changeAnimation(GameObject* entity,char* name);
extern void playSoundFx(int type);
extern void changeLevel(void);
extern void drawString();
extern void loadGame();
extern void drawImage();

#endif // PLAYER_H_INCLUDED
