#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "game.h"



void loadSong(int loop,char filename[200], Game* game );
void loadSound(Game* game);
void freeSound(Game* game);
void playSoundFx(int type, Game* game);



#endif // SOUND_H_INCLUDED
