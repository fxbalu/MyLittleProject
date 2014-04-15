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

    getInput();     /*On vérifie les entrées*/

    updatePlayer();
    updateMonsters();

    draw();         /*On affiche tout*/

    delay(frameLimit);                  /*on attends 16ms pour avoir un jeu tournant à max 60fps*/
    frameLimit = SDL_GetTicks()+16;
}

exit(0);

}

