/**
 * \file common.c
 * \brief Common functions.
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 12 mars 2014
 */


#include "common.h"
#include "log.h"


//premiere version on va test la vitesse des blits avec et sans
SDL_Surface* loadImage(char* file) {
   SDL_Surface* temp = IMG_Load(file);
   SDL_Surface* image = SDL_DisplayFormatAlpha(temp);

   if(temp == NULL){
      logError("erreur IMG_Load \n", __FILE__, __LINE__);
   }

   if(image == NULL){
      logError("erreur DisplayFormatAlpha", __FILE__, __LINE__);
   }
   free(temp);
   return image;
}
