#include "defs.h"



#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


typedef struct Input
{

int left,right,up,down,jump,use,enter,pause;

}Input;


typedef struct Gestion
{

SDL_Surface* screen;
SDL_Surface* tileMenu;


SDL_Surface* HUD_vie;
SDL_Surface* HUD_etoiles;
int etoiles;
int life;

Mix_Music* musique;

Mix_Chunk *miniondead_sound, *jump_sound, *coin_sound, *deadplayer1_sound, *switch_sound;

int nombreMonstres;

int objectNumber;

int onMenu, menuType, choice;


int level;


}Gestion;




/* Structure pour gérer notre héros */

typedef struct GameObject
{
   //Sprite de l'objet
   SDL_Surface *sprite;

   int type;
   int spe;

   int initialized;

   int gid;

   /* Coordonnées de l'objet */
   int x, y;

   int h,w;


   int frameNumber, frameTimer;

   int etat,direction;

   int onGround, timerMort;
   float dirX, dirY;

   int saveX, saveY;

} GameObject;

typedef struct Map
{

SDL_Surface *background;
SDL_Surface *tileSet;
SDL_Surface *backgroundMenu;

int startX, startY;
int maxX, maxY;
int sizeX,sizeY;

GameObject *objects;
int **tile;

} Map;


#endif // STRUCT_H_INCLUDED
