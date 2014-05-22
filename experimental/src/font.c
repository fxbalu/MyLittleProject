/**
 * \file font.c
 * \brief contains the necessary functions to use a font with SDL_TTF
 *
 * Implementation of loadFont and closeFont
 * 
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#include "font.h"

/**
 * \fn TTF_Font* loadFont(char* name, int size)
 * \brief load a font
 *
 * \param[in] font: the TTF_Font to load.
 * \param[in] size: the size of the font to use.
 *
 * The function load a font into a TTF_Font structure, with the proper size.
 * If the loading fails, the function returns NULL.
 */
TTF_Font* loadFont(char* name, int size) {

   TTF_Font* font = TTF_OpenFont(name, size);

   if (font == NULL) {
      printf("Failed to open Font %s: %s\n", name, TTF_GetError());

      return NULL;
   }

   return font;
}

/**
 * \fn closeFont(TTF_Font *font)
 * \brief free the TTF_Font
 *
 * \param[in] font: the TTF_Font to free.
 *
 * The function free the TTF_Font
 */
void closeFont(TTF_Font *font) {

   if (font != NULL) {
      TTF_CloseFont(font);
   }
}

