#include "sound.h"

void loadSong(char filename[200] )
{

    if(jeu.musique != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(jeu.musique);
    }

    jeu.musique = Mix_LoadMUS(filename);
    if(jeu.musique == NULL)
    {
        fprintf(stderr, "Can't read the music \n");
        exit(1);
    }

    if(Mix_PlayMusic(jeu.musique, -1) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }
}



void loadSound(void)
{

   jeu.miniondead_sound = Mix_LoadWAV("sounds/miniondead.wav");
   if (jeu.miniondead_sound == NULL)
    {
        fprintf(stderr, "Can't read the deadminion sound FX \n");
        exit(1);
    }

   jeu.jump_sound = Mix_LoadWAV("sounds/jump.wav");
   if (jeu.jump_sound == NULL)
    {
        fprintf(stderr, "Can't read the jump sound FX \n");
        exit(1);
    }

   jeu.coin_sound = Mix_LoadWAV("sounds/coin.wav");
   if (jeu.coin_sound == NULL)
    {
        fprintf(stderr, "Can't read the coin sound FX \n");
        exit(1);
    }
    jeu.deadplayer1_sound = Mix_LoadWAV("sounds/coin.wav");
   if (jeu.deadplayer1_sound == NULL)
    {
        fprintf(stderr, "Can't read the deadplayer1_sound FX \n");
        exit(1);
    }


}

void freeSound(void)
{

   Mix_FreeChunk(jeu.miniondead_sound);
   Mix_FreeChunk(jeu.jump_sound);
   Mix_FreeChunk(jeu.coin_sound);
   Mix_FreeChunk(jeu.deadplayer1_sound);


}



void playSoundFx(int type)
{

    switch (type)
    {

        case DEADMINION:
            Mix_PlayChannel(-1, jeu.miniondead_sound, 0);
        break;

        case JUMP :
            Mix_PlayChannel(-1, jeu.jump_sound, 0);
        break;

        case COIN:
            Mix_PlayChannel(-1, jeu.coin_sound, 0);
        break;

        case DEADPLAYER:
            Mix_PlayChannel(-1, jeu.deadplayer1_sound, 0);
        break;


   }


}
