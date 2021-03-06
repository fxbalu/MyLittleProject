#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "game.h"


// enum pour les sounds

  enum
{
    DEADMINION,
    JUMPSOUND,
    COINSOUND,
    DEADPLAYER,
    SWITCHSOUND,
};

void loadSong(int loop,char filename[200], Game* game );
void loadSound(Game* game);
void freeSound(Game* game);
void playSoundFx(int type, Game* game);



#endif // SOUND_H_INCLUDED
