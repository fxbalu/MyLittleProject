/**
 * \file animation.c
 * \brief this file contains necessary function to display animations
 *
 * Implementation of drawAnimatedEntity() and changeAnimation()
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#include "animation.h"
#include "draw.h"

/**
 * \fn void drawAnimatedEntity(GameObject* entity, Game* game)
 * \brief displays an animated object
 *
 * \param[in] entity: contains the sprite and other informations for the animation
 * \param[in] game: containins the necessary informations about the game
 *
 * This function manage the animation of an object, times the frames and
 *	displays the right part of the sprite each frame
 */
void drawAnimatedEntity(GameObject* entity, Game* game)
{
    // Gestion du timer

    // Si notre timer (un compte à rebours en fait) arrive à zéro

    if(entity->frameTimer <= 0)
    {
        entity->frameTimer = TIME_BETWEEN_2_FRAMES;

        entity->frameNumber ++;

        if(entity->frameNumber >= entity->sprite->w/entity->w) entity->frameNumber =0;

    }

    else entity->frameTimer --;

    SDL_Rect dest;

    dest.x = entity->x - game->map->startX;
    dest.y = entity->y - game->map->startY;
    dest.w = entity->w;
    dest.h = entity->h;

    SDL_Rect src;

    src.x = entity->frameNumber * entity->w;
    src.y = 0;
    src.h = entity->h;
    src.w = entity->w;

    SDL_BlitSurface(entity->sprite, &src, game->screen, &dest);
}

/**
 * \fn void changeAnimation(GameObject* entity, char* name)
 * \brief changes the animation for a given animated object
 *
 * \param[in] entity: 'GameObject' contains informations about the object
 * \param[in] name: 'char*' contains the name of the new sprite to load
 *
 *  This function changes the sprite loaded up in the 'GameObject' entity,
 *	allowing us to change the animation of an animated object
 */
void changeAnimation(GameObject* entity, char* name)
{
    if(entity->sprite != NULL) SDL_FreeSurface(entity->sprite);

    entity->sprite = loadImage(name);

    entity->frameNumber = 0;
    entity->frameTimer = TIME_BETWEEN_2_FRAMES;

}
