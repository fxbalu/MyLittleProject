#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "game.h"



void initializePlayer(GameObject *player);
void updatePlayer(GameObject *player, Game *game);
void centerScrollingOnPlayer(GameObject* player, Map* map);
void playerGameover(Game* game);
void endLevel(Game* game);
GameObject* createPlayer();
void destroyPlayer(GameObject* player);




#endif // PLAYER_H_INCLUDED
