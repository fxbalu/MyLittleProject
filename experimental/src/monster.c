#include "monster.h"
#include "draw.h"
#include "player.h"
#include "sound.h"
#include "map.h"
#include "animation.h"




void initializeMonster(GameObject* monster, int x, int y){

    monster->sprite = loadImage("data/graphics/flyleft.png");

    monster->direction = LEFT;

    monster->frameNumber = 0;
    monster->frameTimer = TIME_BETWEEN_2_FRAMES;

    monster->w = 75;
    monster->h = 36+40;

    monster->dirX = 0;
    monster->dirY = 0;

    monster->x = x;
    monster->y = y;

    monster->timerMort = 0;
    monster->onGround = 0;

    monster->initialized = 1;

}


int collide(GameObject* player,GameObject* monster){
    if( (player->x >= monster->x + monster->w - 20)  ||
        (player->x + player->w <= 20 + monster->x)   ||
        (player->y >= monster->h + monster->y)  ||
        (player->y + player->h <= monster->y))

    return 0;

    else if(player->y + player->h <= monster->y + 20)
    {
        player->dirY =- 15;
        return 2;
    }
    else return 1;
}

void updateMonsters(Game* game, GameObject* monster){


    if(monster->timerMort == 0){

        monster->dirX =0;
        monster->dirY += GRAVITY_SPEED;

        if(monster->dirY >= MAX_FALL_SPEED) monster->dirY = MAX_FALL_SPEED;

        if(monster->x == monster->saveX || checkFall(monster,game->map) == 1)
        {
            if(monster->direction == LEFT)
            {
                monster->direction = RIGHT;
                changeAnimation(monster, "data/graphics/flyright.png");
            }
            else
            {
                monster->direction = LEFT;
                changeAnimation(monster, "data/graphics/flyleft.png");
            }
        }

        if(monster->direction == LEFT) monster->dirX -= 3;

        else monster->dirX += 3;

        monster->saveX = monster->x;

        monsterCollisionToMap(monster,game->map);

        if(collide(game->player,monster) == 1){

            if(game->life > 0){

                game->life--;
                game->player->timerMort = 1;
                if(game->life<1) playerGameover(game);
            }
        }


        if(collide(game->player,monster) == 2) {
            monster->etat = DEAD;
            monster->timerMort = 20;
            playSoundFx(DEADMINION, game);
        }
    }


    if(monster->etat == DEAD)
    {
        changeAnimation(monster, "data/graphics/flydead.png");

        monster->y += 10;

        monster->timerMort --;

        if(monster->timerMort == 0)
        {
            monster->etat = ALIVE;

            if (monster->sprite != NULL) SDL_FreeSurface(monster->sprite);

            monster->initialized = 2;

        }
    }
}



int checkFall(GameObject* monster, Map* map){
    int x,y;

    if(monster->direction == LEFT)
    {
        x = (int)(monster->x + monster->dirX)/TILE_SIZE;
        y = (int)(monster->y + monster->h -1)/TILE_SIZE;

        if(y<0) y = 1;

        if(y>map->maxY) y = map->maxY;

        if(x<0) x = 1;

        if(x>map->maxX) x = map->maxX;

        if(map->tile[y+1][x] < BLANK_TILE) return 1 ;

        else return 0;
    }
    else
    {
        x = (int)(monster->x + monster->w + monster->dirX) / TILE_SIZE;
        y = (int)(monster->y + monster->h - 1) / TILE_SIZE;

        if (y <= 0) y = 1;

        if (y >= map->maxY) y = map->maxY - 1;

        if (x <= 0) x = 1;

        if (x >= map->maxX) x = map->maxX - 1;

        if (map->tile[y + 1][x] < BLANK_TILE) return 1;

        else return 0;
    }
}

