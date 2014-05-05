#include "animation.h"
#include "draw.h"


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

void changeAnimation(GameObject* entity, char* name)
{
    if(entity->sprite != NULL) SDL_FreeSurface(entity->sprite);

    entity->sprite = loadImage(name);

    entity->frameNumber = 0;
    entity->frameTimer = TIME_BETWEEN_2_FRAMES;

}



