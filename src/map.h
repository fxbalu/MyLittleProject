#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "game.h"



void loadMap (char* name, Map* map, Game* game);
void mapCollision(GameObject *entity, Map *map, Game* game);
void drawMap(Map* map, Game* game);
void monsterCollisionToMap(GameObject* entity, Map* map);
Map* createMap();
void destroyMap(Map* map);


#endif
