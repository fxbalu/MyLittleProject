#include "object.h"



void drawObject(GameObject object, int k){


    int ysource, xsource;

    /* Calcul pour obtenir son y (pour un tileset de 10 tiles
    par ligne, d'où le 10 */

    ysource = (object.gid + k) / 10 * TILE_SIZE;

    /* Et son x */

    xsource = (object.gid + k) % 10 * TILE_SIZE;

    /* Fonction qui blitte la bonne tile au bon endroit en tenant compte du scrolling*/

    drawTile(map.tileSet, object.x - map.startX, object.y - map.startY, xsource, ysource);

}

void initializeObject(){

    int i;

    for(i=0; i<jeu.objectNumber; i++){

        switch(map.objects[i].type){

            case COIN :

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );


                break;


            case DOOR :


                if(map.objects[i].initialized == 0)  drawObject( map.objects[i], -1 );



                break;


            case GREEN_BLOCK :

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );


                break;

            case RED_BLOCK :

                if(map.objects[i].initialized == 1) drawObject( map.objects[i], -1 );

                break;

            case YELLOW_BLOCK :

                if(map.objects[i].initialized == 0)  drawObject( map.objects[i], -1 );

                break;

            case BLUE_BLOCK :

                if(map.objects[i].initialized == 0)  drawObject( map.objects[i], -1 );

                break;

            case GREEN_SWITCH :

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );

                if(map.objects[i].initialized == 1) drawObject( map.objects[i], 0 );

                break;

            case RED_SWITCH :

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );

                if(map.objects[i].initialized == 1) drawObject( map.objects[i], 0 );

                break;

            case YELLOW_SWITCH :

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );

                if(map.objects[i].initialized == 1) drawObject( map.objects[i], 0 );

                break;

            case BLUE_SWITCH :

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );

                if(map.objects[i].initialized == 1) drawObject( map.objects[i], 0 );

                break;



            case PICK :

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );

                break;

            case ELEVATOR_BLOCK:

                if(map.objects[i].initialized == 1) drawObject( map.objects[i], -1 );

                break;

            case ELEVATOR_SWITCH:

                if(map.objects[i].initialized == 0) drawObject( map.objects[i], -1 );

                 if(map.objects[i].initialized == 1) drawObject( map.objects[i], -3 );

                break;

            case FLY :

                if(map.objects[i].initialized == 0){

                    initializeMonsters(map.objects[i].x,map.objects[i].y);
                    map.objects[i].initialized =1;
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


int collidePick(GameObject* player,GameObject* object){


    if( (player->x >= object->x + TILE_SIZE - 20)  ||
        (player->x + player->w <= object->x + 20)   ||
        (player->y >= TILE_SIZE + object->y - 40)  ||
        (player->y + player->h <= object->y + 40))

    return 0;


    else return 1;
}


void updateObject(){

    int i;

    for(i=0; i<jeu.objectNumber; i++){

        switch (map.objects[i].type){

            case COIN :

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0))
                {
                    getItem();
                    map.objects[i].initialized =1 ;
                }

                break;

            case DOOR :

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0)){

                    jeu.level++;

                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;

                    }

                    else
                    {
                        endLevel();
                        initializePlayer();
                    }
                }
                break;


            case BLUE_BLOCK :

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0)){
                    isSolid(&player,&map.objects[i]);
                }

                break;

            case GREEN_BLOCK :

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0)){
                    isSolid(&player,&map.objects[i]);
                }

                break;

            case YELLOW_BLOCK :


                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0)){
                    isSolid(&player,&map.objects[i]);
                }

                break;

            case RED_BLOCK :

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 1)){
                    isSolid(&player,&map.objects[i]);
                }

                break;

            case PICK :

                if((collidePick(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0)){
                    if(jeu.life > 0)
                    {
                        jeu.life--;
                        player.timerMort = 1;
                        if(jeu.life<1) playerGameover();
                    }
                }

                break;

            case ELEVATOR_BLOCK :


                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 1)){
                    isSolid(&player,&map.objects[i]);
                }


                break;

            case ELEVATOR_SWITCH :


                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0) && (input.use == 1)){
                    activateSwitch(ELEVATOR_BLOCK);
                    map.objects[i].initialized = 1;
                    input.use =0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 1) && (input.use == 1)){
                    desactivateSwitch(ELEVATOR_BLOCK);
                    map.objects[i].initialized = 0;
                    input.use = 0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                break;

            case BLUE_SWITCH :

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0) && (input.use == 1)){
                    activateSwitch(BLUE_BLOCK);
                    map.objects[i].initialized = 1;
                    input.use =0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 1) && (input.use == 1)){
                    desactivateSwitch(BLUE_BLOCK);
                    map.objects[i].initialized = 0;
                    input.use = 0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                break;



            case GREEN_SWITCH :

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0) && (input.use == 1)){
                    activateSwitch(GREEN_BLOCK);
                    map.objects[i].initialized = 1;
                    input.use =0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 1) && (input.use == 1)){
                    desactivateSwitch(GREEN_BLOCK);
                    map.objects[i].initialized = 0;
                    input.use = 0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                break;

            case YELLOW_SWITCH :

                 if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0) && (input.use == 1)){
                    activateSwitch(YELLOW_BLOCK);
                    map.objects[i].initialized = 1;
                    input.use =0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 1) && (input.use == 1)){
                    desactivateSwitch(YELLOW_BLOCK);
                    map.objects[i].initialized = 0;
                    input.use = 0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                break;

            case RED_SWITCH :

                 if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 0) && (input.use == 1)){
                    activateSwitch(RED_BLOCK);
                    map.objects[i].initialized = 1;
                    input.use =0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                if((collideObject(&player,&map.objects[i]) == 1) && (map.objects[i].initialized == 1) && (input.use == 1)){
                    desactivateSwitch(RED_BLOCK);
                    map.objects[i].initialized = 0;
                    input.use = 0;
                    playSoundFx(SWITCHSOUND);
                    break;
                }

                break;

            default :

                break;
        }
    }
}

void isSolid(GameObject *entity, GameObject *object){

    if(object->spe == 1){



            if (entity->dirY > 0)
            {
               entity->dirY = 0;

               entity->y = object->y - entity->h;

                entity->onGround = 1;



            }

        }

    if(object->spe == 2){



            if (entity->dirX > 0)
            {

                    entity->dirX=0;
                    entity->x = object->x - entity->w ;

            }



            else if (entity->dirX < 0)
            {

                    entity->dirX=0;
                    entity->x =  object->x + entity->w ;


            }


    }



}

void activateSwitch(int colorBlock){

    int i;

    for(i=0;i<jeu.objectNumber;i++)

    if(map.objects[i].type == colorBlock){

        map.objects[i].initialized = 1;


    }

}

void desactivateSwitch(int colorBlock){


    int i;

    for(i=0;i<jeu.objectNumber;i++)

    if(map.objects[i].type == colorBlock){

        map.objects[i].initialized = 0;


    }


}




