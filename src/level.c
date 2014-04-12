/**
 * \file level.c
 * \brief Functions to draw the level on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "level.h"


void initLevel (Level* level) {

   level->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   level->rectDst = (SDL_Rect*) malloc(sizeof(SDL_Rect));

   level->rectSrc->x = 0;
   level->rectSrc->y = 0;
   level->rectSrc->w = 70;
   level->rectSrc->h = 70;

loadLevel(level);
   /*charger le niveau avec le parseur xml*/
}

void updateLevel (Level* level) {

}

void displayLevel (Level* level, SDL_Surface* screen) {
   displayBackground(level, screen);
}

void displayBackground (Level* level, SDL_Surface* screen) {
    SDL_BlitSurface(level->background, NULL, screen, NULL);/*il faudra gérer la caméra plus tard, double scrolling ?*/
}

//test xml parseur :
void loadLevel (Level* level) {
   XML_File* xmlLevel = createXMLFile();
   setXMLFilePath("res/data/level/level 0.tmx", xmlLevel); // resetXMLFile pour recharger un autre niveau ! ty fx
   openXMLFile(xmlLevel);
   checkFirstLineXMLFile(xmlLevel);

   xmlLevel->root = parseXMLFile(xmlLevel->file);

   printXMLNode(xmlLevel->root, 2);

   printf("%s", xmlLevel->root->first->name);

   level->background = loadImage("res/image/background/backgroundworld1.png");

   level->sizeX = 20;
   level->sizeY = 20;

   closeXMLFile(xmlLevel);
   destroyXMLFile(xmlLevel);
}
