/**
 * \file common.c
 * \brief Common functions.
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 12 mars 2014
 */


#include "common.h"


//premiere version on va test la vitesse des blits avec et sans
SDL_Surface* loadImage(char* file) {
   SDL_Surface* temp = IMG_Load(file);
   SDL_Surface* image = SDL_DisplayFormatAlpha(temp);

   if(image == NULL){
      logError("erreur fonction loadImage", __FILE__, __LINE__);
   }
   free(temp);
   return image;
}
