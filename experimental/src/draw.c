/**
 * \file draw.c
 * \brief contains all the drawing functions
 *
 * Implementation of every functions used to display images are implemented here :
 * drawTile, drawImage, drawHud, drawString, draw, loadImage, delay.
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#include "draw.h"
#include "object.h"
#include "font.h"
#include "map.h"
#include "animation.h"

/**
 * \fn void drawTile(SDL_Surface *image, int destx,int desty,int srcx, int srcy, Game* game)
 * \brief displays a tile from the given tileset to the given destination
 *
 * \param[in] image: the tileset
 * \param[in] srcx: x-axis coordinate of the tile on the tileset
 * \param[in] srcy: y-axis coordinate of the tile on the tileset
 * \param[in] destx: x-axis coordinate of the place of the tiles on the screen
 * \param[in] desty: y-axis coordinate of the place of the tiles on the screen
 * \param[in] game: contains the necessary informations for the displaying (screen pointers)
 *
 */
void drawTile(SDL_Surface *image, int destx,int desty,int srcx, int srcy, Game* game) {
   SDL_Rect dest;

   dest.x = destx;
   dest.y = desty;
   dest.w = TILE_SIZE;
   dest.h = TILE_SIZE;

   SDL_Rect src;

   src.x = srcx ;
   src.y = srcy ;
   src.w = TILE_SIZE;
   src.h = TILE_SIZE;

   SDL_BlitSurface(image,&src,game->screen,&dest);
}

/**
 * \fn void drawImage(SDL_Surface* image,int x,int y, Game* game)
 * \brief displays an image to the given coordinates on the screen
 *
 * \param[in] image: the image to display
 * \param[in] x: x-axis coordinate of the image on the screen
 * \param[in] y: y-axis coordinate of the image on the screen
 * \param[in] game: contains the necessary informations for the displaying (screen pointers)
 *
 * This functions simplifies the use of SDL_BlitSurface by automatically giving it the needed parameters
 *
 */
void drawImage(SDL_Surface* image,int x,int y, Game* game) {

   SDL_Rect dest;

   dest.x = x;
   dest.y = y;
   dest.w = image->w;
   dest.h = image->h;

   SDL_BlitSurface(image,NULL,game->screen,&dest);
}

/**
 * \fn void drawHud(Game* game)
 * \brief displays the Head-up display with the needed informations for the player
 *
 * \param[in] game: needed informations to display on the HUD and the screen pointers
 *
 * This function take the informations from the Game structure and displays them on the HUD:
 * Life, number of coins
 *
 */
void drawHud(Game* game) {

   char text[200];

   drawImage(game->HUD_life,50,30, game);
   sprintf(text, "%d",game->life);
   drawString(text,135,19, 255, 255, 255,game->fontHUD, game);


   drawImage(game->HUD_coin,810,30, game);
   sprintf(text, "%.4d",game->coin);
   drawString(text,900,19, 255, 255, 255, game->fontHUD, game);
}

/**
 * \fn drawString(char* text, int x, int y, int r,int b, int g, TTF_Font* font,Game* game)
 * \brief
 *
 * \param[in] text:
 * \param[in] x:
 * \param[in] y:
 * \param[in] r:
 * \param[in] v:
 * \param[in] b:
 * \param[in] g:
 * \param[in] font:
 * \param[in] game:
 *
 */
void drawString(char* text, int x, int y, int r,int b, int g, TTF_Font* font,Game* game) {
   SDL_Rect dest;
   SDL_Surface * surface;
   SDL_Color foregroundColor;

   foregroundColor.r = r;
   foregroundColor.b = b;
   foregroundColor.g = g;

   surface = TTF_RenderUTF8_Blended(font,text,foregroundColor);

   if(surface == NULL) {
      printf("Couldn't create String %s: %s\n", text, SDL_GetError());

      return;
   }

   dest.x = x;
   dest.y = y;
   dest.w = surface->w;
   dest.h = surface->h;

   SDL_BlitSurface(surface, NULL, game->screen,&dest);

   SDL_FreeSurface(surface);
}

/**
 * \fn void draw(Game* game)
 * \brief
 *
 * \param[in] game:
 *
 */
void draw(Game* game) {

   drawImage(game->map->background, 0, 0,game);

   drawMap(game->map, game);

   drawObject(game);

   drawAnimatedEntity(game->player, game);

   drawHud(game);

   SDL_Flip(game->screen);

   /* Delai */

   SDL_Delay(1); // wtf ????

}

/**
 * \fn SDL_Surface* loadImage(char *name)
 * \brief load into memory a picture
 *
 * \param[in] name: name of the picture to load.
 *
 * This function load into memory a picture and convert it to the right color format
 * (set when initializing the SDL_image screen).
 * With this conversion, the display of the picture will be much faster.
 *
 * If the loading fails, the function returns NULL.
 */
SDL_Surface* loadImage(char *name) {

   SDL_Surface* temp = IMG_Load(name);
   SDL_Surface* image;

   if(temp==NULL) {
      printf("Failed to load image %s\n", name);

      return NULL;
   }

   SDL_SetColorKey(temp, SDL_RLEACCEL, temp->format->colorkey);

   image = SDL_DisplayFormatAlpha(temp);

   SDL_FreeSurface(temp);

   if (image == NULL) {
      printf("Failed to convert image %s to native format\n", name);

      return NULL;
   }

   return image;
}

/**
 * \fn void delay(unsigned int frameLimit)
 * \brief set the framerate at 60 frames per second.
 *
 * \param[in] framelimit:
 *
 * This function waits a certain time to set the framerate at 60 frames per second and reduce the CPU consumption.
 *
 */
void delay(unsigned int frameLimit) {

   unsigned int ticks = SDL_GetTicks();

   if (frameLimit < ticks) {
      return;
   }

   if (frameLimit > ticks + 16) {
      SDL_Delay(16);
   }

   else {
      SDL_Delay(frameLimit - ticks);
   }
}
