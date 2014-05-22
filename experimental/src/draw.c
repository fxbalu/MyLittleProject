#include "draw.h"
#include "object.h"
#include "font.h"
#include "map.h"
#include "animation.h"


void drawTile(SDL_Surface *image, int destx,int desty,int srcx, int srcy, Game* game)
{

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



void drawImage(SDL_Surface* image,int x,int y, Game* game)
{


    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;


    SDL_BlitSurface(image,NULL,game->screen,&dest);

}


void drawHud(Game* game)
{

    char text[200];

    //drawImage(game->HUD_life,50,30, game);
   // sprintf(text, "%d",game->life);
    //drawString(text,135,19, 255, 255, 255,game->fontHUD, game);



    drawImage(game->HUD_coin,810,30, game);
    sprintf(text, "%.4d",game->coin);
    drawString(text,900,19, 255, 255, 255, game->fontHUD, game);
}

void drawString(char* text, int x, int y, int r,int b, int g, TTF_Font* font,Game* game)
{
    SDL_Rect dest;
    SDL_Surface * surface;
    SDL_Color foregroundColor;

    foregroundColor.r = r;
    foregroundColor.b = b;
    foregroundColor.g = g;

    surface = TTF_RenderUTF8_Blended(font,text,foregroundColor);

    if(surface == NULL)
    {
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


void draw(Game* game)
{

    drawImage(game->map->background, 0, 0,game);

    drawMap(game->map, game);

    drawObject(game);

    drawAnimatedEntity(game->player, game);

    drawHud(game);

    SDL_Flip(game->screen);

    /* Delai */

    SDL_Delay(1);

  }


SDL_Surface* loadImage(char *name){

    SDL_Surface* temp = IMG_Load(name);
    SDL_Surface* image;

    if(temp==NULL){
        printf("Failed to load image %s\n", name);

        return NULL;
    }

    SDL_SetColorKey(temp, SDL_RLEACCEL, temp->format->colorkey);

    image = SDL_DisplayFormatAlpha(temp);



    SDL_FreeSurface(temp);

    if (image == NULL)
    {
        printf("Failed to convert image %s to native format\n", name);

        return NULL;
    }

    /* Retourne l'image au format de l'écran pour accélérer son blit */

    return image;


}


void delay(unsigned int frameLimit)
{

    /* Gestion des 60 fps (images/stories/seconde) */

    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
  }
