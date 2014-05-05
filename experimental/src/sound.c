#include "sound.h"

void loadSong(int loop,char filename[200],Game* game ){

    if(game->music != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(game->music);
    }

    game->music = Mix_LoadMUS(filename);
    if(game->music == NULL)
    {
        fprintf(stderr, "Can't read the music \n");
        exit(1);
    }

    if(Mix_PlayMusic(game->music, loop) == -1)
    {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
    }
}



void loadSound(Game* game){

   if(game->miniondead_sound == NULL) game->miniondead_sound = Mix_LoadWAV("data/sounds/miniondead.wav");
   if (game->miniondead_sound == NULL)
    {
        fprintf(stderr, "Can't read the deadminion sound FX \n");
        exit(1);
    }

   if(game->jump_sound == NULL)game->jump_sound = Mix_LoadWAV("data/sounds/jump.wav");
   if (game->jump_sound == NULL)
    {
        fprintf(stderr, "Can't read the jump sound FX \n");
        exit(1);
    }

   if(game->coin_sound == NULL)game->coin_sound = Mix_LoadWAV("data/sounds/coin.wav");
   if (game->coin_sound == NULL)
    {
        fprintf(stderr, "Can't read the coin sound FX \n");
        exit(1);
    }
   if(game->deadplayer1_sound == NULL) game->deadplayer1_sound = Mix_LoadWAV("data/sounds/coin.wav");
   if (game->deadplayer1_sound == NULL)
    {
        fprintf(stderr, "Can't read the deadplayer1_sound FX \n");
        exit(1);
    }

   if(game->switch_sound == NULL) game->switch_sound = Mix_LoadWAV("data/sounds/switch.wav");
   if (game->switch_sound == NULL)
    {
        fprintf(stderr, "Can't read the switch_sound FX \n");
        exit(1);
    }


}

void freeSound(Game* game)
{

   Mix_FreeChunk(game->miniondead_sound);
   Mix_FreeChunk(game->jump_sound);
   Mix_FreeChunk(game->coin_sound);
   Mix_FreeChunk(game->deadplayer1_sound);
   Mix_FreeChunk(game->switch_sound);


}



void playSoundFx(int type, Game* game)
{

    switch (type)
    {

        case DEADMINION:
            Mix_PlayChannel(-1, game->miniondead_sound, 0);
        break;

        case JUMPSOUND :
            Mix_PlayChannel(-1, game->jump_sound, 0);
        break;

        case COINSOUND:
            Mix_PlayChannel(-1, game->coin_sound, 0);
        break;

        case DEADPLAYER:
            Mix_PlayChannel(-1, game->deadplayer1_sound, 0);
        break;

        case SWITCHSOUND:
            Mix_PlayChannel(-1, game->switch_sound, 0);
        break;


   }


}
