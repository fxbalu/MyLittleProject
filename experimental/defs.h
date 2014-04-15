#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#define SCREEN_WIDTH 1050
#define SCREEN_HEIGHT 700

#define MAX_MAP_X 1000
#define MAX_MAP_Y 100

#define TILE_SIZE 70

/* Taille du sprite de notre héros (largeur = width et hauteur = heigth) */
#define PLAYER_WIDTH 72
#define PLAYER_HEIGTH 97

#define TIME_BETWEEN_2_FRAMES 2

#define PLAYER_SPEED 5

//Valeurs attribuées aux états/directions
#define WALK_RIGHT 1
#define WALK_LEFT 2
#define IDLE 3
#define JUMP_RIGHT 4
#define JUMP_LEFT 5
#define RIGHT 1
#define LEFT 2
#define DEAD 6
#define ALIVE 7

 // définissant le seuil entre les tiles traversables (blank) et les tiles solides
#define BLANK_TILE 78
#define TILE_MONSTER1 300
#define TILE_COIN 15
#define TILE_DOOR 44

//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED 1,5
#define MAX_FALL_SPEED 15
#define JUMP_HEIGHT 22

#define MONSTRES_MAX 50
#define LEVEL_MAX 2




  enum
{
    DEADMINION,
    JUMP,
    COIN,
    DEADPLAYER
};




#endif
