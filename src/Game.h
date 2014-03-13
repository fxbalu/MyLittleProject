#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Define.h"

#include "GameStatus.h"
#include "Player.h"

/* Structure gérant tout le jeu*/
typedef struct Game {
   SDL_Surface* screen;

   GameStatus* status;

   Player* player;

} Game;


int gameInit(Game* game);
void gameDelay(Game* game);
void gameUpdate(Game* game);
void gameDisplay(Game* game);

#endif // GAME_H_INCLUDED
