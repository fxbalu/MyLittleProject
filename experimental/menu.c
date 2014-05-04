#include "menu.h"

void updateStartMenu(void)
{
    if(input.down == 1)
    {
            //Si choice = O (il est sur start), on le met à 1 (quit)
        if(jeu.choice == 0)
            jeu.choice++;

        input.down = 0;
    }

        //Si on appuie sur HAUT
    if(input.up == 1)
    {
            //Si choice = 1 (il est sur Quit), on le met à 0 (Start)
        if(jeu.choice == 1)
            jeu.choice--;

        input.up = 0;
    }

        //Si on appuie sur Enter et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
    if(input.enter)
    {
        if(jeu.choice == 0)
        {
            initializePlayer();
            jeu.onMenu = 0;
        }
        //Sinon, on quitte le jeu
        else if(jeu.choice == 1)
        {
            exit(0);
        }
         input.enter = 0;
    }

}

void drawTileMenu(SDL_Surface *image,int x, int y , int frameNumber)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = image->w;
    dest.h = image->h;

    SDL_Rect src;

    src.x = frameNumber * 190;
    src.y = 0;
    src.h = image->h;
    src.w = 190;

    SDL_BlitSurface(image, &src, jeu.screen, &dest);
}



void drawStartMenu(void)
{

    //On crée une varuiable qui contiendra notre texte
    char text[200];

    //Si l'option n'est pas en surbrillance, on l'affiche normalement, sinon on rajoute ">"
    if(jeu.choice != 0)
    {
        sprintf(text, "START");
        drawTileMenu(jeu.tileMenu,430,350,0);
        drawString(text, 460, 350, 255, 255, 255, fontMenu);
    }
    if(jeu.choice != 1)
    {
        sprintf(text, "QUIT");
        drawTileMenu(jeu.tileMenu,430,450,0);
        drawString(text, 470, 450, 255, 255, 255,fontMenu);
    }


    if(jeu.choice == 0)
    {
        sprintf(text, "START");
        drawTileMenu(jeu.tileMenu,430,350,1);
        drawString(text, 460, 350, 255, 255, 255, fontMenu);
    }
    else if(jeu.choice == 1)
    {
        sprintf(text, "QUIT");
        drawTileMenu(jeu.tileMenu,430,450,1);
        drawString(text, 470, 450, 255, 255, 255, fontMenu);
    }

}
