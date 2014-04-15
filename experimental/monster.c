#include "monster.h"

void initializeMonsters(int x, int y)
{
    if(jeu.nombreMonstres<MONSTRES_MAX)
    {
        monster[jeu.nombreMonstres].sprite = loadImage("graphics/flyleft.png");

        monster[jeu.nombreMonstres].direction = LEFT;

        monster[jeu.nombreMonstres].frameNumber = 0;
        monster[jeu.nombreMonstres].frameTimer = TIME_BETWEEN_2_FRAMES;

        monster[jeu.nombreMonstres].x = x;
        monster[jeu.nombreMonstres].y = y;

        monster[jeu.nombreMonstres].w = 75;
        monster[jeu.nombreMonstres].h = 36+40;

        monster[jeu.nombreMonstres].timerMort = 0;
        monster[jeu.nombreMonstres].onGround = 0;

        jeu.nombreMonstres ++;
    }
}

int collide(GameObject* player,GameObject* monster)
{
    if( (player->x >= monster->x + monster->w)  ||
        (player->x + player->w <= monster->x)   ||
        (player->y >= monster->h + monster->y)  ||
        (player->y + player->h <= monster->y))

    return 0;

    else if(player->y + player->h <= monster->y + 10)
    {
        player->dirY =- 15;
        return 2;
    }
    else return 1;
}

void updateMonsters()
{
    int i;

    for(i=0; i<jeu.nombreMonstres; i++)
    {
        if(monster[i].timerMort == 0)
        {
            monster[i].dirX =0;
            monster[i].dirY += GRAVITY_SPEED;

            if(monster[i].dirY >= MAX_FALL_SPEED) monster[i].dirY = MAX_FALL_SPEED;

            if(monster[i].x == monster[i].saveX || checkFall(monster[i]) == 1)
            {
                if(monster[i].direction == LEFT)
                {
                    monster[i].direction = RIGHT;
                    changeAnimation(&monster[i], "graphics/flyright.png");
                }
                else
                {
                    monster[i].direction = LEFT;
                    changeAnimation(&monster[i], "graphics/flyleft.png");
                }
            }

            if(monster[i].direction == LEFT) monster[i].dirX -= 3;

            else monster[i].dirX += 3;

            monster[i].saveX = monster[i].x;



             monsterCollisionToMap(&monster[i]);

            if(collide(&player,&monster[i]) == 1)
            {
                if(jeu.life > 0)
                {
                    jeu.life--;
                    player.timerMort = 1;
                    if(jeu.life<1) playerGameover();
                }
            }


            if(collide(&player,&monster[i]) == 2) {monster[i].etat = DEAD; monster[i].timerMort = 60; playSoundFx(DEADMINION);}
        }


        if(monster[i].etat == DEAD)
        {
            changeAnimation(&monster[i], "graphics/flydead.png");

            monster[i].y += 10;

            monster[i].timerMort --;




           if(monster[i].timerMort == 0)
            {
                monster[i].etat = ALIVE;

                if (monster[i].sprite != NULL) SDL_FreeSurface(monster[i].sprite);

                monster[i] = monster[jeu.nombreMonstres -1];
                jeu.nombreMonstres --;
            }
        }

    }


}

int checkFall(GameObject monster)
{
    int x,y;

    if(monster.direction == LEFT)
    {
        x = (int)(monster.x + monster.dirX)/TILE_SIZE;
        y = (int)(monster.y + monster.h -1)/TILE_SIZE;

        if(y<0) y = 1;

        if(y>MAX_MAP_Y) y = MAX_MAP_Y;

        if(x<0) x = 1;

        if(x>MAX_MAP_X) x = MAX_MAP_X;

        if(map.tile[y+1][x] < BLANK_TILE) return 1 ;

        else return 0;
    }
    else
    {
        x = (int)(monster.x + monster.w + monster.dirX) / TILE_SIZE;
        y = (int)(monster.y + monster.h - 1) / TILE_SIZE;

        if (y <= 0) y = 1;

        if (y >= MAX_MAP_Y) y = MAX_MAP_Y - 1;

        if (x <= 0) x = 1;

        if (x >= MAX_MAP_X) x = MAX_MAP_X - 1;

        if (map.tile[y + 1][x] < BLANK_TILE) return 1;

        else return 0;
    }
}

