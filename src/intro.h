#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "common.h"
#include "define.h"

typedef struct Intro {
   SDL_Surface* backgroundIntro;
   SDL_Surface* objectIntro;

   int frameCounter;
} Intro;

void initIntro (Intro* intro);

void displayIntro (Intro* intro, SDL_Surface* screen);

void endIntro (); // a faire : fait la transition entre l'intro et le main menu

#endif
