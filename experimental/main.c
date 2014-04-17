#include "main.h"

int main(int argc, char *argv[])
{
unsigned int frameLimit = SDL_GetTicks()+16;
int go;

init("MyLittleProject");       /*Initialisation de la SDL dans une fonction séparée*/


initializePlayer();

loadGame(); /* Chargement des ressources (graphismes, sons) */
atexit(cleanup);    /* Appelle la fonction cleanup à la fin du programme */

go=1;

while(go==1)        /*Boucle infinie*/
{

    getInput();

    if(jeu.onMenu == 0)
    {
        /* On met à jour le jeu */
        updatePlayer();
        updateMonsters();
    }
    else
    {
        if(jeu.menuType == START) updateStartMenu();
    }


    //Si on n'est pas dans un menu
    if(jeu.onMenu == 0)
    {
        /* On affiche tout */
        draw();
    }
    else
    {
        if(jeu.menuType == START)
        {
            drawImage(map.background, 0, 0);
            drawStartMenu();
            SDL_Flip(jeu.screen);
            SDL_Delay(1);
        }

    }      /*On affiche tout*/

    delay(frameLimit);                  /*on attends 16ms pour avoir un jeu tournant à max 60fps*/
    frameLimit = SDL_GetTicks()+16;
}

exit(0);

}

