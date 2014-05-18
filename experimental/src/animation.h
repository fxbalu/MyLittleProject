/**
 * \file animation.h
 * \brief header of animation.c
 *
 *	Contains declarations of drawAnimatedEntity() and changeAnimation()
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */
 
#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include "game.h"

void drawAnimatedEntity(GameObject* entity, Game* game);
void changeAnimation(GameObject* entity, char* name);

#endif // ANIMATION_H_INCLUDED
