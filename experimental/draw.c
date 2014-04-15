#include "draw.h"



void drawTile(SDL_Surface *image, int destx,int desty,int srcx, int srcy)
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

    SDL_BlitSurface(image,&src,jeu.screen,&dest);
}


void drawImage(SDL_Surface* image,int x,int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;


    SDL_BlitSurface(image,NULL,jeu.screen,&dest);
}


void drawHud(void)
{
    char text[200];

    drawImage(jeu.HUD_vie,50,30);
    sprintf(text, "%d",jeu.life);
    drawString(text,135,19,font);



    drawImage(jeu.HUD_etoiles,810,30);
    sprintf(text, "%.4d",jeu.etoiles);
    drawString(text,900,19,font);
}



 void draw(void)
  {
    int i;
    drawImage(map.background, 0, 0);

    drawMap();
    /* Affiche l'écran */



    drawAnimatedEntity(&player);



    /* Affiche les monstres */
    for(i = 0 ; i < jeu.nombreMonstres ; i++)
    {
        drawAnimatedEntity(&monster[i]);
    }

    drawHud();

    SDL_Flip(jeu.screen);


    /* Delai */

    SDL_Delay(1);

  }


SDL_Surface* loadImage(char *name)
{
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
