/**
 * \file font.c 
 * \brief contains the necessary functions to use a font with SDL_TTF
 *
 * Implementation of loadFont() and closeFont()
 *
 */

#include "font.h"

TTF_Font* loadFont(char* name, int size)
{

    TTF_Font* font = TTF_OpenFont(name, size);


    if (font == NULL)
    {
        printf("Failed to open Font %s: %s\n", name, TTF_GetError());

        exit(1);
    }

    return font;
}

void closeFont(TTF_Font *font)
{
    /* Ferme la police quand on n'en a plus besoin (avant de quitter) */

    if (font != NULL)
    {
        TTF_CloseFont(font);
    }
}

