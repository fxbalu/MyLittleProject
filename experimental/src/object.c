#include "object.h"
#include "draw.h"
#include "monster.h"
#include "player.h"
#include "sound.h"
#include "animation.h"

void drawObjectTile(GameObject object, int k, Game* game){


    int ysource, xsource;

    /* Calcul pour obtenir son y (pour un tileset de 10 tiles
    par ligne, d'où le 10 */

    ysource = (object.gid + k) / 10 * TILE_SIZE;

    /* Et son x */

    xsource = (object.gid + k) % 10 * TILE_SIZE;

    /* Fonction qui blitte la bonne tile au bon endroit en tenant compte du scrolling*/

    drawTile(game->map->tileSet, object.x - game->map->startX, object.y - game->map->startY, xsource, ysource, game);

}

void drawObject(Game* game){

    int i;

    for(i=0; i<game->objectNumber; i++){

        switch(game->map->objects[i].type){

            case COIN :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );


                break;


            case DOOR :


                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );



                break;


            case GREEN_BLOCK :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );


                break;

            case RED_BLOCK :

                if(game->map->objects[i].initialized == 1) drawObjectTile( game->map->objects[i], -1, game );

                break;

            case YELLOW_BLOCK :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                break;

            case BLUE_BLOCK :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                break;

            case GREEN_SWITCH :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                if(game->map->objects[i].initialized == 1) drawObjectTile( game->map->objects[i], 0, game );

                break;

            case RED_SWITCH :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                if(game->map->objects[i].initialized == 1) drawObjectTile( game->map->objects[i], 0, game );

                break;

            case YELLOW_SWITCH :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                if(game->map->objects[i].initialized == 1) drawObjectTile( game->map->objects[i], 0, game );

                break;

            case BLUE_SWITCH :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                if(game->map->objects[i].initialized == 1) drawObjectTile( game->map->objects[i], 0, game );

                break;



            case PICK :

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                break;

            case ELEVATOR_BLOCK:

                if(game->map->objects[i].initialized == 1) drawObjectTile( game->map->objects[i], -1, game );

                break;

            case ELEVATOR_SWITCH:

                if(game->map->objects[i].initialized == 0) drawObjectTile( game->map->objects[i], -1, game );

                if(game->map->objects[i].initialized == 1) drawObjectTile( game->map->objects[i], -3, game );

                break;

            case FLY :

                if(game->map->objects[i].initialized == 1) drawAnimatedEntity(&(game->map->objects[i]),game);

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

void updateObject(Game* game){

    int i;

    for(i=0; i<game->objectNumber; i++){

        switch (game->map->objects[i].type){


            case FLY :

            if(game->map->objects[i].initialized == 0) initializeMonster(&(game->map->objects[i]),game->map->objects[i].x,game->map->objects[i].y);

            if(game->map->objects[i].initialized == 1) updateMonsters(game, &(game->map->objects[i]));

            break;

            case COIN :

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0))
                {
                    getItem(game);
                    game->map->objects[i].initialized =1 ;
                }

                break;

            case DOOR :

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0)){

                    game->level++;

                    endLevel(game);
                }

                break;

            case BLUE_BLOCK :

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0)){
                    isSolid(game->player,&(game->map->objects[i]));
                }

                break;

            case GREEN_BLOCK :

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0)){
                    isSolid(game->player,&(game->map->objects[i]));
                }

                break;

            case YELLOW_BLOCK :


                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0)){
                    isSolid(game->player,&(game->map->objects[i]));
                }

                break;

            case RED_BLOCK :

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 1)){
                    isSolid(game->player,&(game->map->objects[i]));
                }

                break;


            case PICK :

                if((collidePick(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0)){
                    if(game->life > 0)
                    {
                        game->life--;
                        game->player->timerMort = 1;
                        if(game->life<1) playerGameover(game);
                    }
                }

                break;

            case ELEVATOR_BLOCK :


                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 1)){
                    isSolid(game->player,&(game->map->objects[i]));
                }

                break;

            case ELEVATOR_SWITCH :


                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0) && (game->input->use == 1)){
                    activateSwitch(ELEVATOR_BLOCK,game);
                    game->map->objects[i].initialized = 1;
                    game->input->use =0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 1) && (game->input->use == 1)){
                    desactivateSwitch(ELEVATOR_BLOCK,game);
                    game->map->objects[i].initialized = 0;
                    game->input->use = 0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                break;

            case BLUE_SWITCH :

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0) && (game->input->use == 1)){
                    activateSwitch(BLUE_BLOCK,game);
                    game->map->objects[i].initialized = 1;
                    game->input->use =0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 1) && (game->input->use == 1)){
                    desactivateSwitch(BLUE_BLOCK,game);
                    game->map->objects[i].initialized = 0;
                    game->input->use = 0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                break;

            case GREEN_SWITCH :

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0) && (game->input->use == 1)){
                    activateSwitch(GREEN_BLOCK,game);
                    game->map->objects[i].initialized = 1;
                    game->input->use =0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 1) && (game->input->use == 1)){
                    desactivateSwitch(GREEN_BLOCK,game);
                    game->map->objects[i].initialized = 0;
                    game->input->use = 0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                break;

            case YELLOW_SWITCH :

                 if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0) && (game->input->use == 1)){
                    activateSwitch(YELLOW_BLOCK,game);
                    game->map->objects[i].initialized = 1;
                    game->input->use =0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 1) && (game->input->use == 1)){
                    desactivateSwitch(YELLOW_BLOCK,game);
                    game->map->objects[i].initialized = 0;
                    game->input->use = 0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                break;

            case RED_SWITCH :

                 if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 0) && (game->input->use == 1)){
                    activateSwitch(RED_BLOCK,game);
                    game->map->objects[i].initialized = 1;
                    game->input->use =0;
                    playSoundFx(SWITCHSOUND,game);
                    break;
                }

                if((collideObject(game->player,&(game->map->objects[i])) == 1) && (game->map->objects[i].initialized == 1) && (game->input->use == 1)){
                    desactivateSwitch(RED_BLOCK,game);
                    game->map->objects[i].initialized = 0;
                    game->input->use = 0;
                    playSoundFx(SWITCHSOUND,game);
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

void getItem(Game* game){
    game->coin++;
    playSoundFx(COINSOUND,game);
}

void activateSwitch(int colorBlock, Game* game){

    int i;

    for(i=0;i<game->objectNumber;i++)

    if(game->map->objects[i].type == colorBlock){

        game->map->objects[i].initialized = 1;


    }

}

void desactivateSwitch(int colorBlock, Game* game){


    int i;

    for(i=0;i<game->objectNumber;i++)

    if(game->map->objects[i].type == colorBlock){

        game->map->objects[i].initialized = 0;


    }


}

void destroyGameObject(GameObject* object){

    if(object != NULL){

        if(object->sprite != NULL) SDL_FreeSurface(object->sprite);
        free(object);
    }
}


