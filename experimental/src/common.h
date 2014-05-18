/**
 * \file common.h
 * \brief contains the needed includes and the defines of the parameters of the game
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "xml/xml.h"
#include "log.h"


#define SCREEN_WIDTH 1050
#define SCREEN_HEIGHT 700


#define TILE_SIZE 70

/* Taille du sprite de notre héros (largeur = width et hauteur = heigth) */
#define PLAYER_WIDTH 72
#define PLAYER_HEIGTH 97

// constantes pour l'annimation du hero

#define TIME_BETWEEN_2_FRAMES 1

#define PLAYER_SPEED 10

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


#define COIN 1
#define DOOR 2
#define BLUE_SWITCH 3
#define GREEN_SWITCH 4
#define YELLOW_SWITCH 5
#define RED_SWITCH 6
#define BLUE_BLOCK 7
#define GREEN_BLOCK 8
#define YELLOW_BLOCK 9
#define RED_BLOCK 10
#define PICK 11
#define ELEVATOR_BLOCK 12
#define ELEVATOR_SWITCH 13
#define FLY 300


// définissant le seuil entre les tiles traversables (blank) et les tiles solides
#define BLANK_TILE 77

//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED 1,5
#define MAX_FALL_SPEED 15
#define JUMP_HEIGHT 22

#define LEVEL_MAX 2


// enum pour les sounds

  enum
{
    DEADMINION,
    JUMPSOUND,
    COINSOUND,
    DEADPLAYER,
    SWITCHSOUND,
};

// enum pour le menu

  enum
 {
      START,
      PAUSE
  };



#endif
