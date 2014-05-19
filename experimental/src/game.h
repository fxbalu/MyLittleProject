/**
 * \file game.h
 * \brief header of game.c
 *
 * Declaration of createGame_(), loadGame(), initGame() and destroyGame().
 * Creation of structures Input, GameObject, Map and Game.
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED
#include "common.h"


typedef struct Input{

    int left,right,up,down,jump,use,enter,pause;

}Input;


typedef struct GameObject{
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


typedef struct Map{

    SDL_Surface *background;
    SDL_Surface *tileSet;
    SDL_Surface *backgroundMenu;

    XML_File* xmlLevel;

    int startX, startY;
    int maxX, maxY;
    int sizeX,sizeY;

    GameObject *objects;
    int **tile;

} Map;


typedef struct Game{

    SDL_Surface* screen;
    SDL_Surface* tileMenu;
    SDL_Surface* gameover;
    SDL_Surface* endLevel;
    SDL_Surface* HUD_life;
    SDL_Surface* HUD_coin;

    int coin;
    int life;

    Mix_Music* music;
    Mix_Chunk *miniondead_sound, *jump_sound, *coin_sound, *deadplayer1_sound, *switch_sound;

    int monsterinitialized;
    int objectNumber;
    int onMenu, menuType, choice;
    int level;
    int go;

    Map *map;
    GameObject* player;
    Input *input;
    TTF_Font *fontMenu;
    TTF_Font *fontGameover;
    TTF_Font *fontHUD;

}Game;


void initGame(char *title,Game* game);
void loadGame(Game* game);
void destroyGame(Game* game);
Game* createGame();



#endif // INIT_H_INCLUDED
