#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "game.h"




void drawObjectTile(GameObject object, int k, Game* game);
void drawObject(Game* game);
int collideObject(GameObject* player,GameObject* object);
int collidePick(GameObject* player,GameObject* object);
void updateObject(Game* game);
void isSolid(GameObject *entity, GameObject *object);
void activateSwitch(int colorBlock, Game* game);
void desactivateSwitch(int colorBlock, Game* game);
void getItem(Game* game);
void destroyGameObject(GameObject* object);



#endif // OBJECT_H_INCLUDED
