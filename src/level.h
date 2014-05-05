/**
 * \file level.h
 * \brief Prototypes of functions that draw the level on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */


#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "common.h"
#include "define.h"
#include "input.h"
#include "xml/xml.h"

#define TILE_SIZE 70
#define TILESET_WIDTH 10

/**
 * \struct Camera
 * Position of the camera in the current level.
 */
typedef struct Camera {
   int x;
   int y;
} Camera;

typedef struct GameObject {
   char* name;
   int id; //identifiant de l'objet
   int x;//position de l'objet
   int y;
} GameObject;

/**
 * \struct Level
 * Informations on the current level.
 */
typedef struct Level {
   SDL_Surface* background;
   SDL_Surface* tileset;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;

   int sizeX; //nombre de tiles en largeur
   int sizeY; //nombre de tiles en hauteur

   char** tab; //nom a changer
   GameObject** objects; //tableau des objets

   Camera* camera;
   /*ajouter la camera ici je pense*/
} Level;



void initLevel (Level* level);

void updateLevel (Level* level, Input* input);

void displayLevel (Level* level, SDL_Surface* screen);

void selectTile (SDL_Rect* src, int gid) ;

void displayBackground (Level* level, SDL_Surface* screen);

void loadLevel (Level* level);

#endif
