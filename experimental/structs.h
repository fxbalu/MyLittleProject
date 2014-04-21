#include "defs.h"



#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


typedef struct Input
{

int left,right,up,down,jump,attack,enter,erase,pause;

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

Mix_Chunk *miniondead_sound, *jump_sound, *coin_sound, *deadplayer1_sound;

int nombreMonstres;

int onMenu, menuType, choice;


int level;


}Gestion;

typedef struct Map
{

SDL_Surface *background;
SDL_Surface *tileSet;
SDL_Surface *backgroundMenu;

int startX, startY;
int maxX, maxY;

int tile[MAX_MAP_Y][MAX_MAP_X];

} Map;



/* Structure pour gérer notre héros */

typedef struct GameObject
{
   //Sprite du héros (pas d'animation pour l'instant)
   SDL_Surface *sprite;

   /* Coordonnées du héros */
   int x, y;

   int h,w;


   int frameNumber, frameTimer;

   int etat,direction;

   int onGround, timerMort;
   float dirX, dirY;

   int saveX, saveY;

} GameObject;



#endif // STRUCT_H_INCLUDED
