#include "object.h"


void initializeObject()
{

    int i;
    int k;
    int ysource, xsource;

    for(i=0; i<jeu.objectNumber; i++){

        switch(map.objects[i]->type){

            case COIN :

                if(map.objects[i]->initialized == 0){

                    k = map.objects[i]->gid -1;

                    /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                    par ligne, d'où le 10 */

                    ysource = k / 10 * TILE_SIZE;

                    /* Et son x */

                    xsource = k % 10 * TILE_SIZE;

                    /* Fonction qui blitte la bonne tile au bon endroit en tenant compte du scrolling*/

                    drawTile(map.tileSet, map.objects[i]->x - map.startX, map.objects[i]->y - map.startY, xsource, ysource);

                    }

                break;


            case DOOR :


                if(map.objects[i]->initialized == 0){

                    k = map.objects[i]->gid -1;

                    /* Calcul pour obtenir son y (pour un tileset de 10 tiles
                    par ligne, d'où le 10 */

                    ysource = k / 10 * TILE_SIZE;

                    /* Et son x */

                    xsource = k % 10 * TILE_SIZE;

                    /* Fonction qui blitte la bonne tile au bon endroit en tenant compte du scrolling*/

                    drawTile(map.tileSet, map.objects[i]->x - map.startX, map.objects[i]->y - map.startY, xsource, ysource);

                    }

                break;


            case FLY :

                if(map.objects[i]->initialized == 0){

                    initializeMonsters(map.objects[i]->x,map.objects[i]->y);
                    map.objects[i]->initialized =1;
                }

                break;

            default :

                break;

        }
    }
 }


int collideObject(GameObject* player,GameObject* object){


    if( (player->x >= object->x + TILE_SIZE)  ||
        (player->x + player->w <= object->x)   ||
        (player->y >= TILE_SIZE + object->y)  ||
        (player->y + player->h <= object->y))

    return 0;


    else return 1;
}

void updateObject(){

    int i;

    for(i=0; i<jeu.objectNumber; i++){

        switch (map.objects[i]->type){

            case COIN :

                if((collideObject(&player,map.objects[i]) == 1) && (map.objects[i]->initialized == 0))
                {
                getItem();
                map.objects[i]->initialized =1 ;
                }

                break;

            case DOOR :



                break;

            default :

                break;
        }
    }
}




