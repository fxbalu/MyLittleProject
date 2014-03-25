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


/**
 * \struct Camera
 * Position of the camera in the current level.
 */
typedef struct Camera {
   int x;
   int y;
} Camera;

/**
 * \struct Level
 * Informations on the current level.
 */
typedef struct Level {
   SDL_Surface* background;
   SDL_Surface* tileset;
   SDL_Rect* rectSrc;
   SDL_Rect* rectDst;

   Camera* camera;
   /*ajouter la camera ici je pense*/
} Level;



void initLevel (Level* level);

void updateLevel (Level* level);

void displayLevel (Level* level, SDL_Surface* screen);

void displayBackground (Level* level, SDL_Surface* screen);

#endif
