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

   level->camera = (Camera*) malloc(sizeof(Camera));
   level->camera->x = 0;
   level->camera->y = 0;

   loadLevel(level);
   //rajouter int pour savoir quel level charger

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
   setXMLFilePath("res/data/level/testLevel.tmx", xmlLevel); // resetXMLFile pour recharger un autre niveau ! ty fx
   openXMLFile(xmlLevel);
   checkFirstLineXMLFile(xmlLevel);

   xmlLevel->root = parseXMLFile(xmlLevel->file);

   //on recupère les premières infos dans le xml
   char* pathBackground = xmlLevel->root->first->next->first->attr->value;
   int sizeX = atoi(xmlLevel->root->attr->next->next->value); //a toi de jouer !
   int sizeY = atoi(xmlLevel->root->attr->next->next->next->value); //échec et mat !

   int i,j;

   printf("%s\n", pathBackground);
   printf("%d, %d\n", sizeX, sizeY);

   //printXMLNode(xmlLevel->root, 2);

   //on stocke les premières infos
   level->background = loadImage(pathBackground);
   level->sizeX = sizeX;
   level->sizeY = sizeY;

   //on rempli le tableau de tile, puis le tableau des items.
   level->tab = (char**) malloc(level->sizeY*sizeof(char*)); //colonne puis ligne

   for(i=0 ; i<level->sizeY ; i++) {
      level->tab[i] = (char*) malloc(level->sizeX*sizeof(char));
   }

   for(i=0 ; i<level->sizeY ; i++) {
      for(j=0 ; j<level->sizeX ; j++) {

         level->tab[i][j] = atoi(xmlLevel->root->last->first->current->attr->value);
         xmlLevel->root->last->first->current = xmlLevel->root->last->first->current->next;

      }
   }
   closeXMLFile(xmlLevel);
   destroyXMLFile(xmlLevel);
}
