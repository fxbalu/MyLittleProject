#include "intro.h"

void initIntro (Intro* intro){
   intro->backgroundIntro = loadImage("res/image/intro/backgroundIntro.png");
   intro->objectIntro = loadImage("res/image/intro/sprite.png");
   intro->frameCounter = 0;
}

void displayIntro (Intro* intro, SDL_Surface* screen) {
   intro->frameCounter++;

   SDL_Rect src1;
   src1.x =  intro->frameCounter*7;
   src1.y = 650;
   src1.w = 1050;
   src1.h = 700;

   SDL_Rect src2;
   src2.x = (intro->frameCounter%8) * 72;
   src2.y = 0;
   src2.w = 72;
   src2.h = 97;

   SDL_Rect dst;
   dst.x = 350;
   dst.y = 445;

   SDL_BlitSurface(intro->backgroundIntro, &src1, screen, NULL);
   SDL_BlitSurface(intro->objectIntro, &src2, screen, &dst);
}


